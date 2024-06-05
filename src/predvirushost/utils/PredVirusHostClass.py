import sys
import subprocess
import os
import logging as log
import glob
import pickle
import pandas as pd
from pathlib import Path
from typing import List, Dict, Any
from predvirushost.utils.utils import assign_paths, assign_separators, user_prompt, pretty_output
from predvirushost.utils.process_fasta_input import read_file_in_chunks
logger = log.getLogger(__name__)

DEBUG_MODE: bool = True

class PredVirusHost:
    def __init__(self, args: Dict[str, Any]) -> None:
        if DEBUG_MODE:
            with pretty_output('BOLD', 'FG_WHITE', 'BG_RED') as out:
                out.write('DEBUGGING IS ON. BE CAREFUL!!!')
                out.write('DEBUGGING IS ON. BE CAREFUL!!!')
                out.write('DEBUGGING IS ON. BE CAREFUL!!!')

        self.logger: log.Logger = logger
        self.__set_logging(args['verbose'])
        self.logger.info(f'Initialising PredVirusHost for {args['input_file']}')
        self.__set_variables(args)

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
            if fasta_file.split('/')[-1] != 'fastafile_1.faa' and DEBUG_MODE:
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

    def process_results_chunk(self, index: int) -> None:
        arvog_file: str = f'{self.output_directory}/arVOG_res_{index}.tbl'
        bapog_file: str = f'{self.output_directory}/baPOG_res_{index}.tbl'
        euVOG_file: str = f'{self.output_directory}/euVOG_res_{index}.tbl'

    def process_models(self, model: str, index: int) -> dict[str, List[List[float]]]:
        file: str = f'{self.output_directory}/{model}_res_{index}.tbl'
        line: str
        protein: str
        current_model: str
        score: float
        d: dict[str, List[List[float]]] = {}
        with open(file, 'r') as f:
            for line in f:
                if line[0] == "#":
                    continue
                words = line.rstrip().split()
                protein, current_model, score = words[0, 2, 5]
                # try:
                #     d[words[0]] = float(words[1])
                # except TypeError:
                #     raise TypeError(f'{words[0]}: {words[1]} cannot be cooerced to type float')
        return d
    
    def preprocess_single_file(self, file: str) -> None:
        """Opens an hmmout.tbl file and converts the data to a pandas DataFrame.
        The genome names are read in from the corresponding pickle file and
        are joined to the data frame."""
        index: int = int(file.split('_')[-1].split('.')[0])
        df = pd.read_csv(file, sep='\s+', comment='#', header=None)
        df_small = df.iloc[:,[0,2,4,5]]
        df_small.columns = ['protein', 'model', 'evalue', 'bitscore']

        with open(f'{self.output_directory}/data_{index}.pkl', 'rb') as fp:
            lookup: Dict[bytes, bytes] = pickle.load(fp)
            lookup_df = pd.DataFrame(lookup.items())
            lookup_df.columns = ['protein', 'genome']
            lookup_df = lookup_df.stack().str.decode('utf-8').unstack()
            merged_df = df_small.join(lookup_df.set_index('protein'), on='protein', how='outer')
            logger.debug(merged_df.iloc[:,:])

    def preprocess_results(self) -> None:
        self.protein_results_d: Dict[str, List[float]] = {}
        """
        Load and combine the individual hmmout.tbl files, along with the genome
        names and model weightings.
        """
        logger.info(f'Processing results in: {self.data_path}')
        arVOG_results: List[str] = glob.glob(f'{self.output_directory}/arVOG_res_*.tbl')
        self.preprocess_single_file(arVOG_results[0])

        # baPOG_results: List[str] = glob.glob(f'{self.output_directory}/baPOG_res_*.tbl')
        # euVOG_results: List[str] = glob.glob(f'{self.output_directory}/euVOG_res_*.tbl')
        # d: Dict[str, List[str]] = {}
        # model_index: int = 1
        # words: List[str]
        # word: str
        # index: int
        # logger.debug(arVOG_results)
        # out_file_words: List[str] = arVOG_results[0].split('.')[:-1]
        # out_file: str = '.'.join(out_file_words)
        # out_file += '_formatted.tbl'
        # with open(out_file, 'a') as f_out:
        #     with open(arVOG_results[0], 'r') as f_res:
        #         for line in f_res:
        #             if line[0] == '#':
        #                 continue
        #             words = line.split('-')
        #             for index, word in enumerate(words):
        #                 if 'VOG_' or 'POG_' in word:
        #                     model_index = index
        #                 else:
        #                     continue
        #             protein: str = '-'.join(words[:model_index]).strip()
        #             model: str = words[model_index].strip()
        #             remainder: str = '-'.join(words[model_index + 1:]).strip()
        #             values: List[str] = remainder.split()
        #             values_string: str = '","'.join(values) 
        #             values_string = '"' + values_string + '"'
        #             f_out.write(f'"{protein}","{model}",{values_string}') 

    def __set_logging(self, verbose) -> None:
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

    def __set_variables(self, args: Dict[str, Any]) -> None:
        if not args['process_results_only']:
            self.format: str = args['format']
            self.n_min: int = int(args['n_min'])
            self.separators: tuple[int, int, bytes] = assign_separators(self.format)
            self.n_cpus: int = int(args['n_cpus'])
            max_cpus: int | None = os.cpu_count()
            if isinstance(max_cpus, int):
                self.n_cpus: int = min(self.n_cpus, max_cpus)
            self.logger.debug(f'running on {self.n_cpus} cpus')
            self.logger.debug(f'minimum number of proteins selected as {self.n_min}')
            self.logger.debug(f'using {self.format} for the formatting of protein strings')
            self.logger.debug(f'using {self.separators} as separator values')
        paths: tuple[str, str, str] = assign_paths(args)
        self.data_path = paths[0]
        self.input_file: str = paths[1]
        self.output_directory: str = paths[2]
        self.logger.info(f'Output will be saved in {self.output_directory}.')
        self.ff: str = os.path.join(self.output_directory, "fastafile.faa")
        self.fh: str = os.path.join(self.output_directory, "fasta-headers.txt")
        self.genomes: dict[str, tuple[list[str], int]] = {}
