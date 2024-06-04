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
        chunk = ProcessChunk(file_paths, bytes_pos, values, (1, 0, b'['), 0)
        chunk.create_chunk_variables()
        line_1: bytes = b'>First [Something\n'
        line_2: bytes = b'\n'
        line_3: bytes = b'MADXMVIP\n'
        result_1: bool = chunk.process_line(line_1)
        result_2: bool = chunk.process_line(line_2)
        result_3: bool = chunk.process_line(line_3)
        self.assertEqual(result_1, True)
        self.assertEqual(result_2, False)
        self.assertEqual(result_3, False)
        self.assertEqual(chunk.genome, b'Something\n')
        self.assertEqual(chunk.protein[1:].rstrip(), b'First*[Something')
        self.assertEqual(chunk.seq, b'MADXMVIP\n')

    def test_add_to_dict(self):
        file_size_bytes = os.path.getsize('test_data/test.faa')
        file_paths: List[str] = ['test_data/test.faa', 'test_data/test_output']
        bytes_pos: List[int] = [0, file_size_bytes]
        values: List[int] = [1, 5]
        chunk = ProcessChunk(file_paths, bytes_pos, values, (1, 0, b'['), 0)
        chunk.create_chunk_variables()
        chunk.genome = b'[Something'
        chunk.protein = b'>First [Something\n'
        result_1 = chunk.add_to_dict()
        chunk.d[b'[Else'] = [[b'Zeroth [Else'], [], [b'true']]
        chunk.genome = b'[Else'
        chunk.protein = b'>First [Else\n'
        result_2 = chunk.add_to_dict()
        chunk.protein = b'>Second [Else\n'
        result_3 = chunk.add_to_dict()
        self.assertEqual(result_1, False) 
        self.assertEqual(result_2, False) 
        self.assertEqual(result_3, True) 
        self.assertEqual(chunk.short_proteins, [b'[Something']) 
        #TODO test for the change of false to true when n_min in reached
        #TODO test output lines for output when true and output when looping


