from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = ''
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'
config.JobType.outputFiles = ['analysis.root','hist_analysis.root']
config.JobType.inputFiles = ['MC_pileup.root','Data_pileup_normalized.root']

config.Data.inputDataset = ''
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/Cert_271036-276811_13TeV_PromptReco_Collisions16_JSON_NoL1T.txt'
#config.Data.unitsPerJob = 4
config.Data.outLFNDirBase = '/store/user/%s/crab_Wprime2/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'WPrimeToTaus'
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

## Data ##
#    config.General.requestName = 'Tau_Run2016B_PromptReco_v1'
#    config.Data.inputDataset = '/Tau/Run2016B-PromptReco-v1/MINIAOD'
#    config.Data.unitsPerJob = 15
    #config.Data.totalUnits = 4
#    submit(config)

#    config.General.requestName = 'Tau_Run2016B_PromptReco_v2'
#    config.Data.inputDataset = '/Tau/Run2016B-PromptReco-v2/MINIAOD'
#    config.Data.unitsPerJob = 15
    #config.Data.totalUnits = 4
#    submit(config)

#    config.General.requestName = 'Tau_Run2016C_PromptReco_v2'
#    config.Data.inputDataset = '/Tau/Run2016C-PromptReco-v2/MINIAOD'
#    config.Data.unitsPerJob = 15
    #config.Data.totalUnits = 4
#    submit(config)

    config.General.requestName = 'Tau_Run2016D_PromptReco_v2'
    config.Data.inputDataset = '/Tau/Run2016D-PromptReco-v2/MINIAOD'
    config.Data.unitsPerJob = 14
    #config.Data.totalUnits = 4
    submit(config)

#    config.General.requestName = 'Tau_Run2016B-01Jul2016-v2'
#    config.Data.inputDataset = '/Tau/Run2016B-01Jul2016-v2/MINIAOD'
#    config.Data.unitsPerJob = 12
    #config.Data.totalUnits = 4
#    submit(config)

#    config.General.requestName = 'Tau_Run2016E_PromptReco_v2'
#    config.Data.inputDataset = '/Tau/Run2016E-PromptReco-v2/MINIAOD'
#    config.Data.unitsPerJob = 15
    #config.Data.totalUnits = 4
#    submit(config)


