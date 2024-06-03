import sys
import subprocess
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
        self.logger: log.Logger = logger
        self.set_logging(args.verbose)
        self.logger.info(f'Initialising PredVirusHost for {args.input}')
        self.set_variables(args)

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
        #TODO Check if short proteins are in more than one file
        #TODO Check if there are enough of these proteins to keep
        #TODO Include proteins that pass these checks
    
    def run_hmmsearch(self) -> None:
        hmmsearch_command: List[str] = ['hmmsearch', '--tblout', f'{self.directory}/arVOG_res.tbl',
                                        '--noali', '--cpu', f'{self.cpu_counter}', f'{self.data_path}/arVOG.hmm',
                                        f'{self.directory}/fastafile_1.faa']
        logger.info(f'Running hmmsearch with:\n {hmmsearch_command}')
        subprocess.run(hmmsearch_command, 
                       stdout=subprocess.DEVNULL)
        pass

    def check_hmm(self) -> str:
        return_val: bool = False
        required_files: List[str] = ['baPOG.hmm', 'arVOG.hmm', 'euVOG.hmm', 'arVOG_weights.txt', 'euVOG_weights.txt', 'baPOG_weights.txt']
        found_files: List[str] = []
        msg: str = ''
        logger.debug(f'Looking for models in: {self.data_path}')
        fd: List[str] = glob.glob(f'{self.data_path}/*.hmm')
        fw: List[str] = glob.glob(f'{self.data_path}/*weights.txt')
        logger.debug(f'Models found: {fd}')
        logger.debug(f'Weightings found: {fw}')
        item: str
        for item in fd:
            item = item.split('/')[-1]
            found_files.append(item)
        for item in fw:
            item = item.split('/')[-1]
            found_files.append(item)
        for item in required_files:
            if item not in found_files:
                msg += f'{item} not found in {self.data_path}\n'
                return_val = True
        hmmsearch_status: tuple[int, str] = subprocess.getstatusoutput('hmmsearch -h')
        logger.debug(f'hmmsearch -h returned: {hmmsearch_status}')
        if hmmsearch_status[0] != 0:
            msg += f'hmmsearch not working (status: {hmmsearch_status[0]})\n'
            return_val = True
        if return_val:
            msg = f'\nCannot find required models or hmmsearch executable.\n' + msg
        return msg

    def set_logging(self, verbose) -> None:
        if verbose is None:
            self.verbosity: int = 0
            log.basicConfig(format="%(levelname)s: %(message)s")
        elif verbose == 1: 
            self.verbosity: int = 1
            log.basicConfig(format="%(message)s", level=log.INFO)
        else:
            self.verbosity: int = 2
            log.basicConfig(format="DEBUG: %(asctime)s %(message)s", level=log.DEBUG)
        self.logger.info("Verbose mode on.")
        self.logger.debug("Debug mode on.")
        self.logger.info(" ")

    def set_variables(self, args) -> None:
        self.format: str = args.format
        self.n_min: int = int(args.number)
        self.separators: tuple[int, int, str] = assign_separators(self.format)
        self.cpu_counter: int = int(args.cpu)
        max_cpus: int | None = os.cpu_count()
        if isinstance(max_cpus, int):
            self.cpu_counter: int = min(self.cpu_counter, max_cpus)
        self.logger.debug(f'running on {self.cpu_counter} cpus')
        self.logger.debug(f'minimum number of proteins selected as {self.n_min}')
        self.logger.debug(f'using {self.format} for the formatting of protein strings')
        self.logger.debug(f'using {self.separators} as separator values')
        paths: tuple[str, str, str, str] = assign_paths(args)
        self.data_path = paths[0]
        self.directory: str = paths[3]
        self.logger.info(f'Output will be saved in {self.directory}.')
        self.input_file: str = os.path.join(paths[2], args.input)
        self.ff: str = os.path.join(self.directory, "fastafile.faa")
        self.fh: str = os.path.join(self.directory, "fasta-headers.txt")
        self.genomes: dict[str, tuple[list[str], int]] = {}
