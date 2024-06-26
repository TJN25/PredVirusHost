import sys
import os
import mmap
import multiprocessing
import pickle
import logging as log
from typing import List
logger = log.getLogger(__name__)

MMAP_PAGE_SIZE: int = os.sysconf("SC_PAGE_SIZE")

class ProcessChunk:
    def __init__(self, file_paths: List[str], bytes_pos: List[int], values: List[int], separators: tuple[int, int, bytes], verbosity: int):
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
        self.separators: tuple[int, int, bytes] = separators
        self.__create_chunk_variables()
        log.info(f'Processing chunk {self.file_counter} from byte <{self.start_byte}> to byte <{self.end_byte}>')
        

    def __create_chunk_variables(self) -> None:
        self.d: dict[bytes, List[List[bytes]]] = {}
        self.current_genome: bytes = b""
        self.short_proteins: List[bytes] = []
        self.current_seq: bytes = b""
        self.line_type: int
        self.protein: bytes
        self.genome: bytes
        self.seq: bytes = b''
        # self.protein_dict: Dict[bytes, bytes] = {}
        self.output_lines: str = ''

    def read_chunk(self, *, write_data: bool = True) -> None:
        """Read in chunk of fasta file line by line and pass to processing functions."""
        do_add_to_dict: bool = False
        do_write_fasta: bool = False
        with open(self.file_path, "r+b") as file:
            with open(self.fasta_file, 'a') as self.ff:
                length = self.end_byte - self.offset
                with mmap.mmap(
                    file.fileno(), length, access=mmap.ACCESS_READ, offset=self.offset
                ) as mmapped_file:
                    mmapped_file.seek(self.start_byte - self.offset)
                    for line in iter(mmapped_file.readline, b""):
                        do_add_to_dict = self.process_line(line)
                        if not do_add_to_dict:
                            continue
                        do_write_fasta = self.add_to_dict()
                        if not do_write_fasta:
                            continue
                        if write_data:
                            self.ff.write(self.output_lines)


    def write_chunk(self) -> None:
        """Write the dictionaries of proteins and short proteins out to files."""
        with open(os.path.join(self.output, f'data_{self.file_counter}.pkl'), 'wb') as pickle_file:
            pickle.dump(self.d, pickle_file, protocol=pickle.HIGHEST_PROTOCOL) 
            # pickle.dump(self.protein_dict, pickle_file, protocol=pickle.HIGHEST_PROTOCOL) 
        with open(os.path.join(self.output, f'short_proteins_{self.file_counter}.pkl'), 'wb') as pickle_file:
            pickle.dump(self.short_proteins, pickle_file, protocol=pickle.HIGHEST_PROTOCOL)

    def split_protein_name(self, line: bytes) -> None:
        """
        Take in a line that contains a protein name and process with the 
        separator data into a protein name without spaces and a genome name.
        """
        start_pos: int = self.separators[0]
        end_pos: int = self.separators[1]
        delim: bytes = self.separators[2]

        if start_pos > end_pos:
            words: list[bytes] = line.split(delim)#]
            gl: list[bytes] = words[start_pos:]
            self.genome = delim.join(gl).rstrip()
        elif start_pos < end_pos:
            words: list[bytes] = line.split(delim)#]
            gl: list[bytes] = words[start_pos:end_pos]
            self.genome = delim.join(gl).replace(b'>', b'').rstrip()
        line = line.replace(b' ', b'*') 
        self.protein = line
        return

    def process_line(self, line: bytes) -> bool:
        """Take in a line and check if it is blank, a protein sequence or 
        a protein name."""
        #TOOD include other formats
        if line[:1] == b'\n' or line[:1] == b'\r': 
            return False
        if line[:1] != b'>':
            self.seq += line
            return False
        self.split_protein_name(line)
        return True

    def add_to_dict(self) -> bool:
        """Append protein names, genome names and sequences to a dictionary"""
        do_write: bool = False
        self.output_lines = ''
        # self.protein_dict[self.protein[1:].rstrip()] = self.genome.rstrip()

        if self.current_genome in self.d:
            genomes: List[List[bytes]] = self.d[self.current_genome]
            names: List[bytes] = genomes[0]
            if self.current_genome != self.genome:
                if len(names) < self.n_min and self.current_genome not in self.short_proteins:
                    self.short_proteins.append(self.current_genome)
            if genomes[2][0] == b'true':
                self.output_lines = names[-1].decode('UTF-8') + self.seq.decode('UTF-8')
                do_write = True
            else:
                seqs: List[bytes] = genomes[1]
                seqs.append(self.seq)
                if len(names) >= self.n_min:
                    if self.current_genome in self.short_proteins:
                        self.short_proteins.remove(self.current_genome)
                    genomes[2][0] = b'true'
                    for i, seq in enumerate(seqs):
                        self.output_lines += names[i].decode('UTF-8') +  seq.decode('UTF-8')
                        do_write = True
                    seqs.clear()
        self.current_genome = self.genome
        if self.genome in self.d:
            genome_list: List[List[bytes]] = self.d[self.genome]
            names = genome_list[0]
            names.append(self.protein)
        else:
            self.d[self.genome] = [[self.protein], [], [b'false']]
        self.seq = b""
        return do_write


def process_chunk(file_paths: List[str], bytes_pos: List[int], values: List[int], separators: tuple[int, int, bytes], verbosity: int) -> None:
    """Take a section of a file and create a ProcessChunk instance to run
    over the chunk of the file provided."""
    if verbosity == 0:
        log.basicConfig(format="%(levelname)s: %(message)s")
    elif verbosity == 1: 
        log.basicConfig(format="%(message)s", level=log.INFO)
    else:
        log.basicConfig(format="DEBUG: %(asctime)s %(message)s", level=log.DEBUG)
    log.debug(f'Called: {sys._getframe(  ).f_code.co_name}: {locals()}')
    chunk = ProcessChunk(file_paths, bytes_pos, values, separators, verbosity)
    chunk.read_chunk()
    chunk.write_chunk()
    return

def read_file_in_chunks(file_path: str, output: str, n_cpus: int, n_min: int, separators: tuple[int, int, bytes], verbosity: int):
    """Split the file into similar sized chunks based on the number of required cores"""
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
        process_chunk(file_paths, bytes_pos, values, separators, verbosity)
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
                chunks.append((file_paths, bytes_pos, values, separators, verbosity))
                start_byte = end_byte

    with multiprocessing.Pool(processes=n_cpus) as p:
        p.starmap(process_chunk, chunks)


