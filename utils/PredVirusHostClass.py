import sys
import os
# import pandas
from utils import assign_paths, file_reformat, assign_separators

class PredVirusHost:
    def __init__(self, args):
        self.utils_folder, self.predvirushost_folder, self.user_folder, self.user_output_folder = assign_paths(args)
        self.separators = assign_separators(args.format)
        try:
            os.mkdir(self.user_output_folder)
        except FileExistsError:
            pass
        self.ff = os.path.join(self.user_folder, args.directory, "fastafile.faa") ##input fastafile.faa
        self.fh = os.path.join(self.user_folder, args.directory, "fasta-headers.txt") ##input fasta-headers.txt
        print(self.ff)

if __name__ == '__main__':
    sys.exit('Do not run PredVirusHostClass directly.')