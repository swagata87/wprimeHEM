#!/bin/bash

cd crab_projects/
echo $(pwd)

for i in */; 
do 
    echo "### $i"; 
    cd "$i/results"
    echo "------" $(pwd)
    hadd -f hist.root hist_analysis_*.root
    cd ../..
done;

