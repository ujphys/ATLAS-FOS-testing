from __future__ import print_function
from ROOT import *
from MultiPlots_lib import SetDrawOptions
import os, tarfile
### Disable display output
# os.environ["DISPLAY"]="0"

gStyle.SetOptStat(0)
gStyle.SetOptTitle(0)

#My PC
# filePath='/Users/matt/Documents/work/0-CERN-UJ-HEP/particle/hZdZd/Zd-code/diS_code/met-normalization/submitDir-2024-02-12-1759-5437'
#lxplus
filePath='/eos/user/c/connell/met4l-analysis/diS_model/val2/run/submitDir-2024-02-12-1759-5437'

l_colors = [1,2,kGreen+2,4,6,kCyan-3,kOrange-3]

l_TObjectName = [
                 'h_missingET',
                 'h_missingET_scaled',
                 ]

l_label = [
           'MET',
           'Normalized MET',
           ]

os.system("mkdir -p newPlots")

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
    # SetDrawOptions(h,"125",l_TObjectName[i])
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
    h.Draw("hist same")
            #legend.AddEntry(h,sampleDict[sample[l_TFile.index(f)]],"l")
        
    c1.Draw()
    c1.SaveAs("newPlots/" + l_label[i] + ".png")
        #c1.BuildLegend()
        # Set logy for some plots

    

# tar = tarfile.open("validation_plots.tar.gz","w")
# tar.add("plots")
# tar.close()
#
#
# print("\n\n\n\nscp ilongari@lxplus.cern.ch:"+os.getcwd()+"/validation_plots.tar.gz .\n")


