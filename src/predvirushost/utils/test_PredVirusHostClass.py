import unittest
from typing import Dict, Any
from PredVirusHostClass import PredVirusHost

ARGS: Dict[str, Any] = {'input_file': 'test_data/test.faa', 
                        'output_path': 'test_data/test_output', 
                        'data_path': 'test_data/data', 
                        'format': 'RefSeq',
                        'n_cpus': 1,
                        'n_min': 5,
                        'verbose': None,
                        'process_results_only': False,
                        'preprocess_only': False}

class TestProcessFastaInput(unittest.TestCase):

    def test_check_files(self): 
        prediction = PredVirusHost(ARGS)
        msg: str = prediction.check_files(create_directory=False)
        self.assertEqual(True, len(msg) > 0)

    # def test_check_short_genomes(self):
    #     pass
    # 
    # def test_check_hmm(self): 
    #     pass
    #
    # def test_preprocess_single_file(self):
    #     pass
    #
    # def test_preprocess_results(self):
    #     pass

