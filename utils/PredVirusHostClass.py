import sys
import os
import logging as log
import argparse
import glob
import json
from typing import Any, List
from utils import assign_paths, assign_separators 
from process_fasta_input import process_fasta_file
logger = log.getLogger(__name__)

class PredVirusHost:
    def __init__(self, args: argparse.Namespace) -> None:
        if args.verbose is None:
            log.basicConfig(format="%(levelname)s: %(message)s")
        elif args.verbose == 1: 
            log.basicConfig(format="%(message)s", level=log.INFO)
        else:
            log.basicConfig(format="DEBUG: %(asctime)s %(message)s", level=log.DEBUG)
        logger.info("Verbose mode on.")
        logger.debug("Debug mode on.")
        logger.info(" ")
        logger.info(f'Initialising PredVirusHost for {args.input}')
        self.format: str = args.format
        self.n_min: int = int(args.number)
        self.separators: tuple[int, int, str] = assign_separators(self.format)
        self.cpu_counter: int = int(args.cpu)
        max_cpus: int | None = os.cpu_count()
        if isinstance(max_cpus, int):
            self.cpu_counter: int = min(self.cpu_counter, max_cpus)
        logger.debug(f'running on {self.cpu_counter} cpus')
        logger.debug(f'minimum number of proteins selected as {self.n_min}')
        logger.debug(f'using {self.format} for the formatting of protein strings')
        logger.debug(f'using {self.separators} as separator values')
        paths: tuple[str, str, str, str] = assign_paths(args)
        self.paths: dict[str, str] = {}
        self.paths['utils'] = paths[0]
        self.paths['pvh'] = paths[1]
        self.paths['user'] = paths[2]
        self.paths['user_out'] = paths[3]
        logger.info(f'Output will be saved in {self.paths["user_out"]}.')
        self.directory: str = self.paths["user_out"]
        self.input_file: str = os.path.join(self.paths["user"], args.input)
        self.ff: str = os.path.join(self.directory, "fastafile.faa")
        self.fh: str = os.path.join(self.directory, "fasta-headers.txt")
        self.genomes: dict[str, tuple[list[str], int]] = {}

    def check_files(self) -> str:
        fl: List[str] = glob.glob(f'{self.directory}/fastafile*.faa')
        dl : List[str] = glob.glob(f'{self.directory}/data*.json')
        spl : List[str] = glob.glob(f'{self.directory}/short_proteins*.json')
        msg: str = ""
        n_files: int = 0
        return_val: bool = False
        if len(fl) > 0:
            n_files += len(fl)
            msg += f'Files need to be moved or renamed to something other than <fastafile*.faa>.\n'
            return_val = True
        if len(dl) > 0:
            n_files += len(dl)
            msg += f'Files need to be moved or renamed to something other than <data*.json>.\n'
            return_val = True
        if len(spl) > 0:
            n_files += len(spl)
            msg += f'Files need to be moved or renamed to something other than <data*.json>.\n'
            return_val = True

        if return_val:
            msg = f'\n{n_files} data files found in {self.directory}.\n' + msg
        return msg

    def process_fasta(self) -> None:
        process_fasta_file(self.input_file, self.directory, self.cpu_counter, self.n_min)
        spl : List[str] = glob.glob(f'{self.directory}/short_proteins*.json')
        short_proteins: List[str] = []
        for file_path in spl:
            logger.debug(f'reading file {file_path}')
            with open(file_path, 'r') as j:
                data: List[str] = json.load(j)
                for item in data:
                    short_proteins.append(item)
        logger.debug(short_proteins)
        

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
