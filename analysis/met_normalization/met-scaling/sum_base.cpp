    #include <string>

    void sum_base()
    {
        //Normalization factors
        double norms[11] = {0.068729566, 0.221057757, 0.237594439, 0.169728543, 0.109833669, 0.069514033, 0.04661499, 0.030499267, 0.021510573, 0.014793756, 0.010123407};
        int mH_masses[11] = {300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800};
        //
        std::string out_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/test_2024-05-24/";
        std::string in_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/kinematics-2024-05-10_COPY1/";

        TH1D *h_sum_MET = new TH1D("h_sum_MET","h_sum_MET",100,0,1000);
        TH1D *h_sum_MET_scaled = new TH1D("h_sum_MET_scaled","h_sum_MET_scaled",100,0,1000);
        TH1D *h_sum_MET_NonInt = new TH1D("h_sum_MET_NonInt","h_sum_MET_NonInt",100,0,1000);
        TH1D *h_sum_MET_NonInt_scaled = new TH1D("h_sum_MET_NonInt_scaled","h_sum_MET_NonInt_scaled",100,0,1000);
        TH1D *h_sum_S_pT = new TH1D("h_sum_S_pT", "h_sum_S_pT", 100, 0, 500);
        TH1D *h_sum_S_pT_scaled = new TH1D("h_sum_S_pT_scaled", "h_sum_S_pT_scaled", 100, 0, 500);
        TH1D *h_sum_S_eta = new TH1D("h_sum_S_eta","h_sum_S_eta", 100, -7, 7);
        TH1D *h_sum_S_eta_sclaed = new TH1D("h_sum_S_eta_scaled","h_sum_S_eta_scaled", 100, -7, 7);
        TH1D *h_sum_S_phi = new TH1D("h_sum_S_phi", "h_sum_S_phi", 100, -4, 4);
        TH1D *h_sum_S_phi_scaled = new TH1D("h_sum_S_phi_scaled", "h_sum_S_phi_scaled", 100, -4, 4);
        TH1D *h_sum_S_mass = new TH1D("h_sum_S_mass", "h_sum_S_mass", 100, 0, 200);
        TH1D *h_sum_S_mass_scaled = new TH1D("h_sum_S_mass_scaled", "h_sum_S_mass_scaled", 100, 0, 200);

        //Loop through 11 times (once for each mass point)
        for (int i=0; i<11; i++){
            std::cout << i << std::endl;
            //Get normalization factor
            double normalization_factor = norms[i];
            int mH_GeV = mH_masses[i];
            std::string s = std::to_string(mH_GeV);
            
            //Get histogram from TFile
            std::string in_file = in_path + "hist-reco_mH" + s + ".root";
            TFile *file2 = new TFile((file).c_str(), "read");

            //Sum
            TH1D *h_Phi_S1 = (TH1D*)file2->Get("h_phi_S1");
            h_sum_S_phi -> Add(h_Phi_S1);
            TH1D *h_Phi_S2 = (TH1D*)file2->Get("h_phi_S2");
            h_sum_S_phi -> Add(h_Phi_S2);
            //Scale
            h_sum_S_phi_scaled -> Add(h_sum_S_phi);
            h_sum_S_phi_scaled -> Scale(normalization_factor);

            std::cout << "Done File: " << file << std::endl;
            in_file->Close();
        }
        
        //New file
        std::cout << "Now make new TFile " << std::endl;
        TFile out_File ((f_path_save + "hists_test.root").c_str(), "RECREATE");
        std::cout << "Now cd new TFile " << std::endl;
        out_File.cd();
        std::cout << "Now write to new TFile" << std::endl;
        h_sum_S_phi -> Write();

        // Legend, draw options, etc. //
        h_sum_S_phi -> SetFillColor(kGreen-6);
        // h_sum_S_phi -> SetStats(0);
        h_sum_S_phi -> GetXaxis() -> SetTitle("S Phi summed");
        h_sum_S_phi -> GetYaxis() -> SetTitle("Events");
        h_sum_S_phi -> Draw("HIST");

        // file1 -> Write();
        // file1 -> Close();
    }