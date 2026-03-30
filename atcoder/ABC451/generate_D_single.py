#!/usr/bin/env python3
# 差分 -> ULEB128 -> LZSS（lazy）-> 0 阶 Huffman（码长 4bit×256 打包为 128B）-> "LZS3"+头 -> Base85。
# Huffman 比特数距 0 阶熵约 <0.5%；再压缩需高阶模型或算术码，解码器体积得不偿失。
# 仅标准库；C++ 自写 Huffman 解压 + LZSS 解压 + ULEB128。

import base64
import heapq
import os
from collections import Counter, defaultdict

LIMIT = 10**9
MAGIC = b"LZS3"
WINDOW = 65535
MIN_LEN = 3
MAX_LEN = 255


def build_good():
    pieces = []
    x = 1
    while x <= LIMIT:
        pieces.append(str(x))
        x <<= 1
    good = set()

    def dfs(cur):
        if cur:
            v = int(cur)
            if v <= LIMIT:
                good.add(v)
        if len(cur) >= 10:
            return
        for p in pieces:
            nxt = cur + p
            if len(nxt) > 10:
                continue
            if int(nxt) > LIMIT:
                continue
            dfs(nxt)

    dfs("")
    return sorted(good)


def uleb128_encode_u64(n):
    if n < 0:
        raise ValueError("expected non-negative")
    out = bytearray()
    while True:
        b = n & 0x7F
        n >>= 7
        if n:
            out.append(b | 0x80)
        else:
            out.append(b)
            break
    return bytes(out)


def _find_best_match(data: bytes, i: int, n: int, buckets):
    """返回 (长度, 回溯距离)，无匹配为 (0, 0)。"""
    best_len = 0
    best_off = 0
    if i + MIN_LEN > n:
        return 0, 0
    key = (data[i], data[i + 1], data[i + 2])
    for j in list(buckets.get(key, [])):
        if j >= i:
            continue
        L = 0
        while i + L < n and L < MAX_LEN and data[j + L] == data[i + L]:
            L += 1
        if L >= MIN_LEN and L > best_len:
            best_len = L
            best_off = i - j
    return best_len, best_off


def lzss_compress(data: bytes) -> bytes:
    n = len(data)
    out = bytearray()
    buckets = defaultdict(list)
    i = 0
    while i < n:
        cutoff = i - WINDOW
        if cutoff > 0:
            for k in list(buckets.keys()):
                buckets[k] = [p for p in buckets[k] if p >= cutoff]
                if not buckets[k]:
                    del buckets[k]
        best_len, best_off = _find_best_match(data, i, n, buckets)
        if (
            best_len >= MIN_LEN
            and i + 1 + MIN_LEN <= n
        ):
            l2, _ = _find_best_match(data, i + 1, n, buckets)
            if l2 > best_len:
                out.append(0x00)
                out.append(data[i])
                if i + 3 <= n:
                    kk = (data[i], data[i + 1], data[i + 2])
                    buckets[kk].append(i)
                i += 1
                continue
        if best_len >= MIN_LEN:
            if best_off <= 256:
                out.append(0x02)
                out.append(best_off - 1)
                out.append(best_len)
            else:
                out.append(0x01)
                out.extend(best_off.to_bytes(2, "little"))
                out.append(best_len)
            for k in range(best_len):
                pos = i + k
                if pos + 3 <= n:
                    kk = (data[pos], data[pos + 1], data[pos + 2])
                    buckets[kk].append(pos)
            i += best_len
        else:
            out.append(0x00)
            out.append(data[i])
            if i + 3 <= n:
                kk = (data[i], data[i + 1], data[i + 2])
                buckets[kk].append(i)
            i += 1
    return bytes(out)


def lzss_decompress(data: bytes, expected_len: int) -> bytes:
    out = bytearray()
    si = 0
    while len(out) < expected_len:
        if si >= len(data):
            raise ValueError("truncated")
        t = data[si]
        si += 1
        if t == 0x00:
            out.append(data[si])
            si += 1
        elif t == 0x01:
            off = int.from_bytes(data[si : si + 2], "little")
            ln = data[si + 2]
            si += 3
            pos = len(out)
            if off < 257 or off > WINDOW or ln < MIN_LEN or off > pos:
                raise ValueError("bad long match")
            if pos + ln > expected_len:
                raise ValueError("overflow")
            for j in range(ln):
                out.append(out[pos - off + j])
        elif t == 0x02:
            off = data[si] + 1
            ln = data[si + 1]
            si += 2
            pos = len(out)
            if off < 1 or off > 256 or ln < MIN_LEN or off > pos:
                raise ValueError("bad short match")
            if pos + ln > expected_len:
                raise ValueError("overflow")
            for j in range(ln):
                out.append(out[pos - off + j])
        else:
            raise ValueError("bad token")
    if len(out) != expected_len:
        raise ValueError("len")
    if si != len(data):
        raise ValueError("trailing")
    return bytes(out)


def huffman_lengths(freq):
    lengths = [0] * 256
    if len(freq) == 1:
        sym = next(iter(freq))
        lengths[sym] = 1
        return lengths
    heap = []
    for sym, wt in freq.items():
        heapq.heappush(heap, (wt, id(sym), sym))
    seq = 0
    while len(heap) > 1:
        w1, _, a = heapq.heappop(heap)
        w2, _, b = heapq.heappop(heap)
        seq += 1
        heapq.heappush(heap, (w1 + w2, seq, ("*", a, b)))
    root = heap[0][2]

    def walk(node, d):
        if isinstance(node, int):
            lengths[node] = d
        else:
            _, left, right = node
            walk(left, d + 1)
            walk(right, d + 1)

    walk(root, 0)
    return lengths


def canonical_codes(lengths):
    max_len = max(lengths) if lengths else 0
    order = []
    for L in range(1, max_len + 1):
        for s in range(256):
            if lengths[s] == L:
                order.append(s)
    codes = {}
    code = 0
    cur = 0
    for s in order:
        L = lengths[s]
        if L > cur:
            code <<= L - cur
            cur = L
        codes[s] = code
        code += 1
    return codes


def huffman_encode_bits(data, lengths, codes):
    bits = []
    for byte in data:
        c = codes[byte]
        L = lengths[byte]
        for i in range(L - 1, -1, -1):
            bits.append((c >> i) & 1)
    return bits


def pack_bits(bits):
    out = bytearray()
    cur = 0
    nb = 0
    for b in bits:
        cur = (cur << 1) | b
        nb += 1
        if nb == 8:
            out.append(cur)
            cur = 0
            nb = 0
    if nb:
        cur <<= 8 - nb
        out.append(cur)
    return bytes(out), len(bits)


def pack_lengths_4bit(lengths):
    """256 个码长各 4 bit（0..15），共 128 字节。Huffman 树深通常 ≤15。"""
    if len(lengths) != 256:
        raise ValueError("lengths")
    if max(lengths) > 15:
        raise ValueError("max code length > 15, need 8-bit table")
    out = bytearray(128)
    for i in range(256):
        nib = lengths[i] & 0xF
        if i & 1:
            out[i // 2] |= nib << 4
        else:
            out[i // 2] = nib
    return bytes(out)


def unpack_lengths_4bit(buf128: bytes):
    lengths = [0] * 256
    for i in range(128):
        b = buf128[i]
        lengths[2 * i] = b & 0xF
        lengths[2 * i + 1] = (b >> 4) & 0xF
    return lengths


def huffman_pack_inner(data: bytes) -> bytes:
    freq = Counter(data)
    lengths = huffman_lengths(freq)
    if max(lengths) > 15:
        raise RuntimeError("Huffman max code length > 15; extend format")
    codes = canonical_codes(lengths)
    bits = huffman_encode_bits(data, lengths, codes)
    payload, total_bits = pack_bits(bits)
    out = bytearray()
    out += total_bits.to_bytes(4, "little")
    out += pack_lengths_4bit(lengths)
    out += payload
    return bytes(out)


def huffman_unpack_to_bytes(hp: bytes, expect_len: int) -> bytes:
    total_bits = int.from_bytes(hp[0:4], "little")
    lengths = unpack_lengths_4bit(hp[4:132])
    payload = hp[132:]
    codes = canonical_codes(lengths)
    n_nonzero = sum(1 for x in lengths if x > 0)
    if n_nonzero == 1:
        sym = next(i for i, L in enumerate(lengths) if L > 0)
        return bytes([sym]) * expect_len
    out = bytearray()
    bit_idx = 0
    maxL = max(lengths)
    while len(out) < expect_len:
        found = None
        for L in range(1, maxL + 1):
            if bit_idx + L > total_bits:
                break
            val = 0
            for i in range(L):
                bi = bit_idx + i
                bbyte = payload[bi >> 3]
                bo = 7 - (bi & 7)
                val = (val << 1) | ((bbyte >> bo) & 1)
            for s in range(256):
                if lengths[s] == L and codes[s] == val:
                    found = (s, L)
                    break
            if found:
                break
        if not found:
            raise ValueError("huffman decode failed")
        s, L = found
        out.append(s)
        bit_idx += L
    if bit_idx != total_bits:
        raise ValueError("bit count")
    if len(out) != expect_len:
        raise ValueError("byte count")
    return bytes(out)


def lzs3_pack(uleb: bytes):
    lzss_body = lzss_compress(uleb)
    hp = huffman_pack_inner(lzss_body)
    comp = MAGIC + len(uleb).to_bytes(4, "little") + len(lzss_body).to_bytes(4, "little") + hp
    return comp, lzss_body


def format_b85(comp: bytes) -> str:
    """C++ 相邻字符串字面量拼接为一段，避免 kB85_parts 数组与 for 循环。"""
    b85 = base64.b85encode(comp).decode("ascii")
    chunk = 12000
    parts = [b85[i : i + chunk] for i in range(0, len(b85), chunk)]
    lines = ["static const char kB85[] ="]
    for p in parts:
        lines.append('  "' + p + '"')
    lines.append(";")
    return "\n".join(lines) + "\n"


def cpp_decode_chain():
    return r"""
#define U32(p) ((unsigned)(p)[0] | (unsigned)(p)[1] << 8 | (unsigned)(p)[2] << 16 | (unsigned)(p)[3] << 24)
struct R {
  const unsigned char *p = 0;
  size_t i = 0, bi = 0, rd = 0, mb = 0;
  bool rb(int &o) {
    if (rd >= mb) return 0;
    unsigned char x = p[i];
    o = (x >> (7 - bi)) & 1;
    if (++bi == 8) {
      bi = 0;
      i++;
    }
    rd++;
    return 1;
  }
};
struct H {
  int ch[2], sym;
  H() : ch{-1, -1}, sym(-1) {}
};

static bool huffman_decode_hp(const unsigned char *hp, size_t hpl, vector<unsigned char> &o,
                              unsigned expect) {
  if (hpl < 132) return 0;
  unsigned tb = U32(hp);
  unsigned char lt[256];
  for (int i = 0; i < 128; i++) {
    unsigned char b = hp[4 + i];
    lt[2 * i] = b & 15;
    lt[2 * i + 1] = b >> 4;
  }
  if (132 + (tb + 7u) / 8u != hpl) return 0;
  int ns = 0, os = -1;
  for (int s = 0; s < 256; s++)
    if (lt[s]) {
      ns++;
      os = s;
    }
  if (ns == 1) {
    o.assign(expect, (unsigned char)os);
    return 1;
  }
  unsigned c[256] = {};
  {
    unsigned x = 0, g = 0;
    for (int L = 1; L <= 16; L++)
      for (int s = 0; s < 256; s++)
        if (lt[s] == L) {
          if (L > g) {
            x <<= L - g;
            g = L;
          }
          c[s] = x;
          x++;
        }
  }
  vector<H> N;
  N.reserve(512);
  N.emplace_back();
  int rt = 0;
  for (int s = 0; s < 256; s++) {
    int L = lt[s];
    if (!L) continue;
    unsigned v = c[s];
    int u = rt;
    for (int b = L - 1; b >= 0; b--) {
      int t = (v >> b) & 1;
      if (N[u].ch[t] < 0) {
        N[u].ch[t] = (int)N.size();
        N.emplace_back();
      }
      u = N[u].ch[t];
    }
    if (N[u].sym >= 0) return 0;
    N[u].sym = s;
  }
  R r{};
  r.p = hp + 132;
  r.mb = tb;
  o.clear();
  o.reserve(expect);
  for (unsigned k = 0; k < expect; k++) {
    int u = rt;
    while (N[u].sym < 0) {
      int b;
      if (!r.rb(b)) return 0;
      int nx = N[u].ch[b];
      if (nx < 0) return 0;
      u = nx;
    }
    o.push_back((unsigned char)N[u].sym);
  }
  return o.size() == expect && r.rd == tb;
}

static bool lzss_decode_raw(const unsigned char *p, size_t n, vector<unsigned char> &o,
                            unsigned expect) {
  const unsigned W = 65535;
  size_t si = 0;
  o.clear();
  o.reserve(expect);
  while (o.size() < expect) {
    if (si >= n) return 0;
    unsigned char t = p[si++];
    if (!t) {
      if (si >= n) return 0;
      o.push_back(p[si++]);
    } else if (t == 1) {
      if (si + 3 > n) return 0;
      unsigned off = p[si] | p[si + 1] << 8;
      si += 2;
      unsigned len = p[si++];
      if (off < 257 || off > W || len < 3 || off > o.size() || o.size() + len > expect) return 0;
      size_t pos = o.size();
      for (unsigned j = 0; j < len; j++) o.push_back(o[pos - off + j]);
    } else if (t == 2) {
      if (si + 2 > n) return 0;
      unsigned off = p[si] + 1, len = p[si + 1];
      si += 2;
      if (off < 1 || off > 256 || len < 3 || off > o.size() || o.size() + len > expect) return 0;
      size_t pos = o.size();
      for (unsigned j = 0; j < len; j++) o.push_back(o[pos - off + j]);
    } else
      return 0;
  }
  return o.size() == expect && si == n;
}

static bool lzs3_decode(const vector<unsigned char> &b, vector<unsigned char> &u, unsigned ulen,
                        unsigned llen) {
  if (b.size() < 12 || memcmp(b.data(), "LZS3", 4)) return 0;
  unsigned ol = U32(b.data() + 4), zl = U32(b.data() + 8);
  if (ol != ulen || zl != llen) return 0;
  vector<unsigned char> L;
  if (!huffman_decode_hp(b.data() + 12, b.size() - 12, L, zl)) return 0;
  return lzss_decode_raw(L.data(), L.size(), u, ol);
}

static bool read_uleb128(const vector<unsigned char> &v, size_t &p, unsigned long long &o) {
  o = 0;
  int sh = 0;
  while (p < v.size()) {
    unsigned char c = v[p++];
    o |= (unsigned long long)(c & 127) << sh;
    if ((c & 128) == 0) return 1;
    sh += 7;
    if (sh > 63) return 0;
  }
  return 0;
}

static vector<unsigned char> b85decode(const char *in) {
  static const char A[] =
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
      "!#$%&()*+-;<=>?@^_`{|}~";
  static int D[256];
  static bool I = 0;
  if (!I) {
    I = 1;
    memset(D, -1, sizeof D);
    for (int i = 0; i < 85; i++) D[(unsigned char)A[i]] = i;
  }
  string s;
  for (; *in; in++)
    if ((unsigned char)*in > 32) s += *in;
  int pad = (5 - (int)(s.size() % 5)) % 5;
  for (int i = 0; i < pad; i++) s += '~';
  vector<unsigned char> o;
  o.reserve(s.size() / 5 * 4);
  for (size_t i = 0; i < s.size(); i += 5) {
    unsigned a = 0;
    for (int j = 0; j < 5; j++) {
      int v = D[(unsigned char)s[i + j]];
      if (v < 0) return {};
      a = a * 85 + (unsigned)v;
    }
    o.push_back((unsigned char)(a >> 24));
    o.push_back((unsigned char)(a >> 16));
    o.push_back((unsigned char)(a >> 8));
    o.push_back((unsigned char)a);
  }
  if (pad) o.resize(o.size() - (size_t)pad);
  return o;
}
#undef U32
"""


def main():
    base = os.path.dirname(os.path.abspath(__file__))

    a = build_good()
    deltas = [a[0]] + [a[i] - a[i - 1] for i in range(1, len(a))]
    uleb = b"".join(uleb128_encode_u64(d) for d in deltas)

    comp, lzss_body = lzs3_pack(uleb)
    lzss_len = len(lzss_body)
    assert base64.b85decode(base64.b85encode(comp)) == comp
    assert huffman_unpack_to_bytes(comp[12:], lzss_len) == lzss_body
    assert lzss_decompress(lzss_body, len(uleb)) == uleb

    parts = []
    parts.append("#include <bits/stdc++.h>")
    parts.append("using namespace std;")
    parts.append("")
    parts.append(cpp_decode_chain().strip())
    parts.append("")
    parts.append(format_b85(comp))
    parts.append("static const unsigned kGoodCount = %d;" % len(a))
    parts.append("static const unsigned kUlebLen = %d;" % len(uleb))
    parts.append("static const unsigned kLzssLen = %d;" % lzss_len)
    parts.append("static const unsigned kCompressedLen = %d;" % len(comp))
    parts.append("")
    parts.append("int main() {")
    parts.append("  ios::sync_with_stdio(false);")
    parts.append("  cin.tie(nullptr);")
    parts.append("  int N;")
    parts.append("  cin >> N;")
    parts.append("  if (N < 1 || N > (int)kGoodCount) return 1;")
    parts.append("  vector<unsigned char> blob = b85decode(kB85);")
    parts.append("  if (blob.size() != kCompressedLen) return 1;")
    parts.append("  vector<unsigned char> buf;")
    parts.append("  if (!lzs3_decode(blob, buf, kUlebLen, kLzssLen)) return 1;")
    parts.append("  size_t pos = 0;")
    parts.append("  long long sum = 0;")
    parts.append("  for (int i = 0; i < N; ++i) {")
    parts.append("    unsigned long long d;")
    parts.append("    if (!read_uleb128(buf, pos, d)) return 1;")
    parts.append("    sum += (long long)d;")
    parts.append("  }")
    parts.append("  cout << sum << '\\n';")
    parts.append("  return 0;")
    parts.append("}")
    parts.append("")

    out_path = os.path.join(base, "D_single.cpp")
    with open(out_path, "w", encoding="utf-8") as f:
        f.write("\n".join(parts))
    sz = os.path.getsize(out_path)
    print("Wrote", out_path)
    print("  uleb =", len(uleb), "lzss =", lzss_len, "blob =", len(comp))
    print("  D_single.cpp ~", (sz + 512) // 1024, "KB")


if __name__ == "__main__":
    main()
