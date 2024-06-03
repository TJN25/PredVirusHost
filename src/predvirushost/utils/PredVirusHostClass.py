import sys
import os
import logging as log
import argparse
import glob
import pickle
from typing import List
from predvirushost.utils.utils import assign_paths, assign_separators, user_prompt
from predvirushost.utils.process_fasta_input import read_file_in_chunks
logger = log.getLogger(__name__)

class PredVirusHost:
    def __init__(self, args: argparse.Namespace) -> None:
        if args.verbose is None:
            self.verbosity: int = 0
            log.basicConfig(format="%(levelname)s: %(message)s")
        elif args.verbose == 1: 
            self.verbosity: int = 1
            log.basicConfig(format="%(message)s", level=log.INFO)
        else:
            self.verbosity: int = 2
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
        self.paths['data'] = paths[0]
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
        dl : List[str] = glob.glob(f'{self.directory}/data*.pkl')
        spl : List[str] = glob.glob(f'{self.directory}/short_proteins*.pkl')
        msg: str = ""
        n_files: int = 0
        return_val: bool = False
        if len(fl) > 0:
            n_files += len(fl)
            msg += f'Files need to be moved or renamed to something other than <fastafile*.faa>.\n'
            return_val = True
        if len(dl) > 0:
            n_files += len(dl)
            msg += f'Files need to be moved or renamed to something other than <data*.pkl>.\n'
            return_val = True
        if len(spl) > 0:
            n_files += len(spl)
            msg += f'Files need to be moved or renamed to something other than <data*.pkl>.\n'
            return_val = True

        if return_val:
            msg = f'\n{n_files} data files found in {self.directory}.\n' + msg
        return msg

    def remove_files(self, force_delete: bool) -> bool:
        exit_status: bool = False
        fl: List[str] = glob.glob(f'{self.directory}/fastafile*.faa')
        dl : List[str] = glob.glob(f'{self.directory}/data*.pkl')
        spl : List[str] = glob.glob(f'{self.directory}/short_proteins*.pkl')
        files: tuple[List[str], List[str], List[str]] = (fl, dl, spl)
        do_remove: str = ''
        msg: str = ''
        for file_type in files:
            if len(file_type) == 0:
                continue
            if force_delete:
                do_remove = 'y'
            else:
                msg = f'Remove the following file? (y/N)\n {file_type}'
                do_remove = user_prompt(msg, 'alert')
            logger.debug(f'User input is: {do_remove}')
            if do_remove.lower() == 'y' or do_remove.lower() == 'yes':
                for file in file_type:
                    os.remove(file)
            else:
                exit_status = True
                return exit_status
        return exit_status

    def process_fasta(self) -> None:
        read_file_in_chunks(self.input_file, self.directory, self.cpu_counter, self.n_min, self.verbosity)

    def check_short_proteins(self):
        spl : List[str] = glob.glob(f'{self.directory}/short_proteins*.pkl')
        short_proteins: List[str] = []
        for file_path in spl:
            logger.debug(f'reading file {file_path}')
            with open(file_path, 'rb') as j:
                data: List[str] = pickle.load(j)
                for item in data:
                    short_proteins.append(item)
        for item in short_proteins:
            logger.debug(f'Short protein: {item}')
        # logger.debug(f'Short proteins: {short_proteins}')
        pass
    
    def run_hmmsearch(self) -> None:
        logger.debug(f'Looking for models in: {self.paths['data']}')
        print(self.paths['data'])
        fd: List[str] = glob.glob(f'{self.paths['data']}/*.hmm')
        logger.debug(f'Models found: {fd}')
