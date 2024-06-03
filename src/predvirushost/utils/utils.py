import os
import sys
import logging as log
from pathlib import Path
from . import colors 

logger = log.getLogger(__name__)

def get_logger(verbosity: int) -> log.Logger:
    if verbosity == 0:
        log.basicConfig(format="%(levelname)s: %(message)s")
    if verbosity == 1:
        log.basicConfig(format="%(message)s", level=log.INFO)
    if verbosity == 2:
        log.basicConfig(format="DEBUG: %(asctime)s %(message)s", level=log.DEBUG)
    return logger

def user_prompt(msg, type) -> str:
    user_input: str
    if type == 'alert':
        with colors.pretty_output(colors.BOLD, colors.FG_RED) as out: 
            out.write(msg) 
        user_input = input("")
    else:
        with colors.pretty_output(colors.BOLD) as out: 
            out.write(msg) 
        user_input = input("")

    return user_input

def check_keys(d: dict, n: int) -> None:
    i = 0
    for key in d:
        i += 1
        if i > n:
            return
        print(key)

def assign_paths(args):
    predvirushost_folder: Path = Path(os.path.dirname(os.path.abspath(__file__)))
    user_folder: str = os.getcwd()
    user_output_folder: str = os.path.join(user_folder, args.output)
    data_folder: str = os.path.join(user_folder, args.data)
    return str(data_folder), str(predvirushost_folder), user_folder, user_output_folder


def file_reformat(separators: tuple[int, int, str], input_file: str, fasta_file: str, header_file: str):
    # TODO include the counter at this point for the number of proteins
    exit_val: bool = False
    msg: str = ""
    if os.path.isfile(fasta_file):
        exit_val = True
        msg += f'- Fasta file: {fasta_file}\n'
    if os.path.isfile(header_file):
        exit_val = True
        msg += f'- Fasta headers file: {header_file}\n'
    if exit_val:
        msg = "Exiting due to already present files.\n\n" + msg + \
            "\nPlease select new file names or move the existings files so that they are not written over.\n"
        sys.exit(msg)

    ff = open(fasta_file, 'a')
    fh = open(header_file, 'a')
    with open(input_file, 'r') as fi:
        line: str
        for line in fi:
            line = line.strip()
            line = line.replace(' ', '*')
            if len(line) == 0:
                continue
            ff.write(f'{line}\n')
            if line[0] == ">":
                genome: str
                protein: str
                genome, protein = split_accessions(line, separators)
                fh.write(f'{genome} {protein}\n')
    ff.close()
    fh.close()


def split_accessions(line: str, separators: tuple[int, int, str]) -> tuple[str, str]:
    # TODO make sure each of the tests produce the correct output
    pos_start, pos_end, delim = separators
    line = line.replace('>', '')
    protein: str = line
    words: list[str] = line.split(delim)

    positions: int = pos_start*10 + pos_end
    gl: list[str]
    genome: str = "missing"
    match positions:
        case 10:
            gl = words[pos_start:]
            genome = ''.join(gl)
        case 1:
            gl = words[:pos_end]
            genome = ''.join(gl)
        case 3:
            gl = words[:pos_end]
            genome = ''.join(gl)
        case _:
            pass
    return genome, protein


def assign_separators(input_format: str) -> tuple[int, int, str]:
    match input_format.lower():
        case 'refseq':
            start_pos, end_pos, separator = 1, 0, "["
        case 'genbank':
            start_pos, end_pos, separator = 1, 0, "["
        case 'prokka':
            start_pos, end_pos, separator = 0, 1, "_"
        case 'mgrast':
            start_pos, end_pos, separator = 0, 3, "_"
        case 'mg-rast':
            start_pos, end_pos, separator = 0, 3, "_"
        case _:
            sys.exit(f'File format: {
                     format} not valid. Please provide a valid file format (RefSeq, Genbank, Prokka, MGRAST).')
    return start_pos, end_pos, separator
