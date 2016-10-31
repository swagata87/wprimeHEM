#!/bin/bash

cd crab_projects_Oct25/
echo $(pwd)
#key="$1"
for i in */; 
do 
    echo " "
    echo " $i "; 
    cd "$i/results"
    echo "Deleting hist_analysis*.root files" 
    rm hist_analysis*.root
    echo "Deleting newhist*.root files" 
    rm newhist*.root
    cd ../..
done