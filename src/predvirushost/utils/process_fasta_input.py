import os
import mmap
import multiprocessing
import pickle
import hashlib
import logging
from typing import Dict, List

MMAP_PAGE_SIZE: int = os.sysconf("SC_PAGE_SIZE")
logger = logging.getLogger(__name__)

def process_line(line: bytes) -> tuple[int, bytes, bytes]:
    if line[:1] == b'\n' or line[:1] == b'\r': 
        return 0, b"\n", b""
    if line[:1] != b'>':
        return 1, line, b""
    line = line.rstrip().replace(b' ', b'*')
    protein: bytes
    protein = line
    words: list[bytes] = line.split(b"[")#]
    gl: list[bytes] = words[1:]
    genome: bytes
    genome = b''.join(gl)
    return 2, protein, genome

def align_offset(offset, page_size):
    return (offset // page_size) * page_size

def process_chunk(file_path: str, start_byte, end_byte, file_counter: int, output: str, n_min: int) -> None:
    logger.debug(f'Processing chunk {file_counter} from byte <{start_byte}> to byte <{end_byte}>')
    offset = align_offset(start_byte, MMAP_PAGE_SIZE)
    fasta_file: str = os.path.join(output, f"fastafile_{file_counter}.faa")
    d: dict[bytes, List[List[bytes]]] = {}
    current_genome: bytes = b""
    short_proteins: List[bytes] = []
    line_res: tuple[int, bytes, bytes]
    with open(file_path, "r+b") as file:
        with open(fasta_file, 'a') as ff:
            length = end_byte - offset
            with mmap.mmap(
                file.fileno(), length, access=mmap.ACCESS_READ, offset=offset
            ) as mmapped_file:
                mmapped_file.seek(start_byte - offset)
                current_seq: bytes = b""
                for line in iter(mmapped_file.readline, b""):
                    line_res = process_line(line)
                    d, current_seq, current_genome, short_proteins = process_genome(d, current_seq, current_genome, line_res, n_min, fasta_file, short_proteins, ff)
    with open(os.path.join(output, f'data_{file_counter}.pkl'), 'wb') as pickle_file:
        pickle.dump(d, pickle_file, protocol=pickle.HIGHEST_PROTOCOL)
    with open(os.path.join(output, f'short_proteins_{file_counter}.pkl'), 'wb') as pickle_file:
        pickle.dump(short_proteins, pickle_file, protocol=pickle.HIGHEST_PROTOCOL)

def process_genome(d: Dict[bytes, List[List[bytes]]], seq: bytes, current_genome: bytes, line: tuple[int, bytes, bytes], n_min: int, fasta_file: str, short_proteins: List[bytes], ff) -> tuple[Dict[bytes, List[List[bytes]]], bytes, bytes, List[bytes]]:
    line_type: int = line[0]
    genome: bytes = line[2]
    protein: bytes = line[1]
    if line_type == 0:
        return d, seq, current_genome, short_proteins
    if line_type == 1:
        seq += protein
        return d, seq, current_genome, short_proteins
    if line_type == 2:
        hash_name: bytes = bytes(hashlib.md5(protein).hexdigest(), 'utf-8')
        if current_genome in d:
            genomes: List[List[bytes]] = d[current_genome]
            names: List[bytes] = genomes[0]
            if current_genome != genome:
                if len(names) < n_min:
                    short_proteins.append(current_genome)
            if genomes[2][0] == b'true':
                ff.write(f'>{names[-1].decode('UTF-8')}\n{seq.decode('UTF-8')}\n')
            else:
                seqs: List[bytes] = genomes[1]
                seqs.append(seq)
                if len(names) >= n_min:
                    if current_genome in short_proteins:
                        short_proteins.remove(current_genome)
                    genomes[2][0] = b'true'
                    for i, seq in enumerate(seqs):
                        ff.write(f'>{names[i].decode('UTF-8')}\n{seq.decode('UTF-8')}\n')
                    seqs.clear()
        current_genome = genome
        if genome in d:
            genome_list: List[List[bytes]] = d[genome]
            names = genome_list[0]
            names.append(hash_name)
        else:
            d[genome] = [[hash_name], [], [b'false']]
        seq = b""
    return d, seq, current_genome, short_proteins

def read_file_in_chunks(file_path: str, output: str, n_cpus: int, n_min: int):
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
                chunks.append((file_path, start_byte, end_byte, file_counter, output, n_min))
                start_byte = end_byte

    with multiprocessing.Pool(processes=n_cpus) as p:
        p.starmap(process_chunk, chunks)

def process_fasta_file(file_path: str, output: str, n_cpus: int, n_min: int) -> None:
    read_file_in_chunks(file_path, output, n_cpus, n_min)


