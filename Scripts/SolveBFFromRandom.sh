#!/bin/sh

INPUT_FOLDER="./../Input/Graph/Random/"
OUTPUT_FOLDER="./../Output/BruteForce/"

PROGRAM="./../Bin/Exact/BruteForce.run"

mkdir -p $OUTPUT_FOLDER
for p in `seq 3 7`
do
    for size in `seq 10 5 100`
    do
        for n in `seq 1 5`
        do
            sizefmt=$(printf "%03d" $size)
            nfmt=$(printf "%02d" $n)
            filename="Random_"$sizefmt"_"$nfmt
            date
            { time $PROGRAM -p $p  < $INPUT_FOLDER$filename".graph" > $OUTPUT_FOLDER$filename"_"$p".bforce" } &> $OUTPUT_FOLDER$filename"_"$p".time"
        done
    done
done
