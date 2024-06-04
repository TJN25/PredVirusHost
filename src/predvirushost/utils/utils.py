import os
import sys
import logging as log
from typing import Dict, Any
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

def assign_paths(args: Dict[str, Any]):
    user_folder: str = os.getcwd()
    user_output_folder: str = os.path.join(user_folder, args['output_path'])
    data_folder: str = os.path.join(user_folder, args['data_path'])
    return str(data_folder),  user_folder, user_output_folder

def user_selects_separators() -> tuple[int, int, bytes]:
    valid_response: int = 0
    selected_response: int = 0
    values: list[int] = [0, 0] 
    incorrect_responses: int = 0
    separator: bytes = b''                                                                                                                                                                                                  
    msgs: list[str] = ['Please provide the delimitor that indicates where the genome name begins or ends for the protein names: ',
                       f'Number of times {separator.decode('UTF-8')} appears before the genome begins: ',
                       f'Number of times {separator.decode('UTF-8')} appears before the genome ends (0 if genome continues to the end of the line): ',
                       'Delimitor should be a single character: ',
                       'Please provide an integer value: ']
                       
    while valid_response < 3:
        user_response: str = user_prompt(msgs[selected_response], 'alert')
        if valid_response > 0:
            try:
                values[valid_response - 1] = int(user_response)
                valid_response += 1
                selected_response = valid_response
                continue
            except ValueError:
                incorrect_responses += 1
                selected_response = 4
                continue
        if len(user_response) == 1:
            separator = bytes(user_response, 'utf-8')
            valid_response += 1
            selected_response = valid_response
        else:
            incorrect_responses += 1
            selected_response = 3
        if incorrect_responses > 5:
            sys.exit('Exiting...\n Please read the documentation on how to select delim values')
    return values[0], values[1], separator


def assign_separators(input_format: str) -> tuple[int, int, bytes]:
    match input_format.lower():
        case 'refseq':
            start_pos, end_pos, separator = 1, 0, b"["
        case 'genbank':
            start_pos, end_pos, separator = 1, 0, b"["
        case 'prokka':
            start_pos, end_pos, separator = 0, 1, b"_"
        case 'mgrast':
            start_pos, end_pos, separator = 0, 3, b"_"
        case 'mg-rast':
            start_pos, end_pos, separator = 0, 3, b"_"
        case 'other':
            start_pos, end_pos, separator = user_selects_separators()
        case _:
            sys.exit(f'File format: {
                     format} not valid. Please provide a valid file format (RefSeq, Genbank, Prokka, MGRAST).')
    return start_pos, end_pos, separator
