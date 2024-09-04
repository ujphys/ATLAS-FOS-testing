# ATLAS Analysis: Additional Scalar (AS) decay via dark vector bosons to a 4-lepton plus MET final state
# H(d) -> 2S -> 4Zd -> 4l + MET

## Repository purpose/ aim/ goal
The purpose of this repository is to generate data for decays with a 4l+MET final state, then analyse this data.
The repository is divided into two main sections:
- Generation code - produces simulated data
- Analysis code - produces plots and useful information from simulated data



## How to run
### Generation
### Basic Analysis
- Set up build, source and run directories (assumed to be done on lxplus here)
- Ensure the latest versions of event-analysis.cxx and event-analysis.h are used
- In build/
    - setupATLAS
    - asetup AnalysisBase,24.2.35
    - cmake ../source/
    - make
- In run/
    - source ../build/x86_64-el9-gcc13-opt/setup.sh
    - ATestRun_eljob.py --submission-dir=submitDir
    - Repeat for any more DAOD files (you can edit the inputFilePath in ATestRun_eljob.py)
- On your own PC, from repository main directory (4lMET_Ana/)
    - scp the hist-reco.root files from the folder generated in the previous step
    - root basic-analysis/sum_Nparticles.C
    - root basic-analysis/plot_Stacks.C

## Environments
### Generation code
Must be run in your personal folder on AFS in lxplus, e.g. ??
- HTCondor version??
- Python version??
- MadGraph version??
- Pythia version??
- ROOT version??
### Analysis Code
Can be run locally
- ROOT version??
- Python version??
- C++ version??

## TO DO
- Fix main README
- - Code purpose DONE
- - Describe generation code DONE
- - Describe analysis code
- - How to run code
- Change variable checking function to its own file
- Rationalize analysis code more
- Fix analysis README
- Commit all
- Merge side branch with main
- Add versions to main README

## General info
### Generation code
- Simulated decay data is generated in two steps:
- - Generation programs (e.g. Pythia, MadGraph, HERWIG) simulate decays using quantum mechanics and the Monte Carlo (MC) method.
- - Reconstruction programs repackage the resulting data into .root files
- Decay chains, particles, decay widths, etc. can be customized.
- Resulting data is called 'truth level' data - all information on all particles is known.
- A typical sample fit for analysis:
- - 10,000 decay events
- - 0.5-1 hour to generate
- - 3-5Gb of data
### Analysis code
Analysis code has 3 sections
- includes/ - commonly used functions written as their own files
- - getHistParams - returns the number of bins and x-axis range of input histogram INCOMPLETE
- - scaleHist - scales a histogram and writes it to a .root file 
- - stackHists - loops through iterable, adding histograms to THStack, then draws and saves the THStack plot
- - sumHists - loops through iterable, adding histograms together, then writes the combined histogram to a .root file
- - updateMaxEntries - returns the max of (max bin entries for a given hist : given float)
- basic-analysis/
- - 
- advanced-analyses/ - codes for specific analyses
- - For example scaling based on a variable, looking at variables when boosted into a new reference frame, etc.
- - How to run each analysis is detailed in the README.md file in the advance-analyses/ directory.

### Languages used
 - Generation: ROOT, C++, Python, Shell, MadGraph, Pythia
 - Analysis: ROOT, C++, Python, Shell
(What versions??)

All code is intended to be run on lxplus, the remote computing service for CERN. This requires ssh and a CERN account.
Generation and Analysis are run separately and each may contain sub-folders with different code that is run separately for different occasions.
More detailed instructions on how to run the code is found in the subfolders.

Solved using vectors.
There is a function called set_variables() that is defined in scale_All.cpp and is used to determine what vectors to use for what input.
This function needs to be added to the includes/ folder