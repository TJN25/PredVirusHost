#!/bin/bash
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
     f)
       file_type=$OPTARG
       #echo $file1
       ;;
     h)
 echo 'name-reformat.sh: takes a fasta file and formats it for use in predvirushost.sh'
 echo '# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -'
 echo 'usage: [options] <filename> <file type>'
 echo ' '
 echo 'Basic options:'
 echo '  -i : <filename> the protein fasta file with protein identifiers not containing spaces'
 echo '  -o : <output file> the output file name (default is the INPUT_FILE_NAME-formatted.faa)'
 echo '  -f : <file type> the format of the fasta file (MGRAST, PROKKA, Refseq, Other)'
 echo ' '
 echo 'Options if "Other" file type is selected:'
 echo '  -d : <delim> is the character that separates the contig name from the protein name/detail'
 echo '  -s : <start_pos> is the number of delimiters that you must pass to be left with just the contig name'
 echo '  -e : <end_pos> is the number of delimiters from the end needed to be left with just the contig'
 echo '  For MG-RAST files the format would be -d _ -s 0 -e 3'
 exit
       ;;

   esac
 done


if [[ $file_type = 'PROKKA' ]]; then

       delim='_'
       pos_start='0'
       pos_end='1'


 echo 'PROKKA file type'

 elif [[ $file_type = 'MGRAST' ]]
 then

       delim='_'
       pos_start='0'
       pos_end='3'

 echo 'MGRAST file type'

 elif [[ $file_type = 'Refseq' ]]
 then

       delim='['
       pos_start='1'
       pos_end='0'

 echo 'Refseq file type. Make sure that spaces have been removed'


 elif [[ $file_type = 'Other' ]]
 then

 echo 'Other file type. Make sure delineator, start and end values are correct and all spaces have been removed.'

 if [[ -z $delim ]]; then
 echo 'Error: Delimiter separting the genome name is required. Specify with -d <delimiter>'
 echo ' '
 echo 'Use -h for more help.'
 echo ' '
 exit

 elif [[ -z $pos_start ]]; then
 echo 'Error: Start position of genome name required. Specify with -s <start position>'
 echo ' '
 echo 'Use -h for more help.'
 echo ' '
 exit

 elif [[ -z $pos_end ]]; then
 echo 'Error: Stop position of genome name required. Specify with -e <end position>'
 echo ' '
 echo 'Use -h for more help.'
 echo ' '
 exit

 fi

 else

 echo ' '
 echo 'Error: -f <file type> is required. Options are MGRAST, PROKKA, Refseq and Other. '
 echo 'If Other is selected the the delimiter, start and stop positions of the genome name '
 echo 'is also required.'
 echo ' '
 echo 'Use -h for more help.'
 echo ' '
 exit
 fi

 if [[ -z $file1_input ]]; then
 echo 'Error: Fasta File Needed. Specify with -i <input file>'
 echo ' '
 echo 'Use -h for more help.'
 echo ' '
 exit
 else

 if [[ -z $output_file ]]; then
 output_file=`basename $file1_input`
 fi

 file1=$file1_input

 echo "Writing outputs to $output_file"
 mkdir ${output_file}.tmp.folder
 fi
