import subprocess
import os
import logging as log
import glob
import pickle
from pathlib import Path
from typing import List, Dict, Any
from predvirushost.utils.PredVirusHostClass import PredVirusHost
from predvirushost.utils.utils import user_prompt
from predvirushost.utils.process_fasta_input import read_file_in_chunks
logger = log.getLogger(__name__)

class ProcessInput(PredVirusHost):
    def __init__(self, args: Dict[str, Any]) -> None:
        super().__init__(args)


    def check_files(self, *, create_directory: bool = True) -> str:
        """Checks for the presence of existing pvh generated files."""

        if not os.path.isdir(self.output_directory):
            if create_directory:
                Path(self.output_directory).mkdir(parents=True, exist_ok=True)
            return ''
        fl: List[str] = glob.glob(f'{self.output_directory}/fastafile*.faa')
        dl : List[str] = glob.glob(f'{self.output_directory}/data*.pkl')
        spl : List[str] = glob.glob(f'{self.output_directory}/short_proteins*.pkl')
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
            msg = f'\n{n_files} data files found in {self.output_directory}.\n If you wish to process this data use --process_results_only' + msg

        return msg

    def remove_files(self, force_delete: bool) -> bool:
        """Removes any existing pvh generated files from the output directory."""
        exit_status: bool = False
        fl: List[str] = glob.glob(f'{self.output_directory}/fastafile*.faa')
        dl : List[str] = glob.glob(f'{self.output_directory}/data*.pkl')
        spl : List[str] = glob.glob(f'{self.output_directory}/short_proteins*.pkl')
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
        """Calls the fasta input processor"""
        read_file_in_chunks(self.input_file, self.output_directory, self.n_cpus, self.n_min, self.separators, self.verbosity)

    def check_short_genomes(self):
        """Loads the short protein pickle files and checks if any genomes with
            less than the minimum number of proteins were split across mulitple
            files.
        """
        spl : List[str] = glob.glob(f'{self.output_directory}/short_proteins*.pkl')
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
        """
        Loops over the fasta files and the models running a system call for
        hmmsearch
        """
        models_list: List[str] = ['arVOG', 'baPOG', 'euVOG']
        fasta_files_list: List[str] = glob.glob(f'{self.output_directory}/fastafile*.faa')
        file_number: str
        model: str
        fasta_file: str
        for fasta_file in fasta_files_list:
            if fasta_file.split('/')[-1] != 'fastafile_1.faa' and self.DEBUG_MODE:
                continue
            for model in models_list:
                file_number = fasta_file.split('_')[-1].split('.')[0]
                hmmsearch_command: List[str] = ['hmmsearch', '--tblout', f'{self.output_directory}/{model}_res_{file_number}.tbl',
                                                '--noali', '--cpu', f'{self.n_cpus}', f'{self.data_path}/{model}.hmm',
                                                f'{fasta_file}']
                logger.info(f'Running hmmsearch with:\n {hmmsearch_command}')
                subprocess.run(hmmsearch_command, 
                               stdout=subprocess.DEVNULL)

    def check_hmm(self) -> str:
        """
        Checks that all the required files for running hmmsearch exist, including
        the executable and the files required for processing the data.
        """
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

