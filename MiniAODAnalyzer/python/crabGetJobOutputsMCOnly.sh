#!/bin/bash

cd crab_projects_SSMsigOnly_Jan7/
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
	echo "Data... Skip !"
	continue
    fi
    crab getoutput --wait=100  $i
done;

