# WPrimeToTau

--------------------------------------------
For Bad Charged Hadron and Bad Muon Filters
--------------------------------------------
cmsrel CMSSW_8_0_11

cd CMSSW_8_0_11/src/

cmsenv

git cms-init

git cms-merge-topic -u cms-met:CMSSW_8_0_X-METFilterUpdate



Go to CMSSW_8_X_Y/src/ and do 'cmsenv' and then get the analysis package from github.

To get the package :
git clone https://github.com/swagata87/WPrimeToTau

The main analyzer code is :
WPrimeToTau/MiniAODAnalyzer/plugins/MiniAODAnalyzer.cc

If you make changes here, you need to do : 'scram b' from WPrimeToTau/MiniAODAnalyzer to compile the code.

The main config file is :
WPrimeToTau/MiniAODAnalyzer/python/ConfFile_cfg.py

To run the package, go to WPrimeToTau/MiniAODAnalyzer/python/ and do :

cmsRun ConfFile_cfg.py

####
Some notes about ConfFile_cfg.py
####
- If you decide to calculate pdf uncertainty, then give sensible inputs for generator name and pdf name 

- Depending on whether you are running on data or on MC, change this line -> RunOnData_ = cms.bool(True),

- You will need to run locally to check if things are working fine or not. For that, change the filenames accordingly. The filenames can be found in DAS or by using das_client.py

- For data : bits_MET = cms.InputTag("TriggerResults","","RECO"),
and for MC : bits_MET = cms.InputTag("TriggerResults","","PAT"),.  I expect that this will change in future.

The code takes pile-up distributions of data and MC as inputs. The distributions are already made and saved as root files. You might need to re-make them in future. PU distribution for MC can be made using this file ->

WPrimeToTau/MiniAODAnalyzer/python/MakePileUpHistMC.C 

To make PU distribution for data :

pileupCalc.py -i MyAnalysisJSON.txt --inputLumiJSON pileup_latest.txt  --calcMode true --minBiasXsec 69200 --maxPileupBin 50 --numPileupBins 50  MyDataPileupHistogram.root

Before running it, check if any updated/appropriate value of minBiasXsec, maxPileupBin, numPileupBins are available. 
pileup_latest.txt for 2016 run-period can be found at /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/

Analysis JSON is the one you will later use for crab jobs and can be taken from here ->
https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/

Once you make the data PU distribution, you can normalize it using this script ->
WPrimeToTau/MiniAODAnalyzer/python/NormalizeDataPUHist.C (check the path and filename before running).

twiki for PU reweighting : https://twiki.cern.ch/twiki/bin/view/CMS/PileupJSONFileforData#Pileup_JSON_Files_For_Run_II

Once you have compiled and tested your code locally, you will need to submit crab jobs to run on data and MC. 

Crab config file for MC -> crabConfig_MC_madgraphMLM.py OR crabConfig_MC_powhegAndOthers.py

Crab config file for data -> crabConfig_data.py

Modify the dataset names if you want to run on different datasets.

To submit jobs->
- source /cvmfs/cms.cern.ch/crab3/crab.sh
- Invoke your grid proxy and enter your grid-password
- python crabConfig_*.py

cd crab_projects/ 

Check if jobs are finished : crab status DIRNAME

If jobs are finished, retrieve them : crab getoutput DIRNAME

The files will be retrieved in -> crab_projects/DIRNAME/results/

Rootfiles containing Tree-> analysis_*.root

Rootfiles containing Histograms-> hist_analysis_*.root

You need to do 'hadd' to merge rootfiles. A script would be handy. 
Example :  WPrimeToTau/MiniAODAnalyzer/python/dohadd.sh for merging histogram root files (Can be improved)

####
How much data you processed?
####
- One can do 'crab report DIRNAME' for data and this will give processedLumis.json inside 'results/' folder. 
- export PATH=$HOME/.local/bin:/afs/cern.ch/cms/lumi/brilconda-1.0.3/bin:$PATH  
- brilcalc  lumi  -b "STABLE BEAMS" --normtag=/afs/cern.ch/user/l/lumipro/public/normtag_file/normtag_DATACERT.json -i processedLumis.json -u /fb
- The lumi will be printed


For plotting, any plotter script can be used. This is upto user's taste. 

Example plotter for M_T distribution : WPrimeToTau/MiniAODAnalyzer/test/Plot_mT_Stage1.C 




