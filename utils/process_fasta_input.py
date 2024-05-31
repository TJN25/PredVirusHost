import os
import mmap
import multiprocessing
import json
from typing import Dict, List

MMAP_PAGE_SIZE: int = os.sysconf("SC_PAGE_SIZE")

def process_line(line: bytes) -> tuple[int, str, str]:
    if line[:1] == b'\n' or line[:1] == b'\r': 
        return 0, "\n", ""
    if line[:1] != b'>':
        #ff.write(line.decode("UTF-8"))
        return 1, line.decode("UTF-8"), ""
    line = line.rstrip().replace(b' ', b'*')
    #ff.write(line.decode("UTF-8"))
    protein: bytes
    protein = line
    words: list[bytes] = line.split(b"[")#]
    gl: list[bytes] = words[1:]
    genome: bytes
    genome = b''.join(gl)
    #fh.write(f'{genome.decode("UTF-8")} {protein.decode("UTF-8")}\n')
    return 2, protein.decode("UTF-8"), genome.decode("UTF-8")

def align_offset(offset, page_size):
    return (offset // page_size) * page_size

def process_chunk(file_path: str, start_byte, end_byte, file_counter: int, output: str, n_min: int) -> None:
    ##TODO The remove functions are needed but will cause problems with pvh.check_files()
    offset = align_offset(start_byte, MMAP_PAGE_SIZE)
    #try:
    #    os.remove(os.path.join(output, f"fastafile_{file_counter}.faa"))
    #except OSError:
    #    pass
    #try:
    #    os.remove(os.path.join(output, f"fasta-headers_{file_counter}.txt"))
    #except OSError:
    #    pass
    #ff = open(os.path.join(output, f"fastafile_{file_counter}.faa"), 'a')
    #fh = open(os.path.join(output, f"fasta-headers_{file_counter}.txt"), 'a')
    fasta_file: str = os.path.join(output, f"fastafile_{file_counter}.faa")
    d: dict[str, List[List[str]]] = {}
    current_genome: str = ""
    short_proteins: List[str] = []
    line_res: tuple[int, str, str]
    with open(file_path, "r+b") as file:
        length = end_byte - offset
        with mmap.mmap(
            file.fileno(), length, access=mmap.ACCESS_READ, offset=offset
        ) as mmapped_file:
            mmapped_file.seek(start_byte - offset)
            current_seq: str = ""
            for line in iter(mmapped_file.readline, b""):
                line_res = process_line(line)
                d, current_seq, current_genome, short_proteins = process_genome(d, current_seq, current_genome, line_res, n_min, fasta_file, short_proteins)
    with open(os.path.join(output, f'data_{file_counter}.json'), 'w') as json_file:
        json.dump(d, json_file, indent=4,  sort_keys=True, separators=(',',':'))
    with open(os.path.join(output, f'short_proteins_{file_counter}.json'), 'w') as json_file:
        json.dump(short_proteins, json_file)

def process_genome(d: Dict[str, List[List[str]]], seq: str, current_genome: str, line: tuple[int, str, str], n_min: int, fasta_file: str, short_proteins: List[str]) -> tuple[Dict[str, List[List[str]]], str, str, List[str]]:
    line_type: int = line[0]
    genome: str = line[2]
    protein: str = line[1]
    if line_type == 0:
        return d, seq, current_genome, short_proteins
    if line_type == 1:
        seq += protein
        return d, seq, current_genome, short_proteins
    if line_type == 2:
        if current_genome in d:
            genomes: List[List[str]] = d[current_genome]
            names: List[str] = genomes[0]
            if current_genome != genome:
                if len(names) < n_min:
                    short_proteins.append(current_genome)
            if genomes[2][0] == 'true':
                with open(fasta_file, 'a') as ff:
                    ff.write(f'{names[-1]}\n{seq}\n')
            else:
                seqs: List[str] = genomes[1]
                seqs.append(seq)
                if len(names) >= n_min:
                    if current_genome in short_proteins:
                        short_proteins.remove(current_genome)
                    genomes[2][0] = 'true'
                    with open(fasta_file, 'a') as ff:
                        for i, seq in enumerate(seqs):
                            ff.write(f'{names[i]}\n{seq}\n')
                    seqs.clear()
        current_genome = genome
        if genome in d:
            genome_list: List[List[str]] = d[genome]
            names = genome_list[0]
            names.append(protein)
        else:
            d[genome] = [[protein], [], ['false']]
        seq = ""
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


