from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = ''
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'
#config.JobType.outputFiles = ['analysis.root','hist_analysis.root']
config.JobType.outputFiles = ['hist_analysis.root']
config.JobType.inputFiles = ['configFiles/MC_pileup.root','configFiles/Data_pileup_normalized.root','configFiles/Data_pileup_normalized_UP.root','configFiles/Data_pileup_normalized_DOWN.root', 'configFiles/k_faktors_ele.root', 'configFiles/k_faktors_mu.root', 'configFiles/k_faktors_tau.root']

config.Data.inputDataset = ''
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
#config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/%s/crab_Wprime_Sept19/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'WPrimeToTaus_Sept19'
config.Site.storageSite = 'T2_DE_RWTH'

if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'crab_projects'

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException as hte:
            print "Failed submitting task: %s" % (hte.headers)
        except ClientException as cle:
            print "Failed submitting task: %s" % (cle)

    #############################################################################################
    ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
    #############################################################################################

## Background ##
##
## ZJets
##
#    config.General.requestName = 'ZJetsToNuNu_HT-100To200_13TeV-madgraph'
#    config.Data.inputDataset = '/ZJetsToNuNu_HT-100To200_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 5
#    submit(config)

#    config.General.requestName = 'ZJetsToNuNu_HT-200To400_13TeV-madgraph'
#    config.Data.inputDataset = '/ZJetsToNuNu_HT-200To400_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 5
#    submit(config)

#    config.General.requestName = 'ZJetsToNuNu_HT-400To600_13TeV-madgraph'
#    config.Data.inputDataset = '/ZJetsToNuNu_HT-400To600_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 5
#    submit(config)

    config.General.requestName = 'ZJetsToNuNu_HT-600To800_13TeV-madgraph'
    config.Data.inputDataset = '/ZJetsToNuNu_HT-600To800_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

    config.General.requestName = 'ZJetsToNuNu_HT-800To1200_13TeV-madgraph'
    config.Data.inputDataset = '/ZJetsToNuNu_HT-800To1200_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v3/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

    config.General.requestName = 'ZJetsToNuNu_HT-1200To2500_13TeV-madgraph'
    config.Data.inputDataset = '/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

    config.General.requestName = 'ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph'
    config.Data.inputDataset = '/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

##
## QCD
##
    config.General.requestName = 'QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.Data.inputDataset = '/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

    config.General.requestName = 'QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.Data.inputDataset = '/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

    config.General.requestName = 'QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.Data.inputDataset = '/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

    config.General.requestName = 'QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.Data.inputDataset = '/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

    config.General.requestName = 'QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.Data.inputDataset = '/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

    config.General.requestName = 'QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.Data.inputDataset = '/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

    config.General.requestName = 'QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.Data.inputDataset = '/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

##
## Wjets binned sample ##
##
    config.General.requestName = 'WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.Data.inputDataset = '/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

    config.General.requestName = 'WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.Data.inputDataset = '/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

    config.General.requestName = 'WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.Data.inputDataset = '/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

    config.General.requestName = 'WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.Data.inputDataset = '/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

    config.General.requestName = 'WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.Data.inputDataset = '/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

    config.General.requestName = 'WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.Data.inputDataset = '/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

    config.General.requestName = 'WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.Data.inputDataset = '/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

##
## WJets flat sample ##
##
#    config.General.requestName = 'WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
#    config.Data.inputDataset = '/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 5
#    submit(config)

#    config.General.requestName = 'DYJetsToLL_M-5to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
#    config.Data.inputDataset = '/DYJetsToLL_M-5to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 5
#    submit(config)

    config.General.requestName = 'DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

##
## aMC@NLO
##

#    config.General.requestName = 'DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8'
#    config.Data.inputDataset = '/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 5
    #config.Data.totalUnits = 8
#    submit(config)

#    config.General.requestName = 'DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8'
#    config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 5
    #config.Data.totalUnits = 8
#    submit(config)

#    config.General.requestName = 'WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8'
#    config.Data.inputDataset = '/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 5
    #config.Data.totalUnits = 8
#    submit(config)
