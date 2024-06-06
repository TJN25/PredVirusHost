import pickle
from typing import Dict, Any
from predvirushost.utils.PredVirusHostClass import PredVirusHost

class AnalyseResults(PredVirusHost):
    def __init__(self, args: Dict[str, Any]) -> None:
        super().__init__(args)
        self.genome_file: str = f'{self.output_directory}/genomes.pkl'
        self.protein_file: str = f'{self.output_directory}/proteins.pkl'
        self.host_file: str = f'{self.output_directory}/hosts.pkl'

    def load_hosts(self) -> None:
        with open(self.host_file, 'rb') as f:
            self.hosts_d = pickle.load(f)

    def load_proteins(self) -> None:
        with open(self.protein_file, 'rb') as f:
            self.proteins_d = pickle.load(f)

    def load_genomes(self) -> None:
        with open(self.genome_file, 'rb') as f:
            self.genomes_d = pickle.load(f)

    def load_all(self) -> None:
        self.load_hosts()
        self.load_genomes()
        self.load_proteins()

    def view_host(self, host: str) -> list[str]:
        if not hasattr(self, 'hosts_d'):
            self.load_hosts()
        try:
            return self.hosts_d[host]
        except KeyError:
            raise KeyError(f'{host} is not a valid host name. Use one of {list(self.hosts_d.keys())}')
        
