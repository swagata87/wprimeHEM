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

int NormalizeDataPUHist() {

  // UP //
  TFile *file_in_up  = new TFile("MyDataPileupHistogram_UP.root");
  TFile* outputFile_up = new TFile("Data_pileup_normalized_UP.root","RECREATE");
  outputFile_up->cd();
  TH1D* pileupData_up = (TH1D*)file_in_up->Get("pileup");
  pileupData_up->Scale( 1.0 / pileupData_up->Integral() );
  pileupData_up->Write();
  outputFile_up->Close();
  delete file_in_up;
  delete outputFile_up;

  // DOWN //
  TFile *file_in_down = new TFile("MyDataPileupHistogram_DOWN.root");
  TFile* outputFile_down = new TFile("Data_pileup_normalized_DOWN.root","RECREATE");
  outputFile_down->cd();
  TH1D* pileupData_down = (TH1D*)file_in_down->Get("pileup");
  pileupData_down->Scale( 1.0 / pileupData_down->Integral() );
  pileupData_down->Write();
  outputFile_down->Close();
  delete file_in_down;
  delete outputFile_down;

  // NOMINAL //
  TFile *file_in = new TFile("MyDataPileupHistogram.root");
  TFile* outputFile = new TFile("Data_pileup_normalized.root","RECREATE");
  outputFile->cd();
  TH1D* pileupData = (TH1D*)file_in->Get("pileup");
  pileupData->Scale( 1.0 / pileupData->Integral() );
  pileupData->Write();
  outputFile->Close();
  delete file_in;
  delete outputFile;

  return 0;

}
