import unittest
import process_fasta_input
import os
from typing import Dict, List
from process_fasta_input import ProcessChunk

FILE_SIZE_BYTES = os.path.getsize('test_data/test.faa')
FILE_PATHS: List[str] = ['test_data/test.faa', 'test_data/test_output']
BYTES_POS: List[int] = [0, FILE_SIZE_BYTES]
VALUES: List[int] = [1, 2]

class TestProcessFastaInput(unittest.TestCase):

    def test_process_line(self):
        chunk = ProcessChunk(FILE_PATHS, BYTES_POS, VALUES, (1, 0, b'['), 0)

        line_1: bytes = b'>First [Something\n'
        line_2: bytes = b'\n'
        line_3: bytes = b'MADWMVIP\n'

        result_1: bool = chunk.process_line(line_1)
        result_2: bool = chunk.process_line(line_2)
        result_3: bool = chunk.process_line(line_3)

        self.assertEqual(result_1, True) #line should be treated as a protein name
        self.assertEqual(result_2, False)
        self.assertEqual(result_3, False)
        self.assertEqual(chunk.genome, b'Something\n')
        self.assertEqual(chunk.protein[1:].rstrip(), b'First*[Something')
        self.assertEqual(chunk.seq, b'MADWMVIP\n')

    def test_add_to_dict(self):
        chunk = ProcessChunk(FILE_PATHS, BYTES_POS, VALUES, (1, 0, b'['), 0)

        #First time a new protein and genome is reached
        chunk.genome = b'[Something'
        chunk.protein = b'>First*[Something\n'
        result_1 = chunk.add_to_dict()
        self.assertEqual(result_1, False) 

        #Returns false as 'current_genome' is set to the previous genome
        #and has not been seen before
        chunk.d[b'[Else'] = [[b'>Zeroth*[Else\n'], [b'MADWMVIP\n'], [b'false']]
        chunk.genome = b'[Else'
        chunk.protein = b'>First*[Else\n'
        result_2 = chunk.add_to_dict()
        self.assertEqual(result_2, False) 

        #This flows from the previous run through and will return True because
        #the number of protein is now >= n_min (2)
        chunk.seq = b'PVGARMIP\n'
        chunk.protein = b'>Second*[Else\n'
        result_3 = chunk.add_to_dict()
        self.assertEqual(result_3, True) 
        self.assertEqual(chunk.short_proteins, [b'[Something']) 
        self.assertEqual(chunk.d[b'[Else'][2], [b'true']) 
        self.assertEqual(chunk.output_lines, '>Zeroth*[Else\nMADWMVIP\n>First*[Else\nPVGARMIP\n') 

        #This flows from the previous run and should take the 'true' setting
        #and write only the previous protein to the output
        chunk.seq = b'SVGARMIP\n'
        chunk.protein = b'>Third*[Else\n'
        result_4 = chunk.add_to_dict()
        self.assertEqual(result_4, True) 
        self.assertEqual(chunk.output_lines, '>Second*[Else\nSVGARMIP\n') 

        #TODO test for the change of false to true when n_min in reached
        #TODO test output lines for output when true and output when looping

    def test_split_protein_name(self):

        chunk = ProcessChunk(FILE_PATHS, BYTES_POS, VALUES, (1, 0, b'['), 0)

        line: bytes = b'>First [Something\n'
        chunk.split_protein_name(line) 
        self.assertEqual(chunk.protein, b'>First*[Something\n') #Test the reformat
        self.assertEqual(chunk.genome, b'Something\n') #Test genome split for RefSeq

        chunk = ProcessChunk(FILE_PATHS, BYTES_POS, VALUES, (0, 1, b'|'), 0)

        line: bytes = b'>First |Something\n'
        chunk.split_protein_name(line) 
        self.assertEqual(chunk.genome, b'First*') #Test genome split for genbank

        chunk = ProcessChunk(FILE_PATHS, BYTES_POS, VALUES, (0, 3, b'_'), 0)

        line: bytes = b'>First _Something_else_like_this\n'
        chunk.split_protein_name(line) 
        self.assertEqual(chunk.genome, b'First*_Something_else') #Test genome split for mgrast




