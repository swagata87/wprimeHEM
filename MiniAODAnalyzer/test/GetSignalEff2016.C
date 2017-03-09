#include <iostream>
#include <algorithm>
#include "TLatex.h"
#include <iomanip>
#include <vector>
#include "TPad.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TSystem.h"
#include "TImage.h"
#include "TKey.h"
#include "TH1.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TObjArray.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TPostScript.h"
#include <TPaveStats.h>
#include "TLegend.h"
#include <TProfile.h>
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "THStack.h"

// kfactor source : https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

int GetSignalEff2016() {

  std::vector<float> mass;
  std::vector<float> sigEff;
  std::vector<float> METfilter_sigEff;
  std::vector<float> nGoodTau_sigEff;
  std::vector<float> MET_sigEff;

  /// Signal ///
 
  TFile *file_Wprime_M400 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M-400_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M400 = (TH1D*)file_Wprime_M400->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M400 = (h1_evt_Wprime_M400->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M400  = (TH1D*)file_Wprime_M400->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M400 : " << ( mT_Stage1_Wprime_M400->GetEntries() / evt_Wprime_M400 ) << std::endl;
  float Eff400= ( mT_Stage1_Wprime_M400->GetEntries() / evt_Wprime_M400 );
  mass.push_back(400);
  sigEff.push_back(Eff400);
  //
  TH1D* mT_METfilter_M400  = (TH1D*)file_Wprime_M400->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff400= ( mT_METfilter_M400->GetEntries() / evt_Wprime_M400 );
  METfilter_sigEff.push_back(METFilter_Eff400);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M400  = (TH1D*)file_Wprime_M400->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff400= ( mT_nGoodTau_M400->GetEntries() / evt_Wprime_M400 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff400);
  //MT_met_val_5
  TH1D* mT_met_val_M400  = (TH1D*)file_Wprime_M400->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff400= ( mT_met_val_M400->GetEntries() / evt_Wprime_M400 );
  MET_sigEff.push_back(met_val_Eff400);


  TFile *file_Wprime_M600 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_600_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M600 = (TH1D*)file_Wprime_M600->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M600 = (h1_evt_Wprime_M600->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M600  = (TH1D*)file_Wprime_M600->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M600 : " << ( mT_Stage1_Wprime_M600->GetEntries() / evt_Wprime_M600 ) << std::endl;
  float Eff600 = ( mT_Stage1_Wprime_M600->GetEntries() / evt_Wprime_M600 );
  mass.push_back(600);
  sigEff.push_back(Eff600);
  //
  TH1D* mT_METfilter_M600  = (TH1D*)file_Wprime_M600->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff600= ( mT_METfilter_M600->GetEntries() / evt_Wprime_M600 );
  METfilter_sigEff.push_back(METFilter_Eff600);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M600  = (TH1D*)file_Wprime_M600->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff600= ( mT_nGoodTau_M600->GetEntries() / evt_Wprime_M600 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff600);
  //MT_met_val_5
  TH1D* mT_met_val_M600  = (TH1D*)file_Wprime_M600->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff600= ( mT_met_val_M600->GetEntries() / evt_Wprime_M600 );
  MET_sigEff.push_back(met_val_Eff600);
 

  TFile *file_Wprime_M1000 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M1000 = (TH1D*)file_Wprime_M1000->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M1000 = (h1_evt_Wprime_M1000->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M1000  = (TH1D*)file_Wprime_M1000->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M1000 : " << ( mT_Stage1_Wprime_M1000->GetEntries() / evt_Wprime_M1000 ) << std::endl;
  float Eff1000 = ( mT_Stage1_Wprime_M1000->GetEntries() / evt_Wprime_M1000 );
  mass.push_back(1000);
  sigEff.push_back(Eff1000);
  //
  TH1D* mT_METfilter_M1000  = (TH1D*)file_Wprime_M1000->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff1000= ( mT_METfilter_M1000->GetEntries() / evt_Wprime_M1000 );
  METfilter_sigEff.push_back(METFilter_Eff1000);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M1000  = (TH1D*)file_Wprime_M1000->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff1000= ( mT_nGoodTau_M1000->GetEntries() / evt_Wprime_M1000 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff1000);
  //MT_met_val_5
  TH1D* mT_met_val_M1000  = (TH1D*)file_Wprime_M1000->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff1000= ( mT_met_val_M1000->GetEntries() / evt_Wprime_M1000 );
  MET_sigEff.push_back(met_val_Eff1000);

 
  TFile *file_Wprime_M1200 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_1200_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M1200 = (TH1D*)file_Wprime_M1200->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M1200 = (h1_evt_Wprime_M1200->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M1200  = (TH1D*)file_Wprime_M1200->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M1200 : " << ( mT_Stage1_Wprime_M1200->GetEntries() / evt_Wprime_M1200 ) << std::endl;
  float Eff1200 = ( mT_Stage1_Wprime_M1200->GetEntries() / evt_Wprime_M1200 );
  mass.push_back(1200);
  sigEff.push_back(Eff1200);
  //
  TH1D* mT_METfilter_M1200  = (TH1D*)file_Wprime_M1200->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff1200= ( mT_METfilter_M1200->GetEntries() / evt_Wprime_M1200 );
  METfilter_sigEff.push_back(METFilter_Eff1200);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M1200  = (TH1D*)file_Wprime_M1200->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff1200= ( mT_nGoodTau_M1200->GetEntries() / evt_Wprime_M1200 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff1200);
  //MT_met_val_5
  TH1D* mT_met_val_M1200  = (TH1D*)file_Wprime_M1200->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff1200= ( mT_met_val_M1200->GetEntries() / evt_Wprime_M1200 );
  MET_sigEff.push_back(met_val_Eff1200);



  TFile *file_Wprime_M1400 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_1400_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M1400 = (TH1D*)file_Wprime_M1400->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M1400 = (h1_evt_Wprime_M1400->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M1400  = (TH1D*)file_Wprime_M1400->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M1400 : " << ( mT_Stage1_Wprime_M1400->GetEntries() / evt_Wprime_M1400 ) << std::endl;
  float Eff1400 = ( mT_Stage1_Wprime_M1400->GetEntries() / evt_Wprime_M1400 );
  mass.push_back(1400);
  sigEff.push_back(Eff1400);
  //
  TH1D* mT_METfilter_M1400  = (TH1D*)file_Wprime_M1400->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff1400= ( mT_METfilter_M1400->GetEntries() / evt_Wprime_M1400 );
  METfilter_sigEff.push_back(METFilter_Eff1400);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M1400  = (TH1D*)file_Wprime_M1400->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff1400= ( mT_nGoodTau_M1400->GetEntries() / evt_Wprime_M1400 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff1400);
  //MT_met_val_5
  TH1D* mT_met_val_M1400  = (TH1D*)file_Wprime_M1400->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff1400= ( mT_met_val_M1400->GetEntries() / evt_Wprime_M1400 );
  MET_sigEff.push_back(met_val_Eff1400);



  TFile *file_Wprime_M1600 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_1600_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M1600 = (TH1D*)file_Wprime_M1600->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M1600 = (h1_evt_Wprime_M1600->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M1600  = (TH1D*)file_Wprime_M1600->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M1600 : " << ( mT_Stage1_Wprime_M1600->GetEntries() / evt_Wprime_M1600 ) << std::endl;
  float Eff1600 = ( mT_Stage1_Wprime_M1600->GetEntries() / evt_Wprime_M1600 );
  mass.push_back(1600);
  sigEff.push_back(Eff1600);
  //
  TH1D* mT_METfilter_M1600  = (TH1D*)file_Wprime_M1600->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff1600= ( mT_METfilter_M1600->GetEntries() / evt_Wprime_M1600 );
  METfilter_sigEff.push_back(METFilter_Eff1600);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M1600  = (TH1D*)file_Wprime_M1600->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff1600= ( mT_nGoodTau_M1600->GetEntries() / evt_Wprime_M1600 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff1600);
  //MT_met_val_5
  TH1D* mT_met_val_M1600  = (TH1D*)file_Wprime_M1600->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff1600= ( mT_met_val_M1600->GetEntries() / evt_Wprime_M1600 );
  MET_sigEff.push_back(met_val_Eff1600);



  TFile *file_Wprime_M1800 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_1800_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M1800 = (TH1D*)file_Wprime_M1800->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M1800 = (h1_evt_Wprime_M1800->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M1800  = (TH1D*)file_Wprime_M1800->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M1800 : " << ( mT_Stage1_Wprime_M1800->GetEntries() / evt_Wprime_M1800 ) << std::endl;
  float Eff1800 = ( mT_Stage1_Wprime_M1800->GetEntries() / evt_Wprime_M1800 );
  mass.push_back(1800);
  sigEff.push_back(Eff1800);
  //
  TH1D* mT_METfilter_M1800  = (TH1D*)file_Wprime_M1800->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff1800= ( mT_METfilter_M1800->GetEntries() / evt_Wprime_M1800 );
  METfilter_sigEff.push_back(METFilter_Eff1800);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M1800  = (TH1D*)file_Wprime_M1800->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff1800= ( mT_nGoodTau_M1800->GetEntries() / evt_Wprime_M1800 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff1800);
  //MT_met_val_5
  TH1D* mT_met_val_M1800  = (TH1D*)file_Wprime_M1800->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff1800= ( mT_met_val_M1800->GetEntries() / evt_Wprime_M1800 );
  MET_sigEff.push_back(met_val_Eff1800);
 

  
  TFile *file_Wprime_M2000 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M-2000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M2000 = (TH1D*)file_Wprime_M2000->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M2000 = (h1_evt_Wprime_M2000->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M2000  = (TH1D*)file_Wprime_M2000->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M2000 : " << ( mT_Stage1_Wprime_M2000->GetEntries() / evt_Wprime_M2000 ) << std::endl;
  float Eff2000 = ( mT_Stage1_Wprime_M2000->GetEntries() / evt_Wprime_M2000 );
  mass.push_back(2000);
  sigEff.push_back(Eff2000);
  //
  TH1D* mT_METfilter_M2000  = (TH1D*)file_Wprime_M2000->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff2000= ( mT_METfilter_M2000->GetEntries() / evt_Wprime_M2000 );
  METfilter_sigEff.push_back(METFilter_Eff2000);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M2000  = (TH1D*)file_Wprime_M2000->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff2000= ( mT_nGoodTau_M2000->GetEntries() / evt_Wprime_M2000 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff2000);
  //MT_met_val_5
  TH1D* mT_met_val_M2000  = (TH1D*)file_Wprime_M2000->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff2000= ( mT_met_val_M2000->GetEntries() / evt_Wprime_M2000 );
  MET_sigEff.push_back(met_val_Eff2000);

  
 
  TFile *file_Wprime_M2200 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_2200_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M2200 = (TH1D*)file_Wprime_M2200->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M2200 = (h1_evt_Wprime_M2200->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M2200  = (TH1D*)file_Wprime_M2200->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M2200 : " << ( mT_Stage1_Wprime_M2200->GetEntries() / evt_Wprime_M2200 ) << std::endl;
  float Eff2200 = ( mT_Stage1_Wprime_M2200->GetEntries() / evt_Wprime_M2200 );
  mass.push_back(2200);
  sigEff.push_back(Eff2200);
  //
  TH1D* mT_METfilter_M2200  = (TH1D*)file_Wprime_M2200->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff2200= ( mT_METfilter_M2200->GetEntries() / evt_Wprime_M2200 );
  METfilter_sigEff.push_back(METFilter_Eff2200);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M2200  = (TH1D*)file_Wprime_M2200->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff2200= ( mT_nGoodTau_M2200->GetEntries() / evt_Wprime_M2200 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff2200);
  //MT_met_val_5
  TH1D* mT_met_val_M2200  = (TH1D*)file_Wprime_M2200->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff2200= ( mT_met_val_M2200->GetEntries() / evt_Wprime_M2200 );
  MET_sigEff.push_back(met_val_Eff2200);

  

  TFile *file_Wprime_M2400 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_2400_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M2400 = (TH1D*)file_Wprime_M2400->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M2400 = (h1_evt_Wprime_M2400->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M2400  = (TH1D*)file_Wprime_M2400->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M2400 : " << ( mT_Stage1_Wprime_M2400->GetEntries() / evt_Wprime_M2400 ) << std::endl;
  float Eff2400 = ( mT_Stage1_Wprime_M2400->GetEntries() / evt_Wprime_M2400 );
  mass.push_back(2400);
  sigEff.push_back(Eff2400);
  //
  TH1D* mT_METfilter_M2400  = (TH1D*)file_Wprime_M2400->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff2400= ( mT_METfilter_M2400->GetEntries() / evt_Wprime_M2400 );
  METfilter_sigEff.push_back(METFilter_Eff2400);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M2400  = (TH1D*)file_Wprime_M2400->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff2400= ( mT_nGoodTau_M2400->GetEntries() / evt_Wprime_M2400 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff2400);
  //MT_met_val_5
  TH1D* mT_met_val_M2400  = (TH1D*)file_Wprime_M2400->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff2400= ( mT_met_val_M2400->GetEntries() / evt_Wprime_M2400 );
  MET_sigEff.push_back(met_val_Eff2400);



  TFile *file_Wprime_M2600 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_2600_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M2600 = (TH1D*)file_Wprime_M2600->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M2600 = (h1_evt_Wprime_M2600->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M2600  = (TH1D*)file_Wprime_M2600->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M2600 : " << ( mT_Stage1_Wprime_M2600->GetEntries() / evt_Wprime_M2600 ) << std::endl;
  float Eff2600 = ( mT_Stage1_Wprime_M2600->GetEntries() / evt_Wprime_M2600 );
  mass.push_back(2600);
  sigEff.push_back(Eff2600);
  //
  TH1D* mT_METfilter_M2600  = (TH1D*)file_Wprime_M2600->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff2600= ( mT_METfilter_M2600->GetEntries() / evt_Wprime_M2600 );
  METfilter_sigEff.push_back(METFilter_Eff2600);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M2600  = (TH1D*)file_Wprime_M2600->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff2600= ( mT_nGoodTau_M2600->GetEntries() / evt_Wprime_M2600 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff2600);
  //MT_met_val_5
  TH1D* mT_met_val_M2600  = (TH1D*)file_Wprime_M2600->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff2600= ( mT_met_val_M2600->GetEntries() / evt_Wprime_M2600 );
  MET_sigEff.push_back(met_val_Eff2600);



  TFile *file_Wprime_M2800 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_2800_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M2800 = (TH1D*)file_Wprime_M2800->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M2800 = (h1_evt_Wprime_M2800->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M2800  = (TH1D*)file_Wprime_M2800->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M2800 : " << ( mT_Stage1_Wprime_M2800->GetEntries() / evt_Wprime_M2800 ) << std::endl;
  float Eff2800 = ( mT_Stage1_Wprime_M2800->GetEntries() / evt_Wprime_M2800 );
  mass.push_back(2800);
  sigEff.push_back(Eff2800);
  //
  TH1D* mT_METfilter_M2800  = (TH1D*)file_Wprime_M2800->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff2800= ( mT_METfilter_M2800->GetEntries() / evt_Wprime_M2800 );
  METfilter_sigEff.push_back(METFilter_Eff2800);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M2800  = (TH1D*)file_Wprime_M2800->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff2800= ( mT_nGoodTau_M2800->GetEntries() / evt_Wprime_M2800 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff2800);
  //MT_met_val_5
  TH1D* mT_met_val_M2800  = (TH1D*)file_Wprime_M2800->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff2800= ( mT_met_val_M2800->GetEntries() / evt_Wprime_M2800 );
  MET_sigEff.push_back(met_val_Eff2800);


 
  TFile *file_Wprime_M3000 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M-3000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M3000 = (TH1D*)file_Wprime_M3000->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M3000 = (h1_evt_Wprime_M3000->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M3000  = (TH1D*)file_Wprime_M3000->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M3000 : " << ( mT_Stage1_Wprime_M3000->GetEntries() / evt_Wprime_M3000 ) << std::endl;
  float Eff3000 = ( mT_Stage1_Wprime_M3000->GetEntries() / evt_Wprime_M3000 );
  mass.push_back(3000);
  sigEff.push_back(Eff3000);
  //
  TH1D* mT_METfilter_M3000  = (TH1D*)file_Wprime_M3000->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff3000= ( mT_METfilter_M3000->GetEntries() / evt_Wprime_M3000 );
  METfilter_sigEff.push_back(METFilter_Eff3000);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M3000  = (TH1D*)file_Wprime_M3000->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff3000= ( mT_nGoodTau_M3000->GetEntries() / evt_Wprime_M3000 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff3000);
  //MT_met_val_5
  TH1D* mT_met_val_M3000  = (TH1D*)file_Wprime_M3000->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff3000= ( mT_met_val_M3000->GetEntries() / evt_Wprime_M3000 );
  MET_sigEff.push_back(met_val_Eff3000);

 
  TFile *file_Wprime_M3200 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_3200_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M3200 = (TH1D*)file_Wprime_M3200->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M3200 = (h1_evt_Wprime_M3200->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M3200  = (TH1D*)file_Wprime_M3200->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M3200 : " << ( mT_Stage1_Wprime_M3200->GetEntries() / evt_Wprime_M3200 ) << std::endl;
  float Eff3200 = ( mT_Stage1_Wprime_M3200->GetEntries() / evt_Wprime_M3200 );
  mass.push_back(3200);
  sigEff.push_back(Eff3200);
  //
  TH1D* mT_METfilter_M3200  = (TH1D*)file_Wprime_M3200->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff3200= ( mT_METfilter_M3200->GetEntries() / evt_Wprime_M3200 );
  METfilter_sigEff.push_back(METFilter_Eff3200);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M3200  = (TH1D*)file_Wprime_M3200->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff3200= ( mT_nGoodTau_M3200->GetEntries() / evt_Wprime_M3200 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff3200);
  //MT_met_val_5
  TH1D* mT_met_val_M3200  = (TH1D*)file_Wprime_M3200->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff3200= ( mT_met_val_M3200->GetEntries() / evt_Wprime_M3200 );
  MET_sigEff.push_back(met_val_Eff3200);


  
  TFile *file_Wprime_M3400 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_3400_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M3400 = (TH1D*)file_Wprime_M3400->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M3400 = (h1_evt_Wprime_M3400->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M3400  = (TH1D*)file_Wprime_M3400->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M3400 : " << ( mT_Stage1_Wprime_M3400->GetEntries() / evt_Wprime_M3400 ) << std::endl;
  float Eff3400 = ( mT_Stage1_Wprime_M3400->GetEntries() / evt_Wprime_M3400 );
  mass.push_back(3400);
  sigEff.push_back(Eff3400);
  //
  TH1D* mT_METfilter_M3400  = (TH1D*)file_Wprime_M3400->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff3400= ( mT_METfilter_M3400->GetEntries() / evt_Wprime_M3400 );
  METfilter_sigEff.push_back(METFilter_Eff3400);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M3400  = (TH1D*)file_Wprime_M3400->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff3400= ( mT_nGoodTau_M3400->GetEntries() / evt_Wprime_M3400 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff3400);
  //MT_met_val_5
  TH1D* mT_met_val_M3400  = (TH1D*)file_Wprime_M3400->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff3400= ( mT_met_val_M3400->GetEntries() / evt_Wprime_M3400 );
  MET_sigEff.push_back(met_val_Eff3400);


 
  TFile *file_Wprime_M3600 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_3600_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M3600 = (TH1D*)file_Wprime_M3600->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M3600 = (h1_evt_Wprime_M3600->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M3600  = (TH1D*)file_Wprime_M3600->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M3600 : " << ( mT_Stage1_Wprime_M3600->GetEntries() / evt_Wprime_M3600 ) << std::endl;
  float Eff3600 = ( mT_Stage1_Wprime_M3600->GetEntries() / evt_Wprime_M3600 );
  mass.push_back(3600);
  sigEff.push_back(Eff3600);
  //
  TH1D* mT_METfilter_M3600  = (TH1D*)file_Wprime_M3600->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff3600= ( mT_METfilter_M3600->GetEntries() / evt_Wprime_M3600 );
  METfilter_sigEff.push_back(METFilter_Eff3600);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M3600  = (TH1D*)file_Wprime_M3600->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff3600= ( mT_nGoodTau_M3600->GetEntries() / evt_Wprime_M3600 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff3600);
  //MT_met_val_5
  TH1D* mT_met_val_M3600  = (TH1D*)file_Wprime_M3600->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff3600= ( mT_met_val_M3600->GetEntries() / evt_Wprime_M3600 );
  MET_sigEff.push_back(met_val_Eff3600);



  TFile *file_Wprime_M3800 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_3800_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M3800 = (TH1D*)file_Wprime_M3800->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M3800 = (h1_evt_Wprime_M3800->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M3800  = (TH1D*)file_Wprime_M3800->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M3800 : " << ( mT_Stage1_Wprime_M3800->GetEntries() / evt_Wprime_M3800 ) << std::endl;
  float Eff3800 = ( mT_Stage1_Wprime_M3800->GetEntries() / evt_Wprime_M3800 );
  mass.push_back(3800);
  sigEff.push_back(Eff3800);
  //
  TH1D* mT_METfilter_M3800  = (TH1D*)file_Wprime_M3800->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff3800= ( mT_METfilter_M3800->GetEntries() / evt_Wprime_M3800 );
  METfilter_sigEff.push_back(METFilter_Eff3800);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M3800  = (TH1D*)file_Wprime_M3800->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff3800= ( mT_nGoodTau_M3800->GetEntries() / evt_Wprime_M3800 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff3800);
  //MT_met_val_5
  TH1D* mT_met_val_M3800  = (TH1D*)file_Wprime_M3800->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff3800= ( mT_met_val_M3800->GetEntries() / evt_Wprime_M3800 );
  MET_sigEff.push_back(met_val_Eff3800);
 


  TFile *file_Wprime_M4000 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M-4000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M4000 = (TH1D*)file_Wprime_M4000->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M4000 = (h1_evt_Wprime_M4000->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M4000  = (TH1D*)file_Wprime_M4000->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M4000 : " << ( mT_Stage1_Wprime_M4000->GetEntries() / evt_Wprime_M4000 ) << std::endl;
  float Eff4000 = ( mT_Stage1_Wprime_M4000->GetEntries() / evt_Wprime_M4000 );
  mass.push_back(4000);
  sigEff.push_back(Eff4000);
  //
  TH1D* mT_METfilter_M4000  = (TH1D*)file_Wprime_M4000->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff4000= ( mT_METfilter_M4000->GetEntries() / evt_Wprime_M4000 );
  METfilter_sigEff.push_back(METFilter_Eff4000);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M4000  = (TH1D*)file_Wprime_M4000->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff4000= ( mT_nGoodTau_M4000->GetEntries() / evt_Wprime_M4000 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff4000);
  //MT_met_val_5
  TH1D* mT_met_val_M4000  = (TH1D*)file_Wprime_M4000->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff4000= ( mT_met_val_M4000->GetEntries() / evt_Wprime_M4000 );
  MET_sigEff.push_back(met_val_Eff4000);

 
 
  TFile *file_Wprime_M4200 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_4200_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M4200 = (TH1D*)file_Wprime_M4200->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M4200 = (h1_evt_Wprime_M4200->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M4200  = (TH1D*)file_Wprime_M4200->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M4200 : " << ( mT_Stage1_Wprime_M4200->GetEntries() / evt_Wprime_M4200 ) << std::endl;
  float Eff4200 = ( mT_Stage1_Wprime_M4200->GetEntries() / evt_Wprime_M4200 );
  mass.push_back(4200);
  sigEff.push_back(Eff4200);
  //
  TH1D* mT_METfilter_M4200  = (TH1D*)file_Wprime_M4200->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff4200= ( mT_METfilter_M4200->GetEntries() / evt_Wprime_M4200 );
  METfilter_sigEff.push_back(METFilter_Eff4200);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M4200  = (TH1D*)file_Wprime_M4200->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff4200= ( mT_nGoodTau_M4200->GetEntries() / evt_Wprime_M4200 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff4200);
  //MT_met_val_5
  TH1D* mT_met_val_M4200  = (TH1D*)file_Wprime_M4200->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff4200= ( mT_met_val_M4200->GetEntries() / evt_Wprime_M4200 );
  MET_sigEff.push_back(met_val_Eff4200);

 

  TFile *file_Wprime_M4400 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_4400_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M4400 = (TH1D*)file_Wprime_M4400->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M4400 = (h1_evt_Wprime_M4400->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M4400  = (TH1D*)file_Wprime_M4400->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M4400 : " << ( mT_Stage1_Wprime_M4400->GetEntries() / evt_Wprime_M4400 ) << std::endl;
  float Eff4400 = ( mT_Stage1_Wprime_M4400->GetEntries() / evt_Wprime_M4400 );
  mass.push_back(4400);
  sigEff.push_back(Eff4400);
  //
  TH1D* mT_METfilter_M4400  = (TH1D*)file_Wprime_M4400->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff4400= ( mT_METfilter_M4400->GetEntries() / evt_Wprime_M4400 );
  METfilter_sigEff.push_back(METFilter_Eff4400);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M4400  = (TH1D*)file_Wprime_M4400->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff4400= ( mT_nGoodTau_M4400->GetEntries() / evt_Wprime_M4400 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff4400);
  //MT_met_val_5
  TH1D* mT_met_val_M4400  = (TH1D*)file_Wprime_M4400->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff4400= ( mT_met_val_M4400->GetEntries() / evt_Wprime_M4400 );
  MET_sigEff.push_back(met_val_Eff4400);


 
  TFile *file_Wprime_M4600 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_4600_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M4600 = (TH1D*)file_Wprime_M4600->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M4600 = (h1_evt_Wprime_M4600->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M4600  = (TH1D*)file_Wprime_M4600->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M4600 : " << ( mT_Stage1_Wprime_M4600->GetEntries() / evt_Wprime_M4600 ) << std::endl;
  float Eff4600 = ( mT_Stage1_Wprime_M4600->GetEntries() / evt_Wprime_M4600 );
  mass.push_back(4600);
  sigEff.push_back(Eff4600);
  //
  TH1D* mT_METfilter_M4600  = (TH1D*)file_Wprime_M4600->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff4600= ( mT_METfilter_M4600->GetEntries() / evt_Wprime_M4600 );
  METfilter_sigEff.push_back(METFilter_Eff4600);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M4600  = (TH1D*)file_Wprime_M4600->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff4600= ( mT_nGoodTau_M4600->GetEntries() / evt_Wprime_M4600 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff4600);
  //MT_met_val_5
  TH1D* mT_met_val_M4600  = (TH1D*)file_Wprime_M4600->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff4600= ( mT_met_val_M4600->GetEntries() / evt_Wprime_M4600 );
  MET_sigEff.push_back(met_val_Eff4600);

 

  TFile *file_Wprime_M4800 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_4800_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M4800 = (TH1D*)file_Wprime_M4800->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M4800 = (h1_evt_Wprime_M4800->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M4800  = (TH1D*)file_Wprime_M4800->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M4800 : " << ( mT_Stage1_Wprime_M4800->GetEntries() / evt_Wprime_M4800 ) << std::endl;
  float Eff4800 = ( mT_Stage1_Wprime_M4800->GetEntries() / evt_Wprime_M4800 );
  mass.push_back(4800);
  sigEff.push_back(Eff4800);
  //
  TH1D* mT_METfilter_M4800  = (TH1D*)file_Wprime_M4800->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff4800= ( mT_METfilter_M4800->GetEntries() / evt_Wprime_M4800 );
  METfilter_sigEff.push_back(METFilter_Eff4800);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M4800  = (TH1D*)file_Wprime_M4800->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff4800= ( mT_nGoodTau_M4800->GetEntries() / evt_Wprime_M4800 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff4800);
  //MT_met_val_5
  TH1D* mT_met_val_M4800  = (TH1D*)file_Wprime_M4800->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff4800= ( mT_met_val_M4800->GetEntries() / evt_Wprime_M4800 );
  MET_sigEff.push_back(met_val_Eff4800);

 
  TFile *file_Wprime_M5000 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M-5000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M5000 = (TH1D*)file_Wprime_M5000->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M5000 = (h1_evt_Wprime_M5000->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M5000  = (TH1D*)file_Wprime_M5000->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M5000 : " << ( mT_Stage1_Wprime_M5000->GetEntries() / evt_Wprime_M5000 ) << std::endl;
  float Eff5000 = ( mT_Stage1_Wprime_M5000->GetEntries() / evt_Wprime_M5000 );
  mass.push_back(5000);
  sigEff.push_back(Eff5000);
  //
  TH1D* mT_METfilter_M5000  = (TH1D*)file_Wprime_M5000->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff5000= ( mT_METfilter_M5000->GetEntries() / evt_Wprime_M5000 );
  METfilter_sigEff.push_back(METFilter_Eff5000);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M5000  = (TH1D*)file_Wprime_M5000->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff5000= ( mT_nGoodTau_M5000->GetEntries() / evt_Wprime_M5000 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff5000);
  //MT_met_val_5
  TH1D* mT_met_val_M5000  = (TH1D*)file_Wprime_M5000->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff5000= ( mT_met_val_M5000->GetEntries() / evt_Wprime_M5000 );
  MET_sigEff.push_back(met_val_Eff5000);


 
  TFile *file_Wprime_M5200 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_5200_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M5200 = (TH1D*)file_Wprime_M5200->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M5200 = (h1_evt_Wprime_M5200->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M5200  = (TH1D*)file_Wprime_M5200->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M5200 : " << ( mT_Stage1_Wprime_M5200->GetEntries() / evt_Wprime_M5200 ) << std::endl;
  float Eff5200 = ( mT_Stage1_Wprime_M5200->GetEntries() / evt_Wprime_M5200 );
  mass.push_back(5200);
  sigEff.push_back(Eff5200);
  //
  TH1D* mT_METfilter_M5200  = (TH1D*)file_Wprime_M5200->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff5200= ( mT_METfilter_M5200->GetEntries() / evt_Wprime_M5200 );
  METfilter_sigEff.push_back(METFilter_Eff5200);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M5200  = (TH1D*)file_Wprime_M5200->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff5200= ( mT_nGoodTau_M5200->GetEntries() / evt_Wprime_M5200 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff5200);
  //MT_met_val_5
  TH1D* mT_met_val_M5200  = (TH1D*)file_Wprime_M5200->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff5200= ( mT_met_val_M5200->GetEntries() / evt_Wprime_M5200 );
  MET_sigEff.push_back(met_val_Eff5200);

  

  TFile *file_Wprime_M5400 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_5400_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M5400 = (TH1D*)file_Wprime_M5400->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M5400 = (h1_evt_Wprime_M5400->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M5400  = (TH1D*)file_Wprime_M5400->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M5400 : " << ( mT_Stage1_Wprime_M5400->GetEntries() / evt_Wprime_M5400 ) << std::endl;
  float Eff5400 = ( mT_Stage1_Wprime_M5400->GetEntries() / evt_Wprime_M5400 );
  mass.push_back(5400);
  sigEff.push_back(Eff5400);
  //
  TH1D* mT_METfilter_M5400  = (TH1D*)file_Wprime_M5400->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff5400= ( mT_METfilter_M5400->GetEntries() / evt_Wprime_M5400 );
  METfilter_sigEff.push_back(METFilter_Eff5400);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M5400  = (TH1D*)file_Wprime_M5400->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff5400= ( mT_nGoodTau_M5400->GetEntries() / evt_Wprime_M5400 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff5400);
  //MT_met_val_5
  TH1D* mT_met_val_M5400  = (TH1D*)file_Wprime_M5400->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff5400= ( mT_met_val_M5400->GetEntries() / evt_Wprime_M5400 );
  MET_sigEff.push_back(met_val_Eff5400);


 
  TFile *file_Wprime_M5600 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_5600_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M5600 = (TH1D*)file_Wprime_M5600->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M5600 = (h1_evt_Wprime_M5600->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M5600  = (TH1D*)file_Wprime_M5600->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M5600 : " << ( mT_Stage1_Wprime_M5600->GetEntries() / evt_Wprime_M5600 ) << std::endl;
  float Eff5600 = ( mT_Stage1_Wprime_M5600->GetEntries() / evt_Wprime_M5600 );
  mass.push_back(5600);
  sigEff.push_back(Eff5600);
  //
  TH1D* mT_METfilter_M5600  = (TH1D*)file_Wprime_M5600->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff5600= ( mT_METfilter_M5600->GetEntries() / evt_Wprime_M5600 );
  METfilter_sigEff.push_back(METFilter_Eff5600);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M5600  = (TH1D*)file_Wprime_M5600->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff5600= ( mT_nGoodTau_M5600->GetEntries() / evt_Wprime_M5600 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff5600);
  //MT_met_val_5
  TH1D* mT_met_val_M5600  = (TH1D*)file_Wprime_M5600->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff5600= ( mT_met_val_M5600->GetEntries() / evt_Wprime_M5600 );
  MET_sigEff.push_back(met_val_Eff5600);

 

  TFile *file_Wprime_M5800 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_5800_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M5800 = (TH1D*)file_Wprime_M5800->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M5800 = (h1_evt_Wprime_M5800->GetEntries())*0.68; //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M5800  = (TH1D*)file_Wprime_M5800->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M5800 : " << ( mT_Stage1_Wprime_M5800->GetEntries() / evt_Wprime_M5800 ) << std::endl;
  float Eff5800 = ( mT_Stage1_Wprime_M5800->GetEntries() / evt_Wprime_M5800 );
  mass.push_back(5800);
  sigEff.push_back(Eff5800);
  //
  TH1D* mT_METfilter_M5800  = (TH1D*)file_Wprime_M5800->Get("demo/histoDir/MT_passAllMETFilters_2");
  float METFilter_Eff5800= ( mT_METfilter_M5800->GetEntries() / evt_Wprime_M5800 );
  METfilter_sigEff.push_back(METFilter_Eff5800);
  // MT_nGoodTau_4
  TH1D* mT_nGoodTau_M5800  = (TH1D*)file_Wprime_M5800->Get("demo/histoDir/MT_nGoodTau_4");
  float nGoodTau_Eff5800= ( mT_nGoodTau_M5800->GetEntries() / evt_Wprime_M5800 );
  nGoodTau_sigEff.push_back(nGoodTau_Eff5800);
  //MT_met_val_5
  TH1D* mT_met_val_M5800  = (TH1D*)file_Wprime_M5800->Get("demo/histoDir/MT_met_val_5");
  float met_val_Eff5800= ( mT_met_val_M5800->GetEntries() / evt_Wprime_M5800 );
  MET_sigEff.push_back(met_val_Eff5800);

 
  //--Plotting Styles//
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.12);  
  gStyle->SetPadTopMargin(0.05);   
  gStyle->SetTitleXSize(0.05);
  gStyle->SetTitleXOffset(1.05);
  gStyle->SetTitleYSize(0.05);
  gStyle->SetTitleYOffset(1.05);

  //////// Output File /////////
  //  TFile* outputFile = new TFile("Out_SigEff.root","RECREATE");
  // outputFile->cd();

  //fill your vectors
  TGraph g(mass.size(), &(mass[0]), &(sigEff[0]));
  g.SetLineColor(2); 
  g.SetLineWidth(4);
  g.SetMarkerColor(4);
  g.SetMarkerStyle(21);
  g.SetMaximum(0.8);
  g.SetTitle(" ");
  g.GetXaxis()->SetTitle("M(W') in GeV");
  g.GetYaxis()->SetTitle("Signal Efficiency");
  g.GetXaxis()->SetLimits(800,6000);

  //METfilter_sigEff
  TGraph g1(mass.size(), &(mass[0]), &(METfilter_sigEff[0]));
  g1.SetLineColor(2);
  g1.SetLineWidth(4);
  g1.SetMarkerColor(2);
  g1.SetMarkerStyle(20);
  g1.SetMaximum(0.8);
  g1.SetTitle(" ");
  g1.GetXaxis()->SetTitle("M(W') in GeV");
  g1.GetYaxis()->SetTitle("Signal Efficiency");
  g1.GetXaxis()->SetLimits(800,6000);
  
  //nGoodTau_sigEff
  TGraph g2(mass.size(), &(mass[0]), &(nGoodTau_sigEff[0]));
  g2.SetLineColor(2);
  g2.SetLineWidth(4);
  g2.SetMarkerColor(8);
  g2.SetMarkerStyle(22);
  g2.SetMaximum(0.8);
  g2.SetTitle(" ");
  g2.GetXaxis()->SetTitle("M(W') in GeV");
  g2.GetYaxis()->SetTitle("Signal Efficiency");
  g2.GetXaxis()->SetLimits(800,6000);

  TGraph g3(mass.size(), &(mass[0]), &(MET_sigEff[0]));
  g3.SetLineColor(2);
  g3.SetLineWidth(4);
  g3.SetMarkerColor(6);
  g3.SetMarkerStyle(33);
  g3.SetMaximum(0.8);
  g3.SetTitle(" ");
  g3.GetXaxis()->SetTitle("M(W') in GeV");
  g3.GetYaxis()->SetTitle("Signal Efficiency");
  g3.GetXaxis()->SetLimits(800,6000);

  TCanvas *c1 = new TCanvas("c1","SigEff");
  c1->cd();
  c1->SetGrid();
  g.Draw("AP");
  g1.Draw("P SAME");
  g2.Draw("P SAME");
  g3.Draw("P SAME");


  TLegend *leg_example = new TLegend(0.75,0.60,0.94,0.94);
  leg_example->SetFillColor(0);
  leg_example->SetTextFont(42);
  leg_example->SetHeader("SSM W'"); 
  leg_example->SetBorderSize(0);
  leg_example->AddEntry(&g1, "Stage 0","P");
  leg_example->AddEntry(&g2, "Stage 1","P");
  leg_example->AddEntry(&g3, "Stage 2","P");
  leg_example->AddEntry(&g, "Full selection","P");
  //  leg_example->AddEntry(total_DY, "DY","f");
   leg_example->Draw("same");

   TLatex* CMS_text = new TLatex(0.20,0.90,"CMS");
   CMS_text->SetNDC();
   CMS_text->SetTextSize(0.05);
   CMS_text->SetTextAngle(0);
   CMS_text->Draw("same");
   TLatex* CMS_text_2 = new TLatex(0.20,0.85,"Preliminary");
   CMS_text_2->SetNDC();
   CMS_text_2->SetTextFont(42);
   CMS_text_2->SetTextSize(0.05);
   CMS_text_2->SetTextAngle(0);
   CMS_text_2->Draw("same");

   TLatex* lumiText = new TLatex(0.92,0.975,"Summer'16 MC");
   lumiText->SetNDC();
   lumiText->SetTextFont(42);
   lumiText->SetTextSize(0.04);
   lumiText->SetTextAlign(32);
   lumiText->Draw("same");


  c1->Update();
  c1->Print("SignalEff.pdf");
  

  return 0;

}
