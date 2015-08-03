#/bin/zsh

OUTPUT_DIR="./../Input/Graph/Random/"
PROGRAM_NAME="./../Bin/Generator/RandomGraph.run"

mkdir -p $OUTPUT_DIR

INCREMENT=5
MAX_COUNT=100
FILE_COUNTER=1
for i in `seq 10 $INCREMENT $MAX_COUNT`
do
    for j in `seq 1 5`
    do
        $PROGRAM_NAME -n $i -e -1 > $OUTPUT_DIR"Random_"$(printf "%03d" $i)"_"$(printf "%03d" $j)".graph"
    done 
done

