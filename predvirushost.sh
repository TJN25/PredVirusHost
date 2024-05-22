#!/bin/bash
## PredVirusHost
## Predicts the host domain of contigs from viromes by comparing proteins from a number of
## contigs to hmm models and then scores each contig based on similarity to those models.
## Dependancies:
## - HMMER (http://hmmer.org/download.html)
## - R
## - dplyr (R package)



FILE_PATH=`dirname $0`
keep_files='n'
CPUS='1'
PROTEINCOUNT='1'

while getopts "i:o:d:s:e:kf:c:p:h" arg; do
  case $arg in
    i)
      file1_input=$OPTARG
      #echo $file1
      ;;
    o)
      output_file=$OPTARG
      #echo $output_file
      ;;
    d)
      delim=$OPTARG
      #echo $delim
      ;;
    s)
      pos_start=$OPTARG
      #echo $pos_start
      ;;
    e)
      pos_end=$OPTARG
      #echo $pos_end
      ;;
    k)
      keep_files='y'
      echo "Keeping temp files"
      #echo $keep_files
      ;;
	f)
      file_type=$OPTARG
      #echo $file1
      ;;
	c)
      CPUS=$OPTARG
      #echo $file1
      ;;
	p)
      PROTEINCOUNT=$OPTARG
      #echo $file1
      ;;
    h)
echo 'PredVirusHost.sh: compares proteins from a number of contigs to hmm models and then scores'
echo 'each contig based on similarity to those models.'
echo 'Version 1.1 2024'
echo '# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -'
echo 'usage: [options] <filename> <file type>'
echo ' '
echo 'Basic options:'
echo '  -i : <filename> the protein fasta file with protein identifiers not containing spaces'
echo '  -o : <output file> the output file name (default is the input file name)'
echo '  -f : <file type> the format of the fasta file (MGRAST, PROKKA, Refseq, Other)'
echo '  -c : <Number of cores> The number of cores to use in the hmmsearch step'
echo '  -p : <Number of proteins> contigs with this number of proteins or more will be analysed with the pipeline'
echo ' '
echo 'Options if "Other" file type is selected:'
echo '  -d : <delim> is the character that separates the contig name from the protein name/detail'
echo '  -s : <start_pos> is the number of delimiters that you must pass to be left with just the contig name'
echo '  -e : <end_pos> is the number of delimiters from the end needed to be left with just the contig'
echo '  For MG-RAST files the format would be -d _ -s 0 -e 3'
echo ' '
echo 'Trouble shooting:'
echo '  -k : include in order to keep the temp files to see where there is a problem'
exit
      ;;

  esac
done

if [[ -z $file1_input ]]; then
echo 'Error: Fasta File Needed. Specify with -i <input file>'
echo ' '
echo 'Use -h for more help.'
echo ' '
exit
fi

if [[ -z $output_file ]]; then
output_file=`basename $file1_input`
fi

file1=$file1_input

echo "Writing outputs to $output_file"
mkdir ${output_file}.tmp.folder

arVOG_hmm=$FILE_PATH/data/arVOG.hmm
baPOG_hmm=$FILE_PATH/data/baPOG.hmm
euVOG_hmm=$FILE_PATH/data/euVOG.hmm

 echo 'Match '$file1' to HMM virus models'
 echo `basename $arVOG_hmm`
 echo 'Running HMMSearch on '$file1' and arVOG models'

 hmmsearch --tblout $output_file.tmp.folder/arVOG_res.txt --noali --cpu $CPUS $arVOG_hmm $file1_input >> $output_file.tmp.folder/hmm_output.txt
 echo 'Running HMMSearch on '$file1' and euVOG models'
 hmmsearch --tblout $output_file.tmp.folder/euVOG_res.txt --noali --cpu $CPUS  $euVOG_hmm $file1_input >> $output_file.tmp.folder/hmm_output.txt
 echo 'Running HMMSearch on '$file1' and baPOG models'
 hmmsearch --tblout $output_file.tmp.folder/baPOG_res.txt --noali --cpu $CPUS $baPOG_hmm $file1_input >> $output_file.tmp.folder/hmm_output.txt
 echo 'Making Protein List'

# Calculates a score indicating which domain the genome likely belongs to
host_scoring.R $FILE_PATH $output_file.tmp.folder


cp $output_file.tmp.folder/scores.txt ./$output_file.scores.txt

keep_files_=$keep_files