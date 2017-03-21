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

int Plot_dphi_tau_MET_Stage2_DD() {

  double totalMC =0.0;
  double lumi= 35.865; //20.011 ;  // B->5.882  // C->2.646   D->4.353 ;  // E->4.049 ; F->3.16 ;  G->7.554;  H->5.942  //--inv fb--//

  unsigned long long evt_DYJetsToLL_M50=1;
  unsigned long long evt_DYJetsToLL_M5to50=1;
  unsigned long long evt_TT=1;
 
  TFile *file_DYJetsToLL_M50  = new TFile("../python/crab_projects_March3/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");             
  double xs_DYJetsToLL_M50=4895000;  //--fb--//                                                                                                                    

  TFile *file_DYJetsToLL_M5to50  = new TFile("../python/crab_projects_March3/crab_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");    
  double xs_DYJetsToLL_M5to50=7160000;  //--fb--//                                                                                                                    

  TFile *file_TT              = new TFile("../python/crab_projects_March3/crab_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/results/hist.root");
  double xs_TT=730000; //--fb--//
  double kfact_TT= 1.139;

  TFile *file_TT_Mtt_700to1000      = new TFile("../python/crab_projects_March3/crab_TT_Mtt-700to1000_TuneCUETP8M1_13TeV-powheg-pythia8/results/hist.root");
  double xs_TT_Mtt_700to1000=730000; //--fb--//
  double kfact_TT_Mtt_700to1000= 0.0921;

  TFile *file_TT_Mtt_1000toInf              = new TFile("../python/crab_projects_March3/crab_TT_Mtt-1000toInf_TuneCUETP8M1_13TeV-powheg-pythia8/results/hist.root");
  double xs_TT_Mtt_1000toInf=730000; //--fb--//
  double kfact_TT_Mtt_1000toInf= 0.02474;


  //TFile *file_WJetsToLNu      = new TFile("../python/crab_projects_March3/crab_WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/results/hist.root");
  //double xs_WJetsToLNu=60290000; //--fb--//

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

  TFile *file_ST_tchannel_antitop=new TFile("../python/crab_projects_March3/crab_ST_t-channel_antitop_4f_inclusiveDecays_TuneCUETP8M2T4_13TeV-powhegV2-madspin/results/hist.root");
  double xs_ST_tchannel_antitop = 80950; //--fb--//
  double kfact_ST_tchannel_antitop = 1.0; //0.326;
  //
  TFile *file_ST_tchannel_top=new TFile("../python/crab_projects_March3/crab_ST_t-channel_top_4f_inclusiveDecays_TuneCUETP8M2T4_13TeV-powhegV2-madspin/results/hist.root");
  double xs_ST_tchannel_top =136020; //103200; //--fb--//
  double kfact_ST_tchannel_top = 1.0; //0.43;
  //
  TFile *file_ST_tW_antitop=new TFile("../python/crab_projects_March3/crab_ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4/results/hist.root");
  double xs_ST_tW_antitop = 38090; //--fb--//
  double kfact_ST_tW_antitop =1.0; // 0.94;
  //
  TFile *file_ST_tW_top=new TFile("../python/crab_projects_March3/crab_ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4/results/hist.root");
  double xs_ST_tW_top = 38090; //--fb--//
  double kfact_ST_tW_top = 1.0; //0.94;
  //
  TFile *file_WW=new TFile("../python/crab_projects_March3/crab_WW_TuneCUETP8M1_13TeV-pythia8/results/hist.root");
  double xs_WW = 63210; //--fb--//
  //
  TFile *file_WZ=new TFile("../python/crab_projects_March3/crab_WZ_TuneCUETP8M1_13TeV-pythia8/results/hist.root");
  double xs_WZ = 22820; //--fb--//
  double kfact_WZ = 2.06; // 47.13/22.82
  //
  TFile *file_ZZ=new TFile("../python/crab_projects_March3/crab_ZZ_TuneCUETP8M1_13TeV-pythia8/results/hist.root");
  double xs_ZZ = 10320; //--fb--//
  double kfact_ZZ = 1.60 ; //16523/10320
  //
  std::cout << "get datadriven root file" << std::endl;
  TFile *file_Datadriven  = new TFile("/net/scratch_cms3a/materok/wprime/qcd/dataDrivenTree15_pt_base_Mar7_fromData.root");


  /// DATA ///
  TFile *file_Tau_Run2016B = new TFile("../python/crab_projects_March3/crab_Tau_Run2016B/results/hist.root");
  TFile *file_Tau_Run2016C = new TFile("../python/crab_projects_March3/crab_Tau_Run2016C/results/hist.root");
  TFile *file_Tau_Run2016D = new TFile("../python/crab_projects_March3/crab_Tau_Run2016D/results/hist.root");
  TFile *file_Tau_Run2016E = new TFile("../python/crab_projects_March3/crab_Tau_Run2016E/results/hist.root");
  TFile *file_Tau_Run2016F = new TFile("../python/crab_projects_March3/crab_Tau_Run2016F/results/hist.root");
  TFile *file_Tau_Run2016G = new TFile("../python/crab_projects_March3/crab_Tau_Run2016G/results/hist.root");
  TFile *file_Tau_Run2016H_v2 = new TFile("../python/crab_projects_March3/crab_Tau_Run2016H_1/results/hist.root");
  TFile *file_Tau_Run2016H_v3 = new TFile("../python/crab_projects_March3/crab_Tau_Run2016H_2/results/hist.root");


  /// Signal ///
  TFile *file_Wprime_M4000 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M-4000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_Wprime_M4000= 2.04; // --fb-- //

  //--//
  TH1D* h1_evt_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/eventCount");
  evt_DYJetsToLL_M50 = h1_evt_DYJetsToLL_M50->GetEntries(); // Integral();
  double wt_DYJetsToLL_M50 = (xs_DYJetsToLL_M50*lumi)/evt_DYJetsToLL_M50 ;
  TH1D* dphi_tau_MET_Stage2_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/dphi_tau_MET_Stage2");
  dphi_tau_MET_Stage2_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  std::cout << "DYJetsToLL_M50 weighted nevt=" << dphi_tau_MET_Stage2_DYJetsToLL_M50->Integral() << std::endl;
  totalMC += dphi_tau_MET_Stage2_DYJetsToLL_M50->Integral();

  TH1D* h1_evt_DYJetsToLL_M5to50 = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/eventCount");
  evt_DYJetsToLL_M5to50 = h1_evt_DYJetsToLL_M5to50->GetEntries(); // Integral();
  double wt_DYJetsToLL_M5to50 = (xs_DYJetsToLL_M5to50*lumi)/evt_DYJetsToLL_M5to50 ;
  TH1D* dphi_tau_MET_Stage2_DYJetsToLL_M5to50 = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/dphi_tau_MET_Stage2");
  dphi_tau_MET_Stage2_DYJetsToLL_M5to50->Scale(wt_DYJetsToLL_M5to50);
  std::cout << "DYJetsToLL_M5to50 weighted nevt=" << dphi_tau_MET_Stage2_DYJetsToLL_M5to50->Integral() << std::endl;
  totalMC += dphi_tau_MET_Stage2_DYJetsToLL_M5to50->Integral() ;
  //
  TH1D* total_DY = (TH1D*)dphi_tau_MET_Stage2_DYJetsToLL_M50->Clone(); 
  total_DY->Add(dphi_tau_MET_Stage2_DYJetsToLL_M5to50);
  total_DY->SetFillColorAlpha(kRed,0.5);
  total_DY->SetLineColor(kBlack);
  total_DY->Rebin(25);
  //

  TH1D* h1_evt_TT = (TH1D*)file_TT->Get("demo/histoDir/eventCount");
  evt_TT = h1_evt_TT->GetEntries(); // Integral();
  double wt_TT = (xs_TT*lumi)/evt_TT ;
  TH1D* dphi_tau_MET_Stage2_TT  = (TH1D*)file_TT->Get("demo/histoDir/dphi_tau_MET_Stage2");
  dphi_tau_MET_Stage2_TT->Scale(wt_TT);
  dphi_tau_MET_Stage2_TT->Scale(kfact_TT);
  std::cout << "TTbar weighted nevt=" << dphi_tau_MET_Stage2_TT->Integral() << std::endl;
  totalMC += dphi_tau_MET_Stage2_TT->Integral();

  //file_TT_Mtt_700to1000
  TH1D* h1_evt_TT_Mtt_700to1000 = (TH1D*)file_TT_Mtt_700to1000->Get("demo/histoDir/eventCount");
  evt_TT_Mtt_700to1000 = h1_evt_TT_Mtt_700to1000->GetEntries(); // Integral();
  double wt_TT_Mtt_700to1000 = (xs_TT_Mtt_700to1000*lumi)/evt_TT_Mtt_700to1000 ;
  TH1D* dphi_tau_MET_Stage2_TT_Mtt_700to1000  = (TH1D*)file_TT_Mtt_700to1000->Get("demo/histoDir/dphi_tau_MET_Stage2");
  dphi_tau_MET_Stage2_TT_Mtt_700to1000->Scale(wt_TT_Mtt_700to1000);
  dphi_tau_MET_Stage2_TT_Mtt_700to1000->Scale(kfact_TT_Mtt_700to1000);
  std::cout << "TT_Mtt_700to1000bar weighted nevt=" << dphi_tau_MET_Stage2_TT_Mtt_700to1000->Integral() << std::endl;
  totalMC += dphi_tau_MET_Stage2_TT_Mtt_700to1000->Integral() ;

  //file_TT_Mtt_1000toInf
  TH1D* h1_evt_TT_Mtt_1000toInf = (TH1D*)file_TT_Mtt_1000toInf->Get("demo/histoDir/eventCount");
  evt_TT_Mtt_1000toInf = h1_evt_TT_Mtt_1000toInf->GetEntries(); // Integral();
  double wt_TT_Mtt_1000toInf = (xs_TT_Mtt_1000toInf*lumi)/evt_TT_Mtt_1000toInf ;
  TH1D* dphi_tau_MET_Stage2_TT_Mtt_1000toInf  = (TH1D*)file_TT_Mtt_1000toInf->Get("demo/histoDir/dphi_tau_MET_Stage2");
  dphi_tau_MET_Stage2_TT_Mtt_1000toInf->Scale(wt_TT_Mtt_1000toInf);
  dphi_tau_MET_Stage2_TT_Mtt_1000toInf->Scale(kfact_TT_Mtt_1000toInf);
  std::cout << "TT_Mtt_1000toInfbar weighted nevt=" << dphi_tau_MET_Stage2_TT_Mtt_1000toInf->Integral() << std::endl;
  totalMC += dphi_tau_MET_Stage2_TT_Mtt_1000toInf->Integral() ;

  TH1D* total_TT = (TH1D*)dphi_tau_MET_Stage2_TT->Clone(); 
  total_TT->Add(dphi_tau_MET_Stage2_TT_Mtt_700to1000);
  total_TT->Add(dphi_tau_MET_Stage2_TT_Mtt_1000toInf);
  total_TT->SetFillColor(kBlue-7);
  total_TT->SetLineColor(kBlack);
  total_TT->Rebin(25);


  /*
  TH1D* h1_evt_WJetsToLNu = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/eventCount");
  evt_WJetsToLNu = h1_evt_WJetsToLNu->GetEntries(); //Integral();
  std::cout << "evt_WJetsToLNu = " << evt_WJetsToLNu << std::endl;
  double wt_WJetsToLNu = (xs_WJetsToLNu*lumi)/evt_WJetsToLNu ;
  TH1D* dphi_tau_MET_Stage2_WJetsToLNu  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/dphi_tau_MET_Stage2");
  // Poisson error //
  dphi_tau_MET_Stage2_WJetsToLNu->Sumw2(kFALSE);
  dphi_tau_MET_Stage2_WJetsToLNu->SetBinErrorOption(TH1::kPoisson);
  std::cout << "**WJets** unweighted nevt=" << dphi_tau_MET_Stage2_WJetsToLNu->Integral() << std::endl;
  std::cout << "wt_WJetsToLNu = " << wt_WJetsToLNu << std::endl;
  dphi_tau_MET_Stage2_WJetsToLNu->Scale(wt_WJetsToLNu);
  dphi_tau_MET_Stage2_WJetsToLNu->SetFillColorAlpha(kGreen-7,0.5);
  dphi_tau_MET_Stage2_WJetsToLNu->SetLineColor(kGreen-7);
  dphi_tau_MET_Stage2_WJetsToLNu->Rebin(40);
  std::cout << "**WJets** weighted nevt=" << dphi_tau_MET_Stage2_WJetsToLNu->Integral() << std::endl;
  */

  //file_ST_tchannel_antitop
  TH1D* h1_evt_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/eventCount");
  unsigned long long evt_ST_tchannel_antitop = h1_evt_ST_tchannel_antitop->GetEntries(); //Integral();
  double wt_ST_tchannel_antitop = (xs_ST_tchannel_antitop*lumi)/evt_ST_tchannel_antitop ;
  TH1D* dphi_tau_MET_Stage2_ST_tchannel_antitop  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/dphi_tau_MET_Stage2");
  dphi_tau_MET_Stage2_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  dphi_tau_MET_Stage2_ST_tchannel_antitop->Scale(kfact_ST_tchannel_antitop);
  std::cout << "ST_tchannel_antitop weighted nevt=" << dphi_tau_MET_Stage2_ST_tchannel_antitop->Integral() << std::endl;
  totalMC += dphi_tau_MET_Stage2_ST_tchannel_antitop->Integral();

  //file_ST_tchannel_top
  TH1D* h1_evt_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/eventCount");
  unsigned long long evt_ST_tchannel_top = h1_evt_ST_tchannel_top->GetEntries(); //Integral();
  double wt_ST_tchannel_top = (xs_ST_tchannel_top*lumi)/evt_ST_tchannel_top ;
  TH1D* dphi_tau_MET_Stage2_ST_tchannel_top  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/dphi_tau_MET_Stage2");
  dphi_tau_MET_Stage2_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  dphi_tau_MET_Stage2_ST_tchannel_top->Scale(kfact_ST_tchannel_top);
  std::cout << "ST_tchannel_top weighted nevt=" << dphi_tau_MET_Stage2_ST_tchannel_top->Integral() << std::endl;
  totalMC += dphi_tau_MET_Stage2_ST_tchannel_top->Integral() ;

  //file_ST_tW_antitop
  TH1D* h1_evt_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/eventCount");
  unsigned long long evt_ST_tW_antitop = h1_evt_ST_tW_antitop->GetEntries(); //Integral();
  double wt_ST_tW_antitop = (xs_ST_tW_antitop*lumi)/evt_ST_tW_antitop ;
  TH1D* dphi_tau_MET_Stage2_ST_tW_antitop  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/dphi_tau_MET_Stage2");
  dphi_tau_MET_Stage2_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  dphi_tau_MET_Stage2_ST_tW_antitop->Scale(kfact_ST_tW_antitop);
  std::cout << "ST_tW_antitop weighted nevt=" << dphi_tau_MET_Stage2_ST_tW_antitop->Integral() << std::endl;
  totalMC += dphi_tau_MET_Stage2_ST_tW_antitop->Integral();

  //file_ST_tW_top
  TH1D* h1_evt_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/histoDir/eventCount");
  unsigned long long evt_ST_tW_top = h1_evt_ST_tW_top->GetEntries(); //Integral();
  double wt_ST_tW_top = (xs_ST_tW_top*lumi)/evt_ST_tW_top ;
  TH1D* dphi_tau_MET_Stage2_ST_tW_top  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/dphi_tau_MET_Stage2");
  dphi_tau_MET_Stage2_ST_tW_top->Scale(wt_ST_tW_top);
  dphi_tau_MET_Stage2_ST_tW_top->Scale(kfact_ST_tW_top);
  std::cout << "ST_tW_top weighted nevt=" << dphi_tau_MET_Stage2_ST_tW_top->Integral() << std::endl;
  totalMC += dphi_tau_MET_Stage2_ST_tW_top->Integral() ;

  TH1D* total_ST = (TH1D*)dphi_tau_MET_Stage2_ST_tchannel_antitop->Clone(); 
  total_ST->Add(dphi_tau_MET_Stage2_ST_tchannel_top);
  total_ST->Add(dphi_tau_MET_Stage2_ST_tW_antitop);
  total_ST->Add(dphi_tau_MET_Stage2_ST_tW_top);
  total_ST->SetFillColorAlpha(kCyan,0.5);
  total_ST->SetLineColor(kBlack);
  total_ST->Rebin(25);

  //file_WJetsToLNu_HT100To200
  TH1D* h1_evt_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT100To200 = h1_evt_WJetsToLNu_HT100To200->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT100To200 = (xs_WJetsToLNu_HT100To200*lumi)/evt_WJetsToLNu_HT100To200 ;
  TH1D* dphi_tau_MET_Stage2_WJetsToLNu_HT100To200  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/dphi_tau_MET_Stage2");
  // Poisson error //                           
  //  dphi_tau_MET_Stage2_WJetsToLNu_HT100To200->Sumw2(kFALSE);
  //dphi_tau_MET_Stage2_WJetsToLNu_HT100To200->SetBinErrorOption(TH1::kPoisson);
  dphi_tau_MET_Stage2_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  std::cout << "WJetsToLNu_HT100To200 weighted nevt=" << dphi_tau_MET_Stage2_WJetsToLNu_HT100To200->Integral() << std::endl;
  totalMC += dphi_tau_MET_Stage2_WJetsToLNu_HT100To200->Integral();
  //dphi_tau_MET_Stage2_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);
  //  std::cout << dphi_tau_MET_Stage2_WJetsToLNu_HT100To200->GetBinError(300) << std::endl;

  //file_WJetsToLNu_HT200To400
  TH1D* h1_evt_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT200To400 = h1_evt_WJetsToLNu_HT200To400->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT200To400 = (xs_WJetsToLNu_HT200To400*lumi)/evt_WJetsToLNu_HT200To400 ;
  TH1D* dphi_tau_MET_Stage2_WJetsToLNu_HT200To400  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/dphi_tau_MET_Stage2");
  // Poisson error //                                                                                                                                                      
  // dphi_tau_MET_Stage2_WJetsToLNu_HT200To400->Sumw2(kFALSE);
  //dphi_tau_MET_Stage2_WJetsToLNu_HT200To400->SetBinErrorOption(TH1::kPoisson);
  dphi_tau_MET_Stage2_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
 std::cout << "WJetsToLNu_HT200To400 weighted nevt=" << dphi_tau_MET_Stage2_WJetsToLNu_HT200To400->Integral() << std::endl;
 totalMC += dphi_tau_MET_Stage2_WJetsToLNu_HT200To400->Integral();
  //dphi_tau_MET_Stage2_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);
  //std::cout << dphi_tau_MET_Stage2_WJetsToLNu_HT200To400->GetBinError(300) << std::endl;

  //file_WJetsToLNu_HT400To600
  TH1D* h1_evt_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT400To600 = h1_evt_WJetsToLNu_HT400To600->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT400To600 = (xs_WJetsToLNu_HT400To600*lumi)/evt_WJetsToLNu_HT400To600 ;
  TH1D* dphi_tau_MET_Stage2_WJetsToLNu_HT400To600  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/dphi_tau_MET_Stage2");
  // Poisson error //                                                                                                                                                      
  // dphi_tau_MET_Stage2_WJetsToLNu_HT400To600->Sumw2(kFALSE);
  //dphi_tau_MET_Stage2_WJetsToLNu_HT400To600->SetBinErrorOption(TH1::kPoisson);
  dphi_tau_MET_Stage2_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  std::cout << "WJetsToLNu_HT400To600 weighted nevt=" << dphi_tau_MET_Stage2_WJetsToLNu_HT400To600->Integral() << std::endl;
  totalMC += dphi_tau_MET_Stage2_WJetsToLNu_HT400To600->Integral();
  // dphi_tau_MET_Stage2_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);
  // std::cout << dphi_tau_MET_Stage2_WJetsToLNu_HT400To600->GetBinError(300) << std::endl;

  //file_WJetsToLNu_HT600To800
  TH1D* h1_evt_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT600To800 = h1_evt_WJetsToLNu_HT600To800->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT600To800 = (xs_WJetsToLNu_HT600To800*lumi)/evt_WJetsToLNu_HT600To800 ;
  TH1D* dphi_tau_MET_Stage2_WJetsToLNu_HT600To800  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/dphi_tau_MET_Stage2");
  // Poisson error //                                                                                                                                                      
  //  dphi_tau_MET_Stage2_WJetsToLNu_HT600To800->Sumw2(kFALSE);
  // dphi_tau_MET_Stage2_WJetsToLNu_HT600To800->SetBinErrorOption(TH1::kPoisson);
  dphi_tau_MET_Stage2_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  std::cout << "WJetsToLNu_HT600To800 weighted nevt=" << dphi_tau_MET_Stage2_WJetsToLNu_HT600To800->Integral() << std::endl;
  totalMC +=  dphi_tau_MET_Stage2_WJetsToLNu_HT600To800->Integral();
  // dphi_tau_MET_Stage2_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);
  // std::cout << dphi_tau_MET_Stage2_WJetsToLNu_HT600To800->GetBinError(300) << std::endl;

  //file_WJetsToLNu_HT800To1200
  TH1D* h1_evt_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT800To1200 = h1_evt_WJetsToLNu_HT800To1200->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT800To1200 = (xs_WJetsToLNu_HT800To1200*lumi)/evt_WJetsToLNu_HT800To1200 ;
  TH1D* dphi_tau_MET_Stage2_WJetsToLNu_HT800To1200  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/dphi_tau_MET_Stage2");
  // Poisson error //                                                                                                                                                      
  // dphi_tau_MET_Stage2_WJetsToLNu_HT800To1200->Sumw2(kFALSE);
  //dphi_tau_MET_Stage2_WJetsToLNu_HT800To1200->SetBinErrorOption(TH1::kPoisson);
  dphi_tau_MET_Stage2_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
 std::cout << "WJetsToLNu_HT800To1200 weighted nevt=" << dphi_tau_MET_Stage2_WJetsToLNu_HT800To1200->Integral() << std::endl;
 totalMC += dphi_tau_MET_Stage2_WJetsToLNu_HT800To1200->Integral();
  //dphi_tau_MET_Stage2_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);
  // std::cout << dphi_tau_MET_Stage2_WJetsToLNu_HT800To1200->GetBinError(300) << std::endl;

  //file_WJetsToLNu_HT1200To2500
  TH1D* h1_evt_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT1200To2500 = h1_evt_WJetsToLNu_HT1200To2500->GetEntries(); //Integral();                                                             
  double wt_WJetsToLNu_HT1200To2500 = (xs_WJetsToLNu_HT1200To2500*lumi)/evt_WJetsToLNu_HT1200To2500 ;
  TH1D* dphi_tau_MET_Stage2_WJetsToLNu_HT1200To2500  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/dphi_tau_MET_Stage2");
  // Poisson error //                                                                                                                                                      
  // dphi_tau_MET_Stage2_WJetsToLNu_HT1200To2500->Sumw2(kFALSE);
  //dphi_tau_MET_Stage2_WJetsToLNu_HT1200To2500->SetBinErrorOption(TH1::kPoisson);
  dphi_tau_MET_Stage2_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
 std::cout << "WJetsToLNu_HT1200To2500 weighted nevt=" << dphi_tau_MET_Stage2_WJetsToLNu_HT1200To2500->Integral() << std::endl;
 totalMC += dphi_tau_MET_Stage2_WJetsToLNu_HT1200To2500->Integral();
  // dphi_tau_MET_Stage2_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);
  //std::cout << dphi_tau_MET_Stage2_WJetsToLNu_HT1200To2500->GetBinError(300) << std::endl;

  //file_WJetsToLNu_HT2500ToInf
  TH1D* h1_evt_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT2500ToInf = h1_evt_WJetsToLNu_HT2500ToInf->GetEntries(); //Integral();                                                             
  double wt_WJetsToLNu_HT2500ToInf = (xs_WJetsToLNu_HT2500ToInf*lumi)/evt_WJetsToLNu_HT2500ToInf ;
  TH1D* dphi_tau_MET_Stage2_WJetsToLNu_HT2500ToInf  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/dphi_tau_MET_Stage2");
  // Poisson error //                                                                                                                                                      
  //dphi_tau_MET_Stage2_WJetsToLNu_HT2500ToInf->Sumw2(kFALSE);
  //dphi_tau_MET_Stage2_WJetsToLNu_HT2500ToInf->SetBinErrorOption(TH1::kPoisson);
  dphi_tau_MET_Stage2_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
 std::cout << "WJetsToLNu_HT2500ToInf weighted nevt=" << dphi_tau_MET_Stage2_WJetsToLNu_HT2500ToInf->Integral() << std::endl;
 totalMC += dphi_tau_MET_Stage2_WJetsToLNu_HT2500ToInf->Integral();
  //dphi_tau_MET_Stage2_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);
  ///std::cout << dphi_tau_MET_Stage2_WJetsToLNu_HT2500ToInf->GetBinError(300) << std::endl;

  //file_WToTauNu_M100
  TH1D* h1_evt_WToTauNu_M100 = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M100 = h1_evt_WToTauNu_M100->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M100 = (xs_WToTauNu_M100*lumi)/evt_WToTauNu_M100 ;
  TH1D* dphi_tau_MET_Stage2_WToTauNu_M100  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/dphi_tau_MET_Stage2");
  dphi_tau_MET_Stage2_WToTauNu_M100->Scale(wt_WToTauNu_M100);
 std::cout << "WToTauNu_M100 weighted nevt=" << dphi_tau_MET_Stage2_WToTauNu_M100->Integral() << std::endl;
 totalMC += dphi_tau_MET_Stage2_WToTauNu_M100->Integral() ;

  //file_WToTauNu_M200
  TH1D* h1_evt_WToTauNu_M200 = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M200 = h1_evt_WToTauNu_M200->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M200 = (xs_WToTauNu_M200*lumi)/evt_WToTauNu_M200 ;
  TH1D* dphi_tau_MET_Stage2_WToTauNu_M200  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/dphi_tau_MET_Stage2");
  dphi_tau_MET_Stage2_WToTauNu_M200->Scale(wt_WToTauNu_M200);
 std::cout << "WToTauNu_M200 weighted nevt=" << dphi_tau_MET_Stage2_WToTauNu_M200->Integral() << std::endl;
 totalMC += dphi_tau_MET_Stage2_WToTauNu_M200->Integral();

  //file_WToTauNu_M500
  TH1D* h1_evt_WToTauNu_M500 = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M500 = h1_evt_WToTauNu_M500->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M500 = (xs_WToTauNu_M500*lumi)/evt_WToTauNu_M500 ;
  TH1D* dphi_tau_MET_Stage2_WToTauNu_M500  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/dphi_tau_MET_Stage2");
  dphi_tau_MET_Stage2_WToTauNu_M500->Scale(wt_WToTauNu_M500);
 std::cout << "WToTauNu_M500 weighted nevt=" << dphi_tau_MET_Stage2_WToTauNu_M500->Integral() << std::endl;
 totalMC += dphi_tau_MET_Stage2_WToTauNu_M500->Integral() ;

  //file_WToTauNu_M1000
  TH1D* h1_evt_WToTauNu_M1000 = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M1000 = h1_evt_WToTauNu_M1000->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M1000 = (xs_WToTauNu_M1000*lumi)/evt_WToTauNu_M1000 ;
  TH1D* dphi_tau_MET_Stage2_WToTauNu_M1000  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/dphi_tau_MET_Stage2");
  dphi_tau_MET_Stage2_WToTauNu_M1000->Scale(wt_WToTauNu_M1000);
 std::cout << "WToTauNu_M1000 weighted nevt=" << dphi_tau_MET_Stage2_WToTauNu_M1000->Integral() << std::endl;
 totalMC += dphi_tau_MET_Stage2_WToTauNu_M1000->Integral();

  //file_WToTauNu_M2000
  TH1D* h1_evt_WToTauNu_M2000 = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M2000 = h1_evt_WToTauNu_M2000->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M2000 = (xs_WToTauNu_M2000*lumi)/evt_WToTauNu_M2000 ;
  TH1D* dphi_tau_MET_Stage2_WToTauNu_M2000  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/dphi_tau_MET_Stage2");
  dphi_tau_MET_Stage2_WToTauNu_M2000->Scale(wt_WToTauNu_M2000);
 std::cout << "WToTauNu_M2000 weighted nevt=" << dphi_tau_MET_Stage2_WToTauNu_M2000->Integral() << std::endl;
 totalMC += dphi_tau_MET_Stage2_WToTauNu_M2000->Integral();

  //file_WToTauNu_M3000
  TH1D* h1_evt_WToTauNu_M3000 = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M3000 = h1_evt_WToTauNu_M3000->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M3000 = (xs_WToTauNu_M3000*lumi)/evt_WToTauNu_M3000 ;
  TH1D* dphi_tau_MET_Stage2_WToTauNu_M3000  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/dphi_tau_MET_Stage2");
  dphi_tau_MET_Stage2_WToTauNu_M3000->Scale(wt_WToTauNu_M3000);
 std::cout << "WToTauNu_M3000 weighted nevt=" << dphi_tau_MET_Stage2_WToTauNu_M3000->Integral() << std::endl;
 totalMC += dphi_tau_MET_Stage2_WToTauNu_M3000->Integral();

  //file_WToTauNu_M4000
  TH1D* h1_evt_WToTauNu_M4000 = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M4000 = h1_evt_WToTauNu_M4000->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M4000 = (xs_WToTauNu_M4000*lumi)/evt_WToTauNu_M4000 ;
  TH1D* dphi_tau_MET_Stage2_WToTauNu_M4000  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/dphi_tau_MET_Stage2");
  dphi_tau_MET_Stage2_WToTauNu_M4000->Scale(wt_WToTauNu_M4000);
 std::cout << "WToTauNu_M4000 weighted nevt=" << dphi_tau_MET_Stage2_WToTauNu_M4000->Integral() << std::endl;
 totalMC += dphi_tau_MET_Stage2_WToTauNu_M4000->Integral();

  //file_WToTauNu_M5000
  TH1D* h1_evt_WToTauNu_M5000 = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M5000 = h1_evt_WToTauNu_M5000->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M5000 = (xs_WToTauNu_M5000*lumi)/evt_WToTauNu_M5000 ;
  TH1D* dphi_tau_MET_Stage2_WToTauNu_M5000  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/dphi_tau_MET_Stage2");
  dphi_tau_MET_Stage2_WToTauNu_M5000->Scale(wt_WToTauNu_M5000);
 std::cout << "WToTauNu_M5000 weighted nevt=" << dphi_tau_MET_Stage2_WToTauNu_M5000->Integral() << std::endl;
 totalMC += dphi_tau_MET_Stage2_WToTauNu_M5000->Integral();

  //file_WToTauNu_M6000
  TH1D* h1_evt_WToTauNu_M6000 = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M6000 = h1_evt_WToTauNu_M6000->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M6000 = (xs_WToTauNu_M6000*lumi)/evt_WToTauNu_M6000 ;
  TH1D* dphi_tau_MET_Stage2_WToTauNu_M6000  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/dphi_tau_MET_Stage2");
  dphi_tau_MET_Stage2_WToTauNu_M6000->Scale(wt_WToTauNu_M6000);
 std::cout << "WToTauNu_M6000 weighted nevt=" << dphi_tau_MET_Stage2_WToTauNu_M6000->Integral() << std::endl;
 totalMC += dphi_tau_MET_Stage2_WToTauNu_M6000->Integral();

  //file_WJetsToLNu
  TH1D* h1_evt_WJetsToLNu = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu = h1_evt_WJetsToLNu->GetEntries(); //Integral();                                                             
  double wt_WJetsToLNu = (xs_WJetsToLNu*lumi)/evt_WJetsToLNu ;
  TH1D* dphi_tau_MET_Stage2_WJetsToLNu  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/dphi_tau_MET_Stage2");
  dphi_tau_MET_Stage2_WJetsToLNu->Scale(wt_WJetsToLNu);
 std::cout << "WJetsToLNu weighted nevt=" << dphi_tau_MET_Stage2_WJetsToLNu->Integral() << std::endl;
 totalMC += dphi_tau_MET_Stage2_WJetsToLNu->Integral();

  TH1D* total_WJets = (TH1D*)dphi_tau_MET_Stage2_WJetsToLNu_HT100To200->Clone();
  total_WJets->Add(dphi_tau_MET_Stage2_WJetsToLNu_HT200To400);
  total_WJets->Add(dphi_tau_MET_Stage2_WJetsToLNu_HT400To600);
  total_WJets->Add(dphi_tau_MET_Stage2_WJetsToLNu_HT600To800);
  total_WJets->Add(dphi_tau_MET_Stage2_WJetsToLNu_HT800To1200);
  total_WJets->Add(dphi_tau_MET_Stage2_WJetsToLNu_HT1200To2500);
  total_WJets->Add(dphi_tau_MET_Stage2_WJetsToLNu_HT2500ToInf);
  total_WJets->Add(dphi_tau_MET_Stage2_WToTauNu_M100);
  total_WJets->Add(dphi_tau_MET_Stage2_WToTauNu_M200);
  total_WJets->Add(dphi_tau_MET_Stage2_WToTauNu_M500);
  total_WJets->Add(dphi_tau_MET_Stage2_WToTauNu_M1000);
  total_WJets->Add(dphi_tau_MET_Stage2_WToTauNu_M2000);
  total_WJets->Add(dphi_tau_MET_Stage2_WToTauNu_M3000);
  total_WJets->Add(dphi_tau_MET_Stage2_WToTauNu_M4000);
  total_WJets->Add(dphi_tau_MET_Stage2_WToTauNu_M5000);
  total_WJets->Add(dphi_tau_MET_Stage2_WToTauNu_M6000);
  total_WJets->Add(dphi_tau_MET_Stage2_WJetsToLNu);
  total_WJets->SetFillColorAlpha(kGreen-8,0.5);
  total_WJets->SetLineColor(kBlack);
  //std::cout << "Wjets " << total_WJets->GetBinError(300) << std::endl;

  total_WJets->Rebin(25);


  //file_WW
  TH1D* h1_evt_WW = (TH1D*)file_WW->Get("demo/histoDir/eventCount");
  unsigned long long evt_WW = h1_evt_WW->GetEntries(); //Integral();                                                                         
  double wt_WW = (xs_WW*lumi)/evt_WW ;
  TH1D* dphi_tau_MET_Stage2_WW  = (TH1D*)file_WW->Get("demo/histoDir/dphi_tau_MET_Stage2");
  // Poisson error //
  //dphi_tau_MET_Stage2_WW->Sumw2(kFALSE);
  //dphi_tau_MET_Stage2_WW->SetBinErrorOption(TH1::kPoisson);
  dphi_tau_MET_Stage2_WW->Scale(wt_WW);
 std::cout << "WW weighted nevt=" << dphi_tau_MET_Stage2_WW->Integral() << std::endl;
 totalMC +=dphi_tau_MET_Stage2_WW->Integral() ;

  //file_WZ
  TH1D* h1_evt_WZ = (TH1D*)file_WZ->Get("demo/histoDir/eventCount");
  unsigned long long evt_WZ = h1_evt_WZ->GetEntries(); //Integral();                                                                         
  double wt_WZ = (xs_WZ*lumi)/evt_WZ ;
  TH1D* dphi_tau_MET_Stage2_WZ  = (TH1D*)file_WZ->Get("demo/histoDir/dphi_tau_MET_Stage2");
  // Poisson error //
  //dphi_tau_MET_Stage2_WZ->Sumw2(kFALSE);
  // dphi_tau_MET_Stage2_WZ->SetBinErrorOption(TH1::kPoisson);
  dphi_tau_MET_Stage2_WZ->Scale(wt_WZ);
  dphi_tau_MET_Stage2_WZ->Scale(kfact_WZ);
 std::cout << "WZ weighted nevt=" << dphi_tau_MET_Stage2_WZ->Integral() << std::endl;
 totalMC +=  dphi_tau_MET_Stage2_WZ->Integral();

  //file_ZZ
  TH1D* h1_evt_ZZ = (TH1D*)file_ZZ->Get("demo/histoDir/eventCount");
  unsigned long long evt_ZZ = h1_evt_ZZ->GetEntries(); //Integral();                                                                         
  double wt_ZZ = (xs_ZZ*lumi)/evt_ZZ ;
  TH1D* dphi_tau_MET_Stage2_ZZ  = (TH1D*)file_ZZ->Get("demo/histoDir/dphi_tau_MET_Stage2");
  // Poisson error //
  //dphi_tau_MET_Stage2_ZZ->Sumw2(kFALSE);
  //dphi_tau_MET_Stage2_ZZ->SetBinErrorOption(TH1::kPoisson);
  dphi_tau_MET_Stage2_ZZ->Scale(wt_ZZ);
  dphi_tau_MET_Stage2_ZZ->Scale(kfact_ZZ);
 std::cout << "ZZ weighted nevt=" << dphi_tau_MET_Stage2_ZZ->Integral() << std::endl;
 totalMC += dphi_tau_MET_Stage2_ZZ->Integral();

  TH1D* total_diboson = (TH1D*)dphi_tau_MET_Stage2_WW->Clone();
  total_diboson->Add(dphi_tau_MET_Stage2_WZ);
  total_diboson->Add(dphi_tau_MET_Stage2_ZZ);
  total_diboson->SetFillColorAlpha(kOrange+2,0.5);
  total_diboson->SetLineColor(kBlack);
  total_diboson->Rebin(25);


  //datadriven                                                                                                                                                                                                           
  //  double wt_Datadriven = (lumi/33.507) ;                                                                                                                                                                             
  TH1D* total_QCD = (TH1D*)file_Datadriven->Get("demo/histoDir/dphi_tau_MET_Stage2");
  total_QCD->SetFillStyle(3001);
  total_QCD->SetFillColor(kPink+1);
  total_QCD->SetLineColor(kBlack);
  total_QCD->Rebin(25);  //datadriven                                                                                                                                                                                  

  std::cout << "totalMC(w/o DD) =" << totalMC << std::endl;

   std::cout << "will do data" << std::endl;
  
  //--Data--//
   TH1D* dphi_tau_MET_Stage2_Run2016F  =  (TH1D*)file_Tau_Run2016F->Get("demo/histoDir/dphi_tau_MET_Stage2");
   TH1D* dphi_tau_MET_Stage2_Run2016E  =  (TH1D*)file_Tau_Run2016E->Get("demo/histoDir/dphi_tau_MET_Stage2");
   TH1D* dphi_tau_MET_Stage2_Run2016D  =  (TH1D*)file_Tau_Run2016D->Get("demo/histoDir/dphi_tau_MET_Stage2");
   TH1D* dphi_tau_MET_Stage2_Run2016C  =  (TH1D*)file_Tau_Run2016C->Get("demo/histoDir/dphi_tau_MET_Stage2");
   TH1D* dphi_tau_MET_Stage2_Run2016B  =  (TH1D*)file_Tau_Run2016B->Get("demo/histoDir/dphi_tau_MET_Stage2");
   TH1D* dphi_tau_MET_Stage2_Run2016G  =  (TH1D*)file_Tau_Run2016G->Get("demo/histoDir/dphi_tau_MET_Stage2");
   TH1D* dphi_tau_MET_Stage2_Run2016H_v2  = (TH1D*)file_Tau_Run2016H_v2->Get("demo/histoDir/dphi_tau_MET_Stage2");
   TH1D* dphi_tau_MET_Stage2_Run2016H_v3  = (TH1D*)file_Tau_Run2016H_v3->Get("demo/histoDir/dphi_tau_MET_Stage2");
   
   /*
  std::cout << "Will Clone B" << std::endl;
  TH1D* dphi_tau_MET_Stage2_Run2016BCD = (TH1D*)dphi_tau_MET_Stage2_Run2016B->Clone();
 
  std::cout << "Will add C" << std::endl;
  dphi_tau_MET_Stage2_Run2016BCD->Add(dphi_tau_MET_Stage2_Run2016C);

  std::cout << "Will add D" << std::endl;
  dphi_tau_MET_Stage2_Run2016BCD->Add(dphi_tau_MET_Stage2_Run2016D);

  //  std::cout << "Will add E" << std::endl;
  // dphi_tau_MET_Stage2_Run2016BCDEF->Add(dphi_tau_MET_Stage2_Run2016E);

  // std::cout << "Will add F" << std::endl;
  //  dphi_tau_MET_Stage2_Run2016BCDEF->Add(dphi_tau_MET_Stage2_Run2016F);
  */

  TH1D* dphi_tau_MET_Stage2_Run2016all = (TH1D*)dphi_tau_MET_Stage2_Run2016B->Clone();
  dphi_tau_MET_Stage2_Run2016all->Add(dphi_tau_MET_Stage2_Run2016C);
  dphi_tau_MET_Stage2_Run2016all->Add(dphi_tau_MET_Stage2_Run2016D);
  dphi_tau_MET_Stage2_Run2016all->Add(dphi_tau_MET_Stage2_Run2016E);
  dphi_tau_MET_Stage2_Run2016all->Add(dphi_tau_MET_Stage2_Run2016F);
  dphi_tau_MET_Stage2_Run2016all->Add(dphi_tau_MET_Stage2_Run2016G);
  dphi_tau_MET_Stage2_Run2016all->Add(dphi_tau_MET_Stage2_Run2016H_v2);
  dphi_tau_MET_Stage2_Run2016all->Add(dphi_tau_MET_Stage2_Run2016H_v3);
                                                                                                                                    
  dphi_tau_MET_Stage2_Run2016all->SetMarkerStyle(20);
  dphi_tau_MET_Stage2_Run2016all->SetMarkerColor(kBlack);
  dphi_tau_MET_Stage2_Run2016all->SetLineColor(kBlack);
  dphi_tau_MET_Stage2_Run2016all->Rebin(25);
  
  std::cout << "will do signal " << std::endl;
  //--Signal--//
  TH1D* h1_evt_Wprime_M4000 = (TH1D*)file_Wprime_M4000->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M4000 = h1_evt_Wprime_M4000->GetEntries(); //Integral();                                                                          
  // std::cout << "evt_Wprime_M4000 = " << evt_Wprime_M4000 << std::endl;
  double wt_Wprime_M4000 = (xs_Wprime_M4000*lumi)/evt_Wprime_M4000 ;
  TH1D* dphi_tau_MET_Stage2_Wprime_M4000  = (TH1D*)file_Wprime_M4000->Get("demo/histoDir/dphi_tau_MET_Stage2");
  std::cout << "Sig Eff W' M4000 : " << ( dphi_tau_MET_Stage2_Wprime_M4000->GetEntries() / evt_Wprime_M4000 ) << std::endl;
  dphi_tau_MET_Stage2_Wprime_M4000->Scale(wt_Wprime_M4000);
  //  dphi_tau_MET_Stage2_Wprime_M4000->SetFillColorAlpha(kGreen-7,0.5);
  dphi_tau_MET_Stage2_Wprime_M4000->SetLineColor(kMagenta);
  dphi_tau_MET_Stage2_Wprime_M4000->SetLineWidth(4);
  dphi_tau_MET_Stage2_Wprime_M4000->SetLineStyle(5);
  dphi_tau_MET_Stage2_Wprime_M4000->Rebin(25)  ;
 
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
  TFile* outputFile = new TFile("Out_dphi_tau_MET_Stage2.root","RECREATE");
  outputFile->cd();

  //--//
  THStack *hs = new THStack("hs","");
  // hs->Add(dphi_tau_MET_Stage2_WJetsToLNu);
  hs->Add(total_diboson);
  hs->Add(total_DY);
  hs->Add(total_ST);
  hs->Add(total_TT);
  //  hs->Add(dphi_tau_MET_Stage2_DYJetsToLL_M50);
  hs->Add(total_QCD);
  //  hs->Add(total_ZJets);
  hs->Add(total_WJets);
  //dphi_tau_MET_Stage2_->SetTitle("");
    /*
  eff1->GetYaxis()->SetTitle("Events");
  //eff1->SetMarkerStyle(0);
  //eff1->SetMarkerColor(kBlack);
  eff1->SetLineColor(kBlack);
  eff1->SetLineWidth(2);
  */
  TCanvas* my_canvas = new TCanvas("canvas","canvas",800,600);
  my_canvas->cd();
  //  hs->Draw();
  gPad->SetLogy();
  hs->Draw("HIST");                                                                                                                                        
  hs->SetMaximum(100000);
  hs->SetMinimum(0.1);
  hs->GetXaxis()->SetRangeUser(0, 4);
  //  hs->GetXaxis()->SetLimits(40, 3200);
  hs->GetXaxis()->SetTitle("dPhi(#tau,MET)");
  hs->GetYaxis()->SetTitle("Events");

  TH1F* total =  (TH1F*)hs->GetStack()->Last()->Clone();
  // total->SetFillStyle(3004);                                                                                                                                      
  // total->SetFillColor(kGray+1); 
  //  total->SetMarkerColor(0);
  // total->Draw("SAME E2");
  //hs->GetStack()->Last()->Draw("same E");
  // hs->Draw("SAME HIST");

  //  dphi_tau_MET_Stage2_Run2016E->Draw("SAME E0");
  dphi_tau_MET_Stage2_Run2016all->Draw("SAME E0");
  TH1F* mydata =  (TH1F*)dphi_tau_MET_Stage2_Run2016all->Clone();

  //dphi_tau_MET_Stage2_Run2016C->Draw("SAME E0");
  //dphi_tau_MET_Stage2_Run2016CDE->Draw("SAME E0");
  //
  dphi_tau_MET_Stage2_Wprime_M4000->Draw("SAME HIST");
  //  hs->SetOption("HIST L");
  
  TLatex* CMS_text = new TLatex(0.20,0.90,"CMS");
  CMS_text->SetNDC();
  CMS_text->SetTextSize(0.05);
  CMS_text->SetTextAngle(0);
  //CMS_text->Draw("same");
  TLatex* CMS_text_2 = new TLatex(0.20,0.85,"Work in progress");
  CMS_text_2->SetNDC();
  CMS_text_2->SetTextFont(42);
  CMS_text_2->SetTextSize(0.05);
  CMS_text_2->SetTextAngle(0);
  CMS_text_2->Draw("same");    

  TLatex* lumiText = new TLatex(0.92,0.975,"35.9 fb^{-1} (13 TeV)");
  lumiText->SetNDC();
  lumiText->SetTextFont(42);
  lumiText->SetTextSize(0.04);
  lumiText->SetTextAlign(32);
  lumiText->Draw("same");     


  TLine *l1=new TLine(2.4,0,2.4,1000);
  l1->SetLineColor(12);
  l1->SetLineWidth(4);
  l1->SetLineStyle(2);
  l1->Draw("same");

  TLegend *leg_example = new TLegend(0.55,0.70,0.94,0.94);
  leg_example->SetFillColor(0);
  leg_example->SetNColumns(2);
  leg_example->SetTextFont(42);
  leg_example->SetBorderSize(0);
  leg_example->AddEntry(total_WJets, "Wjets","f");
  leg_example->AddEntry(total_DY, "DY","f");
  leg_example->AddEntry(total_TT, "TT","f");
  //leg_example->AddEntry(dphi_tau_MET_Stage2_WJetsToLNu, "Wjets","f");
  leg_example->AddEntry(total_ST, "Single Top", "f");
  leg_example->AddEntry(total_diboson, "Diboson", "f");
  leg_example->AddEntry(total_QCD, "QCD datadriven", "f");
  // leg_example->AddEntry(total_ZJets, "Z", "f");
  leg_example->AddEntry(dphi_tau_MET_Stage2_Wprime_M4000, "SSM W' 4 TeV", "l");
  leg_example->AddEntry(dphi_tau_MET_Stage2_Run2016all, "Data", "pl" );
  // leg_example->AddEntry(dphi_tau_MET_Stage2_Run2016E, "Data", "pl" );
  // leg_example->AddEntry(dphi_tau_MET_Stage2_Run2016D, "Data", "pl" );
  leg_example->Draw("same");
  
  my_canvas->Write();
  my_canvas->Print("dphi_tau_MET_Stage2_DD.pdf");


  /*

  TCanvas* my_canvas2 = new TCanvas("canvas2","canvas2");
  my_canvas2->cd();
  gPad->SetLogy();
  total->SetMaximum(1000);
  total->SetMarkerStyle(20);
  total->Draw("E");
  my_canvas2->Write();
  */
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
  hs->SetMaximum(100000);
  hs->SetMinimum(0.01);
  //  hs->GetXaxis()->SetLimits(40, 3200);
  hs->GetXaxis()->SetRangeUser(0, 4);
  hs->GetXaxis()->SetTitle("");
  // total->Draw("SAME E2");
  mydata->Draw("SAME E1");
  dphi_tau_MET_Stage2_Wprime_M4000->Draw("SAME HIST");
  //CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  lumiText->Draw("same");
  leg_example->Draw("same");


  /*  TLine *l1=new TLine(2.4,0,2.4,1000);
  l1->SetLineColor(12);
  l1->SetLineWidth(4);
  l1->SetLineStyle(2);*/
  l1->Draw("same");


  ratio_c->cd(2);

  gPad->SetPad(.005, .08, .995, .28); 
  gStyle->SetOptStat(false);
  ratio_c->Update();
  TPad* pad2 = (TPad*)ratio_c->GetPad(2);
  pad2->SetTopMargin(0.04); 
  pad2->SetBottomMargin(0.30); 
  pad2->SetGridx();
  pad2->SetGridy();

  std::cout << "data bins = " << mydata->GetNbinsX() << " width=" << mydata->GetBinWidth(2);
  std::cout << " MC bins = " << total->GetNbinsX() << " width=" << total->GetBinWidth(2) << std::endl;

  int nbin=mydata->GetNbinsX() ;
  float width=mydata->GetBinWidth(2);
  TH1F *data_by_MC = new TH1F("h1", "ratio", nbin, 0, 4);
  std::cout << "before D/MC bins=" << data_by_MC->GetNbinsX() << " width=" << data_by_MC->GetBinWidth(2) << std::endl;

  for (int i=0; i<nbin; i++) {
    float data = mydata->GetBinContent(i);
    float MC = total->GetBinContent(i);
    float ratio=0;
    if (MC>0) ratio=data/MC ;
    data_by_MC->SetBinContent(i,ratio);
    if (data>0) {
      float stat_err = sqrt(data)/data ;  
      data_by_MC->SetBinError(i,stat_err);
    }

    // data_by_MC->SetBinWidth(i,width);  
  }

  //  TH1F* data_by_MC = (TH1F*)mydata->Clone();
  // data_by_MC->Divide(total);
  data_by_MC->SetMarkerStyle(20);
  data_by_MC->Draw("E");
  data_by_MC->GetXaxis()->SetTitle("dPhi(#tau,MET)");
  data_by_MC->GetYaxis()->SetTitle("#frac{DATA}{MC}");
  data_by_MC->GetYaxis()->SetLabelSize(0.12);
  data_by_MC->GetXaxis()->SetLabelSize(0.12);
  data_by_MC->GetYaxis()->SetTitleSize(0.18);
  data_by_MC->GetXaxis()->SetTitleSize(0.18);
  data_by_MC->GetYaxis()->SetTitleOffset(0.20);
  data_by_MC->GetXaxis()->SetTitleOffset(0.75);
  data_by_MC->SetTitle("");
  data_by_MC->GetXaxis()->SetRangeUser(0, 4);
  data_by_MC->SetMaximum(4);
  data_by_MC->SetMinimum(0);
  data_by_MC->GetYaxis()->SetNdivisions(4);



  TLine *l=new TLine(0,1,4,1);
  l->SetLineColor(kRed);
  l->Draw("same");

  std::cout << "D/MC bins=" << data_by_MC->GetNbinsX() << " width=" << data_by_MC->GetBinWidth(2) << std::endl;
  ratio_c->Write();
  ratio_c->Print("dphi_tau_MET_Stage2_ratio_DD.pdf");

 
  return 0;

}
