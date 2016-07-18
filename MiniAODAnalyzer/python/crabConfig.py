from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = ''
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'
config.JobType.outputFiles = ['analysis.root','hist_analysis.root']

config.Data.inputDataset = ''
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
#config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
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

    config.General.requestName = 'WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola'
    config.Data.inputDataset = '/WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    #config.Data.totalUnits = 4
    submit(config)

    config.General.requestName = 'WprimeToTauNu_M-2000_TuneCUETP8M1_13TeV-pythia8-tauola'
    config.Data.inputDataset = '/WprimeToTauNu_M-2000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    #config.Data.totalUnits = 8
    submit(config)

    config.General.requestName = 'WprimeToTauNu_M-3000_TuneCUETP8M1_13TeV-pythia8-tauola'
    config.Data.inputDataset = '/WprimeToTauNu_M-3000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    #config.Data.totalUnits = 8
    submit(config)

    config.General.requestName = 'WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8'
    config.Data.inputDataset = '/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    #config.Data.totalUnits = 8
    submit(config)

    config.General.requestName = 'TT_TuneCUETP8M1_13TeV-powheg-pythia8'
    config.Data.inputDataset = '/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext3-v2/MINIAODSIM'
    config.Data.unitsPerJob = 5
    #config.Data.totalUnits = 8
    submit(config)

    config.General.requestName = 'DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8'
    config.Data.inputDataset = '/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    #config.Data.totalUnits = 8
    submit(config)

    config.General.requestName = 'DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8'
    config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    #config.Data.totalUnits = 8
    submit(config)

