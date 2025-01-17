#include "../../includes/scaleHist.cpp"
#include "../../includes/setVariables.cpp"

using namespace std;

void scale_All()
{
   /*
   Function to loop through event histograms by particle, scale histograms acc. to a varying normalization factor, and save the resulting histograms

   Initialize file paths, lists of particles, variables, masses, etc. to sum over
   Initialize input and output file
   Loop over mH masses
      Use setVariables() to define what variables are relevant to that particle
      Loop over different particles
         Initialize a sum histogram
         Loop over different variables
               Initialize histogram name (depends on variable, particle, number of that particle)
               Apply scaleHist.cpp function (saves the scaled hist to the output file)
   Close files
   */

   // SET FILE PATHS HERE
   string f_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/code_ZdZd/git_Zd/"; //Working dir
   string inFile_S = f_path + "tests_sep-2024/summed_2024-09-04.root"; //In kinematics file
   string outFile_S = f_path + "tests_sep-2024/scaled_2024-09-04.root"; //Out scaled kinematics file
   //Create input and output files
   TFile *inFile = new TFile( (inFile_S).c_str(), "read" );
   TFile *outFile = new TFile( (outFile_S).c_str(), "recreate" );
   //Initialize some variables
   string particles[] = {"H", "S", "Zd", "e", "u", "2l_leading", "2l_subleading", "4l", "l1l2", "l2l3", "l1l4", "l3l4", "missingET_NonInt", "missingET"}; //Different kinds of particle objects
   float norm_factors[11] = {0.068729566, 0.221057757, 0.237594439, 0.169728543, 0.109833669, 0.069514033, 0.04661499, 0.030499267, 0.021510573, 0.014793756, 0.010123407};
   // std::vector<std::string> variables = {"", "phi_", "eta_", "pT_", "m"};
   string hist_data = "_all"; //Other string in hist name: scaled, unscaled, all, etc.
   string mH_masses[11] = {"300", "350", "400", "450", "500", "550", "600", "650", "700", "750", "800"}; //Different masses of H particle
   int n_masses = sizeof(mH_masses) / sizeof(mH_masses[0]);

   //Loop over different files (defined by different mH)
   for (int m = 0; m < n_masses; m++){
      cout << "____________ Getting mH: " << mH_masses[m] << " _____________" << endl;
   
      //Loop over particles
      for (int p = 0; p < sizeof(particles)/sizeof(particles[0]); p++){
         cout << "~~~~~~~ Getting particle: " << particles[p] << " ~~~~~~~" << endl;
         //Set variables based on particle
         // std::vector<std::string> relevant_variables = setVariables(particles[p], variables);
         std::vector<std::string> relevant_variables;
         setVariables(particles[p], relevant_variables);

         //Loop over variables
         for (int v = 0; v < relevant_variables.size(); v++){
            // cout << "-- Getting variable: " << relevant_variables[v] << " --" << endl;
            //Initialize h_sum
            //Example: h_eta_H_all_mH300
            string h_sumS = "h_" + relevant_variables[v] + particles[p] + "_mH" + mH_masses[m] + hist_data;
            string h_scaleS = "h_" + relevant_variables[v] + particles[p] + "_mH" + mH_masses[m] + "_scale";
            cout << h_sumS << endl;
            // Apply scaleHist()
            scaleHist(inFile, outFile, h_sumS, h_scaleS, norm_factors[m]);
         }
      }
   }
    cout << "Closing output file: " << outFile_S << endl;
    outFile -> Close();
    cout << "Closing: " << inFile_S << endl;
    inFile -> Close();
}