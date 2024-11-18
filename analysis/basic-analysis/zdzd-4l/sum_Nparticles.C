#include "../includes/sumHists.cpp"
#include "../includes/setVariables.cpp"

using namespace std;

void sum_Nparticles()
{
   /*
   Function to take event-by-event histograms and sum the base variables for each type of particle, saving the output to a new .root file

   Initialize file paths, lists of particles, variables, masses, etc. to sum over
   Initialize output file
   Loop over different files
      Initialize file string and TFile
      Loop over different particles (MET is defined as its own particle)
         Use setVariables() to define what variables are relevant to that particle
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

   // SET FILE PATHS HERE
   string f_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/code_ZdZd/git_Zd/"; //Working dir
   string inFile_S = f_path + "tests_sep-2024/kinematics-2024-09-04/hist-reco_mH"; //In kinematics file
   string outFile_S = f_path + "tests_sep-2024/summed_2024-09-04.root"; //In kinematics file
   //Create output file
   TFile *outFile = new TFile( (outFile_S).c_str(), "recreate" );
   //Initialize some variables
   string mH_masses[11] = {"300", "350", "400", "450", "500", "550", "600", "650", "700", "750", "800"}; //Different H particle masses
   string particles[] = {"H", "S", "Zd", "e", "u", "2l_leading", "2l_subleading", "4l", "l1l2", "l2l3", "l1l4", "l3l4", "missingET_NonInt", "missingET"}; //Different kinds of particle objects
   int num_particles[] = {1,  2,    4,    4,    4,    1,             1,             1,    1,      1,     1,       1,       1,                   1}; //Corresponds to the how many of each particle there are
   // std::vector<std::string> vars = {"", "phi_", "eta_", "pT_", "m"};
   string hist_data = "_all"; //Extra string in hist name: scaled, unscaled, all, etc.

   //Loop over different files (defined by different mH)
   for (const auto& m: mH_masses){
      string inFile_mH_S = inFile_S + m + ".root";
      cout << "Getting file: " << inFile_mH_S << endl;
      TFile *inFile_mH = new TFile( (inFile_mH_S).c_str(), "read" );
   
      //Loop over particles
      for (int p = 0; p < sizeof(particles)/sizeof(particles[0]); p++){
         cout << "~~~~~~~~ Getting particle: " << particles[p] << " ~~~~~~~~" << endl;
         //Set variables based on particle
         // std::vector<std::string> relevant_variables = setVariables(particles[p], var_list);
         vector<std::string> relevant_variables;
         setVariables(particles[p], relevant_variables);

         //Loop over variables
         for (int v = 0; v < relevant_variables.size(); v++){
            cout << "---- Getting variable: " << relevant_variables[v] << " ----" << endl;
            //Initialize h_sum
            string hist_nameS = "h_" + relevant_variables[v] + particles[p];
            string h_sumS = hist_nameS + "_mH" + m + hist_data;
            cout << "Initializing: " << h_sumS << endl;
            TH1D *h_test = (TH1D*)inFile_mH -> Get( (hist_nameS).c_str() );
            if (num_particles[p] > 1){
               h_test = (TH1D*)inFile_mH -> Get( (hist_nameS + "1").c_str() );
            }
            TH1D *h_sum = new TH1D( (h_sumS).c_str(), (h_sumS).c_str(), h_test->GetNbinsX(),            //Bins
                                                                        h_test->GetXaxis()->GetXmin(),  //x_min
                                                                        h_test->GetXaxis()->GetXmax()); //x_max

            //Loop over num_particles
            for (int n = 0; n < num_particles[p]; n++){
               //Generate histogram name - if there's more than one particle, what number particle it is is also needed
               string hist_nameS2 = hist_nameS;
               if (num_particles[p] > 1){
                  hist_nameS2 = hist_nameS + to_string(n+1);
               }
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

      cout << "Closing: " << inFile_mH_S << endl;
      inFile_mH -> Close();

   } //Close loop over new files

   cout << "Closing output file: " << outFile_S << endl;
   outFile -> Close();
}