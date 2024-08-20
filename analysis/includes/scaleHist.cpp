/*
Input 2 files (input and output files), 2 strings (input and output hist names) and a float
    1. Copy input hist to output hist
    2. Scale output hist by float value
    3. Rename output hist
    4. Save output hist to output file
Output nothing
*/

void scaleHist(TFile* f_in, TFile* f_out, string hist_in, string hist_out, float norm_factor)
{
    // 1. Initialize h_scaled as imported histogram, then scale it___
    TH1D *h_scaled = (TH1D*)f_in -> Get( (hist_in).c_str() );
    h_scaled -> Scale(norm_factor);
    // 3. Rename hist according to variable
    // cout << "Renaming h_scaled" << endl;
    h_scaled->SetTitle( (hist_out).c_str() );
    h_scaled->SetName( (hist_out).c_str() );
    // 4. Save h_scaled
    // cout << "Saving h_scaled" << endl;
    f_out -> cd();
    h_scaled -> Write();
}