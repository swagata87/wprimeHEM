#!/bin/bash

cd crab_projects_Oct31/
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

    if [[ $i == *"crab_Tau_Run2016"* ]]; then
	echo "Data.. Get Output "
	crab getoutput $i
    fi

done;

