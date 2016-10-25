from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = ''
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'
config.JobType.outputFiles = ['hist_analysis.root']
config.JobType.inputFiles = ['MC_pileup.root','Data_pileup_normalized.root','Data_pileup_normalized_UP.root','Data_pileup_normalized_DOWN.root', 'k_faktors_ele.root', 'k_faktors_mu.root', 'k_faktors_tau.root','METFilters_cff.py', 'qcdFakeOutput15pt_eta.root']
#config.JobType.maxMemoryMB = 3000
#config.JobType.numCores = 2

config.Data.inputDataset = ''
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
#config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/%s/crab_Wprime_Oct25/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'WPrimeToTaus_Oct25'
config.Site.storageSite = 'T2_DE_RWTH'

if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'crab_projects_Oct25'

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

## Signal ##

#    config.General.requestName = 'WprimeToTauNu_M-400_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M-400_TuneCUETP8M1_13TeV-pythia8-tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-400_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M-2000_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M-2000_TuneCUETP8M1_13TeV-pythia8-tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-2000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M-3000_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M-3000_TuneCUETP8M1_13TeV-pythia8-tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-3000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M-4000_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.Data.inputDataset = '/WprimeToTauNu_M-4000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 3
    #config.Data.totalUnits = 4
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M-5000_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.Data.inputDataset = '/WprimeToTauNu_M-5000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM'
#    config.Data.unitsPerJob = 3
#    submit(config)

## Background ##
##
## WW
##
#    config.General.requestName = 'WW_TuneCUETP8M1_13TeV-pythia8'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WW_TuneCUETP8M1_13TeV-pythia8']
#    config.Data.inputDataset = '/WW_TuneCUETP8M1_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

##
## WZ
##
#    config.General.requestName = 'WZ_TuneCUETP8M1_13TeV-pythia8'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WZ_TuneCUETP8M1_13TeV-pythia8']
#    config.Data.inputDataset = '/WZ_TuneCUETP8M1_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

##
## ZZ
##
#    config.General.requestName = 'ZZ_TuneCUETP8M1_13TeV-pythia8'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=ZZ_TuneCUETP8M1_13TeV-pythia8']
#    config.Data.inputDataset = '/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

##
## ST_t-channel_antitop_4f_leptonDecays
##
    config.General.requestName = 'ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1']
    config.Data.inputDataset = '/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

##
## ST_t-channel_top_4f_leptonDecays
##
    config.General.requestName = 'ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1']
    config.Data.inputDataset = '/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

##
## ST_tW_antitop_5f_inclusiveDecays
##
    config.General.requestName = 'ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1']
    config.Data.inputDataset = '/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

##
## ST_tW_top_5f_inclusiveDecays
##
    config.General.requestName = 'ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1']
    config.Data.inputDataset = '/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

##
## TT
##
    config.General.requestName = 'TT_TuneCUETP8M1_13TeV-powheg-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=TT_TuneCUETP8M1_13TeV-powheg-pythia8']
    config.Data.inputDataset = '/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext3-v2/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

###
## W mass binned sample ##
###

#    config.General.requestName = 'WToTauNu_M-100_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WToTauNu_M-100_TuneCUETP8M1_13TeV-pythia8-tauola']
#    config.Data.inputDataset = '/WToTauNu_M-100_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WToTauNu_M-200_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WToTauNu_M-200_TuneCUETP8M1_13TeV-pythia8-tauola']
#    config.Data.inputDataset = '/WToTauNu_M-200_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WToTauNu_M-500_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WToTauNu_M-500_TuneCUETP8M1_13TeV-pythia8-tauola']
#    config.Data.inputDataset = '/WToTauNu_M-500_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola']
#    config.Data.inputDataset = '/WToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WToTauNu_M-2000_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WToTauNu_M-2000_TuneCUETP8M1_13TeV-pythia8-tauola']
#    config.Data.inputDataset = '/WToTauNu_M-2000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WToTauNu_M-3000_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WToTauNu_M-3000_TuneCUETP8M1_13TeV-pythia8-tauola']
#    config.Data.inputDataset = '/WToTauNu_M-3000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WToTauNu_M-4000_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WToTauNu_M-4000_TuneCUETP8M1_13TeV-pythia8-tauola']
#    config.Data.inputDataset = '/WToTauNu_M-4000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WToTauNu_M-5000_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WToTauNu_M-5000_TuneCUETP8M1_13TeV-pythia8-tauola']
#    config.Data.inputDataset = '/WToTauNu_M-5000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WToTauNu_M-6000_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WToTauNu_M-6000_TuneCUETP8M1_13TeV-pythia8-tauola']
#    config.Data.inputDataset = '/WToTauNu_M-6000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

