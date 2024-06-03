import unittest
import process_fasta_input
import os
from typing import Dict, List
from process_fasta_input import ProcessChunk

class TestProcessFastaInput(unittest.TestCase):

    def test_process_line(self):
        file_size_bytes = os.path.getsize('test_data/test.faa')
        file_paths: List[str] = ['test_data/test.faa', 'test_data/test_output']
        bytes_pos: List[int] = [0, file_size_bytes]
        values: List[int] = [1, 5]
        chunk = ProcessChunk(file_paths, bytes_pos, values, 0)
        self.d: dict[bytes, List[List[bytes]]] = {}
        self.current_genome: bytes = b""
        self.short_proteins: List[bytes] = []
        self.current_seq: bytes = b""
        self.line_type: int
        self.protein: bytes
        self.genome: bytes
        self.seq: bytes = b''
        self.protein_dict: Dict[bytes, List[bytes]] = {}
        self.output_lines: str = ''
        do_add_to_dict: bool = False
        do_write_fasta: bool = False

        line_1: bytes = b''
        line_2: bytes = b''
        line_3: bytes = b''
    def test_add_to_dict(self):
        pass


