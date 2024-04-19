#include <TStyle.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TMath.h>
#include <TROOT.h>
#include <TFile.h>
#include <TNtuple.h>
#include <TSystem.h>
#include <TH1.h>
#include <TTree.h>
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


// ROOT Globals
TObject  *MyObj = 0;
TCanvas  *c= NULL;       // create a canvass


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



int main(int argc, char *argv[])
{

    if (argc < 3) {
        std::cout << "Usage: diallo_crystall_ball datafile_txt root_file" << std::endl;
        exit(-1);
    }

// Extract info from commabine arguments
    //std::string filename = argv[1];
    char filename[64];   // root file
    strcpy(filename,argv[1]);

// Extract ROOT output file name from the argument list
    char root_file[64];   // root file
    strcpy(root_file,argv[2]);


// Initiate ROOT Graphics session
    TApplication theApp("hello", &argc, argv);
    c = new TCanvas("canv", "Yankee-doodle",1000, 500);
    TString filename_ROOT = root_file;
    TFile *f = new TFile(filename_ROOT,"RECREATE");

    TTree *t_diHiggs = new TTree("t_diHiggs", filename);
    t_diHiggs->ReadFile(filename, "x/F:y/F:err/F");
    t_diHiggs->Draw("y : x : err","","goff");
    TGraphErrors *gr1 = new TGraphErrors(t_diHiggs->GetSelectedRows(),t_diHiggs->GetV2(), t_diHiggs->GetV1(),0,t_diHiggs->GetV3());
    int N =  t_diHiggs->GetEntries();
    Double_t *xx = t_diHiggs->GetV1();
    for (int i = 0; i < N; i++)
    {
        //cout<<xx[i]<<"\n";
    }

    gr1->Draw();
    c->Update();
    gPad->Modified();		// make sure
    gPad->Update();		  // hist is drawn
    gSystem->ProcessEvents();




  TF1 *fitDSCB = new TF1("fitDSCB", DoubleSidedCrystalballFunction, 200, 1100, 7);
  //hpx->GetYaxis()->SetRangeUser(0, 220);
  gStyle->SetOptFit(1);
  // fitDSCB->SetParameters(1,1,2,2,400,10,3000); //Default Params
  fitDSCB->SetParameters(1,1,2,2,400,10,3000);
  //hpx->Integral()


  /*fitDSCB->SetParLimits(0,0,4);
  fitDSCB->SetParLimits(1,0,4);
  fitDSCB->SetParLimits(2,0,3);
  fitDSCB->SetParLimits(3,0,3);*/
  //fitDSCB->SetParLimits(4,0,2);
  //fitDSCB->SetParLimits(4,0,400);
  // fitDSCB->SetParLimits(5,0,1.8);
  //fitDSCB->SetParLimits(6,0,102);



  //fitDSCB->SetParLimits(6,0,hpx->GetMaximum());
  //cout <<hpx->GetMaximum()*(1+0.2) << endl;
  fitDSCB->SetParNames("alpha_{low}", "alpha_{high}","n_{low}", "n_{high}", "mean", "sigma", "Norm");
  gr1->Fit(fitDSCB);
  //hpx->Fit(fitDSCB, "", "",500 , 1200);
  //hpx->Fit(fitDSCB, "", "",410 , 800);
  Double_t chi2 = fitDSCB->GetChisquare();
  cout << "chi2 = " << chi2 << endl;
  // cout << "Eval point 500: " << gr1 -> Eval(500);

  int mass_points[11] = {300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800};

  cout << "gr1: "  << endl;
  for (int i=0; i<11; i++){
      // cout << "Eval point 500: " << gr->Eval(500);
      // cout << "Eval point " << mass_points[i] << ": " << gr1->Eval(mass_points[i]) << endl;
      cout << gr1->Eval(mass_points[i]) << ", ";
      // cout << gr->Eval(plot_points[i]) << ", ";
      };

  cout << ""  << endl;
  cout << "fitDSCB: "  << endl;
  for (int i=0; i<11; i++){
      cout << fitDSCB -> Eval(mass_points[i]) << ", ";
      };

  //hpx->GetXaxis()->SetRangeUser(80,300);
    // fitDSCB->Draw("same");

    gr1->Draw();
    c->Update();
    gPad->Modified();		// make sure
    gPad->Update();		  // hist is drawn
    gSystem->ProcessEvents();



  //
  //hpx->GetYaxis()->SetRangeUser(0, 10000);


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





    // Can use this instead of TheApp->Run();
    std::cout << "\n Done  ...  Now waiting...";
    std::cout << "\n ==> Double click mouse button in graphics window to end program.\n\n\n";
    int n=1;
    while (n>0) {
        MyObj = gPad->WaitPrimitive();
        if (!MyObj) break;
        printf("Loop i=%d, found objIsA=%s, name=%s\n",n,MyObj->ClassName(),MyObj->GetName());
    }



}

