import os
import process_fasta_input as pf

file_path: str = "/Users/nicth99p/bin/projects/PredVirusHost/sequences/protein/archaeal-virus-new.faa"
out_path: str = "/Users/nicth99p/bin/projects/PredVirusHost/out_test/"
file_size_bytes = os.path.getsize(file_path)


pf.process_chunk(file_path, 0, file_size_bytes, 1, out_path, 5)


