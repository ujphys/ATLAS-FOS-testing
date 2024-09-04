using namespace std;

/*
    Summary: function to add n histograms to a THStack
    INPUT a TFile pointer, file path string, draw option string,
          a variable, a particle and 'other' string for extra info,
          array of strings, array size (n), very short array descriptor string
    Initialize stack histogram, canvas and legend
    Loop over n
        Copy histogram from file
        Add() copy to stack histogram
    Save stack histogram as PDF
    OUTPUT nothing

    Example call:
    stackHists(inFile, "myPathTo/NewPlots/", "pfc hist nostack",
                "pT", "Zd", "scale",
                mH_masses, sizeof(mH_masses) / sizeof(mH_masses[0]), "mH");
*/

void stackHists(TFile* f_in, string outpath, string draw_option,
                string variable, string particle, string other,
                string array[], int array_size, string array_descriptor)
{ 
  // Initialize THStack
   string hist_name_S = "h_" + variable + particle + "_" + array_descriptor;
   string h_stack_S = hist_name_S + "_Stacked";
   auto h_stack = new THStack("h_stack", (h_stack_S).c_str() );
   
   // Initialize canvas, legend
   gStyle->SetPalette(104);
   TCanvas *c1 = new TCanvas("c1", "c1");
   // TLegend *leg_c1 = new TLegend(.82, .3, .897, .77); // put legend far right, underneath stats box
   TLegend *leg_c1 = new TLegend(.82, .43, .9, .9); //put legend top right
   leg_c1 -> SetBorderSize(0);
   leg_c1 -> SetFillColor(0);
   leg_c1 -> SetFillStyle(9);
   leg_c1 -> SetTextFont(42);
   leg_c1 -> SetTextSize(0.02);

    // Loop over array of strings
    for (int i = 0; i < array_size; i++){
        // cout << "__ Array element " << i << ": " << array[i] << " __" << endl;
        // Get histogram from TFile, add to h_stack
        string h_copyS = hist_name_S + array[i] + "_" + other;
        cout << "Getting hist: " << h_copyS << endl;
        TH1D *h_copy = (TH1D*)f_in -> Get( (h_copyS).c_str() );
        // cout << "Largest bin: " << h_copy -> GetMaximumBin() << endl;
        h_stack -> Add(h_copy);
        // Add legend entry
        string leg_c1_S = array_descriptor+ "=" + array[i];
        leg_c1 -> AddEntry(h_copy, (leg_c1_S).c_str(), "f");
    }

   //Draw plot
   h_stack -> Draw( (draw_option).c_str() );
   leg_c1 -> Draw();
   //Save plot
   string canvas_S = "plots/" + h_stack_S + ".pdf";
//    string canvas_S = "plots/kTempMap_pngs/" + h_stack_S + ".png";
   cout << "Saving plot: " << outpath + canvas_S << endl;
   c1 -> Print( (outpath + canvas_S).c_str() );
   //Clear canvas
   c1 -> Clear();
}