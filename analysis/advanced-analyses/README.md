# Advanced Analyses
Includes code for anything beyond the simple analysis for generating basic kinematics. Advanced analyses can include adding cuts, analysing over multiple .root files, adding boosting, adding scaling, etc.

## mH-scaling/
Investigates H>2S>4Zd>4l+MET decays over multiple mH masses, scaling all histograms acc. to an mH-specific normalization factor

- crystal-ball-fits/
    - Generates normalization factors by fitting a double-sided crystal ball function to non-resonant di-Higgs data
- scale_All.cpp - scales kinematics acc. to normalization factors, saves to .root file

## baseline-lepton-cuts/
Introduces baseline lepton cuts from High Mass Analysis support note, Table 1: https://cds.cern.ch/record/2653360/files/ATL-COM-PHYS-2019-005.pdf

- baseline-lepton-cuts.cpp - similar to basic-analysis code but adds in baseline e/mu cuts and checks how many leptons make it through these cuts.