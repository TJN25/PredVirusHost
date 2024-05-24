import os
import sys
import argparse
import subprocess
from pathlib import Path

def assign_paths(args):
    utils_folder=Path(os.path.dirname(os.path.abspath(__file__)))
    predvirushost_folder= utils_folder.parent.absolute()
    user_folder = os. getcwd()
    user_output_folder = os.path.join(user_folder, args.output)
    return utils_folder, predvirushost_folder, user_folder, user_output_folder

def file_reformat(separators, args, f, tmp_1, fasta_file,user_output_folder):
    ##TODO include other file types in this process. See predvirushost.sh
    subprocess.run(["sed", "s/ /*/g", args.input], stdout=tmp_1)
    subprocess.run(["sed", f's/{separators[2]}/ /{separators[0]}', os.path.join(user_output_folder, "tmp1")], stdout=fasta_file)
    subprocess.run(["grep", '>', os.path.join(user_output_folder, "fastafile.faa")], stdout=f)

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

def assign_paths(args):
    utils_folder=Path(os.path.dirname(os.path.abspath(__file__)))
    predvirushost_folder= utils_folder.parent.absolute()
    user_folder = os. getcwd()
    user_output_folder = os.path.join(user_folder, args.output)
    return utils_folder, predvirushost_folder, user_folder, user_output_folder

