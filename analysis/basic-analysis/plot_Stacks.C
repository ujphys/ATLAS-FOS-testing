#include "../../includes/stackHists.cpp"
#include "../../includes/setVariables.cpp"

using namespace std;

void plot_Stacks()
{
    /*
    Function to take files with variables for each particle type, scale these histograms according to a varying normalization factor and plot these as stacks

    Initialize file paths, lists of particles, variables, masses, etc. to sum over
    Initialize input file
    Loop over different particles
        Use set_variables() function to define what variables are relevant to that particle
        Loop over different variables
            Initialize a sum histogram
            Loop over mH masses
                Initialize histogram name (depends on variable, particle, number of that particle)
                Call stackHists.cpp function (saves plots)
    Close file
    */

    // SET FILE PATHS HERE
    string f_path = "/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/code_ZdZd/git_Zd/"; //Working dir
    string inFile_S = f_path + "tests_2024-07-03/test_sum_Nparticles2.root"; //In kinematics file
    // string inFile_S = f_path + "tests_2024-08-21/test_scale_All.root"; //In scaled kinematics file
    //Create input and output files
    TFile *inFile = new TFile( (inFile_S).c_str(), "read" );
    //Initialize some variables
    string particles[] = {"H", "S", "Zd", "e", "u", "missingET", "missingET_NonInt"}; //Different kinds of particles included in the input file
    std::vector<std::string> variables = {"", "phi_", "eta_", "pT_", "m"};
    string mH_masses[11] = {"300", "350", "400", "450", "500", "550", "600", "650", "700", "750", "800"}; //Different masses of H particle
    int n_masses = sizeof(mH_masses) / sizeof(mH_masses[0]);

   // Loop over particles
   for (int p = 0; p < sizeof(particles)/sizeof(particles[0]); p++){
      cout << "~~~~~~~ Getting particle: " << particles[p] << " ~~~~~~~" << endl;
      // Set variables based on particle
      std::vector<std::string> relevant_variables = setVariables(particles[p], variables);

      // Loop over variables
      for (int v = 0; v < relevant_variables.size(); v++){
         cout << "-- Getting variable: " << relevant_variables[v] << " --" << endl;

         // Call stackHists
         stackHists(inFile, f_path+"tests_2024-08-21/", "pfc hist",
                relevant_variables[v], particles[p], "all",
                mH_masses, sizeof(mH_masses) / sizeof(mH_masses[0]), "mH");

      } // Close variables

   } // Close particles loop

   cout << "Closing: " << inFile_S << endl;
   inFile -> Close();
}