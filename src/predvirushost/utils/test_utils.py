import unittest
from utils import assign_paths
from typing import Dict

class TestUtils(unittest.TestCase):

    def test_assign_paths(self):
        args: Dict[str, str] = {'output_path': '~/bin/tmp', 
                                'data_path': '../../../../data/', 
                                'input_file': '/Users/nicth99p/bin/projects/PredVirusHost/predvirushost/src/predvirushost/utils/fasta.faa'}
        paths: tuple[str, str, str] = assign_paths(args = args)
        self.assertEqual(paths[0], '/Users/nicth99p/bin/projects/PredVirusHost/data')
        self.assertEqual(paths[1], '/Users/nicth99p/bin/projects/PredVirusHost/predvirushost/src/predvirushost/utils/fasta.faa')
        self.assertEqual(paths[2], '/Users/nicth99p/bin/tmp')
