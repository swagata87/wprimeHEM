from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = ''
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'
config.JobType.outputFiles = ['hist_analysis.root']
config.JobType.inputFiles = ['MC_pileup.root','Data_pileup_normalized.root','Data_pileup_normalized_UP.root','Data_pileup_normalized_DOWN.root', 'k_faktors_ele.root', 'k_faktors_mu.root', 'k_faktors_tau.root','METFilters_cff.py', 'qcdFakeOutput15pt_eta.root']

config.Data.inputDataset = ''
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
#config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'
config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/Final/Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON.txt'
#config.Data.unitsPerJob = 4
config.Data.outLFNDirBase = '/store/user/%s/crab_March3/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'WPrimeToTaus_March3'
config.Site.storageSite = 'T2_DE_RWTH'

if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'crab_projects_March3'

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

##### REMINIAOD #####
#    config.General.requestName = 'Tau_Run2016B'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016B']
#    config.Data.inputDataset = '/Tau/Run2016B-03Feb2017_ver2-v2/MINIAOD'
#    config.Data.unitsPerJob = 25
#    submit(config)

#    config.General.requestName = 'Tau_Run2016C'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016C']
#    config.Data.inputDataset = '/Tau/Run2016C-03Feb2017-v1/MINIAOD'
#    config.Data.unitsPerJob = 25
#    submit(config)

#    config.General.requestName = 'Tau_Run2016D'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016D']
#    config.Data.inputDataset = '/Tau/Run2016D-03Feb2017-v1/MINIAOD'
#    config.Data.unitsPerJob = 25
#    submit(config)

#    config.General.requestName = 'Tau_Run2016E'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016E']
#    config.Data.inputDataset = '/Tau/Run2016E-03Feb2017-v1/MINIAOD'
#    config.Data.unitsPerJob = 25
#    submit(config)

#    config.General.requestName = 'Tau_Run2016F'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016F']
#    config.Data.inputDataset = '/Tau/Run2016F-03Feb2017-v1/MINIAOD'
#    config.Data.unitsPerJob = 25
#    submit(config)

#    config.General.requestName = 'Tau_Run2016G'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016G']
#    config.Data.inputDataset = '/Tau/Run2016G-03Feb2017-v1/MINIAOD'
#    config.Data.unitsPerJob = 25
#    submit(config)

    config.General.requestName = 'Tau_Run2016H_1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016H_1']
    config.Data.inputDataset = '/Tau/Run2016H-03Feb2017_ver2-v1/MINIAOD'
    config.Data.unitsPerJob = 25
    submit(config)

    config.General.requestName = 'Tau_Run2016H_2'
    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016H_2']
    config.Data.inputDataset = '/Tau/Run2016H-03Feb2017_ver3-v1/MINIAOD'
    config.Data.unitsPerJob = 25
    submit(config)


## Data ## ReReco ##

#    config.General.requestName = 'SingleMuon_Run2016B_23Sep2016_v3'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=SingleMuon_Run2016B_23Sep2016_v3']
#    config.Data.inputDataset = '/SingleMuon/Run2016B-23Sep2016-v3/MINIAOD'
#    config.Data.unitsPerJob = 20
#    submit(config)

#    config.General.requestName = 'Tau_Run2016B_23Sep2016_v3'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016B_23Sep2016_v3']
#    config.Data.inputDataset = '/Tau/Run2016B-23Sep2016-v3/MINIAOD'
#    config.Data.unitsPerJob = 25
#    submit(config)

#    config.General.requestName = 'Tau_Run2016C_23Sep2016_v1'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016C_23Sep2016_v1']
#    config.Data.inputDataset = '/Tau/Run2016C-23Sep2016-v1/MINIAOD'
#    config.Data.unitsPerJob = 16
#    submit(config)

#    config.General.requestName = 'Tau_Run2016D_23Sep2016_v1'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016D_23Sep2016_v1']
#    config.Data.inputDataset = '/Tau/Run2016D-23Sep2016-v1/MINIAOD'
#    config.Data.unitsPerJob = 20
#    submit(config)

#    config.General.requestName = 'Tau_Run2016E_23Sep2016_v1'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016E_23Sep2016_v1']
#    config.Data.inputDataset = '/Tau/Run2016E-23Sep2016-v1/MINIAOD'
#    config.Data.unitsPerJob = 20
#    submit(config)

#    config.General.requestName = 'Tau_Run2016F_23Sep2016_v1'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016F_23Sep2016_v1']
#    config.Data.inputDataset = '/Tau/Run2016F-23Sep2016-v1/MINIAOD'
#    config.Data.unitsPerJob = 25
#    submit(config)

#    config.General.requestName = 'Tau_Run2016G_23Sep2016_v1'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016G_23Sep2016_v1']
#    config.Data.inputDataset = '/Tau/Run2016G-23Sep2016-v1/MINIAOD'
#    config.Data.unitsPerJob = 25
#    submit(config)

#    config.General.requestName = ''
#    config.JobType.pyCfgParams = ['sourceFileStringInput=']
#    config.Data.inputDataset = ''
#    config.Data.unitsPerJob = 14
#    submit(config)


##
## Data ## Prompt Reco ##
##

#    config.General.requestName = 'Tau_Run2016B_PromptReco_v2'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016B_PromptReco_v2']
#    config.Data.inputDataset = '/Tau/Run2016B-PromptReco-v2/MINIAOD'
#    config.Data.unitsPerJob = 14
#    submit(config)

#    config.General.requestName = 'Tau_Run2016C_PromptReco_v2'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016C_PromptReco_v2']
#    config.Data.inputDataset = '/Tau/Run2016C-PromptReco-v2/MINIAOD'
#    config.Data.unitsPerJob = 12
#    submit(config)

#    config.General.requestName = 'Tau_Run2016D_PromptReco_v2'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016D_PromptReco_v2']
#    config.Data.inputDataset = '/Tau/Run2016D-PromptReco-v2/MINIAOD'
#    config.Data.unitsPerJob = 12
#    submit(config)

#    config.General.requestName = 'Tau_Run2016E_PromptReco_v2'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016E_PromptReco_v2']
#    config.Data.inputDataset = '/Tau/Run2016E-PromptReco-v2/MINIAOD'
#    config.Data.unitsPerJob = 12
#    submit(config)

#    config.General.requestName = 'Tau_Run2016F_PromptReco_v1'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016F_PromptReco_v1']
#    config.Data.inputDataset = '/Tau/Run2016F-PromptReco-v1/MINIAOD'
#    config.Data.unitsPerJob = 12
#    submit(config)

#    config.General.requestName = 'Tau_Run2016G_PromptReco_v1'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016G_PromptReco_v1']
#    config.Data.inputDataset = '/Tau/Run2016G-PromptReco-v1/MINIAOD'
#    config.Data.unitsPerJob = 12
#    submit(config)

#    config.General.requestName = 'Tau_Run2016H_PromptReco_v3'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016H_PromptReco_v3']
#    config.Data.inputDataset = '/Tau/Run2016H-PromptReco-v3/MINIAOD'
#    config.Data.unitsPerJob = 16
#    submit(config)

#    config.General.requestName = 'Tau_Run2016H_PromptReco_v2'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_Run2016H_PromptReco_v2']
#    config.Data.inputDataset = '/Tau/Run2016H-PromptReco-v2/MINIAOD'
#    config.Data.unitsPerJob = 20
#    submit(config)
