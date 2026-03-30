#!/usr/bin/env python3

def main():
    with open("ABC451_D_table.h", "r", encoding="ascii") as f:
        header = f.read()
    with open("D.cpp", "r", encoding="utf-8") as f:
        body = f.read()
    body = body.replace('#include "ABC451_D_table.h"\n', "")
    out = "ABC451_D_merged.cpp"
    with open(out, "w", encoding="utf-8") as f:
        f.write(header)
        f.write("\n")
        f.write(body)
    print("Wrote", out)


if __name__ == "__main__":
    main()
