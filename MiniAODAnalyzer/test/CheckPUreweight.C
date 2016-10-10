#include <iostream>
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

int CheckPUreweight() {

  double lumi=4.049;  // D->4.353;  //C-> 2.646; //--inv fb--//

  unsigned long long evt_DYJetsToLL_M50=1;
  unsigned long long evt_DYJetsToLL_M5to50=1;
  unsigned long long evt_TT=1;
  unsigned long long evt_WJetsToLNu=1;
  //  TH1::SetDefaultSumw2(); 
  //  gROOT->SetBatch(kTRUE);
  //  TFile *file_DYJetsToLL_M50  = new TFile("../python/crab_projects/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/results/hist.root");
  //double xs_DYJetsToLL_M50=6104000; //--fb--//

  TFile *file_DYJetsToLL_M50  = new TFile("../python/crab_projects/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");             
  double xs_DYJetsToLL_M50=4895000;  //--fb--//                                                                                                                    

  TFile *file_DYJetsToLL_M5to50  = new TFile("../python/crab_projects/crab_DYJetsToLL_M-5to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");    
  double xs_DYJetsToLL_M5to50=7160000;  //--fb--//                                                                                                                    

  TFile *file_TT              = new TFile("../python/crab_projects/crab_TT_TuneCUETP8M1_13TeV-powheg-pythia8/results/hist.root");
  double xs_TT=730000; //--fb--//
  double kfact_TT= 1.139;

  //TFile *file_WJetsToLNu      = new TFile("../python/crab_projects/crab_WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/results/hist.root");
  //double xs_WJetsToLNu=60290000; //--fb--//

  ////  TFile *file_WJetsToLNu      = new TFile("../python/crab_projects/crab_WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  ////  double xs_WJetsToLNu= 50690000; //--fb--//

  TFile *file_WJetsToLNu_HT100To200  = new TFile("../python/crab_projects/crab_WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT100To200 = 1345000 ; //--fb--//
  double kfact_WJetsToLNu_HT100To200 = 1.21 ;

  TFile *file_WJetsToLNu_HT200To400  = new TFile("../python/crab_projects/crab_WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT200To400 = 359700 ; //--fb--//
  double kfact_WJetsToLNu_HT200To400 = 1.21 ;

  TFile *file_WJetsToLNu_HT400To600  = new TFile("../python/crab_projects/crab_WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT400To600 = 48910 ; //--fb--//
  double kfact_WJetsToLNu_HT400To600 = 1.21 ;

  TFile *file_WJetsToLNu_HT600To800  = new TFile("../python/crab_projects/crab_WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT600To800 = 12050 ; //--fb--//
  double kfact_WJetsToLNu_HT600To800 = 1.21 ;

  TFile *file_WJetsToLNu_HT800To1200  = new TFile("../python/crab_projects/crab_WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT800To1200 = 5501 ; //--fb--//
  double kfact_WJetsToLNu_HT800To1200 = 1.21 ;

  TFile *file_WJetsToLNu_HT1200To2500  = new TFile("../python/crab_projects/crab_WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT1200To2500 = 1329 ; //--fb--//
  double kfact_WJetsToLNu_HT1200To2500 = 1.21 ;

  TFile *file_WJetsToLNu_HT2500ToInf  = new TFile("../python/crab_projects/crab_WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT2500ToInf = 32.16  ; //--fb--//
  double kfact_WJetsToLNu_HT2500ToInf = 1.21 ;

  TFile *file_ST_tchannel_antitop=new TFile("../python/crab_projects/crab_ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/results/hist.root");
  double xs_ST_tchannel_antitop = 80950; //--fb--//
  //
  TFile *file_ST_tchannel_top=new TFile("../python/crab_projects/crab_ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/results/hist.root");
  double xs_ST_tchannel_top = 103200; //--fb--//
  //
  TFile *file_ST_tW_antitop=new TFile("../python/crab_projects/crab_ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/results/hist.root");
  double xs_ST_tW_antitop = 38090; //--fb--//
  //
  TFile *file_ST_tW_top=new TFile("../python/crab_projects/crab_ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/results/hist.root");
  double xs_ST_tW_top = 38090; //--fb--//
  //
  TFile *file_WW=new TFile("../python/crab_projects/crab_WW_TuneCUETP8M1_13TeV-pythia8/results/hist.root");
  double xs_WW = 63210; //--fb--//
  //
  TFile *file_WZ=new TFile("../python/crab_projects/crab_WZ_TuneCUETP8M1_13TeV-pythia8/results/hist.root");
  double xs_WZ = 22820; //--fb--//
  double kfact_WZ = 2.06; // 47.13/22.82                                                                                                                                       
  //
  TFile *file_ZZ=new TFile("../python/crab_projects/crab_ZZ_TuneCUETP8M1_13TeV-pythia8/results/hist.root");
  double xs_ZZ = 10320; //--fb--//
  double kfact_ZZ = 1.60 ; //16523/10320                                                                                                                                        
  //
  TFile *file_QCD_HT200to300=new TFile("../python/crab_projects/crab_QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_QCD_HT200to300 = 1717000000; //--fb--//
  //
  TFile *file_QCD_HT300to500=new TFile("../python/crab_projects/crab_QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_QCD_HT300to500 = 351300000; //--fb--//
  //
  TFile *file_QCD_HT500to700=new TFile("../python/crab_projects/crab_QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_QCD_HT500to700 = 31630000 ; //--fb--//
  //
  TFile *file_QCD_HT700to1000=new TFile("../python/crab_projects/crab_QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_QCD_HT700to1000 = 6802000 ; //--fb--//
  //
  TFile *file_QCD_HT1000to1500=new TFile("../python/crab_projects/crab_QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_QCD_HT1000to1500 = 1206000 ; //--fb--//
  //
  TFile *file_QCD_HT1500to2000=new TFile("../python/crab_projects/crab_QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_QCD_HT1500to2000 = 120400 ; //--fb--//
  //
  TFile *file_QCD_HT2000toInf=new TFile("../python/crab_projects/crab_QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_QCD_HT2000toInf = 25250 ; //--fb--//
  //
  TFile *file_ZJetsToNuNu_HT100To200 =new TFile("../python/crab_projects/crab_ZJetsToNuNu_HT-100To200_13TeV-madgraph/results/hist.root");
  double xs_ZJetsToNuNu_HT100To200 =  280350; //--fb--//
  double kfact_ZJetsToNuNu_HT100To200 =  1.23 ; 
  //
  TFile *file_ZJetsToNuNu_HT200To400 =new TFile("../python/crab_projects/crab_ZJetsToNuNu_HT-200To400_13TeV-madgraph/results/hist.root");
  double xs_ZJetsToNuNu_HT200To400 = 77670 ; //--fb--//
  double kfact_ZJetsToNuNu_HT200To400 = 1.23 ; 
  //
  TFile *file_ZJetsToNuNu_HT400To600 =new TFile("../python/crab_projects/crab_ZJetsToNuNu_HT-400To600_13TeV-madgraph/results/hist.root");
  double xs_ZJetsToNuNu_HT400To600 = 10730 ; //--fb--//
  double kfact_ZJetsToNuNu_HT400To600 =  1.23 ;
  //
  TFile *file_ZJetsToNuNu_HT600To800 =new TFile("../python/crab_projects/crab_ZJetsToNuNu_HT-600To800_13TeV-madgraph/results/hist.root");
  double xs_ZJetsToNuNu_HT600To800 = 853 ; //--fb--//
  //
  TFile *file_ZJetsToNuNu_HT800To1200 =new TFile("../python/crab_projects/crab_ZJetsToNuNu_HT-800To1200_13TeV-madgraph/results/hist.root");
  double xs_ZJetsToNuNu_HT800To1200 = 394.2 ; //--fb--//
  //
  TFile *file_ZJetsToNuNu_HT1200To2500 =new TFile("../python/crab_projects/crab_ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/results/hist.root");
  double xs_ZJetsToNuNu_HT1200To2500 = 97.4 ; //--fb--//
  //
  TFile *file_ZJetsToNuNu_HT2500ToInf =new TFile("../python/crab_projects/crab_ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph/results/hist.root");
  double xs_ZJetsToNuNu_HT2500ToInf = 2.308 ; //--fb--//

  /// DATA ///
  //  TFile *file_Tau_Run2016D = new TFile("../python/crab_projects/crab_Tau_Run2016D_PromptReco_v2/results/hist.root");
  // TFile *file_Tau_Run2016C = new TFile("../python/crab_projects/crab_Tau_Run2016C_PromptReco_v2/results/hist.root");
  TFile *file_Tau_Run2016E = new TFile("../python/crab_projects/crab_Tau_Run2016E_PromptReco_v2/results/hist.root");

  /// Signal ///
  TFile *file_Wprime_M1000 = new TFile("../python/crab_projects/crab_WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_Wprime_M1000= 3060; // --fb-- //

  //-DY-//
  TH1D* h1_evt_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/eventCount");
  evt_DYJetsToLL_M50 = h1_evt_DYJetsToLL_M50->GetEntries(); // Integral();
  double wt_DYJetsToLL_M50 = (xs_DYJetsToLL_M50*lumi)/evt_DYJetsToLL_M50 ;
  TH1D* recoVtx_NoPUWt_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  TH1D* h1_evt_DYJetsToLL_M5to50 = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/eventCount");
  evt_DYJetsToLL_M5to50 = h1_evt_DYJetsToLL_M5to50->GetEntries(); // Integral();                                                                                                   
  double wt_DYJetsToLL_M5to50 = (xs_DYJetsToLL_M5to50*lumi)/evt_DYJetsToLL_M5to50 ;
  TH1D* recoVtx_NoPUWt_DYJetsToLL_M5to50 = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_DYJetsToLL_M5to50->Scale(wt_DYJetsToLL_M5to50);
  TH1D* total_DY_NoPUWt = (TH1D*)recoVtx_NoPUWt_DYJetsToLL_M50->Clone();
  total_DY_NoPUWt->Add(recoVtx_NoPUWt_DYJetsToLL_M5to50);
  total_DY_NoPUWt->SetFillColorAlpha(kRed,0.5);
  total_DY_NoPUWt->SetLineColor(kBlack);
  total_DY_NoPUWt->Rebin(2);

  TH1D* recoVtx_WithPUWt_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  TH1D* recoVtx_WithPUWt_DYJetsToLL_M5to50 = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_DYJetsToLL_M5to50->Scale(wt_DYJetsToLL_M5to50);
  TH1D* total_DY_WithPUWt = (TH1D*)recoVtx_WithPUWt_DYJetsToLL_M50->Clone();
  total_DY_WithPUWt->Add(recoVtx_WithPUWt_DYJetsToLL_M5to50);
  total_DY_WithPUWt->SetFillColorAlpha(kRed,0.5);
  total_DY_WithPUWt->SetLineColor(kBlack);
  total_DY_WithPUWt->Rebin(2);


  //-TT-//
  TH1D* h1_evt_TT = (TH1D*)file_TT->Get("demo/histoDir/eventCount");
  evt_TT = h1_evt_TT->GetEntries(); // Integral();
  std::cout << "evt_TT = " << evt_TT << std::endl;
  double wt_TT = (xs_TT*lumi)/evt_TT ;
  TH1D* recoVtx_NoPUWt_TT  = (TH1D*)file_TT->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_TT->Scale(wt_TT);
  recoVtx_NoPUWt_TT->Scale(kfact_TT);
  recoVtx_NoPUWt_TT->SetFillColor(kBlue-7);
  recoVtx_NoPUWt_TT->SetLineColor(kBlack);
  recoVtx_NoPUWt_TT->Rebin(2);
  //
  TH1D* recoVtx_WithPUWt_TT  = (TH1D*)file_TT->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_TT->Scale(wt_TT);
  recoVtx_WithPUWt_TT->Scale(kfact_TT);
  recoVtx_WithPUWt_TT->SetFillColor(kBlue-7);
  recoVtx_WithPUWt_TT->SetLineColor(kBlack);
  recoVtx_WithPUWt_TT->Rebin(2);


  /*
  TH1D* h1_evt_WJetsToLNu = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/eventCount");
  evt_WJetsToLNu = h1_evt_WJetsToLNu->GetEntries(); //Integral();
  std::cout << "evt_WJetsToLNu = " << evt_WJetsToLNu << std::endl;
  double wt_WJetsToLNu = (xs_WJetsToLNu*lumi)/evt_WJetsToLNu ;
  TH1D* recoVtx_NoPUWt_WJetsToLNu  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/recoVtx_NoPUWt");
  // Poisson error //
  recoVtx_NoPUWt_WJetsToLNu->Sumw2(kFALSE);
  recoVtx_NoPUWt_WJetsToLNu->SetBinErrorOption(TH1::kPoisson);
  std::cout << "**WJets** unweighted nevt=" << recoVtx_NoPUWt_WJetsToLNu->Integral() << std::endl;
  std::cout << "wt_WJetsToLNu = " << wt_WJetsToLNu << std::endl;
  recoVtx_NoPUWt_WJetsToLNu->Scale(wt_WJetsToLNu);
  recoVtx_NoPUWt_WJetsToLNu->SetFillColorAlpha(kGreen-7,0.5);
  recoVtx_NoPUWt_WJetsToLNu->SetLineColor(kGreen-7);
  recoVtx_NoPUWt_WJetsToLNu->Rebin(2);
  std::cout << "**WJets** weighted nevt=" << recoVtx_NoPUWt_WJetsToLNu->Integral() << std::endl;
  */

  //file_ST_tchannel_antitop
  TH1D* h1_evt_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/eventCount");
  unsigned long long evt_ST_tchannel_antitop = h1_evt_ST_tchannel_antitop->GetEntries(); //Integral();
  double wt_ST_tchannel_antitop = (xs_ST_tchannel_antitop*lumi)/evt_ST_tchannel_antitop ;
  TH1D* recoVtx_NoPUWt_ST_tchannel_antitop  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  //
  TH1D* recoVtx_WithPUWt_ST_tchannel_antitop  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
 
  //file_ST_tchannel_top
  TH1D* h1_evt_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/eventCount");
  unsigned long long evt_ST_tchannel_top = h1_evt_ST_tchannel_top->GetEntries(); //Integral();
  double wt_ST_tchannel_top = (xs_ST_tchannel_top*lumi)/evt_ST_tchannel_top ;
  TH1D* recoVtx_NoPUWt_ST_tchannel_top  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  //
  TH1D* recoVtx_WithPUWt_ST_tchannel_top  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_ST_tchannel_top->Scale(wt_ST_tchannel_top);

  //file_ST_tW_antitop
  TH1D* h1_evt_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/eventCount");
  unsigned long long evt_ST_tW_antitop = h1_evt_ST_tW_antitop->GetEntries(); //Integral();
  double wt_ST_tW_antitop = (xs_ST_tW_antitop*lumi)/evt_ST_tW_antitop ;
  TH1D* recoVtx_NoPUWt_ST_tW_antitop  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  //
  TH1D* recoVtx_WithPUWt_ST_tW_antitop  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  
  //file_ST_tW_top
  TH1D* h1_evt_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/histoDir/eventCount");
  unsigned long long evt_ST_tW_top = h1_evt_ST_tW_top->GetEntries(); //Integral();
  double wt_ST_tW_top = (xs_ST_tW_top*lumi)/evt_ST_tW_top ;
  TH1D* recoVtx_NoPUWt_ST_tW_top  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_ST_tW_top->Scale(wt_ST_tW_top);
  //
  TH1D* recoVtx_WithPUWt_ST_tW_top  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_ST_tW_top->Scale(wt_ST_tW_top);

  TH1D* total_ST = (TH1D*)recoVtx_NoPUWt_ST_tchannel_antitop->Clone(); 
  total_ST->Add(recoVtx_NoPUWt_ST_tchannel_top);
  total_ST->Add(recoVtx_NoPUWt_ST_tW_antitop);
  total_ST->Add(recoVtx_NoPUWt_ST_tW_top);
  total_ST->SetFillColorAlpha(kCyan,0.5);
  total_ST->SetLineColor(kBlack);
  total_ST->Rebin(2);
  //
  TH1D* total_ST_2 = (TH1D*)recoVtx_WithPUWt_ST_tchannel_antitop->Clone(); 
  total_ST_2->Add(recoVtx_WithPUWt_ST_tchannel_top);
  total_ST_2->Add(recoVtx_WithPUWt_ST_tW_antitop);
  total_ST_2->Add(recoVtx_WithPUWt_ST_tW_top);
  total_ST_2->SetFillColorAlpha(kCyan,0.5);
  total_ST_2->SetLineColor(kBlack);
  total_ST_2->Rebin(2);

  //file_WJetsToLNu_HT100To200
  TH1D* h1_evt_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT100To200 = h1_evt_WJetsToLNu_HT100To200->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT100To200 = (xs_WJetsToLNu_HT100To200*lumi)/evt_WJetsToLNu_HT100To200 ;
  TH1D* recoVtx_NoPUWt_WJetsToLNu_HT100To200  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  // recoVtx_NoPUWt_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);
  //
  TH1D* recoVtx_WithPUWt_WJetsToLNu_HT100To200  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  // recoVtx_WithPUWt_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);

  //file_WJetsToLNu_HT200To400
  TH1D* h1_evt_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT200To400 = h1_evt_WJetsToLNu_HT200To400->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT200To400 = (xs_WJetsToLNu_HT200To400*lumi)/evt_WJetsToLNu_HT200To400 ;
  TH1D* recoVtx_NoPUWt_WJetsToLNu_HT200To400  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  // recoVtx_NoPUWt_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);
  //
  TH1D* recoVtx_WithPUWt_WJetsToLNu_HT200To400  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  // recoVtx_WithPUWt_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);
  //file_WJetsToLNu_HT400To600
  TH1D* h1_evt_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT400To600 = h1_evt_WJetsToLNu_HT400To600->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT400To600 = (xs_WJetsToLNu_HT400To600*lumi)/evt_WJetsToLNu_HT400To600 ;
  TH1D* recoVtx_NoPUWt_WJetsToLNu_HT400To600  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  // recoVtx_NoPUWt_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);
  //
  TH1D* recoVtx_WithPUWt_WJetsToLNu_HT400To600  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  // recoVtx_WithPUWt_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);
  //file_WJetsToLNu_HT600To800
  TH1D* h1_evt_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT600To800 = h1_evt_WJetsToLNu_HT600To800->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT600To800 = (xs_WJetsToLNu_HT600To800*lumi)/evt_WJetsToLNu_HT600To800 ;
  TH1D* recoVtx_NoPUWt_WJetsToLNu_HT600To800  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  // recoVtx_NoPUWt_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);
  //
  TH1D* recoVtx_WithPUWt_WJetsToLNu_HT600To800  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  // recoVtx_WithPUWt_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);
  //file_WJetsToLNu_HT800To1200
  TH1D* h1_evt_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT800To1200 = h1_evt_WJetsToLNu_HT800To1200->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT800To1200 = (xs_WJetsToLNu_HT800To1200*lumi)/evt_WJetsToLNu_HT800To1200 ;
  TH1D* recoVtx_NoPUWt_WJetsToLNu_HT800To1200  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  // recoVtx_NoPUWt_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);
  //
  TH1D* recoVtx_WithPUWt_WJetsToLNu_HT800To1200  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  // recoVtx_WithPUWt_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);

  //file_WJetsToLNu_HT1200To2500
  TH1D* h1_evt_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT1200To2500 = h1_evt_WJetsToLNu_HT1200To2500->GetEntries(); //Integral();                                                             
  double wt_WJetsToLNu_HT1200To2500 = (xs_WJetsToLNu_HT1200To2500*lumi)/evt_WJetsToLNu_HT1200To2500 ;
  TH1D* recoVtx_NoPUWt_WJetsToLNu_HT1200To2500  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  // recoVtx_NoPUWt_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);
  //
  TH1D* recoVtx_WithPUWt_WJetsToLNu_HT1200To2500  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  // recoVtx_WithPUWt_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);

  //file_WJetsToLNu_HT2500ToInf
  TH1D* h1_evt_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT2500ToInf = h1_evt_WJetsToLNu_HT2500ToInf->GetEntries(); //Integral();                                                             
  double wt_WJetsToLNu_HT2500ToInf = (xs_WJetsToLNu_HT2500ToInf*lumi)/evt_WJetsToLNu_HT2500ToInf ;
  TH1D* recoVtx_NoPUWt_WJetsToLNu_HT2500ToInf  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  // recoVtx_NoPUWt_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);

  //
  TH1D* recoVtx_WithPUWt_WJetsToLNu_HT2500ToInf  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  //recoVtx_WithPUWt_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);

  TH1D* total_WJets = (TH1D*)recoVtx_NoPUWt_WJetsToLNu_HT100To200->Clone();
  total_WJets->Add(recoVtx_NoPUWt_WJetsToLNu_HT200To400);
  total_WJets->Add(recoVtx_NoPUWt_WJetsToLNu_HT400To600);
  total_WJets->Add(recoVtx_NoPUWt_WJetsToLNu_HT600To800);
  total_WJets->Add(recoVtx_NoPUWt_WJetsToLNu_HT800To1200);
  total_WJets->Add(recoVtx_NoPUWt_WJetsToLNu_HT1200To2500);
  total_WJets->Add(recoVtx_NoPUWt_WJetsToLNu_HT2500ToInf);
  total_WJets->SetFillColorAlpha(kGreen-8,0.5);
  total_WJets->SetLineColor(kBlack);
  total_WJets->Rebin(2);
  //
  TH1D* total_WJets_2 = (TH1D*)recoVtx_WithPUWt_WJetsToLNu_HT100To200->Clone();
  total_WJets_2->Add(recoVtx_WithPUWt_WJetsToLNu_HT200To400);
  total_WJets_2->Add(recoVtx_WithPUWt_WJetsToLNu_HT400To600);
  total_WJets_2->Add(recoVtx_WithPUWt_WJetsToLNu_HT600To800);
  total_WJets_2->Add(recoVtx_WithPUWt_WJetsToLNu_HT800To1200);
  total_WJets_2->Add(recoVtx_WithPUWt_WJetsToLNu_HT1200To2500);
  total_WJets_2->Add(recoVtx_WithPUWt_WJetsToLNu_HT2500ToInf);
  total_WJets_2->SetFillColorAlpha(kGreen-8,0.5);
  total_WJets_2->SetLineColor(kBlack);
  total_WJets_2->Rebin(2);

  //file_WW
  TH1D* h1_evt_WW = (TH1D*)file_WW->Get("demo/histoDir/eventCount");
  unsigned long long evt_WW = h1_evt_WW->GetEntries(); //Integral();                                                                         
  double wt_WW = (xs_WW*lumi)/evt_WW ;
  TH1D* recoVtx_NoPUWt_WW  = (TH1D*)file_WW->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_WW->Scale(wt_WW);
  //
  TH1D* recoVtx_WithPUWt_WW  = (TH1D*)file_WW->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_WW->Scale(wt_WW);

  //file_WZ
  TH1D* h1_evt_WZ = (TH1D*)file_WZ->Get("demo/histoDir/eventCount");
  unsigned long long evt_WZ = h1_evt_WZ->GetEntries(); //Integral();                                                                         
  double wt_WZ = (xs_WZ*lumi)/evt_WZ ;
  TH1D* recoVtx_NoPUWt_WZ  = (TH1D*)file_WZ->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_WZ->Scale(wt_WZ);
  recoVtx_NoPUWt_WZ->Scale(kfact_WZ);

  //
  TH1D* recoVtx_WithPUWt_WZ  = (TH1D*)file_WZ->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_WZ->Scale(wt_WZ);
  recoVtx_WithPUWt_WZ->Scale(kfact_WZ);

  //file_ZZ
  TH1D* h1_evt_ZZ = (TH1D*)file_ZZ->Get("demo/histoDir/eventCount");
  unsigned long long evt_ZZ = h1_evt_ZZ->GetEntries(); //Integral();                                                                         
  double wt_ZZ = (xs_ZZ*lumi)/evt_ZZ ;
  TH1D* recoVtx_NoPUWt_ZZ  = (TH1D*)file_ZZ->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_ZZ->Scale(wt_ZZ);
  recoVtx_NoPUWt_ZZ->Scale(kfact_ZZ);

  //
  TH1D* recoVtx_WithPUWt_ZZ  = (TH1D*)file_ZZ->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_ZZ->Scale(wt_ZZ);
  recoVtx_WithPUWt_ZZ->Scale(kfact_ZZ);

  TH1D* total_diboson = (TH1D*)recoVtx_NoPUWt_WW->Clone();
  total_diboson->Add(recoVtx_NoPUWt_WZ);
  total_diboson->Add(recoVtx_NoPUWt_ZZ);
  total_diboson->SetFillColorAlpha(kOrange+2,0.5);
  total_diboson->SetLineColor(kBlack);
  total_diboson->Rebin(2);
  //
  TH1D* total_diboson_2 = (TH1D*)recoVtx_WithPUWt_WW->Clone();
  total_diboson_2->Add(recoVtx_WithPUWt_WZ);
  total_diboson_2->Add(recoVtx_WithPUWt_ZZ);
  total_diboson_2->SetFillColorAlpha(kOrange+2,0.5);
  total_diboson_2->SetLineColor(kBlack);
  total_diboson_2->Rebin(2);

  //file_QCD_HT200to300
  TH1D* h1_evt_QCD_HT200to300 = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/eventCount");
  unsigned long long evt_QCD_HT200to300 = h1_evt_QCD_HT200to300->GetEntries(); //Integral();                                                                 
  double wt_QCD_HT200to300 = (xs_QCD_HT200to300*lumi)/evt_QCD_HT200to300 ;
  TH1D* recoVtx_NoPUWt_QCD_HT200to300  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_QCD_HT200to300->Scale(wt_QCD_HT200to300);
  //
  TH1D* recoVtx_WithPUWt_QCD_HT200to300  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_QCD_HT200to300->Scale(wt_QCD_HT200to300);

  //file_QCD_HT300to500
  TH1D* h1_evt_QCD_HT300to500 = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/eventCount");
  unsigned long long evt_QCD_HT300to500 = h1_evt_QCD_HT300to500->GetEntries(); //Integral();                                                                     
  double wt_QCD_HT300to500 = (xs_QCD_HT300to500*lumi)/evt_QCD_HT300to500 ;
  TH1D* recoVtx_NoPUWt_QCD_HT300to500  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_QCD_HT300to500->Scale(wt_QCD_HT300to500);
  //
  TH1D* recoVtx_WithPUWt_QCD_HT300to500  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_QCD_HT300to500->Scale(wt_QCD_HT300to500);

  //file_QCD_HT500to700
  TH1D* h1_evt_QCD_HT500to700 = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/eventCount");
  unsigned long long evt_QCD_HT500to700 = h1_evt_QCD_HT500to700->GetEntries(); //Integral();                                                                
  double wt_QCD_HT500to700 = (xs_QCD_HT500to700*lumi)/evt_QCD_HT500to700 ;
  TH1D* recoVtx_NoPUWt_QCD_HT500to700  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_QCD_HT500to700->Scale(wt_QCD_HT500to700);
  //
  TH1D* recoVtx_WithPUWt_QCD_HT500to700  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_QCD_HT500to700->Scale(wt_QCD_HT500to700);

  //file_QCD_HT700to1000
  TH1D* h1_evt_QCD_HT700to1000 = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/eventCount");
  unsigned long long evt_QCD_HT700to1000 = h1_evt_QCD_HT700to1000->GetEntries(); //Integral();                                                                
  double wt_QCD_HT700to1000 = (xs_QCD_HT700to1000*lumi)/evt_QCD_HT700to1000 ;
  TH1D* recoVtx_NoPUWt_QCD_HT700to1000  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);
  //
  TH1D* recoVtx_WithPUWt_QCD_HT700to1000  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);

  //file_QCD_HT1000to1500
  TH1D* h1_evt_QCD_HT1000to1500 = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/eventCount");
  unsigned long long evt_QCD_HT1000to1500 = h1_evt_QCD_HT1000to1500->GetEntries(); //Integral();                                                                  
  double wt_QCD_HT1000to1500 = (xs_QCD_HT1000to1500*lumi)/evt_QCD_HT1000to1500 ;
  TH1D* recoVtx_NoPUWt_QCD_HT1000to1500  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);
  //
  TH1D* recoVtx_WithPUWt_QCD_HT1000to1500  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);

  //file_QCD_HT1500to2000
  TH1D* h1_evt_QCD_HT1500to2000 = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/eventCount");
  unsigned long long evt_QCD_HT1500to2000 = h1_evt_QCD_HT1500to2000->GetEntries(); //Integral();                                                                  
  double wt_QCD_HT1500to2000 = (xs_QCD_HT1500to2000*lumi)/evt_QCD_HT1500to2000 ;
  TH1D* recoVtx_NoPUWt_QCD_HT1500to2000  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);
  //
  TH1D* recoVtx_WithPUWt_QCD_HT1500to2000  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);

  //file_QCD_HT2000toInf
  TH1D* h1_evt_QCD_HT2000toInf = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/eventCount");
  unsigned long long evt_QCD_HT2000toInf = h1_evt_QCD_HT2000toInf->GetEntries(); //Integral();                                                                  
  double wt_QCD_HT2000toInf = (xs_QCD_HT2000toInf*lumi)/evt_QCD_HT2000toInf ;
  TH1D* recoVtx_NoPUWt_QCD_HT2000toInf  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);
  //
  TH1D* recoVtx_WithPUWt_QCD_HT2000toInf  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);

  TH1D* total_QCD = (TH1D*)recoVtx_NoPUWt_QCD_HT200to300->Clone();
  total_QCD->Add(recoVtx_NoPUWt_QCD_HT300to500);
  total_QCD->Add(recoVtx_NoPUWt_QCD_HT500to700);
  total_QCD->Add(recoVtx_NoPUWt_QCD_HT700to1000);
  total_QCD->Add(recoVtx_NoPUWt_QCD_HT1000to1500);
  total_QCD->Add(recoVtx_NoPUWt_QCD_HT1500to2000);
  total_QCD->Add(recoVtx_NoPUWt_QCD_HT2000toInf);
  total_QCD->SetFillColorAlpha(kPink+1,0.5);
  total_QCD->SetLineColor(kBlack);
  total_QCD->Rebin(2);
  //
  TH1D* total_QCD_2 = (TH1D*)recoVtx_WithPUWt_QCD_HT200to300->Clone();
  total_QCD_2->Add(recoVtx_WithPUWt_QCD_HT300to500);
  total_QCD_2->Add(recoVtx_WithPUWt_QCD_HT500to700);
  total_QCD_2->Add(recoVtx_WithPUWt_QCD_HT700to1000);
  total_QCD_2->Add(recoVtx_WithPUWt_QCD_HT1000to1500);
  total_QCD_2->Add(recoVtx_WithPUWt_QCD_HT1500to2000);
  total_QCD_2->Add(recoVtx_WithPUWt_QCD_HT2000toInf);
  total_QCD_2->SetFillColorAlpha(kPink+1,0.5);
  total_QCD_2->SetLineColor(kBlack);
  total_QCD_2->Rebin(2);

  //file_ZJetsToNuNu_HT100To200
  TH1D* h1_evt_ZJetsToNuNu_HT100To200 = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT100To200 = h1_evt_ZJetsToNuNu_HT100To200->GetEntries(); //Integral();                                                                 
  double wt_ZJetsToNuNu_HT100To200 = (xs_ZJetsToNuNu_HT100To200*lumi)/evt_ZJetsToNuNu_HT100To200 ;
  TH1D* recoVtx_NoPUWt_ZJetsToNuNu_HT100To200  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  recoVtx_NoPUWt_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);
  //
  TH1D* recoVtx_WithPUWt_ZJetsToNuNu_HT100To200  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  recoVtx_WithPUWt_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);

  //file_ZJetsToNuNu_HT200To400
  TH1D* h1_evt_ZJetsToNuNu_HT200To400 = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT200To400 = h1_evt_ZJetsToNuNu_HT200To400->GetEntries(); //Integral();                                                                 
  double wt_ZJetsToNuNu_HT200To400 = (xs_ZJetsToNuNu_HT200To400*lumi)/evt_ZJetsToNuNu_HT200To400 ;
  TH1D* recoVtx_NoPUWt_ZJetsToNuNu_HT200To400  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  recoVtx_NoPUWt_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);
  //
  TH1D* recoVtx_WithPUWt_ZJetsToNuNu_HT200To400  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  recoVtx_WithPUWt_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);

  //file_ZJetsToNuNu_HT400To600
  TH1D* h1_evt_ZJetsToNuNu_HT400To600 = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT400To600 = h1_evt_ZJetsToNuNu_HT400To600->GetEntries(); //Integral();                                                                
  double wt_ZJetsToNuNu_HT400To600 = (xs_ZJetsToNuNu_HT400To600*lumi)/evt_ZJetsToNuNu_HT400To600 ;
  TH1D* recoVtx_NoPUWt_ZJetsToNuNu_HT400To600  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  recoVtx_NoPUWt_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);
  //
  TH1D* recoVtx_WithPUWt_ZJetsToNuNu_HT400To600  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  recoVtx_WithPUWt_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);

  //file_ZJetsToNuNu_HT600To800
  TH1D* h1_evt_ZJetsToNuNu_HT600To800 = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT600To800 = h1_evt_ZJetsToNuNu_HT600To800->GetEntries(); //Integral();                                                                
  double wt_ZJetsToNuNu_HT600To800 = (xs_ZJetsToNuNu_HT600To800*lumi)/evt_ZJetsToNuNu_HT600To800 ;
  TH1D* recoVtx_NoPUWt_ZJetsToNuNu_HT600To800  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);
  //
  TH1D* recoVtx_WithPUWt_ZJetsToNuNu_HT600To800  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);

  //file_ZJetsToNuNu_HT800To1200
  TH1D* h1_evt_ZJetsToNuNu_HT800To1200 = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT800To1200 = h1_evt_ZJetsToNuNu_HT800To1200->GetEntries(); //Integral();                                                            
  double wt_ZJetsToNuNu_HT800To1200 = (xs_ZJetsToNuNu_HT800To1200*lumi)/evt_ZJetsToNuNu_HT800To1200 ;
  TH1D* recoVtx_NoPUWt_ZJetsToNuNu_HT800To1200  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);
  //
  TH1D* recoVtx_WithPUWt_ZJetsToNuNu_HT800To1200  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);

  //file_ZJetsToNuNu_HT1200To2500
  TH1D* h1_evt_ZJetsToNuNu_HT1200To2500 = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT1200To2500 = h1_evt_ZJetsToNuNu_HT1200To2500->GetEntries(); //Integral();                                                             
  double wt_ZJetsToNuNu_HT1200To2500 = (xs_ZJetsToNuNu_HT1200To2500*lumi)/evt_ZJetsToNuNu_HT1200To2500 ;
  TH1D* recoVtx_NoPUWt_ZJetsToNuNu_HT1200To2500  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);
  //
  TH1D* recoVtx_WithPUWt_ZJetsToNuNu_HT1200To2500  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);

  //file_ZJetsToNuNu_HT2500ToInf
  TH1D* h1_evt_ZJetsToNuNu_HT2500ToInf = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT2500ToInf = h1_evt_ZJetsToNuNu_HT2500ToInf->GetEntries(); //Integral();                                                         
  double wt_ZJetsToNuNu_HT2500ToInf = (xs_ZJetsToNuNu_HT2500ToInf*lumi)/evt_ZJetsToNuNu_HT2500ToInf ;
  TH1D* recoVtx_NoPUWt_ZJetsToNuNu_HT2500ToInf  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  //
  TH1D* recoVtx_WithPUWt_ZJetsToNuNu_HT2500ToInf  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);

  TH1D* total_ZJets = (TH1D*)recoVtx_NoPUWt_ZJetsToNuNu_HT100To200->Clone();
  total_ZJets->Add(recoVtx_NoPUWt_ZJetsToNuNu_HT200To400);
  total_ZJets->Add(recoVtx_NoPUWt_ZJetsToNuNu_HT400To600);
  total_ZJets->Add(recoVtx_NoPUWt_ZJetsToNuNu_HT600To800);
  total_ZJets->Add(recoVtx_NoPUWt_ZJetsToNuNu_HT800To1200);
  total_ZJets->Add(recoVtx_NoPUWt_ZJetsToNuNu_HT1200To2500);
  total_ZJets->Add(recoVtx_NoPUWt_ZJetsToNuNu_HT2500ToInf);
  total_ZJets->SetFillColorAlpha(kYellow-9,0.5);
  total_ZJets->SetLineColor(kBlack);
  total_ZJets->Rebin(2);
  //
  TH1D* total_ZJets_2 = (TH1D*)recoVtx_WithPUWt_ZJetsToNuNu_HT100To200->Clone();
  total_ZJets_2->Add(recoVtx_WithPUWt_ZJetsToNuNu_HT200To400);
  total_ZJets_2->Add(recoVtx_WithPUWt_ZJetsToNuNu_HT400To600);
  total_ZJets_2->Add(recoVtx_WithPUWt_ZJetsToNuNu_HT600To800);
  total_ZJets_2->Add(recoVtx_WithPUWt_ZJetsToNuNu_HT800To1200);
  total_ZJets_2->Add(recoVtx_WithPUWt_ZJetsToNuNu_HT1200To2500);
  total_ZJets_2->Add(recoVtx_WithPUWt_ZJetsToNuNu_HT2500ToInf);
  total_ZJets_2->SetFillColorAlpha(kYellow-9,0.5);
  total_ZJets_2->SetLineColor(kBlack);
  total_ZJets_2->Rebin(2);

  //--Data--//
  TH1D* recoVtx_NoPUWt_Run2016E  = (TH1D*)file_Tau_Run2016E->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_Run2016E->SetMarkerStyle(20);
  recoVtx_NoPUWt_Run2016E->SetMarkerColor(kBlack);
  recoVtx_NoPUWt_Run2016E->SetLineColor(kBlack);
  recoVtx_NoPUWt_Run2016E->Rebin(2);
  //
  TH1D* recoVtx_WithPUWt_Run2016E  = (TH1D*)file_Tau_Run2016E->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_Run2016E->SetMarkerStyle(20);
  recoVtx_WithPUWt_Run2016E->SetMarkerColor(kBlack);
  recoVtx_WithPUWt_Run2016E->SetLineColor(kBlack);
  recoVtx_WithPUWt_Run2016E->Rebin(2);

  /*
  TH1D* recoVtx_NoPUWt_Run2016D  = (TH1D*)file_Tau_Run2016D->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_Run2016D->SetMarkerStyle(20);
  recoVtx_NoPUWt_Run2016D->SetMarkerColor(kBlack);
  recoVtx_NoPUWt_Run2016D->SetLineColor(kBlack);
  recoVtx_NoPUWt_Run2016D->Rebin(2);
  //
  TH1D* recoVtx_WithPUWt_Run2016D  = (TH1D*)file_Tau_Run2016D->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_Run2016D->SetMarkerStyle(20);
  recoVtx_WithPUWt_Run2016D->SetMarkerColor(kBlack);
  recoVtx_WithPUWt_Run2016D->SetLineColor(kBlack);
  recoVtx_WithPUWt_Run2016D->Rebin(2);
  */
  //
  /*
  TH1D* recoVtx_NoPUWt_Run2016C  = (TH1D*)file_Tau_Run2016C->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_Run2016C->SetMarkerStyle(20);
  recoVtx_NoPUWt_Run2016C->SetMarkerColor(kBlack);
  recoVtx_NoPUWt_Run2016C->SetLineColor(kBlack);
  recoVtx_NoPUWt_Run2016C->Rebin(2);
  //
  TH1D* recoVtx_WithPUWt_Run2016C  = (TH1D*)file_Tau_Run2016C->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_Run2016C->SetMarkerStyle(20);
  recoVtx_WithPUWt_Run2016C->SetMarkerColor(kBlack);
  recoVtx_WithPUWt_Run2016C->SetLineColor(kBlack);
  recoVtx_WithPUWt_Run2016C->Rebin(2);
  */

  //--Signal--//
  TH1D* h1_evt_Wprime_M1000 = (TH1D*)file_Wprime_M1000->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M1000 = h1_evt_Wprime_M1000->GetEntries(); //Integral();                                                                          
  std::cout << "evt_Wprime_M1000 = " << evt_Wprime_M1000 << std::endl;
  double wt_Wprime_M1000 = (xs_Wprime_M1000*lumi)/evt_Wprime_M1000 ;
  TH1D* recoVtx_NoPUWt_Wprime_M1000  = (TH1D*)file_Wprime_M1000->Get("demo/histoDir/recoVtx_NoPUWt");
  recoVtx_NoPUWt_Wprime_M1000->Scale(wt_Wprime_M1000);
  recoVtx_NoPUWt_Wprime_M1000->SetLineColor(kMagenta);
  recoVtx_NoPUWt_Wprime_M1000->SetLineWidth(2);
  recoVtx_NoPUWt_Wprime_M1000->SetLineStyle(5);
  recoVtx_NoPUWt_Wprime_M1000->Rebin(2);
  //
  TH1D* recoVtx_WithPUWt_Wprime_M1000  = (TH1D*)file_Wprime_M1000->Get("demo/histoDir/recoVtx_WithPUWt");
  recoVtx_WithPUWt_Wprime_M1000->Scale(wt_Wprime_M1000);
  recoVtx_WithPUWt_Wprime_M1000->SetLineColor(kMagenta);
  recoVtx_WithPUWt_Wprime_M1000->SetLineWidth(2);
  recoVtx_WithPUWt_Wprime_M1000->SetLineStyle(5);
  recoVtx_WithPUWt_Wprime_M1000->Rebin(2);
 
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
  TFile* outputFile = new TFile("Out_recoVtx_NoPUWt.root","RECREATE");
  outputFile->cd();

  //--//
  THStack *hs = new THStack("hs","");
  // hs->Add(recoVtx_NoPUWt_WJetsToLNu);
  hs->Add(total_WJets);
  hs->Add(recoVtx_NoPUWt_TT);
  hs->Add(total_DY_NoPUWt);
  hs->Add(total_ST);
  hs->Add(total_diboson);
  hs->Add(total_QCD);
  hs->Add(total_ZJets);

  THStack *hs_2 = new THStack("hs_2","");
  // hs->Add(recoVtx_WithPUWt_WJetsToLNu);
  hs_2->Add(total_WJets_2);
  hs_2->Add(recoVtx_WithPUWt_TT);
  hs_2->Add(total_DY_WithPUWt);
  hs_2->Add(total_ST_2);
  hs_2->Add(total_diboson_2);
  hs_2->Add(total_QCD_2);
  hs_2->Add(total_ZJets_2);

  TCanvas* my_canvas = new TCanvas("canvas","canvas",800,600);
  my_canvas->cd();
  gPad->SetLogy();
  hs->Draw("HIST");                                                                                                                                        
  hs->SetMaximum(10000);
  hs->SetMinimum(0.1);
  hs->GetXaxis()->SetLimits(0, 60);
  hs->GetXaxis()->SetTitle("nVtx");
  hs->GetYaxis()->SetTitle("Events");
  TH1F* total =  (TH1F*)hs->GetStack()->Last()->Clone();
  total->SetFillStyle(3004);                                                                                                                                      
  total->SetFillColor(kGray+1); 
  //  total->SetMarkerColor(0);
  // total->Draw("SAME E2");
  //hs->GetStack()->Last()->Draw("same E");
  // hs->Draw("SAME HIST");
  recoVtx_NoPUWt_Run2016E->Draw("SAME E0");
  recoVtx_NoPUWt_Wprime_M1000->Draw("SAME HIST");
  //  hs->SetOption("HIST L");
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
  TLatex* lumiText = new TLatex(0.95,0.975,"4.05 fb^{-1} (RunE 2016 13 TeV)");
  lumiText->SetNDC();
  lumiText->SetTextFont(42);
  lumiText->SetTextSize(0.04);
  lumiText->SetTextAlign(32);
  lumiText->Draw("same");     
  TLatex* ExtraText = new TLatex(0.65,0.75,"Before PU reweighting");
  ExtraText->SetNDC();
  ExtraText->SetTextFont(42);
  ExtraText->SetTextSize(0.03);
  ExtraText->SetTextAlign(32);
  ExtraText->Draw("same");     
  TLegend *leg_example = new TLegend(0.75,0.60,0.94,0.94);
  leg_example->SetFillColor(0);
  leg_example->SetTextFont(42);
  leg_example->SetBorderSize(0);
  leg_example->AddEntry(total_WJets, "Wjets","f");
  leg_example->AddEntry(total_DY_NoPUWt, "DY","f");
  leg_example->AddEntry(recoVtx_NoPUWt_TT, "t#bar{t}","f");
  //leg_example->AddEntry(recoVtx_NoPUWt_WJetsToLNu, "Wjets","f");
  leg_example->AddEntry(total_ST, "Single Top", "f");
  leg_example->AddEntry(total_diboson, "Diboson", "f");
  leg_example->AddEntry(total_QCD, "QCD", "f");
  leg_example->AddEntry(total_ZJets, "Z#rightarrow#nu#nu", "f");
  leg_example->AddEntry(recoVtx_NoPUWt_Wprime_M1000, "SSM W' 1 TeV", "l");
  leg_example->AddEntry(recoVtx_NoPUWt_Run2016E, "Data", "pl" );
  leg_example->Draw("same");
  my_canvas->Write();
  my_canvas->Print("recoVtx_NoPUWt.pdf");
  //

  TCanvas* my_canvas_2 = new TCanvas("canvas_2","canvas_2",800,600);
  my_canvas_2->cd();
  gPad->SetLogy();
  hs_2->Draw("HIST");                                                                                                                                        
  hs_2->SetMaximum(10000);
  hs_2->SetMinimum(0.1);
  hs_2->GetXaxis()->SetLimits(0, 60);
  hs_2->GetXaxis()->SetTitle("nVtx");
  hs_2->GetYaxis()->SetTitle("Events");
  TH1F* total_2 =  (TH1F*)hs_2->GetStack()->Last()->Clone();
  total_2->SetFillStyle(3004);                                                                                                                                      
  total_2->SetFillColor(kGray+1); 
  recoVtx_WithPUWt_Run2016E->Draw("SAME E0");
  recoVtx_WithPUWt_Wprime_M1000->Draw("SAME HIST");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");    
  lumiText->Draw("same");     
  TLatex* ExtraText2 = new TLatex(0.65,0.75,"After PU reweighting");
  ExtraText2->SetNDC();
  ExtraText2->SetTextFont(42);
  ExtraText2->SetTextSize(0.03);
  ExtraText2->SetTextAlign(32);
  ExtraText2->Draw("same");     

  TLegend *leg_example_2 = new TLegend(0.75,0.60,0.94,0.94);
  leg_example_2->SetFillColor(0);
  leg_example_2->SetTextFont(42);
  leg_example_2->SetBorderSize(0);
  leg_example_2->AddEntry(total_WJets_2, "Wjets","f");
  leg_example_2->AddEntry(total_DY_WithPUWt, "DY","f");
  leg_example_2->AddEntry(recoVtx_WithPUWt_TT, "t#bar{t}","f");
  leg_example_2->AddEntry(total_ST_2, "Single Top", "f");
  leg_example_2->AddEntry(total_diboson_2, "Diboson", "f");
  leg_example_2->AddEntry(total_QCD_2, "QCD", "f");
  leg_example_2->AddEntry(total_ZJets_2, "Z#rightarrow#nu#nu", "f");
  leg_example_2->AddEntry(recoVtx_WithPUWt_Wprime_M1000, "SSM W' 1 TeV", "l");
  leg_example_2->AddEntry(recoVtx_WithPUWt_Run2016E, "Data", "pl" );
  leg_example_2->Draw("same");
  my_canvas_2->Write();
  my_canvas_2->Print("recoVtx_WithPUWt.pdf");

  TCanvas* my_canvasA = new TCanvas("canvasA","canvasA");
  my_canvasA->cd();
  gPad->SetLogy();
  total->SetMaximum(10000);
  total->SetMarkerStyle(20);
  total->Draw("E");
  my_canvasA->Write();
  //
  TCanvas* my_canvasA_2 = new TCanvas("canvasA_2","canvasA_2");
  my_canvasA_2->cd();
  gPad->SetLogy();
  total_2->SetMaximum(10000);
  total_2->SetMarkerStyle(20);
  total_2->Draw("E");
  my_canvasA_2->Write();


  /*

  TCanvas* ratio_c = new TCanvas("ratio","ratio_canvas",800,700);
  ratio_c->SetTopMargin(0.); 
  ratio_c->SetBottomMargin(0.); 
  ratio_c->Update();
  ratio_c->Divide(1, 2);
  ratio_c->cd(1);
  gPad->SetPad(.005, .30, .995, .995);
  TPad* pad1 = (TPad*)ratio_c->GetPad(1); 
  pad1->SetTopMargin(0.05);
  pad1->SetBottomMargin(0.05); 
  ratio_c->Update();
  gPad->SetLogy();
  hs->Draw("HIST");                                                                                                                                        
  hs->SetMaximum(10000);
  hs->SetMinimum(0.1);
  hs->GetXaxis()->SetLimits(0, 60);
  hs->GetXaxis()->SetTitle("");
  // total->Draw("SAME E2");
  recoVtx_NoPUWt_Run2016D->Draw("SAME E1");
  recoVtx_NoPUWt_Wprime_M1000->Draw("SAME HIST");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  lumiText->Draw("same");
  leg_example->Draw("same");
  ExtraText->Draw("same");
  ratio_c->cd(2);
  gPad->SetPad(.005, .18, .995, .30); 
  gStyle->SetOptStat(false);
  ratio_c->Update();
  TPad* pad2 = (TPad*)ratio_c->GetPad(2);
  pad2->SetTopMargin(0.05); 
  pad2->SetBottomMargin(0.38); 
  pad2->SetGridx();
  pad2->SetGridy();
  TH1F* data_by_MC = (TH1F*)recoVtx_NoPUWt_Run2016D->Clone();
  data_by_MC->Divide(total);
  data_by_MC->SetMarkerStyle(20);
  data_by_MC->Draw("E");
  data_by_MC->GetXaxis()->SetLimits(0, 60);
  data_by_MC->GetXaxis()->SetTitle("nVtx");
  data_by_MC->GetYaxis()->SetTitle("#frac{DATA}{MC}");
  data_by_MC->GetYaxis()->SetLabelSize(0.16);
  data_by_MC->GetXaxis()->SetLabelSize(0.18);
  data_by_MC->GetYaxis()->SetTitleSize(0.20);
  data_by_MC->GetXaxis()->SetTitleSize(0.22);
  data_by_MC->GetYaxis()->SetTitleOffset(0.20);
  data_by_MC->GetXaxis()->SetTitleOffset(0.65);
  data_by_MC->SetTitle("");
  data_by_MC->SetMaximum(150);
  data_by_MC->SetMinimum(0);
  data_by_MC->GetYaxis()->SetNdivisions(5);
  ratio_c->Write();
  total->Write("totalMC");
  recoVtx_NoPUWt_Run2016D->Write("data");
  data_by_MC->Write("databymc");
  //

  TCanvas* ratio_c_2 = new TCanvas("ratio_2","ratio_canvas_2",800,700);
  ratio_c_2->SetTopMargin(0.); 
  ratio_c_2->SetBottomMargin(0.); 
  ratio_c_2->Update();
  ratio_c_2->Divide(1, 2);
  ratio_c_2->cd(1);
  gPad->SetPad(.005, .30, .995, .995);
  TPad* pad1_2 = (TPad*)ratio_c_2->GetPad(1); 
  pad1_2->SetTopMargin(0.05);
  pad1_2->SetBottomMargin(0.05); 
  ratio_c_2->Update();
  gPad->SetLogy();
  hs_2->Draw("HIST");                                                                                                                                        
  hs_2->SetMaximum(10000);
  hs_2->SetMinimum(0.1);
  hs_2->GetXaxis()->SetLimits(0, 60);
  hs_2->GetXaxis()->SetTitle("");
  // total->Draw("SAME E2");
  recoVtx_WithPUWt_Run2016D->Draw("SAME E1");
  recoVtx_WithPUWt_Wprime_M1000->Draw("SAME HIST");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  lumiText->Draw("same");
  leg_example_2->Draw("same");
  ExtraText2->Draw("same");
  ratio_c_2->cd(2);
  gPad->SetPad(.005, .18, .995, .30); 
  gStyle->SetOptStat(false);
  ratio_c_2->Update();
  TPad* pad2_2 = (TPad*)ratio_c_2->GetPad(2);
  pad2_2->SetTopMargin(0.05); 
  pad2_2->SetBottomMargin(0.38); 
  pad2_2->SetGridx();
  pad2_2->SetGridy();
  TH1F* data_by_MC_2 = (TH1F*)recoVtx_WithPUWt_Run2016D->Clone();
  data_by_MC_2->Divide(total);
  data_by_MC_2->SetMarkerStyle(20);
  data_by_MC_2->Draw("E");
  data_by_MC_2->GetXaxis()->SetLimits(0, 60);
  data_by_MC_2->GetXaxis()->SetTitle("nVtx");
  data_by_MC_2->GetYaxis()->SetTitle("#frac{DATA}{MC}");
  data_by_MC_2->GetYaxis()->SetLabelSize(0.16);
  data_by_MC_2->GetXaxis()->SetLabelSize(0.18);
  data_by_MC_2->GetYaxis()->SetTitleSize(0.20);
  data_by_MC_2->GetXaxis()->SetTitleSize(0.22);
  data_by_MC_2->GetYaxis()->SetTitleOffset(0.20);
  data_by_MC_2->GetXaxis()->SetTitleOffset(0.65);
  data_by_MC_2->SetTitle("");
  data_by_MC_2->SetMaximum(150);
  data_by_MC_2->SetMinimum(0);
  data_by_MC_2->GetYaxis()->SetNdivisions(5);
  ratio_c_2->Write();


  */

  return 0;

}
