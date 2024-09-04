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
Brief version:
- Copy analysis/source/ directory to your working directory (assumed to be on lxplus)
- In that working directory, create build/ and run/ directories
- In build/
    - setupATLAS
    - asetup AnalysisBase,24.2.35
    - cmake ../source/
    - make
- In run/
    - source ../build/x86_64-el9-gcc13-opt/setup.sh
    - ATestRun_eljob.py --submission-dir=submitDir
    - Repeat for any more DAOD files (you can edit the inputFilePath in ATestRun_eljob.py)
- On your local PC, in the repository main directory (4lMET_Ana/)
    - scp the hist-reco.root files from the folder generated in the previous step to a folder outside of 4lMET_Ana/
    - root basic-analysis/sum_Nparticles.C
    - root basic-analysis/plot_Stacks.C

Detailed version:

## Environments
### Generation code
Lxplus
- HTCondor version??
- MadGraph version??
- Pythia version??
- Python 3.9.12
- ROOT Version: 6.28/10
### Analysis Code
Lxplus:
- ROOT Version: 6.28/10
- Python Version: 3.9.12
- Platform: linuxx8664gcc
- Compiler: g++ (GCC) 13.1.0
- C++ version??
Local PC:
- ROOT Version: 6.28/00
- Python 3.11.3
- C++ version??

## General info
### Generation code
- Simulated decay data is generated in two steps:
    - Generation programs (e.g. Pythia, MadGraph, HERWIG) simulate decays using quantum mechanics and the Monte Carlo (MC) method.
    - Reconstruction programs repackage the resulting data into .root files
- Decay chains, particles, decay widths, etc. can be customized.
- Resulting data is called 'truth level' data - all information on all particles is known.
- A typical sample fit for analysis:
    - 10,000 decay events
    - 0.5-1 hour to generate
    - 3-5Gb of data
### Analysis code
Analysis code has 3 sections
- includes/ - commonly used functions written as their own files
    - getHistParams - returns the number of bins and x-axis range of input histogram INCOMPLETE
    - scaleHist - scales a histogram and writes it to a .root file 
    - stackHists - loops through iterable, adding histograms to THStack, then draws and saves the THStack plot
    - sumHists - loops through iterable, adding histograms together, then writes the combined histogram to a .root file
    - updateMaxEntries - returns the max of (max bin entries for a given hist : given float)
- basic-analysis/ - takes you from a DAOD file to basic kinematic plots
    - The source/ directory contains code for running through events and saving relevant variables to histograms in a .root file
    - sum_Nparticles.C takes the .root file produced from the previous step and in the cases where there are multiple instances of one particle per event, it combines those histograms into one in a new .root file
    - plot_Stacks.C takes the .root file produced from sum_Nparticles.C and produces quality plots as .pdf or .png files.
- advanced-analyses/ - codes for specific analyses
    - For example scaling based on a variable, looking at variables when boosted into a new reference frame, etc.
    - How to run each analysis is detailed in the README.md file in the advance-analyses/ directory.