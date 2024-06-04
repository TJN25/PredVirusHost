#!/usr/bin/env python3

import sys
import argparse
import logging 
from typing import Any, Dict
from predvirushost.utils.utils import get_logger
import predvirushost.utils.PredVirusHostClass as pvh

help_title = """
Scores proteins from a FASTA file against models and predicts the host domain of each genome/contig.
"""


def get_args() -> argparse.Namespace:
    parser: argparse.ArgumentParser = argparse.ArgumentParser(prog='PredVirusHost',
                                                              description=help_title,
                                                              allow_abbrev=False
                                                              )
    parser.add_argument('-i', '--input', required=True)
    parser.add_argument('-o', '--output', default='out')
    parser.add_argument('-n', '--number', default=5)
    parser.add_argument('-c', '--cpu', default=5)
    parser.add_argument('-d', '--data', required=True)
    parser.add_argument('--delete', action='store_true')
    parser.add_argument('--preprocess_only', action='store_true')
    parser.add_argument('--process_results_only', action='store_true')
    parser.add_argument('--forcedelete', action='store_true')
    parser.add_argument('--format', required=True,
                        choices=['RefSeq', 'GenBank', 'PROKKA', 'MGRAST', 'Other'])
    parser.add_argument('-v', dest='verbose', action='count')
    args: argparse.Namespace = parser.parse_args()
    return (args)

if __name__ == '__main__':
    args: argparse.Namespace = get_args()
    if args.verbose is None:
        logger = get_logger(0)
    else:
        logger = get_logger(args.verbose)
    logger.info('PredVirusHost starting...')
    logger.debug(f'predvirushost.py running with args: {args}')
    args_d: Dict[str, Any] = vars(args)
    prediction = pvh.PredVirusHost(args=args_d)
    if not args.process_results_only:
        files_msg: str = prediction.check_files()
        if files_msg != "":
            if not args.delete:
                sys.exit(files_msg)
            exit_status: bool = prediction.remove_files(args.forcedelete)
            logger.debug(f'Exit status: {exit_status}')
            if exit_status:
                sys.exit(files_msg)
        prediction.process_fasta()
        prediction.check_short_proteins()
        if not args.preprocess_only:
            prediction.check_hmm()
            prediction.run_hmmsearch()
    if not args.preprocess_only:
        prediction.preprocess_results()
