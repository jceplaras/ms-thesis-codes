#!/bin/sh

INPUT_FOLDER="./../Input/Graph/Random/"
OUTPUT_FOLDER="./../Output/Heuristics/"

PROGRAM_FOLDER="./../Bin/Heuristics/"

date
for n in `seq 1 5`
do
for flags in "" "-R" "-M" "-R -M"
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
    for ants in 100
    do
        for iter in 10000
        do
            for p in `seq 3 6`
            do
                #AntSystem
                for size in `seq 10 5 100`
                do
                    for run in `seq 1 5`
                    do
                        sizefmt=$(printf "%03d" $size)
                        nfmt=$(printf "%02d" $n)
                        iterfmt=$(printf "%05d" $iter)
                        antfmt=$(printf "%03d" $ants)

                        input=$INPUT_FOLDER"Random_"$sizefmt"_"$nfmt".graph"
                        
                        PROGRAM_NAME="AntSystem"
                        PROGRAM_FULL=$PROGRAM_FOLDER$PROGRAM_NAME".run"
                        PROGRAM_OUTPUT_FOLDER=$OUTPUT_FOLDER$PROGRAM_NAME"/"
                        mkdir -p $PROGRAM_OUTPUT_FOLDER
                        fileout=$PROGRAM_OUTPUT_FOLDER"Random_"$sizefmt"_"$nfmt"_"$flagsfmt"_"$antfmt"_"$iterfmt"_"$p"_"$run
                        if [ -f "$fileout"".ans" ]; then
                            echo "Skipping $fileout"
                        else
                            { time $PROGRAM_FULL $flags -i $iter -n $ants -p $p < $input > $fileout".ans" ; } 2> $fileout".time"
                            echo $fileout 
                            date
                        fi
                    done
                done
                #Elitist
                for size in `seq 10 5 100`
                do
                    for run in `seq 1 5`
                    do
                        sizefmt=$(printf "%03d" $size)
                        nfmt=$(printf "%02d" $n)
                        iterfmt=$(printf "%05d" $iter)
                        antfmt=$(printf "%03d" $ants)

                        input=$INPUT_FOLDER"Random_"$sizefmt"_"$nfmt".graph"
                        
                        PROGRAM_NAME="ElitistAntSystem"
                        PROGRAM_FULL=$PROGRAM_FOLDER$PROGRAM_NAME".run"
                        PROGRAM_OUTPUT_FOLDER=$OUTPUT_FOLDER$PROGRAM_NAME"/"
                        mkdir -p $PROGRAM_OUTPUT_FOLDER

                        fileout=$PROGRAM_OUTPUT_FOLDER"Random_"$sizefmt"_"$nfmt"_"$flagsfmt"_"$antfmt"_"$iterfmt"_"$p"_"$run
                        if [ -f "$fileout"".ans" ]; then
                            echo "Skipping $fileout"
                        else

                        { time $PROGRAM_FULL $flags -E 4 -i $iter -n $ants -p $p  < $input > $fileout".ans" ; } 2> $fileout".time"
                        echo $fileout 
                        date
                        fi
                    done
                done

                #BestWorstSystem
                for size in `seq 10 5 100`
                do
                    for run in `seq 1 5`
                    do
                        sizefmt=$(printf "%03d" $size)
                        nfmt=$(printf "%02d" $n)
                        iterfmt=$(printf "%05d" $iter)
                        antfmt=$(printf "%03d" $ants)

                        input=$INPUT_FOLDER"Random_"$sizefmt"_"$nfmt".graph"
                        
                        PROGRAM_NAME="BestWorstAntSystem"
                        PROGRAM_FULL=$PROGRAM_FOLDER$PROGRAM_NAME".run"
                        PROGRAM_OUTPUT_FOLDER=$OUTPUT_FOLDER$PROGRAM_NAME"/"
                        mkdir -p $PROGRAM_OUTPUT_FOLDER

                        fileout=$PROGRAM_OUTPUT_FOLDER"Random_"$sizefmt"_"$nfmt"_"$flagsfmt"_"$antfmt"_"$iterfmt"_"$p"_"$run
                        if [ -f "$fileout"".ans" ]; then
                            echo "Skipping $fileout"
                        else

                        { time $PROGRAM_FULL $flags -i $iter -n $ants -p $p  < $input > $fileout".ans" ; } 2> $fileout".time"
                        echo $fileout 
                        date
                        fi
                    done
                done
                #MinMaxSystem
                for size in `seq 10 5 100`
                do
                    for run in `seq 1 5`
                    do
                        sizefmt=$(printf "%03d" $size)
                        nfmt=$(printf "%02d" $n)
                        iterfmt=$(printf "%05d" $iter)
                        antfmt=$(printf "%03d" $ants)

                        input=$INPUT_FOLDER"Random_"$sizefmt"_"$nfmt".graph"
                        
                        PROGRAM_NAME="MinMaxAntSystem"
                        PROGRAM_FULL=$PROGRAM_FOLDER$PROGRAM_NAME".run"
                        PROGRAM_OUTPUT_FOLDER=$OUTPUT_FOLDER$PROGRAM_NAME"/"
                        mkdir -p $PROGRAM_OUTPUT_FOLDER

                        fileout=$PROGRAM_OUTPUT_FOLDER"Random_"$sizefmt"_"$nfmt"_"$flagsfmt"_"$antfmt"_"$iterfmt"_"$p"_"$run
                        if [ -f "$fileout"".ans" ]; then
                            echo "Skipping $fileout"
                        else

                        { time $PROGRAM_FULL $flags -i $iter -n $ants -p $p  < $input > $fileout".ans" ; } 2> $fileout".time"
                        echo $fileout 
                        date
                        fi
                    done
                done
                #RankBased
                for size in `seq 10 5 100`
                do
                    for run in `seq 1 5`
                    do
                        sizefmt=$(printf "%03d" $size)
                        nfmt=$(printf "%02d" $n)
                        iterfmt=$(printf "%05d" $iter)
                        antfmt=$(printf "%03d" $ants)

                        input=$INPUT_FOLDER"Random_"$sizefmt"_"$nfmt".graph"
                        
                        PROGRAM_NAME="RankBasedAntSystem"
                        PROGRAM_FULL=$PROGRAM_FOLDER$PROGRAM_NAME".run"
                        PROGRAM_OUTPUT_FOLDER=$OUTPUT_FOLDER$PROGRAM_NAME"/"
                        mkdir -p $PROGRAM_OUTPUT_FOLDER

                        fileout=$PROGRAM_OUTPUT_FOLDER"Random_"$sizefmt"_"$nfmt"_"$flagsfmt"_"$antfmt"_"$iterfmt"_"$p"_"$run
                        if [ -f "$fileout"".ans" ]; then
                            echo "Skipping $fileout"
                        else

                        { time $PROGRAM_FULL $flags -c 5 -E 4 -i $iter -n $ants -p $p  < $input > $fileout".ans" ; } 2> $fileout".time"
                        echo $fileout 
                        date
                        fi
                    done
                done
                #AntColonySystem
                for size in `seq 10 5 100`
                do
                    for run in `seq 1 5`
                    do
                        sizefmt=$(printf "%03d" $size)
                        nfmt=$(printf "%02d" $n)
                        iterfmt=$(printf "%05d" $iter)
                        antfmt=$(printf "%03d" $ants)

                        input=$INPUT_FOLDER"Random_"$sizefmt"_"$nfmt".graph"
                        
                        PROGRAM_NAME="AntColonySystem"
                        PROGRAM_FULL=$PROGRAM_FOLDER$PROGRAM_NAME".run"
                        PROGRAM_OUTPUT_FOLDER=$OUTPUT_FOLDER$PROGRAM_NAME"/"
                        mkdir -p $PROGRAM_OUTPUT_FOLDER

                        fileout=$PROGRAM_OUTPUT_FOLDER"Random_"$sizefmt"_"$nfmt"_"$flagsfmt"_"$antfmt"_"$iterfmt"_"$p"_"$run
                        if [ -f "$fileout"".ans" ]; then
                            echo "Skipping $fileout"
                        else

                        { time $PROGRAM_FULL $flags -i $iter -n $ants -p $p  < $input > $fileout".ans" ; } 2> $fileout".time"
                        echo $fileout 
                        date
                        fi
                    done
                done
            done
        done
    done
done
done
