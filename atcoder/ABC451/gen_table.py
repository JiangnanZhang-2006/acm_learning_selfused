#!/usr/bin/env python3

LIMIT = 1_000_000_000

def main():
    pieces = []
    x = 1
    while x <= LIMIT:
        pieces.append(str(x))
        x <<= 1

    good = set()

    def dfs(cur: str) -> None:
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
    a = sorted(good)

    out_path = "ABC451_D_table.h"
    with open(out_path, "w", encoding="ascii") as out:
        out.write("#ifndef ABC451_D_TABLE_H\n")
        out.write("#define ABC451_D_TABLE_H\n\n")
        out.write(f"static const int GOOD_COUNT = {len(a)};\n")
        out.write("static const int GOOD_TABLE[GOOD_COUNT] = {\n")
        for i, v in enumerate(a):
            if i:
                out.write(",")
            if i % 16 == 0:
                out.write("\n  ")
            else:
                out.write(" ")
            out.write(str(v))
        out.write("\n};\n\n#endif\n")

    print(f"Wrote {out_path}, GOOD_COUNT = {len(a)}")


if __name__ == "__main__":
    main()
