#include <string>

void scale_test()
{
    //Normalization factors
    double norms[11] = {0.068729566, 0.221057757, 0.237594439, 0.169728543, 0.109833669, 0.069514033, 0.04661499, 0.030499267, 0.021510573, 0.014793756, 0.010123407};
    int mH_masses[11] = {300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800};
    //Folders
    std::string f_path_save = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/test_2024-05-24/";
    std::string f_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/kinematics-2024-05-10_COPY1/";

    //Initialize hists
    // TH1D *h_existing = new TH1D();
    // TH1D *h_imported = new TH1D();
    TH1D *h_scaled = new TH1D("h_scaled", "h_scaled", 100, -4, 4);

    //Get histogram from TFile
    std::string in_fileS = f_path_save + "hists_test.root";
    std::cout << "Reading file " << in_fileS << std::endl;
    TFile *in_file = new TFile((in_fileS).c_str(), "update");
    // TFile * in_file = TFile::Open((in_fileS).c_str(), "READ"); //Open .root file

    std::cout << "Extracting histogram " << std::endl;
    TH1D *h1 = (TH1D*)in_file -> Get("h_sum_S_phi");
    TH1D *h2 = (TH1D*)h1 -> Clone();
    TH1D *h3 = new TH1D(*h1);
    h_scaled -> Add(h1);

    //Scale new hist
    // double normalization_factor = norms[0];
    // std::cout << "Calculated norm factor as " << normalization_factor << std::endl;

    // std::cout << "Scale " << std::endl;
    // h_scaled -> Scale(normalization_factor);

    // std::cout << "Done File: " << in_fileS << std::endl;
    // in_file->Close();
    
    //New file
    std::cout << "Now make new TFile " << std::endl;
    std::string out_fileS = f_path_save + "scale_test2.root";
    TFile outputFile ((out_fileS).c_str(), "RECREATE");

    std::cout << "Now cd new TFile " << std::endl;
    out_file.cd();

    std::cout << "Now write new histo" << std::endl;
    h_scaled -> Write();
    // out_file.Write();

    // Legend, draw options, etc. //
    std::cout << "Now draw" << std::endl;
    // h1 -> SetFillColor(kGreen-6);
    // h1 -> GetXaxis() -> SetTitle("MET Non-Int Scaled and Summed");
    // h1 -> GetYaxis() -> SetTitle("Events");
    // h_scaled -> Draw("HIST");
    h1 -> Draw();
    // h2 -> Draw();
    // h3 -> Draw();

    std::cout << "Done File: " << in_fileS << std::endl;
    in_file->Close();

    std::cout << "Done File: " << out_fileS << std::endl;
    out_file->Close();

}