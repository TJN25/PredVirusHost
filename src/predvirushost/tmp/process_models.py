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

def split_line(line: str) -> tuple[str, str, float]:
    words: List[str] = line.rstrip().split()
    protein: str = words[0]
    current_model: str = words[2]
    score: float = float(words[5])
    return protein, current_model, score

def update_dict(d: dict, protein: str, score: float, weight: float, model_index: int) -> dict:
    if protein in d:
        if weight * score > d[protein][0][model_index] * d[protein][1][model_index]:
            d[protein][0][model_index] = weight
            d[protein][1][model_index] = score
    else:
        d[protein] = [[0,0,0],[0,0,0]]
        d[protein][0][model_index] = weight
        d[protein][1][model_index] = score
    return d

def process_file(d: dict, model_index: int, file: str, weights: dict) -> dict:
    with open(file, 'r') as f:
        for line in f:
            if line[0] == "#":
                continue
            protein, current_model, score = split_line(line)
            weight: float = weights[current_model]
            d = update_dict(d, protein, score, weight, model_index)
    return d

def process_results(models: List[str], indexes: List[int], directory: str) -> dict[str, List[List[Any]]]:
    with open('/Users/nicth99p/bin/projects/PredVirusHost/predvirushost/data/weights.pkl', 'rb') as pickle_file:
        weights: dict = pickle.load(pickle_file)
    d: dict[str, List[List[Any]]] = {}
    for model_index, model in enumerate(models):
        for index in indexes:
            file: str = f'{directory}/{model}_res_{index}.tbl'
            d = process_file(d, model_index, file, weights[model_index])
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
