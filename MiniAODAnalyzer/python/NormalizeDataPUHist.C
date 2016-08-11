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

  //  gROOT->SetBatch(kTRUE);
  TFile *file_in  = new TFile("MyDataPileupHistogram_66016_DOWN.root");
  //////// Output File /////////
  TFile* outputFile = new TFile("Data_pileup_normalized_DOWN.root","RECREATE");
  outputFile->cd();

  //--//
  TH1D* pileupData = (TH1D*)file_in->Get("pileup");
  pileupData->Scale( 1.0 / pileupData->Integral() );
  pileupData->Write();
  return 0;

}
