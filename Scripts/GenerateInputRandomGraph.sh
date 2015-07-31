#!/bin/zsh

OUTPUT_DIR="./../Input/Graph/Random/"
PROGRAM_NAME="./../Bin/Generator/RandomGraph.run"

INCREMENT=5
MAX_COUNT=100
FILE_COUNTER=1
for i in `seq 10 $INCREMENT $MAX_COUNT`
do
    $PROGRAM_NAME -n $i -e -1 > $OUTPUT_DIR"Random_"$(printf "%03d" $i)".graph"
    
done

