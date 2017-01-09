#!/bin/bash

cd crab_projects_SSMsigOnly_Jan7/
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
    crab status $i
    #cd ../..
done;

