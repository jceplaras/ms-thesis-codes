#!/bin/zsh
INPUT_DIR="./../Input/Graph/Random/"
PROGRAM_DIR="./../Bin/Heuristics/"
PROGRAM_NAME="AntSystem.run"
PROGRAM_NAME_FULL=$PROGRAM_DIR$PROGRAM_NAME
PROGRAM_NAME_CLEAN=${PROGRAM_NAME/".run"/""}
LOG_DIR="./../Output/Log/"$PROGRAM_NAME_CLEAN"/"
TIME_DIR="./../Output/Time/"$PROGRAM_NAME_CLEAN"/"
SOLVE_DIR="./../Output/Heuristics/"$PROGRAM_NAME_CLEAN"/"

mkdir -p $LOG_DIR
mkdir -p $TIME_DIR
mkdir -p $SOLVE_DIR

#number of ants
MIN_ANT_COUNT=10
MAX_ANT_COUNT=100
INC_ANT_COUNT=10

#number of facilities
MIN_FACILITY_COUNT=3
MAX_FACILITY_COUNT=7
INC_FACILITY_COUNT=1

#number of iterations
MIN_ITER_COUNT=100
MAX_ITER_COUNT=10000
MUL_ITER_COUNT=10

#number of runs
MAX_RUN_COUNT=25
for filename in `ls $INPUT_DIR`
do
    filenameClean=${filename/".graph"/""}
    for (( iterCount = $MIN_ITER_COUNT ; iterCount <= $MAX_ITER_COUNT ; iterCount*=$MUL_ITER_COUNT ));
    do    
        for antCount in `seq $MIN_ANT_COUNT $INC_ANT_COUNT $MAX_ANT_COUNT`
        do
            for facCount in `seq $MIN_FACILITY_COUNT $INC_FACILITY_COUNT $MAX_FACILITY_COUNT`
            do
                for runCount in `seq 1 $MAX_RUN_COUNT`
                do

                iterCountFmt=$(printf "%06d" $iterCount) 
                antCountFmt=$(printf "%04d" $antCount)
                facCountFmt=$(printf "%02d" $facCount)
                runCountFmt=$(printf "%03d" $runCount)


                fileOutput=$filenameClean"_"$iterCountFmt"_"$antCountFmt"_"$facCountFmt"_NR_NM_"$runCountFmt
                { time $PROGRAM_NAME_FULL -i $iterCount -n $antCount -p $facCount -f $SOLVE_DIR$fileOutput".ans" < $INPUT_DIR$filename > $LOG_DIR$fileOutput".log" ; } 2> $TIME_DIR$fileOutput".time"
                fileOutput=$filenameClean"_"$iterCountFmt"_"$antCountFmt"_"$facCountFmt"_WR_NM_"$runCountFmt
                { time $PROGRAM_NAME_FULL -i $iterCount -n $antCount -p $facCount -R -f $SOLVE_DIR$fileOutput".ans" < $INPUT_DIR$filename > $LOG_DIR$fileOutput".log" ; } 2> $TIME_DIR$fileOutput".time"
                fileOutput=$filenameClean"_"$iterCountFmt"_"$antCountFmt"_"$facCountFmt"_NR_WM_"$runCountFmt
                { time $PROGRAM_NAME_FULL -i $iterCount -n $antCount -p $facCount -M -f $SOLVE_DIR$fileOutput".ans" < $INPUT_DIR$filename > $LOG_DIR$fileOutput".log" ; } 2> $TIME_DIR$fileOutput".time"
                fileOutput=$filenameClean"_"$iterCountFmt"_"$antCountFmt"_"$facCountFmt"_WR_WM_"$runCountFmt
                { time $PROGRAM_NAME_FULL -i $iterCount -n $antCount -p $facCount -R -M -f $SOLVE_DIR$fileOutput".ans" < $INPUT_DIR$filename > $LOG_DIR$fileOutput".log" ; } 2> $TIME_DIR$fileOutput".time"

                done
            done
        done
    done
done
