import FWCore.ParameterSet.Config as cms

import FWCore.ParameterSet.VarParsing as VarParsing

process = cms.Process("Demo")
options = VarParsing.VarParsing('analysis')
options.register ('sourceFileStringInput',
                  'default', # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.string,          # string, int, or float
                  "Name of the sample")
options.parseArguments()

process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag

#  as a rule, find the "auto" global tag in $CMSSW_RELEASE_BASE/src/Configuration/AlCa/python/autoCond.py
#  This auto global tag will look up the "proper" global tag
#  that is typically found in the DAS under the Configs for given dataset
#  (although it can be "overridden" by requirements of a given release)

#80X_mcRun2_asymptotic_2016_TrancheIV_v6
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')     # MC
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_mcRun2_asymptotic_2016_TrancheIV_v6', '')     # MC
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')  # DATA

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.load("WPrimeToTau.MiniAODAnalyzer.METFilters_cff")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

#process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
#    ignoreTotal = cms.untracked.int32(1),
#    moduleMemorySummary = cms.untracked.bool(True),
#)

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)

# define which IDs we want to produce
my_id_modules = [
    'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer16_80X_V1_cff'
    ]
#add them to the VID producer
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1))

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
## Moriond 17 samples ##
'/store/mc/RunIISummer16MiniAODv2/WprimeToTauNu_M-1200_TuneCUETP8M1_13TeV-pythia8-tauola/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/70000/006926C1-1EB7-E611-93A8-ECB1D79E5C40.root'
##
# '/store/mc/RunIISpring16MiniAODv2/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/70000/7E9A7536-7A1A-E611-9149-001E67A4055F.root'
#        '/store/mc/RunIISpring16MiniAODv2/WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/00000/0A8E0285-A92B-E611-A376-00259081ED0A.root'
# '/store/mc/RunIISpring16MiniAODv2/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/00000/046410F1-7736-E611-8F28-A0000420FE80.root',
#        '/store/mc/RunIISpring16MiniAODv2/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/00000/000C4CF4-CC21-E611-9D0A-0025905C54FE.root',
#        '/store/mc/RunIISpring16MiniAODv2/WToTauNu_M-100_TuneCUETP8M1_13TeV-pythia8-tauola/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/70000/309E13C9-B42B-E611-9C97-00259073E51E.root'
#        '/store/mc/RunIISpring16MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/00000/061F5F22-4441-E611-BFAA-A0369F3102B6.root'
#        '/store/mc/RunIISpring16MiniAODv2/WToTauNu_M-200_TuneCUETP8M1_13TeV-pythia8-tauola/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/50000/0A494D33-E62B-E611-B087-848F69FD43A0.root'
#        '/store/mc/RunIISpring16MiniAODv2/WToTauNu_M-500_TuneCUETP8M1_13TeV-pythia8-tauola/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/1E246C8A-A42B-E611-BF7B-C45444922D3C.root'
#        '/store/mc/RunIISpring16MiniAODv2/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/10000/346E7295-1940-E611-BD20-E41D2D08DD20.root',
#        '/store/mc/RunIISpring16MiniAODv2/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/60000/02433DFA-0720-E611-9323-1CB72C1B65D4.root',
#        '/store/mc/RunIISpring16MiniAODv2/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/40000/006F5A7A-7D24-E611-97BB-B083FED43141.root',
#        '/store/mc/RunIISpring16MiniAODv2/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/00000/06A61384-FA1A-E611-8E7E-B083FED3F2E9.root',
#        '/store/mc/RunIISpring16MiniAODv2/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/00000/1EA04C7F-FA1A-E611-A203-1418774124DE.root'
#        '/store/mc/RunIISpring16MiniAODv2/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/70000/008C40ED-811D-E611-95E9-00259029E87C.root'
#        '/store/mc/RunIISpring16MiniAODv2/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/50000/1C2B19A5-471B-E611-916B-008CFA111200.root'
#        '/store/mc/RunIISpring16MiniAODv2/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext3-v2/70000/00287FF4-0E40-E611-8D06-00266CFE78EC.root'
#        '/store/mc/RunIISpring16MiniAODv2/TT_Mtt-700to1000_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/60000/00D49225-7D59-E611-85F6-047D7B416516.root'
#        '/store/mc/RunIISpring16MiniAODv2/TT_Mtt-1000toInf_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext2-v1/20000/02A0D9FA-0A41-E611-8B39-0090FAA57E54.root'
#      '/store/data/Run2016B/Tau/MINIAOD/PromptReco-v2/000/273/150/00000/64EFFDF2-D719-E611-A0C3-02163E01421D.root',
#      '/store/data/Run2016B/Tau/MINIAOD/PromptReco-v2/000/273/158/00000/D464EE02-D919-E611-8D74-02163E013917.root',
#      '/store/data/Run2016B/Tau/MINIAOD/PromptReco-v2/000/273/290/00000/4C630F9E-191A-E611-AEB5-02163E013716.root'
#        '/store/data/Run2016B/Tau/MINIAOD/01Jul2016-v2/20000/02C0A083-734F-E611-A834-549F35AF44AF.root'
#        '/store/data/Run2016E/Tau/MINIAOD/PromptReco-v2/000/276/831/00000/0CFBD536-074D-E611-84B7-02163E011E85.root'
#        '/store/data/Run2016E/SingleMuon/MINIAOD/PromptReco-v2/000/276/831/00000/06AD57AB-5A4D-E611-80F2-02163E014448.root'
    )
)

process.demo = cms.EDAnalyzer('MiniAODAnalyzer',
       doFakeHist_ = cms.bool(True),
       doTrees_ = cms.bool(True),
       useReweighting = cms.bool(True),
       RunOnData_ = cms.bool(False),
#       RunOnData_ = cms.bool(True),
### generatorName required only for madgraph and powheg. For other cases one can just write "default"
#       generatorName = cms.string("madgraphMLM"),
       generatorName = cms.string("default"),
#       generatorName = cms.string("powheg"),
### correct pdfName required only for madgraph, for other cases one can just write "default"
#       pdfName = cms.string("NNPDF30_lo_as_0130.LHgrid"),   # madgraphMLM
       pdfName = cms.string("default"),   # powheg and others
       debugLevel_ = cms.int32(0),
       vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
       taus = cms.InputTag("slimmedTaus"),
       muons = cms.InputTag("slimmedMuons"),
       electrons = cms.InputTag("slimmedElectrons"),
       jets = cms.InputTag("slimmedJets"),
       mets = cms.InputTag("slimmedMETs"),
       bits = cms.InputTag("TriggerResults","","HLT"),
#       bits_MET = cms.InputTag("TriggerResults","","RECO"),  ##for data
       bits_MET = cms.InputTag("TriggerResults","","PAT"),  ##for MC
       prescales = cms.InputTag("patTrigger"),
       packed = cms.InputTag("packedGenParticles"),
       pruned = cms.InputTag("prunedGenParticles"),
       objects = cms.InputTag("selectedPatTrigger"),
       genEventInfoProductMiniAOD = cms.InputTag('generator'),
       pileupCollection = cms.InputTag("slimmedAddPileupInfo"),
       PileupMCFile = cms.string("MC_pileup.root"),
       PileupDataFile = cms.string("Data_pileup_normalized.root"),
       PileupDataFile_UP = cms.string("Data_pileup_normalized_UP.root"),
       PileupDataFile_DOWN = cms.string("Data_pileup_normalized_DOWN.root"),
       KFactorE = cms.string("k_faktors_ele.root"),
       KFactorMu = cms.string("k_faktors_mu.root"),
       KFactorTau = cms.string("k_faktors_tau.root"),
       QCDWeightTau = cms.string("qcdFakeOutput15pt_eta.root"),
       #sourceFileString = cms.string(process.source_().dumpConfig().split('\n')[2].split("/")[4]),
       sourceFileString = cms.string(options.sourceFileStringInput),                       
       BadChargedCandidateFilter = cms.InputTag("BadChargedCandidateFilter"),
       BadPFMuonFilter = cms.InputTag("BadPFMuonFilter"),
       eleIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-loose"),
       LHEEventTag = cms.InputTag("externalLHEProducer","","LHE"),
#       LHEEventTag = cms.InputTag("source","","LHEFile")
       tag = cms.untracked.string("initrwgt"),
       doPDFuncertainty_ = cms.bool(True),

)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('hist_analysis.root'),
 #                                  closeFileFast = cms.untracked.bool(True)
)

#process.run = cms.Path(process.BadPFMuonFilter *process.BadChargedCandidateFilter)

process.p = cms.Path(process.METFiltersSequence*process.egmGsfElectronIDSequence*process.demo)
#process.demo)
#process.p = cms.Path(process.demo)
