import argparse
import os
import time
import mmap
import multiprocessing
from typing import Dict, Union, List
#import itertools

MMAP_PAGE_SIZE: int = os.sysconf("SC_PAGE_SIZE")

def process_line(line: bytes, ff, fh) -> tuple[int, str, str]:
    if line[:1] == b'\n' or line[:1] == b'\r': 
        return 0, "\n", ""
    if line[:1] != b'>':
        ff.write(line.decode("UTF-8"))
        return 1, line.decode("UTF-8"), ""
    line = line.rstrip().replace(b' ', b'*')
    ff.write(line.decode("UTF-8"))
    protein: bytes
    protein = line
    words: list[bytes] = line.split(b"[")#]
    gl: list[bytes] = words[1:]
    genome: bytes
    genome = b''.join(gl)
    fh.write(f'{genome.decode("UTF-8")} {protein.decode("UTF-8")}\n')
    return 2, protein.decode("UTF-8"), genome.decode("UTF-8")

def align_offset(offset, page_size):
    return (offset // page_size) * page_size

def process_chunk(file_path: str, start_byte, end_byte, file_counter: int, output: str) -> None:
    ##TODO The remove functions are needed but will cause problems with pvh.check_files()
    offset = align_offset(start_byte, MMAP_PAGE_SIZE)
    try:
        os.remove(os.path.join(output, f"fastafile_{file_counter}.faa"))
    except OSError:
        pass
    try:
        os.remove(os.path.join(output, f"fasta-headers_{file_counter}.txt"))
    except OSError:
        pass
    ff = open(os.path.join(output, f"fastafile_{file_counter}.faa"), 'a')
    fh = open(os.path.join(output, f"fasta-headers_{file_counter}.txt"), 'a')
    d: dict[str, dict[str, list[str] | int]] = {}
    line_res: tuple[int, str, str]
    with open(file_path, "r+b") as file:
        length = end_byte - offset
        with mmap.mmap(
            file.fileno(), length, access=mmap.ACCESS_READ, offset=offset
        ) as mmapped_file:
            mmapped_file.seek(start_byte - offset)
            current_seq: str = ""
            for line in iter(mmapped_file.readline, b""):
                line_res = process_line(line, ff, fh)
                d, current_seq = process_genome(d, current_seq, line_res)

def process_line_no_write(line: str) -> tuple[int, str, str]:
    if line[0] == '\n' or line[0] == '\r': 
        return 0, "\n", ""
    if line[0] != '>':
        return 1, line, ""
    line = line.rstrip().replace(' ', '*')
    protein: str
    protein = line
    words: list[str] = line.split("[")#]
    gl: list[str] = words[1:]
    genome: str
    genome = ''.join(gl)
    return 2, protein, genome

def process_whole_file(file_path: str) -> dict[str, dict[str, list[str] | int]]:
    d: Dict[str, Dict[str, Union[List[str], List[str], int]]] = {}
    current_seq: str = ""
    with open(file_path, 'r')as f:
        for line in f:
            line_res: tuple[int, str, str] = process_line_no_write(line)
            d, current_seq = process_genome(d, current_seq, line_res)
    return d

def process_genome(d: Dict[str, Dict[str, Union[List[str], List[str], int]]], seq: str, line: tuple[int, str, str]) -> tuple[Dict[str, Dict[str, Union[List[str], List[str], int]]], str]:
    if line[0] == 0:
        return d, seq
    if line[0] == 1:
        seq += f'{line[1]}\n'
        return d, seq
    if line[0] == 2:
        if line[2] in d:
            current_genome: Dict[str, Union[List[str], List[str], int]] = d[line[2]]
            current_genome['names'].append(line[1])
            current_genome['seqs'].append(seq)
            current_genome['n'] += 1
        else:
            d[line[2]] = {"names": [line[1]], "seqs": [], "n": 1}
        seq = ""
    return d, seq

def read_file_in_chunks(file_path: str, output: str, n_cpus: int):
    file_size_bytes = os.path.getsize(file_path)
    base_chunk_size = file_size_bytes // n_cpus
    chunks = []

    with open(file_path, "r+b") as file:
        with mmap.mmap(
            file.fileno(), length=0, access=mmap.ACCESS_READ
        ) as mmapped_file:
            start_byte = 0
            file_counter: int = 0
            for _ in range(n_cpus):
                file_counter += 1
                end_byte = min(start_byte + base_chunk_size, file_size_bytes)
                end_byte = mmapped_file.find(b">", end_byte)
                end_byte = end_byte if end_byte != -1 else file_size_bytes
                chunks.append((file_path, start_byte, end_byte, file_counter, output))
                start_byte = end_byte

    with multiprocessing.Pool(processes=n_cpus) as p:
        p.starmap(process_chunk, chunks)

def process_fasta_file(file_path: str, output: str, n_cpus: int) -> None:
    read_file_in_chunks(file_path, output, n_cpus)
