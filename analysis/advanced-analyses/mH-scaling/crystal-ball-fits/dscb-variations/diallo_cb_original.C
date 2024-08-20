#include <TStyle.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TMath.h>
#include <TROOT.h>
#include <TFile.h>
#include <TNtuple.h>
#include <TSystem.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TFitResult.h>
#include <TObject.h>
#include <TTree.h>
#include <TGraph.h>
#include <TColor.h>
#include <TLegend.h>
#include <TSpectrum.h>
#include <TLatex.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string.h>
#include <cmath>
#include <iomanip>
#include "RooWorkspace.h"
#include <RooRealVar.h>
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooAbsArg.h"
#include "RooMomentMorph.h"
#include "RooFit.h"
#include "TRandom3.h"
#include "TGraphErrors.h"
#include "TGaxis.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TSpline.h"
#include "TPaveStats.h"
#include "TExec.h"

using namespace std;
// #include "TMath.h"
//#include <cmath>
double DoubleSidedCrystalballFunction(double *x, double *par)
 { 
   double alpha_l = par[0]; 
   double alpha_h = par[1]; 
   double n_l     = par[2]; 
   double n_h     = par[3]; 
   double mean	= par[4]; 
   double sigma	= par[5];
   double N	= par[6];
   double t = (x[0]-mean)/sigma;
   double result;
   double fact1TLessMinosAlphaL = alpha_l/n_l;
   double fact2TLessMinosAlphaL = (n_l/alpha_l) - alpha_l -t;
   double fact1THihgerAlphaH = alpha_h/n_h;
   double fact2THigherAlphaH = (n_h/alpha_h) - alpha_h +t;
   
   if (-alpha_l <= t && alpha_h >= t)
     {
       result = exp(-0.5*t*t);
     }
   else if (t < -alpha_l)
     {
       
       result = exp(-0.5*alpha_l*alpha_l)*pow(fact1TLessMinosAlphaL*fact2TLessMinosAlphaL, -n_l);
       
     }
   else if (t > alpha_h)
     {
       result = exp(-0.5*alpha_h*alpha_h)*pow(fact1THihgerAlphaH*fact2THigherAlphaH, -n_h);
       
     }
   return N*result;
 }

double DoubleSidedCrystalballIntegral(double *x, double *par)
 { 
   double alpha_l = par[0]; 
   double alpha_h = par[1]; 
   double n_l     = par[2]; 
   double n_h     = par[3]; 
   double mean	= par[4]; 
   double sigma	= par[5];
   double N	= par[6];
   double t = (x[0]-mean)/sigma;
   double Int;
   double ratio_alphaN_l = n_l/alpha_l;
   double ratio_alphaN_h = n_h/alpha_h;
   
   double firstNum_l = (alpha_l*(ratio_alphaN_l-alpha_l-t))/n_l;
   double secondNum_l = alpha_l*(mean-x[0]) -sigma*alpha_l*alpha_l + n_l*sigma;
   //double secondNum_l = -alpha_l*alpha_l*sigma + alpha_l*(mean-x[0]) + n_h*sigma;
   
   double firstNum_h = (alpha_h*(ratio_alphaN_h-alpha_h+t))/n_h;
   double secondNum_h = alpha_h*(mean-x[0]) +sigma*alpha_h*alpha_h - n_h*sigma;
   //double secondNum_h = -alpha_h*alpha_h*sigma + alpha_h*(x[0]-mean) - n_h*sigma;
   
   double Denom_l=(n_l-1)*alpha_l;
   double Denom_h=(n_h-1)*alpha_h;
   
   if (-alpha_l <= t && alpha_h >= t)
     {
       Int = sqrt(M_PI*2)*sigma;
       //Int = sqrt(M_PI/2)*sigma*erf(-t/sqrt(2));
     }
   else if (t < -alpha_l)
     {
       
       Int = (exp((-alpha_l*alpha_l/2))*pow(firstNum_l, -n_l)*secondNum_l)/Denom_l;

     }
   else if (t > alpha_h)
     {
       Int = (exp((-alpha_h*alpha_h/2))*pow(firstNum_h, -n_h)*secondNum_h)/Denom_h;
       
     }
   return N*Int;
 }
 
void diallo_crystall_ball()
{
  TCanvas *c1 = new TCanvas("c1","c1",700,500);
  TPad* thePad = (TPad*)c1->cd();
  
  // TFile *f = new TFile("../../../Ntuple/signal/combined_output_SR2/signal_reco/signal_reco_Nominal/signal_20_175_Nominal_reco_25GeVSliceNoZvetoCutNoXS_m4l_output_combined.root");
  TFile *f = new TFile("normalized-4b.csv"); //.root file where histogram is stored
  TH1F *hpx = (TH1F*)f->Get("havgM_4e"); //get histogram from it's name
  //hpx->Scale(1/hpx->Integral());
  TF1 *fitDSCB = new TF1("fitDSCB", DoubleSidedCrystalballFunction, 70, 250, 7);
  //hpx->GetYaxis()->SetRangeUser(0, 220);
  gStyle->SetOptFit(1);
  fitDSCB->SetParameters(1, 1, 2, 2, hpx->GetMean(), hpx->GetRMS(),3000);
  //hpx->Integral()
  /*fitDSCB->SetParLimits(0,0,4);
  fitDSCB->SetParLimits(1,0,4);
  fitDSCB->SetParLimits(2,0,3);
  fitDSCB->SetParLimits(3,0,3);*/
  //fitDSCB->SetParLimits(4,0,2);
  //fitDSCB->SetParLimits(4,0,400);
  // fitDSCB->SetParLimits(5,0,1.8);
  //fitDSCB->SetParLimits(6,0,102);
  fitDSCB->SetParLimits(6,0,hpx->GetMaximum());
  //cout <<hpx->GetMaximum()*(1+0.2) << endl;
  fitDSCB->SetParNames("alpha_{low}","alpha_{high}","n_{low}", "n_{high}", "mean", "sigma", "Norm");
  hpx->Fit(fitDSCB, "", "",hpx->GetMean()-6*hpx->GetRMS() , hpx->GetMean()+6*hpx->GetRMS());
  //hpx->Fit(fitDSCB, "", "",500 , 1200);
  //hpx->Fit(fitDSCB, "", "",410 , 800);
  Double_t chi2 = fitDSCB->GetChisquare();
  cout << "chi2 = " << chi2 << endl;
  hpx->GetXaxis()->SetRangeUser(80,300);
  hpx->Draw("func");
  //
  //hpx->GetYaxis()->SetRangeUser(0, 10000);
  thePad->Print("DSCBFit.pdf");
  //cout << "int = " << hpx->GetFunction("fitDSCB")->Integral(hpx->GetMean()-10*hpx->GetRMS() , hpx->GetMean()+10*hpx->GetRMS()) << endl;
  
  /*TF1 *rand_DSCB_mZd = new TF1("rand_DSCB_mZd",DoubleSidedCrystalballIntegral, 0, 100, 7);
  rand_DSCB_mZd->SetParameters(hpx->GetFunction("fitDSCB")->GetParameter(0),hpx->GetFunction("fitDSCB")->GetParameter(1),hpx->GetFunction("fitDSCB")->GetParameter(2),hpx->GetFunction("fitDSCB")->GetParameter(3),hpx->GetFunction("fitDSCB")->GetParameter(4),hpx->GetFunction("fitDSCB")->GetParameter(5), hpx->GetFunction("fitDSCB")->GetParameter(6));

  cout << "int2 = " << rand_DSCB_mZd->Eval(70) << endl;*/
  //rand_DSCB_mZd->Draw();

  //hpx->GetFunction("fitDSCB")->GetParameter(1)
  
  //DoubleSidedCrystalballIntegral(double *x, double *par)

  /*  double M_S_j;
  TF1 *rand_DSCB_mS = new TF1("rand_DSCB_mS",DoubleSidedCrystalballFunction, 120, 1500, 7);
  TH1D* hGen_mS = new TH1D("hGen_mS" ,";m_{S} GeV;events/[2.5 GeV]", 552,120,1500);
  // for (int j = 0; j < 95128; j++)
	  //for (int j = 0; j < 281; j++)
	   
  //	    {
	     
	      rand_DSCB_mS->SetParameters(1.156, 1.448, 7.056, 2.427, 249, 5.27, 51.67);
	      // M_S_j = rand_DSCB_mS->GetRandom();
	      hGen_mS->FillRandom("rand_DSCB_mS", 50000);
	      //	    }
	      //  hGen_mS->GetXaxis()->SetRangeUser(200, 300);
	      //hpx->GetXaxis()->SetRangeUser(200, 300);
    hGen_mS->SetLineColor(kBlue);
    hpx->SetLineColor(kRed);
    double scaleReco = 1/hpx->Integral();
    double scaleGen = 1/hGen_mS->Integral();
    hGen_mS->Scale(scaleGen/scaleReco);
    //hpx->Scale(scaleReco);
    cout <<hGen_mS->Integral() << endl;
    hpx->Draw("hist");
    hGen_mS->Draw("hist same");
   
    thePad->Print("DSCBFit.pdf");*/
	
  
  
}

