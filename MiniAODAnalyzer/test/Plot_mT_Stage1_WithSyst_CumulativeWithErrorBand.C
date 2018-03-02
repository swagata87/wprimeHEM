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

int Plot_mT_Stage1_WithSyst_CumulativeWithErrorBand() {

  double totalMC =0.0;
  double totalQCDMC =0.0;
  double lumi= 35.865; //*0.9 ;//*1.3; //36.813;  //13.496 ;  // B->5.882  // C->2.646   D->4.353 ;  // E->4.049 ; F->3.16 ;  G->7.554;  H->5.942  //--inv fb--//
  // lumi error 2.6%  (OLD value 6.2 %)
  double wt_lumi_up = 1.025; 
  double wt_lumi_down = 0.975;

  double wt_pdf_up = 1.10; 
  double wt_pdf_down = 0.90;
  //

  unsigned long long evt_DYJetsToLL_M50=1;
  TFile *file_DYJetsToLL_M50  = new TFile("../python/crab_projects_Feb11/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/IncludeExt_hist.root");             
  double xs_DYJetsToLL_M50=4895000;  //--fb--//                                                                                                                   
  double kfact_DYJetsToLL_M50=1.1778;  //--fb--//                                                                                                                   
  //  double xs_DYJetsToLL_M50=5765400;  //--fb--//                                                                                                                    

  unsigned long long evt_DYJetsToLL_M5to50=1;
  TFile *file_DYJetsToLL_M5to50  = new TFile("../python/crab_projects_Feb11/crab_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");    
  double xs_DYJetsToLL_M5to50=7160000;  //--fb--//                                                                                                                    
  double kfact_DYJetsToLL_M5to50=1.0;  //--fb--//                                                                                                                    
  // double xs_DYJetsToLL_M5to50=18610000;  //--fb--//                                                                                                                    

  unsigned long long evt_TT=1;
  TFile *file_TT              = new TFile("../python/crab_projects_Feb11/crab_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/results/hist.root");
  double xs_TT=730000; //--fb--//
  double kfact_TT= 1.139;

  /*
  TFile *file_TT_Mtt_700to1000      = new TFile("../python/crab_projects_Feb11/crab_TT_Mtt-700to1000_TuneCUETP8M1_13TeV-powheg-pythia8/results/hist.root");
  double xs_TT_Mtt_700to1000=730000; //--fb--//
  double kfact_TT_Mtt_700to1000= 0.0921;

  TFile *file_TT_Mtt_1000toInf              = new TFile("../python/crab_projects_Feb11/crab_TT_Mtt-1000toInf_TuneCUETP8M1_13TeV-powheg-pythia8/results/hist.root");
  double xs_TT_Mtt_1000toInf=730000; //--fb--//
  double kfact_TT_Mtt_1000toInf= 0.02474;
  */

  TFile *file_WJetsToLNu      = new TFile("../python/crab_projects_Feb11/crab_WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/IncludeExt_hist.root");
  double xs_WJetsToLNu= 50690000; //--fb--//
  //
  TFile *file_WToTauNu_M100  = new TFile("../python/crab_projects_Feb11/crab_WToTauNu_M-100_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_WToTauNu_M100 = 165000; //--fb--//
  double kfact_WToTauNu_M100 = 1.0 ; 
  //
  TFile *file_WToTauNu_M200  = new TFile("../python/crab_projects_Feb11/crab_WToTauNu_M-200_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_WToTauNu_M200 = 6370; //--fb--//
  double kfact_WToTauNu_M200 = 1.0 ; 
  //
  TFile *file_WToTauNu_M500  = new TFile("../python/crab_projects_Feb11/crab_WToTauNu_M-500_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_WToTauNu_M500 = 224.0; //--fb--//
  double kfact_WToTauNu_M500 = 1.0 ; 
  //
  TFile *file_WToTauNu_M1000  = new TFile("../python/crab_projects_Feb11/crab_WToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_WToTauNu_M1000 = 13.7; //--fb--//
  double kfact_WToTauNu_M1000 = 1.0 ; 
  //
  TFile *file_WToTauNu_M2000  = new TFile("../python/crab_projects_Feb11/crab_WToTauNu_M-2000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_WToTauNu_M2000 = 0.437; //--fb--//
  double kfact_WToTauNu_M2000 = 1.0 ; 
  //
  TFile *file_WToTauNu_M3000  = new TFile("../python/crab_projects_Feb11/crab_WToTauNu_M-3000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_WToTauNu_M3000 = 0.0342; //--fb--//
  double kfact_WToTauNu_M3000 = 1.0 ; 
  //
  TFile *file_WToTauNu_M4000  = new TFile("../python/crab_projects_Feb11/crab_WToTauNu_M-4000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_WToTauNu_M4000 = 0.00292; //--fb--//
  double kfact_WToTauNu_M4000 = 1.0 ; 
  //
  TFile *file_WToTauNu_M5000  = new TFile("../python/crab_projects_Feb11/crab_WToTauNu_M-5000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_WToTauNu_M5000 = 0.000233; //--fb--//
  double kfact_WToTauNu_M5000 = 1.0 ; 
  //
  TFile *file_WToTauNu_M6000  = new TFile("../python/crab_projects_Feb11/crab_WToTauNu_M-6000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_WToTauNu_M6000 = 0.000015; //--fb--//
  double kfact_WToTauNu_M6000 = 1.0 ; 
  //
  TFile *file_WJetsToLNu_HT100To200  = new TFile("../python/crab_projects_Feb11/crab_WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/IncludeExt_hist.root");
  double xs_WJetsToLNu_HT100To200 = 1345000 ; //--fb--//
  double kfact_WJetsToLNu_HT100To200 = 1.0 ; 

  TFile *file_WJetsToLNu_HT200To400  = new TFile("../python/crab_projects_Feb11/crab_WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/IncludeExt_hist.root");
  double xs_WJetsToLNu_HT200To400 = 359700 ; //--fb--//
  double kfact_WJetsToLNu_HT200To400 = 1.0 ;

  TFile *file_WJetsToLNu_HT400To600  = new TFile("../python/crab_projects_Feb11/crab_WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/IncludeExt_hist.root");
  double xs_WJetsToLNu_HT400To600 = 48910 ; //--fb--//
  double kfact_WJetsToLNu_HT400To600 = 1.0 ;

  TFile *file_WJetsToLNu_HT600To800  = new TFile("../python/crab_projects_Feb11/crab_WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/IncludeExt_hist.root");
  double xs_WJetsToLNu_HT600To800 = 12050 ; //--fb--//
  double kfact_WJetsToLNu_HT600To800 = 1.0 ;

  TFile *file_WJetsToLNu_HT800To1200  = new TFile("../python/crab_projects_Feb11/crab_WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/IncludeExt_hist.root");
  double xs_WJetsToLNu_HT800To1200 = 5501 ; //--fb--//
  double kfact_WJetsToLNu_HT800To1200 = 1.0 ;

  TFile *file_WJetsToLNu_HT1200To2500  = new TFile("../python/crab_projects_Feb11/crab_WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/IncludeExt_hist.root");
  double xs_WJetsToLNu_HT1200To2500 = 1329 ; //--fb--//
  double kfact_WJetsToLNu_HT1200To2500 = 1.0 ;

  TFile *file_WJetsToLNu_HT2500ToInf  = new TFile("../python/crab_projects_Feb11/crab_WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/IncludeExt_hist.root");
  double xs_WJetsToLNu_HT2500ToInf = 32.16  ; //--fb--//
  double kfact_WJetsToLNu_HT2500ToInf = 1.0 ;

  TFile *file_ST_tchannel_antitop=new TFile("../python/crab_projects_Feb11/crab_ST_t-channel_antitop_4f_inclusiveDecays_TuneCUETP8M2T4_13TeV-powhegV2-madspin/results/hist.root");
  double xs_ST_tchannel_antitop = 80950; //--fb--//
  double kfact_ST_tchannel_antitop = 1.0; // 0.326;
  //
  TFile *file_ST_tchannel_top=new TFile("../python/crab_projects_Feb11/crab_ST_t-channel_top_4f_inclusiveDecays_TuneCUETP8M2T4_13TeV-powhegV2-madspin/results/hist.root");
  double xs_ST_tchannel_top = 136020; //  103200; //--fb--//
  double kfact_ST_tchannel_top =1.0; // 0.43;
  //
  TFile *file_ST_tW_antitop=new TFile("../python/crab_projects_Feb11/crab_ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4/results/hist.root");
  double xs_ST_tW_antitop = 38090; //--fb--//
  double kfact_ST_tW_antitop = 1.88;
  //
  TFile *file_ST_tW_top=new TFile("../python/crab_projects_Feb11/crab_ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4/results/hist.root");
  double xs_ST_tW_top = 38090; //--fb--//
  double kfact_ST_tW_top = 1.88;
  //
  TFile *file_WW=new TFile("../python/crab_projects_Feb11/crab_WW_TuneCUETP8M1_13TeV-pythia8/results/IncludeExt_hist.root");
  double xs_WW = 63210; //--fb--//
  //
  TFile *file_WZ=new TFile("../python/crab_projects_Feb11/crab_WZ_TuneCUETP8M1_13TeV-pythia8/results/hist.root");
  double xs_WZ = 22820; //--fb--//
  double kfact_WZ = 2.06; // 47.13/22.82
  //
  TFile *file_ZZ=new TFile("../python/crab_projects_Feb11/crab_ZZ_TuneCUETP8M1_13TeV-pythia8/results/IncludeExt_hist.root");
  double xs_ZZ = 10320; //--fb--//
  double kfact_ZZ = 1.60 ; //16523/10320
  //
  TFile *file_QCD_HT200to300=new TFile("../python/crab_projects_Feb11/crab_QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/IncludeExt_hist.root");
  double xs_QCD_HT200to300 = 1717000000; //--fb--//
  //
  TFile *file_QCD_HT300to500=new TFile("../python/crab_projects_Feb11/crab_QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/IncludeExt_hist.root");
  double xs_QCD_HT300to500 = 351300000; //--fb--//
  //
  TFile *file_QCD_HT500to700=new TFile("../python/crab_projects_Feb11/crab_QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/IncludeExt_hist.root");
  double xs_QCD_HT500to700 = 31630000 ; //--fb--//
  //
  TFile *file_QCD_HT700to1000=new TFile("../python/crab_projects_Feb11/crab_QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/IncludeExt_hist.root");
  double xs_QCD_HT700to1000 = 6802000 ; //--fb--//
  //
  TFile *file_QCD_HT1000to1500=new TFile("../python/crab_projects_Feb11/crab_QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/IncludeExt_hist.root");
  double xs_QCD_HT1000to1500 = 1206000 ; //--fb--//
  //
  TFile *file_QCD_HT1500to2000=new TFile("../python/crab_projects_Feb11/crab_QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/IncludeExt_hist.root");
  double xs_QCD_HT1500to2000 = 120400 ; //--fb--//
  //
  TFile *file_QCD_HT2000toInf=new TFile("../python/crab_projects_Feb11/crab_QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/IncludeExt_hist.root");
  double xs_QCD_HT2000toInf = 25250 ; //--fb--//
  //
  TFile *file_ZJetsToNuNu_HT100To200 =new TFile("../python/crab_projects_Feb11/crab_ZJetsToNuNu_HT-100To200_13TeV-madgraph/results/IncludeExt_hist.root");
  double xs_ZJetsToNuNu_HT100To200 =  280350; //--fb--//
  double kfact_ZJetsToNuNu_HT100To200 =  1.23 ;
  //
  TFile *file_ZJetsToNuNu_HT200To400 =new TFile("../python/crab_projects_Feb11/crab_ZJetsToNuNu_HT-200To400_13TeV-madgraph/results/IncludeExt_hist.root");
  double xs_ZJetsToNuNu_HT200To400 = 77670 ; //--fb--//
  double kfact_ZJetsToNuNu_HT200To400 = 1.23 ;
  //
  TFile *file_ZJetsToNuNu_HT400To600 =new TFile("../python/crab_projects_Feb11/crab_ZJetsToNuNu_HT-400To600_13TeV-madgraph/results/IncludeExt_hist.root");
  double xs_ZJetsToNuNu_HT400To600 = 10730 ; //--fb--//
  double kfact_ZJetsToNuNu_HT400To600 =  1.23 ;
  //
  TFile *file_ZJetsToNuNu_HT600To800 =new TFile("../python/crab_projects_Feb11/crab_ZJetsToNuNu_HT-600To800_13TeV-madgraph/results/hist.root");
  double xs_ZJetsToNuNu_HT600To800 = 853 ; //--fb--//
 double kfact_ZJetsToNuNu_HT600To800 =  1.23 ;
  //
  TFile *file_ZJetsToNuNu_HT800To1200 =new TFile("../python/crab_projects_Feb11/crab_ZJetsToNuNu_HT-800To1200_13TeV-madgraph/results/hist.root");
  double xs_ZJetsToNuNu_HT800To1200 = 394.2 ; //--fb--//
  double kfact_ZJetsToNuNu_HT800To1200 =  1.23 ;
  //
  TFile *file_ZJetsToNuNu_HT1200To2500 =new TFile("../python/crab_projects_Feb11/crab_ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/results/IncludeExt_hist.root");
  double xs_ZJetsToNuNu_HT1200To2500 = 97.4 ; //--fb--//
  double kfact_ZJetsToNuNu_HT1200To2500 =  1.23 ;
  //
  TFile *file_ZJetsToNuNu_HT2500ToInf =new TFile("../python/crab_projects_Feb11/crab_ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph/results/hist.root");
  double xs_ZJetsToNuNu_HT2500ToInf = 2.308 ; //--fb--//
  double kfact_ZJetsToNuNu_HT2500ToInf =  1.23 ;

  /// DATA ///

  TFile *file_Tau_Run2016B = new TFile("../python/crab_projects_Feb11/crab_Tau_Run2016B/results/hist.root");
  TFile *file_Tau_Run2016C = new TFile("../python/crab_projects_Feb11/crab_Tau_Run2016C/results/hist.root");
  TFile *file_Tau_Run2016D = new TFile("../python/crab_projects_Feb11/crab_Tau_Run2016D/results/hist.root");
  TFile *file_Tau_Run2016E = new TFile("../python/crab_projects_Feb11/crab_Tau_Run2016E/results/hist.root");
  TFile *file_Tau_Run2016F = new TFile("../python/crab_projects_Feb11/crab_Tau_Run2016F/results/hist.root");
  TFile *file_Tau_Run2016G = new TFile("../python/crab_projects_Feb11/crab_Tau_Run2016G/results/hist.root");
  TFile *file_Tau_Run2016H_v2 = new TFile("../python/crab_projects_Feb11/crab_Tau_Run2016H_1/results/hist.root");
  TFile *file_Tau_Run2016H_v3 = new TFile("../python/crab_projects_Feb11/crab_Tau_Run2016H_2/results/hist.root");


  /// Signal ///
  //  TFile *file_Wprime_M1000 = new TFile("../python/crab_projects_Feb11/crab_WprimeToTauNu_M-4000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  // double xs_Wprime_M1000= 3060; // --fb-- //

  TFile *file_Wprime_M4000 = new TFile("../python/crab_projects_Feb11/crab_WprimeToTauNu_M-4000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_Wprime_M4000= 2.04; // --fb-- //

  TFile *file_Wprime_M600 = new TFile("../python/crab_projects_Jan22/crab_WprimeToTauNu_M_600_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  double xs_Wprime_M600= 20800; // --fb-- //

  TFile *file_Wprime_M5000 = new TFile("../python/crab_projects_Jan22//crab_WprimeToTauNu_M-5000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_Wprime_M5000= 0.408; // --fb-- //


  //  TFile *file_WprimeNUGIM_M3000_1p5 = new TFile("../python/crab_projects_Feb11/crab_WprimeToTauNUGIM_M3000_gL1p5-madgraph/results/hist.root");
  //double xs_WprimeNUGIM_M3000_1p5= 2.04; // --fb-- //

  //--//
  TH1D* h1_evt_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/eventCount");
  evt_DYJetsToLL_M50 = h1_evt_DYJetsToLL_M50->GetEntries(); // Integral();
  double wt_DYJetsToLL_M50 = (xs_DYJetsToLL_M50*lumi)/evt_DYJetsToLL_M50 ;
  TH1D* mT_Stage1_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50->Scale(kfact_DYJetsToLL_M50);

  std::cout << "DYJetsToLL_M50 weighted nevt=" << mT_Stage1_DYJetsToLL_M50->Integral() << std::endl;
  totalMC += mT_Stage1_DYJetsToLL_M50->Integral();
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_JetEnUp = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_DYJetsToLL_M50_JetEnUp->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_JetEnUp->Scale(kfact_DYJetsToLL_M50);
  //                                                                                                                                                                             
  TH1D* mT_Stage1_DYJetsToLL_M50_JetEnDown = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_DYJetsToLL_M50_JetEnDown->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_JetEnDown->Scale(kfact_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_JetResUp = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_DYJetsToLL_M50_JetResUp->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_JetResUp->Scale(kfact_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_JetResDown = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_DYJetsToLL_M50_JetResDown->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_JetResDown->Scale(kfact_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_MuonEnUp = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_DYJetsToLL_M50_MuonEnUp->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_MuonEnUp->Scale(kfact_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_MuonEnDown = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_DYJetsToLL_M50_MuonEnDown->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_MuonEnDown->Scale(kfact_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_ElectronEnUp = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_DYJetsToLL_M50_ElectronEnUp->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_ElectronEnUp->Scale(kfact_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_ElectronEnDown = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_DYJetsToLL_M50_ElectronEnDown->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_ElectronEnDown->Scale(kfact_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_TauEnUp = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_DYJetsToLL_M50_TauEnUp->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_TauEnUp->Scale(kfact_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_TauEnDown = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_DYJetsToLL_M50_TauEnDown->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_TauEnDown->Scale(kfact_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_PhotonEnUp = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_DYJetsToLL_M50_PhotonEnUp->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_PhotonEnUp->Scale(kfact_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_PhotonEnDown = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_DYJetsToLL_M50_PhotonEnDown->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_PhotonEnDown->Scale(kfact_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_UnclusteredEnUp = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_DYJetsToLL_M50_UnclusteredEnUp->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_UnclusteredEnUp->Scale(kfact_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_UnclusteredEnDown = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_DYJetsToLL_M50_UnclusteredEnDown->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_UnclusteredEnDown->Scale(kfact_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_TauScaleUp = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_DYJetsToLL_M50_TauScaleUp->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_TauScaleUp->Scale(kfact_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_TauScaleDown = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_DYJetsToLL_M50_TauScaleDown->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_TauScaleDown->Scale(kfact_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_pileupUncertUp = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_DYJetsToLL_M50_pileupUncertUp->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_pileupUncertUp->Scale(kfact_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_pileupUncertDown = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_DYJetsToLL_M50_pileupUncertDown->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_pileupUncertDown->Scale(kfact_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_kFactorUp = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_DYJetsToLL_M50_kFactorUp->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_kFactorUp->Scale(kfact_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_kFactorDown = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_DYJetsToLL_M50_kFactorDown->Scale(wt_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_TauIDSFUp = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_DYJetsToLL_M50_TauIDSFUp->Scale(wt_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_TauIDSFDown = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_DYJetsToLL_M50_TauIDSFDown->Scale(wt_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_TauIDSFflatUp = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_DYJetsToLL_M50_TauIDSFflatUp->Scale(wt_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_TauIDSFflatDown = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_DYJetsToLL_M50_TauIDSFflatDown->Scale(wt_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_TauELESFUp = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_DYJetsToLL_M50_TauELESFUp->Scale(wt_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_TauELESFDown = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_DYJetsToLL_M50_TauELESFDown->Scale(wt_DYJetsToLL_M50);

  TH1D* mT_Stage1_DYJetsToLL_M50_trigSFUp = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_DYJetsToLL_M50_trigSFUp->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_trigSFUp->Scale(kfact_DYJetsToLL_M50);
  //                                                                                                                                                                        
  TH1D* mT_Stage1_DYJetsToLL_M50_trigSFDown = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_DYJetsToLL_M50_trigSFDown->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50_trigSFDown->Scale(kfact_DYJetsToLL_M50);

  //
  /*
  TH1D* mT_Stage1_DYJetsToLL_M50_pdfUncertUp = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_DYJetsToLL_M50_pdfUncertUp->Scale(wt_DYJetsToLL_M50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M50_pdfUncertDown = (TH1D*)file_DYJetsToLL_M50->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_DYJetsToLL_M50_pdfUncertDown->Scale(wt_DYJetsToLL_M50); */
  //
  TH1D* h1_evt_DYJetsToLL_M5to50 = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/eventCount");
  evt_DYJetsToLL_M5to50 = h1_evt_DYJetsToLL_M5to50->GetEntries(); // Integral();
  double wt_DYJetsToLL_M5to50 = (xs_DYJetsToLL_M5to50*lumi)/evt_DYJetsToLL_M5to50 ;
  TH1D* mT_Stage1_DYJetsToLL_M5to50 = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_DYJetsToLL_M5to50->Scale(wt_DYJetsToLL_M5to50);
  mT_Stage1_DYJetsToLL_M5to50->Scale(kfact_DYJetsToLL_M5to50);
  std::cout << "DYJetsToLL_M5to50 weighted nevt=" << mT_Stage1_DYJetsToLL_M5to50->Integral() << std::endl;
  totalMC += mT_Stage1_DYJetsToLL_M5to50->Integral() ;
  //
  TH1D* mT_Stage1_DYJetsToLL_M5to50_JetEnUp = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_DYJetsToLL_M5to50_JetEnUp->Scale(wt_DYJetsToLL_M5to50);
  //                                                                                                                                                                            
  TH1D* mT_Stage1_DYJetsToLL_M5to50_JetEnDown = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_DYJetsToLL_M5to50_JetEnDown->Scale(wt_DYJetsToLL_M5to50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M5to50_JetResUp = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_DYJetsToLL_M5to50_JetResUp->Scale(wt_DYJetsToLL_M5to50);
  //                                                                                                                                                                            
  TH1D* mT_Stage1_DYJetsToLL_M5to50_JetResDown = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_DYJetsToLL_M5to50_JetResDown->Scale(wt_DYJetsToLL_M5to50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M5to50_MuonEnUp = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_DYJetsToLL_M5to50_MuonEnUp->Scale(wt_DYJetsToLL_M5to50);
  //                                                                                                                                                                            
  TH1D* mT_Stage1_DYJetsToLL_M5to50_MuonEnDown = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_DYJetsToLL_M5to50_MuonEnDown->Scale(wt_DYJetsToLL_M5to50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M5to50_ElectronEnUp = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_DYJetsToLL_M5to50_ElectronEnUp->Scale(wt_DYJetsToLL_M5to50);
  //                                                                                                                                                                            
  TH1D* mT_Stage1_DYJetsToLL_M5to50_ElectronEnDown = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_DYJetsToLL_M5to50_ElectronEnDown->Scale(wt_DYJetsToLL_M5to50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M5to50_TauEnUp = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_DYJetsToLL_M5to50_TauEnUp->Scale(wt_DYJetsToLL_M5to50);
  //                                                                                                                                                                            
  TH1D* mT_Stage1_DYJetsToLL_M5to50_TauEnDown = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_DYJetsToLL_M5to50_TauEnDown->Scale(wt_DYJetsToLL_M5to50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M5to50_PhotonEnUp = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_DYJetsToLL_M5to50_PhotonEnUp->Scale(wt_DYJetsToLL_M5to50);
  //                                                                                                                                                                            
  TH1D* mT_Stage1_DYJetsToLL_M5to50_PhotonEnDown = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_DYJetsToLL_M5to50_PhotonEnDown->Scale(wt_DYJetsToLL_M5to50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M5to50_UnclusteredEnUp = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_DYJetsToLL_M5to50_UnclusteredEnUp->Scale(wt_DYJetsToLL_M5to50);
  //                                                                                                                                                                            
  TH1D* mT_Stage1_DYJetsToLL_M5to50_UnclusteredEnDown = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_DYJetsToLL_M5to50_UnclusteredEnDown->Scale(wt_DYJetsToLL_M5to50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M5to50_TauScaleUp = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_DYJetsToLL_M5to50_TauScaleUp->Scale(wt_DYJetsToLL_M5to50);
  //                                                                                                                                                                            
  TH1D* mT_Stage1_DYJetsToLL_M5to50_TauScaleDown = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_DYJetsToLL_M5to50_TauScaleDown->Scale(wt_DYJetsToLL_M5to50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M5to50_pileupUncertUp = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_DYJetsToLL_M5to50_pileupUncertUp->Scale(wt_DYJetsToLL_M5to50);
  //                                                                                                                                                                            
  TH1D* mT_Stage1_DYJetsToLL_M5to50_pileupUncertDown = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_DYJetsToLL_M5to50_pileupUncertDown->Scale(wt_DYJetsToLL_M5to50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M5to50_kFactorUp = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_DYJetsToLL_M5to50_kFactorUp->Scale(wt_DYJetsToLL_M5to50);
  //                                                                                                                                                                            
  TH1D* mT_Stage1_DYJetsToLL_M5to50_kFactorDown = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_DYJetsToLL_M5to50_kFactorDown->Scale(wt_DYJetsToLL_M5to50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M5to50_TauIDSFUp = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_DYJetsToLL_M5to50_TauIDSFUp->Scale(wt_DYJetsToLL_M5to50);
  //                                                                                                                                                                            
  TH1D* mT_Stage1_DYJetsToLL_M5to50_TauIDSFDown = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_DYJetsToLL_M5to50_TauIDSFDown->Scale(wt_DYJetsToLL_M5to50);

  TH1D* mT_Stage1_DYJetsToLL_M5to50_TauIDSFflatUp = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_DYJetsToLL_M5to50_TauIDSFflatUp->Scale(wt_DYJetsToLL_M5to50);
  //                                                                                                                                                                            
  TH1D* mT_Stage1_DYJetsToLL_M5to50_TauIDSFflatDown = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_DYJetsToLL_M5to50_TauIDSFflatDown->Scale(wt_DYJetsToLL_M5to50);
  //

  TH1D* mT_Stage1_DYJetsToLL_M5to50_TauELESFUp = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_DYJetsToLL_M5to50_TauELESFUp->Scale(wt_DYJetsToLL_M5to50);
  //                                                                                                                                                                            
  TH1D* mT_Stage1_DYJetsToLL_M5to50_TauELESFDown = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_DYJetsToLL_M5to50_TauELESFDown->Scale(wt_DYJetsToLL_M5to50);
  //
  TH1D* mT_Stage1_DYJetsToLL_M5to50_trigSFUp = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_DYJetsToLL_M5to50_trigSFUp->Scale(wt_DYJetsToLL_M5to50);
  mT_Stage1_DYJetsToLL_M5to50_trigSFUp->Scale(kfact_DYJetsToLL_M5to50);
  //                                                                                                                                                                      
  TH1D* mT_Stage1_DYJetsToLL_M5to50_trigSFDown = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_DYJetsToLL_M5to50_trigSFDown->Scale(wt_DYJetsToLL_M5to50);
  mT_Stage1_DYJetsToLL_M5to50_trigSFDown->Scale(kfact_DYJetsToLL_M5to50);
  //
  //
  /*
  TH1D* mT_Stage1_DYJetsToLL_M5to50_pdfUncertUp = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_DYJetsToLL_M5to50_pdfUncertUp->Scale(wt_DYJetsToLL_M5to50);
  //                                                                                                                                                                            
  TH1D* mT_Stage1_DYJetsToLL_M5to50_pdfUncertDown = (TH1D*)file_DYJetsToLL_M5to50->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_DYJetsToLL_M5to50_pdfUncertDown->Scale(wt_DYJetsToLL_M5to50);
  // */
  
  TH1D* total_DY = (TH1D*)mT_Stage1_DYJetsToLL_M50->Clone(); 
  total_DY->Add(mT_Stage1_DYJetsToLL_M5to50);
  total_DY->SetFillColorAlpha(kRed,0.5);
  total_DY->SetLineColor(kBlack);
  total_DY->Rebin(80);
  //

  TH1D* h1_evt_TT = (TH1D*)file_TT->Get("demo/histoDir/eventCount");
  evt_TT = h1_evt_TT->GetEntries(); // Integral();
  double wt_TT = (xs_TT*lumi)/evt_TT ;
  TH1D* mT_Stage1_TT  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_TT->Scale(wt_TT);
  mT_Stage1_TT->Scale(kfact_TT);
  std::cout << "TTbar weighted nevt=" << mT_Stage1_TT->Integral() << std::endl;
  totalMC += mT_Stage1_TT->Integral();
  //
  TH1D* mT_Stage1_TT_JetEnUp  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_TT_JetEnUp->Scale(wt_TT);
  mT_Stage1_TT_JetEnUp->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_JetEnDown  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_TT_JetEnDown->Scale(wt_TT);
  mT_Stage1_TT_JetEnDown->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_JetResUp  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_TT_JetResUp->Scale(wt_TT);
  mT_Stage1_TT_JetResUp->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_JetResDown  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_TT_JetResDown->Scale(wt_TT);
  mT_Stage1_TT_JetResDown->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_MuonEnUp  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_TT_MuonEnUp->Scale(wt_TT);
  mT_Stage1_TT_MuonEnUp->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_MuonEnDown  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_TT_MuonEnDown->Scale(wt_TT);
  mT_Stage1_TT_MuonEnDown->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_ElectronEnUp  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_TT_ElectronEnUp->Scale(wt_TT);
  mT_Stage1_TT_ElectronEnUp->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_ElectronEnDown  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_TT_ElectronEnDown->Scale(wt_TT);
  mT_Stage1_TT_ElectronEnDown->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_TauEnUp  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_TT_TauEnUp->Scale(wt_TT);
  mT_Stage1_TT_TauEnUp->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_TauEnDown  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_TT_TauEnDown->Scale(wt_TT);
  mT_Stage1_TT_TauEnDown->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_PhotonEnUp  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_TT_PhotonEnUp->Scale(wt_TT);
  mT_Stage1_TT_PhotonEnUp->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_PhotonEnDown  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_TT_PhotonEnDown->Scale(wt_TT);
  mT_Stage1_TT_PhotonEnDown->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_UnclusteredEnUp  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_TT_UnclusteredEnUp->Scale(wt_TT);
  mT_Stage1_TT_UnclusteredEnUp->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_UnclusteredEnDown  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_TT_UnclusteredEnDown->Scale(wt_TT);
  mT_Stage1_TT_UnclusteredEnDown->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_TauScaleUp  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_TT_TauScaleUp->Scale(wt_TT);
  mT_Stage1_TT_TauScaleUp->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_TauScaleDown  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_TT_TauScaleDown->Scale(wt_TT);
  mT_Stage1_TT_TauScaleDown->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_pileupUncertUp  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_TT_pileupUncertUp->Scale(wt_TT);
  mT_Stage1_TT_pileupUncertUp->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_pileupUncertDown  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_TT_pileupUncertDown->Scale(wt_TT);
  mT_Stage1_TT_pileupUncertDown->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_kFactorUp  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_TT_kFactorUp->Scale(wt_TT);
  mT_Stage1_TT_kFactorUp->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_kFactorDown  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_TT_kFactorDown->Scale(wt_TT);
  mT_Stage1_TT_kFactorDown->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_TauIDSFUp  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_TT_TauIDSFUp->Scale(wt_TT);
  mT_Stage1_TT_TauIDSFUp->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_TauIDSFDown  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_TT_TauIDSFDown->Scale(wt_TT);
  mT_Stage1_TT_TauIDSFDown->Scale(kfact_TT);
  // 

  TH1D* mT_Stage1_TT_TauIDSFflatUp  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_TT_TauIDSFflatUp->Scale(wt_TT);
  mT_Stage1_TT_TauIDSFflatUp->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_TauIDSFflatDown  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_TT_TauIDSFflatDown->Scale(wt_TT);
  mT_Stage1_TT_TauIDSFflatDown->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_TauELESFUp  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_TT_TauELESFUp->Scale(wt_TT);
  mT_Stage1_TT_TauELESFUp->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_TauELESFDown  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_TT_TauELESFDown->Scale(wt_TT);
  mT_Stage1_TT_TauELESFDown->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_trigSFUp = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_TT_trigSFUp->Scale(wt_TT);
  mT_Stage1_TT_trigSFUp->Scale(kfact_TT);
  //                                                                                                                                                                      
  TH1D* mT_Stage1_TT_trigSFDown = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_TT_trigSFDown->Scale(wt_TT);
  mT_Stage1_TT_trigSFDown->Scale(kfact_TT);
  //
  //

/*
  TH1D* mT_Stage1_TT_pdfUncertUp  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_TT_pdfUncertUp->Scale(wt_TT);
  mT_Stage1_TT_pdfUncertUp->Scale(kfact_TT);
  //
  TH1D* mT_Stage1_TT_pdfUncertDown  = (TH1D*)file_TT->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_TT_pdfUncertDown->Scale(wt_TT);
  mT_Stage1_TT_pdfUncertDown->Scale(kfact_TT);
  // */

  TH1D* total_TT = (TH1D*)mT_Stage1_TT->Clone(); 
  //  total_TT->Add(mT_Stage1_TT_Mtt_700to1000);
  // total_TT->Add(mT_Stage1_TT_Mtt_1000toInf);
  total_TT->SetFillColor(kBlue-7);
  total_TT->SetLineColor(kBlack);
  total_TT->Rebin(80);

  //file_ST_tchannel_antitop
  TH1D* h1_evt_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/eventCount");
  unsigned long long evt_ST_tchannel_antitop = h1_evt_ST_tchannel_antitop->GetEntries(); //Integral();
  double wt_ST_tchannel_antitop = (xs_ST_tchannel_antitop*lumi)/evt_ST_tchannel_antitop ;
  TH1D* mT_Stage1_ST_tchannel_antitop  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop->Scale(kfact_ST_tchannel_antitop);
  std::cout << "ST_tchannel_antitop weighted nevt=" << mT_Stage1_ST_tchannel_antitop->Integral() << std::endl;
  totalMC += mT_Stage1_ST_tchannel_antitop->Integral();
  //
  TH1D* mT_Stage1_ST_tchannel_antitop_JetEnUp  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_ST_tchannel_antitop_JetEnUp->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_JetEnUp->Scale(kfact_ST_tchannel_antitop);

  TH1D* mT_Stage1_ST_tchannel_antitop_JetEnDown  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_ST_tchannel_antitop_JetEnDown->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_JetEnDown->Scale(kfact_ST_tchannel_antitop);
  //
  TH1D* mT_Stage1_ST_tchannel_antitop_JetResUp  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_ST_tchannel_antitop_JetResUp->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_JetResUp->Scale(kfact_ST_tchannel_antitop);

  TH1D* mT_Stage1_ST_tchannel_antitop_JetResDown  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_ST_tchannel_antitop_JetResDown->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_JetResDown->Scale(kfact_ST_tchannel_antitop);
  //
  TH1D* mT_Stage1_ST_tchannel_antitop_MuonEnUp  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_ST_tchannel_antitop_MuonEnUp->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_MuonEnUp->Scale(kfact_ST_tchannel_antitop);

  TH1D* mT_Stage1_ST_tchannel_antitop_MuonEnDown  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_ST_tchannel_antitop_MuonEnDown->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_MuonEnDown->Scale(kfact_ST_tchannel_antitop);
  //
  TH1D* mT_Stage1_ST_tchannel_antitop_ElectronEnUp  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_ST_tchannel_antitop_ElectronEnUp->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_ElectronEnUp->Scale(kfact_ST_tchannel_antitop);

  TH1D* mT_Stage1_ST_tchannel_antitop_ElectronEnDown  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_ST_tchannel_antitop_ElectronEnDown->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_ElectronEnDown->Scale(kfact_ST_tchannel_antitop);
  //
  TH1D* mT_Stage1_ST_tchannel_antitop_TauEnUp  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_ST_tchannel_antitop_TauEnUp->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_TauEnUp->Scale(kfact_ST_tchannel_antitop);

  TH1D* mT_Stage1_ST_tchannel_antitop_TauEnDown  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_ST_tchannel_antitop_TauEnDown->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_TauEnDown->Scale(kfact_ST_tchannel_antitop);
  //
  TH1D* mT_Stage1_ST_tchannel_antitop_PhotonEnUp  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_ST_tchannel_antitop_PhotonEnUp->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_PhotonEnUp->Scale(kfact_ST_tchannel_antitop);

  TH1D* mT_Stage1_ST_tchannel_antitop_PhotonEnDown  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_ST_tchannel_antitop_PhotonEnDown->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_PhotonEnDown->Scale(kfact_ST_tchannel_antitop);
  //
  TH1D* mT_Stage1_ST_tchannel_antitop_UnclusteredEnUp  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_ST_tchannel_antitop_UnclusteredEnUp->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_UnclusteredEnUp->Scale(kfact_ST_tchannel_antitop);

  TH1D* mT_Stage1_ST_tchannel_antitop_UnclusteredEnDown  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_ST_tchannel_antitop_UnclusteredEnDown->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_UnclusteredEnDown->Scale(kfact_ST_tchannel_antitop);
  //
  TH1D* mT_Stage1_ST_tchannel_antitop_TauScaleUp  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_ST_tchannel_antitop_TauScaleUp->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_TauScaleUp->Scale(kfact_ST_tchannel_antitop);

  TH1D* mT_Stage1_ST_tchannel_antitop_TauScaleDown  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_ST_tchannel_antitop_TauScaleDown->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_TauScaleDown->Scale(kfact_ST_tchannel_antitop);
  //
  TH1D* mT_Stage1_ST_tchannel_antitop_pileupUncertUp  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_ST_tchannel_antitop_pileupUncertUp->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_pileupUncertUp->Scale(kfact_ST_tchannel_antitop);

  TH1D* mT_Stage1_ST_tchannel_antitop_pileupUncertDown  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_ST_tchannel_antitop_pileupUncertDown->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_pileupUncertDown->Scale(kfact_ST_tchannel_antitop);
  //
  TH1D* mT_Stage1_ST_tchannel_antitop_kFactorUp  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_ST_tchannel_antitop_kFactorUp->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_kFactorUp->Scale(kfact_ST_tchannel_antitop);

  TH1D* mT_Stage1_ST_tchannel_antitop_kFactorDown  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_ST_tchannel_antitop_kFactorDown->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_kFactorDown->Scale(kfact_ST_tchannel_antitop);
  //
  TH1D* mT_Stage1_ST_tchannel_antitop_TauIDSFUp  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_ST_tchannel_antitop_TauIDSFUp->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_TauIDSFUp->Scale(kfact_ST_tchannel_antitop);

  TH1D* mT_Stage1_ST_tchannel_antitop_TauIDSFDown  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_ST_tchannel_antitop_TauIDSFDown->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_TauIDSFDown->Scale(kfact_ST_tchannel_antitop);
  //

  TH1D* mT_Stage1_ST_tchannel_antitop_TauIDSFflatUp  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_ST_tchannel_antitop_TauIDSFflatUp->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_TauIDSFflatUp->Scale(kfact_ST_tchannel_antitop);

  TH1D* mT_Stage1_ST_tchannel_antitop_TauIDSFflatDown  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_ST_tchannel_antitop_TauIDSFflatDown->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_TauIDSFflatDown->Scale(kfact_ST_tchannel_antitop);
  //
  TH1D* mT_Stage1_ST_tchannel_antitop_TauELESFUp  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_ST_tchannel_antitop_TauELESFUp->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_TauELESFUp->Scale(kfact_ST_tchannel_antitop);

  TH1D* mT_Stage1_ST_tchannel_antitop_TauELESFDown  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_ST_tchannel_antitop_TauELESFDown->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_TauELESFDown->Scale(kfact_ST_tchannel_antitop);
  //
  //
  TH1D* mT_Stage1_ST_tchannel_antitop_trigSFUp = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_ST_tchannel_antitop_trigSFUp->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_trigSFUp->Scale(kfact_ST_tchannel_antitop);
  //                                                                                                                                                                      
  TH1D* mT_Stage1_ST_tchannel_antitop_trigSFDown = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_ST_tchannel_antitop_trigSFDown->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_trigSFDown->Scale(kfact_ST_tchannel_antitop);
  //
  //

  /*
  TH1D* mT_Stage1_ST_tchannel_antitop_pdfUncertUp  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_ST_tchannel_antitop_pdfUncertUp->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_pdfUncertUp->Scale(kfact_ST_tchannel_antitop);

  TH1D* mT_Stage1_ST_tchannel_antitop_pdfUncertDown  = (TH1D*)file_ST_tchannel_antitop->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_ST_tchannel_antitop_pdfUncertDown->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop_pdfUncertDown->Scale(kfact_ST_tchannel_antitop);
  */  //

  //file_ST_tchannel_top
  TH1D* h1_evt_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/eventCount");
  unsigned long long evt_ST_tchannel_top = h1_evt_ST_tchannel_top->GetEntries(); //Integral();
  double wt_ST_tchannel_top = (xs_ST_tchannel_top*lumi)/evt_ST_tchannel_top ;
  TH1D* mT_Stage1_ST_tchannel_top  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top->Scale(kfact_ST_tchannel_top);
  std::cout << "ST_tchannel_top weighted nevt=" << mT_Stage1_ST_tchannel_top->Integral() << std::endl;
  totalMC += mT_Stage1_ST_tchannel_top->Integral() ;
  //
  TH1D* mT_Stage1_ST_tchannel_top_JetEnUp  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_ST_tchannel_top_JetEnUp->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_JetEnUp->Scale(kfact_ST_tchannel_top);

  TH1D* mT_Stage1_ST_tchannel_top_JetEnDown  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_ST_tchannel_top_JetEnDown->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_JetEnDown->Scale(kfact_ST_tchannel_top);
  //
  TH1D* mT_Stage1_ST_tchannel_top_JetResUp  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_ST_tchannel_top_JetResUp->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_JetResUp->Scale(kfact_ST_tchannel_top);

  TH1D* mT_Stage1_ST_tchannel_top_JetResDown  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_ST_tchannel_top_JetResDown->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_JetResDown->Scale(kfact_ST_tchannel_top);
  //
  TH1D* mT_Stage1_ST_tchannel_top_MuonEnUp  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_ST_tchannel_top_MuonEnUp->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_MuonEnUp->Scale(kfact_ST_tchannel_top);

  TH1D* mT_Stage1_ST_tchannel_top_MuonEnDown  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_ST_tchannel_top_MuonEnDown->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_MuonEnDown->Scale(kfact_ST_tchannel_top);
  //
  TH1D* mT_Stage1_ST_tchannel_top_ElectronEnUp  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_ST_tchannel_top_ElectronEnUp->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_ElectronEnUp->Scale(kfact_ST_tchannel_top);

  TH1D* mT_Stage1_ST_tchannel_top_ElectronEnDown  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_ST_tchannel_top_ElectronEnDown->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_ElectronEnDown->Scale(kfact_ST_tchannel_top);
  //
  TH1D* mT_Stage1_ST_tchannel_top_TauEnUp  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_ST_tchannel_top_TauEnUp->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_TauEnUp->Scale(kfact_ST_tchannel_top);

  TH1D* mT_Stage1_ST_tchannel_top_TauEnDown  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_ST_tchannel_top_TauEnDown->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_TauEnDown->Scale(kfact_ST_tchannel_top);
  //
  TH1D* mT_Stage1_ST_tchannel_top_PhotonEnUp  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_ST_tchannel_top_PhotonEnUp->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_PhotonEnUp->Scale(kfact_ST_tchannel_top);

  TH1D* mT_Stage1_ST_tchannel_top_PhotonEnDown  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_ST_tchannel_top_PhotonEnDown->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_PhotonEnDown->Scale(kfact_ST_tchannel_top);
  //
  TH1D* mT_Stage1_ST_tchannel_top_UnclusteredEnUp  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_ST_tchannel_top_UnclusteredEnUp->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_UnclusteredEnUp->Scale(kfact_ST_tchannel_top);

  TH1D* mT_Stage1_ST_tchannel_top_UnclusteredEnDown  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_ST_tchannel_top_UnclusteredEnDown->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_UnclusteredEnDown->Scale(kfact_ST_tchannel_top);
  //
  TH1D* mT_Stage1_ST_tchannel_top_TauScaleUp  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_ST_tchannel_top_TauScaleUp->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_TauScaleUp->Scale(kfact_ST_tchannel_top);

  TH1D* mT_Stage1_ST_tchannel_top_TauScaleDown  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_ST_tchannel_top_TauScaleDown->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_TauScaleDown->Scale(kfact_ST_tchannel_top);
  //
  TH1D* mT_Stage1_ST_tchannel_top_pileupUncertUp  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_ST_tchannel_top_pileupUncertUp->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_pileupUncertUp->Scale(kfact_ST_tchannel_top);

  TH1D* mT_Stage1_ST_tchannel_top_pileupUncertDown  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_ST_tchannel_top_pileupUncertDown->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_pileupUncertDown->Scale(kfact_ST_tchannel_top);
  //
  TH1D* mT_Stage1_ST_tchannel_top_kFactorUp  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_ST_tchannel_top_kFactorUp->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_kFactorUp->Scale(kfact_ST_tchannel_top);

  TH1D* mT_Stage1_ST_tchannel_top_kFactorDown  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_ST_tchannel_top_kFactorDown->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_kFactorDown->Scale(kfact_ST_tchannel_top);
  //
  TH1D* mT_Stage1_ST_tchannel_top_TauIDSFUp  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_ST_tchannel_top_TauIDSFUp->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_TauIDSFUp->Scale(kfact_ST_tchannel_top);

  TH1D* mT_Stage1_ST_tchannel_top_TauIDSFDown  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_ST_tchannel_top_TauIDSFDown->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_TauIDSFDown->Scale(kfact_ST_tchannel_top);

  TH1D* mT_Stage1_ST_tchannel_top_TauIDSFflatUp  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_ST_tchannel_top_TauIDSFflatUp->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_TauIDSFflatUp->Scale(kfact_ST_tchannel_top);

  TH1D* mT_Stage1_ST_tchannel_top_TauIDSFflatDown  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_ST_tchannel_top_TauIDSFflatDown->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_TauIDSFflatDown->Scale(kfact_ST_tchannel_top);

  TH1D* mT_Stage1_ST_tchannel_top_TauELESFUp  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_ST_tchannel_top_TauELESFUp->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_TauELESFUp->Scale(kfact_ST_tchannel_top);

  TH1D* mT_Stage1_ST_tchannel_top_TauELESFDown  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_ST_tchannel_top_TauELESFDown->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_TauELESFDown->Scale(kfact_ST_tchannel_top);

  TH1D* mT_Stage1_ST_tchannel_top_trigSFUp  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_ST_tchannel_top_trigSFUp->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_trigSFUp->Scale(kfact_ST_tchannel_top);

  TH1D* mT_Stage1_ST_tchannel_top_trigSFDown  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_ST_tchannel_top_trigSFDown->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_trigSFDown->Scale(kfact_ST_tchannel_top);
  //
  /*
  TH1D* mT_Stage1_ST_tchannel_top_pdfUncertUp  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_ST_tchannel_top_pdfUncertUp->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_pdfUncertUp->Scale(kfact_ST_tchannel_top);

  TH1D* mT_Stage1_ST_tchannel_top_pdfUncertDown  = (TH1D*)file_ST_tchannel_top->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_ST_tchannel_top_pdfUncertDown->Scale(wt_ST_tchannel_top);
  mT_Stage1_ST_tchannel_top_pdfUncertDown->Scale(kfact_ST_tchannel_top);
  */ //

  //file_ST_tW_antitop
  TH1D* h1_evt_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/eventCount");
  unsigned long long evt_ST_tW_antitop = h1_evt_ST_tW_antitop->GetEntries(); //Integral();
  double wt_ST_tW_antitop = (xs_ST_tW_antitop*lumi)/evt_ST_tW_antitop ;
  TH1D* mT_Stage1_ST_tW_antitop  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop->Scale(kfact_ST_tW_antitop);
  std::cout << "ST_tW_antitop weighted nevt=" << mT_Stage1_ST_tW_antitop->Integral() << std::endl;
  totalMC += mT_Stage1_ST_tW_antitop->Integral();
  //
  TH1D* mT_Stage1_ST_tW_antitop_JetEnUp  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_ST_tW_antitop_JetEnUp->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_JetEnUp->Scale(kfact_ST_tW_antitop);

  TH1D* mT_Stage1_ST_tW_antitop_JetEnDown  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_ST_tW_antitop_JetEnDown->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_JetEnDown->Scale(kfact_ST_tW_antitop);
  //
  TH1D* mT_Stage1_ST_tW_antitop_JetResUp  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_ST_tW_antitop_JetResUp->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_JetResUp->Scale(kfact_ST_tW_antitop);

  TH1D* mT_Stage1_ST_tW_antitop_JetResDown  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_ST_tW_antitop_JetResDown->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_JetResDown->Scale(kfact_ST_tW_antitop);
  //
  TH1D* mT_Stage1_ST_tW_antitop_MuonEnUp  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_ST_tW_antitop_MuonEnUp->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_MuonEnUp->Scale(kfact_ST_tW_antitop);

  TH1D* mT_Stage1_ST_tW_antitop_MuonEnDown  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_ST_tW_antitop_MuonEnDown->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_MuonEnDown->Scale(kfact_ST_tW_antitop);
  //
  TH1D* mT_Stage1_ST_tW_antitop_ElectronEnUp  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_ST_tW_antitop_ElectronEnUp->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_ElectronEnUp->Scale(kfact_ST_tW_antitop);

  TH1D* mT_Stage1_ST_tW_antitop_ElectronEnDown  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_ST_tW_antitop_ElectronEnDown->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_ElectronEnDown->Scale(kfact_ST_tW_antitop);
  //
  TH1D* mT_Stage1_ST_tW_antitop_TauEnUp  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_ST_tW_antitop_TauEnUp->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_TauEnUp->Scale(kfact_ST_tW_antitop);

  TH1D* mT_Stage1_ST_tW_antitop_TauEnDown  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_ST_tW_antitop_TauEnDown->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_TauEnDown->Scale(kfact_ST_tW_antitop);
  //
  TH1D* mT_Stage1_ST_tW_antitop_PhotonEnUp  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_ST_tW_antitop_PhotonEnUp->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_PhotonEnUp->Scale(kfact_ST_tW_antitop);

  TH1D* mT_Stage1_ST_tW_antitop_PhotonEnDown  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_ST_tW_antitop_PhotonEnDown->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_PhotonEnDown->Scale(kfact_ST_tW_antitop);
  //
  TH1D* mT_Stage1_ST_tW_antitop_UnclusteredEnUp  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_ST_tW_antitop_UnclusteredEnUp->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_UnclusteredEnUp->Scale(kfact_ST_tW_antitop);

  TH1D* mT_Stage1_ST_tW_antitop_UnclusteredEnDown  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_ST_tW_antitop_UnclusteredEnDown->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_UnclusteredEnDown->Scale(kfact_ST_tW_antitop);
  //
  TH1D* mT_Stage1_ST_tW_antitop_TauScaleUp  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_ST_tW_antitop_TauScaleUp->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_TauScaleUp->Scale(kfact_ST_tW_antitop);

  TH1D* mT_Stage1_ST_tW_antitop_TauScaleDown  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_ST_tW_antitop_TauScaleDown->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_TauScaleDown->Scale(kfact_ST_tW_antitop);
  //
  TH1D* mT_Stage1_ST_tW_antitop_pileupUncertUp  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_ST_tW_antitop_pileupUncertUp->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_pileupUncertUp->Scale(kfact_ST_tW_antitop);

  TH1D* mT_Stage1_ST_tW_antitop_pileupUncertDown  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_ST_tW_antitop_pileupUncertDown->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_pileupUncertDown->Scale(kfact_ST_tW_antitop);
  //
  TH1D* mT_Stage1_ST_tW_antitop_kFactorUp  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_ST_tW_antitop_kFactorUp->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_kFactorUp->Scale(kfact_ST_tW_antitop);

  TH1D* mT_Stage1_ST_tW_antitop_kFactorDown  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_ST_tW_antitop_kFactorDown->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_kFactorDown->Scale(kfact_ST_tW_antitop);
  //
  TH1D* mT_Stage1_ST_tW_antitop_TauIDSFUp  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_ST_tW_antitop_TauIDSFUp->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_TauIDSFUp->Scale(kfact_ST_tW_antitop);

  TH1D* mT_Stage1_ST_tW_antitop_TauIDSFDown  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_ST_tW_antitop_TauIDSFDown->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_TauIDSFDown->Scale(kfact_ST_tW_antitop);

  TH1D* mT_Stage1_ST_tW_antitop_TauIDSFflatUp  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_ST_tW_antitop_TauIDSFflatUp->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_TauIDSFflatUp->Scale(kfact_ST_tW_antitop);

  TH1D* mT_Stage1_ST_tW_antitop_TauIDSFflatDown  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_ST_tW_antitop_TauIDSFflatDown->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_TauIDSFflatDown->Scale(kfact_ST_tW_antitop);
  //
  TH1D* mT_Stage1_ST_tW_antitop_TauELESFUp  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_ST_tW_antitop_TauELESFUp->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_TauELESFUp->Scale(kfact_ST_tW_antitop);

  TH1D* mT_Stage1_ST_tW_antitop_TauELESFDown  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_ST_tW_antitop_TauELESFDown->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_TauELESFDown->Scale(kfact_ST_tW_antitop);

  TH1D* mT_Stage1_ST_tW_antitop_trigSFUp  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_ST_tW_antitop_trigSFUp->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_trigSFUp->Scale(kfact_ST_tW_antitop);

  TH1D* mT_Stage1_ST_tW_antitop_trigSFDown  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_ST_tW_antitop_trigSFDown->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_trigSFDown->Scale(kfact_ST_tW_antitop);
  //
  /*
  TH1D* mT_Stage1_ST_tW_antitop_pdfUncertUp  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_ST_tW_antitop_pdfUncertUp->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_pdfUncertUp->Scale(kfact_ST_tW_antitop);

  TH1D* mT_Stage1_ST_tW_antitop_pdfUncertDown  = (TH1D*)file_ST_tW_antitop->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_ST_tW_antitop_pdfUncertDown->Scale(wt_ST_tW_antitop);
  mT_Stage1_ST_tW_antitop_pdfUncertDown->Scale(kfact_ST_tW_antitop);
  */  //

  //file_ST_tW_top
  TH1D* h1_evt_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/histoDir/eventCount");
  unsigned long long evt_ST_tW_top = h1_evt_ST_tW_top->GetEntries(); //Integral();
  double wt_ST_tW_top = (xs_ST_tW_top*lumi)/evt_ST_tW_top ;
  TH1D* mT_Stage1_ST_tW_top  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_ST_tW_top->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top->Scale(kfact_ST_tW_top);
  std::cout << "ST_tW_top weighted nevt=" << mT_Stage1_ST_tW_top->Integral() << std::endl;
  totalMC += mT_Stage1_ST_tW_top->Integral() ;
  //
  TH1D* mT_Stage1_ST_tW_top_JetEnUp  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_ST_tW_top_JetEnUp->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_JetEnUp->Scale(kfact_ST_tW_top);

  TH1D* mT_Stage1_ST_tW_top_JetEnDown  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_ST_tW_top_JetEnDown->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_JetEnDown->Scale(kfact_ST_tW_top);
  //
  TH1D* mT_Stage1_ST_tW_top_JetResUp  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_ST_tW_top_JetResUp->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_JetResUp->Scale(kfact_ST_tW_top);

  TH1D* mT_Stage1_ST_tW_top_JetResDown  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_ST_tW_top_JetResDown->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_JetResDown->Scale(kfact_ST_tW_top);
  //
  TH1D* mT_Stage1_ST_tW_top_MuonEnUp  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_ST_tW_top_MuonEnUp->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_MuonEnUp->Scale(kfact_ST_tW_top);

  TH1D* mT_Stage1_ST_tW_top_MuonEnDown  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_ST_tW_top_MuonEnDown->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_MuonEnDown->Scale(kfact_ST_tW_top);
  //
  TH1D* mT_Stage1_ST_tW_top_ElectronEnUp  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_ST_tW_top_ElectronEnUp->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_ElectronEnUp->Scale(kfact_ST_tW_top);

  TH1D* mT_Stage1_ST_tW_top_ElectronEnDown  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_ST_tW_top_ElectronEnDown->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_ElectronEnDown->Scale(kfact_ST_tW_top);
  //
  TH1D* mT_Stage1_ST_tW_top_TauEnUp  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_ST_tW_top_TauEnUp->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_TauEnUp->Scale(kfact_ST_tW_top);

  TH1D* mT_Stage1_ST_tW_top_TauEnDown  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_ST_tW_top_TauEnDown->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_TauEnDown->Scale(kfact_ST_tW_top);
  //
  TH1D* mT_Stage1_ST_tW_top_PhotonEnUp  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_ST_tW_top_PhotonEnUp->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_PhotonEnUp->Scale(kfact_ST_tW_top);

  TH1D* mT_Stage1_ST_tW_top_PhotonEnDown  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_ST_tW_top_PhotonEnDown->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_PhotonEnDown->Scale(kfact_ST_tW_top);
  //
  TH1D* mT_Stage1_ST_tW_top_UnclusteredEnUp  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_ST_tW_top_UnclusteredEnUp->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_UnclusteredEnUp->Scale(kfact_ST_tW_top);

  TH1D* mT_Stage1_ST_tW_top_UnclusteredEnDown  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_ST_tW_top_UnclusteredEnDown->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_UnclusteredEnDown->Scale(kfact_ST_tW_top);
  //
  TH1D* mT_Stage1_ST_tW_top_TauScaleUp  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_ST_tW_top_TauScaleUp->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_TauScaleUp->Scale(kfact_ST_tW_top);

  TH1D* mT_Stage1_ST_tW_top_TauScaleDown  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_ST_tW_top_TauScaleDown->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_TauScaleDown->Scale(kfact_ST_tW_top);
  //
  TH1D* mT_Stage1_ST_tW_top_pileupUncertUp  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_ST_tW_top_pileupUncertUp->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_pileupUncertUp->Scale(kfact_ST_tW_top);

  TH1D* mT_Stage1_ST_tW_top_pileupUncertDown  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_ST_tW_top_pileupUncertDown->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_pileupUncertDown->Scale(kfact_ST_tW_top);
  //
  TH1D* mT_Stage1_ST_tW_top_kFactorUp  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_ST_tW_top_kFactorUp->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_kFactorUp->Scale(kfact_ST_tW_top);

  TH1D* mT_Stage1_ST_tW_top_kFactorDown  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_ST_tW_top_kFactorDown->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_kFactorDown->Scale(kfact_ST_tW_top);
  //
  TH1D* mT_Stage1_ST_tW_top_TauIDSFUp  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_ST_tW_top_TauIDSFUp->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_TauIDSFUp->Scale(kfact_ST_tW_top);

  TH1D* mT_Stage1_ST_tW_top_TauIDSFDown  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_ST_tW_top_TauIDSFDown->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_TauIDSFDown->Scale(kfact_ST_tW_top);

  TH1D* mT_Stage1_ST_tW_top_TauIDSFflatUp  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_ST_tW_top_TauIDSFflatUp->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_TauIDSFflatUp->Scale(kfact_ST_tW_top);

  TH1D* mT_Stage1_ST_tW_top_TauIDSFflatDown  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_ST_tW_top_TauIDSFflatDown->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_TauIDSFflatDown->Scale(kfact_ST_tW_top);
  //
  TH1D* mT_Stage1_ST_tW_top_TauELESFUp  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_ST_tW_top_TauELESFUp->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_TauELESFUp->Scale(kfact_ST_tW_top);

  TH1D* mT_Stage1_ST_tW_top_TauELESFDown  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_ST_tW_top_TauELESFDown->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_TauELESFDown->Scale(kfact_ST_tW_top);

  TH1D* mT_Stage1_ST_tW_top_trigSFUp  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_ST_tW_top_trigSFUp->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_trigSFUp->Scale(kfact_ST_tW_top);

  TH1D* mT_Stage1_ST_tW_top_trigSFDown  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_ST_tW_top_trigSFDown->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_trigSFDown->Scale(kfact_ST_tW_top);
  //
  /*
  TH1D* mT_Stage1_ST_tW_top_pdfUncertUp  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_ST_tW_top_pdfUncertUp->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_pdfUncertUp->Scale(kfact_ST_tW_top);

  TH1D* mT_Stage1_ST_tW_top_pdfUncertDown  = (TH1D*)file_ST_tW_top->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_ST_tW_top_pdfUncertDown->Scale(wt_ST_tW_top);
  mT_Stage1_ST_tW_top_pdfUncertDown->Scale(kfact_ST_tW_top);
  */ //

  TH1D* total_ST = (TH1D*)mT_Stage1_ST_tchannel_antitop->Clone(); 
  total_ST->Add(mT_Stage1_ST_tchannel_top);
  total_ST->Add(mT_Stage1_ST_tW_antitop);
  total_ST->Add(mT_Stage1_ST_tW_top);
  total_ST->SetFillColorAlpha(kCyan,0.5);
  total_ST->SetLineColor(kBlack);
  total_ST->Rebin(80);

  //file_WJetsToLNu_HT100To200
  TH1D* h1_evt_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT100To200 = h1_evt_WJetsToLNu_HT100To200->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT100To200 = (xs_WJetsToLNu_HT100To200*lumi)/evt_WJetsToLNu_HT100To200 ;
  TH1D* mT_Stage1_WJetsToLNu_HT100To200  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  std::cout << "WJetsToLNu_HT100To200 weighted nevt=" << mT_Stage1_WJetsToLNu_HT100To200->Integral() << std::endl;
  totalMC += mT_Stage1_WJetsToLNu_HT100To200->Integral();
  //
  TH1D* mT_Stage1_WJetsToLNu_HT100To200_JetEnUp  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_WJetsToLNu_HT100To200_JetEnUp->Scale(wt_WJetsToLNu_HT100To200);

  TH1D* mT_Stage1_WJetsToLNu_HT100To200_JetEnDown  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_WJetsToLNu_HT100To200_JetEnDown->Scale(wt_WJetsToLNu_HT100To200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT100To200_JetResUp  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_WJetsToLNu_HT100To200_JetResUp->Scale(wt_WJetsToLNu_HT100To200);

  TH1D* mT_Stage1_WJetsToLNu_HT100To200_JetResDown  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_WJetsToLNu_HT100To200_JetResDown->Scale(wt_WJetsToLNu_HT100To200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT100To200_MuonEnUp  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_WJetsToLNu_HT100To200_MuonEnUp->Scale(wt_WJetsToLNu_HT100To200);

  TH1D* mT_Stage1_WJetsToLNu_HT100To200_MuonEnDown  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_WJetsToLNu_HT100To200_MuonEnDown->Scale(wt_WJetsToLNu_HT100To200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT100To200_ElectronEnUp  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_WJetsToLNu_HT100To200_ElectronEnUp->Scale(wt_WJetsToLNu_HT100To200);

  TH1D* mT_Stage1_WJetsToLNu_HT100To200_ElectronEnDown  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_WJetsToLNu_HT100To200_ElectronEnDown->Scale(wt_WJetsToLNu_HT100To200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT100To200_TauEnUp  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_WJetsToLNu_HT100To200_TauEnUp->Scale(wt_WJetsToLNu_HT100To200);

  TH1D* mT_Stage1_WJetsToLNu_HT100To200_TauEnDown  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_WJetsToLNu_HT100To200_TauEnDown->Scale(wt_WJetsToLNu_HT100To200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT100To200_PhotonEnUp  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_WJetsToLNu_HT100To200_PhotonEnUp->Scale(wt_WJetsToLNu_HT100To200);

  TH1D* mT_Stage1_WJetsToLNu_HT100To200_PhotonEnDown  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_WJetsToLNu_HT100To200_PhotonEnDown->Scale(wt_WJetsToLNu_HT100To200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT100To200_UnclusteredEnUp  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_WJetsToLNu_HT100To200_UnclusteredEnUp->Scale(wt_WJetsToLNu_HT100To200);

  TH1D* mT_Stage1_WJetsToLNu_HT100To200_UnclusteredEnDown  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_WJetsToLNu_HT100To200_UnclusteredEnDown->Scale(wt_WJetsToLNu_HT100To200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT100To200_TauScaleUp  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_WJetsToLNu_HT100To200_TauScaleUp->Scale(wt_WJetsToLNu_HT100To200);

  TH1D* mT_Stage1_WJetsToLNu_HT100To200_TauScaleDown  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_WJetsToLNu_HT100To200_TauScaleDown->Scale(wt_WJetsToLNu_HT100To200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT100To200_pileupUncertUp  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_WJetsToLNu_HT100To200_pileupUncertUp->Scale(wt_WJetsToLNu_HT100To200);

  TH1D* mT_Stage1_WJetsToLNu_HT100To200_pileupUncertDown  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_WJetsToLNu_HT100To200_pileupUncertDown->Scale(wt_WJetsToLNu_HT100To200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT100To200_kFactorUp  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_WJetsToLNu_HT100To200_kFactorUp->Scale(wt_WJetsToLNu_HT100To200);

  TH1D* mT_Stage1_WJetsToLNu_HT100To200_kFactorDown  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_WJetsToLNu_HT100To200_kFactorDown->Scale(wt_WJetsToLNu_HT100To200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT100To200_TauIDSFUp  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_WJetsToLNu_HT100To200_TauIDSFUp->Scale(wt_WJetsToLNu_HT100To200);

  TH1D* mT_Stage1_WJetsToLNu_HT100To200_TauIDSFDown  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_WJetsToLNu_HT100To200_TauIDSFDown->Scale(wt_WJetsToLNu_HT100To200);

  TH1D* mT_Stage1_WJetsToLNu_HT100To200_TauIDSFflatUp  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_WJetsToLNu_HT100To200_TauIDSFflatUp->Scale(wt_WJetsToLNu_HT100To200);

  TH1D* mT_Stage1_WJetsToLNu_HT100To200_TauIDSFflatDown  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_WJetsToLNu_HT100To200_TauIDSFflatDown->Scale(wt_WJetsToLNu_HT100To200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT100To200_TauELESFUp  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_WJetsToLNu_HT100To200_TauELESFUp->Scale(wt_WJetsToLNu_HT100To200);

  TH1D* mT_Stage1_WJetsToLNu_HT100To200_TauELESFDown  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_WJetsToLNu_HT100To200_TauELESFDown->Scale(wt_WJetsToLNu_HT100To200);

  TH1D* mT_Stage1_WJetsToLNu_HT100To200_trigSFUp  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_WJetsToLNu_HT100To200_trigSFUp->Scale(wt_WJetsToLNu_HT100To200);

  TH1D* mT_Stage1_WJetsToLNu_HT100To200_trigSFDown  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_WJetsToLNu_HT100To200_trigSFDown->Scale(wt_WJetsToLNu_HT100To200);
  //
  /*
  TH1D* mT_Stage1_WJetsToLNu_HT100To200_pdfUncertUp  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_WJetsToLNu_HT100To200_pdfUncertUp->Scale(wt_WJetsToLNu_HT100To200);

  TH1D* mT_Stage1_WJetsToLNu_HT100To200_pdfUncertDown  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_WJetsToLNu_HT100To200_pdfUncertDown->Scale(wt_WJetsToLNu_HT100To200);
  */  //

  //file_WJetsToLNu_HT200To400
  TH1D* h1_evt_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT200To400 = h1_evt_WJetsToLNu_HT200To400->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT200To400 = (xs_WJetsToLNu_HT200To400*lumi)/evt_WJetsToLNu_HT200To400 ;
  TH1D* mT_Stage1_WJetsToLNu_HT200To400  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  std::cout << "WJetsToLNu_HT200To400 weighted nevt=" << mT_Stage1_WJetsToLNu_HT200To400->Integral() << std::endl;
  totalMC += mT_Stage1_WJetsToLNu_HT200To400->Integral();
  //
  TH1D* mT_Stage1_WJetsToLNu_HT200To400_JetEnUp  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_WJetsToLNu_HT200To400_JetEnUp->Scale(wt_WJetsToLNu_HT200To400);

  TH1D* mT_Stage1_WJetsToLNu_HT200To400_JetEnDown  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_WJetsToLNu_HT200To400_JetEnDown->Scale(wt_WJetsToLNu_HT200To400);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT200To400_JetResUp  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_WJetsToLNu_HT200To400_JetResUp->Scale(wt_WJetsToLNu_HT200To400);

  TH1D* mT_Stage1_WJetsToLNu_HT200To400_JetResDown  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_WJetsToLNu_HT200To400_JetResDown->Scale(wt_WJetsToLNu_HT200To400);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT200To400_MuonEnUp  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_WJetsToLNu_HT200To400_MuonEnUp->Scale(wt_WJetsToLNu_HT200To400);

  TH1D* mT_Stage1_WJetsToLNu_HT200To400_MuonEnDown  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_WJetsToLNu_HT200To400_MuonEnDown->Scale(wt_WJetsToLNu_HT200To400);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT200To400_ElectronEnUp  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_WJetsToLNu_HT200To400_ElectronEnUp->Scale(wt_WJetsToLNu_HT200To400);

  TH1D* mT_Stage1_WJetsToLNu_HT200To400_ElectronEnDown  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_WJetsToLNu_HT200To400_ElectronEnDown->Scale(wt_WJetsToLNu_HT200To400);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT200To400_TauEnUp  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_WJetsToLNu_HT200To400_TauEnUp->Scale(wt_WJetsToLNu_HT200To400);

  TH1D* mT_Stage1_WJetsToLNu_HT200To400_TauEnDown  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_WJetsToLNu_HT200To400_TauEnDown->Scale(wt_WJetsToLNu_HT200To400);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT200To400_PhotonEnUp  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_WJetsToLNu_HT200To400_PhotonEnUp->Scale(wt_WJetsToLNu_HT200To400);

  TH1D* mT_Stage1_WJetsToLNu_HT200To400_PhotonEnDown  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_WJetsToLNu_HT200To400_PhotonEnDown->Scale(wt_WJetsToLNu_HT200To400);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT200To400_UnclusteredEnUp  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_WJetsToLNu_HT200To400_UnclusteredEnUp->Scale(wt_WJetsToLNu_HT200To400);

  TH1D* mT_Stage1_WJetsToLNu_HT200To400_UnclusteredEnDown  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_WJetsToLNu_HT200To400_UnclusteredEnDown->Scale(wt_WJetsToLNu_HT200To400);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT200To400_TauScaleUp  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_WJetsToLNu_HT200To400_TauScaleUp->Scale(wt_WJetsToLNu_HT200To400);

  TH1D* mT_Stage1_WJetsToLNu_HT200To400_TauScaleDown  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_WJetsToLNu_HT200To400_TauScaleDown->Scale(wt_WJetsToLNu_HT200To400);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT200To400_pileupUncertUp  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_WJetsToLNu_HT200To400_pileupUncertUp->Scale(wt_WJetsToLNu_HT200To400);

  TH1D* mT_Stage1_WJetsToLNu_HT200To400_pileupUncertDown  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_WJetsToLNu_HT200To400_pileupUncertDown->Scale(wt_WJetsToLNu_HT200To400);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT200To400_kFactorUp  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_WJetsToLNu_HT200To400_kFactorUp->Scale(wt_WJetsToLNu_HT200To400);

  TH1D* mT_Stage1_WJetsToLNu_HT200To400_kFactorDown  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_WJetsToLNu_HT200To400_kFactorDown->Scale(wt_WJetsToLNu_HT200To400);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT200To400_TauIDSFUp  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_WJetsToLNu_HT200To400_TauIDSFUp->Scale(wt_WJetsToLNu_HT200To400);

  TH1D* mT_Stage1_WJetsToLNu_HT200To400_TauIDSFDown  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_WJetsToLNu_HT200To400_TauIDSFDown->Scale(wt_WJetsToLNu_HT200To400);

  TH1D* mT_Stage1_WJetsToLNu_HT200To400_TauIDSFflatUp  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_WJetsToLNu_HT200To400_TauIDSFflatUp->Scale(wt_WJetsToLNu_HT200To400);

  TH1D* mT_Stage1_WJetsToLNu_HT200To400_TauIDSFflatDown  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_WJetsToLNu_HT200To400_TauIDSFflatDown->Scale(wt_WJetsToLNu_HT200To400);

  TH1D* mT_Stage1_WJetsToLNu_HT200To400_TauELESFUp  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_WJetsToLNu_HT200To400_TauELESFUp->Scale(wt_WJetsToLNu_HT200To400);

  TH1D* mT_Stage1_WJetsToLNu_HT200To400_TauELESFDown  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_WJetsToLNu_HT200To400_TauELESFDown->Scale(wt_WJetsToLNu_HT200To400);

  TH1D* mT_Stage1_WJetsToLNu_HT200To400_trigSFUp  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_WJetsToLNu_HT200To400_trigSFUp->Scale(wt_WJetsToLNu_HT200To400);

  TH1D* mT_Stage1_WJetsToLNu_HT200To400_trigSFDown  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_WJetsToLNu_HT200To400_trigSFDown->Scale(wt_WJetsToLNu_HT200To400);
  //
  /*
  TH1D* mT_Stage1_WJetsToLNu_HT200To400_pdfUncertUp  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_WJetsToLNu_HT200To400_pdfUncertUp->Scale(wt_WJetsToLNu_HT200To400);

  TH1D* mT_Stage1_WJetsToLNu_HT200To400_pdfUncertDown  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_WJetsToLNu_HT200To400_pdfUncertDown->Scale(wt_WJetsToLNu_HT200To400);
  */  //

  //file_WJetsToLNu_HT400To600
  TH1D* h1_evt_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT400To600 = h1_evt_WJetsToLNu_HT400To600->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT400To600 = (xs_WJetsToLNu_HT400To600*lumi)/evt_WJetsToLNu_HT400To600 ;
  TH1D* mT_Stage1_WJetsToLNu_HT400To600  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  std::cout << "WJetsToLNu_HT400To600 weighted nevt=" << mT_Stage1_WJetsToLNu_HT400To600->Integral() << std::endl;
  totalMC += mT_Stage1_WJetsToLNu_HT400To600->Integral();
  //
  TH1D* mT_Stage1_WJetsToLNu_HT400To600_JetEnUp  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_WJetsToLNu_HT400To600_JetEnUp->Scale(wt_WJetsToLNu_HT400To600);

  TH1D* mT_Stage1_WJetsToLNu_HT400To600_JetEnDown  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_WJetsToLNu_HT400To600_JetEnDown->Scale(wt_WJetsToLNu_HT400To600);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT400To600_JetResUp  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_WJetsToLNu_HT400To600_JetResUp->Scale(wt_WJetsToLNu_HT400To600);

  TH1D* mT_Stage1_WJetsToLNu_HT400To600_JetResDown  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_WJetsToLNu_HT400To600_JetResDown->Scale(wt_WJetsToLNu_HT400To600);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT400To600_MuonEnUp  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_WJetsToLNu_HT400To600_MuonEnUp->Scale(wt_WJetsToLNu_HT400To600);

  TH1D* mT_Stage1_WJetsToLNu_HT400To600_MuonEnDown  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_WJetsToLNu_HT400To600_MuonEnDown->Scale(wt_WJetsToLNu_HT400To600);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT400To600_ElectronEnUp  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_WJetsToLNu_HT400To600_ElectronEnUp->Scale(wt_WJetsToLNu_HT400To600);

  TH1D* mT_Stage1_WJetsToLNu_HT400To600_ElectronEnDown  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_WJetsToLNu_HT400To600_ElectronEnDown->Scale(wt_WJetsToLNu_HT400To600);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT400To600_TauEnUp  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_WJetsToLNu_HT400To600_TauEnUp->Scale(wt_WJetsToLNu_HT400To600);

  TH1D* mT_Stage1_WJetsToLNu_HT400To600_TauEnDown  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_WJetsToLNu_HT400To600_TauEnDown->Scale(wt_WJetsToLNu_HT400To600);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT400To600_PhotonEnUp  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_WJetsToLNu_HT400To600_PhotonEnUp->Scale(wt_WJetsToLNu_HT400To600);

  TH1D* mT_Stage1_WJetsToLNu_HT400To600_PhotonEnDown  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_WJetsToLNu_HT400To600_PhotonEnDown->Scale(wt_WJetsToLNu_HT400To600);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT400To600_UnclusteredEnUp  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_WJetsToLNu_HT400To600_UnclusteredEnUp->Scale(wt_WJetsToLNu_HT400To600);

  TH1D* mT_Stage1_WJetsToLNu_HT400To600_UnclusteredEnDown  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_WJetsToLNu_HT400To600_UnclusteredEnDown->Scale(wt_WJetsToLNu_HT400To600);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT400To600_TauScaleUp  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_WJetsToLNu_HT400To600_TauScaleUp->Scale(wt_WJetsToLNu_HT400To600);

  TH1D* mT_Stage1_WJetsToLNu_HT400To600_TauScaleDown  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_WJetsToLNu_HT400To600_TauScaleDown->Scale(wt_WJetsToLNu_HT400To600);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT400To600_pileupUncertUp  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_WJetsToLNu_HT400To600_pileupUncertUp->Scale(wt_WJetsToLNu_HT400To600);

  TH1D* mT_Stage1_WJetsToLNu_HT400To600_pileupUncertDown  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_WJetsToLNu_HT400To600_pileupUncertDown->Scale(wt_WJetsToLNu_HT400To600);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT400To600_kFactorUp  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_WJetsToLNu_HT400To600_kFactorUp->Scale(wt_WJetsToLNu_HT400To600);

  TH1D* mT_Stage1_WJetsToLNu_HT400To600_kFactorDown  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_WJetsToLNu_HT400To600_kFactorDown->Scale(wt_WJetsToLNu_HT400To600);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT400To600_TauIDSFUp  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_WJetsToLNu_HT400To600_TauIDSFUp->Scale(wt_WJetsToLNu_HT400To600);

  TH1D* mT_Stage1_WJetsToLNu_HT400To600_TauIDSFDown  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_WJetsToLNu_HT400To600_TauIDSFDown->Scale(wt_WJetsToLNu_HT400To600);

  TH1D* mT_Stage1_WJetsToLNu_HT400To600_TauIDSFflatUp  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_WJetsToLNu_HT400To600_TauIDSFflatUp->Scale(wt_WJetsToLNu_HT400To600);

  TH1D* mT_Stage1_WJetsToLNu_HT400To600_TauIDSFflatDown  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_WJetsToLNu_HT400To600_TauIDSFflatDown->Scale(wt_WJetsToLNu_HT400To600);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT400To600_TauELESFUp  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_WJetsToLNu_HT400To600_TauELESFUp->Scale(wt_WJetsToLNu_HT400To600);

  TH1D* mT_Stage1_WJetsToLNu_HT400To600_TauELESFDown  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_WJetsToLNu_HT400To600_TauELESFDown->Scale(wt_WJetsToLNu_HT400To600);

  TH1D* mT_Stage1_WJetsToLNu_HT400To600_trigSFUp  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_WJetsToLNu_HT400To600_trigSFUp->Scale(wt_WJetsToLNu_HT400To600);

  TH1D* mT_Stage1_WJetsToLNu_HT400To600_trigSFDown  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_WJetsToLNu_HT400To600_trigSFDown->Scale(wt_WJetsToLNu_HT400To600);
  //
  /*
  TH1D* mT_Stage1_WJetsToLNu_HT400To600_pdfUncertUp  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_WJetsToLNu_HT400To600_pdfUncertUp->Scale(wt_WJetsToLNu_HT400To600);

  TH1D* mT_Stage1_WJetsToLNu_HT400To600_pdfUncertDown  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_WJetsToLNu_HT400To600_pdfUncertDown->Scale(wt_WJetsToLNu_HT400To600);
  */ //

  //file_WJetsToLNu_HT600To800
  TH1D* h1_evt_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT600To800 = h1_evt_WJetsToLNu_HT600To800->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT600To800 = (xs_WJetsToLNu_HT600To800*lumi)/evt_WJetsToLNu_HT600To800 ;
  TH1D* mT_Stage1_WJetsToLNu_HT600To800  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  std::cout << "WJetsToLNu_HT600To800 weighted nevt=" << mT_Stage1_WJetsToLNu_HT600To800->Integral() << std::endl;
  totalMC +=  mT_Stage1_WJetsToLNu_HT600To800->Integral();
  //
  TH1D* mT_Stage1_WJetsToLNu_HT600To800_JetEnUp  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_WJetsToLNu_HT600To800_JetEnUp->Scale(wt_WJetsToLNu_HT600To800);

  TH1D* mT_Stage1_WJetsToLNu_HT600To800_JetEnDown  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_WJetsToLNu_HT600To800_JetEnDown->Scale(wt_WJetsToLNu_HT600To800);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT600To800_JetResUp  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_WJetsToLNu_HT600To800_JetResUp->Scale(wt_WJetsToLNu_HT600To800);

  TH1D* mT_Stage1_WJetsToLNu_HT600To800_JetResDown  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_WJetsToLNu_HT600To800_JetResDown->Scale(wt_WJetsToLNu_HT600To800);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT600To800_MuonEnUp  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_WJetsToLNu_HT600To800_MuonEnUp->Scale(wt_WJetsToLNu_HT600To800);

  TH1D* mT_Stage1_WJetsToLNu_HT600To800_MuonEnDown  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_WJetsToLNu_HT600To800_MuonEnDown->Scale(wt_WJetsToLNu_HT600To800);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT600To800_ElectronEnUp  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_WJetsToLNu_HT600To800_ElectronEnUp->Scale(wt_WJetsToLNu_HT600To800);

  TH1D* mT_Stage1_WJetsToLNu_HT600To800_ElectronEnDown  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_WJetsToLNu_HT600To800_ElectronEnDown->Scale(wt_WJetsToLNu_HT600To800);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT600To800_TauEnUp  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_WJetsToLNu_HT600To800_TauEnUp->Scale(wt_WJetsToLNu_HT600To800);

  TH1D* mT_Stage1_WJetsToLNu_HT600To800_TauEnDown  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_WJetsToLNu_HT600To800_TauEnDown->Scale(wt_WJetsToLNu_HT600To800);
   //
  TH1D* mT_Stage1_WJetsToLNu_HT600To800_PhotonEnUp  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_WJetsToLNu_HT600To800_PhotonEnUp->Scale(wt_WJetsToLNu_HT600To800);

  TH1D* mT_Stage1_WJetsToLNu_HT600To800_PhotonEnDown  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_WJetsToLNu_HT600To800_PhotonEnDown->Scale(wt_WJetsToLNu_HT600To800);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT600To800_UnclusteredEnUp  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_WJetsToLNu_HT600To800_UnclusteredEnUp->Scale(wt_WJetsToLNu_HT600To800);

  TH1D* mT_Stage1_WJetsToLNu_HT600To800_UnclusteredEnDown  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_WJetsToLNu_HT600To800_UnclusteredEnDown->Scale(wt_WJetsToLNu_HT600To800);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT600To800_TauScaleUp  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_WJetsToLNu_HT600To800_TauScaleUp->Scale(wt_WJetsToLNu_HT600To800);

  TH1D* mT_Stage1_WJetsToLNu_HT600To800_TauScaleDown  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_WJetsToLNu_HT600To800_TauScaleDown->Scale(wt_WJetsToLNu_HT600To800);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT600To800_pileupUncertUp  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_WJetsToLNu_HT600To800_pileupUncertUp->Scale(wt_WJetsToLNu_HT600To800);

  TH1D* mT_Stage1_WJetsToLNu_HT600To800_pileupUncertDown  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_WJetsToLNu_HT600To800_pileupUncertDown->Scale(wt_WJetsToLNu_HT600To800);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT600To800_kFactorUp  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_WJetsToLNu_HT600To800_kFactorUp->Scale(wt_WJetsToLNu_HT600To800);

  TH1D* mT_Stage1_WJetsToLNu_HT600To800_kFactorDown  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_WJetsToLNu_HT600To800_kFactorDown->Scale(wt_WJetsToLNu_HT600To800);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT600To800_TauIDSFUp  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_WJetsToLNu_HT600To800_TauIDSFUp->Scale(wt_WJetsToLNu_HT600To800);

  TH1D* mT_Stage1_WJetsToLNu_HT600To800_TauIDSFDown  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_WJetsToLNu_HT600To800_TauIDSFDown->Scale(wt_WJetsToLNu_HT600To800);

  TH1D* mT_Stage1_WJetsToLNu_HT600To800_TauIDSFflatUp  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_WJetsToLNu_HT600To800_TauIDSFflatUp->Scale(wt_WJetsToLNu_HT600To800);

  TH1D* mT_Stage1_WJetsToLNu_HT600To800_TauIDSFflatDown  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_WJetsToLNu_HT600To800_TauIDSFflatDown->Scale(wt_WJetsToLNu_HT600To800);

  TH1D* mT_Stage1_WJetsToLNu_HT600To800_TauELESFUp  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_WJetsToLNu_HT600To800_TauELESFUp->Scale(wt_WJetsToLNu_HT600To800);

  TH1D* mT_Stage1_WJetsToLNu_HT600To800_TauELESFDown  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_WJetsToLNu_HT600To800_TauELESFDown->Scale(wt_WJetsToLNu_HT600To800);

  TH1D* mT_Stage1_WJetsToLNu_HT600To800_trigSFUp  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_WJetsToLNu_HT600To800_trigSFUp->Scale(wt_WJetsToLNu_HT600To800);

  TH1D* mT_Stage1_WJetsToLNu_HT600To800_trigSFDown  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_WJetsToLNu_HT600To800_trigSFDown->Scale(wt_WJetsToLNu_HT600To800);
  //
  /*
  TH1D* mT_Stage1_WJetsToLNu_HT600To800_pdfUncertUp  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_WJetsToLNu_HT600To800_pdfUncertUp->Scale(wt_WJetsToLNu_HT600To800);

  TH1D* mT_Stage1_WJetsToLNu_HT600To800_pdfUncertDown  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_WJetsToLNu_HT600To800_pdfUncertDown->Scale(wt_WJetsToLNu_HT600To800);
  */ //

  //file_WJetsToLNu_HT800To1200
  TH1D* h1_evt_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT800To1200 = h1_evt_WJetsToLNu_HT800To1200->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT800To1200 = (xs_WJetsToLNu_HT800To1200*lumi)/evt_WJetsToLNu_HT800To1200 ;
  TH1D* mT_Stage1_WJetsToLNu_HT800To1200  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  std::cout << "WJetsToLNu_HT800To1200 weighted nevt=" << mT_Stage1_WJetsToLNu_HT800To1200->Integral() << std::endl;
  totalMC += mT_Stage1_WJetsToLNu_HT800To1200->Integral();
  //
  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_JetEnUp  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_WJetsToLNu_HT800To1200_JetEnUp->Scale(wt_WJetsToLNu_HT800To1200);

  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_JetEnDown  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_WJetsToLNu_HT800To1200_JetEnDown->Scale(wt_WJetsToLNu_HT800To1200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_JetResUp  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_WJetsToLNu_HT800To1200_JetResUp->Scale(wt_WJetsToLNu_HT800To1200);

  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_JetResDown  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_WJetsToLNu_HT800To1200_JetResDown->Scale(wt_WJetsToLNu_HT800To1200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_MuonEnUp  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_WJetsToLNu_HT800To1200_MuonEnUp->Scale(wt_WJetsToLNu_HT800To1200);

  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_MuonEnDown  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_WJetsToLNu_HT800To1200_MuonEnDown->Scale(wt_WJetsToLNu_HT800To1200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_ElectronEnUp  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_WJetsToLNu_HT800To1200_ElectronEnUp->Scale(wt_WJetsToLNu_HT800To1200);

  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_ElectronEnDown  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_WJetsToLNu_HT800To1200_ElectronEnDown->Scale(wt_WJetsToLNu_HT800To1200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_TauEnUp  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_WJetsToLNu_HT800To1200_TauEnUp->Scale(wt_WJetsToLNu_HT800To1200);

  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_TauEnDown  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_WJetsToLNu_HT800To1200_TauEnDown->Scale(wt_WJetsToLNu_HT800To1200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_PhotonEnUp  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_WJetsToLNu_HT800To1200_PhotonEnUp->Scale(wt_WJetsToLNu_HT800To1200);

  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_PhotonEnDown  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_WJetsToLNu_HT800To1200_PhotonEnDown->Scale(wt_WJetsToLNu_HT800To1200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_UnclusteredEnUp  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_WJetsToLNu_HT800To1200_UnclusteredEnUp->Scale(wt_WJetsToLNu_HT800To1200);

  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_UnclusteredEnDown  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_WJetsToLNu_HT800To1200_UnclusteredEnDown->Scale(wt_WJetsToLNu_HT800To1200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_TauScaleUp  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_WJetsToLNu_HT800To1200_TauScaleUp->Scale(wt_WJetsToLNu_HT800To1200);

  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_TauScaleDown  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_WJetsToLNu_HT800To1200_TauScaleDown->Scale(wt_WJetsToLNu_HT800To1200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_pileupUncertUp  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_WJetsToLNu_HT800To1200_pileupUncertUp->Scale(wt_WJetsToLNu_HT800To1200);

  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_pileupUncertDown  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_WJetsToLNu_HT800To1200_pileupUncertDown->Scale(wt_WJetsToLNu_HT800To1200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_kFactorUp  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_WJetsToLNu_HT800To1200_kFactorUp->Scale(wt_WJetsToLNu_HT800To1200);

  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_kFactorDown  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_WJetsToLNu_HT800To1200_kFactorDown->Scale(wt_WJetsToLNu_HT800To1200);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_TauIDSFUp  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_WJetsToLNu_HT800To1200_TauIDSFUp->Scale(wt_WJetsToLNu_HT800To1200);

  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_TauIDSFDown  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_WJetsToLNu_HT800To1200_TauIDSFDown->Scale(wt_WJetsToLNu_HT800To1200);

  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_TauIDSFflatUp  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_WJetsToLNu_HT800To1200_TauIDSFflatUp->Scale(wt_WJetsToLNu_HT800To1200);

  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_TauIDSFflatDown  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_WJetsToLNu_HT800To1200_TauIDSFflatDown->Scale(wt_WJetsToLNu_HT800To1200);

  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_TauELESFUp  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_WJetsToLNu_HT800To1200_TauELESFUp->Scale(wt_WJetsToLNu_HT800To1200);

  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_TauELESFDown  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_WJetsToLNu_HT800To1200_TauELESFDown->Scale(wt_WJetsToLNu_HT800To1200);

  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_trigSFUp  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_WJetsToLNu_HT800To1200_trigSFUp->Scale(wt_WJetsToLNu_HT800To1200);

  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_trigSFDown  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_WJetsToLNu_HT800To1200_trigSFDown->Scale(wt_WJetsToLNu_HT800To1200);
  //
  /*
  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_pdfUncertUp  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_WJetsToLNu_HT800To1200_pdfUncertUp->Scale(wt_WJetsToLNu_HT800To1200);

  TH1D* mT_Stage1_WJetsToLNu_HT800To1200_pdfUncertDown  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_WJetsToLNu_HT800To1200_pdfUncertDown->Scale(wt_WJetsToLNu_HT800To1200);
  */ //

  //file_WJetsToLNu_HT1200To2500
  TH1D* h1_evt_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT1200To2500 = h1_evt_WJetsToLNu_HT1200To2500->GetEntries(); //Integral();                                                             
  double wt_WJetsToLNu_HT1200To2500 = (xs_WJetsToLNu_HT1200To2500*lumi)/evt_WJetsToLNu_HT1200To2500 ;
  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  std::cout << "WJetsToLNu_HT1200To2500 weighted nevt=" << mT_Stage1_WJetsToLNu_HT1200To2500->Integral() << std::endl;
  totalMC += mT_Stage1_WJetsToLNu_HT1200To2500->Integral();
  //
  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_JetEnUp  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_WJetsToLNu_HT1200To2500_JetEnUp->Scale(wt_WJetsToLNu_HT1200To2500);

  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_JetEnDown  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_WJetsToLNu_HT1200To2500_JetEnDown->Scale(wt_WJetsToLNu_HT1200To2500);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_JetResUp  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_WJetsToLNu_HT1200To2500_JetResUp->Scale(wt_WJetsToLNu_HT1200To2500);

  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_JetResDown  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_WJetsToLNu_HT1200To2500_JetResDown->Scale(wt_WJetsToLNu_HT1200To2500);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_MuonEnUp  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_WJetsToLNu_HT1200To2500_MuonEnUp->Scale(wt_WJetsToLNu_HT1200To2500);

  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_MuonEnDown  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_WJetsToLNu_HT1200To2500_MuonEnDown->Scale(wt_WJetsToLNu_HT1200To2500);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_ElectronEnUp  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_WJetsToLNu_HT1200To2500_ElectronEnUp->Scale(wt_WJetsToLNu_HT1200To2500);

  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_ElectronEnDown  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_WJetsToLNu_HT1200To2500_ElectronEnDown->Scale(wt_WJetsToLNu_HT1200To2500);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_TauEnUp  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_WJetsToLNu_HT1200To2500_TauEnUp->Scale(wt_WJetsToLNu_HT1200To2500);

  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_TauEnDown  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_WJetsToLNu_HT1200To2500_TauEnDown->Scale(wt_WJetsToLNu_HT1200To2500);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_PhotonEnUp  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_WJetsToLNu_HT1200To2500_PhotonEnUp->Scale(wt_WJetsToLNu_HT1200To2500);

  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_PhotonEnDown  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_WJetsToLNu_HT1200To2500_PhotonEnDown->Scale(wt_WJetsToLNu_HT1200To2500);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_UnclusteredEnUp  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_WJetsToLNu_HT1200To2500_UnclusteredEnUp->Scale(wt_WJetsToLNu_HT1200To2500);

  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_UnclusteredEnDown  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_WJetsToLNu_HT1200To2500_UnclusteredEnDown->Scale(wt_WJetsToLNu_HT1200To2500);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_TauScaleUp  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_WJetsToLNu_HT1200To2500_TauScaleUp->Scale(wt_WJetsToLNu_HT1200To2500);

  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_TauScaleDown  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_WJetsToLNu_HT1200To2500_TauScaleDown->Scale(wt_WJetsToLNu_HT1200To2500);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_pileupUncertUp  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_WJetsToLNu_HT1200To2500_pileupUncertUp->Scale(wt_WJetsToLNu_HT1200To2500);

  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_pileupUncertDown  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_WJetsToLNu_HT1200To2500_pileupUncertDown->Scale(wt_WJetsToLNu_HT1200To2500);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_kFactorUp  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_WJetsToLNu_HT1200To2500_kFactorUp->Scale(wt_WJetsToLNu_HT1200To2500);

  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_kFactorDown  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_WJetsToLNu_HT1200To2500_kFactorDown->Scale(wt_WJetsToLNu_HT1200To2500);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_TauIDSFUp  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_WJetsToLNu_HT1200To2500_TauIDSFUp->Scale(wt_WJetsToLNu_HT1200To2500);

  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_TauIDSFDown  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_WJetsToLNu_HT1200To2500_TauIDSFDown->Scale(wt_WJetsToLNu_HT1200To2500);

  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_TauIDSFflatUp  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_WJetsToLNu_HT1200To2500_TauIDSFflatUp->Scale(wt_WJetsToLNu_HT1200To2500);

  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_TauIDSFflatDown  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_WJetsToLNu_HT1200To2500_TauIDSFflatDown->Scale(wt_WJetsToLNu_HT1200To2500);

  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_TauELESFUp  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_WJetsToLNu_HT1200To2500_TauELESFUp->Scale(wt_WJetsToLNu_HT1200To2500);

  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_TauELESFDown  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_WJetsToLNu_HT1200To2500_TauELESFDown->Scale(wt_WJetsToLNu_HT1200To2500);

  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_trigSFUp  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_WJetsToLNu_HT1200To2500_trigSFUp->Scale(wt_WJetsToLNu_HT1200To2500);

  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_trigSFDown  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_WJetsToLNu_HT1200To2500_trigSFDown->Scale(wt_WJetsToLNu_HT1200To2500);
  //
  /*
  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_pdfUncertUp  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_WJetsToLNu_HT1200To2500_pdfUncertUp->Scale(wt_WJetsToLNu_HT1200To2500);

  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500_pdfUncertDown  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_WJetsToLNu_HT1200To2500_pdfUncertDown->Scale(wt_WJetsToLNu_HT1200To2500);
  */ //

  //file_WJetsToLNu_HT2500ToInf
  TH1D* h1_evt_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu_HT2500ToInf = h1_evt_WJetsToLNu_HT2500ToInf->GetEntries(); //Integral();                                                             
  double wt_WJetsToLNu_HT2500ToInf = (xs_WJetsToLNu_HT2500ToInf*lumi)/evt_WJetsToLNu_HT2500ToInf ;
  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  std::cout << "WJetsToLNu_HT2500ToInf weighted nevt=" << mT_Stage1_WJetsToLNu_HT2500ToInf->Integral() << std::endl;
  totalMC += mT_Stage1_WJetsToLNu_HT2500ToInf->Integral();
  //
  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_JetEnUp  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_WJetsToLNu_HT2500ToInf_JetEnUp->Scale(wt_WJetsToLNu_HT2500ToInf);

  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_JetEnDown  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_WJetsToLNu_HT2500ToInf_JetEnDown->Scale(wt_WJetsToLNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_JetResUp  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_WJetsToLNu_HT2500ToInf_JetResUp->Scale(wt_WJetsToLNu_HT2500ToInf);

  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_JetResDown  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_WJetsToLNu_HT2500ToInf_JetResDown->Scale(wt_WJetsToLNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_MuonEnUp  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_WJetsToLNu_HT2500ToInf_MuonEnUp->Scale(wt_WJetsToLNu_HT2500ToInf);

  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_MuonEnDown  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_WJetsToLNu_HT2500ToInf_MuonEnDown->Scale(wt_WJetsToLNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_ElectronEnUp  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_WJetsToLNu_HT2500ToInf_ElectronEnUp->Scale(wt_WJetsToLNu_HT2500ToInf);

  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_ElectronEnDown  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_WJetsToLNu_HT2500ToInf_ElectronEnDown->Scale(wt_WJetsToLNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_TauEnUp  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_WJetsToLNu_HT2500ToInf_TauEnUp->Scale(wt_WJetsToLNu_HT2500ToInf);

  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_TauEnDown  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_WJetsToLNu_HT2500ToInf_TauEnDown->Scale(wt_WJetsToLNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_PhotonEnUp  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_WJetsToLNu_HT2500ToInf_PhotonEnUp->Scale(wt_WJetsToLNu_HT2500ToInf);

  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_PhotonEnDown  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_WJetsToLNu_HT2500ToInf_PhotonEnDown->Scale(wt_WJetsToLNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_UnclusteredEnUp  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_WJetsToLNu_HT2500ToInf_UnclusteredEnUp->Scale(wt_WJetsToLNu_HT2500ToInf);

  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_UnclusteredEnDown  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_WJetsToLNu_HT2500ToInf_UnclusteredEnDown->Scale(wt_WJetsToLNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_TauScaleUp  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_WJetsToLNu_HT2500ToInf_TauScaleUp->Scale(wt_WJetsToLNu_HT2500ToInf);

  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_TauScaleDown  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_WJetsToLNu_HT2500ToInf_TauScaleDown->Scale(wt_WJetsToLNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_pileupUncertUp  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_WJetsToLNu_HT2500ToInf_pileupUncertUp->Scale(wt_WJetsToLNu_HT2500ToInf);

  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_pileupUncertDown  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_WJetsToLNu_HT2500ToInf_pileupUncertDown->Scale(wt_WJetsToLNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_kFactorUp  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_WJetsToLNu_HT2500ToInf_kFactorUp->Scale(wt_WJetsToLNu_HT2500ToInf);

  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_kFactorDown  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_WJetsToLNu_HT2500ToInf_kFactorDown->Scale(wt_WJetsToLNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_TauIDSFUp  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_WJetsToLNu_HT2500ToInf_TauIDSFUp->Scale(wt_WJetsToLNu_HT2500ToInf);

  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_TauIDSFDown  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_WJetsToLNu_HT2500ToInf_TauIDSFDown->Scale(wt_WJetsToLNu_HT2500ToInf);

  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_TauIDSFflatUp  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_WJetsToLNu_HT2500ToInf_TauIDSFflatUp->Scale(wt_WJetsToLNu_HT2500ToInf);

  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_TauIDSFflatDown  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_WJetsToLNu_HT2500ToInf_TauIDSFflatDown->Scale(wt_WJetsToLNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_TauELESFUp  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_WJetsToLNu_HT2500ToInf_TauELESFUp->Scale(wt_WJetsToLNu_HT2500ToInf);

  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_TauELESFDown  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_WJetsToLNu_HT2500ToInf_TauELESFDown->Scale(wt_WJetsToLNu_HT2500ToInf);

  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_trigSFUp  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_WJetsToLNu_HT2500ToInf_trigSFUp->Scale(wt_WJetsToLNu_HT2500ToInf);

  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_trigSFDown  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_WJetsToLNu_HT2500ToInf_trigSFDown->Scale(wt_WJetsToLNu_HT2500ToInf);
  //
  /*
  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_pdfUncertUp  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_WJetsToLNu_HT2500ToInf_pdfUncertUp->Scale(wt_WJetsToLNu_HT2500ToInf);

  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf_pdfUncertDown  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_WJetsToLNu_HT2500ToInf_pdfUncertDown->Scale(wt_WJetsToLNu_HT2500ToInf);
  */  //

  //file_WToTauNu_M100
  TH1D* h1_evt_WToTauNu_M100 = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M100 = h1_evt_WToTauNu_M100->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M100 = (xs_WToTauNu_M100*lumi)/evt_WToTauNu_M100 ;
  TH1D* mT_Stage1_WToTauNu_M100  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WToTauNu_M100->Scale(wt_WToTauNu_M100);
  std::cout << "WToTauNu_M100 weighted nevt=" << mT_Stage1_WToTauNu_M100->Integral() << std::endl;
  totalMC += mT_Stage1_WToTauNu_M100->Integral() ;
  //
  TH1D* mT_Stage1_WToTauNu_M100_JetEnUp  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_WToTauNu_M100_JetEnUp->Scale(wt_WToTauNu_M100);

  TH1D* mT_Stage1_WToTauNu_M100_JetEnDown  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_WToTauNu_M100_JetEnDown->Scale(wt_WToTauNu_M100);
  //
  TH1D* mT_Stage1_WToTauNu_M100_JetResUp  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_WToTauNu_M100_JetResUp->Scale(wt_WToTauNu_M100);

  TH1D* mT_Stage1_WToTauNu_M100_JetResDown  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_WToTauNu_M100_JetResDown->Scale(wt_WToTauNu_M100);
  //
  TH1D* mT_Stage1_WToTauNu_M100_MuonEnUp  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_WToTauNu_M100_MuonEnUp->Scale(wt_WToTauNu_M100);

  TH1D* mT_Stage1_WToTauNu_M100_MuonEnDown  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_WToTauNu_M100_MuonEnDown->Scale(wt_WToTauNu_M100);
  //
  TH1D* mT_Stage1_WToTauNu_M100_ElectronEnUp  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_WToTauNu_M100_ElectronEnUp->Scale(wt_WToTauNu_M100);

  TH1D* mT_Stage1_WToTauNu_M100_ElectronEnDown  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_WToTauNu_M100_ElectronEnDown->Scale(wt_WToTauNu_M100);
  //
  TH1D* mT_Stage1_WToTauNu_M100_TauEnUp  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_WToTauNu_M100_TauEnUp->Scale(wt_WToTauNu_M100);

  TH1D* mT_Stage1_WToTauNu_M100_TauEnDown  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_WToTauNu_M100_TauEnDown->Scale(wt_WToTauNu_M100);
  //
  TH1D* mT_Stage1_WToTauNu_M100_PhotonEnUp  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_WToTauNu_M100_PhotonEnUp->Scale(wt_WToTauNu_M100);

  TH1D* mT_Stage1_WToTauNu_M100_PhotonEnDown  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_WToTauNu_M100_PhotonEnDown->Scale(wt_WToTauNu_M100);
  //
  TH1D* mT_Stage1_WToTauNu_M100_UnclusteredEnUp  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_WToTauNu_M100_UnclusteredEnUp->Scale(wt_WToTauNu_M100);

  TH1D* mT_Stage1_WToTauNu_M100_UnclusteredEnDown  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_WToTauNu_M100_UnclusteredEnDown->Scale(wt_WToTauNu_M100);
  //
  TH1D* mT_Stage1_WToTauNu_M100_TauScaleUp  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_WToTauNu_M100_TauScaleUp->Scale(wt_WToTauNu_M100);

  TH1D* mT_Stage1_WToTauNu_M100_TauScaleDown  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_WToTauNu_M100_TauScaleDown->Scale(wt_WToTauNu_M100);
  //
  TH1D* mT_Stage1_WToTauNu_M100_pileupUncertUp  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_WToTauNu_M100_pileupUncertUp->Scale(wt_WToTauNu_M100);

  TH1D* mT_Stage1_WToTauNu_M100_pileupUncertDown  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_WToTauNu_M100_pileupUncertDown->Scale(wt_WToTauNu_M100);
  //
  TH1D* mT_Stage1_WToTauNu_M100_kFactorUp  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_WToTauNu_M100_kFactorUp->Scale(wt_WToTauNu_M100);

  TH1D* mT_Stage1_WToTauNu_M100_kFactorDown  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_WToTauNu_M100_kFactorDown->Scale(wt_WToTauNu_M100);
  //
  TH1D* mT_Stage1_WToTauNu_M100_TauIDSFUp  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_WToTauNu_M100_TauIDSFUp->Scale(wt_WToTauNu_M100);

  TH1D* mT_Stage1_WToTauNu_M100_TauIDSFDown  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_WToTauNu_M100_TauIDSFDown->Scale(wt_WToTauNu_M100);

  TH1D* mT_Stage1_WToTauNu_M100_TauIDSFflatUp  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_WToTauNu_M100_TauIDSFflatUp->Scale(wt_WToTauNu_M100);

  TH1D* mT_Stage1_WToTauNu_M100_TauIDSFflatDown  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_WToTauNu_M100_TauIDSFflatDown->Scale(wt_WToTauNu_M100);
  //
  TH1D* mT_Stage1_WToTauNu_M100_TauELESFUp  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_WToTauNu_M100_TauELESFUp->Scale(wt_WToTauNu_M100);

  TH1D* mT_Stage1_WToTauNu_M100_TauELESFDown  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_WToTauNu_M100_TauELESFDown->Scale(wt_WToTauNu_M100);

  TH1D* mT_Stage1_WToTauNu_M100_trigSFUp  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_WToTauNu_M100_trigSFUp->Scale(wt_WToTauNu_M100);

  TH1D* mT_Stage1_WToTauNu_M100_trigSFDown  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_WToTauNu_M100_trigSFDown->Scale(wt_WToTauNu_M100);
  //
  /*
  TH1D* mT_Stage1_WToTauNu_M100_pdfUncertUp  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_WToTauNu_M100_pdfUncertUp->Scale(wt_WToTauNu_M100);

  TH1D* mT_Stage1_WToTauNu_M100_pdfUncertDown  = (TH1D*)file_WToTauNu_M100->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_WToTauNu_M100_pdfUncertDown->Scale(wt_WToTauNu_M100);
  */ //

  //file_WToTauNu_M200
  TH1D* h1_evt_WToTauNu_M200 = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M200 = h1_evt_WToTauNu_M200->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M200 = (xs_WToTauNu_M200*lumi)/evt_WToTauNu_M200 ;
  TH1D* mT_Stage1_WToTauNu_M200  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WToTauNu_M200->Scale(wt_WToTauNu_M200);
  std::cout << "WToTauNu_M200 weighted nevt=" << mT_Stage1_WToTauNu_M200->Integral() << std::endl;
  totalMC += mT_Stage1_WToTauNu_M200->Integral();
  //
  TH1D* mT_Stage1_WToTauNu_M200_JetEnUp  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_WToTauNu_M200_JetEnUp->Scale(wt_WToTauNu_M200);

  TH1D* mT_Stage1_WToTauNu_M200_JetEnDown  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_WToTauNu_M200_JetEnDown->Scale(wt_WToTauNu_M200);
  //
  TH1D* mT_Stage1_WToTauNu_M200_JetResUp  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_WToTauNu_M200_JetResUp->Scale(wt_WToTauNu_M200);

  TH1D* mT_Stage1_WToTauNu_M200_JetResDown  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_WToTauNu_M200_JetResDown->Scale(wt_WToTauNu_M200);
  //
  TH1D* mT_Stage1_WToTauNu_M200_MuonEnUp  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_WToTauNu_M200_MuonEnUp->Scale(wt_WToTauNu_M200);

  TH1D* mT_Stage1_WToTauNu_M200_MuonEnDown  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_WToTauNu_M200_MuonEnDown->Scale(wt_WToTauNu_M200);
  //
  TH1D* mT_Stage1_WToTauNu_M200_ElectronEnUp  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_WToTauNu_M200_ElectronEnUp->Scale(wt_WToTauNu_M200);

  TH1D* mT_Stage1_WToTauNu_M200_ElectronEnDown  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_WToTauNu_M200_ElectronEnDown->Scale(wt_WToTauNu_M200);
  //
  TH1D* mT_Stage1_WToTauNu_M200_TauEnUp  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_WToTauNu_M200_TauEnUp->Scale(wt_WToTauNu_M200);

  TH1D* mT_Stage1_WToTauNu_M200_TauEnDown  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_WToTauNu_M200_TauEnDown->Scale(wt_WToTauNu_M200);
  //
  TH1D* mT_Stage1_WToTauNu_M200_PhotonEnUp  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_WToTauNu_M200_PhotonEnUp->Scale(wt_WToTauNu_M200);

  TH1D* mT_Stage1_WToTauNu_M200_PhotonEnDown  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_WToTauNu_M200_PhotonEnDown->Scale(wt_WToTauNu_M200);
  //
  TH1D* mT_Stage1_WToTauNu_M200_UnclusteredEnUp  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_WToTauNu_M200_UnclusteredEnUp->Scale(wt_WToTauNu_M200);

  TH1D* mT_Stage1_WToTauNu_M200_UnclusteredEnDown  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_WToTauNu_M200_UnclusteredEnDown->Scale(wt_WToTauNu_M200);
  //
  TH1D* mT_Stage1_WToTauNu_M200_TauScaleUp  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_WToTauNu_M200_TauScaleUp->Scale(wt_WToTauNu_M200);

  TH1D* mT_Stage1_WToTauNu_M200_TauScaleDown  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_WToTauNu_M200_TauScaleDown->Scale(wt_WToTauNu_M200);
  //
  TH1D* mT_Stage1_WToTauNu_M200_pileupUncertUp  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_WToTauNu_M200_pileupUncertUp->Scale(wt_WToTauNu_M200);

  TH1D* mT_Stage1_WToTauNu_M200_pileupUncertDown  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_WToTauNu_M200_pileupUncertDown->Scale(wt_WToTauNu_M200);
  //
  TH1D* mT_Stage1_WToTauNu_M200_kFactorUp  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_WToTauNu_M200_kFactorUp->Scale(wt_WToTauNu_M200);

  TH1D* mT_Stage1_WToTauNu_M200_kFactorDown  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_WToTauNu_M200_kFactorDown->Scale(wt_WToTauNu_M200);
  //
  TH1D* mT_Stage1_WToTauNu_M200_TauIDSFUp  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_WToTauNu_M200_TauIDSFUp->Scale(wt_WToTauNu_M200);

  TH1D* mT_Stage1_WToTauNu_M200_TauIDSFDown  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_WToTauNu_M200_TauIDSFDown->Scale(wt_WToTauNu_M200);

  TH1D* mT_Stage1_WToTauNu_M200_TauIDSFflatUp  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_WToTauNu_M200_TauIDSFflatUp->Scale(wt_WToTauNu_M200);

  TH1D* mT_Stage1_WToTauNu_M200_TauIDSFflatDown  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_WToTauNu_M200_TauIDSFflatDown->Scale(wt_WToTauNu_M200);

  TH1D* mT_Stage1_WToTauNu_M200_TauELESFUp  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_WToTauNu_M200_TauELESFUp->Scale(wt_WToTauNu_M200);

  TH1D* mT_Stage1_WToTauNu_M200_TauELESFDown  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_WToTauNu_M200_TauELESFDown->Scale(wt_WToTauNu_M200);

  TH1D* mT_Stage1_WToTauNu_M200_trigSFUp  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_WToTauNu_M200_trigSFUp->Scale(wt_WToTauNu_M200);

  TH1D* mT_Stage1_WToTauNu_M200_trigSFDown  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_WToTauNu_M200_trigSFDown->Scale(wt_WToTauNu_M200);
  //
  /*
  TH1D* mT_Stage1_WToTauNu_M200_pdfUncertUp  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_WToTauNu_M200_pdfUncertUp->Scale(wt_WToTauNu_M200);

  TH1D* mT_Stage1_WToTauNu_M200_pdfUncertDown  = (TH1D*)file_WToTauNu_M200->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_WToTauNu_M200_pdfUncertDown->Scale(wt_WToTauNu_M200);
  */  //

  //file_WToTauNu_M500
  TH1D* h1_evt_WToTauNu_M500 = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M500 = h1_evt_WToTauNu_M500->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M500 = (xs_WToTauNu_M500*lumi)/evt_WToTauNu_M500 ;
  TH1D* mT_Stage1_WToTauNu_M500  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WToTauNu_M500->Scale(wt_WToTauNu_M500);
  std::cout << "WToTauNu_M500 weighted nevt=" << mT_Stage1_WToTauNu_M500->Integral() << std::endl;
  totalMC += mT_Stage1_WToTauNu_M500->Integral() ;
  //
  TH1D* mT_Stage1_WToTauNu_M500_JetEnUp  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_WToTauNu_M500_JetEnUp->Scale(wt_WToTauNu_M500);

  TH1D* mT_Stage1_WToTauNu_M500_JetEnDown  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_WToTauNu_M500_JetEnDown->Scale(wt_WToTauNu_M500);
  //
  TH1D* mT_Stage1_WToTauNu_M500_JetResUp  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_WToTauNu_M500_JetResUp->Scale(wt_WToTauNu_M500);

  TH1D* mT_Stage1_WToTauNu_M500_JetResDown  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_WToTauNu_M500_JetResDown->Scale(wt_WToTauNu_M500);
  //
  TH1D* mT_Stage1_WToTauNu_M500_MuonEnUp  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_WToTauNu_M500_MuonEnUp->Scale(wt_WToTauNu_M500);

  TH1D* mT_Stage1_WToTauNu_M500_MuonEnDown  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_WToTauNu_M500_MuonEnDown->Scale(wt_WToTauNu_M500);
  //
  TH1D* mT_Stage1_WToTauNu_M500_ElectronEnUp  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_WToTauNu_M500_ElectronEnUp->Scale(wt_WToTauNu_M500);

  TH1D* mT_Stage1_WToTauNu_M500_ElectronEnDown  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_WToTauNu_M500_ElectronEnDown->Scale(wt_WToTauNu_M500);
  //
  TH1D* mT_Stage1_WToTauNu_M500_TauEnUp  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_WToTauNu_M500_TauEnUp->Scale(wt_WToTauNu_M500);

  TH1D* mT_Stage1_WToTauNu_M500_TauEnDown  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_WToTauNu_M500_TauEnDown->Scale(wt_WToTauNu_M500);
  //
  TH1D* mT_Stage1_WToTauNu_M500_PhotonEnUp  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_WToTauNu_M500_PhotonEnUp->Scale(wt_WToTauNu_M500);

  TH1D* mT_Stage1_WToTauNu_M500_PhotonEnDown  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_WToTauNu_M500_PhotonEnDown->Scale(wt_WToTauNu_M500);
  //
  TH1D* mT_Stage1_WToTauNu_M500_UnclusteredEnUp  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_WToTauNu_M500_UnclusteredEnUp->Scale(wt_WToTauNu_M500);

  TH1D* mT_Stage1_WToTauNu_M500_UnclusteredEnDown  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_WToTauNu_M500_UnclusteredEnDown->Scale(wt_WToTauNu_M500);
  //
  TH1D* mT_Stage1_WToTauNu_M500_TauScaleUp  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_WToTauNu_M500_TauScaleUp->Scale(wt_WToTauNu_M500);

  TH1D* mT_Stage1_WToTauNu_M500_TauScaleDown  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_WToTauNu_M500_TauScaleDown->Scale(wt_WToTauNu_M500);
  //
  TH1D* mT_Stage1_WToTauNu_M500_pileupUncertUp  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_WToTauNu_M500_pileupUncertUp->Scale(wt_WToTauNu_M500);

  TH1D* mT_Stage1_WToTauNu_M500_pileupUncertDown  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_WToTauNu_M500_pileupUncertDown->Scale(wt_WToTauNu_M500);
  //
  TH1D* mT_Stage1_WToTauNu_M500_kFactorUp  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_WToTauNu_M500_kFactorUp->Scale(wt_WToTauNu_M500);

  TH1D* mT_Stage1_WToTauNu_M500_kFactorDown  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_WToTauNu_M500_kFactorDown->Scale(wt_WToTauNu_M500);
  //
  TH1D* mT_Stage1_WToTauNu_M500_TauIDSFUp  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_WToTauNu_M500_TauIDSFUp->Scale(wt_WToTauNu_M500);

  TH1D* mT_Stage1_WToTauNu_M500_TauIDSFDown  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_WToTauNu_M500_TauIDSFDown->Scale(wt_WToTauNu_M500);

  TH1D* mT_Stage1_WToTauNu_M500_TauIDSFflatUp  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_WToTauNu_M500_TauIDSFflatUp->Scale(wt_WToTauNu_M500);

  TH1D* mT_Stage1_WToTauNu_M500_TauIDSFflatDown  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_WToTauNu_M500_TauIDSFflatDown->Scale(wt_WToTauNu_M500);
  //
  TH1D* mT_Stage1_WToTauNu_M500_TauELESFUp  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_WToTauNu_M500_TauELESFUp->Scale(wt_WToTauNu_M500);

  TH1D* mT_Stage1_WToTauNu_M500_TauELESFDown  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_WToTauNu_M500_TauELESFDown->Scale(wt_WToTauNu_M500);

  TH1D* mT_Stage1_WToTauNu_M500_trigSFUp  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_WToTauNu_M500_trigSFUp->Scale(wt_WToTauNu_M500);

  TH1D* mT_Stage1_WToTauNu_M500_trigSFDown  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_WToTauNu_M500_trigSFDown->Scale(wt_WToTauNu_M500);
  //
  /*
  TH1D* mT_Stage1_WToTauNu_M500_pdfUncertUp  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_WToTauNu_M500_pdfUncertUp->Scale(wt_WToTauNu_M500);

  TH1D* mT_Stage1_WToTauNu_M500_pdfUncertDown  = (TH1D*)file_WToTauNu_M500->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_WToTauNu_M500_pdfUncertDown->Scale(wt_WToTauNu_M500);
  */  //

  //file_WToTauNu_M1000
  TH1D* h1_evt_WToTauNu_M1000 = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M1000 = h1_evt_WToTauNu_M1000->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M1000 = (xs_WToTauNu_M1000*lumi)/evt_WToTauNu_M1000 ;
  TH1D* mT_Stage1_WToTauNu_M1000  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WToTauNu_M1000->Scale(wt_WToTauNu_M1000);
  std::cout << "WToTauNu_M1000 weighted nevt=" << mT_Stage1_WToTauNu_M1000->Integral() << std::endl;
  totalMC += mT_Stage1_WToTauNu_M1000->Integral();
  //
  TH1D* mT_Stage1_WToTauNu_M1000_JetEnUp  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_WToTauNu_M1000_JetEnUp->Scale(wt_WToTauNu_M1000);

  TH1D* mT_Stage1_WToTauNu_M1000_JetEnDown  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_WToTauNu_M1000_JetEnDown->Scale(wt_WToTauNu_M1000);
  //
  TH1D* mT_Stage1_WToTauNu_M1000_JetResUp  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_WToTauNu_M1000_JetResUp->Scale(wt_WToTauNu_M1000);

  TH1D* mT_Stage1_WToTauNu_M1000_JetResDown  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_WToTauNu_M1000_JetResDown->Scale(wt_WToTauNu_M1000);
  //
  TH1D* mT_Stage1_WToTauNu_M1000_MuonEnUp  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_WToTauNu_M1000_MuonEnUp->Scale(wt_WToTauNu_M1000);

  TH1D* mT_Stage1_WToTauNu_M1000_MuonEnDown  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_WToTauNu_M1000_MuonEnDown->Scale(wt_WToTauNu_M1000);
  //
  TH1D* mT_Stage1_WToTauNu_M1000_ElectronEnUp  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_WToTauNu_M1000_ElectronEnUp->Scale(wt_WToTauNu_M1000);

  TH1D* mT_Stage1_WToTauNu_M1000_ElectronEnDown  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_WToTauNu_M1000_ElectronEnDown->Scale(wt_WToTauNu_M1000);
  //
  TH1D* mT_Stage1_WToTauNu_M1000_TauEnUp  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_WToTauNu_M1000_TauEnUp->Scale(wt_WToTauNu_M1000);

  TH1D* mT_Stage1_WToTauNu_M1000_TauEnDown  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_WToTauNu_M1000_TauEnDown->Scale(wt_WToTauNu_M1000);
  //
  TH1D* mT_Stage1_WToTauNu_M1000_PhotonEnUp  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_WToTauNu_M1000_PhotonEnUp->Scale(wt_WToTauNu_M1000);

  TH1D* mT_Stage1_WToTauNu_M1000_PhotonEnDown  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_WToTauNu_M1000_PhotonEnDown->Scale(wt_WToTauNu_M1000);
  //
  TH1D* mT_Stage1_WToTauNu_M1000_UnclusteredEnUp  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_WToTauNu_M1000_UnclusteredEnUp->Scale(wt_WToTauNu_M1000);

  TH1D* mT_Stage1_WToTauNu_M1000_UnclusteredEnDown  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_WToTauNu_M1000_UnclusteredEnDown->Scale(wt_WToTauNu_M1000);
  //
  TH1D* mT_Stage1_WToTauNu_M1000_TauScaleUp  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_WToTauNu_M1000_TauScaleUp->Scale(wt_WToTauNu_M1000);

  TH1D* mT_Stage1_WToTauNu_M1000_TauScaleDown  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_WToTauNu_M1000_TauScaleDown->Scale(wt_WToTauNu_M1000);
  //
  TH1D* mT_Stage1_WToTauNu_M1000_pileupUncertUp  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_WToTauNu_M1000_pileupUncertUp->Scale(wt_WToTauNu_M1000);

  TH1D* mT_Stage1_WToTauNu_M1000_pileupUncertDown  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_WToTauNu_M1000_pileupUncertDown->Scale(wt_WToTauNu_M1000);
  //
  TH1D* mT_Stage1_WToTauNu_M1000_kFactorUp  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_WToTauNu_M1000_kFactorUp->Scale(wt_WToTauNu_M1000);

  TH1D* mT_Stage1_WToTauNu_M1000_kFactorDown  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_WToTauNu_M1000_kFactorDown->Scale(wt_WToTauNu_M1000);
  //
  TH1D* mT_Stage1_WToTauNu_M1000_TauIDSFUp  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_WToTauNu_M1000_TauIDSFUp->Scale(wt_WToTauNu_M1000);

  TH1D* mT_Stage1_WToTauNu_M1000_TauIDSFDown  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_WToTauNu_M1000_TauIDSFDown->Scale(wt_WToTauNu_M1000);

  TH1D* mT_Stage1_WToTauNu_M1000_TauIDSFflatUp  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_WToTauNu_M1000_TauIDSFflatUp->Scale(wt_WToTauNu_M1000);

  TH1D* mT_Stage1_WToTauNu_M1000_TauIDSFflatDown  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_WToTauNu_M1000_TauIDSFflatDown->Scale(wt_WToTauNu_M1000);
  //
  TH1D* mT_Stage1_WToTauNu_M1000_TauELESFUp  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_WToTauNu_M1000_TauELESFUp->Scale(wt_WToTauNu_M1000);

  TH1D* mT_Stage1_WToTauNu_M1000_TauELESFDown  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_WToTauNu_M1000_TauELESFDown->Scale(wt_WToTauNu_M1000);
  //
  TH1D* mT_Stage1_WToTauNu_M1000_trigSFUp  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_WToTauNu_M1000_trigSFUp->Scale(wt_WToTauNu_M1000);

  TH1D* mT_Stage1_WToTauNu_M1000_trigSFDown  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_WToTauNu_M1000_trigSFDown->Scale(wt_WToTauNu_M1000);
  //
  /*
  TH1D* mT_Stage1_WToTauNu_M1000_pdfUncertUp  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_WToTauNu_M1000_pdfUncertUp->Scale(wt_WToTauNu_M1000);

  TH1D* mT_Stage1_WToTauNu_M1000_pdfUncertDown  = (TH1D*)file_WToTauNu_M1000->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_WToTauNu_M1000_pdfUncertDown->Scale(wt_WToTauNu_M1000);
  */ //

  //file_WToTauNu_M2000
  TH1D* h1_evt_WToTauNu_M2000 = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M2000 = h1_evt_WToTauNu_M2000->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M2000 = (xs_WToTauNu_M2000*lumi)/evt_WToTauNu_M2000 ;
  TH1D* mT_Stage1_WToTauNu_M2000  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WToTauNu_M2000->Scale(wt_WToTauNu_M2000);
  std::cout << "WToTauNu_M2000 weighted nevt=" << mT_Stage1_WToTauNu_M2000->Integral() << std::endl;
  totalMC += mT_Stage1_WToTauNu_M2000->Integral();
  //
  TH1D* mT_Stage1_WToTauNu_M2000_JetEnUp  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_WToTauNu_M2000_JetEnUp->Scale(wt_WToTauNu_M2000);

  TH1D* mT_Stage1_WToTauNu_M2000_JetEnDown  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_WToTauNu_M2000_JetEnDown->Scale(wt_WToTauNu_M2000);
  //
  TH1D* mT_Stage1_WToTauNu_M2000_JetResUp  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_WToTauNu_M2000_JetResUp->Scale(wt_WToTauNu_M2000);

  TH1D* mT_Stage1_WToTauNu_M2000_JetResDown  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_WToTauNu_M2000_JetResDown->Scale(wt_WToTauNu_M2000);
  //
  TH1D* mT_Stage1_WToTauNu_M2000_MuonEnUp  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_WToTauNu_M2000_MuonEnUp->Scale(wt_WToTauNu_M2000);

  TH1D* mT_Stage1_WToTauNu_M2000_MuonEnDown  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_WToTauNu_M2000_MuonEnDown->Scale(wt_WToTauNu_M2000);
  //
  TH1D* mT_Stage1_WToTauNu_M2000_ElectronEnUp  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_WToTauNu_M2000_ElectronEnUp->Scale(wt_WToTauNu_M2000);

  TH1D* mT_Stage1_WToTauNu_M2000_ElectronEnDown  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_WToTauNu_M2000_ElectronEnDown->Scale(wt_WToTauNu_M2000);
  //
  TH1D* mT_Stage1_WToTauNu_M2000_TauEnUp  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_WToTauNu_M2000_TauEnUp->Scale(wt_WToTauNu_M2000);

  TH1D* mT_Stage1_WToTauNu_M2000_TauEnDown  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_WToTauNu_M2000_TauEnDown->Scale(wt_WToTauNu_M2000);
  //
  TH1D* mT_Stage1_WToTauNu_M2000_PhotonEnUp  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_WToTauNu_M2000_PhotonEnUp->Scale(wt_WToTauNu_M2000);

  TH1D* mT_Stage1_WToTauNu_M2000_PhotonEnDown  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_WToTauNu_M2000_PhotonEnDown->Scale(wt_WToTauNu_M2000);
  //
  TH1D* mT_Stage1_WToTauNu_M2000_UnclusteredEnUp  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_WToTauNu_M2000_UnclusteredEnUp->Scale(wt_WToTauNu_M2000);

  TH1D* mT_Stage1_WToTauNu_M2000_UnclusteredEnDown  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_WToTauNu_M2000_UnclusteredEnDown->Scale(wt_WToTauNu_M2000);
  //
  TH1D* mT_Stage1_WToTauNu_M2000_TauScaleUp  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_WToTauNu_M2000_TauScaleUp->Scale(wt_WToTauNu_M2000);

  TH1D* mT_Stage1_WToTauNu_M2000_TauScaleDown  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_WToTauNu_M2000_TauScaleDown->Scale(wt_WToTauNu_M2000);
  //
  TH1D* mT_Stage1_WToTauNu_M2000_pileupUncertUp  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_WToTauNu_M2000_pileupUncertUp->Scale(wt_WToTauNu_M2000);

  TH1D* mT_Stage1_WToTauNu_M2000_pileupUncertDown  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_WToTauNu_M2000_pileupUncertDown->Scale(wt_WToTauNu_M2000);
  //
  TH1D* mT_Stage1_WToTauNu_M2000_kFactorUp  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_WToTauNu_M2000_kFactorUp->Scale(wt_WToTauNu_M2000);

  TH1D* mT_Stage1_WToTauNu_M2000_kFactorDown  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_WToTauNu_M2000_kFactorDown->Scale(wt_WToTauNu_M2000);
  //
  TH1D* mT_Stage1_WToTauNu_M2000_TauIDSFUp  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_WToTauNu_M2000_TauIDSFUp->Scale(wt_WToTauNu_M2000);

  TH1D* mT_Stage1_WToTauNu_M2000_TauIDSFDown  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_WToTauNu_M2000_TauIDSFDown->Scale(wt_WToTauNu_M2000);

  TH1D* mT_Stage1_WToTauNu_M2000_TauIDSFflatUp  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_WToTauNu_M2000_TauIDSFflatUp->Scale(wt_WToTauNu_M2000);

  TH1D* mT_Stage1_WToTauNu_M2000_TauIDSFflatDown  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_WToTauNu_M2000_TauIDSFflatDown->Scale(wt_WToTauNu_M2000);
  //
  TH1D* mT_Stage1_WToTauNu_M2000_TauELESFUp  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_WToTauNu_M2000_TauELESFUp->Scale(wt_WToTauNu_M2000);

  TH1D* mT_Stage1_WToTauNu_M2000_TauELESFDown  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_WToTauNu_M2000_TauELESFDown->Scale(wt_WToTauNu_M2000);
  //
  TH1D* mT_Stage1_WToTauNu_M2000_trigSFUp  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_WToTauNu_M2000_trigSFUp->Scale(wt_WToTauNu_M2000);

  TH1D* mT_Stage1_WToTauNu_M2000_trigSFDown  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_WToTauNu_M2000_trigSFDown->Scale(wt_WToTauNu_M2000);
  //
  /*
  TH1D* mT_Stage1_WToTauNu_M2000_pdfUncertUp  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_WToTauNu_M2000_pdfUncertUp->Scale(wt_WToTauNu_M2000);

  TH1D* mT_Stage1_WToTauNu_M2000_pdfUncertDown  = (TH1D*)file_WToTauNu_M2000->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_WToTauNu_M2000_pdfUncertDown->Scale(wt_WToTauNu_M2000);
  */ //

  //file_WToTauNu_M3000
  TH1D* h1_evt_WToTauNu_M3000 = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M3000 = h1_evt_WToTauNu_M3000->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M3000 = (xs_WToTauNu_M3000*lumi)/evt_WToTauNu_M3000 ;
  TH1D* mT_Stage1_WToTauNu_M3000  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WToTauNu_M3000->Scale(wt_WToTauNu_M3000);
  std::cout << "WToTauNu_M3000 weighted nevt=" << mT_Stage1_WToTauNu_M3000->Integral() << std::endl;
  totalMC += mT_Stage1_WToTauNu_M3000->Integral();
  //
  TH1D* mT_Stage1_WToTauNu_M3000_JetEnUp  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_WToTauNu_M3000_JetEnUp->Scale(wt_WToTauNu_M3000);

  TH1D* mT_Stage1_WToTauNu_M3000_JetEnDown  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_WToTauNu_M3000_JetEnDown->Scale(wt_WToTauNu_M3000);
  //
  TH1D* mT_Stage1_WToTauNu_M3000_JetResUp  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_WToTauNu_M3000_JetResUp->Scale(wt_WToTauNu_M3000);

  TH1D* mT_Stage1_WToTauNu_M3000_JetResDown  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_WToTauNu_M3000_JetResDown->Scale(wt_WToTauNu_M3000);
  //
  TH1D* mT_Stage1_WToTauNu_M3000_MuonEnUp  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_WToTauNu_M3000_MuonEnUp->Scale(wt_WToTauNu_M3000);

  TH1D* mT_Stage1_WToTauNu_M3000_MuonEnDown  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_WToTauNu_M3000_MuonEnDown->Scale(wt_WToTauNu_M3000);
  //
  TH1D* mT_Stage1_WToTauNu_M3000_ElectronEnUp  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_WToTauNu_M3000_ElectronEnUp->Scale(wt_WToTauNu_M3000);

  TH1D* mT_Stage1_WToTauNu_M3000_ElectronEnDown  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_WToTauNu_M3000_ElectronEnDown->Scale(wt_WToTauNu_M3000);
  //
  TH1D* mT_Stage1_WToTauNu_M3000_TauEnUp  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_WToTauNu_M3000_TauEnUp->Scale(wt_WToTauNu_M3000);

  TH1D* mT_Stage1_WToTauNu_M3000_TauEnDown  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_WToTauNu_M3000_TauEnDown->Scale(wt_WToTauNu_M3000);
  //
  TH1D* mT_Stage1_WToTauNu_M3000_PhotonEnUp  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_WToTauNu_M3000_PhotonEnUp->Scale(wt_WToTauNu_M3000);

  TH1D* mT_Stage1_WToTauNu_M3000_PhotonEnDown  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_WToTauNu_M3000_PhotonEnDown->Scale(wt_WToTauNu_M3000);
  //
  TH1D* mT_Stage1_WToTauNu_M3000_UnclusteredEnUp  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_WToTauNu_M3000_UnclusteredEnUp->Scale(wt_WToTauNu_M3000);

  TH1D* mT_Stage1_WToTauNu_M3000_UnclusteredEnDown  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_WToTauNu_M3000_UnclusteredEnDown->Scale(wt_WToTauNu_M3000);
  //
  TH1D* mT_Stage1_WToTauNu_M3000_TauScaleUp  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_WToTauNu_M3000_TauScaleUp->Scale(wt_WToTauNu_M3000);

  TH1D* mT_Stage1_WToTauNu_M3000_TauScaleDown  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_WToTauNu_M3000_TauScaleDown->Scale(wt_WToTauNu_M3000);
  //
  TH1D* mT_Stage1_WToTauNu_M3000_pileupUncertUp  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_WToTauNu_M3000_pileupUncertUp->Scale(wt_WToTauNu_M3000);

  TH1D* mT_Stage1_WToTauNu_M3000_pileupUncertDown  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_WToTauNu_M3000_pileupUncertDown->Scale(wt_WToTauNu_M3000);
  //
  TH1D* mT_Stage1_WToTauNu_M3000_kFactorUp  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_WToTauNu_M3000_kFactorUp->Scale(wt_WToTauNu_M3000);

  TH1D* mT_Stage1_WToTauNu_M3000_kFactorDown  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_WToTauNu_M3000_kFactorDown->Scale(wt_WToTauNu_M3000);
  //
  TH1D* mT_Stage1_WToTauNu_M3000_TauIDSFUp  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_WToTauNu_M3000_TauIDSFUp->Scale(wt_WToTauNu_M3000);

  TH1D* mT_Stage1_WToTauNu_M3000_TauIDSFDown  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_WToTauNu_M3000_TauIDSFDown->Scale(wt_WToTauNu_M3000);

  TH1D* mT_Stage1_WToTauNu_M3000_TauIDSFflatUp  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_WToTauNu_M3000_TauIDSFflatUp->Scale(wt_WToTauNu_M3000);

  TH1D* mT_Stage1_WToTauNu_M3000_TauIDSFflatDown  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_WToTauNu_M3000_TauIDSFflatDown->Scale(wt_WToTauNu_M3000);
  //
  TH1D* mT_Stage1_WToTauNu_M3000_TauELESFUp  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_WToTauNu_M3000_TauELESFUp->Scale(wt_WToTauNu_M3000);

  TH1D* mT_Stage1_WToTauNu_M3000_TauELESFDown  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_WToTauNu_M3000_TauELESFDown->Scale(wt_WToTauNu_M3000);
  //
  TH1D* mT_Stage1_WToTauNu_M3000_trigSFUp  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_WToTauNu_M3000_trigSFUp->Scale(wt_WToTauNu_M3000);

  TH1D* mT_Stage1_WToTauNu_M3000_trigSFDown  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_WToTauNu_M3000_trigSFDown->Scale(wt_WToTauNu_M3000);
  //
  /*
  TH1D* mT_Stage1_WToTauNu_M3000_pdfUncertUp  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_WToTauNu_M3000_pdfUncertUp->Scale(wt_WToTauNu_M3000);

  TH1D* mT_Stage1_WToTauNu_M3000_pdfUncertDown  = (TH1D*)file_WToTauNu_M3000->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_WToTauNu_M3000_pdfUncertDown->Scale(wt_WToTauNu_M3000);
  */ //

  //file_WToTauNu_M4000
  TH1D* h1_evt_WToTauNu_M4000 = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M4000 = h1_evt_WToTauNu_M4000->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M4000 = (xs_WToTauNu_M4000*lumi)/evt_WToTauNu_M4000 ;
  TH1D* mT_Stage1_WToTauNu_M4000  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WToTauNu_M4000->Scale(wt_WToTauNu_M4000);
  std::cout << "WToTauNu_M4000 weighted nevt=" << mT_Stage1_WToTauNu_M4000->Integral() << std::endl;
  totalMC += mT_Stage1_WToTauNu_M4000->Integral();
  //
  TH1D* mT_Stage1_WToTauNu_M4000_JetEnUp  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_WToTauNu_M4000_JetEnUp->Scale(wt_WToTauNu_M4000);

  TH1D* mT_Stage1_WToTauNu_M4000_JetEnDown  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_WToTauNu_M4000_JetEnDown->Scale(wt_WToTauNu_M4000);
  //
  TH1D* mT_Stage1_WToTauNu_M4000_JetResUp  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_WToTauNu_M4000_JetResUp->Scale(wt_WToTauNu_M4000);

  TH1D* mT_Stage1_WToTauNu_M4000_JetResDown  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_WToTauNu_M4000_JetResDown->Scale(wt_WToTauNu_M4000);
  //
  TH1D* mT_Stage1_WToTauNu_M4000_MuonEnUp  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_WToTauNu_M4000_MuonEnUp->Scale(wt_WToTauNu_M4000);

  TH1D* mT_Stage1_WToTauNu_M4000_MuonEnDown  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_WToTauNu_M4000_MuonEnDown->Scale(wt_WToTauNu_M4000);
  //
  TH1D* mT_Stage1_WToTauNu_M4000_ElectronEnUp  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_WToTauNu_M4000_ElectronEnUp->Scale(wt_WToTauNu_M4000);

  TH1D* mT_Stage1_WToTauNu_M4000_ElectronEnDown  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_WToTauNu_M4000_ElectronEnDown->Scale(wt_WToTauNu_M4000);
  //
  TH1D* mT_Stage1_WToTauNu_M4000_TauEnUp  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_WToTauNu_M4000_TauEnUp->Scale(wt_WToTauNu_M4000);

  TH1D* mT_Stage1_WToTauNu_M4000_TauEnDown  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_WToTauNu_M4000_TauEnDown->Scale(wt_WToTauNu_M4000);
  //
  TH1D* mT_Stage1_WToTauNu_M4000_PhotonEnUp  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_WToTauNu_M4000_PhotonEnUp->Scale(wt_WToTauNu_M4000);

  TH1D* mT_Stage1_WToTauNu_M4000_PhotonEnDown  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_WToTauNu_M4000_PhotonEnDown->Scale(wt_WToTauNu_M4000);
  //
  TH1D* mT_Stage1_WToTauNu_M4000_UnclusteredEnUp  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_WToTauNu_M4000_UnclusteredEnUp->Scale(wt_WToTauNu_M4000);

  TH1D* mT_Stage1_WToTauNu_M4000_UnclusteredEnDown  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_WToTauNu_M4000_UnclusteredEnDown->Scale(wt_WToTauNu_M4000);
  //
  TH1D* mT_Stage1_WToTauNu_M4000_TauScaleUp  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_WToTauNu_M4000_TauScaleUp->Scale(wt_WToTauNu_M4000);

  TH1D* mT_Stage1_WToTauNu_M4000_TauScaleDown  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_WToTauNu_M4000_TauScaleDown->Scale(wt_WToTauNu_M4000);
  //
  TH1D* mT_Stage1_WToTauNu_M4000_pileupUncertUp  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_WToTauNu_M4000_pileupUncertUp->Scale(wt_WToTauNu_M4000);

  TH1D* mT_Stage1_WToTauNu_M4000_pileupUncertDown  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_WToTauNu_M4000_pileupUncertDown->Scale(wt_WToTauNu_M4000);
  //
  TH1D* mT_Stage1_WToTauNu_M4000_kFactorUp  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_WToTauNu_M4000_kFactorUp->Scale(wt_WToTauNu_M4000);

  TH1D* mT_Stage1_WToTauNu_M4000_kFactorDown  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_WToTauNu_M4000_kFactorDown->Scale(wt_WToTauNu_M4000);
  //
  TH1D* mT_Stage1_WToTauNu_M4000_TauIDSFUp  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_WToTauNu_M4000_TauIDSFUp->Scale(wt_WToTauNu_M4000);

  TH1D* mT_Stage1_WToTauNu_M4000_TauIDSFDown  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_WToTauNu_M4000_TauIDSFDown->Scale(wt_WToTauNu_M4000);

  TH1D* mT_Stage1_WToTauNu_M4000_TauIDSFflatUp  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_WToTauNu_M4000_TauIDSFflatUp->Scale(wt_WToTauNu_M4000);

  TH1D* mT_Stage1_WToTauNu_M4000_TauIDSFflatDown  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_WToTauNu_M4000_TauIDSFflatDown->Scale(wt_WToTauNu_M4000);
  //
  TH1D* mT_Stage1_WToTauNu_M4000_TauELESFUp  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_WToTauNu_M4000_TauELESFUp->Scale(wt_WToTauNu_M4000);

  TH1D* mT_Stage1_WToTauNu_M4000_TauELESFDown  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_WToTauNu_M4000_TauELESFDown->Scale(wt_WToTauNu_M4000);
  //
  TH1D* mT_Stage1_WToTauNu_M4000_trigSFUp  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_WToTauNu_M4000_trigSFUp->Scale(wt_WToTauNu_M4000);

  TH1D* mT_Stage1_WToTauNu_M4000_trigSFDown  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_WToTauNu_M4000_trigSFDown->Scale(wt_WToTauNu_M4000);
  //
  /*
  TH1D* mT_Stage1_WToTauNu_M4000_pdfUncertUp  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_WToTauNu_M4000_pdfUncertUp->Scale(wt_WToTauNu_M4000);

  TH1D* mT_Stage1_WToTauNu_M4000_pdfUncertDown  = (TH1D*)file_WToTauNu_M4000->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_WToTauNu_M4000_pdfUncertDown->Scale(wt_WToTauNu_M4000);
  */ //

  //file_WToTauNu_M5000
  TH1D* h1_evt_WToTauNu_M5000 = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M5000 = h1_evt_WToTauNu_M5000->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M5000 = (xs_WToTauNu_M5000*lumi)/evt_WToTauNu_M5000 ;
  TH1D* mT_Stage1_WToTauNu_M5000  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WToTauNu_M5000->Scale(wt_WToTauNu_M5000);
  std::cout << "WToTauNu_M5000 weighted nevt=" << mT_Stage1_WToTauNu_M5000->Integral() << std::endl;
  totalMC += mT_Stage1_WToTauNu_M5000->Integral();
  //
  TH1D* mT_Stage1_WToTauNu_M5000_JetEnUp  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_WToTauNu_M5000_JetEnUp->Scale(wt_WToTauNu_M5000);

  TH1D* mT_Stage1_WToTauNu_M5000_JetEnDown  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_WToTauNu_M5000_JetEnDown->Scale(wt_WToTauNu_M5000);
  //
  TH1D* mT_Stage1_WToTauNu_M5000_JetResUp  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_WToTauNu_M5000_JetResUp->Scale(wt_WToTauNu_M5000);

  TH1D* mT_Stage1_WToTauNu_M5000_JetResDown  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_WToTauNu_M5000_JetResDown->Scale(wt_WToTauNu_M5000);
  //
  TH1D* mT_Stage1_WToTauNu_M5000_MuonEnUp  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_WToTauNu_M5000_MuonEnUp->Scale(wt_WToTauNu_M5000);

  TH1D* mT_Stage1_WToTauNu_M5000_MuonEnDown  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_WToTauNu_M5000_MuonEnDown->Scale(wt_WToTauNu_M5000);
  //
  TH1D* mT_Stage1_WToTauNu_M5000_ElectronEnUp  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_WToTauNu_M5000_ElectronEnUp->Scale(wt_WToTauNu_M5000);

  TH1D* mT_Stage1_WToTauNu_M5000_ElectronEnDown  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_WToTauNu_M5000_ElectronEnDown->Scale(wt_WToTauNu_M5000);
  //
  TH1D* mT_Stage1_WToTauNu_M5000_TauEnUp  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_WToTauNu_M5000_TauEnUp->Scale(wt_WToTauNu_M5000);

  TH1D* mT_Stage1_WToTauNu_M5000_TauEnDown  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_WToTauNu_M5000_TauEnDown->Scale(wt_WToTauNu_M5000);
  //
  TH1D* mT_Stage1_WToTauNu_M5000_PhotonEnUp  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_WToTauNu_M5000_PhotonEnUp->Scale(wt_WToTauNu_M5000);

  TH1D* mT_Stage1_WToTauNu_M5000_PhotonEnDown  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_WToTauNu_M5000_PhotonEnDown->Scale(wt_WToTauNu_M5000);
  //
  TH1D* mT_Stage1_WToTauNu_M5000_UnclusteredEnUp  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_WToTauNu_M5000_UnclusteredEnUp->Scale(wt_WToTauNu_M5000);

  TH1D* mT_Stage1_WToTauNu_M5000_UnclusteredEnDown  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_WToTauNu_M5000_UnclusteredEnDown->Scale(wt_WToTauNu_M5000);
  //
  TH1D* mT_Stage1_WToTauNu_M5000_TauScaleUp  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_WToTauNu_M5000_TauScaleUp->Scale(wt_WToTauNu_M5000);

  TH1D* mT_Stage1_WToTauNu_M5000_TauScaleDown  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_WToTauNu_M5000_TauScaleDown->Scale(wt_WToTauNu_M5000);
  //
  TH1D* mT_Stage1_WToTauNu_M5000_pileupUncertUp  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_WToTauNu_M5000_pileupUncertUp->Scale(wt_WToTauNu_M5000);

  TH1D* mT_Stage1_WToTauNu_M5000_pileupUncertDown  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_WToTauNu_M5000_pileupUncertDown->Scale(wt_WToTauNu_M5000);
  //
  TH1D* mT_Stage1_WToTauNu_M5000_kFactorUp  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_WToTauNu_M5000_kFactorUp->Scale(wt_WToTauNu_M5000);

  TH1D* mT_Stage1_WToTauNu_M5000_kFactorDown  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_WToTauNu_M5000_kFactorDown->Scale(wt_WToTauNu_M5000);
  //
  TH1D* mT_Stage1_WToTauNu_M5000_TauIDSFUp  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_WToTauNu_M5000_TauIDSFUp->Scale(wt_WToTauNu_M5000);

  TH1D* mT_Stage1_WToTauNu_M5000_TauIDSFDown  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_WToTauNu_M5000_TauIDSFDown->Scale(wt_WToTauNu_M5000);

  TH1D* mT_Stage1_WToTauNu_M5000_TauIDSFflatUp  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_WToTauNu_M5000_TauIDSFflatUp->Scale(wt_WToTauNu_M5000);

  TH1D* mT_Stage1_WToTauNu_M5000_TauIDSFflatDown  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_WToTauNu_M5000_TauIDSFflatDown->Scale(wt_WToTauNu_M5000);
  //
  TH1D* mT_Stage1_WToTauNu_M5000_TauELESFUp  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_WToTauNu_M5000_TauELESFUp->Scale(wt_WToTauNu_M5000);

  TH1D* mT_Stage1_WToTauNu_M5000_TauELESFDown  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_WToTauNu_M5000_TauELESFDown->Scale(wt_WToTauNu_M5000);
  //
  TH1D* mT_Stage1_WToTauNu_M5000_trigSFUp  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_WToTauNu_M5000_trigSFUp->Scale(wt_WToTauNu_M5000);

  TH1D* mT_Stage1_WToTauNu_M5000_trigSFDown  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_WToTauNu_M5000_trigSFDown->Scale(wt_WToTauNu_M5000);
  //
  /*
  TH1D* mT_Stage1_WToTauNu_M5000_pdfUncertUp  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_WToTauNu_M5000_pdfUncertUp->Scale(wt_WToTauNu_M5000);

  TH1D* mT_Stage1_WToTauNu_M5000_pdfUncertDown  = (TH1D*)file_WToTauNu_M5000->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_WToTauNu_M5000_pdfUncertDown->Scale(wt_WToTauNu_M5000);
  */ //

  //file_WToTauNu_M6000
  TH1D* h1_evt_WToTauNu_M6000 = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/eventCount");
  unsigned long long evt_WToTauNu_M6000 = h1_evt_WToTauNu_M6000->GetEntries(); //Integral();                                                             
  double wt_WToTauNu_M6000 = (xs_WToTauNu_M6000*lumi)/evt_WToTauNu_M6000 ;
  TH1D* mT_Stage1_WToTauNu_M6000  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WToTauNu_M6000->Scale(wt_WToTauNu_M6000);
  std::cout << "WToTauNu_M6000 weighted nevt=" << mT_Stage1_WToTauNu_M6000->Integral() << std::endl;
  totalMC += mT_Stage1_WToTauNu_M6000->Integral();
  //
  TH1D* mT_Stage1_WToTauNu_M6000_JetEnUp  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_WToTauNu_M6000_JetEnUp->Scale(wt_WToTauNu_M6000);

  TH1D* mT_Stage1_WToTauNu_M6000_JetEnDown  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_WToTauNu_M6000_JetEnDown->Scale(wt_WToTauNu_M6000);
  //
  TH1D* mT_Stage1_WToTauNu_M6000_JetResUp  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_WToTauNu_M6000_JetResUp->Scale(wt_WToTauNu_M6000);

  TH1D* mT_Stage1_WToTauNu_M6000_JetResDown  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_WToTauNu_M6000_JetResDown->Scale(wt_WToTauNu_M6000);
  //
  TH1D* mT_Stage1_WToTauNu_M6000_MuonEnUp  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_WToTauNu_M6000_MuonEnUp->Scale(wt_WToTauNu_M6000);

  TH1D* mT_Stage1_WToTauNu_M6000_MuonEnDown  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_WToTauNu_M6000_MuonEnDown->Scale(wt_WToTauNu_M6000);
  //
  TH1D* mT_Stage1_WToTauNu_M6000_ElectronEnUp  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_WToTauNu_M6000_ElectronEnUp->Scale(wt_WToTauNu_M6000);

  TH1D* mT_Stage1_WToTauNu_M6000_ElectronEnDown  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_WToTauNu_M6000_ElectronEnDown->Scale(wt_WToTauNu_M6000);
  //
  TH1D* mT_Stage1_WToTauNu_M6000_TauEnUp  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_WToTauNu_M6000_TauEnUp->Scale(wt_WToTauNu_M6000);
  
  TH1D* mT_Stage1_WToTauNu_M6000_TauEnDown  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_WToTauNu_M6000_TauEnDown->Scale(wt_WToTauNu_M6000);
  //
  TH1D* mT_Stage1_WToTauNu_M6000_PhotonEnUp  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_WToTauNu_M6000_PhotonEnUp->Scale(wt_WToTauNu_M6000);

  TH1D* mT_Stage1_WToTauNu_M6000_PhotonEnDown  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_WToTauNu_M6000_PhotonEnDown->Scale(wt_WToTauNu_M6000);
  //
  TH1D* mT_Stage1_WToTauNu_M6000_UnclusteredEnUp  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_WToTauNu_M6000_UnclusteredEnUp->Scale(wt_WToTauNu_M6000);

  TH1D* mT_Stage1_WToTauNu_M6000_UnclusteredEnDown  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_WToTauNu_M6000_UnclusteredEnDown->Scale(wt_WToTauNu_M6000);
  //
  TH1D* mT_Stage1_WToTauNu_M6000_TauScaleUp  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_WToTauNu_M6000_TauScaleUp->Scale(wt_WToTauNu_M6000);

  TH1D* mT_Stage1_WToTauNu_M6000_TauScaleDown  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_WToTauNu_M6000_TauScaleDown->Scale(wt_WToTauNu_M6000);
  //
  TH1D* mT_Stage1_WToTauNu_M6000_pileupUncertUp  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_WToTauNu_M6000_pileupUncertUp->Scale(wt_WToTauNu_M6000);

  TH1D* mT_Stage1_WToTauNu_M6000_pileupUncertDown  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_WToTauNu_M6000_pileupUncertDown->Scale(wt_WToTauNu_M6000);
  //
  TH1D* mT_Stage1_WToTauNu_M6000_kFactorUp  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_WToTauNu_M6000_kFactorUp->Scale(wt_WToTauNu_M6000);

  TH1D* mT_Stage1_WToTauNu_M6000_kFactorDown  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_WToTauNu_M6000_kFactorDown->Scale(wt_WToTauNu_M6000);

  //
  TH1D* mT_Stage1_WToTauNu_M6000_TauIDSFUp  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_WToTauNu_M6000_TauIDSFUp->Scale(wt_WToTauNu_M6000);

  TH1D* mT_Stage1_WToTauNu_M6000_TauIDSFDown  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_WToTauNu_M6000_TauIDSFDown->Scale(wt_WToTauNu_M6000);

  TH1D* mT_Stage1_WToTauNu_M6000_TauIDSFflatUp  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_WToTauNu_M6000_TauIDSFflatUp->Scale(wt_WToTauNu_M6000);

  TH1D* mT_Stage1_WToTauNu_M6000_TauIDSFflatDown  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_WToTauNu_M6000_TauIDSFflatDown->Scale(wt_WToTauNu_M6000);
  //
  TH1D* mT_Stage1_WToTauNu_M6000_TauELESFUp  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_WToTauNu_M6000_TauELESFUp->Scale(wt_WToTauNu_M6000);

  TH1D* mT_Stage1_WToTauNu_M6000_TauELESFDown  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_WToTauNu_M6000_TauELESFDown->Scale(wt_WToTauNu_M6000);
  //
  TH1D* mT_Stage1_WToTauNu_M6000_trigSFUp  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_WToTauNu_M6000_trigSFUp->Scale(wt_WToTauNu_M6000);

  TH1D* mT_Stage1_WToTauNu_M6000_trigSFDown  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_WToTauNu_M6000_trigSFDown->Scale(wt_WToTauNu_M6000);
  //
  /*
  TH1D* mT_Stage1_WToTauNu_M6000_pdfUncertUp  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_WToTauNu_M6000_pdfUncertUp->Scale(wt_WToTauNu_M6000);

  TH1D* mT_Stage1_WToTauNu_M6000_pdfUncertDown  = (TH1D*)file_WToTauNu_M6000->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_WToTauNu_M6000_pdfUncertDown->Scale(wt_WToTauNu_M6000);
  */  //

  //file_WJetsToLNu
  TH1D* h1_evt_WJetsToLNu = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/eventCount");
  unsigned long long evt_WJetsToLNu = h1_evt_WJetsToLNu->GetEntries(); //Integral();                                                             
  double wt_WJetsToLNu = (xs_WJetsToLNu*lumi)/evt_WJetsToLNu ;
  TH1D* mT_Stage1_WJetsToLNu  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WJetsToLNu->Scale(wt_WJetsToLNu);
  std::cout << "WJetsToLNu weighted nevt=" << mT_Stage1_WJetsToLNu->Integral() << std::endl;
  totalMC += mT_Stage1_WJetsToLNu->Integral();
  //
  TH1D* mT_Stage1_WJetsToLNu_JetEnUp  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_WJetsToLNu_JetEnUp->Scale(wt_WJetsToLNu);

  TH1D* mT_Stage1_WJetsToLNu_JetEnDown  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_WJetsToLNu_JetEnDown->Scale(wt_WJetsToLNu);
  //
  TH1D* mT_Stage1_WJetsToLNu_JetResUp  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_WJetsToLNu_JetResUp->Scale(wt_WJetsToLNu);

  TH1D* mT_Stage1_WJetsToLNu_JetResDown  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_WJetsToLNu_JetResDown->Scale(wt_WJetsToLNu);
  //
  TH1D* mT_Stage1_WJetsToLNu_MuonEnUp  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_WJetsToLNu_MuonEnUp->Scale(wt_WJetsToLNu);

  TH1D* mT_Stage1_WJetsToLNu_MuonEnDown  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_WJetsToLNu_MuonEnDown->Scale(wt_WJetsToLNu);
  //
  TH1D* mT_Stage1_WJetsToLNu_ElectronEnUp  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_WJetsToLNu_ElectronEnUp->Scale(wt_WJetsToLNu);

  TH1D* mT_Stage1_WJetsToLNu_ElectronEnDown  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_WJetsToLNu_ElectronEnDown->Scale(wt_WJetsToLNu);
  //
  TH1D* mT_Stage1_WJetsToLNu_TauEnUp  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_WJetsToLNu_TauEnUp->Scale(wt_WJetsToLNu);

  TH1D* mT_Stage1_WJetsToLNu_TauEnDown  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_WJetsToLNu_TauEnDown->Scale(wt_WJetsToLNu);
  //
  TH1D* mT_Stage1_WJetsToLNu_PhotonEnUp  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_WJetsToLNu_PhotonEnUp->Scale(wt_WJetsToLNu);

  TH1D* mT_Stage1_WJetsToLNu_PhotonEnDown  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_WJetsToLNu_PhotonEnDown->Scale(wt_WJetsToLNu);
  //
  TH1D* mT_Stage1_WJetsToLNu_UnclusteredEnUp  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_WJetsToLNu_UnclusteredEnUp->Scale(wt_WJetsToLNu);

  TH1D* mT_Stage1_WJetsToLNu_UnclusteredEnDown  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_WJetsToLNu_UnclusteredEnDown->Scale(wt_WJetsToLNu);
  //
  TH1D* mT_Stage1_WJetsToLNu_TauScaleUp  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_WJetsToLNu_TauScaleUp->Scale(wt_WJetsToLNu);

  TH1D* mT_Stage1_WJetsToLNu_TauScaleDown  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_WJetsToLNu_TauScaleDown->Scale(wt_WJetsToLNu);
  //
  TH1D* mT_Stage1_WJetsToLNu_pileupUncertUp  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_WJetsToLNu_pileupUncertUp->Scale(wt_WJetsToLNu);

  TH1D* mT_Stage1_WJetsToLNu_pileupUncertDown  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_WJetsToLNu_pileupUncertDown->Scale(wt_WJetsToLNu);
  //
  TH1D* mT_Stage1_WJetsToLNu_kFactorUp  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_WJetsToLNu_kFactorUp->Scale(wt_WJetsToLNu);

  TH1D* mT_Stage1_WJetsToLNu_kFactorDown  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_WJetsToLNu_kFactorDown->Scale(wt_WJetsToLNu);
  //
  TH1D* mT_Stage1_WJetsToLNu_TauIDSFUp  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_WJetsToLNu_TauIDSFUp->Scale(wt_WJetsToLNu);

  TH1D* mT_Stage1_WJetsToLNu_TauIDSFDown  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_WJetsToLNu_TauIDSFDown->Scale(wt_WJetsToLNu);

  TH1D* mT_Stage1_WJetsToLNu_TauIDSFflatUp  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_WJetsToLNu_TauIDSFflatUp->Scale(wt_WJetsToLNu);

  TH1D* mT_Stage1_WJetsToLNu_TauIDSFflatDown  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_WJetsToLNu_TauIDSFflatDown->Scale(wt_WJetsToLNu);
  //
  TH1D* mT_Stage1_WJetsToLNu_TauELESFUp  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_WJetsToLNu_TauELESFUp->Scale(wt_WJetsToLNu);

  TH1D* mT_Stage1_WJetsToLNu_TauELESFDown  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_WJetsToLNu_TauELESFDown->Scale(wt_WJetsToLNu);
  //
  TH1D* mT_Stage1_WJetsToLNu_trigSFUp  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_WJetsToLNu_trigSFUp->Scale(wt_WJetsToLNu);

  TH1D* mT_Stage1_WJetsToLNu_trigSFDown  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_WJetsToLNu_trigSFDown->Scale(wt_WJetsToLNu);
  //
  /*
  TH1D* mT_Stage1_WJetsToLNu_pdfUncertUp  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_WJetsToLNu_pdfUncertUp->Scale(wt_WJetsToLNu);

  TH1D* mT_Stage1_WJetsToLNu_pdfUncertDown  = (TH1D*)file_WJetsToLNu->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_WJetsToLNu_pdfUncertDown->Scale(wt_WJetsToLNu);
  */ //


  TH1D* total_WJets = (TH1D*)mT_Stage1_WJetsToLNu_HT100To200->Clone();
  total_WJets->Add(mT_Stage1_WJetsToLNu_HT200To400);
  total_WJets->Add(mT_Stage1_WJetsToLNu_HT400To600);
  total_WJets->Add(mT_Stage1_WJetsToLNu_HT600To800);
  total_WJets->Add(mT_Stage1_WJetsToLNu_HT800To1200);
  total_WJets->Add(mT_Stage1_WJetsToLNu_HT1200To2500);
  total_WJets->Add(mT_Stage1_WJetsToLNu_HT2500ToInf);
  total_WJets->Add(mT_Stage1_WToTauNu_M100);
  total_WJets->Add(mT_Stage1_WToTauNu_M200);
  total_WJets->Add(mT_Stage1_WToTauNu_M500);
  total_WJets->Add(mT_Stage1_WToTauNu_M1000);
  total_WJets->Add(mT_Stage1_WToTauNu_M2000);
  total_WJets->Add(mT_Stage1_WToTauNu_M3000);
  total_WJets->Add(mT_Stage1_WToTauNu_M4000);
  total_WJets->Add(mT_Stage1_WToTauNu_M5000);
  total_WJets->Add(mT_Stage1_WToTauNu_M6000);
  total_WJets->Add(mT_Stage1_WJetsToLNu);
  total_WJets->SetFillColorAlpha(kGreen-8,0.5);
  total_WJets->SetLineColor(kBlack);
  //std::cout << "Wjets " << total_WJets->GetBinError(300) << std::endl;

  total_WJets->Rebin(80);


  //file_WW
  TH1D* h1_evt_WW = (TH1D*)file_WW->Get("demo/histoDir/eventCount");
  unsigned long long evt_WW = h1_evt_WW->GetEntries(); //Integral();                                                                         
  double wt_WW = (xs_WW*lumi)/evt_WW ;
  TH1D* mT_Stage1_WW  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WW->Scale(wt_WW);
  std::cout << "WW weighted nevt=" << mT_Stage1_WW->Integral() << std::endl;
  totalMC +=mT_Stage1_WW->Integral() ;
  //
  TH1D* mT_Stage1_WW_JetEnUp  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_WW_JetEnUp->Scale(wt_WW);

  TH1D* mT_Stage1_WW_JetEnDown  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_WW_JetEnDown->Scale(wt_WW);
  //
  TH1D* mT_Stage1_WW_JetResUp  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_WW_JetResUp->Scale(wt_WW);

  TH1D* mT_Stage1_WW_JetResDown  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_WW_JetResDown->Scale(wt_WW);
  //
  TH1D* mT_Stage1_WW_MuonEnUp  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_WW_MuonEnUp->Scale(wt_WW);

  TH1D* mT_Stage1_WW_MuonEnDown  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_WW_MuonEnDown->Scale(wt_WW);
  //
  TH1D* mT_Stage1_WW_ElectronEnUp  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_WW_ElectronEnUp->Scale(wt_WW);

  TH1D* mT_Stage1_WW_ElectronEnDown  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_WW_ElectronEnDown->Scale(wt_WW);
  //
  TH1D* mT_Stage1_WW_TauEnUp  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_WW_TauEnUp->Scale(wt_WW);

  TH1D* mT_Stage1_WW_TauEnDown  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_WW_TauEnDown->Scale(wt_WW);
  //
  TH1D* mT_Stage1_WW_PhotonEnUp  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_WW_PhotonEnUp->Scale(wt_WW);

  TH1D* mT_Stage1_WW_PhotonEnDown  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_WW_PhotonEnDown->Scale(wt_WW);
  //
  TH1D* mT_Stage1_WW_UnclusteredEnUp  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_WW_UnclusteredEnUp->Scale(wt_WW);

  TH1D* mT_Stage1_WW_UnclusteredEnDown  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_WW_UnclusteredEnDown->Scale(wt_WW);
  //
  TH1D* mT_Stage1_WW_TauScaleUp  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_WW_TauScaleUp->Scale(wt_WW);

  TH1D* mT_Stage1_WW_TauScaleDown  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_WW_TauScaleDown->Scale(wt_WW);
  //
  TH1D* mT_Stage1_WW_pileupUncertUp  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_WW_pileupUncertUp->Scale(wt_WW);

  TH1D* mT_Stage1_WW_pileupUncertDown  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_WW_pileupUncertDown->Scale(wt_WW);
  //
  TH1D* mT_Stage1_WW_kFactorUp  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_WW_kFactorUp->Scale(wt_WW);

  TH1D* mT_Stage1_WW_kFactorDown  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_WW_kFactorDown->Scale(wt_WW);
  //
  TH1D* mT_Stage1_WW_TauIDSFUp  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_WW_TauIDSFUp->Scale(wt_WW);

  TH1D* mT_Stage1_WW_TauIDSFDown  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_WW_TauIDSFDown->Scale(wt_WW);

  TH1D* mT_Stage1_WW_TauIDSFflatUp  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_WW_TauIDSFflatUp->Scale(wt_WW);

  TH1D* mT_Stage1_WW_TauIDSFflatDown  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_WW_TauIDSFflatDown->Scale(wt_WW);
  //
  TH1D* mT_Stage1_WW_TauELESFUp  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_WW_TauELESFUp->Scale(wt_WW);

  TH1D* mT_Stage1_WW_TauELESFDown  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_WW_TauELESFDown->Scale(wt_WW);
  //
  TH1D* mT_Stage1_WW_trigSFUp  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_WW_trigSFUp->Scale(wt_WW);

  TH1D* mT_Stage1_WW_trigSFDown  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_WW_trigSFDown->Scale(wt_WW);
  //
  /*
  TH1D* mT_Stage1_WW_pdfUncertUp  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_WW_pdfUncertUp->Scale(wt_WW);

  TH1D* mT_Stage1_WW_pdfUncertDown  = (TH1D*)file_WW->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_WW_pdfUncertDown->Scale(wt_WW);
  */ //

  //file_WZ
  TH1D* h1_evt_WZ = (TH1D*)file_WZ->Get("demo/histoDir/eventCount");
  unsigned long long evt_WZ = h1_evt_WZ->GetEntries(); //Integral();                                                                         
  double wt_WZ = (xs_WZ*lumi)/evt_WZ ;
  TH1D* mT_Stage1_WZ  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_WZ->Scale(wt_WZ);
  mT_Stage1_WZ->Scale(kfact_WZ);
  std::cout << "WZ weighted nevt=" << mT_Stage1_WZ->Integral() << std::endl;
  totalMC +=  mT_Stage1_WZ->Integral();
  //
  TH1D* mT_Stage1_WZ_JetEnUp  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_WZ_JetEnUp->Scale(wt_WZ);
  mT_Stage1_WZ_JetEnUp->Scale(kfact_WZ);

  TH1D* mT_Stage1_WZ_JetEnDown  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_WZ_JetEnDown->Scale(wt_WZ);
  mT_Stage1_WZ_JetEnDown->Scale(kfact_WZ);
  //
  TH1D* mT_Stage1_WZ_JetResUp  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_WZ_JetResUp->Scale(wt_WZ);
  mT_Stage1_WZ_JetResUp->Scale(kfact_WZ);

  TH1D* mT_Stage1_WZ_JetResDown  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_WZ_JetResDown->Scale(wt_WZ);
  mT_Stage1_WZ_JetResDown->Scale(kfact_WZ);
  //
  TH1D* mT_Stage1_WZ_MuonEnUp  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_WZ_MuonEnUp->Scale(wt_WZ);
  mT_Stage1_WZ_MuonEnUp->Scale(kfact_WZ);

  TH1D* mT_Stage1_WZ_MuonEnDown  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_WZ_MuonEnDown->Scale(wt_WZ);
  mT_Stage1_WZ_MuonEnDown->Scale(kfact_WZ);
  //
  TH1D* mT_Stage1_WZ_ElectronEnUp  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_WZ_ElectronEnUp->Scale(wt_WZ);
  mT_Stage1_WZ_ElectronEnUp->Scale(kfact_WZ);

  TH1D* mT_Stage1_WZ_ElectronEnDown  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_WZ_ElectronEnDown->Scale(wt_WZ);
  mT_Stage1_WZ_ElectronEnDown->Scale(kfact_WZ);
  //
  TH1D* mT_Stage1_WZ_TauEnUp  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_WZ_TauEnUp->Scale(wt_WZ);
  mT_Stage1_WZ_TauEnUp->Scale(kfact_WZ);

  TH1D* mT_Stage1_WZ_TauEnDown  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_WZ_TauEnDown->Scale(wt_WZ);
  mT_Stage1_WZ_TauEnDown->Scale(kfact_WZ);
  //
  TH1D* mT_Stage1_WZ_PhotonEnUp  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_WZ_PhotonEnUp->Scale(wt_WZ);
  mT_Stage1_WZ_PhotonEnUp->Scale(kfact_WZ);

  TH1D* mT_Stage1_WZ_PhotonEnDown  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_WZ_PhotonEnDown->Scale(wt_WZ);
  mT_Stage1_WZ_PhotonEnDown->Scale(kfact_WZ);
  //
  TH1D* mT_Stage1_WZ_UnclusteredEnUp  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_WZ_UnclusteredEnUp->Scale(wt_WZ);
  mT_Stage1_WZ_UnclusteredEnUp->Scale(kfact_WZ);

  TH1D* mT_Stage1_WZ_UnclusteredEnDown  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_WZ_UnclusteredEnDown->Scale(wt_WZ);
  mT_Stage1_WZ_UnclusteredEnDown->Scale(kfact_WZ);
  //
  TH1D* mT_Stage1_WZ_TauScaleUp  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_WZ_TauScaleUp->Scale(wt_WZ);
  mT_Stage1_WZ_TauScaleUp->Scale(kfact_WZ);

  TH1D* mT_Stage1_WZ_TauScaleDown  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_WZ_TauScaleDown->Scale(wt_WZ);
  mT_Stage1_WZ_TauScaleDown->Scale(kfact_WZ);
  //
  TH1D* mT_Stage1_WZ_pileupUncertUp  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_WZ_pileupUncertUp->Scale(wt_WZ);
  mT_Stage1_WZ_pileupUncertUp->Scale(kfact_WZ);

  TH1D* mT_Stage1_WZ_pileupUncertDown  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_WZ_pileupUncertDown->Scale(wt_WZ);
  mT_Stage1_WZ_pileupUncertDown->Scale(kfact_WZ);
  //
  TH1D* mT_Stage1_WZ_kFactorUp  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_WZ_kFactorUp->Scale(wt_WZ);
  mT_Stage1_WZ_kFactorUp->Scale(kfact_WZ);

  TH1D* mT_Stage1_WZ_kFactorDown  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_WZ_kFactorDown->Scale(wt_WZ);
  mT_Stage1_WZ_kFactorDown->Scale(kfact_WZ);
  //
  TH1D* mT_Stage1_WZ_TauIDSFUp  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_WZ_TauIDSFUp->Scale(wt_WZ);
  mT_Stage1_WZ_TauIDSFUp->Scale(kfact_WZ);

  TH1D* mT_Stage1_WZ_TauIDSFDown  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_WZ_TauIDSFDown->Scale(wt_WZ);
  mT_Stage1_WZ_TauIDSFDown->Scale(kfact_WZ);

  TH1D* mT_Stage1_WZ_TauIDSFflatUp  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_WZ_TauIDSFflatUp->Scale(wt_WZ);
  mT_Stage1_WZ_TauIDSFflatUp->Scale(kfact_WZ);

  TH1D* mT_Stage1_WZ_TauIDSFflatDown  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_WZ_TauIDSFflatDown->Scale(wt_WZ);
  mT_Stage1_WZ_TauIDSFflatDown->Scale(kfact_WZ);
  //
  TH1D* mT_Stage1_WZ_TauELESFUp  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_WZ_TauELESFUp->Scale(wt_WZ);
  mT_Stage1_WZ_TauELESFUp->Scale(kfact_WZ);

  TH1D* mT_Stage1_WZ_TauELESFDown  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_WZ_TauELESFDown->Scale(wt_WZ);
  mT_Stage1_WZ_TauELESFDown->Scale(kfact_WZ);
  //
  TH1D* mT_Stage1_WZ_trigSFUp  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_WZ_trigSFUp->Scale(wt_WZ);
  mT_Stage1_WZ_trigSFUp->Scale(kfact_WZ);

  TH1D* mT_Stage1_WZ_trigSFDown  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_WZ_trigSFDown->Scale(wt_WZ);
  mT_Stage1_WZ_trigSFDown->Scale(kfact_WZ);
  //
  /*
  TH1D* mT_Stage1_WZ_pdfUncertUp  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_WZ_pdfUncertUp->Scale(wt_WZ);
  mT_Stage1_WZ_pdfUncertUp->Scale(kfact_WZ);

  TH1D* mT_Stage1_WZ_pdfUncertDown  = (TH1D*)file_WZ->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_WZ_pdfUncertDown->Scale(wt_WZ);
  mT_Stage1_WZ_pdfUncertDown->Scale(kfact_WZ);
  */ //

  //file_ZZ
  TH1D* h1_evt_ZZ = (TH1D*)file_ZZ->Get("demo/histoDir/eventCount");
  unsigned long long evt_ZZ = h1_evt_ZZ->GetEntries(); //Integral();                                                                         
  double wt_ZZ = (xs_ZZ*lumi)/evt_ZZ ;
  TH1D* mT_Stage1_ZZ  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_ZZ->Scale(wt_ZZ);
  mT_Stage1_ZZ->Scale(kfact_ZZ);
  std::cout << "ZZ weighted nevt=" << mT_Stage1_ZZ->Integral() << std::endl;
  totalMC += mT_Stage1_ZZ->Integral();
  //
  TH1D* mT_Stage1_ZZ_JetEnUp  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_ZZ_JetEnUp->Scale(wt_ZZ);
  mT_Stage1_ZZ_JetEnUp->Scale(kfact_ZZ);

  TH1D* mT_Stage1_ZZ_JetEnDown  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_ZZ_JetEnDown->Scale(wt_ZZ);
  mT_Stage1_ZZ_JetEnDown->Scale(kfact_ZZ);
  //
  TH1D* mT_Stage1_ZZ_JetResUp  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_ZZ_JetResUp->Scale(wt_ZZ);
  mT_Stage1_ZZ_JetResUp->Scale(kfact_ZZ);

  TH1D* mT_Stage1_ZZ_JetResDown  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_ZZ_JetResDown->Scale(wt_ZZ);
  mT_Stage1_ZZ_JetResDown->Scale(kfact_ZZ);
  //
  TH1D* mT_Stage1_ZZ_MuonEnUp  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_ZZ_MuonEnUp->Scale(wt_ZZ);
  mT_Stage1_ZZ_MuonEnUp->Scale(kfact_ZZ);

  TH1D* mT_Stage1_ZZ_MuonEnDown  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_ZZ_MuonEnDown->Scale(wt_ZZ);
  mT_Stage1_ZZ_MuonEnDown->Scale(kfact_ZZ);
  //
  TH1D* mT_Stage1_ZZ_ElectronEnUp  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_ZZ_ElectronEnUp->Scale(wt_ZZ);
  mT_Stage1_ZZ_ElectronEnUp->Scale(kfact_ZZ);

  TH1D* mT_Stage1_ZZ_ElectronEnDown  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_ZZ_ElectronEnDown->Scale(wt_ZZ);
  mT_Stage1_ZZ_ElectronEnDown->Scale(kfact_ZZ);
  //
  TH1D* mT_Stage1_ZZ_TauEnUp  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_ZZ_TauEnUp->Scale(wt_ZZ);
  mT_Stage1_ZZ_TauEnUp->Scale(kfact_ZZ);

  TH1D* mT_Stage1_ZZ_TauEnDown  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_ZZ_TauEnDown->Scale(wt_ZZ);
  mT_Stage1_ZZ_TauEnDown->Scale(kfact_ZZ);
  //
  TH1D* mT_Stage1_ZZ_PhotonEnUp  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_ZZ_PhotonEnUp->Scale(wt_ZZ);
  mT_Stage1_ZZ_PhotonEnUp->Scale(kfact_ZZ);

  TH1D* mT_Stage1_ZZ_PhotonEnDown  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_ZZ_PhotonEnDown->Scale(wt_ZZ);
  mT_Stage1_ZZ_PhotonEnDown->Scale(kfact_ZZ);
  //
  TH1D* mT_Stage1_ZZ_UnclusteredEnUp  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_ZZ_UnclusteredEnUp->Scale(wt_ZZ);
  mT_Stage1_ZZ_UnclusteredEnUp->Scale(kfact_ZZ);

  TH1D* mT_Stage1_ZZ_UnclusteredEnDown  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_ZZ_UnclusteredEnDown->Scale(wt_ZZ);
  mT_Stage1_ZZ_UnclusteredEnDown->Scale(kfact_ZZ);
  //
  TH1D* mT_Stage1_ZZ_TauScaleUp  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_ZZ_TauScaleUp->Scale(wt_ZZ);
  mT_Stage1_ZZ_TauScaleUp->Scale(kfact_ZZ);

  TH1D* mT_Stage1_ZZ_TauScaleDown  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_ZZ_TauScaleDown->Scale(wt_ZZ);
  mT_Stage1_ZZ_TauScaleDown->Scale(kfact_ZZ);
  //
  TH1D* mT_Stage1_ZZ_pileupUncertUp  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_ZZ_pileupUncertUp->Scale(wt_ZZ);
  mT_Stage1_ZZ_pileupUncertUp->Scale(kfact_ZZ);

  TH1D* mT_Stage1_ZZ_pileupUncertDown  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_ZZ_pileupUncertDown->Scale(wt_ZZ);
  mT_Stage1_ZZ_pileupUncertDown->Scale(kfact_ZZ);
  //
  TH1D* mT_Stage1_ZZ_kFactorUp  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_ZZ_kFactorUp->Scale(wt_ZZ);
  mT_Stage1_ZZ_kFactorUp->Scale(kfact_ZZ);

  TH1D* mT_Stage1_ZZ_kFactorDown  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_ZZ_kFactorDown->Scale(wt_ZZ);
  mT_Stage1_ZZ_kFactorDown->Scale(kfact_ZZ);
  //
  TH1D* mT_Stage1_ZZ_TauIDSFUp  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_ZZ_TauIDSFUp->Scale(wt_ZZ);
  mT_Stage1_ZZ_TauIDSFUp->Scale(kfact_ZZ);

  TH1D* mT_Stage1_ZZ_TauIDSFDown  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_ZZ_TauIDSFDown->Scale(wt_ZZ);
  mT_Stage1_ZZ_TauIDSFDown->Scale(kfact_ZZ);

  TH1D* mT_Stage1_ZZ_TauIDSFflatUp  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_ZZ_TauIDSFflatUp->Scale(wt_ZZ);
  mT_Stage1_ZZ_TauIDSFflatUp->Scale(kfact_ZZ);

  TH1D* mT_Stage1_ZZ_TauIDSFflatDown  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_ZZ_TauIDSFflatDown->Scale(wt_ZZ);
  mT_Stage1_ZZ_TauIDSFflatDown->Scale(kfact_ZZ);

  TH1D* mT_Stage1_ZZ_TauELESFUp  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_ZZ_TauELESFUp->Scale(wt_ZZ);
  mT_Stage1_ZZ_TauELESFUp->Scale(kfact_ZZ);

  TH1D* mT_Stage1_ZZ_TauELESFDown  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_ZZ_TauELESFDown->Scale(wt_ZZ);
  mT_Stage1_ZZ_TauELESFDown->Scale(kfact_ZZ);

  TH1D* mT_Stage1_ZZ_trigSFUp  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_ZZ_trigSFUp->Scale(wt_ZZ);
  mT_Stage1_ZZ_trigSFUp->Scale(kfact_ZZ);

  TH1D* mT_Stage1_ZZ_trigSFDown  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_ZZ_trigSFDown->Scale(wt_ZZ);
  mT_Stage1_ZZ_trigSFDown->Scale(kfact_ZZ);
  //
  /*
  TH1D* mT_Stage1_ZZ_pdfUncertUp  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_ZZ_pdfUncertUp->Scale(wt_ZZ);
  mT_Stage1_ZZ_pdfUncertUp->Scale(kfact_ZZ);

  TH1D* mT_Stage1_ZZ_pdfUncertDown  = (TH1D*)file_ZZ->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_ZZ_pdfUncertDown->Scale(wt_ZZ);
  mT_Stage1_ZZ_pdfUncertDown->Scale(kfact_ZZ);
  */ //

  TH1D* total_diboson = (TH1D*)mT_Stage1_WW->Clone();
  total_diboson->Add(mT_Stage1_WZ);
  total_diboson->Add(mT_Stage1_ZZ);
  total_diboson->SetFillColorAlpha(kOrange+2,0.5);
  total_diboson->SetLineColor(kBlack);
  total_diboson->Rebin(80);

  //file_QCD_HT200to300
  TH1D* h1_evt_QCD_HT200to300 = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/eventCount");
  unsigned long long evt_QCD_HT200to300 = h1_evt_QCD_HT200to300->GetEntries(); //Integral();                                                                 
  double wt_QCD_HT200to300 = (xs_QCD_HT200to300*lumi)/evt_QCD_HT200to300 ;
  TH1D* mT_Stage1_QCD_HT200to300  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_QCD_HT200to300->Scale(wt_QCD_HT200to300);
  std::cout << "QCD_HT200to300 weighted nevt=" << mT_Stage1_QCD_HT200to300->Integral() << std::endl;
  totalMC += mT_Stage1_QCD_HT200to300->Integral();
  totalQCDMC += mT_Stage1_QCD_HT200to300->Integral();
  //
  TH1D* mT_Stage1_QCD_HT200to300_JetEnUp  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_QCD_HT200to300_JetEnUp->Scale(wt_QCD_HT200to300);

  TH1D* mT_Stage1_QCD_HT200to300_JetEnDown  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_QCD_HT200to300_JetEnDown->Scale(wt_QCD_HT200to300);
  //
  TH1D* mT_Stage1_QCD_HT200to300_JetResUp  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_QCD_HT200to300_JetResUp->Scale(wt_QCD_HT200to300);

  TH1D* mT_Stage1_QCD_HT200to300_JetResDown  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_QCD_HT200to300_JetResDown->Scale(wt_QCD_HT200to300);
  //
  TH1D* mT_Stage1_QCD_HT200to300_MuonEnUp  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_QCD_HT200to300_MuonEnUp->Scale(wt_QCD_HT200to300);

  TH1D* mT_Stage1_QCD_HT200to300_MuonEnDown  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_QCD_HT200to300_MuonEnDown->Scale(wt_QCD_HT200to300);
  //
  TH1D* mT_Stage1_QCD_HT200to300_ElectronEnUp  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_QCD_HT200to300_ElectronEnUp->Scale(wt_QCD_HT200to300);

  TH1D* mT_Stage1_QCD_HT200to300_ElectronEnDown  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_QCD_HT200to300_ElectronEnDown->Scale(wt_QCD_HT200to300);
  //
  TH1D* mT_Stage1_QCD_HT200to300_TauEnUp  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_QCD_HT200to300_TauEnUp->Scale(wt_QCD_HT200to300);

  TH1D* mT_Stage1_QCD_HT200to300_TauEnDown  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_QCD_HT200to300_TauEnDown->Scale(wt_QCD_HT200to300);
  //
  TH1D* mT_Stage1_QCD_HT200to300_PhotonEnUp  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_QCD_HT200to300_PhotonEnUp->Scale(wt_QCD_HT200to300);

  TH1D* mT_Stage1_QCD_HT200to300_PhotonEnDown  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_QCD_HT200to300_PhotonEnDown->Scale(wt_QCD_HT200to300);
  //
  TH1D* mT_Stage1_QCD_HT200to300_UnclusteredEnUp  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_QCD_HT200to300_UnclusteredEnUp->Scale(wt_QCD_HT200to300);

  TH1D* mT_Stage1_QCD_HT200to300_UnclusteredEnDown  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_QCD_HT200to300_UnclusteredEnDown->Scale(wt_QCD_HT200to300);
  //
  TH1D* mT_Stage1_QCD_HT200to300_TauScaleUp  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_QCD_HT200to300_TauScaleUp->Scale(wt_QCD_HT200to300);

  TH1D* mT_Stage1_QCD_HT200to300_TauScaleDown  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_QCD_HT200to300_TauScaleDown->Scale(wt_QCD_HT200to300);
  //
  TH1D* mT_Stage1_QCD_HT200to300_pileupUncertUp  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_QCD_HT200to300_pileupUncertUp->Scale(wt_QCD_HT200to300);

  TH1D* mT_Stage1_QCD_HT200to300_pileupUncertDown  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_QCD_HT200to300_pileupUncertDown->Scale(wt_QCD_HT200to300);
  //
  TH1D* mT_Stage1_QCD_HT200to300_kFactorUp  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_QCD_HT200to300_kFactorUp->Scale(wt_QCD_HT200to300);

  TH1D* mT_Stage1_QCD_HT200to300_kFactorDown  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_QCD_HT200to300_kFactorDown->Scale(wt_QCD_HT200to300);
  //
  TH1D* mT_Stage1_QCD_HT200to300_TauIDSFUp  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_QCD_HT200to300_TauIDSFUp->Scale(wt_QCD_HT200to300);

  TH1D* mT_Stage1_QCD_HT200to300_TauIDSFDown  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_QCD_HT200to300_TauIDSFDown->Scale(wt_QCD_HT200to300);

  TH1D* mT_Stage1_QCD_HT200to300_TauIDSFflatUp  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_QCD_HT200to300_TauIDSFflatUp->Scale(wt_QCD_HT200to300);

  TH1D* mT_Stage1_QCD_HT200to300_TauIDSFflatDown  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_QCD_HT200to300_TauIDSFflatDown->Scale(wt_QCD_HT200to300);
  //
  TH1D* mT_Stage1_QCD_HT200to300_TauELESFUp  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_QCD_HT200to300_TauELESFUp->Scale(wt_QCD_HT200to300);

  TH1D* mT_Stage1_QCD_HT200to300_TauELESFDown  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_QCD_HT200to300_TauELESFDown->Scale(wt_QCD_HT200to300);
  //
  TH1D* mT_Stage1_QCD_HT200to300_trigSFUp  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_QCD_HT200to300_trigSFUp->Scale(wt_QCD_HT200to300);

  TH1D* mT_Stage1_QCD_HT200to300_trigSFDown  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_QCD_HT200to300_trigSFDown->Scale(wt_QCD_HT200to300);
  //
  /*
  TH1D* mT_Stage1_QCD_HT200to300_pdfUncertUp  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_QCD_HT200to300_pdfUncertUp->Scale(wt_QCD_HT200to300);

  TH1D* mT_Stage1_QCD_HT200to300_pdfUncertDown  = (TH1D*)file_QCD_HT200to300->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_QCD_HT200to300_pdfUncertDown->Scale(wt_QCD_HT200to300);
  */  //

  //file_QCD_HT300to500
  TH1D* h1_evt_QCD_HT300to500 = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/eventCount");
  unsigned long long evt_QCD_HT300to500 = h1_evt_QCD_HT300to500->GetEntries(); //Integral();                                                                     
  double wt_QCD_HT300to500 = (xs_QCD_HT300to500*lumi)/evt_QCD_HT300to500 ;
  TH1D* mT_Stage1_QCD_HT300to500  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_QCD_HT300to500->Scale(wt_QCD_HT300to500);
  std::cout << "QCD_HT300to500 weighted nevt=" << mT_Stage1_QCD_HT300to500->Integral() << std::endl;
  totalMC += mT_Stage1_QCD_HT300to500->Integral();
  totalQCDMC += mT_Stage1_QCD_HT300to500->Integral();
  //
  TH1D* mT_Stage1_QCD_HT300to500_JetEnUp  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_QCD_HT300to500_JetEnUp->Scale(wt_QCD_HT300to500);

  TH1D* mT_Stage1_QCD_HT300to500_JetEnDown  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_QCD_HT300to500_JetEnDown->Scale(wt_QCD_HT300to500);
  //
  TH1D* mT_Stage1_QCD_HT300to500_JetResUp  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_QCD_HT300to500_JetResUp->Scale(wt_QCD_HT300to500);

  TH1D* mT_Stage1_QCD_HT300to500_JetResDown  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_QCD_HT300to500_JetResDown->Scale(wt_QCD_HT300to500);
  //
  TH1D* mT_Stage1_QCD_HT300to500_MuonEnUp  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_QCD_HT300to500_MuonEnUp->Scale(wt_QCD_HT300to500);

  TH1D* mT_Stage1_QCD_HT300to500_MuonEnDown  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_QCD_HT300to500_MuonEnDown->Scale(wt_QCD_HT300to500);
  //
  TH1D* mT_Stage1_QCD_HT300to500_ElectronEnUp  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_QCD_HT300to500_ElectronEnUp->Scale(wt_QCD_HT300to500);

  TH1D* mT_Stage1_QCD_HT300to500_ElectronEnDown  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_QCD_HT300to500_ElectronEnDown->Scale(wt_QCD_HT300to500);
  //
  TH1D* mT_Stage1_QCD_HT300to500_TauEnUp  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_QCD_HT300to500_TauEnUp->Scale(wt_QCD_HT300to500);

  TH1D* mT_Stage1_QCD_HT300to500_TauEnDown  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_QCD_HT300to500_TauEnDown->Scale(wt_QCD_HT300to500);
  //
  TH1D* mT_Stage1_QCD_HT300to500_PhotonEnUp  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_QCD_HT300to500_PhotonEnUp->Scale(wt_QCD_HT300to500);

  TH1D* mT_Stage1_QCD_HT300to500_PhotonEnDown  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_QCD_HT300to500_PhotonEnDown->Scale(wt_QCD_HT300to500);
  //
  TH1D* mT_Stage1_QCD_HT300to500_UnclusteredEnUp  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_QCD_HT300to500_UnclusteredEnUp->Scale(wt_QCD_HT300to500);

  TH1D* mT_Stage1_QCD_HT300to500_UnclusteredEnDown  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_QCD_HT300to500_UnclusteredEnDown->Scale(wt_QCD_HT300to500);
  //
  TH1D* mT_Stage1_QCD_HT300to500_TauScaleUp  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_QCD_HT300to500_TauScaleUp->Scale(wt_QCD_HT300to500);

  TH1D* mT_Stage1_QCD_HT300to500_TauScaleDown  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_QCD_HT300to500_TauScaleDown->Scale(wt_QCD_HT300to500);
  //
  TH1D* mT_Stage1_QCD_HT300to500_pileupUncertUp  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_QCD_HT300to500_pileupUncertUp->Scale(wt_QCD_HT300to500);

  TH1D* mT_Stage1_QCD_HT300to500_pileupUncertDown  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_QCD_HT300to500_pileupUncertDown->Scale(wt_QCD_HT300to500);
  //
  TH1D* mT_Stage1_QCD_HT300to500_kFactorUp  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_QCD_HT300to500_kFactorUp->Scale(wt_QCD_HT300to500);

  TH1D* mT_Stage1_QCD_HT300to500_kFactorDown  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_QCD_HT300to500_kFactorDown->Scale(wt_QCD_HT300to500);
  //
  TH1D* mT_Stage1_QCD_HT300to500_TauIDSFUp  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_QCD_HT300to500_TauIDSFUp->Scale(wt_QCD_HT300to500);

  TH1D* mT_Stage1_QCD_HT300to500_TauIDSFDown  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_QCD_HT300to500_TauIDSFDown->Scale(wt_QCD_HT300to500);

  TH1D* mT_Stage1_QCD_HT300to500_TauIDSFflatUp  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_QCD_HT300to500_TauIDSFflatUp->Scale(wt_QCD_HT300to500);

  TH1D* mT_Stage1_QCD_HT300to500_TauIDSFflatDown  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_QCD_HT300to500_TauIDSFflatDown->Scale(wt_QCD_HT300to500);
  //
  TH1D* mT_Stage1_QCD_HT300to500_TauELESFUp  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_QCD_HT300to500_TauELESFUp->Scale(wt_QCD_HT300to500);

  TH1D* mT_Stage1_QCD_HT300to500_TauELESFDown  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_QCD_HT300to500_TauELESFDown->Scale(wt_QCD_HT300to500);
  //
  TH1D* mT_Stage1_QCD_HT300to500_trigSFUp  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_QCD_HT300to500_trigSFUp->Scale(wt_QCD_HT300to500);

  TH1D* mT_Stage1_QCD_HT300to500_trigSFDown  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_QCD_HT300to500_trigSFDown->Scale(wt_QCD_HT300to500);
  //
  /*
  TH1D* mT_Stage1_QCD_HT300to500_pdfUncertUp  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_QCD_HT300to500_pdfUncertUp->Scale(wt_QCD_HT300to500);

  TH1D* mT_Stage1_QCD_HT300to500_pdfUncertDown  = (TH1D*)file_QCD_HT300to500->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_QCD_HT300to500_pdfUncertDown->Scale(wt_QCD_HT300to500);
  */  //

  //file_QCD_HT500to700
  TH1D* h1_evt_QCD_HT500to700 = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/eventCount");
  unsigned long long evt_QCD_HT500to700 = h1_evt_QCD_HT500to700->GetEntries(); //Integral();                                                                
  double wt_QCD_HT500to700 = (xs_QCD_HT500to700*lumi)/evt_QCD_HT500to700 ;
  TH1D* mT_Stage1_QCD_HT500to700  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_QCD_HT500to700->Scale(wt_QCD_HT500to700);
  std::cout << "QCD_HT500to700 weighted nevt=" << mT_Stage1_QCD_HT500to700->Integral() << std::endl;
  totalMC += mT_Stage1_QCD_HT500to700->Integral();
  totalQCDMC += mT_Stage1_QCD_HT500to700->Integral();
  //
  TH1D* mT_Stage1_QCD_HT500to700_JetEnUp  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_QCD_HT500to700_JetEnUp->Scale(wt_QCD_HT500to700);

  TH1D* mT_Stage1_QCD_HT500to700_JetEnDown  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_QCD_HT500to700_JetEnDown->Scale(wt_QCD_HT500to700);
  //
  TH1D* mT_Stage1_QCD_HT500to700_JetResUp  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_QCD_HT500to700_JetResUp->Scale(wt_QCD_HT500to700);

  TH1D* mT_Stage1_QCD_HT500to700_JetResDown  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_QCD_HT500to700_JetResDown->Scale(wt_QCD_HT500to700);
  //
  TH1D* mT_Stage1_QCD_HT500to700_MuonEnUp  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_QCD_HT500to700_MuonEnUp->Scale(wt_QCD_HT500to700);

  TH1D* mT_Stage1_QCD_HT500to700_MuonEnDown  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_QCD_HT500to700_MuonEnDown->Scale(wt_QCD_HT500to700);
  //
  TH1D* mT_Stage1_QCD_HT500to700_ElectronEnUp  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_QCD_HT500to700_ElectronEnUp->Scale(wt_QCD_HT500to700);

  TH1D* mT_Stage1_QCD_HT500to700_ElectronEnDown  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_QCD_HT500to700_ElectronEnDown->Scale(wt_QCD_HT500to700);
  //
  TH1D* mT_Stage1_QCD_HT500to700_TauEnUp  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_QCD_HT500to700_TauEnUp->Scale(wt_QCD_HT500to700);

  TH1D* mT_Stage1_QCD_HT500to700_TauEnDown  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_QCD_HT500to700_TauEnDown->Scale(wt_QCD_HT500to700);

  //
  TH1D* mT_Stage1_QCD_HT500to700_PhotonEnUp  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_QCD_HT500to700_PhotonEnUp->Scale(wt_QCD_HT500to700);

  TH1D* mT_Stage1_QCD_HT500to700_PhotonEnDown  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_QCD_HT500to700_PhotonEnDown->Scale(wt_QCD_HT500to700);
  //
  TH1D* mT_Stage1_QCD_HT500to700_UnclusteredEnUp  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_QCD_HT500to700_UnclusteredEnUp->Scale(wt_QCD_HT500to700);

  TH1D* mT_Stage1_QCD_HT500to700_UnclusteredEnDown  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_QCD_HT500to700_UnclusteredEnDown->Scale(wt_QCD_HT500to700);
  //
  TH1D* mT_Stage1_QCD_HT500to700_TauScaleUp  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_QCD_HT500to700_TauScaleUp->Scale(wt_QCD_HT500to700);

  TH1D* mT_Stage1_QCD_HT500to700_TauScaleDown  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_QCD_HT500to700_TauScaleDown->Scale(wt_QCD_HT500to700);
  //
  TH1D* mT_Stage1_QCD_HT500to700_pileupUncertUp  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_QCD_HT500to700_pileupUncertUp->Scale(wt_QCD_HT500to700);

  TH1D* mT_Stage1_QCD_HT500to700_pileupUncertDown  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_QCD_HT500to700_pileupUncertDown->Scale(wt_QCD_HT500to700);
  //
  TH1D* mT_Stage1_QCD_HT500to700_kFactorUp  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_QCD_HT500to700_kFactorUp->Scale(wt_QCD_HT500to700);

  TH1D* mT_Stage1_QCD_HT500to700_kFactorDown  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_QCD_HT500to700_kFactorDown->Scale(wt_QCD_HT500to700);
  //
  TH1D* mT_Stage1_QCD_HT500to700_TauIDSFUp  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_QCD_HT500to700_TauIDSFUp->Scale(wt_QCD_HT500to700);

  TH1D* mT_Stage1_QCD_HT500to700_TauIDSFDown  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_QCD_HT500to700_TauIDSFDown->Scale(wt_QCD_HT500to700);

  TH1D* mT_Stage1_QCD_HT500to700_TauIDSFflatUp  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_QCD_HT500to700_TauIDSFflatUp->Scale(wt_QCD_HT500to700);

  TH1D* mT_Stage1_QCD_HT500to700_TauIDSFflatDown  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_QCD_HT500to700_TauIDSFflatDown->Scale(wt_QCD_HT500to700);
  //
  TH1D* mT_Stage1_QCD_HT500to700_TauELESFUp  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_QCD_HT500to700_TauELESFUp->Scale(wt_QCD_HT500to700);

  TH1D* mT_Stage1_QCD_HT500to700_TauELESFDown  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_QCD_HT500to700_TauELESFDown->Scale(wt_QCD_HT500to700);
  //

  TH1D* mT_Stage1_QCD_HT500to700_trigSFUp  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_QCD_HT500to700_trigSFUp->Scale(wt_QCD_HT500to700);

  TH1D* mT_Stage1_QCD_HT500to700_trigSFDown  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_QCD_HT500to700_trigSFDown->Scale(wt_QCD_HT500to700);
  //
  /*
  TH1D* mT_Stage1_QCD_HT500to700_pdfUncertUp  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_QCD_HT500to700_pdfUncertUp->Scale(wt_QCD_HT500to700);

  TH1D* mT_Stage1_QCD_HT500to700_pdfUncertDown  = (TH1D*)file_QCD_HT500to700->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_QCD_HT500to700_pdfUncertDown->Scale(wt_QCD_HT500to700);
  */  //

  //file_QCD_HT700to1000
  TH1D* h1_evt_QCD_HT700to1000 = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/eventCount");
  unsigned long long evt_QCD_HT700to1000 = h1_evt_QCD_HT700to1000->GetEntries(); //Integral();                                                                
  double wt_QCD_HT700to1000 = (xs_QCD_HT700to1000*lumi)/evt_QCD_HT700to1000 ;
  TH1D* mT_Stage1_QCD_HT700to1000  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);
  std::cout << "QCD_HT700to1000 weighted nevt=" << mT_Stage1_QCD_HT700to1000->Integral() << std::endl;
  totalMC += mT_Stage1_QCD_HT700to1000->Integral();
  totalQCDMC += mT_Stage1_QCD_HT700to1000->Integral();
  //
  TH1D* mT_Stage1_QCD_HT700to1000_JetEnUp  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_QCD_HT700to1000_JetEnUp->Scale(wt_QCD_HT700to1000);

  TH1D* mT_Stage1_QCD_HT700to1000_JetEnDown  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_QCD_HT700to1000_JetEnDown->Scale(wt_QCD_HT700to1000);
  //
  TH1D* mT_Stage1_QCD_HT700to1000_JetResUp  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_QCD_HT700to1000_JetResUp->Scale(wt_QCD_HT700to1000);

  TH1D* mT_Stage1_QCD_HT700to1000_JetResDown  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_QCD_HT700to1000_JetResDown->Scale(wt_QCD_HT700to1000);
  //
  TH1D* mT_Stage1_QCD_HT700to1000_MuonEnUp  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_QCD_HT700to1000_MuonEnUp->Scale(wt_QCD_HT700to1000);

  TH1D* mT_Stage1_QCD_HT700to1000_MuonEnDown  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_QCD_HT700to1000_MuonEnDown->Scale(wt_QCD_HT700to1000);
  //
  TH1D* mT_Stage1_QCD_HT700to1000_ElectronEnUp  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_QCD_HT700to1000_ElectronEnUp->Scale(wt_QCD_HT700to1000);

  TH1D* mT_Stage1_QCD_HT700to1000_ElectronEnDown  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_QCD_HT700to1000_ElectronEnDown->Scale(wt_QCD_HT700to1000);
  //
  TH1D* mT_Stage1_QCD_HT700to1000_TauEnUp  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_QCD_HT700to1000_TauEnUp->Scale(wt_QCD_HT700to1000);

  TH1D* mT_Stage1_QCD_HT700to1000_TauEnDown  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_QCD_HT700to1000_TauEnDown->Scale(wt_QCD_HT700to1000);
  //
  TH1D* mT_Stage1_QCD_HT700to1000_PhotonEnUp  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_QCD_HT700to1000_PhotonEnUp->Scale(wt_QCD_HT700to1000);

  TH1D* mT_Stage1_QCD_HT700to1000_PhotonEnDown  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_QCD_HT700to1000_PhotonEnDown->Scale(wt_QCD_HT700to1000);
  //
  TH1D* mT_Stage1_QCD_HT700to1000_UnclusteredEnUp  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_QCD_HT700to1000_UnclusteredEnUp->Scale(wt_QCD_HT700to1000);

  TH1D* mT_Stage1_QCD_HT700to1000_UnclusteredEnDown  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_QCD_HT700to1000_UnclusteredEnDown->Scale(wt_QCD_HT700to1000);
  //
  TH1D* mT_Stage1_QCD_HT700to1000_TauScaleUp  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_QCD_HT700to1000_TauScaleUp->Scale(wt_QCD_HT700to1000);

  TH1D* mT_Stage1_QCD_HT700to1000_TauScaleDown  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_QCD_HT700to1000_TauScaleDown->Scale(wt_QCD_HT700to1000);
  //
  TH1D* mT_Stage1_QCD_HT700to1000_pileupUncertUp  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_QCD_HT700to1000_pileupUncertUp->Scale(wt_QCD_HT700to1000);

  TH1D* mT_Stage1_QCD_HT700to1000_pileupUncertDown  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_QCD_HT700to1000_pileupUncertDown->Scale(wt_QCD_HT700to1000);
  //
  TH1D* mT_Stage1_QCD_HT700to1000_kFactorUp  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_QCD_HT700to1000_kFactorUp->Scale(wt_QCD_HT700to1000);

  TH1D* mT_Stage1_QCD_HT700to1000_kFactorDown  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_QCD_HT700to1000_kFactorDown->Scale(wt_QCD_HT700to1000);
  //
  TH1D* mT_Stage1_QCD_HT700to1000_TauIDSFUp  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_QCD_HT700to1000_TauIDSFUp->Scale(wt_QCD_HT700to1000);

  TH1D* mT_Stage1_QCD_HT700to1000_TauIDSFDown  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_QCD_HT700to1000_TauIDSFDown->Scale(wt_QCD_HT700to1000);

  TH1D* mT_Stage1_QCD_HT700to1000_TauIDSFflatUp  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_QCD_HT700to1000_TauIDSFflatUp->Scale(wt_QCD_HT700to1000);

  TH1D* mT_Stage1_QCD_HT700to1000_TauIDSFflatDown  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_QCD_HT700to1000_TauIDSFflatDown->Scale(wt_QCD_HT700to1000);
  //
  TH1D* mT_Stage1_QCD_HT700to1000_TauELESFUp  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_QCD_HT700to1000_TauELESFUp->Scale(wt_QCD_HT700to1000);

  TH1D* mT_Stage1_QCD_HT700to1000_TauELESFDown  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_QCD_HT700to1000_TauELESFDown->Scale(wt_QCD_HT700to1000);
  //
  TH1D* mT_Stage1_QCD_HT700to1000_trigSFUp  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_QCD_HT700to1000_trigSFUp->Scale(wt_QCD_HT700to1000);

  TH1D* mT_Stage1_QCD_HT700to1000_trigSFDown  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_QCD_HT700to1000_trigSFDown->Scale(wt_QCD_HT700to1000);
  //
  /*
  TH1D* mT_Stage1_QCD_HT700to1000_pdfUncertUp  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_QCD_HT700to1000_pdfUncertUp->Scale(wt_QCD_HT700to1000);

  TH1D* mT_Stage1_QCD_HT700to1000_pdfUncertDown  = (TH1D*)file_QCD_HT700to1000->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_QCD_HT700to1000_pdfUncertDown->Scale(wt_QCD_HT700to1000);
  */  //

  //file_QCD_HT1000to1500
  TH1D* h1_evt_QCD_HT1000to1500 = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/eventCount");
  unsigned long long evt_QCD_HT1000to1500 = h1_evt_QCD_HT1000to1500->GetEntries(); //Integral();                                                                  
  double wt_QCD_HT1000to1500 = (xs_QCD_HT1000to1500*lumi)/evt_QCD_HT1000to1500 ;
  TH1D* mT_Stage1_QCD_HT1000to1500  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);
  std::cout << "QCD_HT1000to1500 weighted nevt=" << mT_Stage1_QCD_HT1000to1500->Integral() << std::endl;
  totalMC += mT_Stage1_QCD_HT1000to1500->Integral();
  totalQCDMC += mT_Stage1_QCD_HT1000to1500->Integral();
  //
  TH1D* mT_Stage1_QCD_HT1000to1500_JetEnUp  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_QCD_HT1000to1500_JetEnUp->Scale(wt_QCD_HT1000to1500);

  TH1D* mT_Stage1_QCD_HT1000to1500_JetEnDown  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_QCD_HT1000to1500_JetEnDown->Scale(wt_QCD_HT1000to1500);
  //
  TH1D* mT_Stage1_QCD_HT1000to1500_JetResUp  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_QCD_HT1000to1500_JetResUp->Scale(wt_QCD_HT1000to1500);

  TH1D* mT_Stage1_QCD_HT1000to1500_JetResDown  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_QCD_HT1000to1500_JetResDown->Scale(wt_QCD_HT1000to1500);
  //
  TH1D* mT_Stage1_QCD_HT1000to1500_MuonEnUp  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_QCD_HT1000to1500_MuonEnUp->Scale(wt_QCD_HT1000to1500);

  TH1D* mT_Stage1_QCD_HT1000to1500_MuonEnDown  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_QCD_HT1000to1500_MuonEnDown->Scale(wt_QCD_HT1000to1500);
  //
  TH1D* mT_Stage1_QCD_HT1000to1500_ElectronEnUp  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_QCD_HT1000to1500_ElectronEnUp->Scale(wt_QCD_HT1000to1500);

  TH1D* mT_Stage1_QCD_HT1000to1500_ElectronEnDown  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_QCD_HT1000to1500_ElectronEnDown->Scale(wt_QCD_HT1000to1500);
  //
  TH1D* mT_Stage1_QCD_HT1000to1500_TauEnUp  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_QCD_HT1000to1500_TauEnUp->Scale(wt_QCD_HT1000to1500);

  TH1D* mT_Stage1_QCD_HT1000to1500_TauEnDown  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_QCD_HT1000to1500_TauEnDown->Scale(wt_QCD_HT1000to1500);
  //
  TH1D* mT_Stage1_QCD_HT1000to1500_PhotonEnUp  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_QCD_HT1000to1500_PhotonEnUp->Scale(wt_QCD_HT1000to1500);

  TH1D* mT_Stage1_QCD_HT1000to1500_PhotonEnDown  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_QCD_HT1000to1500_PhotonEnDown->Scale(wt_QCD_HT1000to1500);
  //
  TH1D* mT_Stage1_QCD_HT1000to1500_UnclusteredEnUp  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_QCD_HT1000to1500_UnclusteredEnUp->Scale(wt_QCD_HT1000to1500);

  TH1D* mT_Stage1_QCD_HT1000to1500_UnclusteredEnDown  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_QCD_HT1000to1500_UnclusteredEnDown->Scale(wt_QCD_HT1000to1500);
  //
  TH1D* mT_Stage1_QCD_HT1000to1500_TauScaleUp  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_QCD_HT1000to1500_TauScaleUp->Scale(wt_QCD_HT1000to1500);

  TH1D* mT_Stage1_QCD_HT1000to1500_TauScaleDown  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_QCD_HT1000to1500_TauScaleDown->Scale(wt_QCD_HT1000to1500);
  //
  TH1D* mT_Stage1_QCD_HT1000to1500_pileupUncertUp  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_QCD_HT1000to1500_pileupUncertUp->Scale(wt_QCD_HT1000to1500);

  TH1D* mT_Stage1_QCD_HT1000to1500_pileupUncertDown  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_QCD_HT1000to1500_pileupUncertDown->Scale(wt_QCD_HT1000to1500);
  //
  TH1D* mT_Stage1_QCD_HT1000to1500_kFactorUp  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_QCD_HT1000to1500_kFactorUp->Scale(wt_QCD_HT1000to1500);

  TH1D* mT_Stage1_QCD_HT1000to1500_kFactorDown  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_QCD_HT1000to1500_kFactorDown->Scale(wt_QCD_HT1000to1500);
  //
  TH1D* mT_Stage1_QCD_HT1000to1500_TauIDSFUp  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_QCD_HT1000to1500_TauIDSFUp->Scale(wt_QCD_HT1000to1500);

  TH1D* mT_Stage1_QCD_HT1000to1500_TauIDSFDown  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_QCD_HT1000to1500_TauIDSFDown->Scale(wt_QCD_HT1000to1500);

  TH1D* mT_Stage1_QCD_HT1000to1500_TauIDSFflatUp  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_QCD_HT1000to1500_TauIDSFflatUp->Scale(wt_QCD_HT1000to1500);

  TH1D* mT_Stage1_QCD_HT1000to1500_TauIDSFflatDown  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_QCD_HT1000to1500_TauIDSFflatDown->Scale(wt_QCD_HT1000to1500);
  //
  TH1D* mT_Stage1_QCD_HT1000to1500_TauELESFUp  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_QCD_HT1000to1500_TauELESFUp->Scale(wt_QCD_HT1000to1500);

  TH1D* mT_Stage1_QCD_HT1000to1500_TauELESFDown  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_QCD_HT1000to1500_TauELESFDown->Scale(wt_QCD_HT1000to1500);
  //
  TH1D* mT_Stage1_QCD_HT1000to1500_trigSFUp  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_QCD_HT1000to1500_trigSFUp->Scale(wt_QCD_HT1000to1500);

  TH1D* mT_Stage1_QCD_HT1000to1500_trigSFDown  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_QCD_HT1000to1500_trigSFDown->Scale(wt_QCD_HT1000to1500);
  //
  /*
  TH1D* mT_Stage1_QCD_HT1000to1500_pdfUncertUp  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_QCD_HT1000to1500_pdfUncertUp->Scale(wt_QCD_HT1000to1500);

  TH1D* mT_Stage1_QCD_HT1000to1500_pdfUncertDown  = (TH1D*)file_QCD_HT1000to1500->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_QCD_HT1000to1500_pdfUncertDown->Scale(wt_QCD_HT1000to1500);
  */  //

  //file_QCD_HT1500to2000
  TH1D* h1_evt_QCD_HT1500to2000 = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/eventCount");
  unsigned long long evt_QCD_HT1500to2000 = h1_evt_QCD_HT1500to2000->GetEntries(); //Integral();                                                                  
  double wt_QCD_HT1500to2000 = (xs_QCD_HT1500to2000*lumi)/evt_QCD_HT1500to2000 ;
  TH1D* mT_Stage1_QCD_HT1500to2000  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);
  std::cout << "QCD_HT1500to2000 weighted nevt=" << mT_Stage1_QCD_HT1500to2000->Integral() << std::endl;
  totalMC += mT_Stage1_QCD_HT1500to2000->Integral() ;
  totalQCDMC += mT_Stage1_QCD_HT1500to2000->Integral() ;
  //
  TH1D* mT_Stage1_QCD_HT1500to2000_JetEnUp  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_QCD_HT1500to2000_JetEnUp->Scale(wt_QCD_HT1500to2000);

  TH1D* mT_Stage1_QCD_HT1500to2000_JetEnDown  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_QCD_HT1500to2000_JetEnDown->Scale(wt_QCD_HT1500to2000);
  //
  TH1D* mT_Stage1_QCD_HT1500to2000_JetResUp  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_QCD_HT1500to2000_JetResUp->Scale(wt_QCD_HT1500to2000);

  TH1D* mT_Stage1_QCD_HT1500to2000_JetResDown  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_QCD_HT1500to2000_JetResDown->Scale(wt_QCD_HT1500to2000);
  //
  TH1D* mT_Stage1_QCD_HT1500to2000_MuonEnUp  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_QCD_HT1500to2000_MuonEnUp->Scale(wt_QCD_HT1500to2000);

  TH1D* mT_Stage1_QCD_HT1500to2000_MuonEnDown  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_QCD_HT1500to2000_MuonEnDown->Scale(wt_QCD_HT1500to2000);
  //
  TH1D* mT_Stage1_QCD_HT1500to2000_ElectronEnUp  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_QCD_HT1500to2000_ElectronEnUp->Scale(wt_QCD_HT1500to2000);

  TH1D* mT_Stage1_QCD_HT1500to2000_ElectronEnDown  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_QCD_HT1500to2000_ElectronEnDown->Scale(wt_QCD_HT1500to2000);
  //
  TH1D* mT_Stage1_QCD_HT1500to2000_TauEnUp  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_QCD_HT1500to2000_TauEnUp->Scale(wt_QCD_HT1500to2000);

  TH1D* mT_Stage1_QCD_HT1500to2000_TauEnDown  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_QCD_HT1500to2000_TauEnDown->Scale(wt_QCD_HT1500to2000);
  //
  TH1D* mT_Stage1_QCD_HT1500to2000_PhotonEnUp  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_QCD_HT1500to2000_PhotonEnUp->Scale(wt_QCD_HT1500to2000);

  TH1D* mT_Stage1_QCD_HT1500to2000_PhotonEnDown  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_QCD_HT1500to2000_PhotonEnDown->Scale(wt_QCD_HT1500to2000);
  //
  TH1D* mT_Stage1_QCD_HT1500to2000_UnclusteredEnUp  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_QCD_HT1500to2000_UnclusteredEnUp->Scale(wt_QCD_HT1500to2000);

  TH1D* mT_Stage1_QCD_HT1500to2000_UnclusteredEnDown  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_QCD_HT1500to2000_UnclusteredEnDown->Scale(wt_QCD_HT1500to2000);
  //
  TH1D* mT_Stage1_QCD_HT1500to2000_TauScaleUp  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_QCD_HT1500to2000_TauScaleUp->Scale(wt_QCD_HT1500to2000);

  TH1D* mT_Stage1_QCD_HT1500to2000_TauScaleDown  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_QCD_HT1500to2000_TauScaleDown->Scale(wt_QCD_HT1500to2000);
  //
  TH1D* mT_Stage1_QCD_HT1500to2000_pileupUncertUp  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_QCD_HT1500to2000_pileupUncertUp->Scale(wt_QCD_HT1500to2000);

  TH1D* mT_Stage1_QCD_HT1500to2000_pileupUncertDown  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_QCD_HT1500to2000_pileupUncertDown->Scale(wt_QCD_HT1500to2000);
  //
  TH1D* mT_Stage1_QCD_HT1500to2000_kFactorUp  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_QCD_HT1500to2000_kFactorUp->Scale(wt_QCD_HT1500to2000);

  TH1D* mT_Stage1_QCD_HT1500to2000_kFactorDown  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_QCD_HT1500to2000_kFactorDown->Scale(wt_QCD_HT1500to2000);
  //
  TH1D* mT_Stage1_QCD_HT1500to2000_TauIDSFUp  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_QCD_HT1500to2000_TauIDSFUp->Scale(wt_QCD_HT1500to2000);

  TH1D* mT_Stage1_QCD_HT1500to2000_TauIDSFDown  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_QCD_HT1500to2000_TauIDSFDown->Scale(wt_QCD_HT1500to2000);

  TH1D* mT_Stage1_QCD_HT1500to2000_TauIDSFflatUp  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_QCD_HT1500to2000_TauIDSFflatUp->Scale(wt_QCD_HT1500to2000);

  TH1D* mT_Stage1_QCD_HT1500to2000_TauIDSFflatDown  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_QCD_HT1500to2000_TauIDSFflatDown->Scale(wt_QCD_HT1500to2000);
  //
  TH1D* mT_Stage1_QCD_HT1500to2000_TauELESFUp  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_QCD_HT1500to2000_TauELESFUp->Scale(wt_QCD_HT1500to2000);

  TH1D* mT_Stage1_QCD_HT1500to2000_TauELESFDown  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_QCD_HT1500to2000_TauELESFDown->Scale(wt_QCD_HT1500to2000);
  //
  TH1D* mT_Stage1_QCD_HT1500to2000_trigSFUp  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_QCD_HT1500to2000_trigSFUp->Scale(wt_QCD_HT1500to2000);

  TH1D* mT_Stage1_QCD_HT1500to2000_trigSFDown  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_QCD_HT1500to2000_trigSFDown->Scale(wt_QCD_HT1500to2000);
  //
  /*
  TH1D* mT_Stage1_QCD_HT1500to2000_pdfUncertUp  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_QCD_HT1500to2000_pdfUncertUp->Scale(wt_QCD_HT1500to2000);

  TH1D* mT_Stage1_QCD_HT1500to2000_pdfUncertDown  = (TH1D*)file_QCD_HT1500to2000->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_QCD_HT1500to2000_pdfUncertDown->Scale(wt_QCD_HT1500to2000);
  */  //

  //file_QCD_HT2000toInf
  TH1D* h1_evt_QCD_HT2000toInf = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/eventCount");
  unsigned long long evt_QCD_HT2000toInf = h1_evt_QCD_HT2000toInf->GetEntries(); //Integral();                                                                  
  double wt_QCD_HT2000toInf = (xs_QCD_HT2000toInf*lumi)/evt_QCD_HT2000toInf ;
  TH1D* mT_Stage1_QCD_HT2000toInf  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);
  std::cout << "QCD_HT2000toInf weighted nevt=" << mT_Stage1_QCD_HT2000toInf->Integral() << std::endl;
  totalMC += mT_Stage1_QCD_HT2000toInf->Integral();
  totalQCDMC += mT_Stage1_QCD_HT2000toInf->Integral();
  //
  TH1D* mT_Stage1_QCD_HT2000toInf_JetEnUp  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_QCD_HT2000toInf_JetEnUp->Scale(wt_QCD_HT2000toInf);

  TH1D* mT_Stage1_QCD_HT2000toInf_JetEnDown  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_QCD_HT2000toInf_JetEnDown->Scale(wt_QCD_HT2000toInf);
  //
  TH1D* mT_Stage1_QCD_HT2000toInf_JetResUp  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_QCD_HT2000toInf_JetResUp->Scale(wt_QCD_HT2000toInf);

  TH1D* mT_Stage1_QCD_HT2000toInf_JetResDown  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_QCD_HT2000toInf_JetResDown->Scale(wt_QCD_HT2000toInf);
  //
  TH1D* mT_Stage1_QCD_HT2000toInf_MuonEnUp  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_QCD_HT2000toInf_MuonEnUp->Scale(wt_QCD_HT2000toInf);

  TH1D* mT_Stage1_QCD_HT2000toInf_MuonEnDown  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_QCD_HT2000toInf_MuonEnDown->Scale(wt_QCD_HT2000toInf);
  //
  TH1D* mT_Stage1_QCD_HT2000toInf_ElectronEnUp  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_QCD_HT2000toInf_ElectronEnUp->Scale(wt_QCD_HT2000toInf);

  TH1D* mT_Stage1_QCD_HT2000toInf_ElectronEnDown  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_QCD_HT2000toInf_ElectronEnDown->Scale(wt_QCD_HT2000toInf);
  //
  TH1D* mT_Stage1_QCD_HT2000toInf_TauEnUp  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_QCD_HT2000toInf_TauEnUp->Scale(wt_QCD_HT2000toInf);

  TH1D* mT_Stage1_QCD_HT2000toInf_TauEnDown  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_QCD_HT2000toInf_TauEnDown->Scale(wt_QCD_HT2000toInf);
  //
  TH1D* mT_Stage1_QCD_HT2000toInf_PhotonEnUp  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_QCD_HT2000toInf_PhotonEnUp->Scale(wt_QCD_HT2000toInf);

  TH1D* mT_Stage1_QCD_HT2000toInf_PhotonEnDown  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_QCD_HT2000toInf_PhotonEnDown->Scale(wt_QCD_HT2000toInf);
  //
  TH1D* mT_Stage1_QCD_HT2000toInf_UnclusteredEnUp  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_QCD_HT2000toInf_UnclusteredEnUp->Scale(wt_QCD_HT2000toInf);

  TH1D* mT_Stage1_QCD_HT2000toInf_UnclusteredEnDown  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_QCD_HT2000toInf_UnclusteredEnDown->Scale(wt_QCD_HT2000toInf);
  //
  TH1D* mT_Stage1_QCD_HT2000toInf_TauScaleUp  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_QCD_HT2000toInf_TauScaleUp->Scale(wt_QCD_HT2000toInf);

  TH1D* mT_Stage1_QCD_HT2000toInf_TauScaleDown  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_QCD_HT2000toInf_TauScaleDown->Scale(wt_QCD_HT2000toInf);
  //
  TH1D* mT_Stage1_QCD_HT2000toInf_pileupUncertUp  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_QCD_HT2000toInf_pileupUncertUp->Scale(wt_QCD_HT2000toInf);

  TH1D* mT_Stage1_QCD_HT2000toInf_pileupUncertDown  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_QCD_HT2000toInf_pileupUncertDown->Scale(wt_QCD_HT2000toInf);
  //
  TH1D* mT_Stage1_QCD_HT2000toInf_kFactorUp  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_QCD_HT2000toInf_kFactorUp->Scale(wt_QCD_HT2000toInf);

  TH1D* mT_Stage1_QCD_HT2000toInf_kFactorDown  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_QCD_HT2000toInf_kFactorDown->Scale(wt_QCD_HT2000toInf);
  //
  TH1D* mT_Stage1_QCD_HT2000toInf_TauIDSFUp  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_QCD_HT2000toInf_TauIDSFUp->Scale(wt_QCD_HT2000toInf);

  TH1D* mT_Stage1_QCD_HT2000toInf_TauIDSFDown  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_QCD_HT2000toInf_TauIDSFDown->Scale(wt_QCD_HT2000toInf);

  TH1D* mT_Stage1_QCD_HT2000toInf_TauIDSFflatUp  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_QCD_HT2000toInf_TauIDSFflatUp->Scale(wt_QCD_HT2000toInf);

  TH1D* mT_Stage1_QCD_HT2000toInf_TauIDSFflatDown  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_QCD_HT2000toInf_TauIDSFflatDown->Scale(wt_QCD_HT2000toInf);
  //
  TH1D* mT_Stage1_QCD_HT2000toInf_TauELESFUp  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_QCD_HT2000toInf_TauELESFUp->Scale(wt_QCD_HT2000toInf);

  TH1D* mT_Stage1_QCD_HT2000toInf_TauELESFDown  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_QCD_HT2000toInf_TauELESFDown->Scale(wt_QCD_HT2000toInf);
  //
  TH1D* mT_Stage1_QCD_HT2000toInf_trigSFUp  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_QCD_HT2000toInf_trigSFUp->Scale(wt_QCD_HT2000toInf);

  TH1D* mT_Stage1_QCD_HT2000toInf_trigSFDown  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_QCD_HT2000toInf_trigSFDown->Scale(wt_QCD_HT2000toInf);
  //
  /*
  TH1D* mT_Stage1_QCD_HT2000toInf_pdfUncertUp  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_QCD_HT2000toInf_pdfUncertUp->Scale(wt_QCD_HT2000toInf);

  TH1D* mT_Stage1_QCD_HT2000toInf_pdfUncertDown  = (TH1D*)file_QCD_HT2000toInf->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_QCD_HT2000toInf_pdfUncertDown->Scale(wt_QCD_HT2000toInf);
  */ //


  //file_ZJetsToNuNu_HT100To200
  TH1D* h1_evt_ZJetsToNuNu_HT100To200 = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT100To200 = h1_evt_ZJetsToNuNu_HT100To200->GetEntries(); //Integral();                                                                  
  double wt_ZJetsToNuNu_HT100To200 = (xs_ZJetsToNuNu_HT100To200*lumi)/evt_ZJetsToNuNu_HT100To200 ;
  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);
  //std::cout << "\n" << mT_Stage1_ZJetsToNuNu_HT100To200->GetBinError(600) << std::endl;
  std::cout << "ZJetsToNuNu_HT100To200 weighted nevt=" << mT_Stage1_ZJetsToNuNu_HT100To200->Integral() << std::endl;
  totalMC += mT_Stage1_ZJetsToNuNu_HT100To200->Integral();
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_JetEnUp  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_ZJetsToNuNu_HT100To200_JetEnUp->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_JetEnUp->Scale(kfact_ZJetsToNuNu_HT100To200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_JetEnDown  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_ZJetsToNuNu_HT100To200_JetEnDown->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_JetEnDown->Scale(kfact_ZJetsToNuNu_HT100To200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_JetResUp  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_ZJetsToNuNu_HT100To200_JetResUp->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_JetResUp->Scale(kfact_ZJetsToNuNu_HT100To200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_JetResDown  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_ZJetsToNuNu_HT100To200_JetResDown->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_JetResDown->Scale(kfact_ZJetsToNuNu_HT100To200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_MuonEnUp  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_ZJetsToNuNu_HT100To200_MuonEnUp->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_MuonEnUp->Scale(kfact_ZJetsToNuNu_HT100To200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_MuonEnDown  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_ZJetsToNuNu_HT100To200_MuonEnDown->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_MuonEnDown->Scale(kfact_ZJetsToNuNu_HT100To200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_ElectronEnUp  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_ZJetsToNuNu_HT100To200_ElectronEnUp->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_ElectronEnUp->Scale(kfact_ZJetsToNuNu_HT100To200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_ElectronEnDown  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_ZJetsToNuNu_HT100To200_ElectronEnDown->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_ElectronEnDown->Scale(kfact_ZJetsToNuNu_HT100To200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_TauEnUp  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_ZJetsToNuNu_HT100To200_TauEnUp->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_TauEnUp->Scale(kfact_ZJetsToNuNu_HT100To200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_TauEnDown  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_ZJetsToNuNu_HT100To200_TauEnDown->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_TauEnDown->Scale(kfact_ZJetsToNuNu_HT100To200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_PhotonEnUp  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_ZJetsToNuNu_HT100To200_PhotonEnUp->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_PhotonEnUp->Scale(kfact_ZJetsToNuNu_HT100To200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_PhotonEnDown  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_ZJetsToNuNu_HT100To200_PhotonEnDown->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_PhotonEnDown->Scale(kfact_ZJetsToNuNu_HT100To200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_UnclusteredEnUp  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_ZJetsToNuNu_HT100To200_UnclusteredEnUp->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_UnclusteredEnUp->Scale(kfact_ZJetsToNuNu_HT100To200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_UnclusteredEnDown  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_ZJetsToNuNu_HT100To200_UnclusteredEnDown->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_UnclusteredEnDown->Scale(kfact_ZJetsToNuNu_HT100To200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_TauScaleUp  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_ZJetsToNuNu_HT100To200_TauScaleUp->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_TauScaleUp->Scale(kfact_ZJetsToNuNu_HT100To200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_TauScaleDown  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_ZJetsToNuNu_HT100To200_TauScaleDown->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_TauScaleDown->Scale(kfact_ZJetsToNuNu_HT100To200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_pileupUncertUp  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_ZJetsToNuNu_HT100To200_pileupUncertUp->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_pileupUncertUp->Scale(kfact_ZJetsToNuNu_HT100To200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_pileupUncertDown  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_ZJetsToNuNu_HT100To200_pileupUncertDown->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_pileupUncertDown->Scale(kfact_ZJetsToNuNu_HT100To200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_kFactorUp  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_ZJetsToNuNu_HT100To200_kFactorUp->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_kFactorUp->Scale(kfact_ZJetsToNuNu_HT100To200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_kFactorDown  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_ZJetsToNuNu_HT100To200_kFactorDown->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_kFactorDown->Scale(kfact_ZJetsToNuNu_HT100To200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_TauIDSFUp  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_ZJetsToNuNu_HT100To200_TauIDSFUp->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_TauIDSFUp->Scale(kfact_ZJetsToNuNu_HT100To200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_TauIDSFDown  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_ZJetsToNuNu_HT100To200_TauIDSFDown->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_TauIDSFDown->Scale(kfact_ZJetsToNuNu_HT100To200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_TauIDSFflatUp  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_ZJetsToNuNu_HT100To200_TauIDSFflatUp->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_TauIDSFflatUp->Scale(kfact_ZJetsToNuNu_HT100To200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_TauIDSFflatDown  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_ZJetsToNuNu_HT100To200_TauIDSFflatDown->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_TauIDSFflatDown->Scale(kfact_ZJetsToNuNu_HT100To200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_TauELESFUp  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_ZJetsToNuNu_HT100To200_TauELESFUp->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_TauELESFUp->Scale(kfact_ZJetsToNuNu_HT100To200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_TauELESFDown  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_ZJetsToNuNu_HT100To200_TauELESFDown->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_TauELESFDown->Scale(kfact_ZJetsToNuNu_HT100To200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_trigSFUp  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_ZJetsToNuNu_HT100To200_trigSFUp->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_trigSFUp->Scale(kfact_ZJetsToNuNu_HT100To200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_trigSFDown  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_ZJetsToNuNu_HT100To200_trigSFDown->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_trigSFDown->Scale(kfact_ZJetsToNuNu_HT100To200);
  //
  /*
  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_pdfUncertUp  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_ZJetsToNuNu_HT100To200_pdfUncertUp->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_pdfUncertUp->Scale(kfact_ZJetsToNuNu_HT100To200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200_pdfUncertDown  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_ZJetsToNuNu_HT100To200_pdfUncertDown->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200_pdfUncertDown->Scale(kfact_ZJetsToNuNu_HT100To200);
  */  //

  //file_ZJetsToNuNu_HT200To400
  TH1D* h1_evt_ZJetsToNuNu_HT200To400 = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT200To400 = h1_evt_ZJetsToNuNu_HT200To400->GetEntries(); //Integral();                                                                  
  double wt_ZJetsToNuNu_HT200To400 = (xs_ZJetsToNuNu_HT200To400*lumi)/evt_ZJetsToNuNu_HT200To400 ;
  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);
  //std::cout << mT_Stage1_ZJetsToNuNu_HT200To400->GetBinError(600) << std::endl;
  std::cout << "ZJetsToNuNu_HT200To400 weighted nevt=" << mT_Stage1_ZJetsToNuNu_HT200To400->Integral() << std::endl;
  totalMC +=  mT_Stage1_ZJetsToNuNu_HT200To400->Integral();
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_JetEnUp  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_ZJetsToNuNu_HT200To400_JetEnUp->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_JetEnUp->Scale(kfact_ZJetsToNuNu_HT200To400);

  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_JetEnDown  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_ZJetsToNuNu_HT200To400_JetEnDown->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_JetEnDown->Scale(kfact_ZJetsToNuNu_HT200To400);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_JetResUp  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_ZJetsToNuNu_HT200To400_JetResUp->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_JetResUp->Scale(kfact_ZJetsToNuNu_HT200To400);

  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_JetResDown  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_ZJetsToNuNu_HT200To400_JetResDown->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_JetResDown->Scale(kfact_ZJetsToNuNu_HT200To400);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_MuonEnUp  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_ZJetsToNuNu_HT200To400_MuonEnUp->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_MuonEnUp->Scale(kfact_ZJetsToNuNu_HT200To400);

  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_MuonEnDown  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_ZJetsToNuNu_HT200To400_MuonEnDown->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_MuonEnDown->Scale(kfact_ZJetsToNuNu_HT200To400);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_ElectronEnUp  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_ZJetsToNuNu_HT200To400_ElectronEnUp->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_ElectronEnUp->Scale(kfact_ZJetsToNuNu_HT200To400);

  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_ElectronEnDown  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_ZJetsToNuNu_HT200To400_ElectronEnDown->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_ElectronEnDown->Scale(kfact_ZJetsToNuNu_HT200To400);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_TauEnUp  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_ZJetsToNuNu_HT200To400_TauEnUp->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_TauEnUp->Scale(kfact_ZJetsToNuNu_HT200To400);

  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_TauEnDown  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_ZJetsToNuNu_HT200To400_TauEnDown->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_TauEnDown->Scale(kfact_ZJetsToNuNu_HT200To400);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_PhotonEnUp  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_ZJetsToNuNu_HT200To400_PhotonEnUp->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_PhotonEnUp->Scale(kfact_ZJetsToNuNu_HT200To400);

  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_PhotonEnDown  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_ZJetsToNuNu_HT200To400_PhotonEnDown->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_PhotonEnDown->Scale(kfact_ZJetsToNuNu_HT200To400);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_UnclusteredEnUp  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_ZJetsToNuNu_HT200To400_UnclusteredEnUp->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_UnclusteredEnUp->Scale(kfact_ZJetsToNuNu_HT200To400);

  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_UnclusteredEnDown  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_ZJetsToNuNu_HT200To400_UnclusteredEnDown->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_UnclusteredEnDown->Scale(kfact_ZJetsToNuNu_HT200To400);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_TauScaleUp  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_ZJetsToNuNu_HT200To400_TauScaleUp->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_TauScaleUp->Scale(kfact_ZJetsToNuNu_HT200To400);

  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_TauScaleDown  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_ZJetsToNuNu_HT200To400_TauScaleDown->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_TauScaleDown->Scale(kfact_ZJetsToNuNu_HT200To400);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_pileupUncertUp  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_ZJetsToNuNu_HT200To400_pileupUncertUp->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_pileupUncertUp->Scale(kfact_ZJetsToNuNu_HT200To400);

  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_pileupUncertDown  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_ZJetsToNuNu_HT200To400_pileupUncertDown->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_pileupUncertDown->Scale(kfact_ZJetsToNuNu_HT200To400);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_kFactorUp  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_ZJetsToNuNu_HT200To400_kFactorUp->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_kFactorUp->Scale(kfact_ZJetsToNuNu_HT200To400);

  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_kFactorDown  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_ZJetsToNuNu_HT200To400_kFactorDown->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_kFactorDown->Scale(kfact_ZJetsToNuNu_HT200To400);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_TauIDSFUp  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_ZJetsToNuNu_HT200To400_TauIDSFUp->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_TauIDSFUp->Scale(kfact_ZJetsToNuNu_HT200To400);

  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_TauIDSFDown  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_ZJetsToNuNu_HT200To400_TauIDSFDown->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_TauIDSFDown->Scale(kfact_ZJetsToNuNu_HT200To400);
  //

  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_TauIDSFflatUp  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_ZJetsToNuNu_HT200To400_TauIDSFflatUp->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_TauIDSFflatUp->Scale(kfact_ZJetsToNuNu_HT200To400);

  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_TauIDSFflatDown  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_ZJetsToNuNu_HT200To400_TauIDSFflatDown->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_TauIDSFflatDown->Scale(kfact_ZJetsToNuNu_HT200To400);

  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_TauELESFUp  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_ZJetsToNuNu_HT200To400_TauELESFUp->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_TauELESFUp->Scale(kfact_ZJetsToNuNu_HT200To400);

  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_TauELESFDown  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_ZJetsToNuNu_HT200To400_TauELESFDown->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_TauELESFDown->Scale(kfact_ZJetsToNuNu_HT200To400);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_trigSFUp  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_ZJetsToNuNu_HT200To400_trigSFUp->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_trigSFUp->Scale(kfact_ZJetsToNuNu_HT200To400);

  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_trigSFDown  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_ZJetsToNuNu_HT200To400_trigSFDown->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_trigSFDown->Scale(kfact_ZJetsToNuNu_HT200To400);
  //
  /*
  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_pdfUncertUp  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_ZJetsToNuNu_HT200To400_pdfUncertUp->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_pdfUncertUp->Scale(kfact_ZJetsToNuNu_HT200To400);

  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400_pdfUncertDown  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_ZJetsToNuNu_HT200To400_pdfUncertDown->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400_pdfUncertDown->Scale(kfact_ZJetsToNuNu_HT200To400);
  */  //


  //file_ZJetsToNuNu_HT400To600
  TH1D* h1_evt_ZJetsToNuNu_HT400To600 = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT400To600 = h1_evt_ZJetsToNuNu_HT400To600->GetEntries(); //Integral();                                                                  
  double wt_ZJetsToNuNu_HT400To600 = (xs_ZJetsToNuNu_HT400To600*lumi)/evt_ZJetsToNuNu_HT400To600 ;
  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);
  //  std::cout << mT_Stage1_ZJetsToNuNu_HT400To600->GetBinError(600) << std::endl;
  std::cout << "ZJetsToNuNu_HT400To600 weighted nevt=" << mT_Stage1_ZJetsToNuNu_HT400To600->Integral() << std::endl;
  totalMC += mT_Stage1_ZJetsToNuNu_HT400To600->Integral();
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_JetEnUp  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_ZJetsToNuNu_HT400To600_JetEnUp->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_JetEnUp->Scale(kfact_ZJetsToNuNu_HT400To600);

  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_JetEnDown  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_ZJetsToNuNu_HT400To600_JetEnDown->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_JetEnDown->Scale(kfact_ZJetsToNuNu_HT400To600);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_JetResUp  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_ZJetsToNuNu_HT400To600_JetResUp->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_JetResUp->Scale(kfact_ZJetsToNuNu_HT400To600);

  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_JetResDown  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_ZJetsToNuNu_HT400To600_JetResDown->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_JetResDown->Scale(kfact_ZJetsToNuNu_HT400To600);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_MuonEnUp  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_ZJetsToNuNu_HT400To600_MuonEnUp->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_MuonEnUp->Scale(kfact_ZJetsToNuNu_HT400To600);

  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_MuonEnDown  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_ZJetsToNuNu_HT400To600_MuonEnDown->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_MuonEnDown->Scale(kfact_ZJetsToNuNu_HT400To600);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_ElectronEnUp  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_ZJetsToNuNu_HT400To600_ElectronEnUp->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_ElectronEnUp->Scale(kfact_ZJetsToNuNu_HT400To600);

  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_ElectronEnDown  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_ZJetsToNuNu_HT400To600_ElectronEnDown->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_ElectronEnDown->Scale(kfact_ZJetsToNuNu_HT400To600);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_TauEnUp  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_ZJetsToNuNu_HT400To600_TauEnUp->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_TauEnUp->Scale(kfact_ZJetsToNuNu_HT400To600);

  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_TauEnDown  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_ZJetsToNuNu_HT400To600_TauEnDown->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_TauEnDown->Scale(kfact_ZJetsToNuNu_HT400To600);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_PhotonEnUp  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_ZJetsToNuNu_HT400To600_PhotonEnUp->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_PhotonEnUp->Scale(kfact_ZJetsToNuNu_HT400To600);

  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_PhotonEnDown  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_ZJetsToNuNu_HT400To600_PhotonEnDown->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_PhotonEnDown->Scale(kfact_ZJetsToNuNu_HT400To600);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_UnclusteredEnUp  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_ZJetsToNuNu_HT400To600_UnclusteredEnUp->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_UnclusteredEnUp->Scale(kfact_ZJetsToNuNu_HT400To600);

  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_UnclusteredEnDown  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_ZJetsToNuNu_HT400To600_UnclusteredEnDown->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_UnclusteredEnDown->Scale(kfact_ZJetsToNuNu_HT400To600);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_TauScaleUp  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_ZJetsToNuNu_HT400To600_TauScaleUp->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_TauScaleUp->Scale(kfact_ZJetsToNuNu_HT400To600);

  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_TauScaleDown  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_ZJetsToNuNu_HT400To600_TauScaleDown->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_TauScaleDown->Scale(kfact_ZJetsToNuNu_HT400To600);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_pileupUncertUp  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_ZJetsToNuNu_HT400To600_pileupUncertUp->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_pileupUncertUp->Scale(kfact_ZJetsToNuNu_HT400To600);

  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_pileupUncertDown  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_ZJetsToNuNu_HT400To600_pileupUncertDown->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_pileupUncertDown->Scale(kfact_ZJetsToNuNu_HT400To600);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_kFactorUp  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_ZJetsToNuNu_HT400To600_kFactorUp->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_kFactorUp->Scale(kfact_ZJetsToNuNu_HT400To600);

  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_kFactorDown  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_ZJetsToNuNu_HT400To600_kFactorDown->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_kFactorDown->Scale(kfact_ZJetsToNuNu_HT400To600);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_TauIDSFUp  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_ZJetsToNuNu_HT400To600_TauIDSFUp->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_TauIDSFUp->Scale(kfact_ZJetsToNuNu_HT400To600);

  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_TauIDSFDown  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_ZJetsToNuNu_HT400To600_TauIDSFDown->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_TauIDSFDown->Scale(kfact_ZJetsToNuNu_HT400To600);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_TauIDSFflatUp  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_ZJetsToNuNu_HT400To600_TauIDSFflatUp->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_TauIDSFflatUp->Scale(kfact_ZJetsToNuNu_HT400To600);

  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_TauIDSFflatDown  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_ZJetsToNuNu_HT400To600_TauIDSFflatDown->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_TauIDSFflatDown->Scale(kfact_ZJetsToNuNu_HT400To600);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_TauELESFUp  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_ZJetsToNuNu_HT400To600_TauELESFUp->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_TauELESFUp->Scale(kfact_ZJetsToNuNu_HT400To600);

  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_TauELESFDown  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_ZJetsToNuNu_HT400To600_TauELESFDown->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_TauELESFDown->Scale(kfact_ZJetsToNuNu_HT400To600);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_trigSFUp  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_ZJetsToNuNu_HT400To600_trigSFUp->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_trigSFUp->Scale(kfact_ZJetsToNuNu_HT400To600);

  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_trigSFDown  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_ZJetsToNuNu_HT400To600_trigSFDown->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_trigSFDown->Scale(kfact_ZJetsToNuNu_HT400To600);
  //
  /*
  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_pdfUncertUp  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_ZJetsToNuNu_HT400To600_pdfUncertUp->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_pdfUncertUp->Scale(kfact_ZJetsToNuNu_HT400To600);

  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600_pdfUncertDown  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_ZJetsToNuNu_HT400To600_pdfUncertDown->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600_pdfUncertDown->Scale(kfact_ZJetsToNuNu_HT400To600);
  */  //



  //file_ZJetsToNuNu_HT600To800
  TH1D* h1_evt_ZJetsToNuNu_HT600To800 = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT600To800 = h1_evt_ZJetsToNuNu_HT600To800->GetEntries(); //Integral();                                                                  
  double wt_ZJetsToNuNu_HT600To800 = (xs_ZJetsToNuNu_HT600To800*lumi)/evt_ZJetsToNuNu_HT600To800 ;
  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800->Scale(kfact_ZJetsToNuNu_HT600To800);
  //  std::cout << mT_Stage1_ZJetsToNuNu_HT600To800->GetBinError(600) << std::endl;
  std::cout << "ZJetsToNuNu_HT600To800 weighted nevt=" << mT_Stage1_ZJetsToNuNu_HT600To800->Integral() << std::endl;
  totalMC += mT_Stage1_ZJetsToNuNu_HT600To800->Integral() ;
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_JetEnUp  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_ZJetsToNuNu_HT600To800_JetEnUp->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_JetEnUp->Scale(kfact_ZJetsToNuNu_HT600To800);

  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_JetEnDown  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_ZJetsToNuNu_HT600To800_JetEnDown->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_JetEnDown->Scale(kfact_ZJetsToNuNu_HT600To800);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_JetResUp  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_ZJetsToNuNu_HT600To800_JetResUp->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_JetResUp->Scale(kfact_ZJetsToNuNu_HT600To800);

  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_JetResDown  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_ZJetsToNuNu_HT600To800_JetResDown->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_JetResDown->Scale(kfact_ZJetsToNuNu_HT600To800);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_MuonEnUp  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_ZJetsToNuNu_HT600To800_MuonEnUp->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_MuonEnUp->Scale(kfact_ZJetsToNuNu_HT600To800);

  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_MuonEnDown  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_ZJetsToNuNu_HT600To800_MuonEnDown->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_MuonEnDown->Scale(kfact_ZJetsToNuNu_HT600To800);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_ElectronEnUp  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_ZJetsToNuNu_HT600To800_ElectronEnUp->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_ElectronEnUp->Scale(kfact_ZJetsToNuNu_HT600To800);

  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_ElectronEnDown  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_ZJetsToNuNu_HT600To800_ElectronEnDown->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_ElectronEnDown->Scale(kfact_ZJetsToNuNu_HT600To800);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_TauEnUp  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_ZJetsToNuNu_HT600To800_TauEnUp->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_TauEnUp->Scale(kfact_ZJetsToNuNu_HT600To800);

  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_TauEnDown  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_ZJetsToNuNu_HT600To800_TauEnDown->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_TauEnDown->Scale(kfact_ZJetsToNuNu_HT600To800);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_PhotonEnUp  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_ZJetsToNuNu_HT600To800_PhotonEnUp->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_PhotonEnUp->Scale(kfact_ZJetsToNuNu_HT600To800);

  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_PhotonEnDown  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_ZJetsToNuNu_HT600To800_PhotonEnDown->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_PhotonEnDown->Scale(kfact_ZJetsToNuNu_HT600To800);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_UnclusteredEnUp  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_ZJetsToNuNu_HT600To800_UnclusteredEnUp->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_UnclusteredEnUp->Scale(kfact_ZJetsToNuNu_HT600To800);

  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_UnclusteredEnDown  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_ZJetsToNuNu_HT600To800_UnclusteredEnDown->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_UnclusteredEnDown->Scale(kfact_ZJetsToNuNu_HT600To800);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_TauScaleUp  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_ZJetsToNuNu_HT600To800_TauScaleUp->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_TauScaleUp->Scale(kfact_ZJetsToNuNu_HT600To800);

  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_TauScaleDown  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_ZJetsToNuNu_HT600To800_TauScaleDown->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_TauScaleDown->Scale(kfact_ZJetsToNuNu_HT600To800);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_pileupUncertUp  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_ZJetsToNuNu_HT600To800_pileupUncertUp->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_pileupUncertUp->Scale(kfact_ZJetsToNuNu_HT600To800);

  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_pileupUncertDown  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_ZJetsToNuNu_HT600To800_pileupUncertDown->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_pileupUncertDown->Scale(kfact_ZJetsToNuNu_HT600To800);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_kFactorUp  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_ZJetsToNuNu_HT600To800_kFactorUp->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_kFactorUp->Scale(kfact_ZJetsToNuNu_HT600To800);

  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_kFactorDown  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_ZJetsToNuNu_HT600To800_kFactorDown->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_kFactorDown->Scale(kfact_ZJetsToNuNu_HT600To800);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_TauIDSFUp  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_ZJetsToNuNu_HT600To800_TauIDSFUp->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_TauIDSFUp->Scale(kfact_ZJetsToNuNu_HT600To800);

  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_TauIDSFDown  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_ZJetsToNuNu_HT600To800_TauIDSFDown->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_TauIDSFDown->Scale(kfact_ZJetsToNuNu_HT600To800);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_TauIDSFflatUp  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_ZJetsToNuNu_HT600To800_TauIDSFflatUp->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_TauIDSFflatUp->Scale(kfact_ZJetsToNuNu_HT600To800);

  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_TauIDSFflatDown  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_ZJetsToNuNu_HT600To800_TauIDSFflatDown->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_TauIDSFflatDown->Scale(kfact_ZJetsToNuNu_HT600To800);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_TauELESFUp  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_ZJetsToNuNu_HT600To800_TauELESFUp->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_TauELESFUp->Scale(kfact_ZJetsToNuNu_HT600To800);

  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_TauELESFDown  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_ZJetsToNuNu_HT600To800_TauELESFDown->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_TauELESFDown->Scale(kfact_ZJetsToNuNu_HT600To800);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_trigSFUp  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_ZJetsToNuNu_HT600To800_trigSFUp->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_trigSFUp->Scale(kfact_ZJetsToNuNu_HT600To800);

  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_trigSFDown  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_ZJetsToNuNu_HT600To800_trigSFDown->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_trigSFDown->Scale(kfact_ZJetsToNuNu_HT600To800);
  //
  /*
  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_pdfUncertUp  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_ZJetsToNuNu_HT600To800_pdfUncertUp->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_pdfUncertUp->Scale(kfact_ZJetsToNuNu_HT600To800);

  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800_pdfUncertDown  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_ZJetsToNuNu_HT600To800_pdfUncertDown->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_ZJetsToNuNu_HT600To800_pdfUncertDown->Scale(kfact_ZJetsToNuNu_HT600To800);
  */ //


  //file_ZJetsToNuNu_HT800To1200
  TH1D* h1_evt_ZJetsToNuNu_HT800To1200 = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT800To1200 = h1_evt_ZJetsToNuNu_HT800To1200->GetEntries(); //Integral();                                                            
  double wt_ZJetsToNuNu_HT800To1200 = (xs_ZJetsToNuNu_HT800To1200*lumi)/evt_ZJetsToNuNu_HT800To1200 ;
  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //std::cout << mT_Stage1_ZJetsToNuNu_HT800To1200->GetBinError(600) << std::endl;
  std::cout << "ZJetsToNuNu_HT800To1200 weighted nevt=" << mT_Stage1_ZJetsToNuNu_HT800To1200->Integral() << std::endl;
  totalMC += mT_Stage1_ZJetsToNuNu_HT800To1200->Integral() ;
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_JetEnUp  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_ZJetsToNuNu_HT800To1200_JetEnUp->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_JetEnUp->Scale(kfact_ZJetsToNuNu_HT800To1200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_JetEnDown  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_ZJetsToNuNu_HT800To1200_JetEnDown->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_JetEnDown->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_JetResUp  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_ZJetsToNuNu_HT800To1200_JetResUp->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_JetResUp->Scale(kfact_ZJetsToNuNu_HT800To1200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_JetResDown  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_ZJetsToNuNu_HT800To1200_JetResDown->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_JetResDown->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_MuonEnUp  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_ZJetsToNuNu_HT800To1200_MuonEnUp->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_MuonEnUp->Scale(kfact_ZJetsToNuNu_HT800To1200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_MuonEnDown  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_ZJetsToNuNu_HT800To1200_MuonEnDown->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_MuonEnDown->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_ElectronEnUp  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_ZJetsToNuNu_HT800To1200_ElectronEnUp->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_ElectronEnUp->Scale(kfact_ZJetsToNuNu_HT800To1200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_ElectronEnDown  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_ZJetsToNuNu_HT800To1200_ElectronEnDown->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_ElectronEnDown->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_TauEnUp  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauEnUp->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauEnUp->Scale(kfact_ZJetsToNuNu_HT800To1200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_TauEnDown  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauEnDown->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauEnDown->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_PhotonEnUp  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_ZJetsToNuNu_HT800To1200_PhotonEnUp->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_PhotonEnUp->Scale(kfact_ZJetsToNuNu_HT800To1200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_PhotonEnDown  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_ZJetsToNuNu_HT800To1200_PhotonEnDown->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_PhotonEnDown->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_UnclusteredEnUp  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_ZJetsToNuNu_HT800To1200_UnclusteredEnUp->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_UnclusteredEnUp->Scale(kfact_ZJetsToNuNu_HT800To1200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_UnclusteredEnDown  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_ZJetsToNuNu_HT800To1200_UnclusteredEnDown->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_UnclusteredEnDown->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_TauScaleUp  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauScaleUp->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauScaleUp->Scale(kfact_ZJetsToNuNu_HT800To1200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_TauScaleDown  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauScaleDown->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauScaleDown->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_pileupUncertUp  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_ZJetsToNuNu_HT800To1200_pileupUncertUp->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_pileupUncertUp->Scale(kfact_ZJetsToNuNu_HT800To1200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_pileupUncertDown  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_ZJetsToNuNu_HT800To1200_pileupUncertDown->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_pileupUncertDown->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_kFactorUp  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_ZJetsToNuNu_HT800To1200_kFactorUp->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_kFactorUp->Scale(kfact_ZJetsToNuNu_HT800To1200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_kFactorDown  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_ZJetsToNuNu_HT800To1200_kFactorDown->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_kFactorDown->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_TauIDSFUp  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauIDSFUp->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauIDSFUp->Scale(kfact_ZJetsToNuNu_HT800To1200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_TauIDSFDown  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauIDSFDown->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauIDSFDown->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_TauIDSFflatUp  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauIDSFflatUp->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauIDSFflatUp->Scale(kfact_ZJetsToNuNu_HT800To1200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_TauIDSFflatDown  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauIDSFflatDown->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauIDSFflatDown->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_TauELESFUp  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauELESFUp->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauELESFUp->Scale(kfact_ZJetsToNuNu_HT800To1200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_TauELESFDown  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauELESFDown->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_TauELESFDown->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_trigSFUp  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_ZJetsToNuNu_HT800To1200_trigSFUp->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_trigSFUp->Scale(kfact_ZJetsToNuNu_HT800To1200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_trigSFDown  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_ZJetsToNuNu_HT800To1200_trigSFDown->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_trigSFDown->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //
  /*
  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_pdfUncertUp  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_ZJetsToNuNu_HT800To1200_pdfUncertUp->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_pdfUncertUp->Scale(kfact_ZJetsToNuNu_HT800To1200);

  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200_pdfUncertDown  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_ZJetsToNuNu_HT800To1200_pdfUncertDown->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_ZJetsToNuNu_HT800To1200_pdfUncertDown->Scale(kfact_ZJetsToNuNu_HT800To1200);
  */ //


  //file_ZJetsToNuNu_HT1200To2500
  TH1D* h1_evt_ZJetsToNuNu_HT1200To2500 = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT1200To2500 = h1_evt_ZJetsToNuNu_HT1200To2500->GetEntries(); //Integral();                                                             
  double wt_ZJetsToNuNu_HT1200To2500 = (xs_ZJetsToNuNu_HT1200To2500*lumi)/evt_ZJetsToNuNu_HT1200To2500 ;
  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //std::cout << mT_Stage1_ZJetsToNuNu_HT1200To2500->GetBinError(600) << std::endl;
  std::cout << "ZJetsToNuNu_HT1200To2500 weighted nevt=" << mT_Stage1_ZJetsToNuNu_HT1200To2500->Integral() << std::endl;
  totalMC += mT_Stage1_ZJetsToNuNu_HT1200To2500->Integral() ;
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_JetEnUp  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_JetEnUp->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_JetEnUp->Scale(kfact_ZJetsToNuNu_HT1200To2500);

  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_JetEnDown  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_JetEnDown->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_JetEnDown->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_JetResUp  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_JetResUp->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_JetResUp->Scale(kfact_ZJetsToNuNu_HT1200To2500);

  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_JetResDown  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_JetResDown->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_JetResDown->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_MuonEnUp  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_MuonEnUp->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_MuonEnUp->Scale(kfact_ZJetsToNuNu_HT1200To2500);

  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_MuonEnDown  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_MuonEnDown->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_MuonEnDown->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_ElectronEnUp  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_ElectronEnUp->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_ElectronEnUp->Scale(kfact_ZJetsToNuNu_HT1200To2500);

  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_ElectronEnDown  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_ElectronEnDown->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_ElectronEnDown->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_TauEnUp  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauEnUp->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauEnUp->Scale(kfact_ZJetsToNuNu_HT1200To2500);

  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_TauEnDown  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauEnDown->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauEnDown->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_PhotonEnUp  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_PhotonEnUp->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_PhotonEnUp->Scale(kfact_ZJetsToNuNu_HT1200To2500);

  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_PhotonEnDown  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_PhotonEnDown->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_PhotonEnDown->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_UnclusteredEnUp  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_UnclusteredEnUp->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_UnclusteredEnUp->Scale(kfact_ZJetsToNuNu_HT1200To2500);

  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_UnclusteredEnDown  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_UnclusteredEnDown->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_UnclusteredEnDown->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_TauScaleUp  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauScaleUp->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauScaleUp->Scale(kfact_ZJetsToNuNu_HT1200To2500);

  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_TauScaleDown  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauScaleDown->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauScaleDown->Scale(kfact_ZJetsToNuNu_HT1200To2500);
   //
  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_pileupUncertUp  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_pileupUncertUp->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_pileupUncertUp->Scale(kfact_ZJetsToNuNu_HT1200To2500);

  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_pileupUncertDown  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_pileupUncertDown->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_pileupUncertDown->Scale(kfact_ZJetsToNuNu_HT1200To2500);

  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_kFactorUp  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_kFactorUp->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_kFactorUp->Scale(kfact_ZJetsToNuNu_HT1200To2500);

  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_kFactorDown  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_kFactorDown->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_kFactorDown->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_TauIDSFUp  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauIDSFUp->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauIDSFUp->Scale(kfact_ZJetsToNuNu_HT1200To2500);

  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_TauIDSFDown  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauIDSFDown->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauIDSFDown->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_TauIDSFflatUp  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauIDSFflatUp->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauIDSFflatUp->Scale(kfact_ZJetsToNuNu_HT1200To2500);

  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_TauIDSFflatDown  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauIDSFflatDown->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauIDSFflatDown->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_TauELESFUp  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauELESFUp->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauELESFUp->Scale(kfact_ZJetsToNuNu_HT1200To2500);

  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_TauELESFDown  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauELESFDown->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_TauELESFDown->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_trigSFUp  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_trigSFUp->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_trigSFUp->Scale(kfact_ZJetsToNuNu_HT1200To2500);

  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_trigSFDown  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_trigSFDown->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_trigSFDown->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //
  /*
  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_pdfUncertUp  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_pdfUncertUp->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_pdfUncertUp->Scale(kfact_ZJetsToNuNu_HT1200To2500);

  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500_pdfUncertDown  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_ZJetsToNuNu_HT1200To2500_pdfUncertDown->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_ZJetsToNuNu_HT1200To2500_pdfUncertDown->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  */ //

  //file_ZJetsToNuNu_HT2500ToInf
  TH1D* h1_evt_ZJetsToNuNu_HT2500ToInf = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT2500ToInf = h1_evt_ZJetsToNuNu_HT2500ToInf->GetEntries(); //Integral();                                                         
  double wt_ZJetsToNuNu_HT2500ToInf = (xs_ZJetsToNuNu_HT2500ToInf*lumi)/evt_ZJetsToNuNu_HT2500ToInf ;
  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  // std::cout << mT_Stage1_ZJetsToNuNu_HT2500ToInf->GetBinError(600) << std::endl;
  std::cout << "ZJetsToNuNu_HT2500ToInf weighted nevt=" << mT_Stage1_ZJetsToNuNu_HT2500ToInf->Integral() << std::endl;
  totalMC += mT_Stage1_ZJetsToNuNu_HT2500ToInf->Integral();
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_JetEnUp  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_JetEnUp->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_JetEnUp->Scale(kfact_ZJetsToNuNu_HT2500ToInf);

  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_JetEnDown  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_JetEnDown->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_JetEnDown->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_JetResUp  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_JetResUp->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_JetResUp->Scale(kfact_ZJetsToNuNu_HT2500ToInf);

  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_JetResDown  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_JetResDown->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_JetResDown->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_MuonEnUp  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_MuonEnUp->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_MuonEnUp->Scale(kfact_ZJetsToNuNu_HT2500ToInf);

  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_MuonEnDown  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_MuonEnDown->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_MuonEnDown->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_ElectronEnUp  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_ElectronEnUp->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_ElectronEnUp->Scale(kfact_ZJetsToNuNu_HT2500ToInf);

  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_ElectronEnDown  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_ElectronEnDown->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_ElectronEnDown->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauEnUp  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauEnUp->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauEnUp->Scale(kfact_ZJetsToNuNu_HT2500ToInf);

  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauEnDown  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauEnDown->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauEnDown->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_PhotonEnUp  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_PhotonEnUp->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_PhotonEnUp->Scale(kfact_ZJetsToNuNu_HT2500ToInf);

  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_PhotonEnDown  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_PhotonEnDown->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_PhotonEnDown->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_UnclusteredEnUp  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_UnclusteredEnUp->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_UnclusteredEnUp->Scale(kfact_ZJetsToNuNu_HT2500ToInf);

  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_UnclusteredEnDown  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_UnclusteredEnDown->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_UnclusteredEnDown->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauScaleUp  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_TauScaleUp");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauScaleUp->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauScaleUp->Scale(kfact_ZJetsToNuNu_HT2500ToInf);

  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauScaleDown  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_TauScaleDown");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauScaleDown->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauScaleDown->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_pileupUncertUp  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_pileupUncertUp");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_pileupUncertUp->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_pileupUncertUp->Scale(kfact_ZJetsToNuNu_HT2500ToInf);

  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_pileupUncertDown  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_pileupUncertDown");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_pileupUncertDown->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_pileupUncertDown->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_kFactorUp  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_kFactorUp");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_kFactorUp->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_kFactorUp->Scale(kfact_ZJetsToNuNu_HT2500ToInf);

  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_kFactorDown  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_kFactorDown");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_kFactorDown->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_kFactorDown->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauIDSFUp  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Up");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauIDSFUp->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauIDSFUp->Scale(kfact_ZJetsToNuNu_HT2500ToInf);

  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauIDSFDown  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_TauIDSF_ptDep_Down");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauIDSFDown->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauIDSFDown->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauIDSFflatUp  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Up");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauIDSFflatUp->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauIDSFflatUp->Scale(kfact_ZJetsToNuNu_HT2500ToInf);

  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauIDSFflatDown  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_TauIDSF_flat_Down");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauIDSFflatDown->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauIDSFflatDown->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauELESFUp  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_TauELESFUp");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauELESFUp->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauELESFUp->Scale(kfact_ZJetsToNuNu_HT2500ToInf);

  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauELESFDown  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_TauELESFDown");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauELESFDown->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauELESFDown->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //
  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_trigSFUp  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_trigSFUp");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_trigSFUp->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_trigSFUp->Scale(kfact_ZJetsToNuNu_HT2500ToInf);

  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_trigSFDown  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_trigSFDown");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_trigSFDown->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_trigSFDown->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //
  /*
  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_pdfUncertUp  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_pdfUncertUp");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_pdfUncertUp->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_pdfUncertUp->Scale(kfact_ZJetsToNuNu_HT2500ToInf);

  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf_pdfUncertDown  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/histoDir/mT_Stage1_pdfUncertDown");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_pdfUncertDown->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_ZJetsToNuNu_HT2500ToInf_pdfUncertDown->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  */  //

  TH1D* total_QCD = (TH1D*)mT_Stage1_QCD_HT200to300->Clone();
  total_QCD->Add(mT_Stage1_QCD_HT300to500);
  total_QCD->Add(mT_Stage1_QCD_HT500to700);
  total_QCD->Add(mT_Stage1_QCD_HT700to1000);
  total_QCD->Add(mT_Stage1_QCD_HT1000to1500);
  total_QCD->Add(mT_Stage1_QCD_HT1500to2000);
  total_QCD->Add(mT_Stage1_QCD_HT2000toInf);
  /*
  total_QCD->Add(mT_Stage1_ZJetsToNuNu_HT100To200);
  total_QCD->Add(mT_Stage1_ZJetsToNuNu_HT200To400);
  total_QCD->Add(mT_Stage1_ZJetsToNuNu_HT400To600);
  total_QCD->Add(mT_Stage1_ZJetsToNuNu_HT600To800);
  total_QCD->Add(mT_Stage1_ZJetsToNuNu_HT800To1200);
  total_QCD->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500);
  total_QCD->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf);
  */
  TH1D* total_ZJets = (TH1D*)mT_Stage1_ZJetsToNuNu_HT100To200->Clone();
  total_ZJets->Add(mT_Stage1_ZJetsToNuNu_HT200To400);
  total_ZJets->Add(mT_Stage1_ZJetsToNuNu_HT400To600);
  total_ZJets->Add(mT_Stage1_ZJetsToNuNu_HT600To800);
  total_ZJets->Add(mT_Stage1_ZJetsToNuNu_HT800To1200);
  total_ZJets->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500);
  total_ZJets->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf);
  //*/
 
  total_ZJets->SetFillColorAlpha(kPink+1,0.5);
  total_ZJets->SetLineColor(kBlack);
  total_ZJets->Rebin(80);
 
  total_QCD->SetFillColorAlpha(kYellow-9,0.5);
  total_QCD->SetLineColor(kBlack);
  total_QCD->Rebin(80);

  std::cout << "totalQCDMC =" << totalQCDMC << std::endl;
  std::cout << "totalMC =" << totalMC << std::endl;

   std::cout << "will do data" << std::endl;
  
  //--Data--//
   TH1D* mT_Stage1_Run2016F  = (TH1D*)file_Tau_Run2016F->Get("demo/histoDir/mT_Stage1");
   TH1D* mT_Stage1_Run2016E  = (TH1D*)file_Tau_Run2016E->Get("demo/histoDir/mT_Stage1");
   TH1D* mT_Stage1_Run2016D  = (TH1D*)file_Tau_Run2016D->Get("demo/histoDir/mT_Stage1");
   TH1D* mT_Stage1_Run2016C  = (TH1D*)file_Tau_Run2016C->Get("demo/histoDir/mT_Stage1");
   TH1D* mT_Stage1_Run2016B  = (TH1D*)file_Tau_Run2016B->Get("demo/histoDir/mT_Stage1");
   TH1D* mT_Stage1_Run2016G  = (TH1D*)file_Tau_Run2016G->Get("demo/histoDir/mT_Stage1");
   TH1D* mT_Stage1_Run2016H_v2  = (TH1D*)file_Tau_Run2016H_v2->Get("demo/histoDir/mT_Stage1");
   TH1D* mT_Stage1_Run2016H_v3  = (TH1D*)file_Tau_Run2016H_v3->Get("demo/histoDir/mT_Stage1");

   mT_Stage1_Run2016F->SetBinErrorOption(TH1::kPoisson);
   mT_Stage1_Run2016E->SetBinErrorOption(TH1::kPoisson);
   mT_Stage1_Run2016D->SetBinErrorOption(TH1::kPoisson);
   mT_Stage1_Run2016C->SetBinErrorOption(TH1::kPoisson);
   mT_Stage1_Run2016B->SetBinErrorOption(TH1::kPoisson);
   mT_Stage1_Run2016G->SetBinErrorOption(TH1::kPoisson);
   mT_Stage1_Run2016H_v2->SetBinErrorOption(TH1::kPoisson);
   mT_Stage1_Run2016H_v3->SetBinErrorOption(TH1::kPoisson);

   TH1D* mT_Stage1_Run2016all = (TH1D*)mT_Stage1_Run2016B->Clone();
   mT_Stage1_Run2016all->Add(mT_Stage1_Run2016C);
   mT_Stage1_Run2016all->Add(mT_Stage1_Run2016D);
   mT_Stage1_Run2016all->Add(mT_Stage1_Run2016E);
   mT_Stage1_Run2016all->Add(mT_Stage1_Run2016F);
   mT_Stage1_Run2016all->Add(mT_Stage1_Run2016G);
   mT_Stage1_Run2016all->Add(mT_Stage1_Run2016H_v2);
   mT_Stage1_Run2016all->Add(mT_Stage1_Run2016H_v3);

   mT_Stage1_Run2016all->SetMarkerStyle(20);
   mT_Stage1_Run2016all->SetMarkerColor(kBlack);
   mT_Stage1_Run2016all->SetLineColor(kBlack);
   mT_Stage1_Run2016all->Rebin(80);

   std::cout << "data  " << mT_Stage1_Run2016all->Integral() << std::endl;
  
  std::cout << "will do signal " << std::endl;
  //--Signal--//
  TH1D* h1_evt_Wprime_M4000 = (TH1D*)file_Wprime_M4000->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M4000 = h1_evt_Wprime_M4000->GetEntries(); //Integral();                                                                          
  // std::cout << "evt_Wprime_M1000 = " << evt_Wprime_M1000 << std::endl;
  double wt_Wprime_M4000 = (xs_Wprime_M4000*lumi)/evt_Wprime_M4000 ;
  TH1D* mT_Stage1_Wprime_M4000  = (TH1D*)file_Wprime_M4000->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M4000 : " << ( mT_Stage1_Wprime_M4000->GetEntries() / evt_Wprime_M4000 ) << std::endl;
  mT_Stage1_Wprime_M4000->Scale(wt_Wprime_M4000);
  //  mT_Stage1_Wprime_M1000->SetFillColorAlpha(kGreen-7,0.5);
  mT_Stage1_Wprime_M4000->SetLineColor(kMagenta);
  mT_Stage1_Wprime_M4000->SetLineWidth(3);
  mT_Stage1_Wprime_M4000->SetLineStyle(5);
  mT_Stage1_Wprime_M4000->Rebin(80);


  
  TH1D* h1_evt_Wprime_M600 = (TH1D*)file_Wprime_M600->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M600 = h1_evt_Wprime_M600->GetEntries(); //Integral();                                                                          
  // std::cout << "evt_Wprime_M1000 = " << evt_Wprime_M1000 << std::endl;
  double wt_Wprime_M600 = (xs_Wprime_M600*lumi)/evt_Wprime_M600 ;
  TH1D* mT_Stage1_Wprime_M600  = (TH1D*)file_Wprime_M600->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M600 : " << ( mT_Stage1_Wprime_M600->GetEntries() / evt_Wprime_M600 ) << std::endl;
  mT_Stage1_Wprime_M600->Scale(wt_Wprime_M600);
  //  mT_Stage1_Wprime_M1000->SetFillColorAlpha(kGreen-7,0.5);
  mT_Stage1_Wprime_M600->SetLineColor(kGreen+2);
  mT_Stage1_Wprime_M600->SetLineWidth(3);
  mT_Stage1_Wprime_M600->SetLineStyle(9);
  mT_Stage1_Wprime_M600->Rebin(80);
 

  TH1D* h1_evt_Wprime_M5000 = (TH1D*)file_Wprime_M5000->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M5000 = h1_evt_Wprime_M5000->GetEntries(); //Integral();                                                                          
  // std::cout << "evt_Wprime_M1000 = " << evt_Wprime_M1000 << std::endl;
  double wt_Wprime_M5000 = (xs_Wprime_M5000*lumi)/evt_Wprime_M5000 ;
  TH1D* mT_Stage1_Wprime_M5000  = (TH1D*)file_Wprime_M5000->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M5000 : " << ( mT_Stage1_Wprime_M5000->GetEntries() / evt_Wprime_M5000 ) << std::endl;
  mT_Stage1_Wprime_M5000->Scale(wt_Wprime_M5000);
  //  mT_Stage1_Wprime_M1000->SetFillColorAlpha(kGreen-7,0.5);
  mT_Stage1_Wprime_M5000->SetLineColor(kBlue);
  mT_Stage1_Wprime_M5000->SetLineWidth(3);
  mT_Stage1_Wprime_M5000->SetLineStyle(9);
  mT_Stage1_Wprime_M5000->Rebin(80);
 
  //--Plotting Styles//
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);
  //  gStyle->SetPadBottomMargin(0.12);  
  gStyle->SetPadBottomMargin(0.01);  
  gStyle->SetPadTopMargin(0.01);   
  gStyle->SetTitleXSize(0.04);
  gStyle->SetTitleXOffset(1.05);
  gStyle->SetTitleYSize(0.05);
  gStyle->SetTitleYOffset(1.05);

  //////// Output File /////////
  TFile* outputFile = new TFile("Out_mT_Stage1_Syst.root","RECREATE");
  outputFile->cd();


  TH1D* totalBkg = (TH1D*)mT_Stage1_DYJetsToLL_M50->Clone();
  totalBkg->Add(mT_Stage1_DYJetsToLL_M5to50);
  totalBkg->Add(mT_Stage1_TT);
  //  totalBkg->Add(mT_Stage1_TT_Mtt_700to1000);
  //  totalBkg->Add(mT_Stage1_TT_Mtt_1000toInf);
  totalBkg->Add(mT_Stage1_ST_tchannel_antitop);
  totalBkg->Add(mT_Stage1_ST_tchannel_top);
  totalBkg->Add(mT_Stage1_ST_tW_antitop);
  totalBkg->Add(mT_Stage1_ST_tW_top);
  totalBkg->Add(mT_Stage1_WJetsToLNu_HT100To200);
  totalBkg->Add(mT_Stage1_WJetsToLNu_HT200To400);
  totalBkg->Add(mT_Stage1_WJetsToLNu_HT400To600);
  totalBkg->Add(mT_Stage1_WJetsToLNu_HT600To800);
  totalBkg->Add(mT_Stage1_WJetsToLNu_HT800To1200);
  totalBkg->Add(mT_Stage1_WJetsToLNu_HT1200To2500);
  totalBkg->Add(mT_Stage1_WJetsToLNu_HT2500ToInf);
  totalBkg->Add(mT_Stage1_WToTauNu_M100);
  totalBkg->Add(mT_Stage1_WToTauNu_M200);
  totalBkg->Add(mT_Stage1_WToTauNu_M500);
  totalBkg->Add(mT_Stage1_WToTauNu_M1000);
  totalBkg->Add(mT_Stage1_WToTauNu_M2000);
  totalBkg->Add(mT_Stage1_WToTauNu_M3000);
  totalBkg->Add(mT_Stage1_WToTauNu_M4000);
  totalBkg->Add(mT_Stage1_WToTauNu_M5000);
  totalBkg->Add(mT_Stage1_WToTauNu_M6000);
  totalBkg->Add(mT_Stage1_WJetsToLNu);
  totalBkg->Add(mT_Stage1_WW);
  totalBkg->Add(mT_Stage1_WZ);
  totalBkg->Add(mT_Stage1_ZZ);
  totalBkg->Add(mT_Stage1_QCD_HT200to300);
  totalBkg->Add(mT_Stage1_QCD_HT300to500);
  totalBkg->Add(mT_Stage1_QCD_HT500to700);
  totalBkg->Add(mT_Stage1_QCD_HT700to1000);
  totalBkg->Add(mT_Stage1_QCD_HT1000to1500);
  totalBkg->Add(mT_Stage1_QCD_HT1500to2000);
  totalBkg->Add(mT_Stage1_QCD_HT2000toInf);
  totalBkg->Add(mT_Stage1_ZJetsToNuNu_HT100To200);
  totalBkg->Add(mT_Stage1_ZJetsToNuNu_HT200To400);
  totalBkg->Add(mT_Stage1_ZJetsToNuNu_HT400To600);
  totalBkg->Add(mT_Stage1_ZJetsToNuNu_HT600To800);
  totalBkg->Add(mT_Stage1_ZJetsToNuNu_HT800To1200);
  totalBkg->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500);
  totalBkg->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf);

  //wjets 
  TH1D* totalBkg_wjets = (TH1D*)mT_Stage1_WJetsToLNu_HT100To200->Clone();
  totalBkg_wjets->Add(mT_Stage1_WJetsToLNu_HT200To400);
  totalBkg_wjets->Add(mT_Stage1_WJetsToLNu_HT400To600);
  totalBkg_wjets->Add(mT_Stage1_WJetsToLNu_HT600To800);
  totalBkg_wjets->Add(mT_Stage1_WJetsToLNu_HT800To1200);
  totalBkg_wjets->Add(mT_Stage1_WJetsToLNu_HT1200To2500);
  totalBkg_wjets->Add(mT_Stage1_WJetsToLNu_HT2500ToInf);
  totalBkg_wjets->Add(mT_Stage1_WToTauNu_M100);
  totalBkg_wjets->Add(mT_Stage1_WToTauNu_M200);
  totalBkg_wjets->Add(mT_Stage1_WToTauNu_M500);
  totalBkg_wjets->Add(mT_Stage1_WToTauNu_M1000);
  totalBkg_wjets->Add(mT_Stage1_WToTauNu_M2000);
  totalBkg_wjets->Add(mT_Stage1_WToTauNu_M3000);
  totalBkg_wjets->Add(mT_Stage1_WToTauNu_M4000);
  totalBkg_wjets->Add(mT_Stage1_WToTauNu_M5000);
  totalBkg_wjets->Add(mT_Stage1_WToTauNu_M6000);
  totalBkg_wjets->Add(mT_Stage1_WJetsToLNu);

  TH1D* totalBkg_QCD = (TH1D*)mT_Stage1_QCD_HT200to300->Clone();
  totalBkg_QCD->Add(mT_Stage1_QCD_HT300to500);
  totalBkg_QCD->Add(mT_Stage1_QCD_HT500to700);
  totalBkg_QCD->Add(mT_Stage1_QCD_HT700to1000);
  totalBkg_QCD->Add(mT_Stage1_QCD_HT1000to1500);
  totalBkg_QCD->Add(mT_Stage1_QCD_HT1500to2000);
  totalBkg_QCD->Add(mT_Stage1_QCD_HT2000toInf);
  totalBkg_QCD->Add(mT_Stage1_ZJetsToNuNu_HT100To200);
  totalBkg_QCD->Add(mT_Stage1_ZJetsToNuNu_HT200To400);
  totalBkg_QCD->Add(mT_Stage1_ZJetsToNuNu_HT400To600);
  totalBkg_QCD->Add(mT_Stage1_ZJetsToNuNu_HT600To800);
  totalBkg_QCD->Add(mT_Stage1_ZJetsToNuNu_HT800To1200);
  totalBkg_QCD->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500);
  totalBkg_QCD->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf);


  TH1* c_totalBkg = totalBkg->GetCumulative(kFALSE);


  TH1D* totalBkg_JetEnUp = (TH1D*)mT_Stage1_DYJetsToLL_M50_JetEnUp->Clone();
  totalBkg_JetEnUp->Add(mT_Stage1_DYJetsToLL_M5to50_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_TT_JetEnUp);
  //  totalBkg_JetEnUp->Add(mT_Stage1_TT_Mtt_700to1000_JetEnUp);
  //  totalBkg_JetEnUp->Add(mT_Stage1_TT_Mtt_1000toInf_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_ST_tchannel_antitop_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_ST_tchannel_top_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_ST_tW_antitop_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_ST_tW_top_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_WJetsToLNu_HT100To200_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_WJetsToLNu_HT200To400_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_WJetsToLNu_HT400To600_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_WJetsToLNu_HT600To800_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_WJetsToLNu_HT800To1200_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_WJetsToLNu_HT1200To2500_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_WToTauNu_M100_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_WToTauNu_M200_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_WToTauNu_M500_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_WToTauNu_M1000_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_WToTauNu_M2000_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_WToTauNu_M3000_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_WToTauNu_M4000_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_WToTauNu_M5000_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_WToTauNu_M6000_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_WJetsToLNu_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_WW_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_WZ_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_ZZ_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_QCD_HT200to300_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_QCD_HT300to500_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_QCD_HT500to700_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_QCD_HT700to1000_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_QCD_HT1000to1500_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_QCD_HT1500to2000_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_QCD_HT2000toInf_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_ZJetsToNuNu_HT100To200_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_ZJetsToNuNu_HT200To400_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_ZJetsToNuNu_HT400To600_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_ZJetsToNuNu_HT600To800_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_JetEnUp);
  totalBkg_JetEnUp->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_JetEnUp);

  TH1* c_totalBkg_JetEnUp = totalBkg_JetEnUp->GetCumulative(kFALSE);

  TH1D* totalBkg_JetEnDown = (TH1D*)mT_Stage1_DYJetsToLL_M50_JetEnDown->Clone();
  totalBkg_JetEnDown->Add(mT_Stage1_DYJetsToLL_M5to50_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_TT_JetEnDown);
  // totalBkg_JetEnDown->Add(mT_Stage1_TT_Mtt_700to1000_JetEnDown);
  // totalBkg_JetEnDown->Add(mT_Stage1_TT_Mtt_1000toInf_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_ST_tchannel_antitop_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_ST_tchannel_top_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_ST_tW_antitop_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_ST_tW_top_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_WJetsToLNu_HT100To200_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_WJetsToLNu_HT200To400_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_WJetsToLNu_HT400To600_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_WJetsToLNu_HT600To800_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_WJetsToLNu_HT800To1200_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_WJetsToLNu_HT1200To2500_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_WToTauNu_M100_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_WToTauNu_M200_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_WToTauNu_M500_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_WToTauNu_M1000_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_WToTauNu_M2000_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_WToTauNu_M3000_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_WToTauNu_M4000_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_WToTauNu_M5000_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_WToTauNu_M6000_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_WJetsToLNu_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_WW_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_WZ_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_ZZ_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_QCD_HT200to300_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_QCD_HT300to500_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_QCD_HT500to700_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_QCD_HT700to1000_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_QCD_HT1000to1500_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_QCD_HT1500to2000_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_QCD_HT2000toInf_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_ZJetsToNuNu_HT100To200_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_ZJetsToNuNu_HT200To400_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_ZJetsToNuNu_HT400To600_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_ZJetsToNuNu_HT600To800_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_JetEnDown);
  totalBkg_JetEnDown->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_JetEnDown);

  TH1* c_totalBkg_JetEnDown = totalBkg_JetEnDown->GetCumulative(kFALSE);

  //
  TH1D* totalBkg_JetResUp = (TH1D*)mT_Stage1_DYJetsToLL_M50_JetResUp->Clone();
  totalBkg_JetResUp->Add(mT_Stage1_DYJetsToLL_M5to50_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_TT_JetResUp);
  //  totalBkg_JetResUp->Add(mT_Stage1_TT_Mtt_700to1000_JetResUp);
  // totalBkg_JetResUp->Add(mT_Stage1_TT_Mtt_1000toInf_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_ST_tchannel_antitop_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_ST_tchannel_top_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_ST_tW_antitop_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_ST_tW_top_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_WJetsToLNu_HT100To200_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_WJetsToLNu_HT200To400_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_WJetsToLNu_HT400To600_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_WJetsToLNu_HT600To800_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_WJetsToLNu_HT800To1200_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_WJetsToLNu_HT1200To2500_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_WToTauNu_M100_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_WToTauNu_M200_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_WToTauNu_M500_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_WToTauNu_M1000_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_WToTauNu_M2000_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_WToTauNu_M3000_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_WToTauNu_M4000_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_WToTauNu_M5000_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_WToTauNu_M6000_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_WJetsToLNu_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_WW_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_WZ_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_ZZ_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_QCD_HT200to300_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_QCD_HT300to500_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_QCD_HT500to700_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_QCD_HT700to1000_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_QCD_HT1000to1500_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_QCD_HT1500to2000_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_QCD_HT2000toInf_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_ZJetsToNuNu_HT100To200_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_ZJetsToNuNu_HT200To400_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_ZJetsToNuNu_HT400To600_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_ZJetsToNuNu_HT600To800_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_JetResUp);
  totalBkg_JetResUp->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_JetResUp);

  TH1* c_totalBkg_JetResUp = totalBkg_JetResUp->GetCumulative(kFALSE);

  TH1D* totalBkg_JetResDown = (TH1D*)mT_Stage1_DYJetsToLL_M50_JetResDown->Clone();
  totalBkg_JetResDown->Add(mT_Stage1_DYJetsToLL_M5to50_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_TT_JetResDown);
  //  totalBkg_JetResDown->Add(mT_Stage1_TT_Mtt_700to1000_JetResDown);
  //  totalBkg_JetResDown->Add(mT_Stage1_TT_Mtt_1000toInf_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_ST_tchannel_antitop_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_ST_tchannel_top_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_ST_tW_antitop_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_ST_tW_top_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_WJetsToLNu_HT100To200_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_WJetsToLNu_HT200To400_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_WJetsToLNu_HT400To600_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_WJetsToLNu_HT600To800_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_WJetsToLNu_HT800To1200_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_WJetsToLNu_HT1200To2500_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_WToTauNu_M100_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_WToTauNu_M200_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_WToTauNu_M500_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_WToTauNu_M1000_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_WToTauNu_M2000_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_WToTauNu_M3000_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_WToTauNu_M4000_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_WToTauNu_M5000_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_WToTauNu_M6000_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_WJetsToLNu_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_WW_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_WZ_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_ZZ_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_QCD_HT200to300_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_QCD_HT300to500_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_QCD_HT500to700_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_QCD_HT700to1000_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_QCD_HT1000to1500_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_QCD_HT1500to2000_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_QCD_HT2000toInf_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_ZJetsToNuNu_HT100To200_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_ZJetsToNuNu_HT200To400_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_ZJetsToNuNu_HT400To600_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_ZJetsToNuNu_HT600To800_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_JetResDown);
  totalBkg_JetResDown->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_JetResDown);

  TH1* c_totalBkg_JetResDown = totalBkg_JetResDown->GetCumulative(kFALSE);

  //
  TH1D* totalBkg_MuonEnUp = (TH1D*)mT_Stage1_DYJetsToLL_M50_MuonEnUp->Clone();
  totalBkg_MuonEnUp->Add(mT_Stage1_DYJetsToLL_M5to50_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_TT_MuonEnUp);
  //  totalBkg_MuonEnUp->Add(mT_Stage1_TT_Mtt_700to1000_MuonEnUp);
  //  totalBkg_MuonEnUp->Add(mT_Stage1_TT_Mtt_1000toInf_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_ST_tchannel_antitop_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_ST_tchannel_top_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_ST_tW_antitop_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_ST_tW_top_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_WJetsToLNu_HT100To200_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_WJetsToLNu_HT200To400_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_WJetsToLNu_HT400To600_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_WJetsToLNu_HT600To800_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_WJetsToLNu_HT800To1200_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_WJetsToLNu_HT1200To2500_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_WToTauNu_M100_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_WToTauNu_M200_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_WToTauNu_M500_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_WToTauNu_M1000_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_WToTauNu_M2000_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_WToTauNu_M3000_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_WToTauNu_M4000_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_WToTauNu_M5000_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_WToTauNu_M6000_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_WJetsToLNu_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_WW_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_WZ_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_ZZ_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_QCD_HT200to300_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_QCD_HT300to500_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_QCD_HT500to700_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_QCD_HT700to1000_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_QCD_HT1000to1500_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_QCD_HT1500to2000_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_QCD_HT2000toInf_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_ZJetsToNuNu_HT100To200_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_ZJetsToNuNu_HT200To400_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_ZJetsToNuNu_HT400To600_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_ZJetsToNuNu_HT600To800_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_MuonEnUp);
  totalBkg_MuonEnUp->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_MuonEnUp);

  TH1* c_totalBkg_MuonEnUp = totalBkg_MuonEnUp->GetCumulative(kFALSE);


  TH1D* totalBkg_MuonEnDown = (TH1D*)mT_Stage1_DYJetsToLL_M50_MuonEnDown->Clone();
  totalBkg_MuonEnDown->Add(mT_Stage1_DYJetsToLL_M5to50_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_TT_MuonEnDown);
  //  totalBkg_MuonEnDown->Add(mT_Stage1_TT_Mtt_700to1000_MuonEnDown);
  //  totalBkg_MuonEnDown->Add(mT_Stage1_TT_Mtt_1000toInf_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_ST_tchannel_antitop_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_ST_tchannel_top_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_ST_tW_antitop_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_ST_tW_top_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_WJetsToLNu_HT100To200_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_WJetsToLNu_HT200To400_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_WJetsToLNu_HT400To600_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_WJetsToLNu_HT600To800_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_WJetsToLNu_HT800To1200_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_WJetsToLNu_HT1200To2500_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_WToTauNu_M100_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_WToTauNu_M200_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_WToTauNu_M500_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_WToTauNu_M1000_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_WToTauNu_M2000_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_WToTauNu_M3000_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_WToTauNu_M4000_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_WToTauNu_M5000_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_WToTauNu_M6000_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_WJetsToLNu_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_WW_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_WZ_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_ZZ_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_QCD_HT200to300_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_QCD_HT300to500_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_QCD_HT500to700_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_QCD_HT700to1000_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_QCD_HT1000to1500_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_QCD_HT1500to2000_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_QCD_HT2000toInf_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_ZJetsToNuNu_HT100To200_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_ZJetsToNuNu_HT200To400_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_ZJetsToNuNu_HT400To600_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_ZJetsToNuNu_HT600To800_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_MuonEnDown);
  totalBkg_MuonEnDown->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_MuonEnDown);

  TH1* c_totalBkg_MuonEnDown = totalBkg_MuonEnDown->GetCumulative(kFALSE);

  //
  TH1D* totalBkg_ElectronEnUp = (TH1D*)mT_Stage1_DYJetsToLL_M50_ElectronEnUp->Clone();
  totalBkg_ElectronEnUp->Add(mT_Stage1_DYJetsToLL_M5to50_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_TT_ElectronEnUp);
  //  totalBkg_ElectronEnUp->Add(mT_Stage1_TT_Mtt_700to1000_ElectronEnUp);
  //  totalBkg_ElectronEnUp->Add(mT_Stage1_TT_Mtt_1000toInf_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_ST_tchannel_antitop_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_ST_tchannel_top_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_ST_tW_antitop_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_ST_tW_top_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_WJetsToLNu_HT100To200_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_WJetsToLNu_HT200To400_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_WJetsToLNu_HT400To600_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_WJetsToLNu_HT600To800_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_WJetsToLNu_HT800To1200_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_WJetsToLNu_HT1200To2500_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_WToTauNu_M100_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_WToTauNu_M200_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_WToTauNu_M500_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_WToTauNu_M1000_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_WToTauNu_M2000_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_WToTauNu_M3000_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_WToTauNu_M4000_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_WToTauNu_M5000_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_WToTauNu_M6000_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_WJetsToLNu_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_WW_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_WZ_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_ZZ_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_QCD_HT200to300_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_QCD_HT300to500_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_QCD_HT500to700_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_QCD_HT700to1000_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_QCD_HT1000to1500_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_QCD_HT1500to2000_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_QCD_HT2000toInf_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_ZJetsToNuNu_HT100To200_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_ZJetsToNuNu_HT200To400_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_ZJetsToNuNu_HT400To600_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_ZJetsToNuNu_HT600To800_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_ElectronEnUp);
  totalBkg_ElectronEnUp->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_ElectronEnUp);

  TH1* c_totalBkg_ElectronEnUp = totalBkg_ElectronEnUp->GetCumulative(kFALSE);


  TH1D* totalBkg_ElectronEnDown = (TH1D*)mT_Stage1_DYJetsToLL_M50_ElectronEnDown->Clone();
  totalBkg_ElectronEnDown->Add(mT_Stage1_DYJetsToLL_M5to50_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_TT_ElectronEnDown);
  //  totalBkg_ElectronEnDown->Add(mT_Stage1_TT_Mtt_700to1000_ElectronEnDown);
  //  totalBkg_ElectronEnDown->Add(mT_Stage1_TT_Mtt_1000toInf_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_ST_tchannel_antitop_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_ST_tchannel_top_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_ST_tW_antitop_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_ST_tW_top_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_WJetsToLNu_HT100To200_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_WJetsToLNu_HT200To400_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_WJetsToLNu_HT400To600_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_WJetsToLNu_HT600To800_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_WJetsToLNu_HT800To1200_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_WJetsToLNu_HT1200To2500_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_WToTauNu_M100_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_WToTauNu_M200_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_WToTauNu_M500_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_WToTauNu_M1000_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_WToTauNu_M2000_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_WToTauNu_M3000_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_WToTauNu_M4000_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_WToTauNu_M5000_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_WToTauNu_M6000_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_WJetsToLNu_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_WW_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_WZ_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_ZZ_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_QCD_HT200to300_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_QCD_HT300to500_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_QCD_HT500to700_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_QCD_HT700to1000_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_QCD_HT1000to1500_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_QCD_HT1500to2000_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_QCD_HT2000toInf_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_ZJetsToNuNu_HT100To200_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_ZJetsToNuNu_HT200To400_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_ZJetsToNuNu_HT400To600_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_ZJetsToNuNu_HT600To800_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_ElectronEnDown);
  totalBkg_ElectronEnDown->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_ElectronEnDown);

  TH1* c_totalBkg_ElectronEnDown = totalBkg_ElectronEnDown->GetCumulative(kFALSE);


  //
  TH1D* totalBkg_TauEnUp = (TH1D*)mT_Stage1_DYJetsToLL_M50_TauEnUp->Clone();
  totalBkg_TauEnUp->Add(mT_Stage1_DYJetsToLL_M5to50_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_TT_TauEnUp);
  //  totalBkg_TauEnUp->Add(mT_Stage1_TT_Mtt_700to1000_TauEnUp);
  //  totalBkg_TauEnUp->Add(mT_Stage1_TT_Mtt_1000toInf_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_ST_tchannel_antitop_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_ST_tchannel_top_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_ST_tW_antitop_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_ST_tW_top_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_WJetsToLNu_HT100To200_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_WJetsToLNu_HT200To400_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_WJetsToLNu_HT400To600_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_WJetsToLNu_HT600To800_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_WJetsToLNu_HT800To1200_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_WJetsToLNu_HT1200To2500_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_WToTauNu_M100_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_WToTauNu_M200_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_WToTauNu_M500_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_WToTauNu_M1000_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_WToTauNu_M2000_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_WToTauNu_M3000_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_WToTauNu_M4000_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_WToTauNu_M5000_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_WToTauNu_M6000_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_WJetsToLNu_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_WW_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_WZ_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_ZZ_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_QCD_HT200to300_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_QCD_HT300to500_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_QCD_HT500to700_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_QCD_HT700to1000_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_QCD_HT1000to1500_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_QCD_HT1500to2000_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_QCD_HT2000toInf_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_ZJetsToNuNu_HT100To200_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_ZJetsToNuNu_HT200To400_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_ZJetsToNuNu_HT400To600_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_ZJetsToNuNu_HT600To800_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_TauEnUp);
  totalBkg_TauEnUp->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauEnUp);

  TH1* c_totalBkg_TauEnUp = totalBkg_TauEnUp->GetCumulative(kFALSE);


  TH1D* totalBkg_TauEnDown = (TH1D*)mT_Stage1_DYJetsToLL_M50_TauEnDown->Clone();
  totalBkg_TauEnDown->Add(mT_Stage1_DYJetsToLL_M5to50_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_TT_TauEnDown);
  // totalBkg_TauEnDown->Add(mT_Stage1_TT_Mtt_700to1000_TauEnDown);
  //  totalBkg_TauEnDown->Add(mT_Stage1_TT_Mtt_1000toInf_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_ST_tchannel_antitop_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_ST_tchannel_top_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_ST_tW_antitop_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_ST_tW_top_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_WJetsToLNu_HT100To200_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_WJetsToLNu_HT200To400_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_WJetsToLNu_HT400To600_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_WJetsToLNu_HT600To800_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_WJetsToLNu_HT800To1200_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_WJetsToLNu_HT1200To2500_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_WToTauNu_M100_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_WToTauNu_M200_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_WToTauNu_M500_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_WToTauNu_M1000_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_WToTauNu_M2000_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_WToTauNu_M3000_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_WToTauNu_M4000_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_WToTauNu_M5000_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_WToTauNu_M6000_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_WJetsToLNu_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_WW_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_WZ_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_ZZ_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_QCD_HT200to300_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_QCD_HT300to500_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_QCD_HT500to700_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_QCD_HT700to1000_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_QCD_HT1000to1500_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_QCD_HT1500to2000_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_QCD_HT2000toInf_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_ZJetsToNuNu_HT100To200_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_ZJetsToNuNu_HT200To400_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_ZJetsToNuNu_HT400To600_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_ZJetsToNuNu_HT600To800_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_TauEnDown);
  totalBkg_TauEnDown->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauEnDown);

  TH1* c_totalBkg_TauEnDown = totalBkg_TauEnDown->GetCumulative(kFALSE);

  //
  TH1D* totalBkg_PhotonEnUp = (TH1D*)mT_Stage1_DYJetsToLL_M50_PhotonEnUp->Clone();
  totalBkg_PhotonEnUp->Add(mT_Stage1_DYJetsToLL_M5to50_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_TT_PhotonEnUp);
  //  totalBkg_PhotonEnUp->Add(mT_Stage1_TT_Mtt_700to1000_PhotonEnUp);
  //  totalBkg_PhotonEnUp->Add(mT_Stage1_TT_Mtt_1000toInf_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_ST_tchannel_antitop_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_ST_tchannel_top_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_ST_tW_antitop_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_ST_tW_top_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_WJetsToLNu_HT100To200_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_WJetsToLNu_HT200To400_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_WJetsToLNu_HT400To600_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_WJetsToLNu_HT600To800_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_WJetsToLNu_HT800To1200_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_WJetsToLNu_HT1200To2500_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_WToTauNu_M100_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_WToTauNu_M200_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_WToTauNu_M500_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_WToTauNu_M1000_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_WToTauNu_M2000_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_WToTauNu_M3000_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_WToTauNu_M4000_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_WToTauNu_M5000_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_WToTauNu_M6000_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_WJetsToLNu_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_WW_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_WZ_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_ZZ_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_QCD_HT200to300_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_QCD_HT300to500_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_QCD_HT500to700_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_QCD_HT700to1000_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_QCD_HT1000to1500_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_QCD_HT1500to2000_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_QCD_HT2000toInf_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_ZJetsToNuNu_HT100To200_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_ZJetsToNuNu_HT200To400_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_ZJetsToNuNu_HT400To600_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_ZJetsToNuNu_HT600To800_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_PhotonEnUp);
  totalBkg_PhotonEnUp->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_PhotonEnUp);

  TH1D* totalBkg_PhotonEnDown = (TH1D*)mT_Stage1_DYJetsToLL_M50_PhotonEnDown->Clone();
  totalBkg_PhotonEnDown->Add(mT_Stage1_DYJetsToLL_M5to50_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_TT_PhotonEnDown);
  //  totalBkg_PhotonEnDown->Add(mT_Stage1_TT_Mtt_700to1000_PhotonEnDown);
  //  totalBkg_PhotonEnDown->Add(mT_Stage1_TT_Mtt_1000toInf_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_ST_tchannel_antitop_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_ST_tchannel_top_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_ST_tW_antitop_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_ST_tW_top_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_WJetsToLNu_HT100To200_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_WJetsToLNu_HT200To400_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_WJetsToLNu_HT400To600_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_WJetsToLNu_HT600To800_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_WJetsToLNu_HT800To1200_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_WJetsToLNu_HT1200To2500_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_WToTauNu_M100_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_WToTauNu_M200_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_WToTauNu_M500_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_WToTauNu_M1000_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_WToTauNu_M2000_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_WToTauNu_M3000_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_WToTauNu_M4000_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_WToTauNu_M5000_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_WToTauNu_M6000_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_WJetsToLNu_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_WW_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_WZ_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_ZZ_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_QCD_HT200to300_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_QCD_HT300to500_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_QCD_HT500to700_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_QCD_HT700to1000_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_QCD_HT1000to1500_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_QCD_HT1500to2000_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_QCD_HT2000toInf_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_ZJetsToNuNu_HT100To200_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_ZJetsToNuNu_HT200To400_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_ZJetsToNuNu_HT400To600_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_ZJetsToNuNu_HT600To800_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_PhotonEnDown);
  totalBkg_PhotonEnDown->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_PhotonEnDown);

  //
  TH1D* totalBkg_UnclusteredEnUp = (TH1D*)mT_Stage1_DYJetsToLL_M50_UnclusteredEnUp->Clone();
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_DYJetsToLL_M5to50_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_TT_UnclusteredEnUp);
  //  totalBkg_UnclusteredEnUp->Add(mT_Stage1_TT_Mtt_700to1000_UnclusteredEnUp);
  //  totalBkg_UnclusteredEnUp->Add(mT_Stage1_TT_Mtt_1000toInf_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_ST_tchannel_antitop_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_ST_tchannel_top_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_ST_tW_antitop_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_ST_tW_top_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_WJetsToLNu_HT100To200_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_WJetsToLNu_HT200To400_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_WJetsToLNu_HT400To600_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_WJetsToLNu_HT600To800_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_WJetsToLNu_HT800To1200_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_WJetsToLNu_HT1200To2500_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_WToTauNu_M100_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_WToTauNu_M200_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_WToTauNu_M500_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_WToTauNu_M1000_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_WToTauNu_M2000_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_WToTauNu_M3000_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_WToTauNu_M4000_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_WToTauNu_M5000_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_WToTauNu_M6000_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_WJetsToLNu_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_WW_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_WZ_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_ZZ_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_QCD_HT200to300_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_QCD_HT300to500_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_QCD_HT500to700_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_QCD_HT700to1000_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_QCD_HT1000to1500_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_QCD_HT1500to2000_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_QCD_HT2000toInf_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_ZJetsToNuNu_HT100To200_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_ZJetsToNuNu_HT200To400_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_ZJetsToNuNu_HT400To600_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_ZJetsToNuNu_HT600To800_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_UnclusteredEnUp);
  totalBkg_UnclusteredEnUp->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_UnclusteredEnUp);

  TH1D* totalBkg_UnclusteredEnDown = (TH1D*)mT_Stage1_DYJetsToLL_M50_UnclusteredEnDown->Clone();
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_DYJetsToLL_M5to50_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_TT_UnclusteredEnDown);
  // totalBkg_UnclusteredEnDown->Add(mT_Stage1_TT_Mtt_700to1000_UnclusteredEnDown);
  // totalBkg_UnclusteredEnDown->Add(mT_Stage1_TT_Mtt_1000toInf_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_ST_tchannel_antitop_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_ST_tchannel_top_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_ST_tW_antitop_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_ST_tW_top_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_WJetsToLNu_HT100To200_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_WJetsToLNu_HT200To400_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_WJetsToLNu_HT400To600_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_WJetsToLNu_HT600To800_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_WJetsToLNu_HT800To1200_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_WJetsToLNu_HT1200To2500_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_WToTauNu_M100_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_WToTauNu_M200_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_WToTauNu_M500_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_WToTauNu_M1000_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_WToTauNu_M2000_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_WToTauNu_M3000_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_WToTauNu_M4000_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_WToTauNu_M5000_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_WToTauNu_M6000_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_WJetsToLNu_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_WW_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_WZ_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_ZZ_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_QCD_HT200to300_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_QCD_HT300to500_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_QCD_HT500to700_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_QCD_HT700to1000_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_QCD_HT1000to1500_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_QCD_HT1500to2000_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_QCD_HT2000toInf_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_ZJetsToNuNu_HT100To200_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_ZJetsToNuNu_HT200To400_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_ZJetsToNuNu_HT400To600_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_ZJetsToNuNu_HT600To800_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_UnclusteredEnDown);
  totalBkg_UnclusteredEnDown->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_UnclusteredEnDown);
  //
  TH1D* totalBkg_TauScaleUp = (TH1D*)mT_Stage1_DYJetsToLL_M50_TauScaleUp->Clone();
  totalBkg_TauScaleUp->Add(mT_Stage1_DYJetsToLL_M5to50_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_TT_TauScaleUp);
  //  totalBkg_TauScaleUp->Add(mT_Stage1_TT_Mtt_700to1000_TauScaleUp);
  //  totalBkg_TauScaleUp->Add(mT_Stage1_TT_Mtt_1000toInf_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_ST_tchannel_antitop_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_ST_tchannel_top_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_ST_tW_antitop_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_ST_tW_top_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_WJetsToLNu_HT100To200_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_WJetsToLNu_HT200To400_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_WJetsToLNu_HT400To600_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_WJetsToLNu_HT600To800_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_WJetsToLNu_HT800To1200_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_WJetsToLNu_HT1200To2500_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_WToTauNu_M100_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_WToTauNu_M200_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_WToTauNu_M500_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_WToTauNu_M1000_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_WToTauNu_M2000_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_WToTauNu_M3000_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_WToTauNu_M4000_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_WToTauNu_M5000_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_WToTauNu_M6000_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_WJetsToLNu_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_WW_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_WZ_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_ZZ_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_QCD_HT200to300_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_QCD_HT300to500_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_QCD_HT500to700_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_QCD_HT700to1000_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_QCD_HT1000to1500_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_QCD_HT1500to2000_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_QCD_HT2000toInf_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_ZJetsToNuNu_HT100To200_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_ZJetsToNuNu_HT200To400_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_ZJetsToNuNu_HT400To600_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_ZJetsToNuNu_HT600To800_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_TauScaleUp);
  totalBkg_TauScaleUp->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauScaleUp);

  TH1D* totalBkg_TauScaleDown = (TH1D*)mT_Stage1_DYJetsToLL_M50_TauScaleDown->Clone();
  totalBkg_TauScaleDown->Add(mT_Stage1_DYJetsToLL_M5to50_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_TT_TauScaleDown);
  //  totalBkg_TauScaleDown->Add(mT_Stage1_TT_Mtt_700to1000_TauScaleDown);
  // totalBkg_TauScaleDown->Add(mT_Stage1_TT_Mtt_1000toInf_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_ST_tchannel_antitop_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_ST_tchannel_top_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_ST_tW_antitop_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_ST_tW_top_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_WJetsToLNu_HT100To200_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_WJetsToLNu_HT200To400_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_WJetsToLNu_HT400To600_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_WJetsToLNu_HT600To800_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_WJetsToLNu_HT800To1200_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_WJetsToLNu_HT1200To2500_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_WToTauNu_M100_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_WToTauNu_M200_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_WToTauNu_M500_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_WToTauNu_M1000_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_WToTauNu_M2000_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_WToTauNu_M3000_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_WToTauNu_M4000_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_WToTauNu_M5000_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_WToTauNu_M6000_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_WJetsToLNu_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_WW_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_WZ_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_ZZ_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_QCD_HT200to300_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_QCD_HT300to500_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_QCD_HT500to700_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_QCD_HT700to1000_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_QCD_HT1000to1500_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_QCD_HT1500to2000_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_QCD_HT2000toInf_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_ZJetsToNuNu_HT100To200_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_ZJetsToNuNu_HT200To400_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_ZJetsToNuNu_HT400To600_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_ZJetsToNuNu_HT600To800_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_TauScaleDown);
  totalBkg_TauScaleDown->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauScaleDown);
 //
  TH1D* totalBkg_pileupUncertUp = (TH1D*)mT_Stage1_DYJetsToLL_M50_pileupUncertUp->Clone();
  totalBkg_pileupUncertUp->Add(mT_Stage1_DYJetsToLL_M5to50_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_TT_pileupUncertUp);
  // totalBkg_pileupUncertUp->Add(mT_Stage1_TT_Mtt_700to1000_pileupUncertUp);
  // totalBkg_pileupUncertUp->Add(mT_Stage1_TT_Mtt_1000toInf_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_ST_tchannel_antitop_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_ST_tchannel_top_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_ST_tW_antitop_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_ST_tW_top_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_WJetsToLNu_HT100To200_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_WJetsToLNu_HT200To400_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_WJetsToLNu_HT400To600_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_WJetsToLNu_HT600To800_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_WJetsToLNu_HT800To1200_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_WJetsToLNu_HT1200To2500_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_WToTauNu_M100_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_WToTauNu_M200_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_WToTauNu_M500_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_WToTauNu_M1000_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_WToTauNu_M2000_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_WToTauNu_M3000_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_WToTauNu_M4000_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_WToTauNu_M5000_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_WToTauNu_M6000_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_WJetsToLNu_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_WW_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_WZ_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_ZZ_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_QCD_HT200to300_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_QCD_HT300to500_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_QCD_HT500to700_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_QCD_HT700to1000_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_QCD_HT1000to1500_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_QCD_HT1500to2000_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_QCD_HT2000toInf_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_ZJetsToNuNu_HT100To200_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_ZJetsToNuNu_HT200To400_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_ZJetsToNuNu_HT400To600_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_ZJetsToNuNu_HT600To800_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_pileupUncertUp);
  totalBkg_pileupUncertUp->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_pileupUncertUp);

  TH1D* totalBkg_pileupUncertDown = (TH1D*)mT_Stage1_DYJetsToLL_M50_pileupUncertDown->Clone();
  totalBkg_pileupUncertDown->Add(mT_Stage1_DYJetsToLL_M5to50_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_TT_pileupUncertDown);
  //  totalBkg_pileupUncertDown->Add(mT_Stage1_TT_Mtt_700to1000_pileupUncertDown);
  // totalBkg_pileupUncertDown->Add(mT_Stage1_TT_Mtt_1000toInf_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_ST_tchannel_antitop_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_ST_tchannel_top_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_ST_tW_antitop_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_ST_tW_top_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_WJetsToLNu_HT100To200_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_WJetsToLNu_HT200To400_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_WJetsToLNu_HT400To600_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_WJetsToLNu_HT600To800_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_WJetsToLNu_HT800To1200_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_WJetsToLNu_HT1200To2500_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_WToTauNu_M100_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_WToTauNu_M200_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_WToTauNu_M500_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_WToTauNu_M1000_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_WToTauNu_M2000_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_WToTauNu_M3000_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_WToTauNu_M4000_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_WToTauNu_M5000_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_WToTauNu_M6000_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_WJetsToLNu_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_WW_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_WZ_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_ZZ_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_QCD_HT200to300_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_QCD_HT300to500_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_QCD_HT500to700_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_QCD_HT700to1000_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_QCD_HT1000to1500_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_QCD_HT1500to2000_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_QCD_HT2000toInf_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_ZJetsToNuNu_HT100To200_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_ZJetsToNuNu_HT200To400_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_ZJetsToNuNu_HT400To600_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_ZJetsToNuNu_HT600To800_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_pileupUncertDown);
  totalBkg_pileupUncertDown->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_pileupUncertDown);
 //
  /*  TH1D* totalBkg_kFactorUp = (TH1D*)mT_Stage1_WJetsToLNu_HT100To200_kFactorUp->Clone();
  totalBkg_kFactorUp->Add(mT_Stage1_WJetsToLNu_HT200To400_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WJetsToLNu_HT400To600_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WJetsToLNu_HT600To800_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WJetsToLNu_HT800To1200_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WJetsToLNu_HT1200To2500_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WJetsToLNu_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WToTauNu_M100_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WToTauNu_M200_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WToTauNu_M500_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WToTauNu_M1000_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WToTauNu_M2000_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WToTauNu_M3000_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WToTauNu_M4000_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WToTauNu_M5000_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WToTauNu_M6000_kFactorUp);

  TH1D* totalBkg_kFactorDown = (TH1D*)mT_Stage1_WJetsToLNu_HT100To200_kFactorDown->Clone();
  totalBkg_kFactorDown->Add(mT_Stage1_WJetsToLNu_HT200To400_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WJetsToLNu_HT400To600_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WJetsToLNu_HT600To800_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WJetsToLNu_HT800To1200_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WJetsToLNu_HT1200To2500_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WJetsToLNu_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WToTauNu_M100_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WToTauNu_M200_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WToTauNu_M500_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WToTauNu_M1000_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WToTauNu_M2000_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WToTauNu_M3000_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WToTauNu_M4000_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WToTauNu_M5000_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WToTauNu_M6000_kFactorDown);
  */

  TH1D* totalBkg_kFactorUp = (TH1D*)mT_Stage1_DYJetsToLL_M50_kFactorUp->Clone();
  totalBkg_kFactorUp->Add(mT_Stage1_DYJetsToLL_M5to50_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_TT_kFactorUp);
  //  totalBkg_kFactorUp->Add(mT_Stage1_TT_Mtt_700to1000_kFactorUp);
  // totalBkg_kFactorUp->Add(mT_Stage1_TT_Mtt_1000toInf_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_ST_tchannel_antitop_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_ST_tchannel_top_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_ST_tW_antitop_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_ST_tW_top_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WJetsToLNu_HT100To200_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WJetsToLNu_HT200To400_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WJetsToLNu_HT400To600_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WJetsToLNu_HT600To800_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WJetsToLNu_HT800To1200_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WJetsToLNu_HT1200To2500_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WToTauNu_M100_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WToTauNu_M200_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WToTauNu_M500_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WToTauNu_M1000_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WToTauNu_M2000_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WToTauNu_M3000_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WToTauNu_M4000_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WToTauNu_M5000_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WToTauNu_M6000_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WJetsToLNu_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WW_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_WZ_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_ZZ_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_QCD_HT200to300_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_QCD_HT300to500_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_QCD_HT500to700_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_QCD_HT700to1000_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_QCD_HT1000to1500_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_QCD_HT1500to2000_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_QCD_HT2000toInf_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_ZJetsToNuNu_HT100To200_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_ZJetsToNuNu_HT200To400_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_ZJetsToNuNu_HT400To600_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_ZJetsToNuNu_HT600To800_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_kFactorUp);
  totalBkg_kFactorUp->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_kFactorUp);

  TH1D* totalBkg_kFactorDown = (TH1D*)mT_Stage1_DYJetsToLL_M50_kFactorDown->Clone();
  totalBkg_kFactorDown->Add(mT_Stage1_DYJetsToLL_M5to50_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_TT_kFactorDown);
  // totalBkg_kFactorDown->Add(mT_Stage1_TT_Mtt_700to1000_kFactorDown);
  // totalBkg_kFactorDown->Add(mT_Stage1_TT_Mtt_1000toInf_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_ST_tchannel_antitop_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_ST_tchannel_top_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_ST_tW_antitop_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_ST_tW_top_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WJetsToLNu_HT100To200_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WJetsToLNu_HT200To400_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WJetsToLNu_HT400To600_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WJetsToLNu_HT600To800_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WJetsToLNu_HT800To1200_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WJetsToLNu_HT1200To2500_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WToTauNu_M100_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WToTauNu_M200_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WToTauNu_M500_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WToTauNu_M1000_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WToTauNu_M2000_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WToTauNu_M3000_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WToTauNu_M4000_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WToTauNu_M5000_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WToTauNu_M6000_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WJetsToLNu_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WW_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_WZ_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_ZZ_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_QCD_HT200to300_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_QCD_HT300to500_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_QCD_HT500to700_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_QCD_HT700to1000_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_QCD_HT1000to1500_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_QCD_HT1500to2000_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_QCD_HT2000toInf_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_ZJetsToNuNu_HT100To200_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_ZJetsToNuNu_HT200To400_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_ZJetsToNuNu_HT400To600_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_ZJetsToNuNu_HT600To800_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_kFactorDown);
  totalBkg_kFactorDown->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_kFactorDown);

  ///


  TH1D* totalBkg_TauIDSFUp = (TH1D*)mT_Stage1_DYJetsToLL_M50_TauIDSFUp->Clone();
  totalBkg_TauIDSFUp->Add(mT_Stage1_DYJetsToLL_M5to50_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_TT_TauIDSFUp);
  //  totalBkg_TauIDSFUp->Add(mT_Stage1_TT_Mtt_700to1000_TauIDSFUp);
  // totalBkg_TauIDSFUp->Add(mT_Stage1_TT_Mtt_1000toInf_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_ST_tchannel_antitop_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_ST_tchannel_top_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_ST_tW_antitop_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_ST_tW_top_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_WJetsToLNu_HT100To200_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_WJetsToLNu_HT200To400_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_WJetsToLNu_HT400To600_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_WJetsToLNu_HT600To800_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_WJetsToLNu_HT800To1200_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_WJetsToLNu_HT1200To2500_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_WToTauNu_M100_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_WToTauNu_M200_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_WToTauNu_M500_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_WToTauNu_M1000_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_WToTauNu_M2000_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_WToTauNu_M3000_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_WToTauNu_M4000_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_WToTauNu_M5000_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_WToTauNu_M6000_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_WJetsToLNu_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_WW_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_WZ_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_ZZ_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_QCD_HT200to300_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_QCD_HT300to500_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_QCD_HT500to700_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_QCD_HT700to1000_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_QCD_HT1000to1500_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_QCD_HT1500to2000_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_QCD_HT2000toInf_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_ZJetsToNuNu_HT100To200_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_ZJetsToNuNu_HT200To400_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_ZJetsToNuNu_HT400To600_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_ZJetsToNuNu_HT600To800_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_TauIDSFUp);
  totalBkg_TauIDSFUp->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauIDSFUp);

  TH1D* totalBkg_TauIDSFDown = (TH1D*)mT_Stage1_DYJetsToLL_M50_TauIDSFDown->Clone();
  totalBkg_TauIDSFDown->Add(mT_Stage1_DYJetsToLL_M5to50_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_TT_TauIDSFDown);
  // totalBkg_TauIDSFDown->Add(mT_Stage1_TT_Mtt_700to1000_TauIDSFDown);
  // totalBkg_TauIDSFDown->Add(mT_Stage1_TT_Mtt_1000toInf_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_ST_tchannel_antitop_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_ST_tchannel_top_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_ST_tW_antitop_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_ST_tW_top_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_WJetsToLNu_HT100To200_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_WJetsToLNu_HT200To400_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_WJetsToLNu_HT400To600_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_WJetsToLNu_HT600To800_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_WJetsToLNu_HT800To1200_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_WJetsToLNu_HT1200To2500_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_WToTauNu_M100_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_WToTauNu_M200_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_WToTauNu_M500_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_WToTauNu_M1000_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_WToTauNu_M2000_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_WToTauNu_M3000_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_WToTauNu_M4000_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_WToTauNu_M5000_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_WToTauNu_M6000_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_WJetsToLNu_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_WW_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_WZ_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_ZZ_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_QCD_HT200to300_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_QCD_HT300to500_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_QCD_HT500to700_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_QCD_HT700to1000_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_QCD_HT1000to1500_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_QCD_HT1500to2000_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_QCD_HT2000toInf_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_ZJetsToNuNu_HT100To200_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_ZJetsToNuNu_HT200To400_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_ZJetsToNuNu_HT400To600_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_ZJetsToNuNu_HT600To800_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_TauIDSFDown);
  totalBkg_TauIDSFDown->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauIDSFDown);

  ///flat
  TH1D* totalBkg_TauIDSFflatUp = (TH1D*)mT_Stage1_DYJetsToLL_M50_TauIDSFflatUp->Clone();
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_DYJetsToLL_M5to50_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_TT_TauIDSFflatUp);
  //  totalBkg_TauIDSFflatUp->Add(mT_Stage1_TT_Mtt_700to1000_TauIDSFflatUp);
  // totalBkg_TauIDSFflatUp->Add(mT_Stage1_TT_Mtt_1000toInf_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_ST_tchannel_antitop_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_ST_tchannel_top_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_ST_tW_antitop_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_ST_tW_top_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_WJetsToLNu_HT100To200_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_WJetsToLNu_HT200To400_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_WJetsToLNu_HT400To600_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_WJetsToLNu_HT600To800_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_WJetsToLNu_HT800To1200_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_WJetsToLNu_HT1200To2500_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_WToTauNu_M100_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_WToTauNu_M200_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_WToTauNu_M500_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_WToTauNu_M1000_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_WToTauNu_M2000_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_WToTauNu_M3000_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_WToTauNu_M4000_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_WToTauNu_M5000_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_WToTauNu_M6000_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_WJetsToLNu_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_WW_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_WZ_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_ZZ_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_QCD_HT200to300_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_QCD_HT300to500_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_QCD_HT500to700_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_QCD_HT700to1000_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_QCD_HT1000to1500_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_QCD_HT1500to2000_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_QCD_HT2000toInf_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_ZJetsToNuNu_HT100To200_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_ZJetsToNuNu_HT200To400_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_ZJetsToNuNu_HT400To600_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_ZJetsToNuNu_HT600To800_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_TauIDSFflatUp);
  totalBkg_TauIDSFflatUp->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauIDSFflatUp);

  TH1D* totalBkg_TauIDSFflatDown = (TH1D*)mT_Stage1_DYJetsToLL_M50_TauIDSFflatDown->Clone();
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_DYJetsToLL_M5to50_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_TT_TauIDSFflatDown);
  // totalBkg_TauIDSFflatDown->Add(mT_Stage1_TT_Mtt_700to1000_TauIDSFflatDown);
  // totalBkg_TauIDSFflatDown->Add(mT_Stage1_TT_Mtt_1000toInf_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_ST_tchannel_antitop_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_ST_tchannel_top_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_ST_tW_antitop_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_ST_tW_top_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_WJetsToLNu_HT100To200_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_WJetsToLNu_HT200To400_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_WJetsToLNu_HT400To600_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_WJetsToLNu_HT600To800_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_WJetsToLNu_HT800To1200_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_WJetsToLNu_HT1200To2500_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_WToTauNu_M100_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_WToTauNu_M200_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_WToTauNu_M500_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_WToTauNu_M1000_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_WToTauNu_M2000_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_WToTauNu_M3000_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_WToTauNu_M4000_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_WToTauNu_M5000_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_WToTauNu_M6000_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_WJetsToLNu_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_WW_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_WZ_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_ZZ_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_QCD_HT200to300_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_QCD_HT300to500_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_QCD_HT500to700_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_QCD_HT700to1000_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_QCD_HT1000to1500_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_QCD_HT1500to2000_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_QCD_HT2000toInf_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_ZJetsToNuNu_HT100To200_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_ZJetsToNuNu_HT200To400_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_ZJetsToNuNu_HT400To600_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_ZJetsToNuNu_HT600To800_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_TauIDSFflatDown);
  totalBkg_TauIDSFflatDown->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauIDSFflatDown);

  /////ele
  TH1D* totalBkg_TauELESFUp = (TH1D*)mT_Stage1_DYJetsToLL_M50_TauELESFUp->Clone();
  totalBkg_TauELESFUp->Add(mT_Stage1_DYJetsToLL_M5to50_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_TT_TauELESFUp);
  //  totalBkg_TauELESFUp->Add(mT_Stage1_TT_Mtt_700to1000_TauELESFUp);
  // totalBkg_TauELESFUp->Add(mT_Stage1_TT_Mtt_1000toInf_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_ST_tchannel_antitop_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_ST_tchannel_top_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_ST_tW_antitop_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_ST_tW_top_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_WJetsToLNu_HT100To200_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_WJetsToLNu_HT200To400_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_WJetsToLNu_HT400To600_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_WJetsToLNu_HT600To800_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_WJetsToLNu_HT800To1200_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_WJetsToLNu_HT1200To2500_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_WToTauNu_M100_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_WToTauNu_M200_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_WToTauNu_M500_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_WToTauNu_M1000_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_WToTauNu_M2000_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_WToTauNu_M3000_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_WToTauNu_M4000_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_WToTauNu_M5000_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_WToTauNu_M6000_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_WJetsToLNu_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_WW_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_WZ_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_ZZ_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_QCD_HT200to300_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_QCD_HT300to500_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_QCD_HT500to700_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_QCD_HT700to1000_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_QCD_HT1000to1500_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_QCD_HT1500to2000_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_QCD_HT2000toInf_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_ZJetsToNuNu_HT100To200_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_ZJetsToNuNu_HT200To400_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_ZJetsToNuNu_HT400To600_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_ZJetsToNuNu_HT600To800_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_TauELESFUp);
  totalBkg_TauELESFUp->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauELESFUp);

  TH1D* totalBkg_TauELESFDown = (TH1D*)mT_Stage1_DYJetsToLL_M50_TauELESFDown->Clone();
  totalBkg_TauELESFDown->Add(mT_Stage1_DYJetsToLL_M5to50_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_TT_TauELESFDown);
  // totalBkg_TauELESFDown->Add(mT_Stage1_TT_Mtt_700to1000_TauELESFDown);
  // totalBkg_TauELESFDown->Add(mT_Stage1_TT_Mtt_1000toInf_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_ST_tchannel_antitop_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_ST_tchannel_top_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_ST_tW_antitop_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_ST_tW_top_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_WJetsToLNu_HT100To200_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_WJetsToLNu_HT200To400_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_WJetsToLNu_HT400To600_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_WJetsToLNu_HT600To800_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_WJetsToLNu_HT800To1200_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_WJetsToLNu_HT1200To2500_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_WToTauNu_M100_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_WToTauNu_M200_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_WToTauNu_M500_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_WToTauNu_M1000_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_WToTauNu_M2000_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_WToTauNu_M3000_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_WToTauNu_M4000_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_WToTauNu_M5000_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_WToTauNu_M6000_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_WJetsToLNu_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_WW_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_WZ_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_ZZ_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_QCD_HT200to300_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_QCD_HT300to500_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_QCD_HT500to700_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_QCD_HT700to1000_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_QCD_HT1000to1500_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_QCD_HT1500to2000_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_QCD_HT2000toInf_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_ZJetsToNuNu_HT100To200_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_ZJetsToNuNu_HT200To400_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_ZJetsToNuNu_HT400To600_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_ZJetsToNuNu_HT600To800_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_TauELESFDown);
  totalBkg_TauELESFDown->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_TauELESFDown);

  /////trig
  TH1D* totalBkg_trigSFUp = (TH1D*)mT_Stage1_DYJetsToLL_M50_trigSFUp->Clone();
  totalBkg_trigSFUp->Add(mT_Stage1_DYJetsToLL_M5to50_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_TT_trigSFUp);
  //  totalBkg_trigSFUp->Add(mT_Stage1_TT_Mtt_700to1000_trigSFUp);
  // totalBkg_trigSFUp->Add(mT_Stage1_TT_Mtt_1000toInf_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_ST_tchannel_antitop_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_ST_tchannel_top_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_ST_tW_antitop_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_ST_tW_top_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_WJetsToLNu_HT100To200_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_WJetsToLNu_HT200To400_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_WJetsToLNu_HT400To600_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_WJetsToLNu_HT600To800_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_WJetsToLNu_HT800To1200_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_WJetsToLNu_HT1200To2500_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_WToTauNu_M100_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_WToTauNu_M200_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_WToTauNu_M500_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_WToTauNu_M1000_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_WToTauNu_M2000_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_WToTauNu_M3000_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_WToTauNu_M4000_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_WToTauNu_M5000_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_WToTauNu_M6000_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_WJetsToLNu_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_WW_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_WZ_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_ZZ_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_QCD_HT200to300_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_QCD_HT300to500_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_QCD_HT500to700_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_QCD_HT700to1000_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_QCD_HT1000to1500_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_QCD_HT1500to2000_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_QCD_HT2000toInf_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_ZJetsToNuNu_HT100To200_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_ZJetsToNuNu_HT200To400_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_ZJetsToNuNu_HT400To600_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_ZJetsToNuNu_HT600To800_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_trigSFUp);
  totalBkg_trigSFUp->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_trigSFUp);

  TH1D* totalBkg_trigSFDown = (TH1D*)mT_Stage1_DYJetsToLL_M50_trigSFDown->Clone();
  totalBkg_trigSFDown->Add(mT_Stage1_DYJetsToLL_M5to50_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_TT_trigSFDown);
  // totalBkg_trigSFDown->Add(mT_Stage1_TT_Mtt_700to1000_trigSFDown);
  // totalBkg_trigSFDown->Add(mT_Stage1_TT_Mtt_1000toInf_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_ST_tchannel_antitop_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_ST_tchannel_top_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_ST_tW_antitop_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_ST_tW_top_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_WJetsToLNu_HT100To200_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_WJetsToLNu_HT200To400_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_WJetsToLNu_HT400To600_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_WJetsToLNu_HT600To800_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_WJetsToLNu_HT800To1200_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_WJetsToLNu_HT1200To2500_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_WToTauNu_M100_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_WToTauNu_M200_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_WToTauNu_M500_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_WToTauNu_M1000_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_WToTauNu_M2000_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_WToTauNu_M3000_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_WToTauNu_M4000_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_WToTauNu_M5000_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_WToTauNu_M6000_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_WJetsToLNu_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_WW_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_WZ_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_ZZ_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_QCD_HT200to300_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_QCD_HT300to500_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_QCD_HT500to700_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_QCD_HT700to1000_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_QCD_HT1000to1500_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_QCD_HT1500to2000_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_QCD_HT2000toInf_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_ZJetsToNuNu_HT100To200_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_ZJetsToNuNu_HT200To400_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_ZJetsToNuNu_HT400To600_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_ZJetsToNuNu_HT600To800_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_trigSFDown);
  totalBkg_trigSFDown->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_trigSFDown);


  //
  /*
  TH1D* totalBkg_pdfUncertUp = (TH1D*)mT_Stage1_DYJetsToLL_M50_pdfUncertUp->Clone();
  totalBkg_pdfUncertUp->Add(mT_Stage1_DYJetsToLL_M5to50_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_TT_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_TT_Mtt_700to1000_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_TT_Mtt_1000toInf_pdfUncertUp);
  // totalBkg_pdfUncertUp->Add(mT_Stage1_ST_tchannel_antitop_pdfUncertUp);
  //  totalBkg_pdfUncertUp->Add(mT_Stage1_ST_tchannel_top_pdfUncertUp);
  // totalBkg_pdfUncertUp->Add(mT_Stage1_ST_tW_antitop_pdfUncertUp);
  //  totalBkg_pdfUncertUp->Add(mT_Stage1_ST_tW_top_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_WJetsToLNu_HT100To200_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_WJetsToLNu_HT200To400_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_WJetsToLNu_HT400To600_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_WJetsToLNu_HT600To800_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_WJetsToLNu_HT800To1200_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_WJetsToLNu_HT1200To2500_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_pdfUncertUp);
  // totalBkg_pdfUncertUp->Add(mT_Stage1_WToTauNu_M100_pdfUncertUp);
  //  totalBkg_pdfUncertUp->Add(mT_Stage1_WToTauNu_M200_pdfUncertUp);
  // totalBkg_pdfUncertUp->Add(mT_Stage1_WToTauNu_M500_pdfUncertUp);
  // totalBkg_pdfUncertUp->Add(mT_Stage1_WToTauNu_M1000_pdfUncertUp);
  //  totalBkg_pdfUncertUp->Add(mT_Stage1_WToTauNu_M2000_pdfUncertUp);
  // totalBkg_pdfUncertUp->Add(mT_Stage1_WToTauNu_M3000_pdfUncertUp);
  //  totalBkg_pdfUncertUp->Add(mT_Stage1_WToTauNu_M4000_pdfUncertUp);
  //  totalBkg_pdfUncertUp->Add(mT_Stage1_WToTauNu_M5000_pdfUncertUp);
  //  totalBkg_pdfUncertUp->Add(mT_Stage1_WToTauNu_M6000_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_WJetsToLNu_pdfUncertUp);
  //  totalBkg_pdfUncertUp->Add(mT_Stage1_WW_pdfUncertUp);
  //  totalBkg_pdfUncertUp->Add(mT_Stage1_WZ_pdfUncertUp);
  //  totalBkg_pdfUncertUp->Add(mT_Stage1_ZZ_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_QCD_HT200to300_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_QCD_HT300to500_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_QCD_HT500to700_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_QCD_HT700to1000_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_QCD_HT1000to1500_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_QCD_HT1500to2000_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_QCD_HT2000toInf_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_ZJetsToNuNu_HT100To200_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_ZJetsToNuNu_HT200To400_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_ZJetsToNuNu_HT400To600_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_ZJetsToNuNu_HT600To800_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_pdfUncertUp);
  totalBkg_pdfUncertUp->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_pdfUncertUp);

  TH1D* totalBkg_pdfUncertDown = (TH1D*)mT_Stage1_DYJetsToLL_M50_pdfUncertDown->Clone();
  totalBkg_pdfUncertDown->Add(mT_Stage1_DYJetsToLL_M5to50_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_TT_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_TT_Mtt_700to1000_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_TT_Mtt_1000toInf_pdfUncertDown);
  //  totalBkg_pdfUncertDown->Add(mT_Stage1_ST_tchannel_antitop_pdfUncertDown);
  //  totalBkg_pdfUncertDown->Add(mT_Stage1_ST_tchannel_top_pdfUncertDown);
  //  totalBkg_pdfUncertDown->Add(mT_Stage1_ST_tW_antitop_pdfUncertDown);
  //  totalBkg_pdfUncertDown->Add(mT_Stage1_ST_tW_top_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_WJetsToLNu_HT100To200_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_WJetsToLNu_HT200To400_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_WJetsToLNu_HT400To600_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_WJetsToLNu_HT600To800_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_WJetsToLNu_HT800To1200_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_WJetsToLNu_HT1200To2500_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_WJetsToLNu_HT2500ToInf_pdfUncertDown);
  //  totalBkg_pdfUncertDown->Add(mT_Stage1_WToTauNu_M100_pdfUncertDown);
  //  totalBkg_pdfUncertDown->Add(mT_Stage1_WToTauNu_M200_pdfUncertDown);
  //  totalBkg_pdfUncertDown->Add(mT_Stage1_WToTauNu_M500_pdfUncertDown);
  //  totalBkg_pdfUncertDown->Add(mT_Stage1_WToTauNu_M1000_pdfUncertDown);
  //  totalBkg_pdfUncertDown->Add(mT_Stage1_WToTauNu_M2000_pdfUncertDown);
  //  totalBkg_pdfUncertDown->Add(mT_Stage1_WToTauNu_M3000_pdfUncertDown);
  //  totalBkg_pdfUncertDown->Add(mT_Stage1_WToTauNu_M4000_pdfUncertDown);
  //  totalBkg_pdfUncertDown->Add(mT_Stage1_WToTauNu_M5000_pdfUncertDown);
  //  totalBkg_pdfUncertDown->Add(mT_Stage1_WToTauNu_M6000_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_WJetsToLNu_pdfUncertDown);
  //  totalBkg_pdfUncertDown->Add(mT_Stage1_WW_pdfUncertDown);
  //  totalBkg_pdfUncertDown->Add(mT_Stage1_WZ_pdfUncertDown);
  //  totalBkg_pdfUncertDown->Add(mT_Stage1_ZZ_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_QCD_HT200to300_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_QCD_HT300to500_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_QCD_HT500to700_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_QCD_HT700to1000_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_QCD_HT1000to1500_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_QCD_HT1500to2000_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_QCD_HT2000toInf_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_ZJetsToNuNu_HT100To200_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_ZJetsToNuNu_HT200To400_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_ZJetsToNuNu_HT400To600_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_ZJetsToNuNu_HT600To800_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_ZJetsToNuNu_HT800To1200_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500_pdfUncertDown);
  totalBkg_pdfUncertDown->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf_pdfUncertDown);
  //
  */
 //
  totalBkg->Rebin(80);
  c_totalBkg->Rebin(80);

  totalBkg_QCD->Rebin(80);
  totalBkg_wjets->Rebin(80);

  totalBkg_JetEnUp->Rebin(80);
  totalBkg_JetEnDown->Rebin(80);

  c_totalBkg_JetEnUp->Rebin(80);
  c_totalBkg_JetEnDown->Rebin(80);

  totalBkg_JetResUp->Rebin(80);
  totalBkg_JetResDown->Rebin(80);

  c_totalBkg_JetResUp->Rebin(80);
  c_totalBkg_JetResDown->Rebin(80);

  totalBkg_MuonEnUp->Rebin(80);
  totalBkg_MuonEnDown->Rebin(80);
  totalBkg_ElectronEnUp->Rebin(80);
  totalBkg_ElectronEnDown->Rebin(80);
  totalBkg_TauEnUp->Rebin(80);
  totalBkg_TauEnDown->Rebin(80);

  c_totalBkg_MuonEnUp->Rebin(80);
  c_totalBkg_MuonEnDown->Rebin(80);
  c_totalBkg_ElectronEnUp->Rebin(80);
  c_totalBkg_ElectronEnDown->Rebin(80);
  c_totalBkg_TauEnUp->Rebin(80);
  c_totalBkg_TauEnDown->Rebin(80);

  totalBkg_PhotonEnUp->Rebin(80);
  totalBkg_PhotonEnDown->Rebin(80);
  totalBkg_UnclusteredEnUp->Rebin(80);
  totalBkg_UnclusteredEnDown->Rebin(80);
  totalBkg_TauScaleUp->Rebin(80);
  totalBkg_TauScaleDown->Rebin(80);
  totalBkg_pileupUncertUp->Rebin(80);
  totalBkg_pileupUncertDown->Rebin(80);
  totalBkg_kFactorUp->Rebin(80);
  totalBkg_kFactorDown->Rebin(80);
  totalBkg_TauIDSFUp->Rebin(80);
  totalBkg_TauIDSFDown->Rebin(80);

  totalBkg_TauIDSFflatUp->Rebin(80);
  totalBkg_TauIDSFflatDown->Rebin(80);

  totalBkg_TauELESFUp->Rebin(80);
  totalBkg_TauELESFDown->Rebin(80);

  totalBkg_trigSFUp->Rebin(80);
  totalBkg_trigSFDown->Rebin(80);

  //  totalBkg_pdfUncertUp->Rebin(80);
  //  totalBkg_pdfUncertDown->Rebin(80);

  // totalBkg_lumiUp->Rebin(80);
  // totalBkg_lumiDown->Rebin(80)     ;

  TH1D* bkg_lumi_up = (TH1D*)totalBkg->Clone();
  bkg_lumi_up->Scale(wt_lumi_up);
  TH1D* bkg_lumi_down = (TH1D*)totalBkg->Clone();
  bkg_lumi_down->Scale(wt_lumi_down);

  TH1D* bkg_pdf_up = (TH1D*)totalBkg->Clone();
  bkg_pdf_up->Scale(wt_pdf_up);
  TH1D* bkg_pdf_down = (TH1D*)totalBkg->Clone();
  bkg_pdf_down->Scale(wt_pdf_down);

  float wt_QCD_up=1.5;
  float wt_QCD_down=0.5;
  TH1D* bkg_QCD_up = (TH1D*)totalBkg_QCD->Clone();
  bkg_QCD_up->Scale(wt_QCD_up);
  TH1D* bkg_QCD_down = (TH1D*)totalBkg_QCD->Clone();
  bkg_QCD_down->Scale(wt_QCD_down);

  float wt_wjets_up=1.020;
  float wt_wjets_down=0.980;
  TH1D* bkg_wjets_up = (TH1D*)totalBkg_wjets->Clone();
  bkg_wjets_up->Scale(wt_wjets_up);
  TH1D* bkg_wjets_down = (TH1D*)totalBkg_wjets->Clone();
  bkg_wjets_down->Scale(wt_wjets_down);

  int nbin1 = totalBkg->GetNbinsX();
  for (int n=0; n<nbin1; n++) {

    double delta_JetEnUp   = fabs(totalBkg_JetEnUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_JetEnDown = fabs(totalBkg_JetEnDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_JetEn = min(delta_JetEnUp,delta_JetEnDown);
  
    double delta_JetResUp   = fabs(totalBkg_JetResUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_JetResDown = fabs(totalBkg_JetResDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_JetRes = min(delta_JetResUp,delta_JetResDown);

    double delta_MuonEnUp   = fabs(totalBkg_MuonEnUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_MuonEnDown = fabs(totalBkg_MuonEnDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_MuonEn = min(delta_MuonEnUp,delta_MuonEnDown);

    double delta_ElectronEnUp   = fabs(totalBkg_ElectronEnUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_ElectronEnDown = fabs(totalBkg_ElectronEnDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_ElectronEn = min(delta_ElectronEnUp,delta_ElectronEnDown);

    double delta_TauEnUp   = fabs(totalBkg_TauEnUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_TauEnDown = fabs(totalBkg_TauEnDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_TauEn = min(delta_TauEnUp,delta_TauEnDown);

    double delta_PhotonEnUp   = fabs(totalBkg_PhotonEnUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_PhotonEnDown = fabs(totalBkg_PhotonEnDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_PhotonEn = min(delta_PhotonEnUp,delta_PhotonEnDown);

    double delta_UnclusteredEnUp   = fabs(totalBkg_UnclusteredEnUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_UnclusteredEnDown = fabs(totalBkg_UnclusteredEnDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_UnclusteredEn = min(delta_UnclusteredEnUp,delta_UnclusteredEnDown);

    double delta_TauScaleUp   = fabs(totalBkg_TauScaleUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_TauScaleDown = fabs(totalBkg_TauScaleDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_TauScale = min(delta_TauScaleUp,delta_TauScaleDown);

    double delta_pileupUncertUp   = fabs(totalBkg_pileupUncertUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_pileupUncertDown = fabs(totalBkg_pileupUncertDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_pileupUncert = min(delta_pileupUncertUp,delta_pileupUncertDown);

    double delta_kFactorUp   = fabs(totalBkg_kFactorUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_kFactorDown = fabs(totalBkg_kFactorDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_kFactor = min(delta_kFactorUp,delta_kFactorDown);
    //  std::cout << "delta_syst_kFactor = " << delta_syst_kFactor << std::endl;
 
    double delta_TauIDSFUp   = fabs(totalBkg_TauIDSFUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_TauIDSFDown = fabs(totalBkg_TauIDSFDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_TauIDSF = min(delta_TauIDSFUp,delta_TauIDSFDown);

    double delta_TauIDSFflatUp   = fabs(totalBkg_TauIDSFflatUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_TauIDSFflatDown = fabs(totalBkg_TauIDSFflatDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_TauIDSFflat = min(delta_TauIDSFflatUp,delta_TauIDSFflatDown);
    
    double delta_TauELESFUp   = fabs(totalBkg_TauELESFUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_TauELESFDown = fabs(totalBkg_TauELESFDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_TauELESF = min(delta_TauELESFUp,delta_TauELESFDown);
    
    double delta_trigSFUp   = fabs(totalBkg_trigSFUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_trigSFDown = fabs(totalBkg_trigSFDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_trigSF = min(delta_trigSFUp,delta_trigSFDown);
    
    double delta_lumiUp   = fabs(bkg_lumi_up->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_lumiDown = fabs(bkg_lumi_down->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_lumi = min(delta_lumiUp,delta_lumiDown);

    double delta_pdfUp   = fabs(bkg_pdf_up->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_pdfDown = fabs(bkg_pdf_down->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_pdf = min(delta_pdfUp,delta_pdfDown);

    double delta_QCDUp   = fabs(bkg_QCD_up->GetBinContent(n)   - totalBkg_QCD->GetBinContent(n)) ;
    double delta_QCDDown = fabs(bkg_QCD_down->GetBinContent(n) - totalBkg_QCD->GetBinContent(n)) ;
    double delta_syst_QCD = min(delta_QCDUp,delta_QCDDown);

    double delta_wjetsUp   = fabs(bkg_wjets_up->GetBinContent(n)   - totalBkg_wjets->GetBinContent(n)) ;
    double delta_wjetsDown = fabs(bkg_wjets_down->GetBinContent(n) - totalBkg_wjets->GetBinContent(n)) ;
    double delta_syst_wjets = min(delta_wjetsUp,delta_wjetsDown);

    //    std::cout << "delta_syst_lumi = " << delta_syst_lumi << std::endl;
    /// Double_t  y_lumi[200] ;
    //  y_lumi[n] = delta_syst_lumi ;

    double delta_syst_tot = sqrt( (delta_syst_JetEn*delta_syst_JetEn) + (delta_syst_JetRes*delta_syst_JetRes) + (delta_syst_MuonEn*delta_syst_MuonEn) + (delta_syst_ElectronEn*delta_syst_ElectronEn) + (delta_syst_TauEn*delta_syst_TauEn) + (delta_syst_PhotonEn*delta_syst_PhotonEn) + (delta_syst_UnclusteredEn*delta_syst_UnclusteredEn) + (delta_syst_TauScale*delta_syst_TauScale) + (delta_syst_pileupUncert*delta_syst_pileupUncert) + (delta_syst_TauIDSF*delta_syst_TauIDSF) + (delta_syst_TauIDSFflat*delta_syst_TauIDSFflat) + (delta_syst_TauELESF*delta_syst_TauELESF)+ (delta_syst_trigSF*delta_syst_trigSF) + (delta_syst_lumi*delta_syst_lumi) + (delta_syst_pdf*delta_syst_pdf) + (delta_syst_kFactor*delta_syst_kFactor) + (delta_syst_QCD*delta_syst_QCD) + (delta_syst_wjets*delta_syst_wjets) );

    totalBkg->SetBinError(n,delta_syst_tot);
  }

  //

  //  gStyle->SetErrorX(0);

  TLatex* CMS_text1 = new TLatex(0.20,0.90,"CMS");
  CMS_text1->SetNDC();
  CMS_text1->SetTextSize(0.05);
  CMS_text1->SetTextAngle(0);
  // CMS_text1->Draw("same");
  TLatex* CMS_text_21 = new TLatex(0.20,0.85,"Preliminary");
  CMS_text_21->SetNDC();
  CMS_text_21->SetTextFont(42);
  CMS_text_21->SetTextSize(0.05);
  CMS_text_21->SetTextAngle(0);
  //CMS_text_21->Draw("same");

  TLatex* lumiText1 = new TLatex(0.92,0.975,"35.9 fb^{-1} (13 TeV)");
  lumiText1->SetNDC();
  lumiText1->SetTextFont(42);
  lumiText1->SetTextSize(0.04);
  lumiText1->SetTextAlign(32);
  //  lumiText1->Draw("same");

 
  TH1* b_total_diboson =   total_diboson->GetCumulative(kFALSE);
  TH1* b_total_DY =        total_DY->GetCumulative(kFALSE);
  TH1* b_total_ST =        total_ST->GetCumulative(kFALSE);
  TH1* b_total_TT =        total_TT->GetCumulative(kFALSE);
  TH1* b_total_QCD =       total_QCD->GetCumulative(kFALSE);
  TH1* b_total_ZJets =    total_ZJets->GetCumulative(kFALSE);
  TH1* b_total_WJets =     total_WJets->GetCumulative(kFALSE);



  THStack *b_hs = new THStack("b_hs"," ");
  b_hs->Add(b_total_diboson);
  b_hs->Add(b_total_DY);
  b_hs->Add(b_total_ST);
  b_hs->Add(b_total_TT);
  b_hs->Add(b_total_QCD);
  b_hs->Add(b_total_ZJets);
  b_hs->Add(b_total_WJets);

  TCanvas* b_my_canvas = new TCanvas("backwardcumulative","b_cumulative",800,600);
  b_my_canvas->cd();
  gPad->SetLogy();
  b_hs->Draw("HIST");
  b_hs->SetMaximum(1000000);
  b_hs->SetMinimum(0.01);
  //  b_hs->GetXaxis()->SetRangeUser(300, 3000);
  b_hs->GetXaxis()->SetRangeUser(160, 3200);
  //b_hs->GetXaxis()->SetTitle("M_{T} [GeV]");
  b_hs->GetYaxis()->SetTitle("Events integrated beyond M_{T}");
  //  b_hs->GetYaxis()->SetTitleSize(0.20);


  TH1* b_mT_Stage1_Run2016all =   mT_Stage1_Run2016all->GetCumulative(kFALSE);
  b_mT_Stage1_Run2016all->Draw("SAME E X0");
  //                                                                                                                                                                                         
  TH1* b_mT_Stage1_Wprime_M4000 =   mT_Stage1_Wprime_M4000->GetCumulative(kFALSE);
  b_mT_Stage1_Wprime_M4000->Draw("SAME HIST");

   TH1* b_mT_Stage1_Wprime_M600 =   mT_Stage1_Wprime_M600->GetCumulative(kFALSE);
   b_mT_Stage1_Wprime_M600->Draw("SAME HIST");

  TH1* b_mT_Stage1_Wprime_M5000 =   mT_Stage1_Wprime_M5000->GetCumulative(kFALSE);
  b_mT_Stage1_Wprime_M5000->Draw("SAME HIST");

  TLegend *leg_example1 = new TLegend(0.43,0.55,0.75,0.94);
  leg_example1->SetFillColor(0);
  //leg_example->SetNColumns(2);
  leg_example1->SetTextFont(42);
  leg_example1->SetBorderSize(0);
  leg_example1->AddEntry(mT_Stage1_Run2016all, "Data", "pe" );
  leg_example1->AddEntry(mT_Stage1_Wprime_M600, "SSM W' 0.6 TeV", "l");
  leg_example1->AddEntry(mT_Stage1_Wprime_M4000, "SSM W' 4 TeV", "l");
  leg_example1->AddEntry(mT_Stage1_Wprime_M5000, "SSM W' 5 TeV", "l");
  leg_example1->SetTextSize(0.04);

  TLegend *leg_example2 = new TLegend(0.75,0.48,0.94,0.94);
  leg_example2->SetFillColor(0);
  //  leg_example2->SetNColumns(2);
  leg_example2->SetTextFont(42);
  leg_example2->SetBorderSize(0);
  leg_example2->AddEntry(total_WJets, "W+jets","f");
  leg_example2->AddEntry(total_ZJets, "Z(#nu#nu)jets", "f");
  leg_example2->AddEntry(total_QCD, "multijet", "f");
  leg_example2->AddEntry(total_TT, "t#bart","f");
  //leg_example->AddEntry(mT_Stage1_WJetsToLNu, "Wjets","f");
  leg_example2->AddEntry(total_ST, "Single Top", "f");
  leg_example2->AddEntry(total_DY, "DY","f");
  leg_example2->AddEntry(total_diboson, "Diboson", "f");
  leg_example2->SetTextSize(0.04);

   // leg_example->AddEntry(mT_Stage1_Run2016E, "Data", "pl" );
  // leg_example->AddEntry(mT_Stage1_Run2016D, "Data", "pl" );

  leg_example1->Draw("same");
  leg_example2->Draw("same");

  //  CMS_text->Draw("same");
  // CMS_text_2->Draw("same");
  lumiText1->Draw("same");
  b_my_canvas->Write();
  b_my_canvas->Print("BackwardCumulative.png");
  b_my_canvas->Print("BackwardCumulative.pdf");

  //--//
  THStack *hs = new THStack("hs","");
  // hs->Add(mT_Stage1_WJetsToLNu);
  //  hs->Add(mT_Stage1_DYJetsToLL_M50);
  hs->Add(total_diboson);
  hs->Add(total_DY);
  hs->Add(total_ST);
  hs->Add(total_TT);
  hs->Add(total_QCD);
  hs->Add(total_ZJets);
  hs->Add(total_WJets);
  //mT_Stage1_->SetTitle("");
  //  hs->GetYaxis()->SetTitleSize(0.20);

  totalBkg->SetFillColor(kGray+1);
  totalBkg->SetFillStyle(3001);
  // totalBkg->Draw("same e2");
  totalBkg->GetXaxis()->SetRangeUser(160,3200);

  TH1F* total =  (TH1F*)hs->GetStack()->Last()->Clone();
  TH1* c_total =  total->GetCumulative(kFALSE);


  mT_Stage1_Run2016all->GetXaxis()->SetRangeUser(160,3200);

  TH1F* mydata =  (TH1F*)mT_Stage1_Run2016all->Clone();
  TH1* c_mydata =  mydata->GetCumulative(kFALSE);

  
  TLatex* CMS_text = new TLatex(0.20,0.90,"CMS");
  CMS_text->SetNDC();
  CMS_text->SetTextSize(0.05);
  CMS_text->SetTextAngle(0);
  //  CMS_text->Draw("same");
  TLatex* CMS_text_2 = new TLatex(0.20,0.85,"Preliminary");
  CMS_text_2->SetNDC();
  CMS_text_2->SetTextFont(42);
  CMS_text_2->SetTextSize(0.05);
  CMS_text_2->SetTextAngle(0);
  //CMS_text_2->Draw("same");    

  TLatex* lumiText = new TLatex(0.92,0.975,"35.9 fb^{-1} (13 TeV)");
  lumiText->SetNDC();
  lumiText->SetTextFont(42);
  lumiText->SetTextSize(0.04);
  lumiText->SetTextAlign(32);
  // lumiText->Draw("same");     


  TCanvas* ratio_c = new TCanvas("ratio","ratio_canvas",600,700);
  ratio_c->SetTopMargin(0.); 
  ratio_c->SetBottomMargin(0.); 
  ratio_c->Update();
  ratio_c->Divide(1, 2);
  ratio_c->cd(1);
  //  gPad->SetPad(.005, .30, .995, .995);
  gPad->SetPad(.005, .35, .995, .995);
  TPad* pad1 = (TPad*)ratio_c->GetPad(1); 
  pad1->SetTopMargin(0.05);
  pad1->SetBottomMargin(0.05); 
  ratio_c->Update();
  gPad->SetLogy();
  hs->Draw("HIST");                                                                                                                                        
  // hs->GetXaxis()->SetTitle("M_{T} [GeV]");
  hs->GetYaxis()->SetTitle("Events/80 GeV");
  hs->SetMaximum(100000);
  hs->SetMinimum(0.01);
  //  hs->GetXaxis()->SetRangeUser(300, 3000);
  hs->GetXaxis()->SetRangeUser(160, 3200);
  //  hs->GetXaxis()->SetTitle("");
  hs->GetYaxis()->SetLabelSize(0.05);
  hs->GetXaxis()->SetLabelSize(0.05);
  // total->Draw("SAME E2");
  totalBkg->SetFillColor(kGray+1);
  totalBkg->SetFillStyle(3001);
  // totalBkg->Draw("same e2");
  totalBkg->GetXaxis()->SetRangeUser(160,3200);
  mydata->Draw("SAME E X0");
  int mynbin=mydata->GetNbinsX() ;

  for (int i=1; i<mynbin+1; i++) {
    float content=mydata->GetBinContent(i);
    float midbin=mydata->GetBinCenter(i);
     
    if ( (content==0) && (midbin>300) && (midbin<1700) ) {
      std::cout << "content = " << content << std::endl;
      TLine *l=new TLine(midbin,0.0,midbin,1.6);
      l->SetLineColor(kBlack);
      l->Draw("SAME");
      // delete l;
    }
  }

  mT_Stage1_Wprime_M4000->Draw("SAME HIST");
  mT_Stage1_Wprime_M600->Draw("SAME HIST");
  mT_Stage1_Wprime_M5000->Draw("SAME HIST");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  lumiText->Draw("same");
  leg_example1->Draw("same");
  leg_example2->Draw("same");
  ratio_c->cd(2);
  //  gPad->SetPad(.005, .08, .995, .24); 
  gPad->SetPad(.005, .1, .995, .32); 
  gStyle->SetOptStat(false);
  ratio_c->Update();
  TPad* pad2 = (TPad*)ratio_c->GetPad(2);
  pad2->SetTopMargin(0.05); 
  pad2->SetBottomMargin(0.4); 
  pad2->SetGridx();
  pad2->SetGridy();
  std::cout << "data bins = " << mydata->GetNbinsX() << " width=" << mydata->GetBinWidth(2);
  std::cout << " MC bins = " << total->GetNbinsX() << " width=" << total->GetBinWidth(2) << std::endl;
  int nbin=mydata->GetNbinsX() ;
  float width=mydata->GetBinWidth(2);
  TH1F *data_by_MC = new TH1F("h12", "ratio", nbin, 0, 8000);
  TH1F *data_by_MC_syst = new TH1F("h2", "ratio_syst", nbin, 0, 8000);
  std::cout << "before D/MC bins=" << data_by_MC->GetNbinsX() << " width=" << data_by_MC->GetBinWidth(2) << std::endl;
  for (int i=0; i<nbin; i++) {
    float data = mydata->GetBinContent(i);
    float MC = total->GetBinContent(i);
    float syst_err = totalBkg->GetBinError(i);
    float ratio=0;
    if (MC>0) ratio=data/MC ;
    data_by_MC->SetBinContent(i,ratio);
    if (data>0) {
      //      float stat_err = sqrt(data) ;  
      float stat_err = sqrt(data)/data ;  
      data_by_MC->SetBinError(i,stat_err);
    }
    data_by_MC_syst->SetBinContent(i,1.0);
    //   float ratio_syst_err = (data/(MC*MC))*syst_err  ;  // abs error : sigma_f , where f = data/mc
    float ratio_syst_err = (syst_err/MC) ;  // relative error : sigma_f / f , where f = data/mc
    if (data==0 && MC==0) ratio_syst_err=0;
    data_by_MC_syst->SetBinError(i,ratio_syst_err);
    // data_by_MC->SetBinWidth(i,width);  
  }

  //  TH1F* data_by_MC = (TH1F*)mydata->Clone();
  // data_by_MC->Divide(total);
  data_by_MC->SetMarkerStyle(20);
  data_by_MC_syst->SetFillColor(kGray);
  data_by_MC_syst->SetFillStyle(3001);
  data_by_MC_syst->Draw("e2");
  data_by_MC->Draw("same E X0");
  data_by_MC_syst->GetXaxis()->SetTitle("M_{T} (GeV)");
  data_by_MC_syst->GetYaxis()->SetTitle("#frac{DATA}{MC}");
  data_by_MC_syst->GetYaxis()->SetLabelSize(0.10);
  data_by_MC_syst->GetXaxis()->SetLabelSize(0.15);
  data_by_MC_syst->GetYaxis()->SetTitleSize(0.15);
  data_by_MC_syst->GetXaxis()->SetTitleSize(0.18);
  data_by_MC_syst->GetYaxis()->SetTitleOffset(0.28);
  data_by_MC_syst->GetXaxis()->SetTitleOffset(0.90);
  data_by_MC_syst->SetTitle("");
  data_by_MC_syst->GetXaxis()->SetRangeUser(160, 3200);
  data_by_MC_syst->SetMaximum(2);
  data_by_MC_syst->SetMinimum(0);
  data_by_MC_syst->GetYaxis()->SetNdivisions(4);

  TLine *l=new TLine(160,1,3200,1);
  l->SetLineColor(kRed);
  l->Draw("same");

  std::cout << "D/MC bins=" << data_by_MC->GetNbinsX() << " width=" << data_by_MC->GetBinWidth(2) << std::endl;
  ratio_c->Write();
  ratio_c->Update();

  ratio_c->Print("mT_Stage1_ratio_syst.pdf");
  ratio_c->Print("mT_Stage1_ratio_syst.png");
  /////

  //cumulative syst band
  int c_nbin1 = c_totalBkg->GetNbinsX();
  for (int n=1; n<c_nbin1+1; n++) {
    std::cout << "n=" << n << std::endl;
    double c_delta_JetEnUp   = fabs(c_totalBkg_JetEnUp->GetBinContent(n)   - c_totalBkg->GetBinContent(n)) ;
    double c_delta_JetEnDown = fabs(c_totalBkg_JetEnDown->GetBinContent(n) - c_totalBkg->GetBinContent(n)) ;
    double c_delta_syst_JetEn = min(c_delta_JetEnUp,c_delta_JetEnDown);
    if ((c_delta_syst_JetEn/c_totalBkg->GetBinContent(n) > 0.01)) c_delta_syst_JetEn=0; 
    // std::cout << "c_totalBkg_JetEnUp->GetBinContent(n) " << c_totalBkg_JetEnUp->GetBinContent(n) << std::endl;
    // std::cout << "c_totalBkg_JetEnDown->GetBinContent(n) " << c_totalBkg_JetEnDown->GetBinContent(n) << std::endl;
    // std::cout << "c_totalBkg->GetBinContent(n) " << c_totalBkg->GetBinContent(n) << std::endl;
    // std::cout << "c_delta_syst_JetEn " << c_delta_syst_JetEn << std::endl;
   
    double c_delta_JetResUp   = fabs(c_totalBkg_JetResUp->GetBinContent(n)   - c_totalBkg->GetBinContent(n)) ;
    double c_delta_JetResDown = fabs(c_totalBkg_JetResDown->GetBinContent(n) - c_totalBkg->GetBinContent(n)) ;
    double c_delta_syst_JetRes = min(c_delta_JetResUp,c_delta_JetResDown);
    if ((c_delta_syst_JetRes/c_totalBkg->GetBinContent(n) > 0.01)) c_delta_syst_JetRes=0; 
    // std::cout << "c_delta_syst_JetRes " << c_delta_syst_JetRes << std::endl;

    double c_delta_MuonEnUp   = fabs(c_totalBkg_MuonEnUp->GetBinContent(n)   - c_totalBkg->GetBinContent(n)) ;
    double c_delta_MuonEnDown = fabs(c_totalBkg_MuonEnDown->GetBinContent(n) - c_totalBkg->GetBinContent(n)) ;
    double c_delta_syst_MuonEn = min(c_delta_MuonEnUp,c_delta_MuonEnDown);
    if ((c_delta_syst_MuonEn/c_totalBkg->GetBinContent(n) > 0.01)) c_delta_syst_MuonEn=0; 
    // std::cout << "c_totalBkg_MuonEnUp->GetBinContent(n) = " << c_totalBkg_MuonEnUp->GetBinContent(n) << std::endl;
    // std::cout  << "c_totalBkg_MuonEnDown->GetBinContent(n) = " << c_totalBkg_MuonEnDown->GetBinContent(n) << std::endl;
    //std::cout << "c_delta_syst_MuonEn " << c_delta_syst_MuonEn << std::endl;

    double c_delta_ElectronEnUp   = fabs(c_totalBkg_ElectronEnUp->GetBinContent(n)   - c_totalBkg->GetBinContent(n)) ;
    double c_delta_ElectronEnDown = fabs(c_totalBkg_ElectronEnDown->GetBinContent(n) - c_totalBkg->GetBinContent(n)) ;
    double c_delta_syst_ElectronEn = min(c_delta_ElectronEnUp,c_delta_ElectronEnDown);
    if ((c_delta_syst_ElectronEn/c_totalBkg->GetBinContent(n) > 0.01)) c_delta_syst_ElectronEn=0; 
    // std::cout << "c_delta_syst_ElectronEn " << c_delta_syst_ElectronEn << std::endl;

    double c_delta_TauEnUp   = fabs(c_totalBkg_TauEnUp->GetBinContent(n)   - c_totalBkg->GetBinContent(n)) ;
    double c_delta_TauEnDown = fabs(c_totalBkg_TauEnDown->GetBinContent(n) - c_totalBkg->GetBinContent(n)) ;
    double c_delta_syst_TauEn = min(c_delta_TauEnUp,c_delta_TauEnDown);
    if ((c_delta_syst_TauEn/c_totalBkg->GetBinContent(n) > 0.10)) c_delta_syst_TauEn=0; 
    // std::cout << "c_delta_syst_TauEn " << c_delta_syst_TauEn << std::endl;
    /*
    double delta_PhotonEnUp   = fabs(totalBkg_PhotonEnUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_PhotonEnDown = fabs(totalBkg_PhotonEnDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_PhotonEn = min(delta_PhotonEnUp,delta_PhotonEnDown);

    double delta_UnclusteredEnUp   = fabs(totalBkg_UnclusteredEnUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_UnclusteredEnDown = fabs(totalBkg_UnclusteredEnDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_UnclusteredEn = min(delta_UnclusteredEnUp,delta_UnclusteredEnDown);

    double delta_TauScaleUp   = fabs(totalBkg_TauScaleUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_TauScaleDown = fabs(totalBkg_TauScaleDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_TauScale = min(delta_TauScaleUp,delta_TauScaleDown);

    double delta_pileupUncertUp   = fabs(totalBkg_pileupUncertUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_pileupUncertDown = fabs(totalBkg_pileupUncertDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_pileupUncert = min(delta_pileupUncertUp,delta_pileupUncertDown);

    double delta_kFactorUp   = fabs(totalBkg_kFactorUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_kFactorDown = fabs(totalBkg_kFactorDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_kFactor = min(delta_kFactorUp,delta_kFactorDown);
    //  std::cout << "delta_syst_kFactor = " << delta_syst_kFactor << std::endl;
 
    double delta_TauIDSFUp   = fabs(totalBkg_TauIDSFUp->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_TauIDSFDown = fabs(totalBkg_TauIDSFDown->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_TauIDSF = min(delta_TauIDSFUp,delta_TauIDSFDown);
    
    double delta_lumiUp   = fabs(bkg_lumi_up->GetBinContent(n)   - totalBkg->GetBinContent(n)) ;
    double delta_lumiDown = fabs(bkg_lumi_down->GetBinContent(n) - totalBkg->GetBinContent(n)) ;
    double delta_syst_lumi = min(delta_lumiUp,delta_lumiDown);

    double delta_QCDUp   = fabs(bkg_QCD_up->GetBinContent(n)   - totalBkg_QCD->GetBinContent(n)) ;
    double delta_QCDDown = fabs(bkg_QCD_down->GetBinContent(n) - totalBkg_QCD->GetBinContent(n)) ;
    double delta_syst_QCD = min(delta_QCDUp,delta_QCDDown);
    */
    //    std::cout << "delta_syst_lumi = " << delta_syst_lumi << std::endl;
    /// Double_t  y_lumi[200] ;
    //  y_lumi[n] = delta_syst_lumi ;

    double c_delta_syst_tot = sqrt( (c_delta_syst_JetEn*c_delta_syst_JetEn) + (c_delta_syst_JetRes*c_delta_syst_JetRes) + (c_delta_syst_MuonEn*c_delta_syst_MuonEn) + (c_delta_syst_ElectronEn*c_delta_syst_ElectronEn) + (c_delta_syst_TauEn*c_delta_syst_TauEn) ) ; //+ (delta_syst_PhotonEn*delta_syst_PhotonEn) + (delta_syst_UnclusteredEn*delta_syst_UnclusteredEn) + (delta_syst_TauScale*delta_syst_TauScale) + (delta_syst_pileupUncert*delta_syst_pileupUncert) + (delta_syst_TauIDSF*delta_syst_TauIDSF) + (delta_syst_lumi*delta_syst_lumi) + (delta_syst_kFactor*delta_syst_kFactor) + (delta_syst_QCD*delta_syst_QCD) );
    // std::cout << "err=" << c_delta_syst_tot << std::endl;
    c_totalBkg->SetBinError(n,c_delta_syst_tot);
  }



  //////
  ////cumulative with syst band
  ///////
  TCanvas* c2_ratio_c = new TCanvas("c2_ratio","c2_ratio_canvas",600,700);
  c2_ratio_c->SetTopMargin(0.); 
  c2_ratio_c->SetBottomMargin(0.); 
  c2_ratio_c->Update();
  c2_ratio_c->Divide(1, 2);
  c2_ratio_c->cd(1);
  //  gPad->SetPad(.005, .30, .995, .995);
  gPad->SetPad(.005, .35, .995, .995);
  TPad* c_pad1 = (TPad*)c2_ratio_c->GetPad(1); 
  c_pad1->SetTopMargin(0.05);
  c_pad1->SetBottomMargin(0.05); 
  c2_ratio_c->Update();
  gPad->SetLogy();
  b_hs->Draw("HIST");                                                                                                                                        
  // b_hs->GetXaxis()->SetTitle("M_{T} [GeV]");
  b_hs->GetYaxis()->SetTitle("Events integrated beyond M_{T}");
  b_hs->SetMaximum(100000);
  b_hs->SetMinimum(0.01);
  //  b_hs->GetXaxis()->SetRangeUser(300, 3000);
  b_hs->GetXaxis()->SetRangeUser(160, 3200);
  //  hs->GetXaxis()->SetTitle("");
  b_hs->GetYaxis()->SetLabelSize(0.05);
  b_hs->GetXaxis()->SetLabelSize(0.05);
  // total->Draw("SAME E2");
  c_totalBkg->SetFillColor(kGray+1);
  c_totalBkg->SetFillStyle(3001);
  // totalBkg->Draw("same e2");
  c_totalBkg->GetXaxis()->SetRangeUser(160,3200);
  c_mydata->Draw("SAME E X0");
  b_mT_Stage1_Wprime_M4000->Draw("SAME HIST");
  b_mT_Stage1_Wprime_M600->Draw("SAME HIST");
  b_mT_Stage1_Wprime_M5000->Draw("SAME HIST");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  lumiText->Draw("same");
  leg_example1->Draw("same");
  leg_example2->Draw("same");
  c2_ratio_c->cd(2);
  //  gPad->SetPad(.005, .08, .995, .24); 
  gPad->SetPad(.005, .1, .995, .32); 
  gStyle->SetOptStat(false);
  c2_ratio_c->Update();
  TPad* c_pad2 = (TPad*)c2_ratio_c->GetPad(2);
  c_pad2->SetTopMargin(0.05); 
  c_pad2->SetBottomMargin(0.4); 
  c_pad2->SetGridx();
  c_pad2->SetGridy();
  std::cout << "cumulative data bins = " << c_mydata->GetNbinsX() << " width=" << c_mydata->GetBinWidth(2);
  std::cout << "cumulative  MC bins = " << c_total->GetNbinsX() << " width=" << c_total->GetBinWidth(2) << std::endl;
  int c_nbin=c_mydata->GetNbinsX() ;
  float c_width=c_mydata->GetBinWidth(2);
  TH1F *c_data_by_MC = new TH1F("c_h12", "c_ratio", c_nbin, 0, 8000);
  TH1F *c_data_by_MC_syst = new TH1F("c_h2", "c_ratio_syst", c_nbin, 0, 8000);
  std::cout << "before D/MC bins=" << c_data_by_MC->GetNbinsX() << " width=" << c_data_by_MC->GetBinWidth(2) << std::endl;
  float seebefore=1;
  for (int i=1; i<c_nbin+1; i++) {
    float c_data = c_mydata->GetBinContent(i);
    float c_MC = c_total->GetBinContent(i);
    float MC = total->GetBinContent(i);
    float c_syst_err = totalBkg->GetBinError(i);
    float c_ratio=0;
    if (c_MC>0) c_ratio=c_data/c_MC ;
    c_data_by_MC->SetBinContent(i,c_ratio);
    if (c_data>0) {
      float c_stat_err = sqrt(c_data)/c_data ;  
      c_data_by_MC->SetBinError(i,c_stat_err);
    }
    c_data_by_MC_syst->SetBinContent(i,1.0);
    //   float ratio_syst_err = (data/(MC*MC))*syst_err  ;  // abs error : sigma_f , where f = data/mc
    //    float c_ratio_syst_err = (c_syst_err/c_MC) ;  // relative error : sigma_f / f , where f = data/mc
    float c_ratio_syst_err= 0.45;
    if (MC>0) c_ratio_syst_err = (c_syst_err/MC) ;  // relative error : sigma_f / f , where f = data/mc
    // if (i==1) c_ratio_syst_err=0.45;
    if (c_ratio_syst_err>0.5) c_ratio_syst_err=0.45;
    if (c_ratio_syst_err/seebefore > 1.4) c_ratio_syst_err=seebefore;
    //   float c_ratio_syst_err = (c_syst_err) ;  // relative error : sigma_f / f , where f = data/mc
    // std::cout << "i=" << i << " err=" << c_syst_err << " nMC=" << c_MC << " rel_err=" << c_ratio_syst_err << std::endl;
    if (c_data==0 && c_MC==0) c_ratio_syst_err=0;
    c_data_by_MC_syst->SetBinError(i,c_ratio_syst_err);
    seebefore=c_ratio_syst_err;
    // data_by_MC->SetBinWidth(i,width);  
  }

  //  TH1F* data_by_MC = (TH1F*)mydata->Clone();
  // data_by_MC->Divide(total);
  c_data_by_MC->SetMarkerStyle(20);
  c_data_by_MC_syst->SetFillColor(kGray);
  c_data_by_MC_syst->SetFillStyle(3001);
  c_data_by_MC_syst->Draw("e2");
  c_data_by_MC->Draw("same E X0");
  c_data_by_MC_syst->GetXaxis()->SetTitle("M_{T} (GeV)");
  c_data_by_MC_syst->GetYaxis()->SetTitle("#frac{DATA}{MC}");
  c_data_by_MC_syst->GetYaxis()->SetLabelSize(0.10);
  c_data_by_MC_syst->GetXaxis()->SetLabelSize(0.15);
  c_data_by_MC_syst->GetYaxis()->SetTitleSize(0.15);
  c_data_by_MC_syst->GetXaxis()->SetTitleSize(0.18);
  c_data_by_MC_syst->GetYaxis()->SetTitleOffset(0.28);
  c_data_by_MC_syst->GetXaxis()->SetTitleOffset(0.90);
  c_data_by_MC_syst->SetTitle("");
  c_data_by_MC_syst->GetXaxis()->SetRangeUser(160, 3200);
  c_data_by_MC_syst->SetMaximum(2);
  c_data_by_MC_syst->SetMinimum(0);
  c_data_by_MC_syst->GetYaxis()->SetNdivisions(4);

  TLine *c_l=new TLine(160,1,3200,1);
  c_l->SetLineColor(kRed);
  c_l->Draw("same");

  std::cout << "D/MC bins=" << c_data_by_MC->GetNbinsX() << " width=" << c_data_by_MC->GetBinWidth(2) << std::endl;
  c2_ratio_c->Write();
  c2_ratio_c->Print("c2_mT_Stage1_ratio_syst.pdf");
  c2_ratio_c->Print("c2_mT_Stage1_ratio_syst.png");
  /////


  /*
  TCanvas* c_ratio_c = new TCanvas("c_ratio_c","c_ratio_canvas_c",600,800);
  c_ratio_c->SetTopMargin(0.);
  c_ratio_c->SetBottomMargin(0.);
  c_ratio_c->Update();
  c_ratio_c->Divide(1, 2);
  c_ratio_c->cd(1);

  gPad->SetPad(.005, .32, .995, .995);
  TPad* c_pad1 = (TPad*)c_ratio_c->GetPad(1);
  c_pad1->SetTopMargin(0.05);
  c_pad1->SetBottomMargin(0.05);

  c_ratio_c->Update();
  gPad->SetLogy();

  b_hs->Draw("HIST");
  b_hs->SetMaximum(1000000);
  b_hs->SetMinimum(0.01);
  b_hs->GetXaxis()->SetRangeUser(0, 3000);
  b_hs->GetXaxis()->SetTitle("");
  // total->Draw("SAME E2");                                                                                                                                                         
  b_hs->GetYaxis()->SetLabelSize(0.05);
  b_hs->GetXaxis()->SetLabelSize(0.05);
 
  c_totalBkg->SetFillColor(kGray+1);
  c_totalBkg->SetFillStyle(3001);
  // totalBkg->Draw("same e2");                                                                                                                                                       
  c_totalBkg->GetXaxis()->SetRangeUser(0,3000);
  c_mydata->Draw("SAME E1");
  c_mydata->GetXaxis()->SetRangeUser(0,3000);
  b_mT_Stage1_Wprime_M4000->Draw("SAME HIST");
  b_mT_Stage1_Wprime_M600->Draw("SAME HIST");
  b_mT_Stage1_Wprime_M5000->Draw("SAME HIST");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  lumiText->Draw("same");
  leg_example->Draw("same");
  c_ratio_c->cd(2);

  //  gPad->SetPad(.005, .08, .995, .24);
  gPad->SetPad(.005, .1, .995, .29);
  gStyle->SetOptStat(false);
  c_ratio_c->Update();
  TPad* c_pad2 = (TPad*)c_ratio_c->GetPad(2);
  c_pad2->SetTopMargin(0.05);
  c_pad2->SetBottomMargin(0.4);
  c_pad2->SetGridx();
  c_pad2->SetGridy();
  int c_nbin=c_mydata->GetNbinsX() ;
  float c_width=c_mydata->GetBinWidth(2);
  TH1F *c_data_by_MC = new TH1F("c_h1", "c_ratio", c_nbin, 0, 8000);
  TH1F *c_data_by_MC_syst = new TH1F("c_h2", "c_ratio_syst", c_nbin, 0, 8000);
  // std::cout << "before D/MC bins=" << c_data_by_MC->GetNbinsX() << " width=" << c_data_by_MC->GetBinWidth(2) << std::endl;                                                         

  for (int i=0; i<c_nbin; i++) {
    float c_data = c_mydata->GetBinContent(i);
    float c_MC = c_total->GetBinContent(i);
    float c_syst_err = c_totalBkg->GetBinError(i);
    float c_ratio=0;
    if (c_MC>0) c_ratio=c_data/c_MC ;
    c_data_by_MC->SetBinContent(i,c_ratio);
    if (c_data>0) {
      float c_stat_err = sqrt(c_data)/c_data ;
      c_data_by_MC->SetBinError(i,c_stat_err);
    }
    c_data_by_MC_syst->SetBinContent(i,1.0);
    //   float ratio_syst_err = (data/(MC*MC))*syst_err  ;  // abs error : sigma_f , where f = data/mc                                                                                
    float c_ratio_syst_err = (c_syst_err/c_MC) ;  // relative error : sigma_f / f , where f = data/mc                                                                                 
    // std::cout << "c_syst_err/c_MC = " << c_syst_err << "/" << c_MC << std::endl;                                                                                                   
    // std::cout << "c_ratio_syst_err = " << c_ratio_syst_err << std::endl;                                                                                                           
    if (c_data==0 && c_MC==0) c_ratio_syst_err=0;
    c_data_by_MC_syst->SetBinError(i,0);

    // data_by_MC->SetBinWidth(i,width);                                                                                                                                              
  }

  c_data_by_MC->SetMarkerStyle(20);
  c_data_by_MC->Draw("same E");
  c_data_by_MC->GetXaxis()->SetTitle("M_{T} [GeV]");
  c_data_by_MC->GetYaxis()->SetTitle("#frac{DATA}{MC}");
  c_data_by_MC->GetYaxis()->SetLabelSize(0.15);
  c_data_by_MC->GetXaxis()->SetLabelSize(0.15);
  c_data_by_MC->GetYaxis()->SetTitleSize(0.20);
  c_data_by_MC->GetXaxis()->SetTitleSize(0.20);
  c_data_by_MC->GetYaxis()->SetTitleOffset(0.22);
  c_data_by_MC->GetXaxis()->SetTitleOffset(0.90);
  c_data_by_MC->SetTitle("");
  c_data_by_MC->GetXaxis()->SetRangeUser (0, 3000);
  c_data_by_MC->SetMaximum(2);
  c_data_by_MC->SetMinimum(0);
  c_data_by_MC->GetYaxis()->SetNdivisions(2);

  TLine *c_l=new TLine(0,1,3000,1);
  c_l->SetLineColor(kRed);
  c_l->Draw("same");
  c_ratio_c->Write();
  c_ratio_c->Print("c_mT_Stage1_ratio_syst.pdf");
  c_ratio_c->Print("c_mT_Stage1_ratio_syst.png");


  */
  return 0;

}

//  LocalWords:  SetLineColor
