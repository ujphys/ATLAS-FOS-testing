using namespace std;

/*
INPUT 2 files (input and output files), 2 strings (input and output hist names) and an integer
    1. Initialize output hist based on input hist dimensions
    2. Loop from 0 to n - copy hists from input file and Add() to output hist
    3. Rename output hist
    4. Save output hist to output file
OUTPUT nothing
*/

void sumHists(TFile* f_in, TFile* f_out, string hist_in, string hist_out, string array1, int array1_size)
{
    // 1. Initialize h_summed using dimensions of hist_in
    // cout << "Initializing h_summed" << endl;
    string hist_in1 = hist_in + to_string(array1_size);
    TH1D *h1 = (TH1D*)f_in -> Get( (hist_in1).c_str() );
    TH1D *h_summed = new TH1D( (hist_out).c_str(), (hist_out).c_str(),  h1->GetNbinsX(),            //Bins
                                                                        h1->GetXaxis()->GetXmin(),  //x_min
                                                                        h1->GetXaxis()->GetXmax()); //x_max
    // 2. Get histograms from file - loop through n histograms
    // cout << "Looping through " << n << " histograms" << endl;
    for(int i = 1; i < array1_size; i++){
        string h_copyS = hist_in + array1[i];
        cout << "Getting: " << h_copyS << endl;
        TH1D *h_copy = (TH1D*)f_in -> Get( (h_copyS).c_str() );
        //Add to h_summed
        h_summed -> Add(h_copy);
    }
    // 3. Save h_summed
    // cout << "Saving h_summed" << endl;
    f_out -> cd();
    h_summed -> Write();
}