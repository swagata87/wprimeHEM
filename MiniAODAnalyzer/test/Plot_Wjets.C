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

int Plot_Wjets() {

  double lumi= 35.865; //20 ;  // B->5.882  // C->2.646   D->4.353 ;  // E->4.049 ; F->3.16 ;  G->7.554;  H->5.942  //--inv fb--//

  TFile *file_TT              = new TFile("../python/crab_projects_March3/crab_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/results/hist.root");
  double xs_TT=730000; //--fb--//
  double kfact_TT= 1.139;
  
  TFile *file_TT_Mtt_700to1000      = new TFile("../python/crab_projects_March3/crab_TT_Mtt-700to1000_TuneCUETP8M1_13TeV-powheg-pythia8/results/hist.root");
  double xs_TT_Mtt_700to1000=730000; //--fb--//
  double kfact_TT_Mtt_700to1000= 0.0921;

  TFile *file_TT_Mtt_1000toInf              = new TFile("../python/crab_projects_March3/crab_TT_Mtt-1000toInf_TuneCUETP8M1_13TeV-powheg-pythia8/results/hist.root");
  double xs_TT_Mtt_1000toInf=730000; //--fb--//
  double kfact_TT_Mtt_1000toInf= 0.02474;
  //

  //  TFile *file_TT_only              = new TFile("../python/crab_projects_TTBulkOnly/crab_TT_TuneCUETP8M1_13TeV-powheg-pythia8/results/hist.root");
  //  double xs_TT_only=730000; //--fb--//
  // double kfact_TT_only= 1.139;


  
  TFile *file_WJetsToLNu      = new TFile("../python/crab_projects_March3/crab_WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu= 50690000; //--fb--//
  //
  TFile *file_WToTauNu_M100  = new TFile("../python/crab_projects_March3/crab_WToTauNu_M-100_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_WToTauNu_M100 = 165000; //--fb--//
  double kfact_WToTauNu_M100 = 1.0 ; 
  //
  TFile *file_WToTauNu_M200  = new TFile("../python/crab_projects_March3/crab_WToTauNu_M-200_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_WToTauNu_M200 = 6370; //--fb--//
  double kfact_WToTauNu_M200 = 1.0 ; 
  //
  TFile *file_WToTauNu_M500  = new TFile("../python/crab_projects_March3/crab_WToTauNu_M-500_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_WToTauNu_M500 = 224.0; //--fb--//
  double kfact_WToTauNu_M500 = 1.0 ; 
  //
  TFile *file_WToTauNu_M1000  = new TFile("../python/crab_projects_March3/crab_WToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_WToTauNu_M1000 = 13.7; //--fb--//
  double kfact_WToTauNu_M1000 = 1.0 ; 
  //
  TFile *file_WToTauNu_M2000  = new TFile("../python/crab_projects_March3/crab_WToTauNu_M-2000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_WToTauNu_M2000 = 0.437; //--fb--//
  double kfact_WToTauNu_M2000 = 1.0 ; 
  //
  TFile *file_WToTauNu_M3000  = new TFile("../python/crab_projects_March3/crab_WToTauNu_M-3000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_WToTauNu_M3000 = 0.0342; //--fb--//
  double kfact_WToTauNu_M3000 = 1.0 ; 
  //
  TFile *file_WToTauNu_M4000  = new TFile("../python/crab_projects_March3/crab_WToTauNu_M-4000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_WToTauNu_M4000 = 0.00292; //--fb--//
  double kfact_WToTauNu_M4000 = 1.0 ; 
  //
  TFile *file_WToTauNu_M5000  = new TFile("../python/crab_projects_March3/crab_WToTauNu_M-5000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_WToTauNu_M5000 = 0.000233; //--fb--//
  double kfact_WToTauNu_M5000 = 1.0 ; 
  //
  TFile *file_WToTauNu_M6000  = new TFile("../python/crab_projects_March3/crab_WToTauNu_M-6000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_WToTauNu_M6000 = 0.000015; //--fb--//
  double kfact_WToTauNu_M6000 = 1.0 ; 
  //
  TFile *file_WJetsToLNu_HT100To200  = new TFile("../python/crab_projects_March3/crab_WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT100To200 = 1345000 ; //--fb--//
  double kfact_WJetsToLNu_HT100To200 = 1.0 ; 

  TFile *file_WJetsToLNu_HT200To400  = new TFile("../python/crab_projects_March3/crab_WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT200To400 = 359700 ; //--fb--//
  double kfact_WJetsToLNu_HT200To400 = 1.0 ;

  TFile *file_WJetsToLNu_HT400To600  = new TFile("../python/crab_projects_March3/crab_WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT400To600 = 48910 ; //--fb--//
  double kfact_WJetsToLNu_HT400To600 = 1.0 ;

  TFile *file_WJetsToLNu_HT600To800  = new TFile("../python/crab_projects_March3/crab_WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT600To800 = 12050 ; //--fb--//
  double kfact_WJetsToLNu_HT600To800 = 1.0 ;

  TFile *file_WJetsToLNu_HT800To1200  = new TFile("../python/crab_projects_March3/crab_WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT800To1200 = 5501 ; //--fb--//
  double kfact_WJetsToLNu_HT800To1200 = 1.0 ;

  TFile *file_WJetsToLNu_HT1200To2500  = new TFile("../python/crab_projects_March3/crab_WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT1200To2500 = 1329 ; //--fb--//
  double kfact_WJetsToLNu_HT1200To2500 = 1.0 ;

  TFile *file_WJetsToLNu_HT2500ToInf  = new TFile("../python/crab_projects_March3/crab_WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT2500ToInf = 32.16  ; //--fb--//
  double kfact_WJetsToLNu_HT2500ToInf = 1.0 ;
 
  //

  TH1D* h1_evt_TT = (TH1D*)file_TT->Get("demo/histoDir/eventCount");
  evt_TT = h1_evt_TT->GetEntries(); // Integral();
  double wt_TT = (xs_TT*lumi)/evt_TT ;
  std::cout << "TT bulk (overlap removed) -> total evt=" << evt_TT << " , wt=" << wt_TT << std::endl;
  TH1D* mT_Stage1_TT  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_TT->Scale(wt_TT);
  mT_Stage1_TT->Scale(kfact_TT);
  std::cout << "TTbar weighted nevt=" << mT_Stage1_TT->Integral() << std::endl;
  mT_Stage1_TT->SetFillColor(kRed-9);
  mT_Stage1_TT->SetLineColor(kRed-9);
  mT_Stage1_TT->Rebin(40);

  //file_TT_Mtt_700to1000
  TH1D* h1_evt_TT_Mtt_700to1000 = (TH1D*)file_TT_Mtt_700to1000->Get("demo/histoDir/eventCount");
  evt_TT_Mtt_700to1000 = h1_evt_TT_Mtt_700to1000->GetEntries(); // Integral();
  double wt_TT_Mtt_700to1000 = (xs_TT_Mtt_700to1000*lumi)/evt_TT_Mtt_700to1000 ;
  std::cout << "TT 700-1000 (overlap removed) -> total evt=" << evt_TT_Mtt_700to1000 << " , wt=" << wt_TT_Mtt_700to1000 << std::endl;
  TH1D* mT_Stage1_TT_Mtt_700to1000  = (TH1D*)file_TT_Mtt_700to1000->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_TT_Mtt_700to1000->Scale(wt_TT_Mtt_700to1000);
  mT_Stage1_TT_Mtt_700to1000->Scale(kfact_TT_Mtt_700to1000);
  std::cout << "TT_Mtt_700to1000bar weighted nevt=" << mT_Stage1_TT_Mtt_700to1000->Integral() << std::endl;
  mT_Stage1_TT_Mtt_700to1000->SetFillColor(kGreen-9);
  mT_Stage1_TT_Mtt_700to1000->SetLineColor(kGreen-9);
  mT_Stage1_TT_Mtt_700to1000->Rebin(40);

  //file_TT_Mtt_1000toInf
  TH1D* h1_evt_TT_Mtt_1000toInf = (TH1D*)file_TT_Mtt_1000toInf->Get("demo/histoDir/eventCount");
  evt_TT_Mtt_1000toInf = h1_evt_TT_Mtt_1000toInf->GetEntries(); // Integral();
  double wt_TT_Mtt_1000toInf = (xs_TT_Mtt_1000toInf*lumi)/evt_TT_Mtt_1000toInf ;
  std::cout << "TT 1000-Inf (overlap removed) -> total evt=" << evt_TT_Mtt_1000toInf << " , wt=" << wt_TT_Mtt_1000toInf << std::endl;
  TH1D* mT_Stage1_TT_Mtt_1000toInf  = (TH1D*)file_TT_Mtt_1000toInf->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_TT_Mtt_1000toInf->Scale(wt_TT_Mtt_1000toInf);
  mT_Stage1_TT_Mtt_1000toInf->Scale(kfact_TT_Mtt_1000toInf);
  std::cout << "TT_Mtt_1000toInfbar weighted nevt=" << mT_Stage1_TT_Mtt_1000toInf->Integral() << std::endl;
  mT_Stage1_TT_Mtt_1000toInf->SetFillColor(kCyan+2);
  mT_Stage1_TT_Mtt_1000toInf->SetLineColor(kCyan+2);
  mT_Stage1_TT_Mtt_1000toInf->Rebin(40);



  //
  /*
  TH1D* h1_evt_TT_only = (TH1D*)file_TT_only->Get("demo/histoDir/eventCount");
  evt_TT_only = h1_evt_TT_only->GetEntries(); // Integral();
  double wt_TT_only = (xs_TT_only*lumi)/evt_TT_only ;
  std::cout << "TT bulk only -> total evt=" << evt_TT_only << " , wt=" << wt_TT_only << std::endl;
  TH1D* mT_Stage1_TT_only  = (TH1D*)file_TT_only->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_TT_only->Scale(wt_TT_only);
  mT_Stage1_TT_only->Scale(kfact_TT_only);
  std::cout << "TT_onlybar weighted nevt=" << mT_Stage1_TT_only->Integral() << std::endl;
  mT_Stage1_TT_only->SetFillColor(kMagenta);
  mT_Stage1_TT_only->SetFillStyle(3004);
  mT_Stage1_TT_only->SetLineColor(kMagenta);
  mT_Stage1_TT_only->SetLineWidth(3);
  mT_Stage1_TT_only->Rebin(40);
  */

  
  //
  //file_WJetsToLNu_HT100To200
  TH1D* h1_evt_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT100To200 = h1_evt_WJetsToLNu_HT100To200->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT100To200 = (xs_WJetsToLNu_HT100To200*lumi)/evt_WJetsToLNu_HT100To200 ;
  TH1D* mT_Stage1_WJetsToLNu_HT100To200  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  std::cout << "WJetsToLNu_HT100To200 weighted nevt=" << mT_Stage1_WJetsToLNu_HT100To200->Integral() << std::endl;

  //file_WJetsToLNu_HT200To400
  TH1D* h1_evt_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT200To400 = h1_evt_WJetsToLNu_HT200To400->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT200To400 = (xs_WJetsToLNu_HT200To400*lumi)/evt_WJetsToLNu_HT200To400 ;
  TH1D* mT_Stage1_WJetsToLNu_HT200To400  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  std::cout << "WJetsToLNu_HT200To400 weighted nevt=" << mT_Stage1_WJetsToLNu_HT200To400->Integral() << std::endl;

  //file_WJetsToLNu_HT400To600
  TH1D* h1_evt_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT400To600 = h1_evt_WJetsToLNu_HT400To600->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT400To600 = (xs_WJetsToLNu_HT400To600*lumi)/evt_WJetsToLNu_HT400To600 ;
  TH1D* mT_Stage1_WJetsToLNu_HT400To600  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  std::cout << "WJetsToLNu_HT400To600 weighted nevt=" << mT_Stage1_WJetsToLNu_HT400To600->Integral() << std::endl;

  //file_WJetsToLNu_HT600To800
  TH1D* h1_evt_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT600To800 = h1_evt_WJetsToLNu_HT600To800->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT600To800 = (xs_WJetsToLNu_HT600To800*lumi)/evt_WJetsToLNu_HT600To800 ;
  TH1D* mT_Stage1_WJetsToLNu_HT600To800  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  std::cout << "WJetsToLNu_HT600To800 weighted nevt=" << mT_Stage1_WJetsToLNu_HT600To800->Integral() << std::endl;

  //file_WJetsToLNu_HT800To1200
  TH1D* h1_evt_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT800To1200 = h1_evt_WJetsToLNu_HT800To1200->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT800To1200 = (xs_WJetsToLNu_HT800To1200*lumi)/evt_WJetsToLNu_HT800To1200 ;
  TH1D* mT_Stage1_WJetsToLNu_HT800To1200  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  std::cout << "WJetsToLNu_HT800To1200 weighted nevt=" << mT_Stage1_WJetsToLNu_HT800To1200->Integral() << std::endl;

  //file_WJetsToLNu_HT1200To2500
  TH1D* h1_evt_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT1200To2500 = h1_evt_WJetsToLNu_HT1200To2500->GetEntries(); //Integral();                                                             
  double wt_WJetsToLNu_HT1200To2500 = (xs_WJetsToLNu_HT1200To2500*lumi)/evt_WJetsToLNu_HT1200To2500 ;
  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  std::cout << "WJetsToLNu_HT1200To2500 weighted nevt=" << mT_Stage1_WJetsToLNu_HT1200To2500->Integral() << std::endl;

  //file_WJetsToLNu_HT2500ToInf
  TH1D* h1_evt_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT2500ToInf = h1_evt_WJetsToLNu_HT2500ToInf->GetEntries(); //Integral();                                                             
  double wt_WJetsToLNu_HT2500ToInf = (xs_WJetsToLNu_HT2500ToInf*lumi)/evt_WJetsToLNu_HT2500ToInf ;
  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  std::cout << "WJetsToLNu_HT2500ToInf weighted nevt=" << mT_Stage1_WJetsToLNu_HT2500ToInf->Integral() << std::endl;

  //file_WToTauNu_M100
  TH1D* h1_evt_WToTauNu_M100 = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M100 = h1_evt_WToTauNu_M100->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M100 = (xs_WToTauNu_M100*lumi)/evt_WToTauNu_M100 ;
  TH1D* mT_Stage1_WToTauNu_M100  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WToTauNu_M100->Scale(wt_WToTauNu_M100);
  std::cout << "WToTauNu_M100 weighted nevt=" << mT_Stage1_WToTauNu_M100->Integral() << std::endl;

  //file_WToTauNu_M200
  TH1D* h1_evt_WToTauNu_M200 = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M200 = h1_evt_WToTauNu_M200->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M200 = (xs_WToTauNu_M200*lumi)/evt_WToTauNu_M200 ;
  TH1D* mT_Stage1_WToTauNu_M200  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WToTauNu_M200->Scale(wt_WToTauNu_M200);
  std::cout << "WToTauNu_M200 weighted nevt=" << mT_Stage1_WToTauNu_M200->Integral() << std::endl;
    
  //file_WToTauNu_M500
  TH1D* h1_evt_WToTauNu_M500 = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M500 = h1_evt_WToTauNu_M500->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M500 = (xs_WToTauNu_M500*lumi)/evt_WToTauNu_M500 ;
  TH1D* mT_Stage1_WToTauNu_M500  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WToTauNu_M500->Scale(wt_WToTauNu_M500);
  std::cout << "WToTauNu_M500 weighted nevt=" << mT_Stage1_WToTauNu_M500->Integral() << std::endl;
 
  //file_WToTauNu_M1000
  TH1D* h1_evt_WToTauNu_M1000 = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M1000 = h1_evt_WToTauNu_M1000->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M1000 = (xs_WToTauNu_M1000*lumi)/evt_WToTauNu_M1000 ;
  TH1D* mT_Stage1_WToTauNu_M1000  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WToTauNu_M1000->Scale(wt_WToTauNu_M1000);
  std::cout << "WToTauNu_M1000 weighted nevt=" << mT_Stage1_WToTauNu_M1000->Integral() << std::endl;

  //file_WToTauNu_M2000
  TH1D* h1_evt_WToTauNu_M2000 = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M2000 = h1_evt_WToTauNu_M2000->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M2000 = (xs_WToTauNu_M2000*lumi)/evt_WToTauNu_M2000 ;
  TH1D* mT_Stage1_WToTauNu_M2000  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WToTauNu_M2000->Scale(wt_WToTauNu_M2000);
  std::cout << "WToTauNu_M2000 weighted nevt=" << mT_Stage1_WToTauNu_M2000->Integral() << std::endl;

  //file_WToTauNu_M3000
  TH1D* h1_evt_WToTauNu_M3000 = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M3000 = h1_evt_WToTauNu_M3000->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M3000 = (xs_WToTauNu_M3000*lumi)/evt_WToTauNu_M3000 ;
  TH1D* mT_Stage1_WToTauNu_M3000  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WToTauNu_M3000->Scale(wt_WToTauNu_M3000);
  std::cout << "WToTauNu_M3000 weighted nevt=" << mT_Stage1_WToTauNu_M3000->Integral() << std::endl;

  //file_WToTauNu_M4000
  TH1D* h1_evt_WToTauNu_M4000 = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M4000 = h1_evt_WToTauNu_M4000->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M4000 = (xs_WToTauNu_M4000*lumi)/evt_WToTauNu_M4000 ;
  TH1D* mT_Stage1_WToTauNu_M4000  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WToTauNu_M4000->Scale(wt_WToTauNu_M4000);
  std::cout << "WToTauNu_M4000 weighted nevt=" << mT_Stage1_WToTauNu_M4000->Integral() << std::endl;

  //file_WToTauNu_M5000
  TH1D* h1_evt_WToTauNu_M5000 = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M5000 = h1_evt_WToTauNu_M5000->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M5000 = (xs_WToTauNu_M5000*lumi)/evt_WToTauNu_M5000 ;
  TH1D* mT_Stage1_WToTauNu_M5000  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WToTauNu_M5000->Scale(wt_WToTauNu_M5000);
  std::cout << "WToTauNu_M5000 weighted nevt=" << mT_Stage1_WToTauNu_M5000->Integral() << std::endl;

  //file_WToTauNu_M6000
  TH1D* h1_evt_WToTauNu_M6000 = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M6000 = h1_evt_WToTauNu_M6000->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M6000 = (xs_WToTauNu_M6000*lumi)/evt_WToTauNu_M6000 ;
  TH1D* mT_Stage1_WToTauNu_M6000  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WToTauNu_M6000->Scale(wt_WToTauNu_M6000);
  std::cout << "WToTauNu_M6000 weighted nevt=" << mT_Stage1_WToTauNu_M6000->Integral() << std::endl;

  //file_WJetsToLNu
  TH1D* h1_evt_WJetsToLNu = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu = h1_evt_WJetsToLNu->GetEntries(); //Integral();                                                             
  double wt_WJetsToLNu = (xs_WJetsToLNu*lumi)/evt_WJetsToLNu ;
  TH1D* mT_Stage1_WJetsToLNu  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WJetsToLNu->Scale(wt_WJetsToLNu);
  std::cout << " BULK WJetsToLNu weighted nevt=" << mT_Stage1_WJetsToLNu->Integral() << std::endl;
  mT_Stage1_WJetsToLNu->SetFillColorAlpha(kBlue-4,0.5);
  mT_Stage1_WJetsToLNu->SetLineColor(kBlack);
  mT_Stage1_WJetsToLNu->Rebin(40);

  //
  TH1D* total_WJets = (TH1D*)mT_Stage1_WJetsToLNu_HT100To200->Clone();
  total_WJets->Add(mT_Stage1_WJetsToLNu_HT200To400);
  total_WJets->Add(mT_Stage1_WJetsToLNu_HT400To600);
  total_WJets->Add(mT_Stage1_WJetsToLNu_HT600To800);
  total_WJets->Add(mT_Stage1_WJetsToLNu_HT800To1200);
  total_WJets->Add(mT_Stage1_WJetsToLNu_HT1200To2500);
  total_WJets->Add(mT_Stage1_WJetsToLNu_HT2500ToInf);
  total_WJets->SetFillColorAlpha(kGreen,0.5);
  total_WJets->SetLineColor(kBlack);
  total_WJets->Rebin(40);

  //
  TH1D* total_WToTau = (TH1D*)mT_Stage1_WToTauNu_M100->Clone();
  total_WToTau->Add(mT_Stage1_WToTauNu_M200);
  total_WToTau->Add(mT_Stage1_WToTauNu_M500);
  total_WToTau->Add(mT_Stage1_WToTauNu_M1000);
  total_WToTau->Add(mT_Stage1_WToTauNu_M2000);
  total_WToTau->Add(mT_Stage1_WToTauNu_M3000);
  total_WToTau->Add(mT_Stage1_WToTauNu_M4000);
  total_WToTau->Add(mT_Stage1_WToTauNu_M5000);
  total_WToTau->Add(mT_Stage1_WToTauNu_M6000);
  total_WToTau->SetFillColorAlpha(kOrange,0.5);
  total_WToTau->SetLineColor(kBlack);
  total_WToTau->Rebin(40);
 
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
  TFile* outputFile = new TFile("MC_stiching.root","RECREATE");
  outputFile->cd();

  //--//
  THStack *hs1 = new THStack("hs1","");
  hs1->Add(mT_Stage1_TT);
  hs1->Add(mT_Stage1_TT_Mtt_700to1000);
  hs1->Add(mT_Stage1_TT_Mtt_1000toInf);

  //--//
  // THStack *hs3 = new THStack("hs3","");
  // hs3->Add(mT_Stage1_TT_only);

  TCanvas* my_canvas = new TCanvas("TTBarcanvas","TTBarcanvas",800,600);
  my_canvas->cd();
  //  hs->Draw();
  gPad->SetLogy();
  hs1->Draw("HIST");                                                                                                                                         
  hs1->SetMaximum(10000);
  hs1->SetMinimum(0.1);
  hs1->GetXaxis()->SetLimits(0, 2000);
  hs1->GetXaxis()->SetTitle("M_{T} [GeV]");
  hs1->GetYaxis()->SetTitle("Events");

  //hs3->Draw("HIST SAME");

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

  TLatex* lumiText = new TLatex(0.92,0.975,"35.9 fb^{-1} 13 TeV");
  lumiText->SetNDC();
  lumiText->SetTextFont(42);
  lumiText->SetTextSize(0.04);
  lumiText->SetTextAlign(32);
  lumiText->Draw("same");     

  TLegend *leg_example = new TLegend(0.60,0.60,0.94,0.94);
  leg_example->SetFillColor(0);
  leg_example->SetTextFont(42);
  leg_example->SetBorderSize(0);
  leg_example->SetTextSize(0.03);
  leg_example->AddEntry(mT_Stage1_TT, "TTbar Bulk","f");
  leg_example->AddEntry(mT_Stage1_TT_Mtt_700to1000, "TTbar Mtt 700-1000 GeV","f");
  leg_example->AddEntry(mT_Stage1_TT_Mtt_1000toInf, "TTbar Mtt >1000 GeV","f");
  // leg_example->AddEntry(mT_Stage1_TT_only, "TTbar Bulk only","f");
  leg_example->Draw("same");
  my_canvas->Write();
  my_canvas->Print("TTBar.pdf");
  //--//

  /*
  TCanvas* my_canvas2 = new TCanvas("TTBarcanvas2","TTBarcanvas2",800,600);
  my_canvas2->cd();
  //  hs->Draw();
  gPad->SetLogy();
  hs3->Draw("HIST");                                                                                                                                        
  hs3->SetMaximum(10000);
  hs3->SetMinimum(0.1);
  hs3->GetXaxis()->SetLimits(0, 3000);
  hs3->GetXaxis()->SetTitle("M_{T} [GeV]");
  hs3->GetYaxis()->SetTitle("Events");
  */

  //
  //--//
   
 THStack *hs2 = new THStack("hs2","");
  hs2->Add(mT_Stage1_WJetsToLNu);
  hs2->Add(total_WJets);
  hs2->Add(total_WToTau);
  

  
  TCanvas* my_canvas_2 = new TCanvas("Wcanvas","Wcanvas",800,600);
  my_canvas_2->cd();
  //  hs->Draw();
  gPad->SetLogy();
  hs2->Draw("HIST");                                                                                                                                        
  hs2->SetMaximum(10000);
  hs2->SetMinimum(0.1);
  hs2->GetXaxis()->SetLimits(0, 3000);
  hs2->GetXaxis()->SetTitle("M_{T} [GeV]");
  hs2->GetYaxis()->SetTitle("Events");

  CMS_text->Draw("same");
  CMS_text_2->Draw("same");    
  lumiText->Draw("same");     

  /*
  TLegend *leg_example3 = new TLegend(0.60,0.60,0.94,0.94);
  leg_example3->SetFillColor(0);
  leg_example3->SetTextFont(42);
  leg_example3->SetBorderSize(0);
  leg_example3->SetTextSize(0.03);
  leg_example3->AddEntry(mT_Stage1_TT_only, "TTbar Bulk Only","f");
  leg_example3->Draw("same");
  my_canvas2->Write();
  my_canvas2->Print("TTBarBulkOnly.pdf");
  */
 
  TLegend *leg_example_2 = new TLegend(0.60,0.60,0.94,0.94);
  leg_example_2->SetFillColor(0);
  leg_example_2->SetTextFont(42);
  leg_example_2->SetTextSize(0.03);
  leg_example_2->SetBorderSize(0);
  leg_example_2->AddEntry(mT_Stage1_WJetsToLNu, "WJets Bulk","f");
  leg_example_2->AddEntry(total_WJets, "WJets HT binned","f");
  leg_example_2->AddEntry(total_WToTau, "WToTau Mass Binned","f");
  leg_example_2->Draw("same");
  my_canvas_2->Write();
  my_canvas_2->Print("WBkg.pdf");
 
  return 0;

}
