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

// kfactor source : https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

int Plot_compare_M() {

  double lumi=1;

  TFile *file_HEmiss = new TFile("../python/crab_projects_HCALissue_v3/crab_SingleMuonHEmiss/results/hist.root");
  TFile *file_Prompt = new TFile("../python/crab_projects_HCALissue_v3/crab_SingleMuonPrompt/results/hist.root");


  TCanvas* ratio_c = new TCanvas("ratio","ratio_canvas",600,800);
  ratio_c->SetTopMargin(0.); 
  ratio_c->SetBottomMargin(0.); 
  ratio_c->Update();
  ratio_c->Divide(1, 2);
  ratio_c->cd(1);

   std::cout << "will do data" << std::endl;
  
  //--Data--//
   TH1D* hist_HEmiss  = (TH1D*)file_HEmiss->Get("demo/histoDir/m_Stage1");
   TH1D* hist_Prompt  = (TH1D*)file_Prompt->Get("demo/histoDir/m_Stage1");


   hist_HEmiss->SetMarkerStyle(20);
   hist_HEmiss->SetMarkerColor(kBlack);
   hist_HEmiss->SetLineColor(kBlack);
   hist_HEmiss->Rebin(50);

   hist_Prompt->SetMarkerStyle(22);
   hist_Prompt->SetMarkerColor(kRed);
   hist_Prompt->SetLineColor(kRed);
   hist_Prompt->Rebin(50);

  //--Plotting Styles//
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.12);  
  gStyle->SetPadTopMargin(0.05);   
  gStyle->SetTitleXSize(0.05);
  gStyle->SetTitleXOffset(1.05);
  gStyle->SetTitleYSize(0.05);
  gStyle->SetTitleYOffset(1.05);


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
  //  CMS_text_21->Draw("same");

  TLegend *leg_example = new TLegend(0.60,0.70,0.90,0.90);
  leg_example->SetFillColor(0);
  // leg_example->SetNColumns(2);
  leg_example->SetTextFont(42);
  leg_example->SetBorderSize(0);
  leg_example->AddEntry(hist_HEmiss, "HE failure", "pl" );
  leg_example->AddEntry(hist_Prompt, "Regular", "pl" );



  //  TCanvas* my_canvas = new TCanvas("canvas","canvas",800,600);
  //my_canvas->cd();
  //  hs->Draw();
  gPad->SetLogy();
  //  hs->SetMaximum(10000);
  // hs->SetMinimum(0.001);
  // hs->GetXaxis()->SetLimits(0, 4000);
  //  hist_HEmiss->GetXaxis()->SetTitle("M_{T} [GeV]");
  hist_HEmiss->GetYaxis()->SetTitle("Events");
   // totalBkg->Draw("same e2");
  
  hist_HEmiss->GetXaxis()->SetRangeUser(0,1000);
  hist_Prompt->GetXaxis()->SetRangeUser(0,1000);

  hist_HEmiss->Draw("E0");
  hist_Prompt->Draw("SAME E0");
  leg_example->Draw("same");

  TH1F* mydata_fail =  (TH1F*)hist_HEmiss->Clone();
  TH1F* mydata_regular =  (TH1F*)hist_Prompt->Clone();


  gPad->SetPad(.005, .30, .995, .995);
  TPad* pad1 = (TPad*)ratio_c->GetPad(1); 
  pad1->SetTopMargin(0.05);
  pad1->SetBottomMargin(0.05); 
  
  ratio_c->Update();
  gPad->SetLogy();

  hist_HEmiss->GetXaxis()->SetTitle("");
  hist_Prompt->GetXaxis()->SetTitle("");
  hist_HEmiss->SetTitle("");
  hist_Prompt->SetTitle("");
  
  ratio_c->cd(2);

  gPad->SetPad(.005, .12, .995, .29); 
  gStyle->SetOptStat(false);
  ratio_c->Update();
  TPad* pad2 = (TPad*)ratio_c->GetPad(2);
  pad2->SetTopMargin(0.04); 
  pad2->SetBottomMargin(0.45); 
  pad2->SetGridx();
  pad2->SetGridy();

  std::cout << "data fail bins = " << mydata_fail->GetNbinsX() << " width=" << mydata_fail->GetBinWidth(2);
  std::cout << "data regular bins = " << mydata_regular->GetNbinsX() << " width=" << mydata_regular->GetBinWidth(2);
  int nbin5=mydata_fail->GetNbinsX() ;
  float width5=mydata_fail->GetBinWidth(2);
  TH1F *data_by_MC5 = new TH1F("h1", "ratio5", nbin5, 0, 13000);
  //TH1F *data_by_MC_syst = new TH1F("h2", "ratio_syst5", nbin5, 0, 8000);
  // std::cout << "before D/MC bins=" << data_by_MC->GetNbinsX() << " width=" << data_by_MC->GetBinWidth(2) << std::endl;

  for (int i=0; i<nbin5; i++) {
    float data5 = mydata_fail->GetBinContent(i);
    float MC5 = mydata_regular->GetBinContent(i);
    // float syst_err = totalBkg->GetBinError(i);
    float ratio5=999;
    if (MC5>0) ratio5=data5/MC5 ;
    data_by_MC5->SetBinContent(i,ratio5);
    if (data5>0) {
      float stat_err5 = sqrt(data5)/data5 ;  
      data_by_MC5->SetBinError(i,stat_err5);
    }
  }

  data_by_MC5->SetMarkerStyle(20);
  data_by_MC5->SetFillColor(kGray);
  data_by_MC5->SetFillStyle(3001);
  /// data_by_MC5->Draw("e2");
  data_by_MC5->Draw("same E");
  data_by_MC5->GetXaxis()->SetTitle("M_{#mu#tau}^{vis} [GeV]");
  data_by_MC5->GetYaxis()->SetTitle("#frac{HE fail}{regular}");
  data_by_MC5->GetYaxis()->SetLabelSize(0.12);
  data_by_MC5->GetXaxis()->SetLabelSize(0.12);
  data_by_MC5->GetYaxis()->SetTitleSize(0.18);
  data_by_MC5->GetXaxis()->SetTitleSize(0.23);
  data_by_MC5->GetYaxis()->SetTitleOffset(0.20);
  data_by_MC5->GetXaxis()->SetTitleOffset(0.75);
  data_by_MC5->SetTitle("");
  data_by_MC5->GetXaxis()->SetRangeUser(0,1000);
  data_by_MC5->SetMaximum(1.2);
  data_by_MC5->SetMinimum(0.8);
  data_by_MC5->GetYaxis()->SetNdivisions(4);

  TLine *l5=new TLine(0,1,1000,1);
  l5->SetLineColor(kRed);
  l5->Draw("same");
 
  //  std::cout << "D/MC bins=" << data_by_MC->GetNbinsX() << " width=" << data_by_MC->GetBinWidth(2) << std::endl;
  // ratio_noband->Write();
  // ratio_noband->Print("mT_Stage1_ratio_noBAND_F.pdf");
  ratio_c->Print("M_plot.png");

 
  return 0;

}

