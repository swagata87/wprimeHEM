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
//class MiniAODAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
class MiniAODAnalyzer : public edm::EDAnalyzer {
public:
  explicit MiniAODAnalyzer(const edm::ParameterSet&);
  ~MiniAODAnalyzer();
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  virtual void beginRun( edm::Run const &iRun, edm::EventSetup const &iSetup ) override;

  float DRTauMu(TLorentzVector, std::vector<TLorentzVector>);
  bool PassTauID(const pat::Tau &tau);
  bool PassTauID_DM(const pat::Tau &tau);
  bool PassTauID_DM_iso(const pat::Tau &tau);
  bool PassTauID_DM_iso_ele(const pat::Tau &tau);
  bool PassTauID_newDM(const pat::Tau &tau);
  bool PassTauAcceptance(TLorentzVector tau);
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
  bool passTau50MET90;
  bool passMu19Tau20;
  bool passTau140;
  bool passMu50_Tau50MET90;
  bool passMu50_Mu19Tau20;
  bool passMu50_Tau140;
  //
  ///
  bool passEle27;
  bool passEle115;
  bool passPhoton175;
  bool passElePhoton;
  bool passEle27Photon;

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
  edm::EDGetTokenT<bool> BadChCandFilterToken_;
  edm::EDGetTokenT<bool> BadPFMuonFilterToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> > eleIdMapToken_;
 
  //------//
  std::string pileupMC_ ;
  std::string pileupData_ ;
  std::string pileupData_UP_ ;
  std::string pileupData_DOWN_ ;
  bool RunOnData;
  int debugLevel;

  TH1I *h1_EventCount;
  TH1I *h1_EventCount_trg;
  TH1I *h1_EventCount_trg_filter;
  TH1I *h1_EventCount_trg_filter_vtx;
  TH1I *h1_EventCount_trg_filter_vtx_mu;
  TH1I *h1_EventCount_trg_filter_vtx_mu_DM;
  TH1I *h1_EventCount_trg_filter_vtx_mu_DM_iso;
  TH1I *h1_EventCount_trg_filter_vtx_mu_DM_iso_ele;
  TH1I *h1_EventCount_trg_filter_vtx_mu_tau;
  TH1I *h1_EventCount_trg_filter_vtx_mu_tau_newDM;

  TH1I* h1_EventCount_trigEff_Deno;

  //  TH1I  *h1_EventCount_trigEff_MuPlusTauTrg_Num;
  //  TH1I  *h1_EventCount_trigEff_MuTrg_Num;
  //  TH1I  *h1_EventCount_trigEff_TauTrg_Num;

  TH1I* h1_EventCount_trigEff_Mu50_Num;
  TH1I* h1_EventCount_trigEff_Tau50MET90_Num;
  TH1I* h1_EventCount_trigEff_Mu19Tau20_Num;
  TH1I* h1_EventCount_trigEff_Tau140_Num;
  TH1I* h1_EventCount_trigEff_Mu50_Tau50MET90_Num;
  TH1I* h1_EventCount_trigEff_Mu50_Mu19Tau20_Num;
  TH1I* h1_EventCount_trigEff_Mu50_Tau140_Num;


  TH1I  *h1_EventCount_trigEff_Ele27_Num;
  TH1I  *h1_EventCount_trigEff_Ele115_Num;
  TH1I  *h1_EventCount_trigEff_Photon175_Num;
  TH1I  *h1_EventCount_trigEff_ElePhoton_Num;
  TH1I  *h1_EventCount_trigEff_Ele27Photon_Num;

  /*
  TH1F *h1_TauPt_Stage1;
  TH1F *h1_TauCharge_Stage1;
  TH1F *h1_TauDxy_Stage1;
  TH1F *h1_TauChIso_Stage1;
  TH1F *h1_TauNeuIso_Stage1;
  TH1F *h1_TauNTrack_Stage1;
  TH1F *h1_TauEta_Stage1;
  TH1F *h1_TauPhi_Stage1;
  */ //
  TH1F *h1_M_Stage1;

  int Run;
  int LumiSc;
  //  double  final_wt_NOPU=1;
  double final_weight=1;
  /*
  double final_weight_PUweight_UP=1;
  double final_weight_PUweight_DOWN=1;
  double final_weight_tauIDSF_flat_UP=1;
  double final_weight_tauIDSF_flat_DOWN=1;
  double final_weight_tauIDSF_ptDep_UP=1;
  double final_weight_tauIDSF_ptDep_DOWN=1;
  double final_weight_tauELESF_UP=1;
  double final_weight_tauELESF_DOWN=1;
  double final_weight_trigSF_UP=1;
  double final_weight_trigSF_DOWN=1;
  */
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
  BadChCandFilterToken_(consumes<bool>(iConfig.getParameter<edm::InputTag>("BadChargedCandidateFilter"))),
  BadPFMuonFilterToken_(consumes<bool>(iConfig.getParameter<edm::InputTag>("BadPFMuonFilter"))),
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

  h1_EventCount_trg = histoDir.make<TH1I>("eventCount_trg", "EventCount_trg", 10, 0, 10);
  h1_EventCount_trg_filter = histoDir.make<TH1I>("eventCount_trg_filter", "EventCount_trg_filter", 10, 0, 10);
  h1_EventCount_trg_filter_vtx = histoDir.make<TH1I>("eventCount_trg_filter_vtx", "EventCount_trg_filter_vtx", 10, 0, 10);
  h1_EventCount_trg_filter_vtx_mu = histoDir.make<TH1I>("eventCount_trg_filter_vtx_mu", "EventCount_trg_filter_vtx_mu", 10, 0, 10);

  h1_EventCount_trg_filter_vtx_mu_DM = histoDir.make<TH1I>("eventCount_trg_filter_vtx_mu_DM", "EventCount_trg_filter_vtx_mu_DM", 10, 0, 10);
  h1_EventCount_trg_filter_vtx_mu_DM_iso = histoDir.make<TH1I>("eventCount_trg_filter_vtx_mu_DM_iso", "EventCount_trg_filter_vtx_mu_DM_iso", 10, 0, 10);
  h1_EventCount_trg_filter_vtx_mu_DM_iso_ele = histoDir.make<TH1I>("eventCount_trg_filter_vtx_mu_DM_iso_ele", "EventCount_trg_filter_vtx_mu_DM_iso_ele", 10, 0, 10);

  h1_EventCount_trg_filter_vtx_mu_tau = histoDir.make<TH1I>("eventCount_trg_filter_vtx_mu_tau", "EventCount_trg_filter_vtx_mu_tau", 10, 0, 10);
  h1_EventCount_trg_filter_vtx_mu_tau_newDM = histoDir.make<TH1I>("eventCount_trg_filter_vtx_mu_tau_newDM", "EventCount_trg_filter_vtx_mu_tau_newDM", 10, 0, 10);

  /*
  TH1I* h1_EventCount_trigEff_Mu50_Num;
  TH1I* h1_EventCount_trigEff_Tau50MET90_Num;
  TH1I* h1_EventCount_trigEff_Mu19Tau20_Num;
  TH1I* h1_EventCount_trigEff_Tau140_Num;
  TH1I* h1_EventCount_trigEff_Mu50_Tau50MET90_Num;
  TH1I* h1_EventCount_trigEff_Mu50_Mu19Tau20_Num;
  TH1I* h1_EventCount_trigEff_Mu50_Tau140_Num;
  */

  h1_EventCount_trigEff_Mu50_Num = histoDir.make<TH1I>("eventCount_trigEff_Mu50_Num", "EventCount_trigEff_Mu50_Num", 10, 0, 10);
  h1_EventCount_trigEff_Tau50MET90_Num = histoDir.make<TH1I>("eventCount_trigEff_Tau50MET90_Num", "EventCount_trigEff_Tau50MET90_Num", 10, 0, 10);
  h1_EventCount_trigEff_Mu19Tau20_Num = histoDir.make<TH1I>("eventCount_trigEff_Mu19Tau20_Num", "EventCount_trigEff_Mu19Tau20_Num", 10, 0, 10);
  h1_EventCount_trigEff_Tau140_Num = histoDir.make<TH1I>("eventCount_trigEff_Tau140_Num", "EventCount_trigEff_Tau140_Num", 10, 0, 10);
  h1_EventCount_trigEff_Mu50_Tau50MET90_Num = histoDir.make<TH1I>("eventCount_trigEff_Mu50_Tau50MET90_Num", "EventCount_trigEff_Mu50_Tau50MET90_Num", 10, 0, 10);
  h1_EventCount_trigEff_Mu50_Mu19Tau20_Num = histoDir.make<TH1I>("eventCount_trigEff_Mu50_Mu19Tau20_Num", "EventCount_trigEff_Mu50_Mu19Tau20_Num", 10, 0, 10);
  h1_EventCount_trigEff_Mu50_Tau140_Num = histoDir.make<TH1I>("eventCount_trigEff_Mu50_Tau140_Num", "EventCount_trigEff_Mu50_Tau140_Num", 10, 0, 10);

  h1_EventCount_trigEff_Ele27_Num = histoDir.make<TH1I>("eventCount_trigEff_Ele27_Num", "EventCount_trigEff_Ele27_Num", 10, 0, 10);
  h1_EventCount_trigEff_Ele115_Num = histoDir.make<TH1I>("eventCount_trigEff_Ele115_Num", "EventCount_trigEff_Ele115_Num", 10, 0, 10);
  h1_EventCount_trigEff_Photon175_Num = histoDir.make<TH1I>("eventCount_trigEff_Photon175_Num", "EventCount_trigEff_Photon175_Num", 10, 0, 10);
  h1_EventCount_trigEff_ElePhoton_Num = histoDir.make<TH1I>("eventCount_trigEff_ElePhoton_Num", "EventCount_trigEff_ElePhoton_Num", 10, 0, 10);
  h1_EventCount_trigEff_Ele27Photon_Num = histoDir.make<TH1I>("eventCount_trigEff_Ele27Photon_Num", "EventCount_trigEff_Ele27Photon_Num", 10, 0, 10);

  h1_EventCount_trigEff_Deno = histoDir.make<TH1I>("eventCount_trigEff_Deno", "EventCount_trigEff_Deno", 10, 0, 10);

  /* h1_TauPt_Stage1 = histoDir.make<TH1F>("tauPt_Stage1", "TauPt_Stage1", 1000, 0, 4000);
  h1_TauCharge_Stage1 = histoDir.make<TH1F>("tauCharge_Stage1", "TauCharge_Stage1", 5, -2.5, 2.5);
  h1_TauDxy_Stage1 = histoDir.make<TH1F>("tauDxy_Stage1", "TauDxy_Stage1", 1000, 0, 1);
  h1_TauChIso_Stage1 = histoDir.make<TH1F>("tauChIso_Stage1", "TauChIso_Stage1", 200, 0, 20);
  h1_TauNeuIso_Stage1 = histoDir.make<TH1F>("tauNeuIso_Stage1", "TauNeuIso_Stage1", 500, 0, 50);
  h1_TauNTrack_Stage1 = histoDir.make<TH1F>("tauNTrack_Stage1", "TauNTrack_Stage1", 50, -0.5, 49.5);
  h1_TauEta_Stage1 = histoDir.make<TH1F>("tauEta_Stage1", "TauEta_Stage1", 480, -2.4, 2.4);
  h1_TauPhi_Stage1 = histoDir.make<TH1F>("tauPhi_Stage1", "TauPhi_Stage1", 800, -4.0, 4.0);*/
  h1_M_Stage1 = histoDir.make<TH1F>("m_Stage1", "M_Stage1", 13000, 0, 13000);
  /*
  h1_MET_Stage1 = histoDir.make<TH1F>("met_Stage1", "MET_Stage1", 13000, 0, 13000);
  h1_MET_phi_Stage1 = histoDir.make<TH1F>("met_phi_stage1", "MET_phi_Stage1", 800, -4.0, 4.0);
  */
  /*
  h1_M_Stage1_metUncert_JetEnUp = histoDir.make<TH1F>("mT_Stage1_metUncert_JetEnUp", "MT_Stage1_metUncert_JetEnUp", 13000, 0, 13000);
  h1_M_Stage1_metUncert_JetEnDown = histoDir.make<TH1F>("mT_Stage1_metUncert_JetEnDown", "MT_Stage1_metUncert_JetEnDown", 13000, 0, 13000);
  h1_M_Stage1_metUncert_JetResUp = histoDir.make<TH1F>("mT_Stage1_metUncert_JetResUp", "MT_Stage1_metUncert_JetResUp", 13000, 0, 13000);
  h1_M_Stage1_metUncert_JetResDown = histoDir.make<TH1F>("mT_Stage1_metUncert_JetResDown", "MT_Stage1_metUncert_JetResDown", 13000, 0, 13000);
  h1_M_Stage1_metUncert_MuonEnUp = histoDir.make<TH1F>("mT_Stage1_metUncert_MuonEnUp", "MT_Stage1_metUncert_MuonEnUp", 13000, 0, 13000);
  h1_M_Stage1_metUncert_MuonEnDown = histoDir.make<TH1F>("mT_Stage1_metUncert_MuonEnDown", "MT_Stage1_metUncert_MuonEnDown", 13000, 0, 13000);
  h1_M_Stage1_metUncert_ElectronEnUp = histoDir.make<TH1F>("mT_Stage1_metUncert_ElectronEnUp", "MT_Stage1_metUncert_ElectronEnUp", 13000, 0, 13000);
  h1_M_Stage1_metUncert_ElectronEnDown = histoDir.make<TH1F>("mT_Stage1_metUncert_ElectronEnDown", "MT_Stage1_metUncert_ElectronEnDown", 13000, 0, 13000);
  h1_M_Stage1_metUncert_TauEnUp = histoDir.make<TH1F>("mT_Stage1_metUncert_TauEnUp", "MT_Stage1_metUncert_TauEnUp", 13000, 0, 13000);
  h1_M_Stage1_metUncert_TauEnDown = histoDir.make<TH1F>("mT_Stage1_metUncert_TauEnDown", "MT_Stage1_metUncert_TauEnDown", 13000, 0, 13000);
  h1_M_Stage1_metUncert_PhotonEnUp = histoDir.make<TH1F>("mT_Stage1_metUncert_PhotonEnUp", "MT_Stage1_metUncert_PhotonEnUp", 13000, 0, 13000);
  h1_M_Stage1_metUncert_PhotonEnDown = histoDir.make<TH1F>("mT_Stage1_metUncert_PhotonEnDown", "MT_Stage1_metUncert_PhotonEnDown", 13000, 0, 13000);
  h1_M_Stage1_metUncert_UnclusteredEnUp = histoDir.make<TH1F>("mT_Stage1_metUncert_UnclusteredEnUp", "MT_Stage1_metUncert_UnclusteredEnUp", 13000, 0, 13000);
  h1_M_Stage1_metUncert_UnclusteredEnDown = histoDir.make<TH1F>("mT_Stage1_metUncert_UnclusteredEnDown", "MT_Stage1_metUncert_UnclusteredEnDown", 13000, 0, 13000);
  h1_M_Stage1_TauScaleUp = histoDir.make<TH1F>("mT_Stage1_TauScaleUp", "MT_Stage1_TauScaleUp", 13000, 0, 13000);
  h1_M_Stage1_TauScaleDown = histoDir.make<TH1F>("mT_Stage1_TauScaleDown", "MT_Stage1_TauScaleDown", 13000, 0, 13000);
  h1_M_Stage1_pileupUncertUp = histoDir.make<TH1F>("mT_Stage1_pileupUncertUp", "MT_Stage1_pileupUncertUp", 13000, 0, 13000);
  h1_M_Stage1_pileupUncertDown =histoDir.make<TH1F>("mT_Stage1_pileupUncertDown", "MT_Stage1_pileupUncertDown", 13000, 0, 13000);
  h1_M_Stage1_TauIDSF_flat_Up =histoDir.make<TH1F>("mT_Stage1_TauIDSF_flat_Up", "MT_Stage1_TauIDSF_flat_Up", 13000, 0, 13000);
  h1_M_Stage1_TauIDSF_flat_Down =histoDir.make<TH1F>("mT_Stage1_TauIDSF_flat_Down", "MT_Stage1_TauIDSF_flat_Down", 13000, 0, 13000);
  h1_M_Stage1_TauIDSF_ptDep_Up =histoDir.make<TH1F>("mT_Stage1_TauIDSF_ptDep_Up", "MT_Stage1_TauIDSF_ptDep_Up", 13000, 0, 13000);
  h1_M_Stage1_TauIDSF_ptDep_Down =histoDir.make<TH1F>("mT_Stage1_TauIDSF_ptDep_Down", "MT_Stage1_TauIDSF_ptDep_Down", 13000, 0, 13000);
  h1_M_Stage1_TauELESFUp =histoDir.make<TH1F>("mT_Stage1_TauELESFUp", "MT_Stage1_TauELESFUp", 13000, 0, 13000);
  h1_M_Stage1_TauELESFDown =histoDir.make<TH1F>("mT_Stage1_TauELESFDown", "MT_Stage1_TauELESFDown", 13000, 0, 13000);
  h1_M_Stage1_trigSFUp =histoDir.make<TH1F>("mT_Stage1_trigSFUp", "MT_Stage1_trigSFUp", 13000, 0, 13000);
  h1_M_Stage1_trigSFDown =histoDir.make<TH1F>("mT_Stage1_trigSFDown", "MT_Stage1_trigSFDown", 13000, 0, 13000);
  */

  //  h1_recoVtx_NoPUWt = histoDir.make<TH1F>("recoVtx_NoPUWt", "RecoVtx_NoPUWt", 100, 0, 100);
  //  h1_recoVtx_WithPUWt = histoDir.make<TH1F>("recoVtx_WithPUWt", "RecoVtx_WithPUWt", 100, 0, 100);

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
   passTau50MET90=0;
   passMu19Tau20=0;
   passTau140=0;
   passMu50_Tau50MET90=0;
   passMu50_Mu19Tau20=0;
   passMu50_Tau140=0;

   passEle27=0;
   passEle115=0;
   passPhoton175=0;
   passElePhoton=0;
   passEle27Photon=0;

   /////ele triggers
   for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
     if ( 
	 (names.triggerName(i)).find("HLT_Ele27_WPTight_Gsf_v") != std::string::npos) {
       passEle27 =triggerBits->accept(i) ;
       if (passEle27 ==true) break;
     }
   }
   //
   for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
     if ( 
	 (names.triggerName(i)).find("HLT_Ele115_CaloIdVT_GsfTrkIdT_v") != std::string::npos) {
       passEle115 =triggerBits->accept(i) ;
       if (passEle115 ==true) break;
     }
   }
   //
   for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
     if ( 
	 (names.triggerName(i)).find("HLT_Photon175_v") != std::string::npos) {
       passPhoton175 =triggerBits->accept(i) ;
       if (passPhoton175 ==true) break;
     }
   }
   //   
   for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
     if ( 
	 (names.triggerName(i)).find("HLT_Ele27_WPTight_Gsf_v") != std::string::npos or
	 (names.triggerName(i)).find("HLT_Ele115_CaloIdVT_GsfTrkIdT_v") != std::string::npos or
	 (names.triggerName(i)).find("HLT_Photon175_v") != std::string::npos) {
       passElePhoton=triggerBits->accept(i) ;
       if (passElePhoton==true) break;
     }
   }
   //   
   for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
     if ( 
	 (names.triggerName(i)).find("HLT_Ele27_WPTight_Gsf_v") != std::string::npos or
	 (names.triggerName(i)).find("HLT_Photon175_v") != std::string::npos) {
       passEle27Photon=triggerBits->accept(i) ;
       if (passEle27Photon==true) break;
     }
   }
   
   //////muon tau triggers
  //   std::cout << "=== TRIGGER PATHS === " << std::endl;
   for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
     if ( 
	 (names.triggerName(i)).find("HLT_Mu50_v") != std::string::npos or
	 (names.triggerName(i)).find("HLT_TkMu50_v") != std::string::npos
	  ) {
       passMu50=triggerBits->accept(i) ;
       if (passMu50==true) break;
     }
   }

   for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
     if ( 
	 (names.triggerName(i)).find("HLT_LooseIsoPFTau50_Trk30_eta2p1_MET90_v") != std::string::npos 	  ) {
       passTau50MET90=triggerBits->accept(i) ;
       if (passTau50MET90==true) break;
     }
   }

   for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
     if ( 
	 (names.triggerName(i)).find("HLT_LooseIsoPFTau50_Trk30_eta2p1_MET90_v") != std::string::npos or
	 (names.triggerName(i)).find("HLT_Mu50_v") != std::string::npos or
	 (names.triggerName(i)).find("HLT_TkMu50_v") != std::string::npos 
	  ) {
       passMu50_Tau50MET90=triggerBits->accept(i) ;
       if (passMu50_Tau50MET90==true) break;
     }
   }

   for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
     if ( 
	 (names.triggerName(i)).find("HLT_IsoMu19_eta2p1_LooseCombinedIsoPFTau20_v") != std::string::npos or
	 (names.triggerName(i)).find("HLT_Mu50_v") != std::string::npos or
	 (names.triggerName(i)).find("HLT_TkMu50_v") != std::string::npos 
	  ) {
       passMu50_Mu19Tau20=triggerBits->accept(i) ;
       if (passMu50_Mu19Tau20==true) break;
     }
   }

   for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
     if ( 
	 (names.triggerName(i)).find("HLT_IsoMu19_eta2p1_LooseCombinedIsoPFTau20_v") != std::string::npos 
	  ) {
       passMu19Tau20=triggerBits->accept(i) ;
       if (passMu19Tau20==true) break;
     }
   }

   for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
     if ( 
	 (names.triggerName(i)).find("HLT_VLooseIsoPFTau140_Trk50_eta2p1_v") != std::string::npos 
	  ) {
       passTau140=triggerBits->accept(i) ;
       if (passTau140==true) break;
     }
   }

   for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
     if ( 
	 (names.triggerName(i)).find("HLT_VLooseIsoPFTau140_Trk50_eta2p1_v") != std::string::npos or
	 (names.triggerName(i)).find("HLT_Mu50_v") != std::string::npos or
	 (names.triggerName(i)).find("HLT_TkMu50_v") != std::string::npos 
	  ) {
       passMu50_Tau140=triggerBits->accept(i) ;
       if (passMu50_Tau140==true) break;
     }
   }


   //---Trigger MET---//
   edm::Handle<edm::TriggerResults> triggerBits_MET;
   iEvent.getByToken(triggerBits_MET_, triggerBits_MET);
   const edm::TriggerNames &names_MET = iEvent.triggerNames(*triggerBits_MET);
   bool passAllMETFilters=0;
   bool passHBHENoiseFilter=0;
   bool passHBHENoiseIsoFilter=0;
   bool passEcalDeadCellTriggerPrimitiveFilter=0;
   bool passgoodVertices=0;
   bool passeeBadScFilter=0;
   bool passglobalTightHalo2016Filter=0;
   bool NobadMuons=0;
   //   std::cout << " === TRIGGER PATHS (MET) === " << std::endl;
   for (unsigned int i = 0, n = triggerBits_MET->size(); i < n; ++i) {
     if ( (names_MET.triggerName(i)).find("Flag_HBHENoiseFilter") != std::string::npos ) {
       passHBHENoiseFilter=triggerBits_MET->accept(i) ;
     }
     if ( (names_MET.triggerName(i)).find("Flag_HBHENoiseIsoFilter") != std::string::npos ) {
       passHBHENoiseIsoFilter=triggerBits_MET->accept(i) ;
     }
     if ( (names_MET.triggerName(i)).find("Flag_EcalDeadCellTriggerPrimitiveFilter") != std::string::npos ) {
       passEcalDeadCellTriggerPrimitiveFilter=triggerBits_MET->accept(i) ;
     }
     if ( (names_MET.triggerName(i)).find("Flag_goodVertices") != std::string::npos ) {
       passgoodVertices=triggerBits_MET->accept(i) ;
     }
     if ( (names_MET.triggerName(i)).find("Flag_eeBadScFilter") != std::string::npos ) {
       passeeBadScFilter=triggerBits_MET->accept(i) ;
     }
     if ( (names_MET.triggerName(i)).find("Flag_globalTightHalo2016Filter") != std::string::npos ) {
       passglobalTightHalo2016Filter=triggerBits_MET->accept(i) ;
     }
     if (RunOnData) {
       if ( (names_MET.triggerName(i)).find("Flag_noBadMuons") != std::string::npos ) {
	 NobadMuons=triggerBits_MET->accept(i) ;
       }
     } else if (!RunOnData) {
       NobadMuons=1;
     }
   }
   if (!RunOnData) passeeBadScFilter=1;
   //---MET FILTERS THAT ARE UNAVAILABLE IN MINIAOD AS FLAG---//
   edm::Handle<bool> ifilterbadChCand;
   iEvent.getByToken(BadChCandFilterToken_, ifilterbadChCand);
   bool  filterbadChCandidate = *ifilterbadChCand;
   //   if (filterbadChCandidate<1)   std::cout << "filterbadChCandidate=" << filterbadChCandidate << std::endl;
   edm::Handle<bool> ifilterbadPFMuon;
   iEvent.getByToken(BadPFMuonFilterToken_, ifilterbadPFMuon);
   bool filterbadPFMuon = *ifilterbadPFMuon;
   //  if (filterbadPFMuon<1)   std::cout << "filterbadPFMuon=" << filterbadPFMuon << std::endl;
   //Pass All MET Filters? //
   passAllMETFilters =  passHBHENoiseFilter * passHBHENoiseIsoFilter * passEcalDeadCellTriggerPrimitiveFilter * passgoodVertices * passeeBadScFilter * passglobalTightHalo2016Filter * filterbadChCandidate * filterbadPFMuon * NobadMuons ;
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



   edm::Handle<edm::ValueMap<bool> > ele_id_decisions;
   iEvent.getByToken(eleIdMapToken_ ,ele_id_decisions);

   //   TLorentzVector LooseEle(0,0,0,0);
   int nEle=0;
   //int nEleIDFail=0;
   // float IDfail_ele_pT[10]={0};
   // float IDfail_ele_eta[10]={0};

   iEvent.getByToken(electronToken_, electrons);
   // for (const pat::Electron &el : *electrons) {
   //   std::cout << "\n***********electrons->size() = " << electrons->size() << std::endl;
   for (size_t i = 0; i < electrons->size(); ++i){
     const auto el = electrons->ptrAt(i);
     if (el->pt() < 5) continue;
     //https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2
     //if ( (el.pt()>20) &&  ( abs(el.eta())<2.5 )  && (el.electronID("cutBasedElectronID-Spring15-25ns-V1-standalone-loose")>6) ){
     bool isPassEleId  = (*ele_id_decisions)[el];
     //    std::cout << "pT=" << el->pt() << " eta=" << abs(el->eta()) << " idpass=" << isPassEleId << std::endl;
     if ( (el->pt()>50) && (isPassEleId) ){
       nEle++;
       //printf("elec with pt %4.1f, supercluster eta %+5.3f, sigmaIetaIeta %.3f (%.3f with full5x5 shower shapes)\n",
       //     el->pt(), el->superCluster()->eta(), el->sigmaIetaIeta(), el->full5x5_sigmaIetaIeta());

       break;
       //  IDfail_ele_pT[nEleIDFail]=el->pt();
       //IDfail_ele_eta[nEleIDFail]=el->eta();
       // nEleIDFail++;
     }
   }


   int nMu=0;
   TLorentzVector Muon_sel(0,0,0,0);
   iEvent.getByToken(muonToken_, muons);
   for (const pat::Muon &mu : *muons) {
     //https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2#Tight_Muon
     //     if ( (mu.pt()>20.0) &&  (abs(mu.eta())<2.4) && (mu.isLooseMuon(PV)) &&  ((mu.isolationR03().sumPt/mu.pt())<0.10) ) {
     if ( (mu.pt()>53.0) &&  (abs(mu.eta())<2.4) && ( mu.isHighPtMuon(PV) ) &&  ((mu.isolationR03().sumPt/mu.pt())<0.10) ) {
       Muon_sel.SetPxPyPzE(mu.px(),mu.py(),mu.pz(),mu.energy());
       //    std::cout << "\nmuon pt " << Muon_sel.Pt() << std::endl; 
       nMu++;
       break;
     }
   }

   //   int tau_vis_charge=0;
   // double tau_vis_dxy=0;
   // int tau_vis_nTrack=0;
   // double tau_vis_chIso=0;
   // double tau_vis_neuIso=0;
   //int tau_vis_DM=0;

   int nTau=0;
   int nTau_DM=0;
   int nTau_DM_iso=0;
   int nTau_DM_iso_ele=0;
   int nTau_newDM=0;
   TLorentzVector tau_vis_p4(0,0,0,0);
   //   TLorentzVector tau_vis_p4_newDM(0,0,0,0);
   iEvent.getByToken(tauToken_, taus);
   //
   for (const pat::Tau &tau : *taus) {
     //old,tight_iso,vlooseEle_rej,tightMu_rej
       if ( (PassTauID_DM(tau)==true) ) {
	 nTau_DM++;
	 break;	 
       }
   }
   //
   for (const pat::Tau &tau : *taus) {
     //old,tight_iso,vlooseEle_rej,tightMu_rej
       if ( (PassTauID_DM_iso(tau)==true) ) {
	 nTau_DM_iso++;
	 break;	 
       }
   }
   //
   for (const pat::Tau &tau : *taus) {
     if ( (PassTauID_DM_iso_ele(tau)==true) ) {
	 nTau_DM_iso_ele++;
	 break;	 
       }
   }
   //
   for (const pat::Tau &tau : *taus) {
     //old,tight_iso,vlooseEle_rej,tightMu_rej
       if ( (PassTauID(tau)==true) ) {
     	 tau_vis_p4.SetPxPyPzE(tau.px(),tau.py(),tau.pz(),tau.energy());
	 nTau++;
	 break;	 
       }
     }
   //
   for (const pat::Tau &tau : *taus) {
     //new,tight_iso,vlooseEle_rej,tightMu_rej
     if ( (PassTauID_newDM(tau)==true) ) {
       //	 tau_vis_p4_newDM.SetPxPyPzE(tau.px(),tau.py(),tau.pz(),tau.energy());
       nTau_newDM++;
       break;	 
     }
   }   
    ////// MET //////
   edm::Handle<pat::METCollection> mets;
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

   //   std::cout << "recoil phi = " << recoil_phi << std::endl;

   //-------------------------//
   //**--MET UNCERTAINTIES--**//
   //-------------------------//
   //--JetEnergy Up--//
   /*   double met_val_JetEnUp=met.shiftedPt(pat::MET::JetEnUp);
   double met_phi_JetEnUp=met.shiftedPhi(pat::MET::JetEnUp);
   //--JetEnergy Down--//
   double met_val_JetEnDown=met.shiftedPt(pat::MET::JetEnDown);
   double met_phi_JetEnDown=met.shiftedPhi(pat::MET::JetEnDown);
   //--JetRes Up--//
   double met_val_JetResUp=met.shiftedPt(pat::MET::JetResUp);
   double met_phi_JetResUp=met.shiftedPhi(pat::MET::JetResUp);
   //--JetRes Down--//
   double met_val_JetResDown=met.shiftedPt(pat::MET::JetResDown);
   double met_phi_JetResDown=met.shiftedPhi(pat::MET::JetResDown);
   //--MuonEnergy Up--//
   double met_val_MuonEnUp=met.shiftedPt(pat::MET::MuonEnUp);
   double met_phi_MuonEnUp=met.shiftedPhi(pat::MET::MuonEnUp);
   //--MuonEnergy Down--//
   double met_val_MuonEnDown=met.shiftedPt(pat::MET::MuonEnDown);
   double met_phi_MuonEnDown=met.shiftedPhi(pat::MET::MuonEnDown);
   //--ElectronEnergy Up--//
   double met_val_ElectronEnUp=met.shiftedPt(pat::MET::ElectronEnUp);
   double met_phi_ElectronEnUp=met.shiftedPhi(pat::MET::ElectronEnUp);
   //--ElectronEnergy Down--//
   double met_val_ElectronEnDown=met.shiftedPt(pat::MET::ElectronEnDown);
   double met_phi_ElectronEnDown=met.shiftedPhi(pat::MET::ElectronEnDown);
   //--TauEnergy Up--//
   double met_val_TauEnUp=met.shiftedPt(pat::MET::TauEnUp);
   double met_phi_TauEnUp=met.shiftedPhi(pat::MET::TauEnUp);
   //--TauEnergy Down--//
   double met_val_TauEnDown=met.shiftedPt(pat::MET::TauEnDown);
   double met_phi_TauEnDown=met.shiftedPhi(pat::MET::TauEnDown);
   //--PhotonEnergy Up--//
   double met_val_PhotonEnUp=met.shiftedPt(pat::MET::PhotonEnUp);
   double met_phi_PhotonEnUp=met.shiftedPhi(pat::MET::PhotonEnUp);
   //--PhotonEnergy Down--//
   double met_val_PhotonEnDown=met.shiftedPt(pat::MET::PhotonEnDown);
   double met_phi_PhotonEnDown=met.shiftedPhi(pat::MET::PhotonEnDown);
   //--UnclusteredEnergy Up--//
   double met_val_UnclusteredEnUp=met.shiftedPt(pat::MET::UnclusteredEnUp);
   double met_phi_UnclusteredEnUp=met.shiftedPhi(pat::MET::UnclusteredEnUp);
   //--UnclusteredEnergy Down--//
   double met_val_UnclusteredEnDown=met.shiftedPt(pat::MET::UnclusteredEnDown);
   double met_phi_UnclusteredEnDown=met.shiftedPhi(pat::MET::UnclusteredEnDown);
   */

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
   double mutau_mass=0.0;

  if (passMu50) { 
    h1_EventCount_trg->Fill(1);
    if (passAllMETFilters ) {
      h1_EventCount_trg_filter->Fill(1);
      if ( (nvtx>0) ) { 
	h1_EventCount_trg_filter_vtx->Fill(1);
	if (nMu==1) { 
	  h1_EventCount_trg_filter_vtx_mu->Fill(1);
	  //
	  if (nTau_DM==1) {
	    h1_EventCount_trg_filter_vtx_mu_DM->Fill(1);
	  }
	  //
	  if (nTau_DM_iso==1) {
	    h1_EventCount_trg_filter_vtx_mu_DM_iso->Fill(1);
	  }
	  //
	  if (nTau_DM_iso_ele==1) {
	    h1_EventCount_trg_filter_vtx_mu_DM_iso_ele->Fill(1);
	  }
	  //
	  if ((nTau==1)) {
	    h1_EventCount_trg_filter_vtx_mu_tau->Fill(1);
	    TLorentzVector mutau=(Muon_sel+tau_vis_p4);
	    mutau_mass=mutau.M();
	    //	    std::cout << "mutau mass " << mutau_mass << std::endl;
	    h1_M_Stage1->Fill(mutau_mass,final_weight);
	  }
	  //
	  if ((nTau_newDM==1)) {
	    h1_EventCount_trg_filter_vtx_mu_tau_newDM->Fill(1);
	  }
	  //
	}
      }
    }
  }

   /*
   passMu50=0;
   passTau50MET90=0;
   passMu19Tau20=0;
   passTau140=0;
   passMu50_Tau50MET90=0;
   passMu50_Mu19Tau20=0;
   passMu50_Tau140=0;
   */
  if ((nTau>0) && (nMu>0) ) {
    // std::cout << "Enter Deno" << std::endl;
    h1_EventCount_trigEff_Deno->Fill(1);
  }
  // Numerator //
  if ((nTau>0) && (nMu>0) && passMu50 ) {
    h1_EventCount_trigEff_Mu50_Num->Fill(1);
  }  
  if ((nTau>0) && (nMu>0) && passTau50MET90 ) {
    h1_EventCount_trigEff_Tau50MET90_Num->Fill(1);
  }  
  if ((nTau>0) && (nMu>0) && passMu19Tau20 ) {
    h1_EventCount_trigEff_Mu19Tau20_Num->Fill(1);
  }
  if ((nTau>0) && (nMu>0) && passTau140 ) {
    h1_EventCount_trigEff_Tau140_Num->Fill(1);
  }
  if ((nTau>0) && (nMu>0) && passMu50_Tau50MET90 ) {
    h1_EventCount_trigEff_Mu50_Tau50MET90_Num->Fill(1);
  }
  if ((nTau>0) && (nMu>0) && passMu50_Mu19Tau20 ) {
    h1_EventCount_trigEff_Mu50_Mu19Tau20_Num->Fill(1);
  }
  if ((nTau>0) && (nMu>0) && passMu50_Tau140 ) {
    h1_EventCount_trigEff_Mu50_Tau140_Num->Fill(1);
  }
  

  /*
  ///// ele
  if ((nTau>0) && (nEle>0) ) {
    // std::cout << "Enter Deno" << std::endl;
    h1_EventCount_trigEff_Deno->Fill(1);
  }
  // Numerator //
  if ((nTau>0) && (nEle>0) && passEle27 ) {
    h1_EventCount_trigEff_Ele27_Num->Fill(1);
  }  
  if ((nTau>0) && (nEle>0) && passEle115 ) {
    h1_EventCount_trigEff_Ele115_Num->Fill(1);
  }  
  if ((nTau>0) && (nEle>0) && passPhoton175 ) {
    h1_EventCount_trigEff_Photon175_Num->Fill(1);
  }  
  if ((nTau>0) && (nEle>0) && passElePhoton ) {
    h1_EventCount_trigEff_ElePhoton_Num->Fill(1);
  }  
  if ((nTau>0) && (nEle>0) && passEle27Photon ) {
    h1_EventCount_trigEff_Ele27Photon_Num->Fill(1);
  }  


  */


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

//

bool MiniAODAnalyzer::PassTauID_DM(const pat::Tau &tau)
{
  bool passTauID_=true;
  //----Tau ID----//
  if ( tau.tauID("decayModeFinding") < 0.5 ) passTauID_=false;
  if (tau.pt()<30) passTauID_=false;
  if (fabs(tau.eta())>2.3) passTauID_=false;
  return passTauID_;
 //  return  PassTauID_Old_VLoose(tau);
}

bool MiniAODAnalyzer::PassTauID_DM_iso(const pat::Tau &tau)
{
  bool passTauID_=true;
  //----Tau ID----//
  if ( tau.tauID("decayModeFinding") < 0.5 ) passTauID_=false;
  if ( tau.tauID("byTightIsolationMVArun2v1DBoldDMwLT") < 0.5 ) passTauID_=false;
  if (tau.pt()<30) passTauID_=false;
  if (fabs(tau.eta())>2.3) passTauID_=false;

  return passTauID_;
 //  return  PassTauID_Old_VLoose(tau);
}

bool MiniAODAnalyzer::PassTauID_DM_iso_ele(const pat::Tau &tau)
{
  bool passTauID_=true;
  //----Tau ID----//
  if ( tau.tauID("decayModeFinding") < 0.5 ) passTauID_=false;
  if ( tau.tauID("byTightIsolationMVArun2v1DBoldDMwLT") < 0.5 ) passTauID_=false;
  if ( tau.tauID("againstElectronVLooseMVA6") < 0.5 ) passTauID_=false;
  if (tau.pt()<30) passTauID_=false;
  if (fabs(tau.eta())>2.3) passTauID_=false;

  return passTauID_;
 //  return  PassTauID_Old_VLoose(tau);
}


bool MiniAODAnalyzer::PassTauID_newDM(const pat::Tau &tau)
{
  bool passTauID_=true;
  //----Tau ID----//
  if ( tau.tauID("decayModeFindingNewDMs") < 0.5 ) passTauID_=false;
  if ( tau.tauID("byTightIsolationMVArun2v1DBnewDMwLT") < 0.5 ) passTauID_=false;
  if ( tau.tauID("againstElectronVLooseMVA6") < 0.5 ) passTauID_=false;
  if ( tau.tauID("againstMuonTight3") < 0.5 ) passTauID_=false;
  if (tau.pt()<30) passTauID_=false;
  if (fabs(tau.eta())>2.3) passTauID_=false;

  return passTauID_;
 //  return  PassTauID_Old_VLoose(tau);
}

bool MiniAODAnalyzer::PassTauAcceptance(TLorentzVector tau) // For analysis //
{
  bool passTauAcc_=true;
  //  std::cout << "Inside PassTauAcceptance -> TAU pt=" << tau.Pt() << " energy=" << tau.Energy() << std::endl;
  //----pT----//
  if ( tau.Pt() < 30 ) passTauAcc_=false;

  //----Eta----//
  if ( fabs(tau.PseudoRapidity()) > 2.3 ) passTauAcc_=false;

  return passTauAcc_;
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
