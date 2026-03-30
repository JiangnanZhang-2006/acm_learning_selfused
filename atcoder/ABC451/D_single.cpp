#include <bits/stdc++.h>
using namespace std;

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

static const char kB85[] =
  "Oj=VjPRkPjFj)Wqzrq0kC5V`asj920sfn1ntE{W5y2_fWs;bPos;Zi-yPC_YslKYIs;Q}}nyRa-+L@WEshhjI%d4xKy1J>mx~dD!xw*RRnyR|Ex~;0q%gVc%nu)5qsmjZ{o2i(YnwhD&y1UA}s;jEGs+XFoh<BN}iguWos)=}*d6$T0c6WCsfdUqgwuP(+T0+tmmX_AAwuQ7fYfdKC87Og<nLAi~TTGu54kpsp;?pU`Ln920r!j30lWCZ>hhu4&$;0DA@LGTJ+82;5Gr2f;Fd^C6XZl!Ztu?tgclMs9P99VUbe5m{(!-rOBGw&Mr>*f}{Gn)k!zT@7E#bwPb2|@&{e`qY3^;T4nK*mU_=oN?khX=%tvYCW(BaL2Z3}Z?Ccx<-??T}0Eq}%zE*yE-+W&+<oH$`K(AgRLOITY&^TOEI+NQqOq=ggdWG-R2hCubLba4N8amTxm%)`BhG;_B3IBDV18w*QfenBVXKXg23WX!Fl%s!D`<2?+7G_d={n~$u1e2ug_(is$nM>7q?KhV0!+{5OVSrod+rPf6*vOm%u3^>SsNMueoBAgy2INXj_9t<;Pzl+^N&V{jW##+Ky2G5Jo!}G${7;v{Xyk3qU1Upl@;gh=KJqUUb`{iyj<{ZJ`af#q@iQsXG;BkrIaf#q@l;Q6~Du1sXo`*3H+YT&?j7YfT@woe#S3G__Jbpjt!_GR+LfRjy7N`7N=iwYJk7MF|Q}%J``#ALdoO*uFJwIn2pR<oo*~h2s{`B^8wy@a4UjW+WbI||fG_dhuaDM!%e*CVs9Pvk%wS`!0p~D~fl~4T2%t!IEkl~B`s$b<&|0<XHRKLol|M;gh!`s8khD6_dtn@ZeA?w4-g{jeUsn+vp*7Ir6a;ewzY1i{<(Q>KLa;fM1r0BU++jJ?m=u>UbrrV)U&;DuAa;fqDT6}!PNO|W=|Mj#z7<K03rB0KTOV6B?x>VKl=}V<g=hP)Gl__+o(sHTNa=i3Egf%e89cF1d%+ht4r0X+D)@HeAc*k#=xrdz#lef($Z<_UC@WYWlHd@*pG4(S^^*aRVdfS*@!r=P7f@=T4HGklp|6rZ}V4eS9o&R8+{&hdYKmE{>6d}VJeExbBVQCKz9Kl1dP6l;28PuWJB|Pd=&ZQ2)D0T_e=hBB@oww3X+vz85^pm#wN%KCsQ0x=Z`bk5uO&{4x9fEY7(rNz6bbZ=s{>o^yiKqK1r~4^Guu2_=FAYpB4=24(C%x9g$u=GJv?Yh<I}Z6gZ=Ri}e4aPYPm}-D`yKLTbgA|`<og}+eT_G{4ZJQ+=S-c>nLC{_cRFP5bjjT5leyD%@bKZ<9#)>_9Fh1m$+-HLu+_tzKPQQuKF7_vH=1Or;U!NAH=1O|@RNC_P3D<5nq=#IMC*KirwwE|n0RpP4}VObOUF;8<EPT`)9HBW^t^QU^vV2ubocbh@9C4@(<R=aF7*j_s7t*<eQzx;^$B;VPk&6Bonm|XWb-wN@9C3etWB1&Ja5>WEn;l7iL(9Qh90auh;c`8u1@1!t%Yb?pZDThLsJf*?)Ayt>yx|JCwHz+?_8bUxjVgbcY8Gc?Ty4Lo;KFz9)v%XJ5#~eC+OLy=-H=(u1!YGH5)YWb;;oCl3k)p{J!b(y*{Mxw%JH%3>|WPZ&5zCsGnQZPp#@F*7XwyT%Y^uCJwnUb;;^-9P}qb)*c)@xCZ-No<`j~jk<Xobn-Uo<ZaW)+ozH4ru$r;ZSrrm$@=e;eXdVV`8_-2@^^{p-zTShmmKF`59JQP?&41FEo?S$;*a;iwTAi>p~)JX)TI(qi77;v^V8P&68?H$&rA8~e?2a7Q$dKCJ_=|t6G4cV^V0r$Z7~y5dYj4Vyq=yUY2rqnBx&MCpHjkjk*A3=YHw2#WW<><CQVK1K}}8SWE9lirAd>ez)N*MHac4=_At}s<EEzdH8-il%$z*Q!_1kC1o)FCV*xW536WDVfSi(@eU$5z>+Gj^regs!7zyqvsl80T0&*%(#!sTBU1d7!Dc4y}y2@qn6H|Jc6*V`hsl87=Wbt=N`KC^?MC&9^kx4iar~G~W>^$gkC!ddV4=xtwiA@rkB{WKCl;|<i_VqaBFK<(2Wj0n*Wo0%vDYUYi92D5#rpE;@Z&PK0p1jHH%$~f-`eRL&3T&`bB&N#+HdraL!A{0h>}5{IRHKTTsgq@bpLVid-lv0M3MpDtD5n)wII5||RZJXI{nDlF>S0(*+unK~h8sw92UEIDY^kl4I-Syb5~rambvvZ$cS*$7PP4#H!ZiOpROsVQjx^udOwQ>)L}{7bC+nFrJFh+)7=GAVogW8158!@})}ExP>PnuZsp?9eq^WtjP5orN-FMLN;k`RP1=KwFWDK&Nj_Y3uVX=k8KLj+;v_8#b+HR9+x=fWc($-BaWWvHvHo{lM<Kf`LG*X<ITB(()l&2>xRXJ*@N^(-1pWj(2PETfJ{&J`0u%FIU{&J-$$x3o%YNaX3N^(-1o4HdZz)xCK^`%c*RQ07!1!Sc;A!R8}PFku`oSAy5m#Uu~Oubag)k;&e5d6^X&z7Yr+URlxDb~>PVQNyGogH-O>!(LuIy&jm*G`VQbam6Cu9T-FRgx;nfng%7kyc2nBvq0s$x3o>t0gJPgIO?ZCJki4te7>E2C{JWQk3NX8mWnjoOM*CIX+61rzbsCDNajy5|rfR)br^kj>>oRQ#VN|PD)df?Mt;T)VoscOSLZ4yHf2-wJy}VQteB%F4VhH?MhRVPNtnrI+}Gf>S@%|si#v;r76jqu9T-GDaq-~o65;f!fz`k^0IF$Ci1d={nqvycwC*uWbP{`aak+yQ~fI^w}h9|lJde|PE9RT($!5ZRKA>=YN>rWFQ+B+<i4Dj)05SeJy}!Ll|5Nf`f^`RPFAX4PD|;@eK|kAM5~INT#3cVn@N+4kvWAgrzU2)UrtPwRKA>?rBvlArzuq}cWIKUm(!BPgub26Laa6L<4)4Dc9oN~te9LB`W2IFgq{xtKK+D)aSc2<BU4`H6=B2{B})>eiBiO=VpN@qnu$}BuAW_+h*dULZei#{`9rlWsHKR~#A$6sCXFVIEvTin6zwHVe$_o`liI{f$&>WPpQbd>(M=5$uNr7*riO}Z_Nitxvl@OnNnSLs8e7p%jHbV8ob`0q?NiH<F=9_fMD%1&Hp+9flh{)hEd)O-JxB)vB-^RCQ-KnDN_$FhB2ENJc^YaqX|b6$GbYAl*vy+5lg5cMig?i`s$~C-nro&_JZY$zH4`SHWYkQWiIc^NJXn*(i~B=;4h${LtDT0N`BPgQ?1@Swr4n@VCr=`D@+Zcmn)Nx%emWo49K1BJ@L}pg)algQ;_G4iOgNM0NS``H`O+pFNz=%faV8u|hZ14Lm$N2&5iaIW1~l+vOgNJcB*Kj_;!HS`4kYlSPYN{t>Pg_npO$39i82ad#GCn(e==|8OgNIn$%hhtt0{*Pc=l5cB>hTjET^)k-r*){%0my?F)Q0b+8gLz!rZ44aI2>Zx^SzdIFlZ_Q;8|Wl;TQpC9RaTvX+Wk*-g$eQ;8|WolTUd5>tsO#Fr{~aicObBQi51GE<2?I>}BXrxI`FN^vDPl4(+DQfX7%#ZFSXQ;9b*rsg!<#+#Vaa~e~LIJ&7$B+jXwQ#z$MlRl+5lAK9SB=aUpaV47x@M9;#VLlrP@YqUmCsAc7#FXMnaVAYnnwd2+YGl->5=}Bwi9d~GrxJ70B{-8aB4%Vv%!%>oCVfhAC&;dp;?2WT4xrq|o0!vc8g64v%xSreH!-DoQiSwoMr5HqC{IC36VinA=OaoJ(uDNAnK#(U<xHMb$wGQio|8<JC#4DLLV8^(bfwalN?j>*rP7oqrdqmCo|tl_3Fyk4{{bw@miyGakul=$;qOE7z%tS%T13l8nQ0R(B4lYNy&8FnZtL7b)`w1MZ|-6H;p)R6REabyXjG{ZeHA{6l_E-!C*+MPM3<8#<jHw5UQCyhB}kA`q)DrpDny$Jlf;cRb0)52)y$f?lUFiSi7G^ypAkH{lgNoYS(B)dI*AjIq@N6F$WpTpP8_k&-sj=lLxBxsJ-Az$j0E9hrwbi8Sm~I+Onh|AU?yV$GZ+b&z)cdGB{WKCl+h`ez)Z#he+4rb37Ei4#sYkWKejS(>Tv3C>Tv3C>Siz#q_UkQl<6#{V*xwWGZ+bCx@IsF;jWpC1hHi-*G^7k+tW==beC?Ml{CC9EH5E&VnmqL(;B*CS4>EfI_ZfLVnmpcCL~F1Wi70ws+QJM-NsBvlM*EAtfnMMi4tN&mr8%MX$2sp6oQab5+vGIOh}UwB;LxHktQTbR#dAhRh2)kDsnZ`5+wGcPii#wqfcry_M=QllZUFCjBbJ(C~|_@!+j5e9}uY$XOzz=o>HVqpi-nsQY5JoREaioC&P@EW=;Ks-`Gl#B}kL0vXvrAktIly<x7<=RJl^+N|7TnREa;8WT_H!@+C-<sF6B}6QQ!4g(T1^QY7SSrAU+AjXl`Y-Hkoi)7_0d*wVzQQY3<qQVLXwEflE|REas*(xgdJB-hNJ1~O`<O;pLMnJPq#$x<Y#5>$yYie(haDU?$vrcq3yl_E|`x>Sij%0#IWW~5BiiJFl)3Q4n5;$isEyoSma=50*cnYA-&X4K?y(-vgKnJPt*hl+S#KI$H{JyK7!p7u7n8#r-BOG9l6P~?v5Y?>uBN@$egH>vd0;y0<pZ&QfgrxCqPtjXran#q${GHWJIBYK=h^)1xyw#ky-rb~LBe5vQkofiQ$lBeyNGF#N!)=ukeo=l14$ev7z-EER}bndpv{M7EY$$F>T!%tODRZmq-Mml|UKD+C}NKl6iZMLbCnKE-GPGsXS(&}X6Fw=~~PBRTS%rxbc{20mg)a>l1XJt6dG~+PSUu8Ak(tJ!b_?T(`Qz!jQnS6BfrcXL#_?T(eSxvUpG%9VjskYjs2-CO1PTvVQ5vKw);6|JX(<xOgpNkJV97*4|F!Ij#wM>GU1u_a`6v!#K+NT_+9Q=4{;m)4U)j5?pl{u9?+(h`wd$@`2;wQU^p3c=Yb0<?8byFqwB4%St>_ooAOx8MIVkPz>Ut%SsiD@EQNS2Z%q=|iqoNAuV)jnl(<gn9$8gf`^Ya&|6o^;7;B3j6v&ebSZPiJeChvA0O9Rb_mp^liCiQC|(0~t6N$=l$kZ-SjvY1ViN_NGkyX`q=j6DERW?XXj6GIrQ0u$en-A3hrxe%M-_oVn<K17CWbq^a6Um{_UwB~PI$ZE#cX)=jPteGd*B)4G!C9(*zftulLfI`~Tsj4mPgA*O|)l&YTQ3VWC-%vDZes&f@l#ZJ1qT}j8o!G>tJpqEl5)QN9FIN1}8kuB&Yy#(&1OL_@`GFZe-q{*+1HSwjr1h=4<G9|qPx1g5v6PS@Xi4&NSIf)aPkvWMIoKoI`Xltdt1mkL@y#(fJr)$7YZBBQ3n|Tv4*61Pmq1&9Yl&5Q<$P}krL&=4yN^*F0Q^TsB9aN<`KOI!1IVny`Q<9YA_ohv}spVKrys5X9DNagLll&^BDalH5Qk<Alr?tUJ(xmBA|7J<jq_vWi<mW1<IaN8zsY-HvYbi={byZT7<hPM2PEVMppGh=!Q@^5_x=BiMQk<7+U8#1Z+LvlwsdlB>mug+9cBR^vYF(*zrP`NjQk<G~H0o*8)2XLZPNtnrI+}GUPE6f&r8y~1PfldsR!Vjgd097=lX+P;m6P}Gx3Js7<nAjcaalWx$zOt>=~+FzB)*)NmJ<4MX=<jHs%dJa^yJf3OX<mdIWMOr^yI#ro~)_r%ATyL>dKeXlKOITwNm<WUrtNu$^G&rTvX!ZPA){+Oq^Va%qe|2Gd0rsa%8Hd^yK9#rzurAN~vqROqEo=oR%yl^zM2UVXuc8c9oN~tevG~!r-USteadU@OUZr>?9kAY2nEln)fiP4j{2ASd}bFmL*FPr0i7GN}Qc^^6cC~sj{<k4?-Wx9jR?aEJl_iOKK@JX*6kVMJ=eOX)0^>sq0Lh)*@a^pQbeZF{Xx!XlSK)(?dlxG*e%-OEIOG)A7<u@uhgu-imx>HTzWOtERtdo?MBG5_&Qxqat~>Q=O!q!kq0b1U#sIBc7$6hm8z4bY^afd3fpN<ECzkdARB3<ECzkX6U3OO8YdrQt3;jE|j`cgA#XYaAHZONcL&Psf8L>nJdhd=1TJ=d6JY#N+hKh_J;Z#7+as+Hg+0w#G2T<kuy|NHAOXYCay%)$eraR^=hZ%$K#>>Vavly4YWCUX<_{#|1h;Y#W}tPwjZ?W=%wU|c_Lm&om~|3Bu=i1b#zm!qMcn7x>IS0n6oFr8hjC_S4BFyDVdQvx+&GsPOge?<4yc&-%?M4G^a9kbW`c6)zM7SnWZyIb#zlcr&mQTCQh!3V_8nFiezR?jLDIiFZfC4*-Z`~vS#dCLfRYXUc%hYQBKCfb~Y2Su$js!*;q{F6wXmh<rL0QO%;^USx=&-ippiN(>X;mlv7z{Gn7*~MKhFB?Wu<vcFK0jcFK0jcFJccrzKr8lv6oHGgVVLMKhFBwW^)1RPAb~LBLM}x@Rb+T13l8nQ0R(B4wmZ<rLA?Oyv~Wsk2jNrgDmHRL)UM<rL0QOoExpDWI~QPC9i~Q>wC^Rg}(APt|2Jlv6oHGn7-iQ@c~UQ@c~UQ#nODRWp=RldhS{DgWscIYm6#6U~u4*%R;5O{$s7DgWB(oTHnDrX4|+kuuUIT13l8nQ0R(B4wmZ^;FByPT5Y`OuYol&`#Y<y#&k9PZl)G&`iAqx>KmfNGSy}^b;>ZJ5@6D6E8tB^b<&?kxe3+MKp?O6w)b|pq@o^%g|1)s%7XWZB;yO0%$6y)ZV46so7EQ;qOE7z&wc)$dNpW6UdP~i4*HmPKHF<RZsJ=aSvJ@Ie}j08+dq-wlW(;;bW%@9XMF&*-=b<bnK|7WkowGDcMm?5}GA6N@$ePDcMm@%8GvlG8;tB(M;_W@6^VPKB}KpPpYTYQ|hUZ+9%Ib=c)75$ZZqqDUjMH88T!xi8Yka{3(-}GIJ(QWcWBqdu1<d`tXtzA;S*MGxifdVKep<&EF?$VLaXPdAsEEcgg1OlkHhfHkx-zbk)<QuAXlBJl*nY>!Y(xR{1qs<jhx0#dP+mr$=2nI_aw4C(^Qx%{#>%nmaVq*+}9@;!i@#dKOdAvYrPCFVuEv_^YSluAhp!ek$qstE00|-(^3akI+K?A0+!qb#`^I@ZrUp-KuBorhdw2?4|A^W~`;|B3|Mp?jmb;se3YVv8R<Xc~d8qGHfvuVThAVn+!zQVkW~8J^0h#jXn6&-;F)^(_x61(<ZlSpBB1JzfWc~n|_!PrUYsK{K<hDU`CqVs%)z!w`-J!`V}F@8wWcLJU>)2$1jeTG?M0$U1O!zI$dL>);eKKoL8mC!&wS&`7rzt+e4Q-#@Ze{E|1}end>Q;$4}viomG_Ttf%nAPvMA{lPAUWlP0E3Oq!WBGHP-3laHjC^*H)T$I?%W=_gYnbuuSYB6Tt+QzCqdN!qFMDJS~ZPmxJ7(kIBIom7d{NSq0is*yUW6RMLz4|W(Z$Pm}3?^E}w`_$IaPvEAuifd@5wu(bupBYZC9W9i$QrS+*igr{}=&22QXK17~>E9{eDc>pIDc>pIDc>m#dVb|Ua-X?KYt#6t4SIJoBsJ+Zl-c|#lbJGeCQfAD@RIh*UfE0ADgOBSSYATl*K8ArnK+4)h?zSYDa6d3jTG!?r(;Ds8Y#&s*5js$PQJ=@_EWK<osAUzmQ!7@PPU45v{SuPy;HqYy;HqYy;HqYU9e70x@)!xuGl7Ss$Opr^LUyXsiCTx8mZ3k6aA~EyI`F3iO)!!^oh?%ob-vV*eBSkpYiJS5ZObNIN!%@4}u>Mx7Vknr=+K(rqc;OdYeon+F>Ts2`%;M?M$EJ!B5RHYNbt7sp(-SrG$*B>0u|Ogr1fXc6F1ptefr%c2$$Ite%z<clHwBUY;b$klv)#lOerKopj09Or3Q2I4OHsE%oWYnJxACNL7ZW9YLzBnySgFteUFHs;ru-$*QcM&cb=uynH<fe<*gR?!ikDru!8?b_#FfP5f#5uv7P7r%ft(SE;X=Jqc6tOrC_P=t`VE^*DX%S(P|_>Tvti@~>0Ql|1QFq2MR#l|NLe#P3tttej5uH<lBL-ltntIGyT!8maVZr(mbc;3c(G<*8^Pfe&1{@l&FaIw=#Pkvb_8qLDf&6GK%x=OYhV9%<aobq@|4k(*MSdf05?#Ti;w(4`JY(e0D!NS`*6b`mEIy-udeaNE@3x2eN#Q%AN><uZP_)AY=rt~C8|r~Tlk{otn$B53x>uE9+n*)@`;vQ*t-r<*Ek=1<##p2cL*?UUxnpEgAKvL=sgno8-T+b8}hquVFYQzwR>T~Ds3*HirQ)8Z-dA6^ndgg9f;+NQS3Yiy>r%4D$9(6X5<G|6G6OARtuY5%h(ml-%^Be0R!OqLpCu+!(+O>eZEMjCM#Y3IzIe96&crm|$#Oq@m<b+%K|+NW%%rL|8>YLnwl4iac^lNL0^jWJ_PSkmgMTE7+^bU2f~ZeiuZ+_qBLOJyyTwo=(i+f?|<d}oh_t{my?ZBv+2m{XWjbBLc6P0k{2aT9Zhp2pQa%*oV7olME^Vkb`;d)SHZVkcFOp7tVp*op6AAtDkXA`&4Yd)SGTQ`p+4%dVV`8e+zrjv87>mXap2WVDejBu`^%lj|q3waP>A!)XqH(BPyo(+?3eI4O&an7GNI!A%Ydbup(|;3su5XQNE~$)A}s^CxS9n>mxU!A*S0+Ti){*u(b1)cO+Vq5KQm)a>O>&Q#vwr)4U3Ql`@dJNn7A!SA8r!+L1sx`&?(f$Gej)(*ZB!($7Geh6uyXkArJ#tLpQQ<tioy;SAuq}Zv}*Gri=_;@hQ843w=B3#Is3JH{vGLj}jf@CNrj#S7{Pkv;th?_Z*_B6eXG87XbK{9eCLV{!{CPIR8@+U7Ma`GoHB69L4FCu)UG87ZGu9*r6l&YBu3CvYZ2LV6DPIG#m%!!!mbP)W|?aoz7Q?=0K3RA72<igaYIXo(<;Z;uxs#2VuB~+z3DNagLl9c54W>02R)YwmERQ6>`Q<9YA=BlMB$x3okoSWHG`tVcRl|8vr|0YjvRFbk%oS!PHe5$GPs--E(^=zdn$<)<KQ<C09r8z!Yo_!?I*-rk7X6Yp<$x3ovsdlB>mug+9cBR^vYF(*zrP`NjU8#1Z+LvlwsY-Hb)YGY_Q%<IxO*)!&H0o*8r8zTo(v;+-IXyX(d08pgP32_XR!!w(-d0cFy57TY3zN94oyBDCD<yskf2Cyh@RIs+URX=%$)&2ATB)U~m(!C?RWGL{^yI#rm(!B^a(c3-t15c3r>iPoPD|;@%GFEh$$dF5rziKwm2p#xkvO>%X)<wgCorY-<jmJg>B*9+m(!D!s+^@%<tnAF?J`wT`f^yXm(#iERffJCY1&p!(z14ylM8~MLb7delfmGp->{HwA*Y8VYHQrWtT=+isbW;IDp-{)N|UiuQ7UqE)627Q3Z}}<%smKyD0Zc_6tNmujV-98(WKF(wG_6ZousL++NZ5DdsvBiGJcrT^v0SRDWRg3<4p||(9unP)hx!AV^7CPE5?=MOL{5sl-KQ3p01kxs(ErIEJ^6do{Wj+*-mzndkSL3pois$sQ}<an{_toa3W7>PiamBNx+FOBTYulHZvy1WZ2A`8Ixl&c+n<NPZ}iEOrP<yO?1hpjWrV{qGZ%enu(K9GI+5kixPOTe`s%^!G*cCbFkB&Dr;k%ktsx!qE4Pf>EuqHMEKN`UZ**a$3yzVmxh)e3_VC%ojRL*U2H#ThZ2106X!^uIz+>XI(ZWgB*Td?;!HS__GHguCEUs2#-0pmhZ14Lm{F!2Nrw_)#GVvs;YOd`Njw<S^30fVCP7R%lYcUA=1u&`hZ0zsFyc?uWiaAT9?D_FpQ%k{l=f8n+$7CeNMZXXC3|RFLwyU_Ta@BX6?EZOP8D>g5@Xj&aV0pCoJme3wX&ABQqfCWDY?c<aV0pDsj`&fN^vDPlI2ehG-gI*W=3RYN^vKrSt-Pn;!XUiP9&!iO)5<)O)7hssmfPMaVF+8+{T-j({mbbV@h!+7gZ_5nbk9@XH=&WXVj+>Q;8|Wo@B{RB(q^Y3}pChC&OVr8wpM%>MW%=lAK9SB+03hQzoWOOq!J9Nv2A1C-JP5;!b)*rxIplOw5Uykv=^n&#6u%`4!TfS-5Ip)Ek)7a~f`AP0VSzjW;o-<}|M=P@as)%#<gk3Fs+8dQhI6<Y_{BP@b2wCi@vYsguf?C{Icg(rJ=}^r1Z{PfMjPl)6&sOQkN9x>AJn%U4Ph(+*UjJsDG<;3b(--+GslCOlpIJ?MTo23kbRNSSF9Eh1&4OpPS>qfaqS-Ft|7(CN)B{meh+9{Exv(5azPq)GHt`YKe3Dny@>G^r9^OqY`-<jHw5UQCrDK}wM(u4JhaY$i_<G}X+Sxsz8iYUWK`$x<Y#5@viv^5#z>B=KfWqD1N>PC}A=F{dF)XnXMV;b?Q-26`TpKIyyn(`Kg4P2awoRW_<_{q)`Y>4_R{{q%y6QVKyxDZBU6wNw1BQJF8j^w><FcNsNvCaz@F%$m8AS2ACF>CX5G|J`z3%$?-))y$msI(btit{Quo$!mvZ9-KL2M?XIf+8S6`hhGi^KU_4X;(mS`C=m7G<-*kWC#MlIaT6!GJvf<@iJ3jg>F!TX8BcP0X6&YJ%4Y1QZpvotr@1{m`za>gq&)L}+e6WZUUha-{(5ohaq4mEQjIPYr5ai(e?2ef^U(ef)WaZl>TV-V#A((k);zJpdiPNCp>lTWcJHeXh8&5m_-&!nA5l-Jr_^p?dkcb;$>4uv@ISJCTy$neWcs*i=2=dE9XRS+cwR!_^m)AeEg|8<m^n-I*r~Bol)p`qn<Y6*^yM$p;f*<t{VdFuW=k_AnUc)O$={}VPEP$SOq`wiT`BXi)3Z~ivY+UuO=UW3DaqfbCx6SsQwu{;WjiNZ4<yHJp)5Z+klv*E>G<VI^Uzb}a1;M5CPR9j-YR27?n7@2lbn$`$rGHBImr{8kuB*Y==%70aP1GhHOx69I;RbXdkvI1LbGcP^galDLu37O(B_ZBew#%$ihdjP^py0J{5R?NZ_<=$b64)eSq^3%96JM;ze`muRJBsoOI10G^zGE<FVmR6PJ{lFjZ><}OGPadv{KPaMLApa?bPLO(?X{!ewsxzifI(mDWp?K{up|&@*%|;l`2K8g=kxxD6OHXhfs7fCqp81GABbKbTTIoNiXA1)Tj2ZaSEn2dzg9<{!r~r)b#Dt?bO{*O%j?VH&fGfJv>;`VK3c3oo=Mb)yhLae7Xq*Afyz6kW=N*PSsDBK|Wms^*IiD6QOGl4jx<sFF`ofAtG8SXr-c-idrd`pq&kL%g{_oQ!hawRXkn-WEA?F)biv{slDsr`=RGUi#)5;x0NmBOL<eHpqUv{qoAD~1nB4|M?pU7nYj}<rfx*d$ekSo=;$Y(B6(M-^Qb4zpr1-a-QuTTB6ad7WT#&ueRVvm)b$kqITQCO<zA<#r<Ho1vYu7yc4~RJ3EU}P9Y4`eZw)_AI&pJ)@RAfE!x*~c(af4TlSeXixC!>APL}~XTm<QG6Q#gU#HPN=Ua7CLn)@lz;3rFfmop?^`kyxeK5hbfwo-;NUfE0ADSKrvY^3!ub;<vVV(XI^T%8n&`FBbAcS+XBootEL$efKN`YK}Ulde;)Q?664Q?64NT$u$r41R(dxO1n$u1_+`d6rYmvXtUa)nzHfl;TQpC&8{wjLET?HZvy1WYfl+D3gT}SeZA`rwSzDM4yf{{BfrtNjx~y!;LsmAg95uPvcoK_zBQRnS2E5WKO0;|0^l-DJFeSgIt`Iboe#N??#^VY41j!^l9%#p7d#ERQNUA{56o@L#93nllI>0VW@{3bl53_jGxyLI&2i3jFYjGrom2|1wX<x@^4f3OrP@_eu<OxOrN4;)L^Eg1uIONj1<&hr;~c0=PG}ksq5mVUR2A<nyeJ<>n5uOJG%+0!APY|RtiTdM=D`Vp2jMEc~fbLpojd!^A%fYRfqM4vLD`VV@=Fyxs5k5rsg!<#+#VZys78nTtfaIB=+V{xgNF~IB`Xm)*I+jha_iq$%h(zib?NAnAj=o*i38`#=%T%6wd9FshKY0PEKUIjV|L)&w`(y1u-K`?%6+13TJl7<4T@1sr>O%^2(p@GI=;Dv8<WhvU1WVEh2K#CU<O|wRFzyllLi|+b2q;o%(i4c1m_i"
  "a`@>a$(`FKcWj@c%6^L}`Yfe=`f4ntefn45q_ZV``fFxR;~6ogObZEarG5HW->1`4JGMyo>EukFM9Jh#nOt=7rbzec{PB`K`e$~@no~QrOzzn+=1#8(D9o4frTl4s8ehhrKmE6`^P$9_O}U4c3v+=oa3)R!$-tR76DI;>(e0AeO&-}Ul)6&sPVW^h6z=g;yTwlL6*PNf(qg6ziGw0(F;XcLNs5|GRKkrkn5m@2O(rU8B~3)BsFgJmr-?FYF;mp6nmw{^Y$n$cJULTqh?<#GQz~j@O-!k&l{9-~`?eEDw&$VvVYG)pTHz<@jXWGwwZcyhH1Oj~TqL!^P3(!*cnK_tEQwW0s#Q?JLkSEd>}Ep?&xXbywicyYx#)ib%)Lt0Qngg@cquJZma2BRN%AZwYlYuK!-n+9)w+kD41v>3pKl9a31P8?#6JWy(6lx+lkQ<B+`>;@vU>HC*Q}bZ3RAF~33&K;FwGIqO@yhil_Q>>jH&3#k<UoyrcSa)Jv&*GQHq?cgzV)`&Qy+iM?E$2q;t|a=^XU+<xgHz_2o}qRQ2UgUR0-9Bc7I)QaR~wRU@9C-Bmi?0&vQFo$76*O<&*8L;a!hPO@v5en@5y@KV!pu7@C6ZY`nY!ql|fCyP})TB+jIOHIOm`l?!P64P*&n}oF7ChBC|N}gqe+)A5?Qqypjn}p|TrKaI6HwkIDOgU3;!B2Wr_oYu>WcQ^@HImbCoZVFB>ZdnVEjJ1EETyL5I*O@jxK2JqwA?2`r|+bm1(fk<r*BCuHwkIDOT{k~yi)N?#V-`RQt?a0FBH5|@k_-o6ueULOT{fW38+(0rlCzjnuRqAY82Eds8Z8#oxOCl+$E;rH!~*+vRm0s6=dO7P8DR~R!?(vy@uWwCYG{kYbKVmWT~hBYbF*FQk<TRgrzw=imBvPPa>*PoS*MiDNagLl9c47IVny}+^M^jH*%)#RHZp7PE5U2r8y~1N>h{N$edRJIY|?gkv*xCl#x0$DNaoFbfq~mwNjMi`IS@VRZp2!J~r(#wNjMi<1D2q-1I8LUk)_xYbSGAJDSN~f}O==_VAPR@Kf^GOrvoPJUJrvz04}Zh&alr##K%-s&SQ5jH;XLRP-fIhPrI5+(N0hvvUtZAIcr6$5Bo)MB^k*I*MG#mog_EML6my+{&NRYMaTEdx)Nl$*zqx(WiMuJIX1NkvqyM-ce8KwM?9elaV!alO-Z#q)tAHe~O>eYMn)N{+m?UNS3ry*^xb&6KQ2LG?M{KS~>`RSbC5PYAHoZDqB%a>YLRqsHL?O^kYp%%{_^e*qJ?vlh~O(iIZ6pb1G{hO@zt+8#MlNCZaU-CQm|S^d?V2Wb`IaG9>dNPckp<4fHrLw>`Hz4LQ?IY-VIjN-1eYGqNUjM9#>c<4HfFojyMu59<zI8d!KR^&x6!RHKWnhwU)pPSQl}Bu>&q!-+GpCLBqJ5@E!caVM=ZXR#9UWc@Lx>5VYrOgNIfX@?SF#F%j>g&KHKr}t7%1~l_#OgNJurW{GXnK$z${$#_6EKHbjC+f18aVL*uFyc?trn1U=Dt+z}W~`(z{gV>Cv@M~&h3qZLaVHA8aI2>Zx>JcU>!mo7oJme3rxIG(OIs;urLC0Q<0UwfoJrK#N^vDPlAK9$r-vFdBQi51GBYJOlhdq};!1HQ{#2(DQ;8;(CY2_YJ<L?)E2TJ-a~f`AP0VSzjW;o+IFpO2l;TY4nbk9@Q;9R`Q;8|Wl;Te^WTz5Yu%8Apd^Qu|u%8WtrxJA*Qk+RnB&QN&)XAxnQzoWON^vC9B{-A#)=F_FJt9+yGcqP-M9j#a9+GF&rxJXM=}s)%H8AQ8%xSreH!-H>G~C9UnA39_SCuGFMr3A66VinA6rnvRPfl_)p*<*1OWBisjGk1<<xG?(r3vXY$wGQio|Gr0(w9nIDRiaMmr7kJLV9JZr3vYWDo~z`sn75d%&Bj^OUV-+F8&_$KO6%sB4wmZw279HGSVhSl6%pon5OQ%#64(q=9d2EAHE)}G6hJJLZ*dEktfkp=&4d9sS<uj(xgdwGG0uVlO^QIc`{Uq1u8_Exss$wu$eqa(^oQT=1pA5tC=-(B}kH_Nty8z%b7fglf{`ji4&-iISNVe#+-#KF!bTe9S!b&9ke(Q)<fHcxtPFC7CLaT(}j+ij0DHWOvVCcFcUF=nT!O{DWX$Erio1wnT!O?U?=cXF@Twj1k7M3$W!}cCl03$rw*qMrw*oL0Xj=5(pgTD%4RSVy;CuOmMf-X0X`b(n7~UGQq6Sa=1sjc)YnON>A6!&!qUR>7X~Crja@OTrZsfLi6gF<ktQTbi4tN&mex|*%37&yWj)+v#ECH?PO8dcM3|8#BuR9q`$mvb3PDII1u-H`rDVj3F(OUusfiL|M3rSqvZYy5`r@Y}T`?k0YBctvPii#wqfcry#ECe1skp}IA+m=kEvz@t_#yEMktTUe@|oo-M4AOEM3o{+ktIlzXEJ;^$!28V*iHR}sS;F)I-4m{B&iZqi7r&RQsqmPE>x)!GbKoq`BqAiCqE)oi8_fBsF6AwDacYy0+k|8M!HmqJ=oLTjXl`Y-Hkoi)7_0MN|ho=DFq;<NRrV?ktIlzosB9)l_E`i$?#()s$|tnnyHecNX(TYN|7Z<lPIQ9Orn`ZGKyss$|+JL<g2Afll-JgktS+H%}AN46Og2vH8?Z;Xko*_hY(PnniVuEP@bPfPokv>=|XybNYaG#yqPa1OUaV*WW1RuPeDo((^oQ3o|_4i%8fO1Caz@F%$m8AS29qZlqaPL>FCUqC#Rb-bDRX!N|yW7or;$G+c5Xxv4%k1PtU=ILL3NbVY!DoZs(>(RLIJi8B=#XIC)cdJvVdHcRe?A)9)$P$eoIvY>C#$o4M(`o}aEn-Oo+j^xe--sUm&+RO}>9!bI%U>?BXHrtW%w>YJ$3T&C`Nf9jjL>FcSxo{`L(x#`2H<m0AAPU8(eZaRL;KD;D_2yn+Wew<Xv#Y~)3$<1G;N@V7*)0)3dYW+E@^yF0QtfyM1U1d7!Da~J}HGZG>WjPv2&0nWAew=cga-4FQai&2`IMNDpSLw;uPHO!*tMu{ZPHO!*tMvJN1oLH2HdNxbsq9uxYW+TBiSr~+nIe426Xr;q)%teoe|;{38n|<&R{b{0ZIs(7mA_9-Os)E5Z__J&nOpR?Qr$~+E!4MDD}I?<^!iF=Z__J&nOpSj?51xWI?E~6Sx&Obb(T}@sg=J@)l9AWXq3v|r`=QTsrOXt=%$HGt@?i&$(6rOenjWwPJTq^<W7D>;i)H7rdItl3TPD2DV4uY*-WkaWpC5+Mwwgm%HN|hGb1uHBQj-g(?F(H{W7=dmA_1)olZIm3JMAeWpC3$rdItsWiq$v_SE}oeYHN?pKVKybH<0^hldMOGNnkhu-U`+oL7r&31R;5|G0nr3T(}EIHFe88|YGpBxiOB^y;V6s-I4(NxDy~RV3Xco1~L;l5Ue*GHWGH`oe1^O=PJi=_K7Hy;RQZ62|E)Zj;lMKQ{$GT&eoyPby^na-{0Xo!BIDq;jNkrgvbR-IUJk6VQ<}y9Dy2PTGoDnJ;8Z>gnN9PoW}bb_t!>B-rUTI!%t1;!ifpSBWdcnb{J&N%mCxDt(nc%AaLQ@g;bZ*i$>ONa9bxr;!?WDt9V(Dt9V(Dn}A$b_x9}CU;<&-GX#;Cs({nis_N6nHs5oik^I_^Z)z3hn)^2`f^;u%Z0hXjW`jf0yN-8oCwo_8ff+j%vDVu!8D3#6w)c(;V0ZvyTVTI2|K(b(d-jRgr8zm!QdxpDt3~llL<7KNwAePm`S9<O(qg?Rg;RWoK<Aha8u$|O(qg^))PmtPn|Mta8qAdHn=J4R!>^8dexIt!A|0`X!Z%JnKXM2dLM=xNOT3R@jk_5`xTPcc%NpneVWN@yh~l;dbQK6@DquZCEz7l60C{lC~p(9l?~#2`H<du@Yuul!qlrzJrCe^f3ZK-vVW~)|60lZwUhm8Cu_V<GQxJd&iWo4H>OUV)I9iP4_;*Zd(C_$hQ=2V{1DSZ(B>>B+}<bL-Y2h7GWHWMVKrX@cJn5~gU7?chG^D%iSO1=ezI#l#EP;-Sv8*GYdyr?S50TQorQ$cR!ro{rmUK3$*lJiS?(vlSv8*GYdyr)dx`n$C$GUz0<w4&lfbN=1!VK=CbQg4q{*!J5-Q28_YykE9b}HOM_D7RpT~8ehTaz^vspcw$?VobntJt<+`>!F3RAF{n70tXhf-cln$6a_9D$2I+8#_TOj+s8*G_J_b9K`edUKW27J6dOOj+rRJvwU%_Nyn(nLgEI`&E+`dScH{>sc{prY!Wuo|<~e`0-P`texd#?<*&HSwH5&V$VuZr6|&rX^TBFN@CAXKOHe=rNWrA(~ndBvD1!I@8PFej+nF47J70sCnGX)GbSwb`7<Ug^u?Z>f|#?@oKr((J7qLBQ}HQ_Juzpd3YfFg7J73kb1HKxb1GPkEJmDSn6uLsdUN&D7J6dOPt`JF&rh#mEAUhOD<`*vpQnPEzST1`C5ckKWU(q(l_z4Q{Ph1S>3=;tITN#yJ2?{mdVlgnzn+)#(*Am1&rj(xdsvC(%$Qiog^ZW;(*AmM*y(>gFXyHF^yL(-8f28oDUwqprb$cr>CV?n`RU?Hm-Exgl{vlwVa%4>)aj&4`RVs8CH(*Hg;;Ch#+&I=eJXFIP4ub0l|3v})5@Gpbo`cXA*Y8Vby8fytT=;l8g3&^#A&#VHxZ`dG~7m&Wlw@@h*dmV_b~J!{Gr;J3^cPcS(!2zXv~bski$%d8gp@`!_-Z5$?fANqGZ%enu(LQ!%p7~EKHrg8g}?;u=NsYl4+9f9V|?iCQFPo)!9vlsGfqG4^ceDI2-iYDY8>!r#+6D<v1Jt1V1c2NCyXgolTVLY^Mi)nX4(9vYZ|IaChnD%$kjwY3wG489U1f-dIlZ!g%}i+*nT^ew#Z9{~I*$rcVlF@TN_+GI%p5<=>`<89y%lKQ8@0F8}*OeGUvQ&YjM~PH3jKIpr~T>5IQi%9)ijDskB9@JyWTo;n}a9K1X@a8Gf{L;c~UEfn6zu7~XkDV<X~rgcJ!XVfU6MG7cUPeNqWMw*$EQ!;91LW&ep%*atfiWF1IjXbE+oTQqF)AdY+6yww=q!faXP@<VN3MuJXLW+6zP@<lan`<dWPszef4V2?>{gTqfv@M~&h3qZMiYdcbP8z~+))L~1aTXHdid<1kiYakLIO{3LSx=0o9c3`_lH!V7QBKy%Tv1DkDRD(Pg*8#8QB0zlMKX$I6u6?E?PR#3mlRSJQsRnSQA?_+byY5^rvDW>D(P`WFyl-((+)JljWFX&iYb+<mlRXFQ@T^SQsRntYFtrEiYakLHj^dA6uGjKV<TZ32-r)CDWI~K6jI`fTv1M4PF+r2PF+r2ONuFUrNtD!td|s1sgW)yrhY`v$eH;Qo}``HmlRW=u9p;ZaMZ)7Fyl-((+)JljWFX(IMWU^<0_>&>6B9_r8((NdVEzW&q{OCGa6H#l;@}PnJnWb!erP?l;@>6>2#$z=}vl6o}9{@%ACra%ACra%ACrS=ciX)DbGTxQ=XYhsnu{2=Bj*s>TIM=B9DI$dLNDf)ySP(iPgxRT#41lpCXb{jW&vKtK37@hfaQL`<Q<Cda%eD8Y%Y_`-)^}r+TM)rbdcnXs4MPWN4<!WZ6ucDU)R~Y^F?&6!@xSXs4qxWN4?cGHT;bMr8D6Pex?)W=}?B$k9xV6wLUEvzb5YB=crX1c{)LIr>P(oc${>^x?}L4eov&v^WsfL)(S9n7~dNG~uI88Z^vcClMNEFcUF=nT!O?U?<*F?<x0``^tUgGZ+b&z)yKh#sX$A6ET3D0-xI%IVCwIIVCwIIVCd~3DQ|klFD?JQ!#*@>Y0oLv0XD53GmlU#sXNfmTRXcGHvOmrn*bFP0E^H7M2%~xG^G3YUzz#F{`E|NgZ^=i7_HfNRtvIwz8JiQq@aqDemJYBuR-9byianB*cj^B1@$|+BAZYQVKyxDTxwoD<&jKi4t#ROh}UwB&#Y_l`6`g*A+P$>4_41QKz*Udr_yg8hcTuBuT^7O~yAt4U{=SZDGEL!4HU3i8IP)l+P(rB+w~RB&iZqi7G^!Ig{bWOEV_^!f)&)NRp&U)Y(drB}kH_NphvimnvMTa-~R-nJPq|%Cc06Ir$Q#Nz_Q4M2XPZPC}As6sZz&HPWO>?#7<%Y3|0J>}l@Cp6qF2RH+g{NGSy>M3#zFi7G^#>}gUYsS<1EPlFjXQzoip)l8KlMr5fHREa7?nME>+WfaOOlv60CQA&{~C0!~+pXDM{i8E3rYDCRQoP{LWsk49l"
;

static const unsigned kGoodCount = 1257874;
static const unsigned kUlebLen = 1297230;
static const unsigned kLzssLen = 22832;
static const unsigned kCompressedLen = 14568;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  if (N < 1 || N > (int)kGoodCount) return 1;
  vector<unsigned char> blob = b85decode(kB85);
  if (blob.size() != kCompressedLen) return 1;
  vector<unsigned char> buf;
  if (!lzs3_decode(blob, buf, kUlebLen, kLzssLen)) return 1;
  size_t pos = 0;
  long long sum = 0;
  for (int i = 0; i < N; ++i) {
    unsigned long long d;
    if (!read_uleb128(buf, pos, d)) return 1;
    sum += (long long)d;
  }
  cout << sum << '\n';
  return 0;
}
