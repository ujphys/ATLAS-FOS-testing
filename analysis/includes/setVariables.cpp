/*
INPUT string and vector list of strings
    Edit the list based on the input string
    Input string represents a particle while the output list represents the variables associated with it.
    Example variable list: {"", "phi_", "eta_", "pT_", "m"};
OUTPUT new vector list of strings

TODO
Make more intuitive - maybe assign a list of variables for each particle, rather than having an input list and adjusting it
*/

vector<string> setVariables(string particle, vector<string>& input_list){
   // Copy input list to intermediate list
   std::vector<std::string> output_list = input_list;

    if (particle == "missingET_NonInt" || particle == "missingET"){
      // For MET, no variables (i.e. the list only has one element - an empty string)
      output_list.assign(output_list.begin(), output_list.begin()+1);
    }
    else if (particle == "u" || particle == "e"){
      // For electrons and muons, do not use mass
      output_list.assign(output_list.begin()+1, output_list.end()-1);
    }
    else {
      // For all other particles
      output_list.assign(output_list.begin()+1, output_list.end());
    }

   return output_list;
}