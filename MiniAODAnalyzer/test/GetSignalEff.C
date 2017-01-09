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

int GetSignalEff() {

  /// Signal ///
  TFile *file_Wprime_M400 = new TFile("../python/crab_projects_SSMsigOnly_Jan7/crab_WprimeToTauNu_M-400_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M400 = (TH1D*)file_Wprime_M400->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M400 = h1_evt_Wprime_M400->GetEntries(); //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M400  = (TH1D*)file_Wprime_M400->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M400 : " << ( mT_Stage1_Wprime_M400->GetEntries() / evt_Wprime_M400 ) << std::endl;

  TFile *file_Wprime_M1000 = new TFile("../python/crab_projects_SSMsigOnly_Jan7/crab_WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M1000 = (TH1D*)file_Wprime_M1000->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M1000 = h1_evt_Wprime_M1000->GetEntries(); //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M1000  = (TH1D*)file_Wprime_M1000->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M1000 : " << ( mT_Stage1_Wprime_M1000->GetEntries() / evt_Wprime_M1000 ) << std::endl;

  TFile *file_Wprime_M2000 = new TFile("../python/crab_projects_SSMsigOnly_Jan7/crab_WprimeToTauNu_M-2000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M2000 = (TH1D*)file_Wprime_M2000->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M2000 = h1_evt_Wprime_M2000->GetEntries(); //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M2000  = (TH1D*)file_Wprime_M2000->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M2000 : " << ( mT_Stage1_Wprime_M2000->GetEntries() / evt_Wprime_M2000 ) << std::endl;

  TFile *file_Wprime_M3000 = new TFile("../python/crab_projects_SSMsigOnly_Jan7/crab_WprimeToTauNu_M-3000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M3000 = (TH1D*)file_Wprime_M3000->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M3000 = h1_evt_Wprime_M3000->GetEntries(); //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M3000  = (TH1D*)file_Wprime_M3000->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M3000 : " << ( mT_Stage1_Wprime_M3000->GetEntries() / evt_Wprime_M3000 ) << std::endl;

  TFile *file_Wprime_M4000 = new TFile("../python/crab_projects_SSMsigOnly_Jan7/crab_WprimeToTauNu_M-4000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M4000 = (TH1D*)file_Wprime_M4000->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M4000 = h1_evt_Wprime_M4000->GetEntries(); //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M4000  = (TH1D*)file_Wprime_M4000->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M4000 : " << ( mT_Stage1_Wprime_M4000->GetEntries() / evt_Wprime_M4000 ) << std::endl;

  TFile *file_Wprime_M5000 = new TFile("../python/crab_projects_SSMsigOnly_Jan7/crab_WprimeToTauNu_M-5000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M5000 = (TH1D*)file_Wprime_M5000->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M5000 = h1_evt_Wprime_M5000->GetEntries(); //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M5000  = (TH1D*)file_Wprime_M5000->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M5000 : " << ( mT_Stage1_Wprime_M5000->GetEntries() / evt_Wprime_M5000 ) << std::endl;

  TFile *file_Wprime_M5800 = new TFile("../python/crab_projects_SSMsigOnly_Jan7/crab_WprimeToTauNu_M_5800_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  TH1D* h1_evt_Wprime_M5800 = (TH1D*)file_Wprime_M5800->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M5800 = h1_evt_Wprime_M5800->GetEntries(); //Integral();                                                                          
  TH1D* mT_Stage1_Wprime_M5800  = (TH1D*)file_Wprime_M5800->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M5800 : " << ( mT_Stage1_Wprime_M5800->GetEntries() / evt_Wprime_M5800 ) << std::endl;

  //--Plotting Styles//
  /*
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.12);  
  gStyle->SetPadTopMargin(0.05);   
  gStyle->SetTitleXSize(0.05);
  gStyle->SetTitleXOffset(1.05);
  gStyle->SetTitleYSize(0.05);
  gStyle->SetTitleYOffset(1.05);
  */
  //////// Output File /////////
  // TFile* outputFile = new TFile("Out_mT_Stage1.root","RECREATE");
  // outputFile->cd();

  //  TCanvas* my_canvas = new TCanvas("canvas","canvas",800,600);
  // my_canvas->cd();
  
  return 0;

}
