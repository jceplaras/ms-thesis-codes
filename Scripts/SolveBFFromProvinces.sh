#!/bin/sh

INPUT_FOLDER="./../Input/Graph/Philippines/"
OUTPUT_FOLDER="./../Output/BruteForce/"

PROGRAM="./../Bin/Exact/BruteForce.run"

mkdir -p $OUTPUT_FOLDER
for p in `seq 2 7`
do
    filename="Provinces"
    date
    echo $filename"_"$p
    { time $PROGRAM -p $p  < $INPUT_FOLDER$filename".graph" > $OUTPUT_FOLDER$filename"_"$p".bforce" } &> $OUTPUT_FOLDER$filename"_"$p".time"
done
