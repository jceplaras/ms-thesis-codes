#!/bin/zsh

INPUTDIR=$1

echo $INPUTDIR
for file in `ls -A1 $INPUTDIR*.ans | xargs -n1 basename`
do
    fileclean=${file/".ans"/""}
    strout=${fileclean//"_"/","}
    ans=`awk '{ print $NF }' < $INPUTDIR$fileclean".ans"`
    time=`cat $INPUTDIR$fileclean."time"`
    time=${time%% user*}
    time=`echo $time | awk '{ print $NF }'`
    time=${time/"s"/""}
    strout=$strout","$ans","$time
    echo $strout
done    
