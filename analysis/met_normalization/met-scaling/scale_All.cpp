#include <string>

void scale_MET()
{
    //Normalization factors
    double norms1[11] = {0.068729566, 0.221057757, 0.237594439, 0.169728543, 0.109833669, 0.069514033, 0.04661499, 0.030499267, 0.021510573, 0.014793756, 0.010123407}; //original fit
    double norms2[11] = {0.066050607, 0.217609643, 0.252699304, 0.163169155, 0.106328223, 0.070064774, 0.046660255, 0.031388042, 0.021317631, 0.0146108, 0.010101565}; //latest fit
    double norms_fig8[11] ={0.08010287524866395, 0.26822783132571654, 0.23308569912109822, 0.14819630770210918, 0.09576668210842124, 0.06282846595993904, 0.0418047070705195, 0.02818541669827609, 0.019239540513570564, 0.013286400665396957, 0.00927607358628875};
    int mH_masses[11] = {300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800};
    int start_mH = 300;

    // std::string f_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/diS_code/met-normalization/new-MET-hists1/";
    std::string f_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/kinematics-2024-05-10/";

    TH1D *h_sum_NonInt = new TH1D();
    TH1D *h_sum_NonIntScaled = new TH1D();

    //Loop through 11 times
    for (int i=0; i<11; i++){
        std::cout << i << std::endl;
        //Get normalization factor
        double norm_factor1 = norms1[i];
        double norm_factor2 = norms_fig8[i];
        int mH_GeV = mH_masses[i];
        // int mH_mass = start_mH + i * 50;
        std::string s = std::to_string(mH_GeV);
        std::string file = f_path + "hist-reco-mH" + s + ".root";

        // std::cout << "Normalization factor: " << normalization_factor << std::endl;
        std::cout << "mH mass 1: " << mH_GeV << std::endl;
        // std::cout << "mH mass 2: " << mH_mass << std::endl;
        std::cout << "Norm Factor 1: " << norm_factor1 << std::endl;
        std::cout << "Norm Factor 2: " << norm_factor2 << std::endl;
        
        //Get histogram from TFile
        TFile *file2 = new TFile((file).c_str(), "update");
        // mH300 has an overscaled plot, so it must be scaled back
        if (mH_GeV == start_mH){
            std::cout << "Doing mH300 " << std::endl;
            //Scale histogram
            TH1D *h1 = (TH1D*)file2 -> Get("h_missingET_NonInt");
            TH1D *h2 = (TH1D*)file2->Get("h_missingET_Yscaled1");
            // h1 -> Scale(norm_factor2/(norm_factor1 * norm_factor1)); //Divide by the old normalization factor and multiply by the new
            // Save histogram to new file
            // test_hist->Draw();
            h_sum_NonIntScaled -> Add(h1);
            h_sum_NonInt -> Add(h2);
            // h1->Write();
            // file2 -> Write();
            file2->Close();
        }
        else{
            //Scale histogram
            TH1D *h1 = (TH1D*)file2 -> Get("h_missingET_NonInt");
            TH1D *h2 = (TH1D*)file2->Get("h_missingET_Yscaled1");
            // h1 -> Scale(norm_factor2/norm_factor1); //Divide by the old normalization factor and multiply by the new
            // Save histogram to new file
            // test_hist->Draw();
            h_sum_NonIntScaled -> Add(h1);
            h_sum_NonInt -> Add(h2);
            // h1->Write();
            // file2 -> Write();
            file2->Close();
        }
        std::cout << "Done File: " << file << std::endl;
        // file2->Close();
    }
    
    //New file
    // TFile *file1 = new TFile((f_path + "met-hists.root").c_str(), "write");
    // file1 -> cd();

    // Legend, draw options, etc. //
    // h_sum_NonInt -> GetXaxis() -> SetTitleSize(0.05);
    // h_sum_NonInt -> GetXaxis() -> SetLabelSize(0.05);
    // h_sum_NonInt -> GetYaxis() -> SetTitleSize(0.04);
    // h_sum_NonInt -> GetYaxis() -> SetLabelSize(0.04);
    h_sum_NonInt -> SetStats(0);
    h_sum_NonInt -> SetFillColor(kGreen-6);
    h_sum_NonInt -> GetXaxis() -> SetTitle("Summed MET distributions [GeV]");
    h_sum_NonInt -> GetYaxis() -> SetTitle("Entries");
    h_sum_NonInt -> SetLineStyle(1);
    h_sum_NonInt -> Draw();
    // h_sum_NonInt -> Write();

    // h_sum_NonIntScaled -> SetFillColor(kGreen-6);
    // h_sum_NonIntScaled -> SetStats(0);
    // h_sum_NonIntScaled -> GetXaxis() -> SetTitle("Scaled MET summed [GeV]");
    // h_sum_NonIntScaled -> GetYaxis() -> SetTitle("Entries");
    // h_sum_NonIntScaled -> Draw("HIST");
    // h_sum_NonIntScaled -> Write();
    // file1 -> Write();
    // file1 -> Close();
}