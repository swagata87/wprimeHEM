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

int EfficiencyPlotter() {

  //  gROOT->SetBatch(kTRUE);
  TFile *file_in  = new TFile("../hist_analysis.root");
  //////// Output File /////////
  TFile* outputFile = new TFile("MyEff.root","RECREATE");
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
  TH1F* den1 = (TH1F*)file_in->Get("demo/tauPt_reco");
  TH1F* num1 = (TH1F*)file_in->Get("demo/tauPt_goodreco");
  TGraphAsymmErrors* eff1 = new TGraphAsymmErrors(num1,den1,"cp");
  eff1->SetTitle("");
  eff1->GetXaxis()->SetTitle("p_{T}(#tau)");
  eff1->GetYaxis()->SetTitle("ID efficiency");
  eff1->SetMarkerStyle(0);
  eff1->SetMarkerColor(kBlack);
  eff1->SetLineColor(kBlack);
  eff1->SetLineWidth(2);
 
  TCanvas* canvas_eff1 = new TCanvas("eff1","eff1",800,600);
  canvas_eff1->cd();
  eff1->Draw("Ap");
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
  canvas_eff1->Print("Tau_ID_eff.pdf");
  return 0;

}
