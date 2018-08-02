#!/bin/bash

cd  crab_projects_HCALissue_v3/
echo " "
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
    crab getoutput $i
    #cd ../..
done;

