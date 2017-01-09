#!/bin/bash

cd crab_projects_Nov9/
echo $(pwd)
#num=101
#num2=0
#num3=1001
key="$1"
#for i in */; 
#do 
echo " "
echo "### $key"; 
cd "$key/results"
echo "Deleting hist_analysis*.root files" 
rm hist_analysis*.root
echo "Deleting newhist*.root files" 
rm newhist*.root
cd ../..
