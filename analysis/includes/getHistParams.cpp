// !!!!! INCOMPLETE !!!!!

/*
Input 2 files (input and output files), 2 strings (input and output hist names) and an integer
    1. Copy input hist from input file
    2. Get parameters from input hist
Output array of parameters?
*/

void getHistParams(TFile* f_in, string hist_in)
{
    // 1. Copy input histogram
    // cout << "Getting input hist" << endl;
    TH1D *h_in = (TH1D*)f_in -> Get( (hist_in).c_str() );
    // 2. Get histogram dimensions
    int nBins = h_in->GetNbinsX();
    float xMin = h_in->GetXaxis()->GetXmin();
    float xMax = h_in->GetXaxis()->GetXmax();
}