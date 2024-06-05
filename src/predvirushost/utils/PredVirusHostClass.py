import os
import logging as log
from typing import Dict, Any
from predvirushost.utils.utils import assign_paths, assign_separators, pretty_output
logger = log.getLogger(__name__)

DEBUG_MODE: bool = False

class PredVirusHost:
    def __init__(self, args: Dict[str, Any]) -> None:
        if DEBUG_MODE:
            with pretty_output('BOLD', 'FG_WHITE', 'BG_RED') as out:
                out.write('DEBUGGING IS ON. BE CAREFUL!!!')
                out.write('DEBUGGING IS ON. BE CAREFUL!!!')
                out.write('DEBUGGING IS ON. BE CAREFUL!!!')

        self.logger: log.Logger = logger
        self.__set_logging(args['verbose'])
        self.logger.info(f'Initialising PredVirusHost for {args['input_file']}')
        self.__set_variables(args)

    def __set_logging(self, verbose) -> None:
        if verbose is None:
            self.verbosity: int = 0
            log.basicConfig(format="%(levelname)s: %(message)s")
        elif verbose == 1: 
            self.verbosity: int = 1
            log.basicConfig(format="%(message)s", level=log.INFO)
        else:
            self.verbosity: int = 2
            log.basicConfig(format="DEBUG: %(asctime)s %(message)s", level=log.DEBUG)
        self.logger.info("Verbose mode on.")
        self.logger.debug("Debug mode on.")
        self.logger.info(" ")

    def __set_variables(self, args: Dict[str, Any]) -> None:
        self.n_cpus: int = int(args['n_cpus'])
        max_cpus: int | None = os.cpu_count()
        if isinstance(max_cpus, int):
            self.n_cpus: int = min(self.n_cpus, max_cpus)
        if not args['process_results_only']:
            self.format: str = args['format']
            self.n_min: int = int(args['n_min'])
            self.separators: tuple[int, int, bytes] = assign_separators(self.format)
            self.logger.debug(f'running on {self.n_cpus} cpus')
            self.logger.debug(f'minimum number of proteins selected as {self.n_min}')
            self.logger.debug(f'using {self.format} for the formatting of protein strings')
            self.logger.debug(f'using {self.separators} as separator values')
        paths: tuple[str, str, str] = assign_paths(args)
        self.data_path = paths[0]
        self.input_file: str = paths[1]
        self.output_directory: str = paths[2]
        self.logger.info(f'Output will be saved in {self.output_directory}.')
        self.ff: str = os.path.join(self.output_directory, "fastafile.faa")
        self.fh: str = os.path.join(self.output_directory, "fasta-headers.txt")
        self.genomes: dict[str, tuple[list[str], int]] = {}
