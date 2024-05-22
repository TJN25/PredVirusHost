#!/usr/bin/env python3
import os
import sys
import subprocess
import argparse
from pathlib import Path

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

def assign_paths(args):
    utils_folder=Path(os.path.dirname(os.path.abspath(__file__)))
    predvirushost_folder= utils_folder.parent.absolute()
    user_folder = os. getcwd()
    user_output_folder = os.path.join(user_folder, args.output)
    return utils_folder, predvirushost_folder, user_folder, user_output_folder

def assign_separators(format):
    match format.lower():
        case 'refseq':
            start_pos, end_pos, separator = 1, 0, "\["
        case 'genbank':
            start_pos, end_pos, separator = 1, 0, "\["
        case 'prokka':
            start_pos, end_pos, separator = 0, 1, "_"
        case 'mgrast':
            start_pos, end_pos, separator = 0, 3, "_"
        case 'mg-rast':
            start_pos, end_pos, separator = 0, 3, "_"
        case _:
            sys.exit(f'File format: {format} not valid. Please provide a valid file format (RefSeq, Genbank, Prokka, MGRAST).')
    return start_pos, end_pos, separator

def file_reformat(separators, args, f, tmp_1, fasta_file,user_output_folder):
    ##TODO include other file types in this process. See predvirushost.sh
    subprocess.run(["sed", "s/ /*/g", args.input], stdout=tmp_1)
    subprocess.run(["sed", f's/{separators[2]}/ /{separators[0]}', os.path.join(user_output_folder, "tmp1")], stdout=fasta_file)
    subprocess.run(["grep", '>', os.path.join(user_output_folder, "fastafile.faa")], stdout=f)

if __name__ == '__main__':
    args = get_args()
    utils_folder, predvirushost_folder, user_folder, user_output_folder = assign_paths(args)
    separators = assign_separators(args.format)
    try:
        os.mkdir(user_output_folder)
    except FileExistsError:
        pass
    tmp_1 = open(f'{user_output_folder}/tmp1', 'w')
    fasta_file = open(f'{user_output_folder}/fastafile.faa', 'w')
    f = open(f'{user_output_folder}/fasta-headers.txt', 'w')
    
    file_reformat(separators, args, f, tmp_1, fasta_file, user_output_folder)
    f.close()
    tmp_1.close()
    fasta_file.close()
