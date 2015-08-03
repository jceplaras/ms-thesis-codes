#!/bin/sh

INPUT_FOLDER="./../Input/IP/Random/"
OUTPUT_FOLDER="./../Output/Exact/"

mkdir -p $OUTPUT_FOLDER
for p in `seq 3 7`
do
    for n in `seq 1 5`
    do
        for size in `seq 60 5 100`
        do
            sizefmt=$(printf "%03d" $size)
            nfmt=$(printf "%02d" $n)
            filename="Random_"$sizefmt"_"$nfmt"_"$p".lp"
            lp_solve -time -S1 < $INPUT_FOLDER$filename &> $OUTPUT_FOLDER$filename".out"
        done
    done
done
