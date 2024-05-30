/*

*/
#include <string>

void sum_base()
{
    //Normalization factors
    double norms[11] = {0.068729566, 0.221057757, 0.237594439, 0.169728543, 0.109833669, 0.069514033, 0.04661499, 0.030499267, 0.021510573, 0.014793756, 0.010123407};
    int mH_masses[11] = {300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800};
    //
    std::string f_path_save = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/test_2024-05-24/";
    std::string f_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/kinematics-2024-05-10_COPY1/";

    TH1D *h_sum_MET1 = new TH1D();
    TH1D *h_sum_MET2 = new TH1D();
    TH1D *h_sum_S_pT = new TH1D();
    TH1D *h_sum_S_eta = new TH1D();
    TH1D *h_sum_S_phi = new TH1D("h_sum_S_phi", "h_sum_S_phi", 100, -4, 4);
    TH1D *h_sum_S_mass = new TH1D();

    //Loop through 11 times (once for each mass point)
    for (int i=0; i<11; i++){
        std::cout << i << std::endl;
        //Get normalization factor
        double normalization_factor = norms[i];
        int mH_GeV = mH_masses[i];
        std::string s = std::to_string(mH_GeV);
        std::string file = f_path + "hist-reco_mH" + s + ".root";

        // std::cout << "Normalization factor: " << normalization_factor << std::endl;
        // // std::cout << "mH mass 1: " << mH_GeV << std::endl;
        // // std::cout << "mH mass 2: " << mH_mass << std::endl;
        // std::cout << "File: " << file << std::endl;
        
        //Get histogram from TFile
        TFile *file2 = new TFile((file).c_str(), "read");

        //S
        TH1D *h_Phi_S1 = (TH1D*)file2->Get("h_phi_S1");
        h_sum_S_phi -> Add(h_Phi_S1);
        TH1D *h_Phi_S2 = (TH1D*)file2->Get("h_phi_S2");
        h_sum_S_phi -> Add(h_Phi_S2);
        //MET
        // TH1D *h_MET1 = (TH1D*)file2->Get("h_missingET");
        // h_sum_MET1 -> Add(h_MET1);
        // TH1D *h_MET2 = (TH1D*)file2->Get("h_missingET_NonInt");
        // h_sum_MET2 -> Add(h_MET2);

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
    std::cout << "Now make new TFile " << std::endl;
    TFile outputFile ((f_path_save + "hists_test.root").c_str(), "RECREATE");
    std::cout << "Now cd new TFile " << std::endl;
    outputFile.cd();
    std::cout << "Now write to new TFile" << std::endl;
    h_sum_S_phi -> Write();

    // Legend, draw options, etc. //
    //Draw S Phi
    h_sum_S_phi -> SetFillColor(kGreen-6);
    // h_sum_S_phi -> SetStats(0);
    h_sum_S_phi -> GetXaxis() -> SetTitle("S Phi summed");
    h_sum_S_phi -> GetYaxis() -> SetTitle("Events");
    h_sum_S_phi -> Draw("HIST");
    //Draw MET
    // h_sum_MET2 -> SetFillColor(kGreen-6);
    // h_sum_MET2 -> SetStats(0);
    // h_sum_MET2 -> GetXaxis() -> SetTitle("Scaled MET summed");
    // h_sum_MET2 -> GetYaxis() -> SetTitle("Events");
    // h_sum_MET2 -> Draw("HIST");

    // file1 -> Write();
    // file1 -> Close();
}