#!/usr/bin/env python3

import sys
import os

ADDRESS_INSTRUCTIONS = set("12AB")
START_ADDRESS = 0x200


class HexConverter:
    def __init__(self):
        self.addr = START_ADDRESS
        self.labels = {}
        self.unknown_labels = []
        self.processed = []

    def remove_comments(self, line):
        comment_loc = line.find("#")
        line = line[:comment_loc].strip()
        return line

    def swap_label(self, instr, label):
        return f"{instr[0]}{hex(self.labels[instr[1:]])[2:]}"

    def add_label(self, instr):
        self.labels[instr[:-1]] = self.addr

    def process_instr(self, instr):
        if instr[0] in ADDRESS_INSTRUCTIONS:
            label = instr[1:]
            if label in self.labels:
                self.processed.append(self.swap_label(instr, label))
                return
            else:
                self.unknown_labels.append(len(self.processed))

        self.processed.append(instr)

    def resolve_labels(self):
        for i in self.unknown_labels:
            instr = self.processed[i]
            label = instr[1:]
            self.processed[i] = self.swap_label(instr, label)

    def convert(self, lines):
        for line in lines:
            line = self.remove_comments(line)

            if not line:
                continue

            instrs = line.split(" ")

            for instr in instrs:
                instr = instr.strip()

                if line[-1] == ":":
                    self.add_label(instr)
                else:
                    self.process_instr(instr)
                    self.addr += 2

        self.resolve_labels()
        return "".join(self.processed)


def main():
    if len(sys.argv) < 2:
        print("Usage: hexc.py [filename]")
        return

    in_file = sys.argv[1]
    out_file = os.path.splitext(in_file)[0] + ".bin"

    with open(in_file) as file:
        lines = file.readlines()

    converter = HexConverter()
    processed_string = converter.convert(lines)

    with open(out_file, "wb") as file:
        data = bytes.fromhex(processed_string)
        file.write(data)


if __name__ == "__main__":
    main()
