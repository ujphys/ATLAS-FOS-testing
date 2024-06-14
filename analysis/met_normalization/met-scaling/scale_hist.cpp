void scale_hist(TFile* f_in, TFile* f_out, string hist_in, string hist_out, double norm_factor)
{
    //Initialize h_scaled as imported histogram, then scale it
    TH1D *h_scaled = (TH1D*)f_in -> Get( (hist_in).c_str() );
    h_scaled -> Scale(norm_factor);
    //Rename hist according to variable
    // cout << "Renaming h_scaled" << endl;
    h_scaled->SetTitle( (hist_out).c_str() );
    h_scaled->SetName( (hist_out).c_str() );
    //Save h_scaled
    // cout << "Saving h_scaled" << endl;
    f_out -> cd();
    h_scaled -> Write();
}