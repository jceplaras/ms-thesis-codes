#!/bin/sh

INPUT_FOLDER="./../Input/Graph/Philippines/"
OUTPUT_FOLDER="./../Output/Heuristics/Philippines/"

PROGRAM_FOLDER="./../Bin/Heuristics/"
p=1
date
for flags in "" "-R -M" "-R" "-M"
do
    flagsfmt="NMNR"
    
    if [ "$flags" = "-R" ]; then
        flagsfmt="NMWR"
    fi
    if [ "$flags" = "-M" ]; then
        flagsfmt="WMNR"
    fi
    if [ "$flags" = "-R -M" ]; then
        flags=(-R -M)
        flagsfmt="WMWR"
    fi

    for ants in 100 1000
    do
        for iter in 10000 100000
        do
            for run in `seq 1 5`
            do
              for p in `seq 2 7`
              do
                    input=$INPUT_FOLDER"Provinces.graph"

                    PROGRAM_NAME="MinMaxAntSystem"
                    PROGRAM_FULL=$PROGRAM_FOLDER$PROGRAM_NAME".run"
                    PROGRAM_OUTPUT_FOLDER=$OUTPUT_FOLDER$PROGRAM_NAME"/"
                    mkdir -p $PROGRAM_OUTPUT_FOLDER
                    fileout=$PROGRAM_OUTPUT_FOLDER"Pmed_"$p"_"$flagsfmt"_"$ants"_"$iter"_"$run
                    if [ -f "$fileout"".ans" ]; then
                        echo "Skipping $fileout"
                    else
                        { time $PROGRAM_FULL $flags -i $iter -n $ants -p $p -f $fileout".log" < $input > $fileout".ans"  ; } 2> $fileout".time"
                        echo $fileout 
                        date
                    fi
              done
            done
        done
    done
done
