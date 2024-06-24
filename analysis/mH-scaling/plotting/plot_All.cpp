#include "updateMaxEntries.cpp"

using namespace std;

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
        //Initialize legends
        TLegend *leg_c_sum = new TLegend(.60, .25, .8, .75);
        leg_c_sum -> SetBorderSize(0);
        leg_c_sum -> SetFillColor(0);
        leg_c_sum -> SetFillStyle(9);
        leg_c_sum -> SetTextFont(42);
        leg_c_sum -> SetTextSize(0.04);
        c_scale -> cd();
        TLegend *leg_c_scale = new TLegend(.60, .25, .8, .75);
        leg_c_scale -> SetBorderSize(0);
        leg_c_scale -> SetFillColor(0);
        leg_c_scale -> SetFillStyle(9);
        leg_c_scale -> SetTextFont(42);
        leg_c_scale -> SetTextSize(0.04);

        //Track maximum bin values
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
            double mBV_sum = h_sum ->GetBinContent( h_sum->GetMaximumBin() );
            double mBV_scale = h_scale ->GetBinContent( h_scale->GetMaximumBin() );
            cout << "Max bin values for (sum, scale) are (" << maxBinValue_sum << ", " << maxBinValue_scale << ")" << endl;
            // cout << "Sum: " << mBV_sum << endl << "Scale: " << mBV_scale << endl;

            //Draw hists
            string leg_string = "mH" + mH_GeV;
            c_sum -> cd();
            leg_c_sum -> AddEntry(h_sum, (leg_string).c_str(), "f");
            h_sum -> SetFillColor(j+1);
            // h_sum -> SetMaximum( maxBinValue_sum );
            h_sum -> GetYaxis()->SetRangeUser(20, maxBinValue_sum * 10);
            // h_sum -> Draw("HIST SAME");
            c_scale -> cd();
            leg_c_scale -> AddEntry(h_sum, (leg_string).c_str(), "f");
            // h_scale -> SetMaximum( maxBinValue_scale );
            h_scale -> GetYaxis()->SetRangeUser(20, maxBinValue_scale * 10);
            h_scale -> SetFillColor(j+1);
            // h_scale -> Draw("HIST SAME");
            if (j == 0){
                c_sum -> cd();
                h_sum -> Draw("HIST");
                c_scale -> cd();
                h_scale -> Draw("HIST");
            }
            else{
                c_sum -> cd();
                h_sum -> Draw("HIST SAME");
                c_scale -> cd();
                h_scale -> Draw("HIST SAME");
            }
        }
        //Draw legends
        c_sum -> cd();
        leg_c_sum -> Draw();
        c_scale -> cd();
        leg_c_scale -> Draw();
        //Save canvasses
        // cout << "Saving plots" << endl;
        string h_sum_plotS = "plots_all/" + c_sumS + ".pdf";
        string h_scale_plotS = "plots_all/" + c_scaleS + ".pdf";
        c_sum -> Print( (h_sum_plotS).c_str() );
        c_scale -> Print( (h_scale_plotS).c_str() );
    }

    //Close file
    cout << "Closing files" << endl;
    in_sum_M -> Close();
    in_scale_M -> Close();
}