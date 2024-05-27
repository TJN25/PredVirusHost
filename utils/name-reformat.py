#!/usr/bin/env python3
import os
import argparse

from utils import assign_paths, file_reformat, assign_separators #type: ignore

help_title= """
Takes a protein FASTA file and reformats the header so that the protein name and\n
genome name are both retained after using hmmsearch
"""

def get_args():
    parser = argparse.ArgumentParser(prog='name-reformat',
                    description=help_title
                    )
    parser.add_argument('-i', '--input', required=True)
    parser.add_argument('-o', '--output', default='out')
    parser.add_argument('-f', '--format', required=True, choices=['RefSeq', 'GenBank', 'PROKKA', 'MGRAST'])
    parser.add_argument('-v', dest='verbose', action='store_true')
    args = parser.parse_args()
    return(args)

if __name__ == '__main__':
    args = get_args()
    utils_folder, predvirushost_folder, user_folder, user_output_folder = assign_paths(args)
    separators = assign_separators(args.format)
    try:
        os.mkdir(user_output_folder)
    except FileExistsError:
        pass
    input_file: str = os.path.join(user_folder, args.input)
    fasta_file: str = os.path.join(user_output_folder, "fastafile.faa")
    header_file: str = os.path.join(user_output_folder, "fasta-headers.txt")
    file_reformat(separators, input_file, fasta_file, header_file)
