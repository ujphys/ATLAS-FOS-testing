/*
This file will...
*/
#include <string>

void scale_base()
{
    //Normalization factors
    double norms[11] = {0.068729566, 0.221057757, 0.237594439, 0.169728543, 0.109833669, 0.069514033, 0.04661499, 0.030499267, 0.021510573, 0.014793756, 0.010123407};
    int mH_masses[11] = {300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800};
    //File path strings
    std::string in_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/kinematics-2024-05-10_COPY1/";
    std::string out_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/test_2024-05-24/";
    //List of variables
    std::string var_list[] = {"phi", "eta", "pT", "mass"};

    //Input file
    // std::string in_file = in_path + "hist-reco_mH" + s + ".root";
    TFile *f_in = new TFile((out_path + "allS_test.root").c_str(), "read");
    //Output file
    std::cout << "Now make output file " << std::endl;
    TFile f_out ((out_path + "allS_scaled_test.root").c_str(), "RECREATE");

    //Loop through 11 times (once for each mass point)
    for (int i=0; i<11; i++){
        std::cout << mH_masses[i] << std::endl;
        //Get normalization factor
        double normalization_factor = norms[i];
        int mH_GeV = mH_masses[i];
        std::string s = std::to_string(mH_GeV);

        //Scale all hists
        //Loop through variables
        for (int j=0; j < 4/*var_list.size()*/; ++j){
            
            //Get histogram from input file
            std::cout << var_list[j] << std::endl;
            std::string hist_string = "h_SUM_" + var_list[j] + "_S_mH" + s;
            TH1D *h_scaled = (TH1D*)f_in -> Get( (hist_string).c_str() );

            //Scale by normalization factor
            h_scaled -> Scale(normalization_factor);
            
            //Rename title+name for scaled hist
            std::string hist_scaled_string = "h_SCALED_" + var_list[j] + "_S_mH" + s;
            h_scaled -> SetTitle((hist_scaled_string).c_str()); h_scaled -> SetName((hist_scaled_string).c_str());
            
            //Save to file
            f_out.cd();
            std::cout << "Write to output file" << std::endl;
            h_scaled -> Write();

        }

    }

    std::cout << "Done File: " << f_in << std::endl;
    f_in->Close();

    // Legend, draw options, etc. //
    //Draw S Phi
    // h_sum_S_phi -> SetFillColor(kGreen-6);
    // // h_sum_S_phi -> SetStats(0);
    // h_sum_S_phi -> GetXaxis() -> SetTitle("S Phi summed");
    // h_sum_S_phi -> GetYaxis() -> SetTitle("Events");
    // h_sum_S_phi -> Draw("HIST");
    //Draw MET
    // h_sum_MET2 -> SetFillColor(kGreen-6);
    // h_sum_MET2 -> SetStats(0);
    // h_sum_MET2 -> GetXaxis() -> SetTitle("Scaled MET summed");
    // h_sum_MET2 -> GetYaxis() -> SetTitle("Events");
    // h_sum_MET2 -> Draw("HIST");

    // file1 -> Write();
    // file1 -> Close();
}