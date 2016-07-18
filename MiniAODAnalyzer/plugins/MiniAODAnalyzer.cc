// -*- C++ -*-
//
// Package:    WPrimeToTau/MiniAODAnalyzer
// Class:      MiniAODAnalyzer
// 
/**\class MiniAODAnalyzer MiniAODAnalyzer.cc WPrimeToTau/MiniAODAnalyzer/plugins/MiniAODAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Swagata Mukherjee
//         Created:  Tue, 05 Jul 2016 09:41:37 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "DataFormats/Common/interface/RefToPtr.h"

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/MET.h"
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

#include "TTree.h"
#include "TFile.h"
#include<string>
#include "TH1.h"
#include "TLorentzVector.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class MiniAODAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
  explicit MiniAODAnalyzer(const edm::ParameterSet&);
  ~MiniAODAnalyzer();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  bool SelectTau(const pat::Tau &tau);
  bool FindTauIDEfficiency(const edm::Event&,TLorentzVector gen_p4);

  // ----------member data ---------------------------
  edm::EDGetTokenT<reco::VertexCollection> vtxToken_;
  edm::EDGetTokenT<pat::TauCollection> tauToken_;
  edm::EDGetTokenT<pat::MuonCollection> muonToken_;
  edm::EDGetTokenT<pat::ElectronCollection> electronToken_;
  edm::EDGetTokenT<pat::METCollection> metToken_;
  edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
  edm::EDGetTokenT<edm::TriggerResults> triggerBits_MET_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjects_;
  edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescales_;
  // edm::EDGetTokenT<edm::ValueMap<bool> > eleLooseIdMapToken_;
  edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;
  edm::EDGetTokenT<edm::View<pat::PackedGenParticle> > packedGenToken_;
  //------//

  TFile*  rootFile_;
  std::string outputFile_; // output file
  TTree* mytree;
  TH1D *h1_TauPt_Gen;
  TH1I *h1_nGoodTau_Reco;
  TH1I *h1_nGenTau;
  TH1D *h1_TauPt_reco;
  TH1D *h1_TauPt_goodreco;
  TH1D *h1_TauPt_Stage1;
  TH1D *h1_MT_Stage1;
  
  bool RunOnData;
  int Run;
  int Event;
  //  int num_PU_vertices;

};

//
// constructors and destructor
//
MiniAODAnalyzer::MiniAODAnalyzer(const edm::ParameterSet& iConfig):
  vtxToken_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertices"))),
  tauToken_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("taus"))),
  muonToken_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons"))),
  electronToken_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electrons"))),
  metToken_(consumes<pat::METCollection>(iConfig.getParameter<edm::InputTag>("mets"))),
  triggerBits_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits"))),
  triggerBits_MET_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits_MET"))),
  triggerObjects_(consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>("objects"))),
  triggerPrescales_(consumes<pat::PackedTriggerPrescales>(iConfig.getParameter<edm::InputTag>("prescales"))),
  //  eleLooseIdMapToken_(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleLooseIdMap"))),
  prunedGenToken_(consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned"))),
  packedGenToken_(consumes<edm::View<pat::PackedGenParticle> >(iConfig.getParameter<edm::InputTag>("packed"))),
  outputFile_(iConfig.getParameter<std::string>("outputFile")),
  RunOnData(iConfig.getParameter<bool>("RunOnData_"))
{
   //now do what ever initialization is needed
  //usesResource("TFileService");
  
  rootFile_   = TFile::Open(outputFile_.c_str(),"RECREATE"); // open output file to store histograms  
  edm::Service<TFileService> fs;

  h1_nGenTau = fs->make<TH1I>("nGenTau", "nGenTau", 5, -0.5, 4.5);
  h1_nGoodTau_Reco = fs->make<TH1I>("nGoodTauReco", "nGoodTauReco", 5, -0.5, 4.5);
  h1_TauPt_Gen = fs->make<TH1D>("tauPt_Gen", "TauPt_Gen", 100, 0, 1000);
  h1_TauPt_reco = fs->make<TH1D>("tauPt_reco", "TauPt_reco", 50, 0, 1000);
  h1_TauPt_goodreco = fs->make<TH1D>("tauPt_goodreco", "TauPt_goodreco", 50, 0, 1000);
  //h1_TauPt_passID = fs->make<TH1D>("tauPt_passID", "TauPt_passID", 100, 0, 1000);
  h1_TauPt_Stage1 = fs->make<TH1D>("tauPt_Stage1", "TauPt_Stage1", 100, 0, 1000);
  h1_MT_Stage1 = fs->make<TH1D>("mT_Stage1", "MT_Stage1", 1000, 0, 2000);
}


MiniAODAnalyzer::~MiniAODAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
  delete rootFile_;

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MiniAODAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace reco;
  using namespace pat;
  
  //---Clear---//
  Run=0;
  Event=0;
  //num_PU_vertices=0;
  //------//

   Run   = iEvent.id().run();
   Event = iEvent.id().event();
   //  std::cout << "\n\n --EVENT-- " << Event << std::endl;

   int nGenTau=0;
   TLorentzVector tauGen_p4;
   const Candidate * MyTau;
   const Candidate * MyTauSel;

   double TauPt_Gen=0;

   if (!RunOnData) {
     //--GenParticles--//
     Handle<edm::View<reco::GenParticle> > pruned;
     iEvent.getByToken(prunedGenToken_,pruned);
     
     Handle<edm::View<pat::PackedGenParticle> > packed;
     iEvent.getByToken(packedGenToken_,packed);
     
     for(size_t i=0; i<pruned->size();i++){
       if(   (abs((*pruned)[i].pdgId())==15) && ( ((*pruned)[i].status()==2) )) {
	 MyTau = &(*pruned)[i];
	 if (MyTau->pt()>20.0)  {
	   MyTauSel=MyTau;
	   nGenTau++;
	   TauPt_Gen=MyTauSel->pt();
	   // std::cout << " pt " << TauPt_Gen << " nMother=" << MyTau->numberOfMothers() << " mother pdgID = " << MyTau->mother(0)->pdgId() << " mother status = " << MyTau->mother(0)->status()  << std::endl;
	   //  const Candidate * MotherOfMyTau=MyTau->mother(0);
	 }
       }
     }
   }
   //   if ((!RunOnData) && (nGenTau>1))   std::cout << "\n#### #### #### ######### nGenTau=" << nGenTau << std::endl; 
   h1_nGenTau->Fill(nGenTau);
   h1_TauPt_Gen->Fill(TauPt_Gen);
   if (nGenTau==1) tauGen_p4.SetPxPyPzE(MyTauSel->px(),MyTauSel->py(),MyTauSel->pz(),MyTauSel->energy());

   if (nGenTau==1) FindTauIDEfficiency(iEvent,tauGen_p4);

   //---Trigger---//
   edm::Handle<edm::TriggerResults> triggerBits;
   edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
   edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;

   iEvent.getByToken(triggerBits_, triggerBits);
   iEvent.getByToken(triggerObjects_, triggerObjects);
   iEvent.getByToken(triggerPrescales_, triggerPrescales);

   const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);

   bool passTauTrig=0;
   
   //   std::cout << "=== TRIGGER PATHS === " << std::endl;
   for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
     //    std::cout << "Trigger " << names.triggerName(i) << 
     // ", prescale " << triggerPrescales->getPrescaleForIndex(i) <<
     // ": " << (triggerBits->accept(i) ? "PASS" : "fail (or not run)") 
     //	       << std::endl;
     if ( (names.triggerName(i)).find("HLT_LooseIsoPFTau50_Trk30_eta2p1_MET90") != std::string::npos ) {
       passTauTrig=triggerBits->accept(i) ;
     }
   }
   if (!RunOnData) passTauTrig=1;
   // std::cout << "RunOnData=" << RunOnData <<  " ## passTauTrig=" << passTauTrig << std::endl;

   //---Trigger MET---//
   edm::Handle<edm::TriggerResults> triggerBits_MET;
   iEvent.getByToken(triggerBits_MET_, triggerBits_MET);
   const edm::TriggerNames &names_MET = iEvent.triggerNames(*triggerBits_MET);

   bool passHBHENoiseFilter=0;
   bool passHBHENoiseIsoFilter=0;
   bool passEcalDeadCellTriggerPrimitiveFilter=0;
   bool passgoodVertices=0;
   bool passeeBadScFilter=0;
   bool passglobalTightHalo2016Filter=0;

   //   std::cout << " === TRIGGER PATHS (MET) === " << std::endl;
   for (unsigned int i = 0, n = triggerBits_MET->size(); i < n; ++i) {
     //std::cout << "Trigger " << names_MET.triggerName(i) << 
     //  ": " << (triggerBits_MET->accept(i) ? "PASS" : "fail (or not run)") 
     //	       << std::endl;
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
	
   }
   /*
   if (!RunOnData) { 
     passHBHENoiseFilter=1;
     passHBHENoiseIsoFilter=1;
     passEcalDeadCellTriggerPrimitiveFilter=1;
     passgoodVertices=1;
     passeeBadScFilter=1;
     passglobalTightHalo2016Filter=1;
   }
   */
   //   if (!RunOnData) passTauTrig=1;
   //std::cout << "RunOnData=" << RunOnData <<  " ## passHBHENoiseFilter=" << passHBHENoiseFilter 
   // <<  " ## passHBHENoiseIsoFilter=" << passHBHENoiseIsoFilter 
   //	     << " ## passEcalDeadCellTriggerPrimitiveFilter=" << passEcalDeadCellTriggerPrimitiveFilter 
   //	     << " ## passgoodVertices=" << passgoodVertices 
   //	     << " ## passeeBadScFilter=" << passeeBadScFilter 
   //	     << " ## passglobalTightHalo2016Filter=" << passglobalTightHalo2016Filter << std::endl;


   edm::Handle<reco::VertexCollection> vertices;
   iEvent.getByToken(vtxToken_, vertices);
   if (vertices->empty()) return; // skip the event if no PV found
   // std::cout << "Number of vertices " << vertices->size() << std::endl;
   const reco::Vertex &PV = vertices->front();
   reco::VertexCollection vtxs = *vertices;
   
   int nvtx=0;

   if( vertices.isValid() ){
     for( reco::VertexCollection::const_iterator vtx = vtxs.begin(); vtx!=vtxs.end(); ++vtx ) {
       bool isGood = ( (vtx->ndof() >= 4.0) &&
		       (abs(vtx->z()) <= 24.0) &&
		       (abs(vtx->position().Rho()) <= 2.0) 
		       );
       //       std::cout << "vtx->ndof()=" << vtx->ndof() << " ## vtx->z()=" << vtx->z() << " ## vtx->position().Rho()=" << vtx->position().Rho() << std::endl;
       //       std::cout << "Vertex is good? " << isGood << std::endl;
       if( !isGood ) continue;
       nvtx++;
     }
   }
   //   std::cout << "Number of good vertices " << nvtx << std::endl;


   edm::Handle<pat::METCollection> mets;
   double met_val=-999;
   double met_phi=-999;
   iEvent.getByToken(metToken_, mets);
   const pat::MET &met = mets->front();
   met_val=met.pt();
   met_phi=met.phi();
   //   printf("MET: pt %5.1f, phi %+4.2f, sumEt (%.1f). genMET %.1f. MET with JES up/down: %.1f/%.1f\n",
   //	  met.pt(), met.phi(), met.sumEt(),
   //	  met.genMET()->pt(),
   //	  met.shiftedPt(pat::MET::JetEnUp), met.shiftedPt(pat::MET::JetEnDown));
   // std::cout << "MET=" << met_val << std::endl;


   int nTightMu=0;
   edm::Handle<pat::MuonCollection> muons;
   iEvent.getByToken(muonToken_, muons);
   for (const pat::Muon &mu : *muons) {
     if (mu.isTightMuon(PV)) nTightMu++ ;
     //       printf("muon with pt %4.1f, dz(PV) %+5.3f, POG loose id %d, tight id %d\n",
     //	    mu.pt(), mu.muonBestTrack()->dz(PV.position()), mu.isLooseMuon(), mu.isTightMuon(PV));
   }
   //  std::cout << "nTightMu=" << nTightMu << std::endl;


   int nLooseEle=0;
   edm::Handle<pat::ElectronCollection> electrons;
   iEvent.getByToken(electronToken_, electrons);
   //   std::cout << "nEle = " << electrons->size() << std::endl;
   for (const pat::Electron &el : *electrons) {
     //std::cout <<      el.electronIDs().size() << std::endl;
     //std::cout <<      el.electronIDs().front().first << std::endl;
     if (el.pt() < 5) continue;
     if ( el.electronID("cutBasedElectronID-Spring15-25ns-V1-standalone-loose")>6 ) nLooseEle++;
     //printf("elec with pt %4.1f, supercluster eta %+5.3f, sigmaIetaIeta %.3f  ", 
     //		 el.pt(), el.superCluster()->eta(), el.sigmaIetaIeta()  );
   }
   //  std::cout << "nLooseEle=" << nLooseEle << std::endl;   

   edm::Handle<pat::TauCollection> taus;
   int nGoodTau=0;
   double tau_pt[10]={0};
   double tau_phi[10]={0};
   //  double tau_px=0;
   //double tau_py=0;
   //double tau_pz=0;
   //double tau_E=0;
   //TLorentzVector tauGoodReco_p4;
   
   iEvent.getByToken(tauToken_, taus);
  
   for (const pat::Tau &tau : *taus) {
     if (SelectTau(tau)==true) {
       // std::cout << "Tau selected" << std::endl; 
       tau_pt[nGoodTau]=tau.pt();
       tau_phi[nGoodTau]=tau.phi();
       nGoodTau++;
     }
   }
   h1_nGoodTau_Reco->Fill(nGoodTau);
   // std::cout << "nGoodTau=" << nGoodTau << std::endl;

   //-----//

   //---------------//
   //---Selection---//
   //---------------//   
   if (passTauTrig && passHBHENoiseFilter && passHBHENoiseIsoFilter && passEcalDeadCellTriggerPrimitiveFilter && passgoodVertices && passeeBadScFilter && passglobalTightHalo2016Filter) {
     if ( (nvtx>0) && (nGoodTau==1) && (met_val>120) && (nTightMu==0) && (nLooseEle==0) ) {
       double dphi_tau_met = deltaPhi(tau_phi[0],met_phi);
       double pToverEtMiss=tau_pt[0]/met_val ;
       if (pToverEtMiss>0.7 && pToverEtMiss<1.3) {
	 // std::cout << "pToverEtMiss=" << pToverEtMiss << std::endl;
	 if (dphi_tau_met>2.4) {  
	   // std::cout << "dphi_tau_met=" << dphi_tau_met << std::endl;
	   //** Stage1 = final stage (all cuts applied) **//
	   h1_TauPt_Stage1->Fill(tau_pt[0]);
	   double MT=  sqrt(2*tau_pt[0]*met_val*(1- cos(dphi_tau_met)));
	   h1_MT_Stage1->Fill(MT);
	 }
       }
     }
   }
   
   mytree->Fill();
   
   
#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}

bool MiniAODAnalyzer::FindTauIDEfficiency(const edm::Event& iEvent, TLorentzVector gen_p4) {

  edm::Handle<pat::TauCollection> taus;
  iEvent.getByToken(tauToken_, taus);
  TLorentzVector tauReco_p4;
  TLorentzVector tauGoodReco_p4;

  for (const pat::Tau &tau : *taus) {
    tauReco_p4.SetPxPyPzE(tau.px(),tau.py(),tau.pz(),tau.energy());
    double deltaR_tau_gen_reco = gen_p4.DeltaR(tauReco_p4);
    if (deltaR_tau_gen_reco<0.4) {
      h1_TauPt_reco->Fill(tau.pt());
      if (SelectTau(tau)==true) {
	h1_TauPt_goodreco->Fill(tau.pt());
      }
    }
  }
  return true;
}

bool MiniAODAnalyzer::SelectTau(const pat::Tau &tau)
{

  bool passTau=true;
  
  //----pT----//
  if ( tau.pt() < 80 ) passTau=false;
  
  //----Eta----//
  if ( fabs(tau.eta()) > 2.1 ) passTau=false;

  //----Tau ID----//
  if ( tau.tauID("decayModeFindingNewDMs") < 0.5 ) passTau=false;
  if ( tau.tauID("byMediumIsolationMVArun2v1DBnewDMwLT") < 0.5 ) passTau=false;
  if ( tau.tauID("againstElectronLooseMVA6") < 0.5 ) passTau=false;
  if ( tau.tauID("againstMuonLoose3") < 0.5 ) passTau=false;

   return passTau;
}

// ------------ method called once each job just before starting event loop  ------------
void 
MiniAODAnalyzer::beginJob()
{
  rootFile_->cd();
  mytree  = new TTree("tree","tr");

  //----
  mytree->Branch("event_runNo",  &Run,   "event_runNo/I");
  mytree->Branch("event_evtNo",  &Event, "event_evtNo/I");
  //mytree->Branch("num_PU_vertices",&num_PU_vertices,"num_PU_vertices/I");


}

// ------------ method called once each job just after ending the event loop  ------------
void 
MiniAODAnalyzer::endJob() 
{
  rootFile_->cd();
  mytree->Write();
  rootFile_->Close();

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

//define this as a plug-in
DEFINE_FWK_MODULE(MiniAODAnalyzer);
