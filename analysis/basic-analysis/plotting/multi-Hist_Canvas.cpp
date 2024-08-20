// !!!!! INCOMPLETE !!!!!

#include "../../includes/updateMaxEntries.cpp"

using namespace std;

void plot_All()
{
    /*
    INPUT ?
    Goal: for each particle, for each variable, overlay distributions for each mH on the same canvas
    1. Initialize variables - file names, TFiles, mH list, variable list
    Loop over vars
        Make 2 Canvasses: (S, SS)
        Loop over mH
            Make hist names
            Get 2 hists (S, SS)
            cd to the correct canvas and plot
    OUTPUT ?
    */
    string f_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/"; //Working dir
    string inFile_S = f_path + "tests_2024-06-14/test_sum.root"; //In file name
    TFile *inFile = new TFile( (inFile_S).c_str(), "read"); //In TFile

    string variables[] = {"phi", "eta", "pT"};
    int mH_masses[11] = {300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800};
    float maxBinVal = 0;

    //___Loop through variables___
    for(int i=0; i<3; i++){
        cout << "_________ Getting variable: " << variables[i] << " _________" << endl;
        //Make canvass
        string c1_S = "h_" + variables[i] + "_S_all_mH";
        TCanvas *c1 = new TCanvas( (c1_S).c_str(), (c1_S).c_str());
        //Initialize legends
        TLegend *leg_c1 = new TLegend(.82, .3, .897, .77);
        leg_c1 -> SetBorderSize(0);
        leg_c1 -> SetFillColor(0);
        leg_c1 -> SetFillStyle(9);
        leg_c1 -> SetTextFont(42);
        leg_c1 -> SetTextSize(0.02);

        //Find maximum bin value
        for (int j=0; j<11; j++){
            string mH_GeV = std::to_string(mH_masses[j]);
            string h_sum_S = c1_S + mH_GeV;
            TH1D *h_copy = (TH1D*)inFile -> Get( (h_sum_S).c_str() );
            maxBinVal = updateMaxEntries(h_copy, maxBinVal);
        }

        //___Loop over mH masses___
        for (int j=0; j<11; j++){
            string mH_GeV = std::to_string(mH_masses[j]);
            cout << "____ Getting mH: " << mH_GeV << " ____" << endl;
            //Hist names
            string h_sum_S = c1_S + mH_GeV;
            //Get hists
            // cout << h_sum_S << endl;
            TH1D *h_sum = (TH1D*)inFile -> Get( (h_sum_S).c_str() );
            //Draw hist
            string leg_string = "mH=" + mH_GeV;
            leg_c1 -> AddEntry(h_sum, (leg_string).c_str(), "f");
            h_sum -> SetFillColor(j+1);
            //For the first histogram, set the Y-axis range and plot name
            if (j == 0){
                h_sum -> GetYaxis() -> SetRangeUser(0, maxBinVal * 1.5);
                string h_sum_name_S = variables[i] + ": distributions per mH [GeV]";
                h_sum -> SetTitle( (h_sum_name_S).c_str() );
                h_sum -> SetName( (h_sum_name_S).c_str() );
            }
            h_sum -> Draw("HIST SAME");
        }
        //Draw legends
        leg_c1 -> Draw();
        //Save canvasses
        // cout << "Saving plots" << endl;
        string h_sum_S = "plots/" + c1_S + ".pdf";
        c1 -> Print( (h_sum_S).c_str() );
    }

    //Close file
    cout << "Closing file" << endl;
    inFile -> Close();
}