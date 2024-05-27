#!/usr/bin/env python3
import os
import sys
import subprocess
import argparse
from pathlib import Path
from typing import get_type_hints
import PredVirusHostClass as pvh

help_title = """
Scores proteins from a FASTA file against models and predicts the host domain of each genome/contig.
"""


def get_args() -> argparse.Namespace:
    parser: argparse.ArgumentParser = argparse.ArgumentParser(prog='PredVirusHost',
                                                              description=help_title
                                                              )
    parser.add_argument('-d', '--directory', required=True)
    parser.add_argument('-o', '--output', default='out')
    parser.add_argument('-n', '--number', default=5)
    parser.add_argument('-f', '--format', required=True,
                        choices=['RefSeq', 'GenBank', 'PROKKA', 'MGRAST'])
    parser.add_argument('-v', dest='verbose', action='store_true')
    args: argparse.Namespace = parser.parse_args()
    return (args)


if __name__ == '__main__':
    args: argparse.Namespace = get_args()
    prediction = pvh.PredVirusHost(args=args)
    prediction.check_files()
    prediction.load_protein_names()
    prediction.protein_count()
    prediction.count_filter(number=args.number)
