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

int TauIDEfficiency() {

  //  gROOT->SetBatch(kTRUE);
  //  TFile *file_in_2015  = new TFile("../python/crab_projects_2015_SameCode_Feb9/Sig2015.root");
  // TFile *file_in_2017  = new TFile("../python/crab_projects_Feb8_TauIDEff_SigOnly/Sig2016.root");
   TFile *file_in_2017  = new TFile("../python/hist_analysis.root");
  //////// Output File /////////
  TFile* outputFile = new TFile("TauIDEff.root","RECREATE");
  outputFile->cd();

  //--//
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);  
  gStyle->SetPadTopMargin(0.05);   
  gStyle->SetTitleXSize(0.05);
  gStyle->SetTitleXOffset(1.05);
  gStyle->SetTitleYSize(0.05);
  gStyle->SetTitleYOffset(1.05);

  //--//
  /*
  TH1F* den1_2015 = (TH1F*)file_in_2015->Get("demo/histoDir/tauPt_Gen_den");
  TH1F* num1_2015 = (TH1F*)file_in_2015->Get("demo/histoDir/tauPt_Gen_num");

  den1_2015->Rebin(10);
  num1_2015->Rebin(10);

  TGraphAsymmErrors* eff1_2015 = new TGraphAsymmErrors(num1_2015,den1_2015,"cp");
  eff1_2015->SetTitle("");
  eff1_2015->GetXaxis()->SetTitle("p_{T}(Gen #tau)");
  eff1_2015->GetYaxis()->SetTitle("Tau ID efficiency");
  eff1_2015->SetMarkerStyle(20);
  eff1_2015->SetMarkerColor(kRed);
  eff1_2015->SetLineColor(kRed);
  eff1_2015->SetLineWidth(2);
  eff1_2015->GetXaxis()->SetLimits(0,3000);
  */
  TH1F* den0_2017 = (TH1F*)file_in_2017->Get("demo/histoDir/tauPt_Gen_den_reco");
  TH1F* den1_2017 = (TH1F*)file_in_2017->Get("demo/histoDir/tauPt_Gen_den");
  TH1F* den2_2017 = (TH1F*)file_in_2017->Get("demo/histoDir/tauPt_Gen_den_decay");
  TH1F* den3_2017 = (TH1F*)file_in_2017->Get("demo/histoDir/tauPt_Gen_den_decay_iso");
  TH1F* den4_2017 = (TH1F*)file_in_2017->Get("demo/histoDir/tauPt_Gen_den_decay_iso_muon");

  TH1F* num0_2017 = (TH1F*)file_in_2017->Get("demo/histoDir/tauPt_Gen_num_reco");
  TH1F* num1_2017 = (TH1F*)file_in_2017->Get("demo/histoDir/tauPt_Gen_num_tot");
  TH1F* num2_2017 = (TH1F*)file_in_2017->Get("demo/histoDir/tauPt_Gen_num_decay");
  TH1F* num3_2017 = (TH1F*)file_in_2017->Get("demo/histoDir/tauPt_Gen_num_decay_iso");
  TH1F* num4_2017 = (TH1F*)file_in_2017->Get("demo/histoDir/tauPt_Gen_num_decay_iso_muon");
  TH1F* num5_2017 = (TH1F*)file_in_2017->Get("demo/histoDir/tauPt_Gen_num_decay_iso_muon_ele");

  den0_2017->Rebin(10);
  den1_2017->Rebin(10);
  den2_2017->Rebin(10);
  den3_2017->Rebin(10);
  den4_2017->Rebin(10);

  num0_2017->Rebin(10);
  num1_2017->Rebin(10);
  num2_2017->Rebin(10);
  num3_2017->Rebin(10);
  num4_2017->Rebin(10);
  num5_2017->Rebin(10);

  TGraphAsymmErrors* eff0_2017 = new TGraphAsymmErrors(num0_2017,den0_2017,"cp");
  eff0_2017->SetTitle("");
  eff0_2017->GetXaxis()->SetTitle("p_{T}(Gen #tau)");
  eff0_2017->GetYaxis()->SetTitle("Tau efficiency");
  eff0_2017->SetMarkerStyle(20);
  eff0_2017->SetMarkerColor(kCyan);
  eff0_2017->SetLineColor(kCyan);
  eff0_2017->SetLineWidth(2);
  eff0_2017->GetXaxis()->SetLimits(0,3000);
  eff0_2017->SetMaximum(1.5);

  TGraphAsymmErrors* eff1_2017 = new TGraphAsymmErrors(num1_2017,den1_2017,"cp");
  eff1_2017->SetTitle("");
  eff1_2017->GetXaxis()->SetTitle("p_{T}(Gen #tau)");
  eff1_2017->GetYaxis()->SetTitle("Tau efficiency");
  eff1_2017->SetMarkerStyle(20);
  eff1_2017->SetMarkerColor(kBlue);
  eff1_2017->SetLineColor(kBlue);
  eff1_2017->SetLineWidth(2);
  eff1_2017->GetXaxis()->SetLimits(0,3000);
  eff1_2017->SetMaximum(1.5);

  TGraphAsymmErrors* eff2_2017 = new TGraphAsymmErrors(num2_2017,den1_2017,"cp");
  eff2_2017->SetTitle("");
  eff2_2017->GetXaxis()->SetTitle("p_{T}(Gen #tau)");
  eff2_2017->GetYaxis()->SetTitle("Tau efficiency");
  eff2_2017->SetMarkerStyle(20);
  eff2_2017->SetMarkerColor(kGreen);
  eff2_2017->SetLineColor(kGreen);
  eff2_2017->SetLineWidth(2);
  eff2_2017->SetMaximum(1.5);

  TGraphAsymmErrors* eff3_2017 = new TGraphAsymmErrors(num3_2017,den2_2017,"cp");
  eff3_2017->SetTitle("");
  eff3_2017->GetXaxis()->SetTitle("p_{T}(Gen #tau)");
  //  eff3_2017->GetYaxis()->SetTitle("Tau ID (decay+iso) efficiency");
  eff3_2017->SetMarkerStyle(20);
  eff3_2017->SetMarkerColor(kRed+2);
  eff3_2017->SetLineColor(kRed+2);
  eff3_2017->SetLineWidth(2);
  eff3_2017->SetMaximum(1.5);

  TGraphAsymmErrors* eff4_2017 = new TGraphAsymmErrors(num4_2017,den3_2017,"cp");
  eff4_2017->SetTitle("");
  eff4_2017->GetXaxis()->SetTitle("p_{T}(Gen #tau)");
  // eff4_2017->GetYaxis()->SetTitle("Tau ID (decay+iso) efficiency");
  eff4_2017->SetMarkerStyle(20);
  eff4_2017->SetMarkerColor(kCyan+2);
  eff4_2017->SetLineColor(kCyan+2);
  eff4_2017->SetLineWidth(2);
  eff4_2017->SetMaximum(1.5);

  TGraphAsymmErrors* eff5_2017 = new TGraphAsymmErrors(num5_2017,den4_2017,"cp");
  eff5_2017->SetTitle("");
  eff5_2017->GetXaxis()->SetTitle("p_{T}(Gen #tau)");
  //  eff5_2017->GetYaxis()->SetTitle("Tau ID (decay+iso) efficiency");
  eff5_2017->SetMarkerStyle(20);
  eff5_2017->SetMarkerColor(kMagenta);
  eff5_2017->SetLineColor(kMagenta);
  eff5_2017->SetLineWidth(2);
  eff5_2017->SetMaximum(1.5);

  TCanvas* canvas_eff1 = new TCanvas("eff1","eff1",800,600);
  canvas_eff1->cd();
  //  eff1_2015->Draw("Ap");
  eff1_2017->Draw("Ap");
  canvas_eff1->SetGrid();

  //
  TLegend *leg_example = new TLegend(0.75,0.80,0.94,0.94);
  leg_example->SetFillColor(0);
  leg_example->SetTextFont(42);
  //  leg_example->SetHeader("SSM W'");
  leg_example->SetBorderSize(0);
  //  leg_example->AddEntry(eff1_2015, "Fall15","PL");
  leg_example->AddEntry(eff1_2017, "Summer16","PL");
  leg_example->Draw("same");
  //

  TLatex* CMS_text = new TLatex(0.24,0.88,"CMS");
  CMS_text->SetNDC();
  CMS_text->SetTextSize(0.05);
  CMS_text->SetTextAngle(0);
  CMS_text->Draw("same");
  TLatex* CMS_text_2 = new TLatex(0.20,0.83,"Preliminary");
  CMS_text_2->SetNDC();
  CMS_text_2->SetTextFont(42);
  CMS_text_2->SetTextSize(0.05);
  CMS_text_2->SetTextAngle(0);
  CMS_text_2->Draw("same");    
  canvas_eff1->Write();
  canvas_eff1->Print("TauIDeffcompare.pdf");

  //////
 
  TCanvas* canvas_eff2 = new TCanvas("eff2","eff2",800,600);
  canvas_eff2->cd();
  // eff1_2015->Draw("Ap");
  eff0_2017->Draw("Ap");
  eff1_2017->Draw("p : same");
  eff2_2017->Draw("p : same");
  eff3_2017->Draw("p : same");
  eff4_2017->Draw("p : same");
  eff5_2017->Draw("p : same");
  canvas_eff2->SetGrid();

  //
  TLegend *leg_example1 = new TLegend(0.75,0.70,0.94,0.94);
  leg_example1->SetFillColor(0);
  leg_example1->SetTextFont(42);
  //  leg_example->SetHeader("SSM W'");
  leg_example1->SetBorderSize(0);
  leg_example1->AddEntry(eff0_2017, "Reconstruction","PL");
  leg_example1->AddEntry(eff2_2017, "TauID (Only DecayMode)","PL");
  leg_example1->AddEntry(eff3_2017, "TauID (Only Isolation)","PL");
  leg_example1->AddEntry(eff4_2017, "TauID (Only #mu rej)","PL");
  leg_example1->AddEntry(eff5_2017, "TauID (Only e rej)","PL");
  leg_example1->AddEntry(eff1_2017, "TauID (Full)","PL");
  leg_example1->Draw("same");
  //

  CMS_text->Draw("same");
  CMS_text_2->Draw("same");    
  canvas_eff2->Write();
  canvas_eff2->Print("TauIDeffcompare_2.pdf");


 

  return 0;

}
