using namespace std;

double updateMaxEntries(TH1D* hist, double current_max)
{
    /*Get the maximum entries from a histogram
    Compare to the current max entries and return the larger value*/
    int maxBin = hist->GetMaximumBin();
    double maxEntries = hist->GetBinContent(maxBin);
    if (maxEntries > current_max){ current_max = maxEntries; }
    return current_max;
}

void plot_All()
{
    /*
    Goal: for each particle, for each variable, make 2 plots: distribution for all 11 mH masses overlaid, then the same for the scaled distributions
    Open 2 files: 1 for summed vars and 1 for scaled, summed vars (S, SS)
    Loop over vars
        Make 2 Canvasses: (S, SS)
        Loop over mH
            Make hist names
            Get 2 hists (S, SS)
            cd to the correct canvas and plot

    */
    string f_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/"; //Working dir
    string in_sum_M_S = f_path + "tests_2024-06-14/test_sum.root"; //In file name - summed vars
    string in_scale_M_S = f_path + "tests_2024-06-14/test_scale.root"; //In file name - scaled, summed vars
    TFile *in_sum_M = new TFile( (in_sum_M_S).c_str(), "read"); //In TFile - summed vars
    TFile *in_scale_M = new TFile( (in_scale_M_S).c_str(), "read"); //In TFile - scaled, summed vars

    string variables[] = {"phi", "eta", "pT"};
    int mH_masses[11] = {300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800};

    //___Loop through variables___
    for(int i=0; i<3; i++){
        cout << "_________ Getting variable: " << variables[i] << " _________" << endl;
        //Make canvasses
        string c_sumS = "h_" + variables[i] + "_S_all_mH";
        string c_scaleS = "h_" + variables[i] + "_S_scale_mH";
        TCanvas *c_sum = new TCanvas("c_sum", "c_sum");
        TCanvas *c_scale = new TCanvas("c_scale", "c_scale");

        float maxBinValue_sum = 0;
        float maxBinValue_scale = 0;

        //___Loop over mH masses___
        for (int j=0; j<11; j++){
            string mH_GeV = std::to_string(mH_masses[j]);
            cout << "____ Getting mH: " << mH_GeV << " ____" << endl;
            //Hist names
            string h_sumS = c_sumS + mH_GeV;
            string h_scaleS = c_scaleS + mH_GeV;
            //Get hists
            // cout << h_sumS << endl;
            // cout << h_scaleS << endl;
            TH1D *h_sum = (TH1D*)in_sum_M -> Get( (h_sumS).c_str() );
            TH1D *h_scale = (TH1D*)in_scale_M -> Get( (h_scaleS).c_str() );
            maxBinValue_sum = updateMaxEntries(h_sum, maxBinValue_sum);
            maxBinValue_scale = updateMaxEntries(h_scale, maxBinValue_scale);
            cout << "Max bin values for (sum, scale) are (" << maxBinValue_sum << ", " << maxBinValue_scale << ")" << endl;
            //Draw hists
            c_sum -> cd();
            h_sum -> SetMaximum( maxBinValue_sum );
            h_sum -> Draw("HIST SAME");
            c_scale -> cd();
            h_scale -> SetMaximum( maxBinValue_scale );
            h_scale -> Draw("HIST SAME");
        }
        //Save canvasses
        // cout << "Saving plots" << endl;
        string h_sum_plotS = "plots_all/" + c_sumS + ".pdf";
        string h_scale_plotS = "plots_all/" + c_scaleS + ".pdf";
        c_sum -> Print( (h_sum_plotS).c_str() );
        c_scale -> Print( (h_scale_plotS).c_str() );
    }

    //Close file
    cout << "Closing file" << endl;
    in_sum_M -> Close();
    in_scale_M -> Close();
}