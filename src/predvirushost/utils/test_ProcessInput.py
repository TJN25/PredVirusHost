import unittest
from typing import Dict, Any
from ProcessInput import ProcessInput

ARGS: Dict[str, Any] = {'input_file': 'test_data/test.faa', 
                        'output_path': 'test_data/test_output', 
                        'data_path': 'test_data/data', 
                        'format': 'RefSeq',
                        'n_cpus': 1,
                        'n_min': 5,
                        'verbose': None,
                        'process_results_only': False,
                        'preprocess_only': False}

class TestProcessInput(unittest.TestCase):

    def test_check_files(self): 
        prediction = ProcessInput(ARGS)
        msg: str = prediction.check_files(create_directory=False)
        self.assertEqual(True, len(msg) > 0)


