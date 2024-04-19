#include <string>

void sum_MET()
{
    //Normalization factors
    double norms[11] = {0.068729566, 0.221057757, 0.237594439, 0.169728543, 0.109833669, 0.069514033, 0.04661499, 0.030499267, 0.021510573, 0.014793756, 0.010123407};
    int mH_masses[11] = {300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800};
    int start_mH = 300;

    std::string f_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/diS_code/met-normalization/correct_new-MET-hists1/";

    TH1D *h_sum_NonInt = new TH1D();
    TH1D *h_sum_NonIntScaled = new TH1D();

    //Loop through 11 times
    for (int i=0; i<11; i++){
        std::cout << i << std::endl;
        //Get normalization factor
        double normalization_factor = norms[i];
        int mH_GeV = mH_masses[i];
        int mH_mass = start_mH + i * 50;
        std::string s = std::to_string(mH_GeV);
        std::string file = f_path + "hist-reco-mH" + s + ".root";

        // std::cout << "Normalization factor: " << normalization_factor << std::endl;
        // // std::cout << "mH mass 1: " << mH_GeV << std::endl;
        // // std::cout << "mH mass 2: " << mH_mass << std::endl;
        // std::cout << "File: " << file << std::endl;
        
        //Get histogram from TFile
        TFile *file2 = new TFile((file).c_str(), "read");
        // mH300 has an overscaled plot, so it must be scaled back
        if (mH_mass == start_mH){
            std::cout << "Renormalizing mH300 " << std::endl;
            TH1D *h1 = (TH1D*)file2->Get("h_missingET_NonInt");
            h_sum_NonIntScaled -> Add(h1);
            TH1D *h2 = (TH1D*)file2->Get("h_missingET_Yscaled1");
            h_sum_NonInt -> Add(h2);
        }
        else{
            TH1D *h1 = (TH1D*)file2->Get("h_missingET_NonInt");
            h_sum_NonIntScaled -> Add(h1);
            TH1D *h2 = (TH1D*)file2->Get("h_missingET_Yscaled1");
            h_sum_NonInt -> Add(h2);
        }
        std::cout << "Done File: " << file << std::endl;

        // //Scale histogram
        // test_hist->Scale(normalization_factor);

        // //Save histogram to new file
        // test_hist->Draw();
        // test_hist->Write();
        
        // file1->Write();
        file2->Close();
    }
    
    //New file
    // TFile *file1 = new TFile((f_path + "met-hists.root").c_str(), "update");
    // file1 -> cd();

    // Legend, draw options, etc. //
    // h_sum_NonInt -> SetStats(0);
    // h_sum_NonInt -> SetFillColor(kGreen-6);
    // h_sum_NonInt -> GetXaxis() -> SetTitle("Summed MET distributions");
    // h_sum_NonInt -> GetYaxis() -> SetTitle("Events");
    // h_sum_NonInt -> GetXaxis() -> SetTitleSize(0.05);
    // h_sum_NonInt -> GetXaxis() -> SetLabelSize(0.05);
    // h_sum_NonInt -> GetYaxis() -> SetTitleSize(0.04);
    // h_sum_NonInt -> GetYaxis() -> SetLabelSize(0.04);
    // h_sum_NonInt -> SetLineStyle(1);
    // h_sum_NonInt -> Draw();
    // h_sum_NonInt -> Write();

    h_sum_NonIntScaled -> SetFillColor(kGreen-6);
    h_sum_NonIntScaled -> SetStats(0);
    h_sum_NonIntScaled -> GetXaxis() -> SetTitle("Scaled MET summed");
    h_sum_NonIntScaled -> GetYaxis() -> SetTitle("Events");
    h_sum_NonIntScaled -> Draw("HIST");
    // h_sum_NonIntScaled -> Write();
    // file1 -> Write();
    // file1 -> Close();
}