import sys
import os
import logging as log
import argparse
from typing import Any
from utils import assign_paths, assign_separators 
from process_fasta_input import process_fasta_file

class PredVirusHost:
    def __init__(self, args: argparse.Namespace) -> None:
        if args.verbose:
            log.basicConfig(format="%(message)s", level=log.DEBUG)
            log.info("Verbose flag used: printing output.")
        else:
            log.basicConfig(format="%(levelname)s: %(message)s")
        log.info(f'Initialising PredVirusHost for {args.directory}')
        self.format: str = args.format
        self.separators: tuple[int, int, str] = assign_separators(self.format)
        self.cpu_counter: int = min(args.cpu, os.cpu_count())
        paths: tuple[str, str, str, str] = assign_paths(args)
        self.paths: dict[str, str] = {}
        self.paths['utils'] = paths[0]
        self.paths['pvh'] = paths[1]
        self.paths['user'] = paths[2]
        self.paths['user_out'] = paths[3]
        log.info(f'Output will be saved in {self.paths["user_out"]}.')
        self.directory: str = self.paths["user_out"]
        self.input_file: str = os.path.join(self.paths["user"], args.input)
        self.ff: str = os.path.join(self.directory, "fastafile.faa")
        self.fh: str = os.path.join(self.directory, "fasta-headers.txt")
        self.genomes: dict[str, tuple[list[str], int]] = {}

    def check_files(self) -> bool:
        file_found: int = 0
        msg: str = ""
        if not os.path.exists(self.ff):
            file_found += 1 
            msg += f'- Fasta file: {self.ff}\n'
        if not os.path.exists(self.fh):
            file_found += 1 
            msg += f'- Fasta headers file: {self.fh}\n'
        if file_found == 2:
            msg = "Files found\n\n" + msg
            print(msg)
            return True
        if file_found == 1:
            msg = "Only one file found. Something might be wrong. Exiting...\n\n" + msg
            sys.exit(msg)
        return False

    def process_fasta(self) -> None:
        process_fasta_file(self.input_file, self.directory, self.cpu_counter)

    def load_protein_names(self) -> None:
        with open(self.fh, 'r') as fh:
            lines: list[str] = fh.readlines()
        self.proteins_dict: dict[str, list[Any]] = {}
        line: str
        for line in lines:
            try:
                key: str
                value: str
                value, key = line.strip().split(' ')
                value = value[1:]
            except ValueError:
                continue
            if not key in self.proteins_dict:
                self.proteins_dict[key] = [value]
            else:
                self.proteins_dict[key].append(value)

    def protein_count(self) -> None:
        for key, value in self.proteins_dict.items():
            length: int = len(value)
            self.proteins_dict[key] = [value, length]

    def count_filter(self, number: int) -> None:
        print(f'Number of proteins as a minimum is: {number}')
        if number == 1:
            return
        f = open(f'{self.directory}/tmp1', 'a')
        with open(self.ff, 'r') as ff:
            line: str
            for line in ff:
                line = line.strip()
                if len(line) > 0:
                    if line[0] == ">":
                        f.write(f'\n{line}\t')
                    else:
                        f.write(f'{line}')
        f.close()
