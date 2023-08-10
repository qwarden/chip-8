#!/usr/bin/env python3

import sys
import os


def main():
    if len(sys.argv) < 2:
        print("Usage: chex.py [filename] ")
        return

    in_file = sys.argv[1]
    out_file = os.path.splitext(in_file)[0] + ".bin"

    stripped = ""
    hex_chars = set('0123456789abcdefABCDEF')

    with open(in_file) as file:
        for line in file:
            stripped_line = ''.join(line.strip().split())
            for c in stripped_line:
                if c == "#":
                    break
                elif c not in hex_chars:
                    print(f'Invalid hex char: {c}')
                    return
                else:
                    stripped += c

    with open(out_file, 'wb') as file:
        data = bytes.fromhex(stripped)
        file.write(data)


if __name__ == "__main__":
    main()
