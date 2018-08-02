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
#config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/Final/Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON.txt'
#config.Data.unitsPerJob = 4
config.Data.outLFNDirBase = '/store/user/%s/crab_HCALissue_v3/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'HCALissue_v3'
config.Site.storageSite = 'T2_DE_RWTH'

if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'crab_projects_HCALissue_v3'

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

#    config.General.requestName = 'SingleMuonHEmiss'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=SingleMuon']
#    config.Data.inputDataset = '/SingleMuon/CMSSW_10_1_7-101X_dataRun2_Prompt_HEmiss_v1_RelVal_sigMu2018B-v1/MINIAOD'
#    config.Data.unitsPerJob = 22
#    submit(config)

    config.General.requestName = 'SingleMuonPrompt'
    config.JobType.pyCfgParams = ['sourceFileStringInput=SingleMuon2']
    config.Data.inputDataset = '/SingleMuon/CMSSW_10_1_7-101X_dataRun2_Prompt_v11_RelVal_sigMu2018B-v1/MINIAOD'
    config.Data.unitsPerJob = 22
    submit(config)

