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
#include "TH1D.h"
#include "TH2F.h"
#include "TPostScript.h"
#include <TPaveStats.h>
#include "TLegend.h"
#include <TProfile.h>
#include "TGraph.h"
#include "TGraphAsymmErrors.h"

int MakePileUpHistMC() {

  //////// Output File /////////
  TFile* outputFile = new TFile("MC_pileup.root","RECREATE");
  outputFile->cd();

  //--//
  TH1D* pileup = new TH1D("pileup","pileup",100,0,100); 
  double probValue[100]={0.000829312873542,
			0.00124276120498,
			0.00339329181587,
			0.00408224735376,
			0.00383036590008,
			0.00659159288946,
			0.00816022734493,
			0.00943640833116,
			0.0137777376066,
			0.017059392038,
			0.0213193035468,
			0.0247343174676,
			0.0280848773878,
			0.0323308476564,
			0.0370394341409,
			0.0456917721191,
			0.0558762890594,
			0.0576956187107,
			0.0625325287017,
			0.0591603758776,
			0.0656650815128,
			0.0678329011676,
			0.0625142146389,
			0.0548068448797,
			0.0503893295063,
			0.040209818868,
			0.0374446988111,
			0.0299661572042,
			0.0272024759921,
			0.0219328403791,
			0.0179586571619,
			0.0142926728247,
			0.00839941654725,
			0.00522366397213,
			0.00224457976761,
			0.000779274977993,
			0.000197066585944,
			7.16031761328e-05,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0};

  for (int i=1; i<51; i++) {
    pileup->SetBinContent(i,probValue[i-1]);
  }
  pileup->Write();
  return 0;

}
