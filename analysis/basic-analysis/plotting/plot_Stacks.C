#include "../../includes/stackHists.cpp"
#include "../../includes/setVariables.cpp"

using namespace std;

// vector<string> set_variables(string particle, vector<string>& input_list){
//    //Function to set the variable list based on what particle you are given
//    std::vector<std::string> v_list = input_list;
//    if (particle == "missingET_NonInt" || particle == "missingET"){
//       //For MET, no variables (i.e. the list only has one element - an empty string)
//       v_list.assign(v_list.begin(), v_list.begin()+1);
//       }
//    else if (particle == "u" || particle == "e"){
//       //For electrons and muons, do not use mass
//       v_list.assign(v_list.begin()+1, v_list.end()-1);
//    }
//    else {
//       // For all other particles
//       v_list.assign(v_list.begin()+1, v_list.end());
//    }

//    return v_list;
// }

void plot_Stacks()
{
    /*
    Function to take files with variables for each particle type and scale these histograms according to a varying normalization factor
    Initialize file paths, lists of particles, variables, masses, etc. to sum over
    Initialize input file
    Loop over different particles
        Use set_variables() function to define what variables are relevant to that particle
        Loop over different variables
            Initialize a sum histogram
            Loop over mH masses
                Initialize histogram name (depends on variable, particle, number of that particle)
                Apply scaleHist.cpp function
    Close file
    */

   //Initialize some variables
   string f_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/git_Zd/"; //Working dir
   // string inFile_S = f_path + "tests_2024-07-03/summed-Particles_all-mH.root"; //In kinematics file
   string inFile_S = f_path + "tests_2024-07-03/scaled-Particles_all-mH.root"; //In scaled kinematics file
   string particles[] = {"H", "S", "Zd", "e", "u", "missingET", "missingET_NonInt"}; //Different kinds of particles included in the input file
   // string particles[] = {"S"};
   std::vector<std::string> variables = {"", "phi_", "eta_", "pT_", "m"};
   string mH_masses[11] = {"300", "350", "400", "450", "500", "550", "600", "650", "700", "750", "800"}; //Different masses of H particle
   int n_masses = sizeof(mH_masses) / sizeof(mH_masses[0]);

   //Create input and output files
   TFile *inFile = new TFile( (inFile_S).c_str(), "read" );

   //Loop over particles
   for (int p = 0; p < sizeof(particles)/sizeof(particles[0]); p++){
      cout << "~~~~~~~ Getting particle: " << particles[p] << " ~~~~~~~" << endl;
      //Set variables based on particle
      std::vector<std::string> relevant_variables = setVariables(particles[p], variables);

      //Loop over variables
      for (int v = 0; v < relevant_variables.size(); v++){
         cout << "-- Getting variable: " << relevant_variables[v] << " --" << endl;

         //Call stackHists
         stackHists(inFile, f_path+"tests_2024-07-03/", "pfc hist",
                relevant_variables[v], particles[p], "scale",
                mH_masses, sizeof(mH_masses) / sizeof(mH_masses[0]), "mH");

      } //Close variables

   } //Close particles loop

   cout << "Closing: " << inFile_S << endl;
   inFile -> Close();
}