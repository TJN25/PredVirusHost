#!/usr/bin/env python3
import os
import argparse
from pathlib import Path

from utils import assign_paths, file_reformat, assign_separators

help_title= """
Takes a protein FASTA file and retains only genomes that contain at least n proteins.
"""

def get_args():
    parser = argparse.ArgumentParser(prog='minimum-contig-size.py',
                    description=help_title
                    )
    parser.add_argument('-d', '--directory', required=True)
    parser.add_argument('-n', '--number', default=5)
    parser.add_argument('-v', dest='verbose', action='store_true')
    args = parser.parse_args()
    return(args)

if __name__ == '__main__':
    args = get_args()
    if args.verbose:
        log.basicConfig(format="%(message)s", level=log.DEBUG)
        log.info("Verbose flag used: printing output.")
    else:
        log.basicConfig(format="%(levelname)s: %(message)s")
        
    ff = os.path.join(user_folder, args.directory, "fastafile.faa") ##input fastafile.faa
    fh = os.path.join(user_folder, args.directory, "fasta-headers.txt") ##input fasta-headers.txt
    
    
    
    
    
    
    tmp_1 = open(f'{user_output_folder}/tmp1', 'w')
    fasta_file = open(f'{user_output_folder}/fastafile.faa', 'w')
    f = open(f'{user_output_folder}/fasta-headers.txt', 'w')
    
    file_reformat(separators, args, f, tmp_1, fasta_file, user_output_folder)
    f.close()
    tmp_1.close()
    fasta_file.close()
