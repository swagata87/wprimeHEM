import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      # '/store/mc/RunIISpring16MiniAODv2/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/70000/7E9A7536-7A1A-E611-9149-001E67A4055F.root'
#        '/store/mc/RunIIFall15MiniAODv1/WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/1AF74AF6-BFA6-E511-96DF-0CC47A1DF7F8.root'
#        '/store/mc/RunIIFall15MiniAODv1/WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/26FC919F-C3A6-E511-9A22-0CC47A4D7674.root'
#        '/store/mc/RunIISpring16MiniAODv2/WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/00000/0A8E0285-A92B-E611-A376-00259081ED0A.root'
       '/store/data/Run2016B/Tau/MINIAOD/PromptReco-v2/000/273/150/00000/64EFFDF2-D719-E611-A0C3-02163E01421D.root'
    )
)

process.demo = cms.EDAnalyzer('MiniAODAnalyzer',
       outputFile = cms.string('analysis.root'), 
       vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
       taus = cms.InputTag("slimmedTaus"),
       muons = cms.InputTag("slimmedMuons"),
       electrons = cms.InputTag("slimmedElectrons"),
       mets = cms.InputTag("slimmedMETs"),
       bits = cms.InputTag("TriggerResults","","HLT"),
       bits_MET = cms.InputTag("TriggerResults","","RECO"),                       
       prescales = cms.InputTag("patTrigger"),
       objects = cms.InputTag("selectedPatTrigger")
)

process.out = cms.OutputModule("PoolOutputModule",
        fileName = cms.untracked.string('analysis.root')
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('hist_analysis.root')
)

process.p = cms.Path(process.demo)
