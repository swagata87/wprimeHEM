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

int Reminiaodcompare_MET() {


  /// reminiaod DATA ///
  TFile *file_Tau_Run2016B = new TFile("../python/crab_projects_March3/crab_Tau_Run2016B/results/hist.root");
  TFile *file_Tau_Run2016C = new TFile("../python/crab_projects_March3/crab_Tau_Run2016C/results/hist.root");
  TFile *file_Tau_Run2016D = new TFile("../python/crab_projects_March3/crab_Tau_Run2016D/results/hist.root");
  TFile *file_Tau_Run2016E = new TFile("../python/crab_projects_March3/crab_Tau_Run2016E/results/hist.root");
  TFile *file_Tau_Run2016F = new TFile("../python/crab_projects_March3/crab_Tau_Run2016F/results/hist.root");
  TFile *file_Tau_Run2016G = new TFile("../python/crab_projects_March3/crab_Tau_Run2016G/results/hist.root");
  TFile *file_Tau_Run2016H_v2 = new TFile("../python/crab_projects_March3/crab_Tau_Run2016H_1/results/hist.root");
  TFile *file_Tau_Run2016H_v3 = new TFile("../python/crab_projects_March3/crab_Tau_Run2016H_2/results/hist.root");


   std::cout << "will do data" << std::endl;
  
  //--Data--//
   TH1D* met_Stage1_Run2016F  =  (TH1D*)file_Tau_Run2016F->Get("demo/histoDir/met_Stage1");
   TH1D* met_Stage1_Run2016E  =  (TH1D*)file_Tau_Run2016E->Get("demo/histoDir/met_Stage1");
   TH1D* met_Stage1_Run2016D  =  (TH1D*)file_Tau_Run2016D->Get("demo/histoDir/met_Stage1");
   TH1D* met_Stage1_Run2016C  =  (TH1D*)file_Tau_Run2016C->Get("demo/histoDir/met_Stage1");
   TH1D* met_Stage1_Run2016B  =  (TH1D*)file_Tau_Run2016B->Get("demo/histoDir/met_Stage1");
   TH1D* met_Stage1_Run2016G  =  (TH1D*)file_Tau_Run2016G->Get("demo/histoDir/met_Stage1");
   TH1D* met_Stage1_Run2016H_v2  = (TH1D*)file_Tau_Run2016H_v2->Get("demo/histoDir/met_Stage1");
   TH1D* met_Stage1_Run2016H_v3  = (TH1D*)file_Tau_Run2016H_v3->Get("demo/histoDir/met_Stage1");
   

  TH1D* met_Stage1_Run2016all = (TH1D*)met_Stage1_Run2016B->Clone();
  met_Stage1_Run2016all->Add(met_Stage1_Run2016C);
  met_Stage1_Run2016all->Add(met_Stage1_Run2016D);
  met_Stage1_Run2016all->Add(met_Stage1_Run2016E);
  met_Stage1_Run2016all->Add(met_Stage1_Run2016F);
  met_Stage1_Run2016all->Add(met_Stage1_Run2016G);
  met_Stage1_Run2016all->Add(met_Stage1_Run2016H_v2);
  met_Stage1_Run2016all->Add(met_Stage1_Run2016H_v3);
                                                                                                                                    
  met_Stage1_Run2016all->SetMarkerStyle(20);
  met_Stage1_Run2016all->SetMarkerColor(kBlack);
  met_Stage1_Run2016all->SetLineColor(kBlack);
  met_Stage1_Run2016all->Rebin(50);

  ////

  /// rereco old DATA ///
  TFile *file_Tau_Run2016B_old = new TFile("/net/scratch_cms3a/mukherjee/Ana_Oct14/CMSSW_8_0_25/src/WPrimeToTau/MiniAODAnalyzer/python/crab_projects_Jan14_CorrectJSON/crab_Tau_Run2016B_23Sep2016_v3/results/hist.root");
  TFile *file_Tau_Run2016C_old = new TFile("/net/scratch_cms3a/mukherjee/Ana_Oct14/CMSSW_8_0_25/src/WPrimeToTau/MiniAODAnalyzer/python/crab_projects_Jan14_CorrectJSON/crab_Tau_Run2016C_23Sep2016_v1/results/hist.root");
  TFile *file_Tau_Run2016D_old = new TFile("/net/scratch_cms3a/mukherjee/Ana_Oct14/CMSSW_8_0_25/src/WPrimeToTau/MiniAODAnalyzer/python/crab_projects_Jan14_CorrectJSON/crab_Tau_Run2016D_23Sep2016_v1/results/hist.root");
  TFile *file_Tau_Run2016E_old = new TFile("/net/scratch_cms3a/mukherjee/Ana_Oct14/CMSSW_8_0_25/src/WPrimeToTau/MiniAODAnalyzer/python/crab_projects_Jan14_CorrectJSON/crab_Tau_Run2016E_23Sep2016_v1/results/hist.root");
  TFile *file_Tau_Run2016F_old = new TFile("/net/scratch_cms3a/mukherjee/Ana_Oct14/CMSSW_8_0_25/src/WPrimeToTau/MiniAODAnalyzer/python/crab_projects_Jan15/crab_Tau_Run2016F_23Sep2016_v1/results/hist.root");
  TFile *file_Tau_Run2016G_old = new TFile("/net/scratch_cms3a/mukherjee/Ana_Oct14/CMSSW_8_0_25/src/WPrimeToTau/MiniAODAnalyzer/python/crab_projects_Jan15/crab_Tau_Run2016G_23Sep2016_v1/results/hist.root");
  TFile *file_Tau_Run2016H_v2_old = new TFile("/net/scratch_cms3a/mukherjee/Ana_Oct14/CMSSW_8_0_25/src/WPrimeToTau/MiniAODAnalyzer/python/crab_projects_Jan15/crab_Tau_Run2016H_PromptReco_v2/results/hist.root");
  TFile *file_Tau_Run2016H_v3_old = new TFile("/net/scratch_cms3a/mukherjee/Ana_Oct14/CMSSW_8_0_25/src/WPrimeToTau/MiniAODAnalyzer/python/crab_projects_Jan14_CorrectJSON/crab_Tau_Run2016H_PromptReco_v3/results/hist.root");


   std::cout << "will do data" << std::endl;
  
  //--Data--//
   TH1D* met_Stage1_Run2016F_old  =  (TH1D*)file_Tau_Run2016F_old->Get("demo/histoDir/met_Stage1");
   TH1D* met_Stage1_Run2016E_old  =  (TH1D*)file_Tau_Run2016E_old->Get("demo/histoDir/met_Stage1");
   TH1D* met_Stage1_Run2016D_old  =  (TH1D*)file_Tau_Run2016D_old->Get("demo/histoDir/met_Stage1");
   TH1D* met_Stage1_Run2016C_old  =  (TH1D*)file_Tau_Run2016C_old->Get("demo/histoDir/met_Stage1");
   TH1D* met_Stage1_Run2016B_old  =  (TH1D*)file_Tau_Run2016B_old->Get("demo/histoDir/met_Stage1");
   TH1D* met_Stage1_Run2016G_old  =  (TH1D*)file_Tau_Run2016G_old->Get("demo/histoDir/met_Stage1");
   TH1D* met_Stage1_Run2016H_v2_old  = (TH1D*)file_Tau_Run2016H_v2_old->Get("demo/histoDir/met_Stage1");
   TH1D* met_Stage1_Run2016H_v3_old  = (TH1D*)file_Tau_Run2016H_v3_old->Get("demo/histoDir/met_Stage1");
   

  TH1D* met_Stage1_Run2016all_old = (TH1D*)met_Stage1_Run2016B_old->Clone();
  met_Stage1_Run2016all_old->Add(met_Stage1_Run2016C_old);
  met_Stage1_Run2016all_old->Add(met_Stage1_Run2016D_old);
  met_Stage1_Run2016all_old->Add(met_Stage1_Run2016E_old);
  met_Stage1_Run2016all_old->Add(met_Stage1_Run2016F_old);
  met_Stage1_Run2016all_old->Add(met_Stage1_Run2016G_old);
  met_Stage1_Run2016all_old->Add(met_Stage1_Run2016H_v2_old);
  met_Stage1_Run2016all_old->Add(met_Stage1_Run2016H_v3_old);
                                                                                                                                    
  met_Stage1_Run2016all_old->SetMarkerStyle(24);
  met_Stage1_Run2016all_old->SetMarkerColor(kBlue);
  met_Stage1_Run2016all_old->SetLineColor(kBlue);
  met_Stage1_Run2016all_old->Rebin(50);
  

 
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
  TFile* outputFile = new TFile("comp_reminiaod_pt.root","RECREATE");
  outputFile->cd();

  //--//
 
  TCanvas* my_canvas = new TCanvas("canvas","canvas",800,600);
  my_canvas->cd();
  gPad->SetLogy();

  met_Stage1_Run2016all->Draw("E0");
  met_Stage1_Run2016all_old->Draw("SAME E0");

  met_Stage1_Run2016all->SetMaximum(100000);
  met_Stage1_Run2016all->SetMinimum(0.1);
  met_Stage1_Run2016all->GetXaxis()->SetRangeUser(100, 1200);
  met_Stage1_Run2016all->GetXaxis()->SetTitle("#tau pT [GeV]"); 
  met_Stage1_Run2016all->GetYaxis()->SetTitle("Events");

  TH1F* mydata =  (TH1F*)met_Stage1_Run2016all->Clone();
  TH1F* mydata_old =  (TH1F*)met_Stage1_Run2016all_old->Clone();

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


  TLatex* lumiText = new TLatex(0.92,0.975,"Era 2016 B-H (13 TeV)");
  lumiText->SetNDC();
  lumiText->SetTextFont(42);
  lumiText->SetTextSize(0.04);
  lumiText->SetTextAlign(32);
  lumiText->Draw("same");     

  TLegend *leg_example = new TLegend(0.65,0.70,0.94,0.94);
  leg_example->SetFillColor(0);
  leg_example->SetTextFont(42);
  leg_example->SetBorderSize(0);
  leg_example->AddEntry(met_Stage1_Run2016all, "Re-MiniAOD Data", "pl" );
  leg_example->AddEntry(met_Stage1_Run2016all_old, "Old Data", "pl" );
  leg_example->Draw("same");
  
  my_canvas->Write();
  my_canvas->Print("reminiaod_compare_tauMET.pdf");

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
  
  mydata->GetXaxis()->SetTitle("");
  mydata->SetTitle("");
 
  // total->Draw("SAME E2");
  mydata->Draw("E1");
  mydata_old->Draw("SAME E1");
  
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  lumiText->Draw("same");
  leg_example->Draw("same");
  ratio_c->cd(2);

  gPad->SetPad(.005, .08, .995, .28); 
  gStyle->SetOptStat(false);
  ratio_c->Update();
  TPad* pad2 = (TPad*)ratio_c->GetPad(2);
  pad2->SetTopMargin(0.04); 
  pad2->SetBottomMargin(0.30); 
  pad2->SetGridx();
  pad2->SetGridy();

  std::cout << "data 1 bins = " << mydata->GetNbinsX() << " width=" << mydata->GetBinWidth(2);
  std::cout << "data 2 bins = " << mydata_old->GetNbinsX() << " width=" << mydata_old->GetBinWidth(2) << std::endl;

  int nbin=mydata->GetNbinsX() ;
  float width=mydata->GetBinWidth(2);
  TH1F *data_by_MC = new TH1F("h1", "ratio", nbin, 0, 8000);
  std::cout << "before D/MC bins=" << data_by_MC->GetNbinsX() << " width=" << data_by_MC->GetBinWidth(2) << std::endl;

  for (int i=0; i<nbin; i++) {
    float data = mydata->GetBinContent(i);
    float MC = mydata_old->GetBinContent(i);
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
  data_by_MC->GetXaxis()->SetTitle("MET [GeV]");
  data_by_MC->GetYaxis()->SetTitle("#frac{new}{old}");
  data_by_MC->GetYaxis()->SetLabelSize(0.12);
  data_by_MC->GetXaxis()->SetLabelSize(0.12);
  data_by_MC->GetYaxis()->SetTitleSize(0.18);
  data_by_MC->GetXaxis()->SetTitleSize(0.18);
  data_by_MC->GetYaxis()->SetTitleOffset(0.20);
  data_by_MC->GetXaxis()->SetTitleOffset(0.75);
  data_by_MC->SetTitle("");
  data_by_MC->GetXaxis()->SetRangeUser(100, 1200);
  data_by_MC->SetMaximum(2);
  data_by_MC->SetMinimum(0);
  data_by_MC->GetYaxis()->SetNdivisions(4);



  TLine *l=new TLine(100,1,1200,1);
  l->SetLineColor(kRed);
  l->Draw("same");

  std::cout << "D/MC bins=" << data_by_MC->GetNbinsX() << " width=" << data_by_MC->GetBinWidth(2) << std::endl;
  ratio_c->Write();
  ratio_c->Print("reminiaod_compare_tauMET_ratio.pdf");

 
  return 0;

}
