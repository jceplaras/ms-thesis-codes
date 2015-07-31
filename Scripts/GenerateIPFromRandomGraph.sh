#!/bin/zsh

INPUT_DIR="../Input/Graph/Random/"
OUTPUT_DIR="../Input/IP/"
PROGRAM_NAME="./../Bin/Exact/GraphToIP.run"
mkdir -p $OUTPUT_DIR
for filename in `ls $INPUT_DIR`
do
    for p in `seq 3 7`
    do
        OUTPUT_FILE=${filename/.graph/}
        $PROGRAM_NAME -p $p < $INPUT_DIR$filename > $OUTPUT_DIR$OUTPUT_FILE"_"$p".lp"
    done
done
