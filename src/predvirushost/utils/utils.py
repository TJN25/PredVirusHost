import os
import sys
import logging as log
from typing import Dict, Any
from pathlib import Path

logger = log.getLogger(__name__)

def get_logger(verbosity: int) -> log.Logger:
    if verbosity == 0:
        log.basicConfig(format="%(levelname)s: %(message)s")
    if verbosity == 1:
        log.basicConfig(format="%(message)s", level=log.INFO)
    if verbosity == 2:
        log.basicConfig(format="DEBUG: %(asctime)s %(message)s", level=log.DEBUG)
    return logger

def user_prompt(msg, msg_type) -> str:
    """Prompt the user for a response with a message that can be displayed in 
    different ways."""
    user_input: str
    if msg_type == 'alert':
        with pretty_output(BOLD, FG_RED) as out: 
            out.write(msg) 
        user_input = input("")
    else:
        with pretty_output(BOLD) as out: 
            out.write(msg) 
        user_input = input("")
    return user_input

def get_absolute_paths(user_path: str) -> str:
    abs_path: str = ''
    match user_path[0]:
        case '/':
            abs_path = user_path
        case '~':
            abs_path = os.path.expanduser(user_path)
        case '.':
            abs_path = os.path.abspath(user_path)
        case _:
            abs_path = os.path.abspath(user_path)
    return abs_path

def assign_paths(args: Dict[str, Any]):
    """Process user input to assign paths as absolute paths"""
    user_output_folder: str = get_absolute_paths(user_path=args['output_path'])
    data_folder: str = get_absolute_paths(user_path=args['data_path'])
    input_folder: str = get_absolute_paths(user_path=args['input_file'])

    return data_folder, input_folder, user_output_folder

def user_selects_separators() -> tuple[int, int, bytes]:
    """Prompts the user for the separator data and validates the input."""
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
    """Takes the file type from the user input and assign separator values."""
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


# Special END separator
END = '0e8ed89a-47ba-4cdb-938e-b8af8e084d5c'

# Text attributes
ALL_OFF = '\033[0m'
BOLD = '\033[1m'
UNDERSCORE = '\033[4m'
BLINK = '\033[5m'
REVERSE = '\033[7m'
CONCEALED = '\033[7m'

# Foreground colors
FG_BLACK = '\033[30m'
FG_RED = '\033[31m'
FG_GREEN = '\033[32m'
FG_YELLOW = '\033[33m'
FG_BLUE = '\033[34m'
FG_MAGENTA = '\033[35m'
FG_CYAN = '\033[36m'
FG_WHITE = '\033[37m'

# Background colors
BG_BLACK = '\033[40m'
BG_RED = '\033[41m'
BG_GREEN = '\033[42m'
BG_YELLOW = '\033[43m'
BG_BLUE = '\033[44m'
BG_MAGENTA = '\033[45m'
BG_CYAN = '\033[46m'
BG_WHITE = '\033[47m'


class pretty_output():
    '''
    Context manager for pretty terminal prints
    '''

    def __init__(self, *attr):
        self.attributes = attr

    def __enter__(self):
        return self

    def __exit__(self, type, value, traceback):
        pass

    def write(self, msg):
        style = ''.join(self.attributes)
        print('{}{}{}'.format(style, msg.replace(END, ALL_OFF + style), ALL_OFF))

