#include "../../includes/scaleHist.cpp"

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

void scale_All()
{
    /*
    Function to take files with variables for each particle type and scale these histograms according to a varying normalization factor
    Initialize file paths, lists of particles, variables, masses, etc. to sum over
    Initialize input and output file
    Loop over mH masses
        Use set_variables() function to define what variables are relevant to that particle
        Loop over different particles
            Initialize a sum histogram
            Loop over different variables
                Initialize histogram name (depends on variable, particle, number of that particle)
                Apply scaleHist.cpp function
    Close files
    */

   //Initialize some variables
   string f_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/"; //Working dir
   string inFile_S = f_path + "tests_2024-07-03/summed-Particles_all-mH.root"; //In kinematics file
   string outFile_S = f_path + "tests_2024-07-03/scaled-Particles_all-mH.root"; //Out scaled kinematics file
   string particles[] = {"H", "S", "Zd", "e", "u", "missingET", "missingET_NonInt"}; //Different kinds of particles included in the input file
   float norm_factors[11] = {0.068729566, 0.221057757, 0.237594439, 0.169728543, 0.109833669, 0.069514033, 0.04661499, 0.030499267, 0.021510573, 0.014793756, 0.010123407};
   std::vector<std::string> variables = {"", "phi_", "eta_", "pT_", "m"};
   string hist_data = "_all"; //Other string in hist name: scaled, unscaled, all, etc.
   string mH_masses[11] = {"300", "350", "400", "450", "500", "550", "600", "650", "700", "750", "800"}; //Different masses of H particle
   int n_masses = sizeof(mH_masses) / sizeof(mH_masses[0]);

   //Create input and output files
   TFile *inFile = new TFile( (inFile_S).c_str(), "read" );
   TFile *outFile = new TFile( (outFile_S).c_str(), "recreate" );

   //Loop over different files (defined by different mH)
   for (int m = 0; m < n_masses; m++){
      cout << "____________ Getting mH: " << mH_masses[m] << " _____________" << endl;
   
      //Loop over particles
      for (int p = 0; p < sizeof(particles)/sizeof(particles[0]); p++){
         cout << "~~~~~~~ Getting particle: " << particles[p] << " ~~~~~~~" << endl;
         //Set variables based on particle
         std::vector<std::string> relevant_variables = set_variables(particles[p], variables);

         //Loop over variables
         for (int v = 0; v < relevant_variables.size(); v++){
            cout << "-- Getting variable: " << relevant_variables[v] << " --" << endl;
            //Initialize h_sum
            //Example: h_eta_H_all_mH300
            string h_sumS = "h_" + relevant_variables[v] + particles[p] + hist_data + "_mH" + mH_masses[m];
            string h_scaleS = "h_" + relevant_variables[v] + particles[p] + "_scale_mH" + mH_masses[m];
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