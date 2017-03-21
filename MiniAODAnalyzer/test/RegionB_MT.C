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

int RegionB_MT() {

  TFile *file_DD_RegB = new TFile("/net/scratch_cms3a/materok/wprime/qcd/dataDrivenTree15_pt_base_Mar7_fromData.root");
  TFile *file_contamination_RegB = new TFile("bg.root");

  TH1D* mT_DD_RegB             =  (TH1D*)file_DD_RegB->Get("demo/histoDir/mT_Stage1");
  mT_DD_RegB->SetMarkerStyle(20);
  mT_DD_RegB->SetMarkerColor(kBlack);
  mT_DD_RegB->SetLineColor(kBlack);
  mT_DD_RegB->Rebin(100);
  mT_DD_RegB->SetStats(kFALSE);

  TH1D* mT_contamination_RegB  =  (TH1D*)file_contamination_RegB->Get("demo/histoDir/mT_Stage1");
  mT_contamination_RegB->SetMarkerStyle(23);
  mT_contamination_RegB->SetMarkerColor(kRed);
  mT_contamination_RegB->SetLineColor(kRed);

  mT_contamination_RegB->Rebin(100);
  mT_contamination_RegB->SetStats(kFALSE);

 
  //--Plotting Styles//
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.12);  
  gStyle->SetPadTopMargin(0.05);   
  gStyle->SetTitleXSize(0.05);
  gStyle->SetTitleXOffset(1.05);
  gStyle->SetTitleYSize(0.05);
  gStyle->SetTitleYOffset(1.05);
  //  gStyle->SetOptStat("e");

  //////// Output File /////////
  TFile* outputFile = new TFile("contamination_regB.root","RECREATE");
  outputFile->cd();

  //--//
 
  TCanvas* my_canvas = new TCanvas("canvas","canvas",800,600);
  my_canvas->cd();
  gPad->SetLogy();
  mT_DD_RegB->SetTitle(" ");

  mT_DD_RegB->Draw("E1");
  mT_contamination_RegB->Draw("SAME E1");

  mT_DD_RegB->SetMaximum(10000);
  mT_DD_RegB->SetMinimum(0.1);
  mT_DD_RegB->GetXaxis()->SetRangeUser(100, 2200);
  mT_DD_RegB->GetXaxis()->SetTitle("MT [GeV]"); 
  mT_DD_RegB->GetYaxis()->SetTitle("Events");

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


  TLatex* lumiText = new TLatex(0.92,0.975,"Region B");
  lumiText->SetNDC();
  lumiText->SetTextFont(42);
  lumiText->SetTextSize(0.04);
  lumiText->SetTextAlign(32);
  lumiText->Draw("same");     

  TLegend *leg_example = new TLegend(0.55,0.75,0.94,0.94);
  leg_example->SetFillColor(0);
  leg_example->SetTextFont(42);
  leg_example->SetBorderSize(0);
  leg_example->AddEntry(mT_DD_RegB, "After subtracting contamination", "pl" );
  leg_example->AddEntry(mT_contamination_RegB, "Contamination", "pl" );
  leg_example->Draw("same");
  
  my_canvas->Write();
  my_canvas->Print("regB_contamination.pdf");

 
  return 0;

}
