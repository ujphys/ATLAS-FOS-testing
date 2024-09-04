/*
INPUT string and vector list of strings
    Edit the list based on the input string
    Input string represents a particle while the output list represents the variables associated with it.
    Example variable list: {"", "phi_", "eta_", "pT_", "m"};
OUTPUT new vector list of strings

TODO
?
*/

#include <iostream>
#include <string>
#include <vector>

void setVariables(const std::string& particle, std::vector<std::string>& output_list) {
    // Clear the output list
    output_list.clear();

    // Check each line and set the output_list accordingly
    if (particle == "missingET_NonInt" || particle == "missingET") {
        output_list = {""};
    }
    else if (particle == "H" || particle == "Zd" || particle == "S") {
        output_list = {"pT_", "eta_", "phi_", "m_"};
    }
    else if (particle == "e" || particle == "u") {
        output_list = {"pT_", "eta_", "phi_"};
    }
    else if (particle == "2l_leading" || particle == "2l_subleading") {
        output_list = {"pT_"};
    }
    else if (particle == "4l") {
        output_list = {"pT_", "eta_", "phi_", "invMass_"};
    }
    else if (particle == "l1l2" || particle == "l3l4") {
        output_list = {"eta_", "phi_", "invMass_", "deltaR_"};
    }
    else if (particle == "l1l4" || particle == "l2l3") {
        output_list = {"deltaR_"};
    }
}