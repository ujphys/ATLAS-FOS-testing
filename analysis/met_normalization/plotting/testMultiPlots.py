from __future__ import print_function
from ROOT import *
from MultiPlots_lib import SetDrawOptions
import os, tarfile
### Disable display output
# os.environ["DISPLAY"]="0"

gStyle.SetOptStat(0)
gStyle.SetOptTitle(0)


filePath='/eos/user/c/connell/lepton_jets/lepton_jets_model/validation_plots/run/submitDir'


l_colors = [1,2,kGreen+2,4,6,kCyan-3,kOrange-3]

l_TObjectName = ["h_DG_Pt",
                 "h_DG_eta",
                 "h_DG_phi",
                 "h_DG_deltaPhi",

                 "h_fd2Pt",
                 "h_fd2Eta",
                 "h_fd2Phi",
                 "h_fd2M",

                 "h_fd1Pt",
                 "h_fd1Eta",
                 "h_fd1Phi",
                 "h_fd1M",

                 "h_leadMuonPt",
                 "h_subLeadMuonPt",
                 "h_muonPhi",
                 "h_muonEta",
                 "h_muonPairInvMass",
                 "h_muonPairOpenAngle",

                 "h_leadElecPt",
                 "h_subLeadElecPt",
                 "h_elecPhi",
                 "h_elecEta",
                 "h_elecPairInvMass",
                 "h_elecPairOpenAngle",

                 "h_higgsEta",
                 "h_higgsPhi",
                 "h_higgsPt",
                 "h_higgsM",

                 "h_4lInvMass",
                 "h_missingET",

                 #Boosted
                 "h_higgsPt_boost",
                 "h_fd2Pt_boost",
                 "h_fd1Pt_boost",]

l_label = ["Dark Photon Pt [MeV]",
           "Dark Photon Eta",
           "Dark Photon #phi",
           "Dark Photon #Delta#phi",

           "fd2 Pt [MeV]",
           "fd2 Eta",
           "fd2 #phi [rad]",
           "fd2 mass [MeV]",

           "HLSP Pt [MeV]",
           "HLSP Eta",
           "HLSP #phi [rad]",
           "HLSP mass [MeV]",

           "Leading Muon Pt [MeV]",
           "Subleading Muon Pt [MeV]",
           "Muon #phi [rad]",
           "Muon Eta",
           "Muon Pair Inv. Mass [MeV]",
           "Muon Pair #DeltaR",

           "Leading Elec Pt [MeV]",
           "SubLeading electron Pt [MeV]",
           "Electron #phi [rad]",
           "Electron Eta",
           "Electron pair Invariant Mass [MeV]",
           "Electron Pair #DeltaR",

           "Higgs Pt [MeV]",
           "Higgs Eta",
           "Higgs #phi [rad]",
           "Higgs mass [MeV]",

           "4-lepton Invariant Mass",
           "MET",

           #Boosted
           "Higgs Pt (Higgs Frame)",
           "Dark lepton Pt (Higgs Frame)",
           "HLSP Pt (Higgs Frame)",]

#os.system("mkdir -p plots")

my_file = "/hist-reco.root"
file = TFile(filePath+my_file)

# ### Loop over list_of_samples first axis
# for sample in list_of_samples:
#     sample_index = list_of_samples.index(sample)
#     os.system("mkdir -p plots/{0}".format(subfolderName[sample_index]))
#     l_files = ["hist-DAOD_TRUTH1."+s+".root" for s in sample]
#     l_TFile = [TFile(filePath+my_file )for my_file in l_files if os.path.isfile(filePath+my_file)]

    

    ### Loop over TObjects
    ### plots of every quantity for each sample (sample = file)
for i in range(len(l_TObjectName)):
    c1 = TCanvas(l_label[i],l_label[i],1)
        #legend = TLegend()
    histMax = -999
    h = file.Get(l_TObjectName[i])
    SetDrawOptions(h,"125",l_TObjectName[i])
    # if h.Integral()==0:
    #     continue

    # if h.GetMaximum()/h.Integral() >= histMax:
    #     histMax = h.GetMaximum()/h.Integral()
    # h = file.Get(l_TObjectName[i])
    # if h.Integral()==0:
    #     continue
    # h.Scale(1./h.Integral())

            # labels and title
    h.SetTitle(l_label[i])
    h.GetXaxis().SetTitle(l_label[i])
    h.GetYaxis().SetTitle("N. of entries")
    h.GetYaxis().SetTitleOffset(1.4)

#     # Skip this for logy plots
#     if("OpenAngle" not in l_TObjectName[i]):
# #          if(True):
#         h.GetYaxis().SetRangeUser(0.,histMax * 1.2)
#
#     if ("OpenAngle" in l_TObjectName[i]):
#         h.GetXaxis().SetRangeUser(0.,1.)
            # line color and style
        # h.SetLineColor(l_colors[l_TFile.index(file)])
            #h.SetLineWidth(2)

            #SetName

        # h.SetTitle(sampleDict[sample[file.index(file)]])
            # external Draw options
    print("Now drawing {}".format(l_label[i]))
    h.Draw("hist same")
            #legend.AddEntry(h,sampleDict[sample[l_TFile.index(f)]],"l")
        
    c1.Draw()
    c1.SaveAs("try1_plots/" + l_label[i] + ".png")
        #c1.BuildLegend()
        # Set logy for some plots
