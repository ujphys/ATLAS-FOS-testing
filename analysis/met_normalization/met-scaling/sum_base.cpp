#include <string>

void sum_base()
{
    //Normalization factors
    double norms[11] = {0.068729566, 0.221057757, 0.237594439, 0.169728543, 0.109833669, 0.069514033, 0.04661499, 0.030499267, 0.021510573, 0.014793756, 0.010123407};
    int mH_masses[11] = {300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800};
    //File path strings
    std::string in_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/kinematics-2024-05-10_COPY1/";
    std::string out_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/test_2024-05-24/";

    std::string var_list[] = {"phi", "eta", "pT", "mass"};

    // TH1D *h_sum_MET = new TH1D("h_sum_MET","h_sum_MET",100,0,1000);
    // TH1D *h_sum_MET_scaled = new TH1D("h_sum_MET_scaled","h_sum_MET_scaled",100,0,1000);
    // TH1D *h_sum_MET_NonInt = new TH1D("h_sum_MET_NonInt","h_sum_MET_NonInt",100,0,1000);
    // TH1D *h_sum_MET_NonInt_scaled = new TH1D("h_sum_MET_NonInt_scaled","h_sum_MET_NonInt_scaled",100,0,1000);
    // TH1D *h_sum_S_pT = new TH1D("h_sum_S_pT", "h_sum_S_pT", 100, 0, 500);
    // TH1D *h_sum_S_pT_scaled = new TH1D("h_sum_S_pT_scaled", "h_sum_S_pT_scaled", 100, 0, 500);
    // TH1D *h_sum_S_eta = new TH1D("h_sum_S_eta","h_sum_S_eta", 100, -7, 7);
    // TH1D *h_sum_S_eta_sclaed = new TH1D("h_sum_S_eta_scaled","h_sum_S_eta_scaled", 100, -7, 7);
    // TH1D *h_sum_S_phi = new TH1D("h_sum_S_phi", "h_sum_S_phi", 100, -4, 4);
    // TH1D *h_sum_S_phi_scaled = new TH1D("h_sum_S_phi_scaled", "h_sum_S_phi_scaled", 100, -4, 4);
    // TH1D *h_sum_S_mass = new TH1D("h_sum_S_mass", "h_sum_S_mass", 100, 0, 200);
    // TH1D *h_sum_S_mass_scaled = new TH1D("h_sum_S_mass_scaled", "h_sum_S_mass_scaled", 100, 0, 200);

    //Output file
    std::cout << "Now make output file " << std::endl;
    TFile f_out ((out_path + "allS_test.root").c_str(), "RECREATE");

    //Loop through 11 times (once for each mass point)
    for (int i=0; i<11; i++){
        std::cout << i << std::endl;
        //Get normalization factor
        double normalization_factor = norms[i];
        int mH_GeV = mH_masses[i];
        std::string s = std::to_string(mH_GeV);
        
        //Input file
        std::string in_file = in_path + "hist-reco_mH" + s + ".root";
        TFile *f_in = new TFile((in_file).c_str(), "read");

        /* ___________Sum all vars: phi, eta, pT, mass___________*/
        //Sum phi
        TH1D *h_Phi_S1 = (TH1D*)f_in->Get("h_phi_S1");
        TH1D *h_Phi_S2 = (TH1D*)f_in->Get("h_phi_S2");
        TH1D *h_sum_S_phi = new TH1D("h_sum_S_phi", "h_sum_S_phi", 100, -4, 4);
        h_sum_S_phi -> Add(h_Phi_S1, h_Phi_S2);
        //Sum eta
        TH1D *h_eta_S1 = (TH1D*)f_in->Get("h_eta_S1");
        TH1D *h_eta_S2 = (TH1D*)f_in->Get("h_eta_S2");
        TH1D *h_sum_S_eta = new TH1D("h_sum_S_eta","h_sum_S_eta", 100, -6, 6);
        h_sum_S_eta -> Add(h_eta_S1, h_eta_S2);
        //Sum pT
        TH1D *h_pT_S1 = (TH1D*)f_in->Get("h_pT_S1");
        TH1D *h_pT_S2 = (TH1D*)f_in->Get("h_pT_S2");
        TH1D *h_sum_S_pT = new TH1D("h_sum_S_pT", "h_sum_S_pT", 100, 0, 500);
        h_sum_S_pT -> Add(h_pT_S1, h_pT_S2);
        //Sum mass
        TH1D *h_mS1 = (TH1D*)f_in->Get("h_mS1");
        TH1D *h_mS2 = (TH1D*)f_in->Get("h_mS2");
        TH1D *h_sum_S_mass = new TH1D("h_sum_S_mass", "h_sum_S_mass", 100, 0, 200);
        h_sum_S_mass -> Add(h_mS1, h_mS2);

        //Rename title+name for all summed hists
        std::string h_phi_String = "h_SUM_phi_S_mH" + s;
        h_sum_S_phi -> SetTitle((h_phi_String).c_str()); h_sum_S_phi -> SetName((h_phi_String).c_str());
        std::string h_eta_String = "h_SUM_eta_S_mH" + s;
        h_sum_S_eta -> SetTitle((h_eta_String).c_str()); h_sum_S_eta -> SetName((h_eta_String).c_str());
        std::string h_pT_String = "h_SUM_pT_S_mH" + s;
        h_sum_S_pT -> SetTitle((h_pT_String).c_str()); h_sum_S_pT -> SetName((h_pT_String).c_str());
        std::string h_mass_String = "h_SUM_mass_S_mH" + s;
        h_sum_S_mass -> SetTitle((h_mass_String).c_str()); h_sum_S_mass -> SetName((h_mass_String).c_str());        
        //Write all to output file
        std::cout << "cd to output file " << std::endl;
        f_out.cd();
        std::cout << "Write to output file" << std::endl;
        h_sum_S_phi -> Write();
        h_sum_S_eta -> Write();
        h_sum_S_pT -> Write();
        h_sum_S_mass -> Write();

        //Scale
        // h_sum_S_phi_scaled -> Add(h_sum_S_phi);
        // h_sum_S_phi_scaled -> Scale(normalization_factor);

        std::cout << "Done File: " << f_in << std::endl;
        f_in->Close();
    }

    // Legend, draw options, etc. //
    // h_sum_S_phi -> SetFillColor(kGreen-6);
    // h_sum_S_phi -> SetStats(0);
    // h_sum_S_phi -> GetXaxis() -> SetTitle("S Phi summed");
    // h_sum_S_phi -> GetYaxis() -> SetTitle("Events");
    // h_sum_S_phi -> Draw("HIST");

    // file1 -> Write();
    // file1 -> Close();
}