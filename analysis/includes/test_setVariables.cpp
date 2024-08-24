#include "scaleHist.cpp"
#include "setVariables.cpp"
#include "updateMaxEntries.cpp"

void test_setVariables(){
    string particles[] = {"H", "S", "Zd", "e", "u", "missingET", "missingET_NonInt"}; //Different kinds of particles included in the input file
    std::vector<std::string> variables = {"", "phi_", "eta_", "pT_", "m"};

    setVariables("H", variables);

    //Loop over particles
    for (int p = 0; p < sizeof(particles)/sizeof(particles[0]); p++){
        cout << "~~~~~~~ Getting particle: " << particles[p] << " ~~~~~~~" << endl;
        //Set variables based on particle
        std::vector<std::string> relevant_variables = setVariables(particles[p], variables);
        // cout << setVariables(particles[p], variables) << endl;

        // Loop over variables
        for (int v = 0; v < relevant_variables.size(); v++){
            cout << "-- Getting variable: " << relevant_variables[v] << " --" << endl;
            // Initialize h_sum
            // Example: h_eta_H_all_mH300
            // string h_sumS = "h_" + relevant_variables[v] + particles[p] + hist_data + "_mH" + mH_masses[m];
            // string h_scaleS = "h_" + relevant_variables[v] + particles[p] + "_scale_mH" + mH_masses[m];
            // // Apply scaleHist()
            // cout << h_sumS << endl;
            // cout << h_scaleS << endl;
            // cout << norm_factors[m] << endl;
            // scaleHist(inFile, outFile, h_sumS, h_scaleS, norm_factors[m]);
        }
    }
}