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

#include "TTree.h"
#include "TFile.h"
#include<string>
#include "TH1.h"

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
  //  bool CutBasedLooseEleID(const pat::Electron ele) ; 
  

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;



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

  //------

  TFile*  rootFile_;
  std::string outputFile_; // output file
  TTree* mytree;
  TH1D *h1_TauPt_Stage1;
  TH1D *h1_MT_Stage1;
  
  bool RunOnData=true;
  int Run;
  int Event;
  //  int num_PU_vertices;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

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
  outputFile_(iConfig.getParameter<std::string>("outputFile"))

{
   //now do what ever initialization is needed
  //usesResource("TFileService");
  
  rootFile_   = TFile::Open(outputFile_.c_str(),"RECREATE"); // open output file to store histograms  
  edm::Service<TFileService> fs;

  h1_TauPt_Stage1 = fs->make<TH1D>("tauPt_Stage1", "TauPt_Stage1", 100, 0, 500);
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
  
  //---Clear---//
  Run=0;
  Event=0;
  //num_PU_vertices=0;
  //------//

   Run   = iEvent.id().run();
   Event = iEvent.id().event();
   std::cout << "\n\n --EVENT-- " << Event << std::endl;

   //---Trigger---//
   edm::Handle<edm::TriggerResults> triggerBits;
   edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
   edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;

   iEvent.getByToken(triggerBits_, triggerBits);
   iEvent.getByToken(triggerObjects_, triggerObjects);
   iEvent.getByToken(triggerPrescales_, triggerPrescales);

   const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);

   bool passTauTrig=0;
   
   std::cout << "\n\n === TRIGGER PATHS === " << std::endl;
   for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
       std::cout << "Trigger " << names.triggerName(i) << 
     ", prescale " << triggerPrescales->getPrescaleForIndex(i) <<
     ": " << (triggerBits->accept(i) ? "PASS" : "fail (or not run)") 
     	       << std::endl;
     if ( (names.triggerName(i)).find("HLT_LooseIsoPFTau50_Trk30_eta2p1_MET90") != std::string::npos ) {
       passTauTrig=triggerBits->accept(i) ;
     }
   }
   if (!RunOnData) passTauTrig=1;
   std::cout << "RunOnData=" << RunOnData <<  " ## passTauTrig=" << passTauTrig << std::endl;

   //---Trigger MET---//
   edm::Handle<edm::TriggerResults> triggerBits_MET;
   iEvent.getByToken(triggerBits_MET_, triggerBits_MET);
   const edm::TriggerNames &names_MET = iEvent.triggerNames(*triggerBits_MET);
   bool passHBHENoiseFilter=0;
   std::cout << "\n\n === TRIGGER PATHS (MET) === " << std::endl;
   for (unsigned int i = 0, n = triggerBits_MET->size(); i < n; ++i) {
       std::cout << "Trigger " << names_MET.triggerName(i) << 
         ": " << (triggerBits_MET->accept(i) ? "PASS" : "fail (or not run)") 
     	       << std::endl;
        if ( (names_MET.triggerName(i)).find("Flag_HBHENoiseFilter") != std::string::npos ) {
       passHBHENoiseFilter=triggerBits_MET->accept(i) ;
        }
   }
   //   if (!RunOnData) passTauTrig=1;
   std::cout << "RunOnData=" << RunOnData <<  " ## passHBHENoiseFilter=" << passHBHENoiseFilter << std::endl;




   edm::Handle<reco::VertexCollection> vertices;
   iEvent.getByToken(vtxToken_, vertices);
   if (vertices->empty()) return; // skip the event if no PV found
   std::cout << "Number of vertices " << vertices->size() << std::endl;
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
   std::cout << "Number of good vertices " << nvtx << std::endl;


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


   int nTightMu=0;
   edm::Handle<pat::MuonCollection> muons;
   iEvent.getByToken(muonToken_, muons);
   for (const pat::Muon &mu : *muons) {
     if (mu.isTightMuon(PV)) nTightMu++ ;
     //       printf("muon with pt %4.1f, dz(PV) %+5.3f, POG loose id %d, tight id %d\n",
     //	    mu.pt(), mu.muonBestTrack()->dz(PV.position()), mu.isLooseMuon(), mu.isTightMuon(PV));
   }
   std::cout << "nTightMu=" << nTightMu << std::endl;

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
   std::cout << "nLooseEle=" << nLooseEle << std::endl;   

   edm::Handle<pat::TauCollection> taus;
   int nGoodTau=0;
   double tau_pt=0;
   double tau_phi=-999;
   iEvent.getByToken(tauToken_, taus);
   for (const pat::Tau &tau : *taus) {
     //----pT----//
     tau_pt=tau.pt();
     if ( tau.pt() < 80 ) {
       std::cout << "Do not pass tau pT cut" << std::endl;
       continue;
     }
     //----phi----//
     tau_phi=tau.phi();
     //----Eta----//
     if ( fabs(tau.eta()) > 2.1 ) {
       std::cout << "Do not pass tau eta cut" << std::endl;
       continue;
     }
     //----Tau ID----//
     if ( tau.tauID("decayModeFindingNewDMs") < 0.5 ) {
       std::cout << "Do not pass tau decay Mode Finding discriminator" << std::endl;
       continue;
     }
     if ( tau.tauID("byMediumIsolationMVArun2v1DBnewDMwLT") < 0.5 ) {
       std::cout << "Do not pass tau isolation discriminator" << std::endl;
       continue;
     } 
     if ( tau.tauID("againstElectronLooseMVA6") < 0.5 ) {
       std::cout << "Do not pass Electron rejection discriminator of Tau" << std::endl;
       continue;
     }
     if ( tau.tauID("againstMuonLoose3") < 0.5 ) {
       std::cout << "Do not pass Muon rejection discriminator of Tau" << std::endl;
       continue;
     }
   
     nGoodTau++;
     //printf("tau  with pt %4.1f, dxy signif %.1f, ID(byMediumCombinedIsolationDeltaBetaCorr3Hits) %.1f, lead candidate pt %.1f, pdgId %d \n",
     //	    tau.pt(), tau.dxy_Sig(), tau.tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits"), tau.leadCand()->pt(), tau.leadCand()->pdgId());
   }
   
   std::cout << "nGoodTau=" << nGoodTau << std::endl;
   double dphi_tau_met = deltaPhi(tau_phi,met_phi);
   
   if (passTauTrig && (nvtx>0) && (nGoodTau==1) && (met_val>120) && (nTightMu==0) && (nLooseEle==0) ) {
     double pToverEtMiss=tau_pt/met_val ;
     if (pToverEtMiss>0.7 && pToverEtMiss<1.3) {
       if (dphi_tau_met>2.4) {  
	 std::cout << "Event selected! " << std::endl;
	 h1_TauPt_Stage1->Fill(tau_pt);
	 	 double MT=  sqrt(2*tau_pt*met_val*(1- cos(dphi_tau_met)));
	  std::cout << "MT=" << MT << std::endl;
	  h1_MT_Stage1->Fill(MT);
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


//bool MiniAODAnalyzer::CutBasedLooseEleID(const pat::Electron ele) {
//  bool passLooseID=false;
  
//  return passLooseID;
//}


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
