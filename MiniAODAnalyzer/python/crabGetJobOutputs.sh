#!/bin/bash

cd crab_projects/
echo $(pwd)

for i in */; 
do 
    echo " "
    echo " "
    echo " "
    echo "%%%%%%%%%%%%%%%%%%%"
    echo " "
    echo " "
    echo " "
    echo "### $i"; 
    #cd "$i/results"
    #echo "------" $(pwd)
    crab getoutput $i
    #cd ../..
done;

