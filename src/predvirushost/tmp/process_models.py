import sys
import argparse
import pickle
from typing import Any, Callable, List

def __get_args() -> argparse.Namespace:
    parser: argparse.ArgumentParser = argparse.ArgumentParser(prog='tmp',
                                                              description='',
                                                              allow_abbrev=False
                                                              )
    parser.add_argument('-d', '--directory', required=True)
    parser.add_argument('-v', dest='verbose', action='count')
    args: argparse.Namespace = parser.parse_args()
    return (args)

def create_dict(func: Callable, index) -> dict[str, Any]:
    d: dict[str, Any] =func(index)
    return d

def process_models(model: str, directory: str) -> dict[str, float]:
    file: str = f'{directory}/{model}_weights.txt'
    line: str
    d: dict[str, float] = {}
    with open(file, 'r') as f:
        next(f)
        for line in f:
            words = line.rstrip().split()
            try:
                d[words[0]] = float(words[1])
            except TypeError:
                raise TypeError(f'{words[0]}: {words[1]} cannot be cooerced to type float')
    return d

def main() -> None:
    args: argparse.Namespace = __get_args()
    directory: str = args.directory
    models: list[str] = ['arVOG', 'euVOG', 'baPOG']
    models_dict: list[dict[str, float]] = [process_models(model, directory) for model in models]
    with open(f'{directory}/weights.pkl', 'wb') as pickle_file:
        pickle.dump(models_dict, pickle_file, protocol=pickle.HIGHEST_PROTOCOL) 
    
if __name__ == '__main__':
    sys.exit(main())
