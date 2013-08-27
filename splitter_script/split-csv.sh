#!/bin/bash

### Splits a CSV file given the number of lines each flle should have.

SCRIPTNAME=${0##*/}

function print_usage() {
    echo "Usage: $SCRIPTNAME <file.csv> <nbr of lines per file> <root_directory>"
}

## Check the number of arguments.
if [ $# -ne 3 ]; then
    print_usage
    exit 1
fi

## Get the root directory
ROOT_DIR=$3
## And move into it.
cd $3

## Get the header line.
INPUT_FILE=$1
HEADER=$(sed -n '1p' $INPUT_FILE)

## Copy the source file.
tail -n +2 $INPUT_FILE > temp_source_file.csv

## The split command.
SPLIT=$(command -v split || exit 0)

## Prefix and extension.
PREFIX=${INPUT_FILE%%.csv}
EXTENSION=${INPUT_FILE##*.}


## Split the files according to the given number of lines.
NBR_OF_LINES=$2
$SPLIT -d -l $((NBR_OF_LINES - 1)) temp_source_file.csv $PREFIX

NBR_OF_FILES=$(ls -1 *[0-9] | grep $PREFIX | wc -l)


tail -n +2 temp_source_file.csv | $SPLIT -d -l $((NBR_OF_LINES - 1)) temp_source_file.csv $PREFIX

for i in $(echo "$PREFIX*[0-9]");
do
    TEMP_FILE=$$_$i
    echo $HEADER > $TEMP_FILE
    cat $i >> $TEMP_FILE
    mv $TEMP_FILE $i.csv
done

## Remove the temporary copy of the original source file.
rm temp_source_file.csv

printf '%s: created %d files: %s00.%s to %s%02d.%s each with %d lines.\n' $SCRIPTNAME $NBR_OF_FILES $PREFIX $EXTENSION $PREFIX $((NBR_OF_FILES - 1)) $EXTENSION $NBR_OF_LINES
