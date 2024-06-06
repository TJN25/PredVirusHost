# PredVirusHost

PredVirusHost is a series of tools for predicting the host domain of contigs from viromes (such as metagenomes). 
It does this by comparing proteins from a number of contigs to hmm models and then scores each contig based on 
similarity to those models.

PredVirusHost is built in Python 3.12 and requires the HMMER suite.

# Install

1. Install dependecies

- [HMMER](http://hmmer.org/documentation.html)
- [Jupyter](https://jupyter.org/install)

2. Create environment

- Use Conda/Mamba ([micromamba](https://mamba.readthedocs.io/en/latest/installation/micromamba-installation.html) is small and fast)

```
conda create --name predvirushost -c conda-forge -c defaults python pip
conda activate predvirushost
```

3. Download this repo

4. Install PredVirusHost

```
cd PredVirusHost
pip install .
```

5. Download and extract [models](https://figshare.com/ndownloader/files/46880200)

- `tar xvf models-v0.2.0.tgz`

# Running PredVirusHost

PredVirusHost can be run from the command line or from a jupyter notebook.

## Command line

Running PredVirusHost on command line can be done with `run_predvirushost.py`.
This will require an input fasta file `-i fasta_file.faa`, an output directory 
`-o output_directory/`, the location of the [models]() `--data_path models-v0.2.0`,
and the fasta file protein name format (see below for details) `--format RefSeq`.

```
run_predvirushost.py -i /path/to/input/fasta_file.faa \
                     -o /path/to/output/directory \
                     --data_path /path/to/models/directory \
                     --format <fasta protein name format [RefSeq, GenBank, PROKKA, MGRAST, Other]>
                     --n_min <Minimum number of proteins a genome must have to be included> \
                     --n_cpus <Number of cpu cores to run on>
```

By default, PredVirusHost will check if there are already output files in the specified
output directory in order to prevent overwriting or appending existing files. If you
want to overwrite existing files this can be done with `--delete` (THIS WILL REMOVE ALL
FILES named fastafile\_*.faa, data\_*.pkl, and short_proteins\_*.pkl) which will prompt
for the removal of files. To skip the prompt `--forcedelete` can be added added as well.

The slowest step in the pipeline is `hmmsearch` which is unavoidable due to what hmmsearch
has to do. PredVirusHost can be split into steps so that data can be preprocessed, and
the results data processed, while the hmmsearch can be done separately (e.g. on a cluster).
To run only the preprocessing steps (up to but not including running hmmsearch) use 
`--preprocess_only` and to run the steps after the hmmsearch use `--process_results_only`.

If the hmmsearch is being run separately it should be run with:

```
model=<one of [arVOG, euVOG, baPOG]>
file_number=<number found in fastafile_NUMBER.faa>
hmmsearch --tblout /path/to/output/directory/${model}_res_${file_number}.tbl \
          --noali --cpu <NUMBER OF CPUS TO RUN ON> \
          /path/to/data/${model}.hmm
          /path/to/fastafile_${file_number}.faa
```

## Jupyter Notebook

Install jupyter into the current environment with `pip install jupyterlab`.

- Import modules

```
import predvirushost.utils.ProcessInput as pvhin
import predvirushost.utils.ProcessResults as pvhres
import predvirushost.utils.AnalyseResults as analyse
```

- provide input data for PredViruHost 

```
input_d = {'input_file': '/path/to/fastafile.faa', 
                        'output_path': '/path/to/output/directory', 
                        'data_path': '/path/to/models-v0.2.0', 
                        'format': 'RefSeq',
                        'n_cpus': 1,
                        'n_min': 5,
                        'verbose': None,
                        'process_results_only': False,
                        'preprocess_only': False}
```

- Run preprocessing

```
prediction = pi.ProcessInput(args=input_d)
prediction.check_files()
prediction.process_fasta()
prediction.check_short_genomes()

## These are the hmmsearch steps and can be run separately
prediction.check_hmm()
prediction.run_hmmsearch()
```

- Process results

```
results = pr.ProcessResults(input_d)
results.process_results()
results.process_genomes()
results.write_genomes(file_type='pkl')
results.write_proteins(file_type='pkl')
results.write_hosts(file_type='pkl')
```

- View result

```
analysis = analyse.AnalyseResults(input_d)
analysis.view_host('Archaea')
```

# Input format

Input files with multiple different genomes need to be preprocessed so that each 
protein is mapped to the correct genome. PredVirusHost does this by splitting protein
names on a delimiter.

## Example format (RefSeq)

FILE-NAME.faa
```
>protein_id[contig_name]
protein_sequence

>protein_id[contig_name]
protein_sequence

>protein_id[contig_name]
protein_sequence
```

## Using a different format

If other is selected then PredVirusHost will prompt for:

- A delimiter

 - is the character that separates the contig name from the protein name/detail

- A start position

 - is the number of delimiters that you must pass to be left with just the contig name.

- An end position

 - is the number of delimiters from the end needed to be left with just the contig



