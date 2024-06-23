using namespace std;

void plot_SumScales()
{
    /*
    Make 2 Canvasses: 1 for summed vars and 1 for scaled-summed vars (S, SS)
    Open 1 files: (S, SS over all masses)
    Loop over vars
        Make 2 hist names: (S, SS)
        Get  2 hists
        Make canvas, draw first hist, repeat for 2nd
        Save canvasses as pdf
    Close file
    */

    string f_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/"; //Working dir
    string in_fileS = f_path + "tests_2024-06-14/test_SumScale_Masses.root"; //In file name
    TFile *in_file = new TFile( (in_fileS).c_str(), "read"); //In TFile

    string variables[] = {"phi", "eta", "pT"};
    
    //___Loop through variables___
    for(int i=0; i<3; i++){
        cout << "_________ Getting variable: " << variables[i] << " _________" << endl;
        //Hist names
        string h_sumS = "h_" + variables[i] + "_S_sum";
        string h_scaleS = "h_" + variables[i] + "_S_sumscale";
        //Get hists
        TH1D *h_sum = (TH1D*)in_file -> Get( (h_sumS).c_str() );
        TH1D *h_scale = (TH1D*)in_file -> Get( (h_scaleS).c_str() );
        //Draw hists
        TCanvas *c_sum = new TCanvas("c_sum", "c_sum");
        h_sum -> Draw("HIST");
        TCanvas *c_scale = new TCanvas("c_scale", "c_scale");
        h_scale -> Draw("HIST");
        //Save canvasses
        cout << "Saving plots" << endl;
        string h_sum_plotS = h_sumS + ".pdf";
        string h_scale_plotS = h_scaleS + ".pdf";
        c_sum -> Print( (h_sum_plotS).c_str() );
        c_scale -> Print( (h_scale_plotS).c_str() );
    }

    //Close file
    cout << "Closing file" << endl;
    in_file -> Close();
}