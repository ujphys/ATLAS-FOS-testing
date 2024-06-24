// !!!! INCOMPLETE !!!!

#include "sumHists.cpp"
#include "getHistParams.cpp"

using namespace std;

int sumParticles()
{
    /*
    INPUT ?
    1. Initialize variables - file and histogram names, TFiles, 
    OUTPUT ?
    */
    string f_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/";
    string outSumS = f_path + "tests_2024-06-14/test_sum.root";
    string outScaleS = f_path + "tests_2024-06-14/test_scale.root";

    TFile *out_sum = new TFile( (outSumS).c_str(), "recreate");
    TFile *out_scale = new TFile( (outScaleS).c_str(), "recreate");

    //___Normalization factors and mH___
    int mH_masses[11] = {300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800};

    //___Loop over mH masses___
    for (int i=0; i<11; i++){
        double normalization_factor = norms[i];
        string mH_GeV = std::to_string(mH_masses[i]);
        cout << "_________ Getting mH: " << mH_GeV << " _________" << endl;
        string inFileS = f_path + "kinematics-2024-05-10_COPY1/hist-reco_mH" + mH_GeV + ".root";
        TFile *in_file = new TFile( (inFileS).c_str(), "read");
        //___Loop through variables___
        string variables[] = {"phi", "eta", "pT"};
        for(int i=0; i<3; i++){
            cout << "----- Getting variable: " << variables[i] << " -----" << endl;
            //___Get hist names___
            string h_in = "h_" + variables[i] + "_S";
            string h_sum = "h_" + variables[i] + "_S_all" + "_mH" + mH_GeV;
            string h_scale = "h_" + variables[i] + "_S_scale" + "_mH" + mH_GeV;
            int n_particles = 2;

            //___Call sum_hists___
            sumHists(in_file, out_sum, h_in, h_sum, n_particles);
        }
        
        in_file -> Close();
    }

    

    out_file -> Close();

    return 0;
}