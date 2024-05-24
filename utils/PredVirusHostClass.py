import sys
import os
import logging as log
# import pandas
from utils import assign_paths, file_reformat, assign_separators

class PredVirusHost:
    def __init__(self, args: list):
        if args.verbose:
            log.basicConfig(format="%(message)s", level=log.DEBUG)
            log.info("Verbose flag used: printing output.")
        else:
            log.basicConfig(format="%(levelname)s: %(message)s")
        log.info(f'Initialising PredVirusHost for {args.directory}')
        self.utils_folder, self.predvirushost_folder, self.user_folder, self.user_output_folder = assign_paths(args)
        log.info(f'Output will be saved in {self.user_output_folder}.')
        self.separators = assign_separators(args.format)
        self.directory = os.path.join(self.user_folder, args.directory)
        self.ff = os.path.join(self.directory, "fastafile.faa") ##input fastafile.faa
        self.fh = os.path.join(self.directory, "fasta-headers.txt") ##input fasta-headers.txt


    def check_files(self) -> None:
        exit_val = False
        msg = ""
        if not os.path.exists(self.ff):
            exit_val = True
            msg += f'- Fasta file: {self.ff}\n'
        if not os.path.exists(self.fh):
            exit_val = True
            msg += f'- Fasta headers file: {self.fh}\n'
        if exit_val:
            msg = "Exiting due to missing files.\n\n" + msg + "\nConsider running name-reformat.py or using the correct -d [DIRECTORY] path.\n"
            sys.exit(msg)
            
    def load_protein_names(self) -> None:
        with open(self.fh, 'r') as fh:
            lines = fh.readlines()
        self.proteins_dict = {}
        for line in lines:
            try:
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
            length = len(value)
            self.proteins_dict[key] = [value, length]
    def count_filter(self, number: int) -> None:
        print(f'Number of proteins as a minimum is: {number}')
        if number == 1:
            return
        f = open(f'{self.directory}/tmp1', 'w')
        


if __name__ == '__main__':
    sys.exit('Do not run PredVirusHostClass directly.')