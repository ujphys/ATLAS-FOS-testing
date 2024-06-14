// #include "test_func.h"  // Include the header file
using namespace std;

void sum_hists(TFile* f_in, TFile* f_out, string hist_in, string hist_out, int n)
{
    //Initialize h_summed using dimensions of hist_in
    // cout << "Initializing h_summed" << endl;
    string hist_in1 = hist_in + std::to_string(n);
    TH1D *h1 = (TH1D*)f_in -> Get( (hist_in1).c_str() );
    TH1D *h_summed = new TH1D("h_summed", "h_summed",   h1->GetNbinsX(),            //Bins
                                                        h1->GetXaxis()->GetXmin(),  //x_min
                                                        h1->GetXaxis()->GetXmax()); //x_max
    //Get histograms from file - loop through n histograms
    // cout << "Looping through " << n << " histograms" << endl;
    for(int i=1; i<n+1; i++){
        string hist_in2 = hist_in + std::to_string(i);
        cout << "Getting: " << hist_in2 << endl;
        TH1D *h_copy = (TH1D*)f_in -> Get( (hist_in2).c_str() );
        //Add to h_summed
        h_summed -> Add(h_copy);
    }
    //Rename hist according to variable
    // cout << "Renaming h_summed" << endl;
    h_summed->SetTitle( (hist_out).c_str() );
    h_summed->SetName( (hist_out).c_str() );
    //Save h_summed
    // cout << "Saving h_summed" << endl;
    f_out -> cd();
    h_summed -> Write();
}

void scale_hist(TFile* f_in, TFile* f_out, string hist_in, string hist_out, double norm_factor)
{
    //Initialize h_scaled as imported histogram, then scale it
    TH1D *h_scaled = (TH1D*)f_in -> Get( (hist_in).c_str() );
    h_scaled -> Scale(norm_factor);
    //Rename hist according to variable
    // cout << "Renaming h_scaled" << endl;
    h_scaled->SetTitle( (hist_out).c_str() );
    h_scaled->SetName( (hist_out).c_str() );
    //Save h_scaled
    // cout << "Saving h_scaled" << endl;
    f_out -> cd();
    h_scaled -> Write();
}

int sum_scale_All()
{
    string f_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/";
    string outSumS = f_path + "tests_2024-06-14/test_sum.root";
    string outScaleS = f_path + "tests_2024-06-14/test_scale.root";

    TFile *out_sum = new TFile( (outSumS).c_str(), "recreate");
    TFile *out_scale = new TFile( (outScaleS).c_str(), "recreate");

    //Normalization factors and mH
    double norms[11] = {0.068729566, 0.221057757, 0.237594439, 0.169728543, 0.109833669, 0.069514033, 0.04661499, 0.030499267, 0.021510573, 0.014793756, 0.010123407};
    int mH_masses[11] = {300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800};

    //Loop over mH masses
    for (int i=0; i<11; i++){
        double normalization_factor = norms[i];
        string mH_GeV = std::to_string(mH_masses[i]);
        cout << "_________ Getting mH: " << mH_GeV << " _________" << endl;
        string inFileS = f_path + "kinematics-2024-05-10_COPY1/hist-reco_mH" + mH_GeV + ".root";
        TFile *in_file = new TFile( (inFileS).c_str(), "read");
        //Loop through variables
        string variables[] = {"phi", "eta", "pT"};
        for(int i=0; i<3; i++){
            cout << "----- Getting variable: " << variables[i] << " -----" << endl;
            //Get hist names
            string h_in = "h_" + variables[i] + "_S";
            string h_sum = "h_" + variables[i] + "_S_all" + "_mH" + mH_GeV;
            string h_scale = "h_" + variables[i] + "_S_scale" + "_mH" + mH_GeV;
            int n_particles = 2;
            // double normalization_factor = 0.1;// 0.068729566;

            //Call sum_hists
            sum_hist(in_file, out_sum, h_in, h_sum, n_particles);
            //Call scale_hists
            scale_hist(out_sum, out_scale, h_sum, h_scale, normalization_factor);
        }
        
        in_file -> Close();
    }

    

    out_sum -> Close();
    out_scale -> Close();

    return 0;
}