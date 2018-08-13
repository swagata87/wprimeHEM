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

process.GlobalTag = GlobalTag(process.GlobalTag, '101X_dataRun2_Prompt_HEmiss_v1', '') 
####process.GlobalTag = GlobalTag(process.GlobalTag, '101X_dataRun2_Prompt_v11', '') 

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
#process.load("WPrimeToTau.MiniAODAnalyzer.METFilters_cff")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.load('RecoMET.METFilters.BadChargedCandidateFilter_cfi')
process.BadChargedCandidateFilter.muons = cms.InputTag("slimmedMuons")
process.BadChargedCandidateFilter.PFCandidates = cms.InputTag("packedPFCandidates")
process.BadChargedCandidateFilter.taggingMode = cms.bool(True)

process.load('RecoMET.METFilters.BadPFMuonFilter_cfi')
process.BadPFMuonFilter.muons = cms.InputTag("slimmedMuons")
process.BadPFMuonFilter.PFCandidates = cms.InputTag("packedPFCandidates")
process.BadPFMuonFilter.taggingMode = cms.bool(True)

#process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
#    ignoreTotal = cms.untracked.int32(1),
#    moduleMemorySummary = cms.untracked.bool(True),
#)

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)

# define which IDs we want to produce
my_id_modules = [
  #   'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV70_cff'
  #  'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronHLTPreselecition_Summer16_V1_cff'
   'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer16_80X_V1_cff'
    ]
#add them to the VID producer
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1))

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#        '/store/data/Run2017F/Tau/MINIAOD/PromptReco-v1/000/305/043/00000/B68B7448-1AB2-E711-BE14-02163E012A93.root'
#        '/store/relval/CMSSW_10_1_7/SingleMuon/MINIAOD/101X_dataRun2_Prompt_HEmiss_v1_RelVal_sigMu2018B-v1/10000/F0173B54-EA7F-E811-A82E-003048FFCBB8.root',
#        '/store/relval/CMSSW_10_1_7/SingleMuon/MINIAOD/101X_dataRun2_Prompt_HEmiss_v1_RelVal_sigMu2018B-v1/10000/C22BB9A2-EC7F-E811-9BF6-0025905A6082.root'
#        '/store/relval/CMSSW_10_1_7/SingleMuon/MINIAOD/101X_dataRun2_Prompt_v11_RelVal_sigMu2018B-v1/10000/A20C0E46-1F80-E811-BA58-0025905B8586.root'
        ''
    )
#    eventsToProcess = cms.untracked.VEventRange('1:40000-1:86000'),
)

process.demo = cms.EDAnalyzer('MiniAODAnalyzer',
#       doFakeHist_ = cms.bool(True),
##       doTrees_ = cms.bool(True),
#       useReweighting = cms.bool(True),
#       doFakeHist_ = cms.bool(False),
#       doTrees_ = cms.bool(False),
#       useReweighting = cms.bool(False),
#       RunOnData_ = cms.bool(False),
       RunOnData_ = cms.bool(True),
### generatorName required only for madgraph and powheg. For other cases one can just write "default"
#       generatorName = cms.string("madgraphMLM"),
#       generatorName = cms.string("default"),
#       generatorName = cms.string("powheg"),
### correct pdfName required only for madgraph, for other cases one can just write "default"
#       pdfName = cms.string("NNPDF30_lo_as_0130.LHgrid"),   # madgraphMLM
#       pdfName = cms.string("NNPDF23_lo_as_0130_qed.LHgrid"), # NUGIM madgraph
#       pdfName = cms.string("default"),   # powheg and others
       debugLevel_ = cms.int32(0),
       vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
       taus = cms.InputTag("slimmedTaus"),
       muons = cms.InputTag("slimmedMuons"),
       electrons = cms.InputTag("slimmedElectrons"),
       jets = cms.InputTag("slimmedJets"),
       met = cms.InputTag("slimmedMETs"),
       met_reminiaod = cms.InputTag("slimmedMETs"),
       bits = cms.InputTag("TriggerResults","","HLT"),
       bits_MET = cms.InputTag("TriggerResults","","HLT"), ## data
       #bits_MET = cms.InputTag("TriggerResults","","PAT"),  ##for MC and reminiAOD DATA
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
#       KFactorE = cms.string("k_faktors_ele.root"),
#       KFactorMu = cms.string("k_faktors_mu.root"),
#       KFactorTau = cms.string("k_faktors_tau.root"),
#       QCDWeightTau = cms.string("qcdFakeOutput15pt_eta.root"),
       #sourceFileString = cms.string(process.source_().dumpConfig().split('\n')[2].split("/")[4]),
#       sourceFileString = cms.string(options.sourceFileStringInput),                       
       BadChargedCandidateFilter = cms.InputTag("BadChargedCandidateFilter"),
       BadPFMuonFilter = cms.InputTag("BadPFMuonFilter"),
#       eleIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronHLTPreselection-Summer16-V1"),
#       eleIdMap = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV70"),
       eleIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-loose"),
  #     LHEEventTag = cms.InputTag("externalLHEProducer","","LHE"),
#       LHEEventTag = cms.InputTag("externalLHEProducer"),
  #     LHEEventTag = cms.InputTag("source","","LHEFile"),
#       tag = cms.untracked.string("initrwgt"),
#       doPDFuncertainty_ = cms.bool(False),

)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('hist_analysis.root'),
 #                                  closeFileFast = cms.untracked.bool(True)
)

#process.run = cms.Path(process.BadPFMuonFilter *process.BadChargedCandidateFilter)

#process.p = cms.Path(process.METFiltersSequence*process.egmGsfElectronIDSequence*process.demo)
process.p = cms.Path(process.egmGsfElectronIDSequence*process.demo)
#process.demo)
#process.p = cms.Path(process.demo)
