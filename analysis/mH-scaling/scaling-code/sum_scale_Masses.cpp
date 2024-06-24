#include "sumHists.cpp"
#include "scaleHists.cpp"
#include "getHistParams.cpp"

using namespace std;

int sum_scale_Masses()
{
    /*
    2 in files - summed particle variables and scaled, summed particle variables
    1 out file - sum of all masses for each variable and scaled, sum of all masses for each variable
    3 arrays initialized - normalization factors, mH masses, variables
    Loop over particles
        Loop over variables
            Initialize two histograms (sum over masses and scaled-sum over masses)
            Loop over mH: , summed+scaled var file
                Get hist from summed var file > Add() to sum over masses hist
                Get hist from scaled, summed var file > Add() to scaled-sum over masses hist
            Save both histograms
    */

    string f_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/"; //Working dir
    string in_sum_M_S = f_path + "tests_2024-06-14/test_sum.root"; //In file name - summed vars
    string in_scale_M_S = f_path + "tests_2024-06-14/test_scale.root"; //In file name - scaled, summed vars
    TFile *in_sum_M = new TFile( (in_sum_M_S).c_str(), "read"); //In TFile - summed vars
    TFile *in_scale_M = new TFile( (in_scale_M_S).c_str(), "read"); //In TFile - scaled, summed vars

    string out_M_S = f_path + "tests_2024-06-14/test_SumScale_Masses.root"; //Out file name
    TFile *out_sum_M = new TFile( (out_M_S).c_str(), "recreate"); //Out TFile

    //___Normalization factors, mH values and particle variables___
    double norms[11] = {0.068729566, 0.221057757, 0.237594439, 0.169728543, 0.109833669, 0.069514033, 0.04661499, 0.030499267, 0.021510573, 0.014793756, 0.010123407};
    int mH_masses[11] = {300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800};
    string variables[] = {"phi", "eta", "pT"};
    
    //___Loop through variables___
    for(int i=0; i<3; i++){
        //___Initialize sum histograms___
        cout << "_________ Getting variable: " << variables[i] << " _________" << endl;
        string h_exampleS = "h_" + variables[i] + "_S_all_mH300";
        // cout << "Example hist: " << h_exampleS << endl;
        string h_sumS = "h_" + variables[i] + "_S_sum";
        string h_sumscaleS = "h_" + variables[i] + "_S_sumscale";

        TH1D *h_example = (TH1D*)in_sum_M -> Get( (h_exampleS).c_str() );
        TH1D *h_sum = new TH1D( (h_sumS).c_str(), (h_sumS).c_str(), h_example->GetNbinsX(),            //Bins
                                                                    h_example->GetXaxis()->GetXmin(),  //x_min
                                                                    h_example->GetXaxis()->GetXmax()); //x_max
        TH1D *h_sum_scaled = new TH1D( (h_sumscaleS).c_str(), (h_sumscaleS).c_str(), h_example->GetNbinsX(),            //Bins
                                                                                    h_example->GetXaxis()->GetXmin(),  //x_min
                                                                                    h_example->GetXaxis()->GetXmax()); //x_max

        //___Loop over mH masses___
        for (int j=0; j<11; j++){
            string mH_GeV = std::to_string(mH_masses[j]);
            cout << "____ Getting mH: " << mH_GeV << " ____" << endl;
            //Make histogram names
            string h_allS = "h_" + variables[i] + "_S_all_mH" + mH_GeV;
            string h_scaleS = "h_" + variables[i] + "_S_scale_mH" + mH_GeV;
            //Get histograms
            TH1D *h_all = (TH1D*)in_sum_M -> Get( (h_allS).c_str() );
            TH1D *h_scale = (TH1D*)in_scale_M -> Get( (h_scaleS).c_str() );
            //Add to sum hists
            h_sum -> Add(h_all);
            h_sum_scaled -> Add(h_scale);
        }
        //Save sum hists to out file
        cout << "Saving hists" << endl;
        out_sum_M -> cd();
        h_sum -> Write();
        h_sum_scaled -> Write();

    }
    //Close files
    cout << "Closing files" << endl;
    in_sum_M -> Close();
    in_scale_M -> Close();
    out_sum_M -> Close();

    return 0;
}