import sys
import os
import mmap
import multiprocessing
import pickle
import logging as log
from typing import Dict, List
logger = log.getLogger(__name__)

MMAP_PAGE_SIZE: int = os.sysconf("SC_PAGE_SIZE")

class ProcessChunk:
    def __init__(self, file_paths: List[str], bytes_pos: List[int], values: List[int], verbosity):
        if verbosity == 0:
            log.basicConfig(format="%(levelname)s: %(message)s")
        elif verbosity == 1: 
            log.basicConfig(format="%(message)s", level=log.INFO)
        else:
            log.basicConfig(format="DEBUG: %(asctime)s %(message)s", level=log.DEBUG)
        log.debug(f'Called: {sys._getframe(  ).f_code.co_name}: {locals()}')
        self.file_path: str = file_paths[0]
        self.output: str = file_paths[1]
        self.start_byte: int = bytes_pos[0]
        self.end_byte: int = bytes_pos[1]
        self.file_counter: int = values[0]
        self.n_min: int = values[1]
        self.page_size: int = os.sysconf("SC_PAGE_SIZE")
        self.offset: int = (self.start_byte // self.page_size) * self.page_size
        self.fasta_file: str = os.path.join(self.output, f"fastafile_{self.file_counter}.faa")
        log.info(f'Processing chunk {self.file_counter} from byte <{self.start_byte}> to byte <{self.end_byte}>')

    
    def read_chunk(self) -> None:
        self.d: dict[bytes, List[List[bytes]]] = {}
        self.current_genome: bytes = b""
        self.short_proteins: List[bytes] = []
        self.current_seq: bytes = b""
        self.line_type: int
        self.protein: bytes
        self.genome: bytes
        self.seq: bytes = b''
        self.protein_dict: Dict[bytes, List[bytes]] = {}
        with open(self.file_path, "r+b") as file:
            with open(self.fasta_file, 'a') as self.ff:
                length = self.end_byte - self.offset
                with mmap.mmap(
                    file.fileno(), length, access=mmap.ACCESS_READ, offset=self.offset
                ) as mmapped_file:
                    mmapped_file.seek(self.start_byte - self.offset)
                    for line in iter(mmapped_file.readline, b""):
                        self.process_line(line)

    def write_chunk(self) -> None:
        with open(os.path.join(self.output, f'data_{self.file_counter}.pkl'), 'wb') as pickle_file:
            pickle.dump(self.protein_dict, pickle_file, protocol=pickle.HIGHEST_PROTOCOL) 
        with open(os.path.join(self.output, f'short_proteins_{self.file_counter}.pkl'), 'wb') as pickle_file:
            pickle.dump(self.short_proteins, pickle_file, protocol=pickle.HIGHEST_PROTOCOL)

    def process_line(self, line: bytes) -> None:
        #TOOD include other formats
        if line[:1] == b'\n' or line[:1] == b'\r': 
            return
        if line[:1] != b'>':
            self.seq += line
            return
        line = line.replace(b' ', b'*')
        self.protein = line
        words: list[bytes] = line.split(b"[")#]
        gl: list[bytes] = words[1:]
        self.genome = b''.join(gl)
        self.process_genome()
        return

    def process_genome(self) -> None:
        output_lines: str = ''
        self.protein_dict[self.protein[1:].rstrip()] = [self.genome.rstrip()]

        if self.current_genome in self.d:
            genomes: List[List[bytes]] = self.d[self.current_genome]
            names: List[bytes] = genomes[0]
            if self.current_genome != self.genome:
                if len(names) < self.n_min:
                    self.short_proteins.append(self.current_genome)
            if genomes[2][0] == b'true':
                output_lines = names[-1].decode('UTF-8') + '\n' + self.seq.decode('UTF-8') + '\n'
                self.ff.write(output_lines)
            else:
                seqs: List[bytes] = genomes[1]
                seqs.append(self.seq)
                if len(names) >= self.n_min:
                    if self.current_genome in self.short_proteins:
                        self.short_proteins.remove(self.current_genome)
                    genomes[2][0] = b'true'
                    for i, seq in enumerate(seqs):
                        output_lines = names[i].decode('UTF-8') + '\n' + seq.decode('UTF-8') + '\n'
                        self.ff.write(output_lines)
                    seqs.clear()
        self.current_genome = self.genome
        if self.genome in self.d:
            genome_list: List[List[bytes]] = self.d[self.genome]
            names = genome_list[0]
            names.append(self.protein)
        else:
            self.d[self.genome] = [[self.protein], [], [b'false']]
        self.seq = b""
        return


def process_chunk(file_paths: List[str], bytes_pos: List[int], values: List[int], verbosity: int) -> None:
    if verbosity == 0:
        log.basicConfig(format="%(levelname)s: %(message)s")
    elif verbosity == 1: 
        log.basicConfig(format="%(message)s", level=log.INFO)
    else:
        log.basicConfig(format="DEBUG: %(asctime)s %(message)s", level=log.DEBUG)
    log.debug(f'Called: {sys._getframe(  ).f_code.co_name}: {locals()}')
    chunk = ProcessChunk(file_paths, bytes_pos, values, verbosity)
    chunk.read_chunk()
    chunk.write_chunk()
    return

def read_file_in_chunks(file_path: str, output: str, n_cpus: int, n_min: int, verbosity: int):
    if verbosity == 0:
        log.basicConfig(format="%(levelname)s: %(message)s")
    elif verbosity == 1: 
        log.basicConfig(format="%(message)s", level=log.INFO)
    else:
        log.basicConfig(format="DEBUG: %(asctime)s %(message)s", level=log.DEBUG)
    log.debug(f'Called: {sys._getframe(  ).f_code.co_name}: {locals()}')
    file_size_bytes = os.path.getsize(file_path)
    if n_cpus == 1:
        file_paths: List[str] = [file_path, output]
        bytes_pos: List[int] = [0, file_size_bytes]
        values: List[int] = [1, n_min]
        process_chunk(file_paths, bytes_pos, values, verbosity)
        return
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
                file_paths: List[str] = [file_path, output]
                bytes_pos: List[int] = [start_byte, end_byte]
                values: List[int] = [file_counter, n_min]
                chunks.append((file_paths, bytes_pos, values, verbosity))
                start_byte = end_byte

    with multiprocessing.Pool(processes=n_cpus) as p:
        p.starmap(process_chunk, chunks)


