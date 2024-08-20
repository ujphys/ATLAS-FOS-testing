using namespace std;

void plot_test()
{
    string f_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/"; //Working dir
    string in_sum_M_S = f_path + "tests_2024-06-14/test_SumScale_Masses.root"; //In file name - summed vars
    TFile *in_sum_M = new TFile( (in_sum_M_S).c_str(), "read");

    TH1D *h_copy = (TH1D*)in_sum_M -> Get( "h_pT_S_sum" );

    TCanvas *c1 = new TCanvas("c_sum", "c_sum");
    TText T;
    T.SetTextFont(42); T.SetTextAlign(21);
    c1 -> Divide(2,1);

    c1 -> cd(1);
    h_copy -> Draw();
    T.DrawTextNDC(.5,.95,"Default drawing option");
    c1 -> cd(2);
    h_copy -> Draw("nostack");
    T.DrawTextNDC(.5,.95,"No Stack option");

}