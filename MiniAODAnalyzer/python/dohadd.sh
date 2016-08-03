#!/bin/bash

echo $(pwd)

cd crab_projects/crab_WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/
echo $(pwd)
#rm hist.root
hadd -f hist.root hist_analysis_*.root
cd ../../../


cd crab_projects/crab_WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/
echo $(pwd)
#rm hist.root
hadd -f hist.root hist_analysis_*.root
cd ../../../
echo $(pwd)

cd crab_projects/crab_WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/
echo $(pwd)
#rm hist.root
hadd -f hist.root hist_analysis_*.root
cd ../../../

cd crab_projects/crab_WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/
echo $(pwd)
#rm hist.root
hadd -f hist.root hist_analysis_*.root
cd ../../../

cd crab_projects/crab_WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/results/
echo $(pwd)
#rm hist.root
hadd -f hist.root hist_analysis_*.root
cd ../../../

cd crab_projects/crab_WW_TuneCUETP8M1_13TeV-pythia8/results/
echo $(pwd)
#rm hist.root
hadd -f hist.root hist_analysis_*.root
cd ../../../

cd crab_projects/crab_WZ_TuneCUETP8M1_13TeV-pythia8/results/
echo $(pwd)
#rm hist.root
hadd -f hist.root hist_analysis_*.root
cd ../../../

cd crab_projects/crab_ZJetsToNuNu_HT-100To200_13TeV-madgraph/results/
echo $(pwd)
#rm hist.root
hadd -f hist.root hist_analysis_*.root
cd ../../../

cd crab_projects/crab_ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/results/
echo $(pwd)
#rm hist.root
hadd -f hist.root hist_analysis_*.root
cd ../../../

cd crab_projects/crab_ZJetsToNuNu_HT-200To400_13TeV-madgraph/results/
echo $(pwd)
#rm hist.root
hadd -f hist.root hist_analysis_*.root
cd ../../../

cd crab_projects/crab_ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph/results/
echo $(pwd)
#rm hist.root
hadd -f hist.root hist_analysis_*.root
cd ../../../

cd crab_projects/crab_ZJetsToNuNu_HT-400To600_13TeV-madgraph/results/
echo $(pwd)
#rm hist.root
hadd -f hist.root hist_analysis_*.root
cd ../../../

cd crab_projects/crab_ZJetsToNuNu_HT-600To800_13TeV-madgraph/results/
echo $(pwd)
#rm hist.root
hadd -f hist.root hist_analysis_*.root
cd ../../../

cd crab_projects/crab_ZJetsToNuNu_HT-800To1200_13TeV-madgraph/results/
echo $(pwd)
#rm hist.root
hadd -f hist.root hist_analysis_*.root
cd ../../../

cd crab_projects/crab_ZZ_TuneCUETP8M1_13TeV-pythia8/results/
echo $(pwd)
#rm hist.root
hadd -f hist.root hist_analysis_*.root
cd ../../../

