// -*- C++ -*-
//
// Original Author:  Swagata Mukherjee
//         Created:  Tue, 05 Jul 2016 09:41:37 GMT
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/global/EDFilter.h"
#include "FWCore/Framework/interface/EDProducer.h"
//#include "PhysicsTools/HepMCCandAlgos/interface/PDFWeightsHelper.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "DataFormats/Common/interface/RefToPtr.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Particle.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/PatCandidates/interface/VIDCutFlowResult.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include <vector>
#include "TTree.h"
#include "TFile.h"
#include <string>
#include "TH1.h"
#include "TLorentzVector.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include "TProfile.h"

//#include "stdlib.h"
// cant set lorentzvetor branch without this
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif
#ifdef __CINT__
#pragma link C++ class std::vector<float>+;
#endif

// new includes
#include <unordered_map>
#include <unordered_set>
#include "helper.hh"
#include "TString.h"
//
// class declaration
//

class MiniAODAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
  ///////class MiniAODAnalyzer : public edm::EDAnalyzer {
public:
  explicit MiniAODAnalyzer(const edm::ParameterSet&);
  ~MiniAODAnalyzer();
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  virtual void beginRun( edm::Run const &iRun, edm::EventSetup const &iSetup ) ; //override;

  float DRTauMu(TLorentzVector, std::vector<TLorentzVector>);
  bool PassTauID(const pat::Tau &tau);

  double GetTauIDScaleFactor(double tau_pt, std::string mode);
  double GetTauIDScaleFactorUncert(double tauSF, double tau_pt, std::string mode, std::string up, std::string down);  

  edm::Handle<pat::MuonCollection> muons;
  // pat::Electron objects can be recast as reco::GsfElectron objects //
  edm::Handle<edm::View<reco::GsfElectron> > electrons;
  //edm::Handle<pat::ElectronCollection> electrons;
  edm::Handle<pat::TauCollection> taus;
  edm::Handle<pat::JetCollection> jets;
  edm::Handle<edm::View<reco::GenParticle> > pruned; ///might not work for data
  //reco::GenParticle* GetTruthMatch(std::string name, pat::Tau lepton);

  edm::Service<TFileService> fs;
  Helper* helper =new Helper(fs);  
  bool passMu50;
  ///

  // ----------member data ---------------------------
  edm::LumiReWeighting LumiWeights_;
  edm::LumiReWeighting LumiWeights_UP_;
  edm::LumiReWeighting LumiWeights_DOWN_;
  edm::EDGetTokenT<reco::VertexCollection> vtxToken_;
  edm::EDGetTokenT<pat::TauCollection> tauToken_;
  edm::EDGetTokenT<pat::MuonCollection> muonToken_;
  edm::EDGetTokenT<pat::JetCollection> jetToken_;
  edm::EDGetToken  electronToken_;
  //edm::EDGetTokenT<pat::ElectronCollection> electronToken_;
  edm::EDGetTokenT<pat::METCollection> metToken_;
  edm::EDGetTokenT<pat::METCollection> metToken_reminiaod_;
  edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
  edm::EDGetTokenT<edm::TriggerResults> triggerBits_MET_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjects_;
  edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescales_;
  // edm::EDGetTokenT<edm::ValueMap<bool> > eleLooseIdMapToken_;
  edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;
  edm::EDGetTokenT<edm::View<pat::PackedGenParticle> > packedGenToken_;
  edm::EDGetTokenT<GenEventInfoProduct> genEventInfoProductTagToken_;
  edm::EDGetTokenT<std::vector<PileupSummaryInfo> > puCollection_;
  //edm::EDGetTokenT<bool> BadChCandFilterToken_;
  // edm::EDGetTokenT<bool> BadPFMuonFilterToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> > eleIdMapToken_;
 
  //------//
  std::string pileupMC_ ;
  std::string pileupData_ ;
  std::string pileupData_UP_ ;
  std::string pileupData_DOWN_ ;
  bool RunOnData;
  int debugLevel;

  TH1I *h1_EventCount;
  TH1I *h1_EventCount_trig;
  TH1I *h1_EventCount_trig_vtx;
  TH1I *h1_EventCount_trig_vtx_mu;
  TH1I *h1_EventCount_trig_vtx_mu_tau;

  TH1F *h1_TauPt_Stage1;
  TH1F *h1_TauEta_Stage1;
  TH1F *h1_TauPhi_Stage1;

  TH1F *h1_MuPt_Stage1;
  TH1F *h1_MuEta_Stage1;
  TH1F *h1_MuPhi_Stage1;

  TH1F *h1_MuPt_Stage2;
  TH1F *h1_MuEta_Stage2;
  TH1F *h1_MuPhi_Stage2;

  TH1F *h1_M_Stage1;
  TH1F *h1_Mtot_Stage1;
  TH1F *h1_Mcoll_Stage1;
  TH1F *h1_MTmumet_Stage1;

  TH1F *h1_MET_Stage1;
  TH1F *h1_MET_phi_Stage1;

  TH1F *h1_MET_Stage2;
  TH1F *h1_MET_phi_Stage2;

  TH1F* h1_nrecoVtx_Stage1;
  TH1F* h1_nrecoVtx_Stage2;

  int Run;
  int LumiSc;
  //  double  final_wt_NOPU=1;
  double final_weight=1;
  unsigned long Event;
  std::ofstream myfile;

};

//
// constructors and destructor
//
MiniAODAnalyzer::MiniAODAnalyzer(const edm::ParameterSet& iConfig):
  vtxToken_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertices"))),
  tauToken_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("taus"))),
  muonToken_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons"))),
  jetToken_(consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("jets"))),
  // electronsMiniAODToken_    = mayConsume<edm::View<reco::GsfElectron> >
  // (iConfig.getParameter<edm::InputTag>
  // ("electronsMiniAOD"));
  electronToken_(mayConsume<edm::View<reco::GsfElectron>>(iConfig.getParameter<edm::InputTag>("electrons"))),
  metToken_(consumes<pat::METCollection>(iConfig.getParameter<edm::InputTag>("met"))),
  metToken_reminiaod_(consumes<pat::METCollection>(iConfig.getParameter<edm::InputTag>("met_reminiaod"))),
  triggerBits_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits"))),
  triggerBits_MET_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits_MET"))),
  triggerObjects_(consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>("objects"))),
  triggerPrescales_(consumes<pat::PackedTriggerPrescales>(iConfig.getParameter<edm::InputTag>("prescales"))),
  //  eleLooseIdMapToken_(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleLooseIdMap"))),
  prunedGenToken_(consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned"))),
  packedGenToken_(consumes<edm::View<pat::PackedGenParticle> >(iConfig.getParameter<edm::InputTag>("packed"))),
  genEventInfoProductTagToken_(consumes<GenEventInfoProduct>(iConfig.getParameter<edm::InputTag>("genEventInfoProductMiniAOD"))),
  puCollection_(consumes<std::vector<PileupSummaryInfo> >(iConfig.getParameter<edm::InputTag>("pileupCollection"))),
  //BadChCandFilterToken_(consumes<bool>(iConfig.getParameter<edm::InputTag>("BadChargedCandidateFilter"))),
  //BadPFMuonFilterToken_(consumes<bool>(iConfig.getParameter<edm::InputTag>("BadPFMuonFilter"))),
  eleIdMapToken_(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleIdMap"))),
  // LHEEventToken_( consumes<LHEEventProduct>( iConfig.getParameter<edm::InputTag>( "LHEEventTag" ))),
  //  LHERunInfoToken_( consumes<LHERunInfoProduct,edm::InRun> ( iConfig.getParameter<edm::InputTag>( "LHEEventTag" ))),
  //  LHERunInfoToken_( consumes<LHERunInfoProduct,edm::InRun> (edm::InputTag("externalLHEProducer"))),
  //  LHERunInfoToken_( consumes<LHERunInfoProduct,edm::InRun> (edm::InputTag("source"))),
  // pdfName_(iConfig.getParameter<std::string>("pdfName")),
  //tag_(iConfig.getUntrackedParameter<std::string>( "tag", "initrwgt" )),
  RunOnData(iConfig.getParameter<bool>("RunOnData_")),
  // doTrees(iConfig.getParameter<bool>("doTrees_")),
  // doFakeHist(iConfig.getParameter<bool>("doFakeHist_")),
  // doPDFuncertainty(iConfig.getParameter<bool>("doPDFuncertainty_")),
  // generatorName_(iConfig.getParameter<std::string>("generatorName")),
  debugLevel(iConfig.getParameter<int>("debugLevel_"))
{
   //now do what ever initialization is needed
  //usesResource("TFileService");
  pileupMC_ = iConfig.getParameter<std::string>("PileupMCFile") ;
  pileupData_ = iConfig.getParameter<std::string>("PileupDataFile") ;
  pileupData_UP_ = iConfig.getParameter<std::string>("PileupDataFile_UP") ;
  pileupData_DOWN_ = iConfig.getParameter<std::string>("PileupDataFile_DOWN") ;
  
  TFileDirectory histoDir = fs->mkdir("histoDir");
  TFileDirectory controlDir = fs->mkdir("controlDir");
  /////  if (isPowheg) lheString = "source" ;

  h1_EventCount = histoDir.make<TH1I>("eventCount", "EventCount", 10, 0, 10);
  h1_EventCount_trig = histoDir.make<TH1I>("eventCount_trig", "EventCount_trig", 10, 0, 10);
  h1_EventCount_trig_vtx = histoDir.make<TH1I>("eventCount_trig_vtx", "EventCount_trig_vtx", 10, 0, 10);
  h1_EventCount_trig_vtx_mu = histoDir.make<TH1I>("eventCount_trig_vtx_mu", "EventCount_trig_vtx_mu", 10, 0, 10);
  h1_EventCount_trig_vtx_mu_tau = histoDir.make<TH1I>("eventCount_trig_vtx_mu_tau", "EventCount_trig_vtx_mu_tau", 10, 0, 10);

  h1_TauPt_Stage1 = histoDir.make<TH1F>("tauPt_Stage1", "TauPt_Stage1", 4000, 0, 4000);
  h1_TauEta_Stage1 = histoDir.make<TH1F>("tauEta_Stage1", "TauEta_Stage1", 480, -2.4, 2.4);
  h1_TauPhi_Stage1 = histoDir.make<TH1F>("tauPhi_Stage1", "TauPhi_Stage1", 800, -4.0, 4.0);

  h1_MuPt_Stage1 = histoDir.make<TH1F>("muPt_Stage1", "muPt_Stage1", 4000, 0, 4000);
  h1_MuEta_Stage1 = histoDir.make<TH1F>("muEta_Stage1", "muEta_Stage1", 480, -2.4, 2.4);
  h1_MuPhi_Stage1 = histoDir.make<TH1F>("muPhi_Stage1", "muPhi_Stage1", 800, -4.0, 4.0);

  h1_MuPt_Stage2 = histoDir.make<TH1F>("muPt_Stage2", "muPt_Stage2", 4000, 0, 4000);
  h1_MuEta_Stage2 = histoDir.make<TH1F>("muEta_Stage2", "muEta_Stage2", 480, -2.4, 2.4);
  h1_MuPhi_Stage2 = histoDir.make<TH1F>("muPhi_Stage2", "muPhi_Stage2", 800, -4.0, 4.0);

  h1_M_Stage1 = histoDir.make<TH1F>("m_Stage1", "M_Stage1", 13000, 0, 13000);
  h1_Mtot_Stage1 = histoDir.make<TH1F>("mtot_Stage1", "Mtot_Stage1", 13000, 0, 13000);
  h1_Mcoll_Stage1 = histoDir.make<TH1F>("mcoll_Stage1", "Mcoll_Stage1", 13000, 0, 13000);
  h1_MTmumet_Stage1 = histoDir.make<TH1F>("mTmumet_Stage1", "MTmumet_Stage1", 13000, 0, 13000);

  h1_MET_Stage1 = histoDir.make<TH1F>("met_Stage1", "MET_Stage1", 13000, 0, 13000);
  h1_MET_phi_Stage1 = histoDir.make<TH1F>("met_phi_Stage1", "MET_phi_Stage1", 800, -4.0, 4.0);
  h1_nrecoVtx_Stage1 = histoDir.make<TH1F>("nrecoVtx_Stage1", "NrecoVtx_Stage1", 100, 0, 100);

  h1_MET_Stage2 = histoDir.make<TH1F>("met_Stage2", "MET_Stage2", 13000, 0, 13000);
  h1_MET_phi_Stage2 = histoDir.make<TH1F>("met_phi_Stage2", "MET_phi_Stage2", 800, -4.0, 4.0);
  h1_nrecoVtx_Stage2 = histoDir.make<TH1F>("nrecoVtx_Stage2", "NrecoVtx_Stage2", 100, 0, 100);

  if (!RunOnData) {
    LumiWeights_ = edm::LumiReWeighting(pileupMC_, pileupData_, "pileup", "pileup");
    LumiWeights_UP_ = edm::LumiReWeighting(pileupMC_, pileupData_UP_, "pileup", "pileup");
    LumiWeights_DOWN_ = edm::LumiReWeighting(pileupMC_, pileupData_DOWN_, "pileup", "pileup");
  }
}


MiniAODAnalyzer::~MiniAODAnalyzer()
{
}

void MiniAODAnalyzer::beginRun( edm::Run const &iRun, edm::EventSetup const &iSetup ) {
}

// ------------ method called for each event  ------------
void MiniAODAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace reco;
  using namespace pat;

  h1_EventCount->Fill(1);

  //---Clear---//
  Run=0;
  Event=0;
  LumiSc=0;
  //------//
  Run   = iEvent.id().run();
  Event = iEvent.id().event();
  LumiSc = iEvent.luminosityBlock(); // iEvent.id().lumi();
  //std::cout << "\n --EVENT-- " << Event  <<   "  lumisc=" << LumiSc << "  run=" << Run << std::endl;
  

  //-- probValue --//
  //-- https://github.com/cms-sw/cmssw/blob/CMSSW_8_1_X/SimGeneral/MixingModule/python/mix_2016_25ns_SpringMC_PUScenarioV1_PoissonOOTPU_cfi.py --//
  //----------//
  //--PileUp--//
  //----------//
  int MC_TrueNumInteractions=-1;
  double Lumi_Wt=1;
  double Lumi_Wt_UP=1;
  double Lumi_Wt_DOWN=1;
  if (!RunOnData) {
    Handle<std::vector< PileupSummaryInfo > >  PupInfo;
    iEvent.getByToken(puCollection_, PupInfo);
    std::vector<PileupSummaryInfo>::const_iterator PVI;
    int Tnpv = -1;
    for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
      int BX = PVI->getBunchCrossing();
      // std::cout << " --PVI-- " << " BX=" << BX << std::endl;
      if(BX == 0) {
	Tnpv = PVI->getTrueNumInteractions();
	// std::cout << "Tnpv=" << Tnpv << std::endl;
	continue;
      }
    }
    MC_TrueNumInteractions = Tnpv;
    Lumi_Wt = LumiWeights_.weight( MC_TrueNumInteractions );
    // Lumi_Wt_UP = LumiWeights_UP_.weight( MC_TrueNumInteractions );
    //Lumi_Wt_DOWN = LumiWeights_DOWN_.weight( MC_TrueNumInteractions );
  }
  //  std::cout << "RunOnData=" << RunOnData << " MC_TrueNumInteractions=" << MC_TrueNumInteractions << " Lumi_Wt=" << Lumi_Wt << std::endl;


  ///-- MC event weight --///
  double mc_event_weight=-20;
  if (!RunOnData) {
    Handle<GenEventInfoProduct> genEvtInfo;
    iEvent.getByToken(genEventInfoProductTagToken_, genEvtInfo );
    mc_event_weight = genEvtInfo->weight();
  }
  if (RunOnData) {
    mc_event_weight=1.0;
  }
  //  std::cout << "RunOnData=" << RunOnData << " mc_event_weight=" << mc_event_weight << std::endl;


   //---Trigger---//
   edm::Handle<edm::TriggerResults> triggerBits;
   edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
   edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;
   iEvent.getByToken(triggerBits_, triggerBits);
   iEvent.getByToken(triggerObjects_, triggerObjects);
   iEvent.getByToken(triggerPrescales_, triggerPrescales);
   const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);
  
   passMu50=0;
  
   /////ele triggers
   //   for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
   // if ( 
   //	 (names.triggerName(i)).find("HLT_Ele27_WPTight_Gsf_v") != std::string::npos or
   //	 (names.triggerName(i)).find("HLT_Ele115_CaloIdVT_GsfTrkIdT_v") != std::string::npos or
   //	 (names.triggerName(i)).find("HLT_Photon175_v") != std::string::npos) {
   //  passElePhoton=triggerBits->accept(i) ;
   //  if (passElePhoton==true) break;
   // }
   // }
   //   
   for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
     if ( 
	 (names.triggerName(i)).find("HLT_Mu50_v") != std::string::npos 
	  ) {
       passMu50=triggerBits->accept(i) ;
       if (passMu50==true) break;
     }
   }

   //   std::cout << "trigger mu50 " << passMu50 << std::endl;

   //---Trigger MET---//
   edm::Handle<edm::TriggerResults> triggerBits_MET;
   iEvent.getByToken(triggerBits_MET_, triggerBits_MET);
   const edm::TriggerNames &names_MET = iEvent.triggerNames(*triggerBits_MET);
   //  bool passAllMETFilters=0;

   //   bool goodVertices =0;
   // bool globalSuperTightHalo2016Filter =0;
   // bool HBHENoiseFilter =0;
   //  bool HBHENoiseIsoFilter =0;
   // bool EcalDeadCellTriggerPrimitiveFilter =0;
   // bool BadPFMuonFilter=0;
   // bool BadChargedCandidateFilter =0;
   // bool  eeBadScFilter=0;
   // bool  ecalBadCalibFilter =0;
  
 //   std::cout << " === TRIGGER PATHS (MET) === " << std::endl;
   /*
   for (unsigned int i = 0, n = triggerBits_MET->size(); i < n; ++i) {
     //std::cout << names_MET.triggerName(i) << std::endl;
     if ( (names_MET.triggerName(i)).find("Flag_goodVertices") != std::string::npos ) {
       goodVertices=triggerBits_MET->accept(i) ;
     }
     if ( (names_MET.triggerName(i)).find("Flag_globalSuperTightHalo2016Filter") != std::string::npos ) {
      globalSuperTightHalo2016Filter =triggerBits_MET->accept(i) ;
     }
     if ( (names_MET.triggerName(i)).find("Flag_HBHENoiseFilter") != std::string::npos ) {
     HBHENoiseFilter =triggerBits_MET->accept(i) ;
     }
     if ( (names_MET.triggerName(i)).find("Flag_HBHENoiseIsoFilter") != std::string::npos ) {
      HBHENoiseIsoFilter=triggerBits_MET->accept(i) ;
     }
     if ( (names_MET.triggerName(i)).find("Flag_EcalDeadCellTriggerPrimitiveFilter") != std::string::npos ) {
      EcalDeadCellTriggerPrimitiveFilter=triggerBits_MET->accept(i) ;
     }
     if ( (names_MET.triggerName(i)).find("Flag_BadPFMuonFilter") != std::string::npos ) {
      BadPFMuonFilter =triggerBits_MET->accept(i) ;
     }
     if ( (names_MET.triggerName(i)).find("Flag_BadChargedCandidateFilter") != std::string::npos ) {
      BadChargedCandidateFilter =triggerBits_MET->accept(i) ;
     }
     if ( (names_MET.triggerName(i)).find("Flag_eeBadScFilter") != std::string::npos ) {
       eeBadScFilter=triggerBits_MET->accept(i) ;
     }
     if ( (names_MET.triggerName(i)).find("Flag_ecalBadCalibFilter") != std::string::npos ) {
       ecalBadCalibFilter=triggerBits_MET->accept(i) ;
     }
   }
   */
   //   passAllMETFilters =  goodVertices * globalSuperTightHalo2016Filter * HBHENoiseFilter * HBHENoiseIsoFilter * EcalDeadCellTriggerPrimitiveFilter * BadPFMuonFilter * BadChargedCandidateFilter * eeBadScFilter * ecalBadCalibFilter ;
   // std::cout << goodVertices << globalSuperTightHalo2016Filter << HBHENoiseFilter << HBHENoiseIsoFilter << EcalDeadCellTriggerPrimitiveFilter << BadPFMuonFilter << BadChargedCandidateFilter << eeBadScFilter << ecalBadCalibFilter << std::endl; 
   //  std::cout << "passAllMETFilters=" << passAllMETFilters << std::endl;


   ///-- VERTEX --///
   edm::Handle<reco::VertexCollection> vertices;
   iEvent.getByToken(vtxToken_, vertices);
   if (vertices->empty()) return; // skip the event if no PV found
   // std::cout << "Number of vertices " << vertices->size() << std::endl;
   const reco::Vertex &PV = vertices->front();
   reco::VertexCollection vtxs = *vertices;
   int nvtx=0;
   int recoVtx = vertices->size();
   if( vertices.isValid() ){
     for( reco::VertexCollection::const_iterator vtx = vtxs.begin(); vtx!=vtxs.end(); ++vtx ) {
       bool isGood = ( (vtx->ndof() >= 4.0) &&
               (abs(vtx->z()) <= 24.0) &&
               (abs(vtx->position().Rho()) <= 2.0)
               );
       if( !isGood ) continue;
       nvtx++;
     }
   }
   //   std::cout << "Number of good vertices " << nvtx << std::endl;

   /*
   edm::Handle<edm::ValueMap<bool> > ele_id_decisions;
   iEvent.getByToken(eleIdMapToken_ ,ele_id_decisions);
   int nEle=0;
   iEvent.getByToken(electronToken_, electrons);
   for (size_t i = 0; i < electrons->size(); ++i){
     const auto el = electrons->ptrAt(i);
     if (el->pt() < 5) continue;
     bool isPassEleId  = (*ele_id_decisions)[el];
     if ( (el->pt()>50) && (isPassEleId) ){
       nEle++;
       break;
     }
   }
   */

   int nMu=0;
   double mu_pt=0;
   double mu_eta=0;
   double mu_phi=0;
   TLorentzVector Muon_sel(0,0,0,0);
   iEvent.getByToken(muonToken_, muons);
   for (const pat::Muon &mu : *muons) {
     //https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2#Tight_Muon
     //     if ( (mu.pt()>20.0) &&  (abs(mu.eta())<2.4) && (mu.isLooseMuon(PV)) &&  ((mu.isolationR03().sumPt/mu.pt())<0.10) ) {
     if ( (mu.pt()>53.0) &&  (abs(mu.eta())<2.4) && ( mu.isHighPtMuon(PV) ) &&  ((mu.isolationR03().sumPt/mu.pt())<0.10) ) {
       Muon_sel.SetPxPyPzE(mu.px(),mu.py(),mu.pz(),mu.energy());
       //std::cout << "muon pt " << Muon_sel.Pt() << std::endl; 
       nMu++;
       mu_pt=mu.pt();
       mu_eta=mu.eta();
       mu_phi=mu.phi();
       break;
     }
   }

   //   std::cout << "nMuon " << nMu << std::endl;

   int nTau=0;
   double tau_pt=0;
   double tau_eta=0;
   double tau_phi=0;
   TLorentzVector tau_vis_p4(0,0,0,0);
   iEvent.getByToken(tauToken_, taus);
   for (const pat::Tau &tau : *taus) {
     if ( (PassTauID(tau)==true) ) {
       tau_vis_p4.SetPxPyPzE(tau.px(),tau.py(),tau.pz(),tau.energy());
       // std::cout << "tau pt " << tau.pt() << std::endl;
       nTau++;
       tau_pt=tau.pt();
       tau_eta=tau.eta();
       tau_phi=tau.phi();
       break;	 
     }
   }

   //   std::cout << "nTau " << nTau << std::endl;
   ////  if (nTau>0) std::cout << "got a tau !!" << std::endl;

    ////// MET //////
   edm::Handle<pat::METCollection> mets;
   TLorentzVector met_p4(0,0,0,0);
   TLorentzVector neutrino_p4(0,0,0,0);
   if (!RunOnData) { 
     iEvent.getByToken(metToken_, mets);
   } else if (RunOnData) {
     iEvent.getByToken(metToken_reminiaod_, mets);
   }

   const pat::MET &met = mets->front();
   double met_val=met.pt();
   double met_phi=met.phi();
   float met_px=met.px();
   float met_py=met.py();
   float met_E=met.energy();
   met_p4.SetPxPyPzE(met.px(),met.py(),met.pz(),met.energy());
   neutrino_p4.SetPtEtaPhiM(met.pt(),tau_eta,met.phi(),0);

   //----------------//
   //--Final Weight--//
   //----------------//
   if (!RunOnData) {
     final_weight               = Lumi_Wt * mc_event_weight ;// * tauID_SF * trig_SF * tauELE_SF;
   }
   else {
     final_weight               = 1.0;
 }

   //---------------//
   //---Selection---//
   //---------------//
   // std::cout << "Proceed to selection cuts " << std::endl;
   // std::cout << "passMu50 " << passMu50  << " nvtx " << nvtx << " nMu " << nMu << "  nTau " << nTau << std::endl;
   double mutau_mass=0.0;
   double mutaumet_mass=0.0;
   double coll_mass=0.0;

  if (passMu50) {
      h1_EventCount_trig->Fill(1);
    //    if (passAllMETFilters ) {
      if ( (nvtx>0) ) { 
      h1_EventCount_trig_vtx->Fill(1);
	if (nMu>0) { 
	  h1_EventCount_trig_vtx_mu->Fill(1);
	  h1_MuPt_Stage2->Fill(mu_pt,final_weight);
	  h1_MuEta_Stage2->Fill(mu_eta,final_weight);
	  h1_MuPhi_Stage2->Fill(mu_phi,final_weight);
	  h1_MET_Stage2->Fill(met_val,final_weight);
	  h1_MET_phi_Stage2->Fill(met_phi,final_weight);
	  h1_nrecoVtx_Stage2->Fill(nvtx,final_weight);
	  if ((nTau>0)) {
	    h1_EventCount_trig_vtx_mu_tau->Fill(1);
	    TLorentzVector mutau=(Muon_sel+tau_vis_p4);
	    mutau_mass=mutau.M();
	    ////std::cout << "\nmutau mass " << mutau_mass << std::endl;
	    h1_M_Stage1->Fill(mutau_mass,final_weight);

	    TLorentzVector mutaumet=(Muon_sel+tau_vis_p4+met_p4);
	    mutaumet_mass=mutaumet.M();
	    ///std::cout << "mutaumet mass " << mutaumet_mass << std::endl;
	    h1_Mtot_Stage1->Fill(mutaumet_mass,final_weight);

	    TLorentzVector tau_full=(tau_vis_p4+neutrino_p4);
	    TLorentzVector mutau_coll=(Muon_sel+tau_full);
	    coll_mass=mutau_coll.M();
	    ////std::cout << "coll mass " << coll_mass << std::endl;
	    h1_Mcoll_Stage1->Fill(coll_mass,final_weight);

	    double dphi_mu_met = deltaPhi(mu_phi,met_phi);
	    double MT_mu_met=  sqrt(2*mu_pt*met_val*(1- cos(dphi_mu_met)));
	    ////std::cout << "mT " << MT_mu_met << std::endl;
	    h1_MTmumet_Stage1->Fill(MT_mu_met,final_weight);

	    h1_TauPt_Stage1->Fill(tau_pt,final_weight);
	    h1_TauEta_Stage1->Fill(tau_eta,final_weight);
	    h1_TauPhi_Stage1->Fill(tau_phi,final_weight);
	    h1_MuPt_Stage1->Fill(mu_pt,final_weight);
	    h1_MuEta_Stage1->Fill(mu_eta,final_weight);
	    h1_MuPhi_Stage1->Fill(mu_phi,final_weight);
	    h1_MET_Stage1->Fill(met_val,final_weight);
	    h1_MET_phi_Stage1->Fill(met_phi,final_weight);
	    h1_nrecoVtx_Stage1->Fill(nvtx,final_weight);
	  }
	}
      }
      // }
  }



#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}

float MiniAODAnalyzer::DRTauMu(TLorentzVector Tau, std::vector<TLorentzVector> MuonVect) {
  float dR12=999.0;
  int size=MuonVect.size();
  for (int n=0; n<size; n++) {
    float mydR12=Tau.DeltaR(MuonVect.at(n));
    if (mydR12<dR12) dR12=mydR12;
  }
  return dR12;
}

double MiniAODAnalyzer::GetTauIDScaleFactor(double tau_pt, std::string mode) {
  double tauSF=1.0;
  if (mode=="nominal") tauSF=0.95 ;
  if (mode=="nominal_ptDep") {
    tauSF=0.95 - (0.5*(tau_pt/1000.0)) ;
    if (tauSF<0.0) tauSF=0.0;
  }
  //
  return tauSF;
}

double MiniAODAnalyzer::GetTauIDScaleFactorUncert(double tauSF, double tau_pt, std::string mode, std::string up, std::string down) {
  double tauSF1=tauSF;
  double flat_uncert = (tauSF * (5.0/100.0) );
  double ptDep_uncert_up    = 0.0;
  double ptDep_uncert_down  = 0.0;

  if (up=="up5") {
    ptDep_uncert_up   = (5.0/100.0)*(tau_pt/1000.0);
  }
  if (up=="up20") {
    ptDep_uncert_up   = (20.0/100.0)*(tau_pt/1000.0);
  }
  if (up=="up50") {
    ptDep_uncert_up   = (50.0/100.0)*(tau_pt/1000.0);
  }
  if (down=="down20") {
    ptDep_uncert_down = (20.0/100.0)*(tau_pt/1000.0);
  }
  if (down=="down50") {
    ptDep_uncert_down = (50.0/100.0)*(tau_pt/1000.0);
  }
  if (down=="down35") {
    ptDep_uncert_down = (35.0/100.0)*(tau_pt/1000.0);
  }
  //
  if (mode=="flat_up") tauSF1=(tauSF+flat_uncert);
  if (mode=="flat_down") tauSF1=(tauSF-flat_uncert);
  //
  if (mode=="ptDep_up") tauSF1=(tauSF+ptDep_uncert_up);
  if (mode=="ptDep_down") {
    tauSF1=(tauSF-ptDep_uncert_down);
    if (tauSF1<0.0) tauSF1=0.0;

  }
  //  std::cout << "SF=" << tauSF << " flat_uncert=" << flat_uncert << " ptDep_uncert=" << ptDep_uncert << std::endl;

  return tauSF1;
}
/*
bool MiniAODAnalyzer::PassFinalCuts(int nGoodTau_, double met_val_,double met_phi_,double tau_pt_,double tau_phi_) {
  bool passed=false;
  if (nGoodTau_==1) {
    if ( met_val_>200 && tau_pt_>80.0) {
      dphi_tau_met = deltaPhi(tau_phi_,met_phi_);
      pToverEtMiss=tau_pt_/met_val_ ;
      if (pToverEtMiss>0.7 && pToverEtMiss<1.3) {
    // std::cout << "pToverEtMiss=" << pToverEtMiss << std::endl;
    if (fabs(dphi_tau_met)>2.4) {
      // std::cout << "dphi_tau_met=" << dphi_tau_met << std::endl;
      passed=true;
    }
      }
    }
  }
  return passed;
}
*/

bool MiniAODAnalyzer::PassTauID(const pat::Tau &tau)
{
  bool passTauID_=true;
  //----Tau ID----//
  if ( tau.tauID("decayModeFinding") < 0.5 ) passTauID_=false;
  if ( tau.tauID("byTightIsolationMVArun2v1DBoldDMwLT") < 0.5 ) passTauID_=false;
  if ( tau.tauID("againstElectronVLooseMVA6") < 0.5 ) passTauID_=false;
  /////if ( tau.tauID("againstElectronTightMVA6") < 0.5 ) passTauID_=false;
  /////  if ( tau.tauID("againstMuonLoose3") < 0.5 ) passTauID_=false;
  if ( tau.tauID("againstMuonTight3") < 0.5 ) passTauID_=false;
  if (tau.pt()<30) passTauID_=false;
  if (fabs(tau.eta())>2.3) passTauID_=false;

  return passTauID_;
 //  return  PassTauID_Old_VLoose(tau);
}

// ------------ method called once each job just before starting event loop  ------------
void
MiniAODAnalyzer::beginJob()
{
  if (RunOnData) myfile.open ("SelectedDataEvents.txt");
  // Create_Trees();
  helper->CreateHistoUnchangedName("h_counters", 10, 0, 11, "N_{events}");
}

// ------------ method called once each job just after ending the event loop  ------------
void
MiniAODAnalyzer::endJob()
{
  
  if (RunOnData) myfile.close();

  /*  TFileDirectory CutFlowDir = fs->mkdir("CutFlowDir");
  TH1F *cutflow = CutFlowDir.make<TH1F>("cutflow", "cutflow", 11, 0, 10);
  cutflow->SetBinContent(1, (h1_MT_passTauTrig->Integral()) );
  cutflow->SetBinContent(2, (h1_MT_passAllMETFilters->Integral()) );
  cutflow->SetBinContent(3, (h1_MT_leptonVeto->Integral()) );
  cutflow->SetBinContent(4, (h1_MT_nGoodTau->Integral()) );
  cutflow->SetBinContent(5, (h1_MT_met_val->Integral()) );
  cutflow->SetBinContent(6, (h1_MT_pTbyET->Integral()) );
  cutflow->SetBinContent(7, (h1_MT_dphi->Integral()) );

  cutflow->Write();
  */

}



// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MiniAODAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(MiniAODAnalyzer);
