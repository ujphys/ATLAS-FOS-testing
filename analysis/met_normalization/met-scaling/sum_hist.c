void sum_hist(TFile* f_in, TFile* f_out, string hist_in, string hist_out, int n)
{
    //Initialize h_summed using dimensions of hist_in
    // cout << "Initializing h_summed" << endl;
    string hist_in1 = hist_in + std::to_string(n);
    TH1D *h1 = (TH1D*)f_in -> Get( (hist_in1).c_str() );
    TH1D *h_summed = new TH1D("h_summed", "h_summed", h1->GetNbinsX(),       //Bins
                                                 h1->GetXaxis()->GetXmin(),  //x_min
                                                 h1->GetXaxis()->GetXmax()); //x_max
    //Get histograms from file - loop through n histograms
    // cout << "Looping through " << n << " histograms" << endl;
    for(int i=1; i<n+1; i++){
        string hist_in2 = hist_in + std::to_string(i);
        cout << "Getting: " << hist_in2 << endl;
        TH1D *h_copy = (TH1D*)f_in -> Get( (hist_in2).c_str() );
        //Add to h_summed
        h_summed -> Add(h_copy);
    }
    //Rename hist according to variable
    // cout << "Renaming h_summed" << endl;
    h_summed->SetTitle( (hist_out).c_str() );
    h_summed->SetName( (hist_out).c_str() );
    //Save h_summed
    // cout << "Saving h_summed" << endl;
    f_out -> cd();
    h_summed -> Write();
}