# Plan for sum_base_vars branch

The purpose of this branch is to create a code which can sum all base variables in a .root file.

## Questions
- What particles are there?
    - H x1, S x2, Zd x4, leptons x8 (15 total)
- What is a base variable?
    - Phi, Eta, pT and mass
    - Each particle has its own variable for these histograms
    - Additionally there is MET and non-interacting MET histograms
    - 62 histograms total
- What input files?
    - 11 .root files, for mass points mH = [300, 350, ... , 800]
    - 11 * 62 = 682 histograms total

## Code plan
Run for each particle:
- Loop through mH mass points (input file)
    - Open input file
    - Loop through variables
        - Call sum function - this sums each individual particle and saves to output file 1
        - Call scale function - this just scales the summed histograms and saves them to output file 2

        !!! At this point we have the regular and scaled versions of the variables for whichever particle we're running on

    - Close files

### Summing function
- Input
    - Particle
    - Number of particles
    - Input file name
    - Output file name
- Action
    - Initialize summed histogram
        - How to get right dimensions? If clauses? Get dimensions from the histogram to be added?
    - Get histogram 1, add 
    - 