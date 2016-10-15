#!/bin/bash

cd crab_projects/
echo $(pwd)
#num=101
#num2=0
#num3=1001

for i in */; 
do 
    echo " "
    echo "### $i"; 
    cd "$i/results"
    #echo "------" $(pwd)
    n=$(ls -1 | wc -l)
    echo $n " files"

    if [ $n -le 100 ]; then 
	hadd -f hist.root hist_analysis_*.root

    elif [ $n -gt 100 ]; then 
	#let "a=n/100"
	#let "b=n%100"
	#echo $a, $b
        #if [ $b -ne "$num2" ]; then
	#    let a=a+1
	#    echo "do haddin " $a "iterations"
	#fi    
	hadd -f newhist1.root   hist_analysis_1.root    hist_analysis_10*.root 
 	hadd -f newhist2.root   hist_analysis_11*.root
	hadd -f newhist3.root   hist_analysis_12*.root
	hadd -f newhist4.root   hist_analysis_13*.root
	hadd -f newhist5.root   hist_analysis_14*.root
	hadd -f newhist6.root   hist_analysis_15*.root
	hadd -f newhist7.root   hist_analysis_16*.root
	hadd -f newhist8.root   hist_analysis_17*.root
	hadd -f newhist9.root   hist_analysis_18*.root
	hadd -f newhist10.root  hist_analysis_19*.root

	hadd -f newhist11.root   hist_analysis_2.root    hist_analysis_20*.root 
 	hadd -f newhist12.root   hist_analysis_21*.root
	hadd -f newhist13.root   hist_analysis_22*.root
	hadd -f newhist14.root   hist_analysis_23*.root
	hadd -f newhist15.root   hist_analysis_24*.root
	hadd -f newhist16.root   hist_analysis_25*.root
	hadd -f newhist17.root   hist_analysis_26*.root
	hadd -f newhist18.root   hist_analysis_27*.root
	hadd -f newhist19.root   hist_analysis_28*.root
	hadd -f newhist20.root   hist_analysis_29*.root

	hadd -f newhist21.root   hist_analysis_3.root    hist_analysis_30*.root 
 	hadd -f newhist22.root   hist_analysis_31*.root
	hadd -f newhist23.root   hist_analysis_32*.root
	hadd -f newhist24.root   hist_analysis_33*.root
	hadd -f newhist25.root   hist_analysis_34*.root
	hadd -f newhist26.root   hist_analysis_35*.root
	hadd -f newhist27.root   hist_analysis_36*.root
	hadd -f newhist28.root   hist_analysis_37*.root
	hadd -f newhist29.root   hist_analysis_38*.root
	hadd -f newhist30.root   hist_analysis_39*.root

	hadd -f newhist31.root   hist_analysis_4*.root
	hadd -f newhist32.root   hist_analysis_5*.root
	hadd -f newhist33.root   hist_analysis_6*.root
	hadd -f newhist34.root   hist_analysis_7*.root
	hadd -f newhist35.root   hist_analysis_8*.root
	hadd -f newhist36.root   hist_analysis_9*.root
	
	hadd -f hist.root  newhist*.root
	
    fi	
    cd ../..
done;

