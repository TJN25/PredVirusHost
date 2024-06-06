import pickle
import inspect
from typing import Any, Dict, List
from predvirushost.utils.PredVirusHostClass import PredVirusHost
from predvirushost.utils.utils import pretty_output

class ProcessResults(PredVirusHost):
    def __init__(self, args: Dict[str, Any]) -> None:
        super().__init__(args)
        self.d: dict[str, List[List[float]]] = {}
        self.models = ['arVOG', 'euVOG', 'baPOG']
        self.hosts = ['Archaea', 'Eukaryota', 'Bacteria']
        if self.n_cpus ==  1:
            self.indexes: list[int] = [1]
        else:
            self.indexes: list[int] = list(range(1, self.n_cpus))



    def assign_host(self, values: list) -> list:
        model_index: int = values[0].index(max(values[0]))
        if values[0][model_index] <= 30:
            return ['None']
        return [self.hosts[model_index]]

    def get_host_assignments(self) -> None:
        key: str
        values: list
        host: list

        for key, values in self.genome_scores.items():
            host = self.assign_host(values)
            self.genome_scores[key][3] = host
    
    def create_hosts_dict(self):
        self.hosts_d: dict[str, list[str]] = {'Archaea': [], 'Eukaryota': [], 'Bacteria': [], 'None': []}
        for key, value in self.genome_scores.items():
            self.hosts_d[value[3][0]].append(key)




    def split_line(self, line: str) -> tuple[str, str, float]:
        words: List[str] = line.rstrip().split()
        protein: str = words[0]
        current_model: str = words[2]
        score: float = float(words[5])
        return protein, current_model, score

    def update_dict(self, protein: str, score: float, weight: float, model_index: int):
        if protein in self.d:
            if weight * score > self.d[protein][0][model_index] * self.d[protein][1][model_index]:
                self.d[protein][0][model_index] = weight
                self.d[protein][1][model_index] = score
        else:
            self.d[protein] = [[0,0,0],[0,0,0]]
            self.d[protein][0][model_index] = weight
            self.d[protein][1][model_index] = score

    def process_results_file(self, model_index: int, file: str, weights: dict):
        with open(file, 'r') as f:
            for line in f:
                if line[0] == "#":
                    continue
                protein, current_model, score = self.split_line(line)
                weight: float = weights[current_model]
                self.update_dict(protein, score, weight, model_index)

    def process_results(self):
        with open(f'{self.data_path}/weights.pkl', 'rb') as pickle_file:
            weights: dict = pickle.load(pickle_file)
        for model_index, model in enumerate(self.models):
            for index in self.indexes:
                file: str = f'{self.output_directory}/{model}_res_{index}.tbl'
                self.process_results_file(model_index, file, weights[model_index])

    def remove_unwanted_characters(self, genome) -> str:
        closing_strings = ['[]', '{}', '()', '"', "''", '<>', '`']
        for item in closing_strings:
            if len(item) == 1:
                count = genome.count(item)
                if count % 2 == 1:
                    genome = genome.replace(item, '')
            else:
                open_count = genome.count(item[0])
                close_count = genome.count(item[1])
                if open_count != close_count:
                    genome = genome.replace(item[0], '').replace(item[1], '')
        return genome

    def process_genomes_file(self, file):
        with open(file, 'rb') as pickle_file:
            genomes_d: dict[bytes, list[bytes]] = pickle.load(pickle_file)
            key: bytes
            values: List[bytes]
            word: bytes
            for key, values in genomes_d.items():
                genome: str = key.decode('UTF-8')
                genome = self.remove_unwanted_characters(genome)
                if genome not in self.genome_scores:
                    self.genome_scores[genome] = [[0,0,0], 0, 0, []]

                for word in values[0]:
                    self.genome_scores[genome][1] += 1
                    protein: str = word.decode('UTF-8').rstrip().replace('>', '')
                    try:
                        scores = self.d[protein][0]
                        weights = self.d[protein][1]
                        current_scores = self.genome_scores[genome][0]
                        weighted_scores = [a*b for a,b in zip(scores,weights)]
                        new_scores = [a+b for a,b in zip(weighted_scores,current_scores)]
                        formatted_scores = [ round(elem, 2) for elem in new_scores ]
                        self.genome_scores[genome][0] = formatted_scores
                        self.genome_scores[genome][2] += 1
                    except KeyError:
                        pass
        self.get_host_assignments()
        self.create_hosts_dict()

    def process_genomes(self):
        self.genome_scores: dict[str, Any] = {}
        for index in self.indexes:
            file: str = f'{self.output_directory}/data_{index}.pkl'
            self.process_genomes_file(file)
        
    def write_genomes(self, file_type: str, file_name: str | None = None):
        if file_name is None:
            file_name = f'{self.output_directory}/genomes.{file_type}'
        if file_type == 'pkl':
            with open(file_name, 'wb') as f:
                pickle.dump(self.genome_scores, f, protocol=pickle.HIGHEST_PROTOCOL) 

    def write_proteins(self, file_type: str, file_name: str | None = None):
        #Allowing the file_name to be set could cause probelms. Consider removing
        if file_name is None:
            file_name = f'{self.output_directory}/proteins.{file_type}'
        if file_type == 'pkl':
            with open(file_name, 'wb') as f:
                pickle.dump(self.d, f, protocol=pickle.HIGHEST_PROTOCOL) 

    def write_hosts(self, file_type: str, file_name: str | None = None):
        #Allowing the file_name to be set could cause probelms. Consider removing
        if file_name is None:
            file_name = f'{self.output_directory}/hosts.{file_type}'
        if file_type == 'pkl':
            with open(file_name, 'wb') as f:
                pickle.dump(self.hosts_d, f, protocol=pickle.HIGHEST_PROTOCOL) 

