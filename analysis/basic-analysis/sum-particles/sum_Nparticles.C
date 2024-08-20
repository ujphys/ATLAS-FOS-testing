#include "../../includes/sumHists.cpp"

using namespace std;

vector<string> set_variables(string particle, vector<string>& input_list){
   //Function to set the variable list based on what particle you are given
   std::vector<std::string> v_list = input_list;
   if (particle == "missingET_NonInt" || particle == "missingET"){
      //For MET, no variables (i.e. the list only has one element - an empty string)
      v_list.assign(v_list.begin(), v_list.begin()+1);
      }
   else if (particle == "u" || particle == "e"){
      //For electrons and muons, do not use mass
      v_list.assign(v_list.begin()+1, v_list.end()-1);
   }
   else {
      // For all other particles
      v_list.assign(v_list.begin()+1, v_list.end());
   }

   return v_list;
}

void sum_Nparticles()
{
    /*
    Function to take analysis output files and sum the base variables for each type of particle
    Initialize file paths, lists of particles, variables, masses, etc. to sum over
    Initialize output file
    Loop over different files
        Initialize file string and TFile
        Loop over different particles (MET is defined as its own particle)
            Use set_variables() function to define what variables are relevant to that particle
            Loop over different variables
                Initialize a sum histogram
                Loop over the number of that kind of particle
                    Initialize histogram name (depends on variable, particle, number of that particle)
                    Copy histogram from file
                    Add() copy to sum histogram
                Save sum histogram to output file
        Close file
   Close output file
    */

   //Initialize some variables 
   string mH_masses[11] = {"300", "350", "400", "450", "500", "550", "600", "650", "700", "750", "800"}; //Different H particle masses
   string particles[] = {"H", "S", "Zd", "e", "u", "missingET", "missingET_NonInt"}; //Different kinds of particles
   int num_particles[] = {1,  2,    4,    4,    4,    1,          1}; //Corresponds to the how many of each particle there are
   std::vector<std::string> variables = {"", "phi_", "eta_", "pT_", "m"};
   string hist_data = "_all"; //Extra string in hist name: scaled, unscaled, all, etc.
   string f_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/"; //Working dir
   string inFile_S = f_path + "kinematics-2024-05-10_COPY1/hist-reco_mH"; //In kinematics file
   string outFile_S = f_path + "tests_2024-07-03/summed-Particles_all-mH.root"; //In kinematics file
   //Create output file
   TFile *outFile = new TFile( (outFile_S).c_str(), "recreate" );

   //Loop over different files (defined by different mH)
   for (const auto& m: mH_masses){
      string inFile_mHS = inFile_S + m + ".root";
      cout << "Getting file: " << inFile_mHS << endl;
      TFile *inFile_mH = new TFile( (inFile_mHS).c_str(), "read" );
   
      //Loop over particles
      for (int p = 0; p < sizeof(particles)/sizeof(particles[0]); p++){
         cout << "~~~~~~~~ Getting particle: " << particles[p] << " ~~~~~~~~" << endl;
         //Set variables based on particle
         std::vector<std::string> relevant_variables = set_variables(particles[p], variables);

         //Loop over variables
         for (int v = 0; v < relevant_variables.size(); v++){
            cout << "---- Getting variable: " << relevant_variables[v] << " ----" << endl;
            //Initialize h_sum
            string hist_nameS = "h_" + relevant_variables[v] + particles[p];
            string h_sumS = hist_nameS + hist_data + "_mH" + m;
            cout << "Initializing: " << h_sumS << endl;
            TH1D *h_test = (TH1D*)inFile_mH -> Get( (hist_nameS).c_str() );
            if (num_particles[p] > 1){    h_test = (TH1D*)inFile_mH -> Get( (hist_nameS + "1").c_str() );   }
            TH1D *h_sum = new TH1D( (h_sumS).c_str(), (h_sumS).c_str(), h_test->GetNbinsX(),            //Bins
                                                                        h_test->GetXaxis()->GetXmin(),  //x_min
                                                                        h_test->GetXaxis()->GetXmax()); //x_max

            //Loop over num_particles
            for (int n = 0; n < num_particles[p]; n++){
               //Generate histogram name - if there's more than one particle, what number particle it is is also needed
               string hist_nameS2 = hist_nameS;
               if (num_particles[p] > 1){    hist_nameS2 = hist_nameS + to_string(n+1);   }
               cout << hist_nameS2 << endl;
               //Copy histogram and add to h_sum
               TH1D *h_copy = (TH1D*)inFile_mH -> Get( (hist_nameS2).c_str() );
               h_sum -> Add(h_copy);
            }

            //Save h_sum to outfile
            outFile -> cd();
            h_sum -> Write();
         } //Close loop over variables

      } //Close loop over particles

      cout << "Closing: " << inFile_mHS << endl;
      inFile_mH -> Close();

   } //Close loop over new files

   cout << "Closing output file: " << outFile_S << endl;
   outFile -> Close();
}