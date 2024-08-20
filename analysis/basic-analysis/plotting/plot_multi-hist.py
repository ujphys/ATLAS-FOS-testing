#from _future_ import print_function
from ROOT import *
from MultiPlots_lib import SetDrawOptions
import os, tarfile
# import atlasplots as aplt
# astyle.SetAtlasStyle()
# astyle.ATLASLabel(0.2, 0.87, "Internal")
# atlas_style.ATLASLabel(0, 0, text=None, color=1)
### Disable display output
# os.environ["DISPLAY"]="0"

gStyle.SetOptStat(0)
gStyle.SetOptTitle(0)
gROOT.SetStyle("ATLAS")
# aplt.set_atlas_style()

# filePath='/home/mattc/Documents/met4l/met4l_data/h250_zd30/zd30-h250-hists/'
filePath='/eos/user/c/connell/met4l-analysis/diS_model/val2/run/plotting/fig8_new-MET-hists1'
# filePath = '/afs/cern.ch/user/x/xmapekul/mc_prod_validation/MCValidation'

l_colors = [1,2,kGreen+2,4,6,kCyan-3,kOrange-3]

#Create new histogram
# print("Creating new hist")
# test_hist = ROOT.TH1D("test","m_ll , data " ,150 ,50.e3 ,200.e3)

l_TObjectName = [
                 'h_missingET',
                 'h_missingET_NonInt',
                #  'test_hist',
                 'h_missingET_Yscaled1',
                 'h_missingET_Xscaled',
                 ]

l_label = [
           'All MET? [GeV]',
           'MET Scaled [GeV]',
        #    'Scaled MET',
           'MET [GeV]',
           'X-Normalized MET [GeV]',
           ]

os.system("mkdir -p plots")

my_file1 = "/hist-reco-mH300.root"
my_file2 = "/hist-reco-mH350.root"
my_file3 = "/hist-reco-mH400.root"
my_file4 = "/hist-reco-mH450.root"
my_file5 = "/hist-reco-mH500.root"
my_file6 = "/hist-reco-mH550.root"
my_file7 = "/hist-reco-mH600.root"
my_file8 = "/hist-reco-mH650.root"
my_file9 = "/hist-reco-mH700.root"
my_file10 = "/hist-reco-mH750.root"
my_file11 = "/hist-reco-mH800.root"
file1 = TFile(filePath+my_file1)
file2 = TFile(filePath+my_file2)
file3 = TFile(filePath+my_file3)
file4 = TFile(filePath+my_file4)
file5 = TFile(filePath+my_file5)
file6 = TFile(filePath+my_file6)
file7 = TFile(filePath+my_file7)
file8 = TFile(filePath+my_file8)
file9 = TFile(filePath+my_file9)
file10 = TFile(filePath+my_file10)
file11 = TFile(filePath+my_file11)
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
    h1 = file1.Get(l_TObjectName[i])
    h2 = file2.Get(l_TObjectName[i])
    h3 = file3.Get(l_TObjectName[i])
    h4 = file4.Get(l_TObjectName[i])
    h5 = file5.Get(l_TObjectName[i])
    h6 = file6.Get(l_TObjectName[i])
    h7 = file7.Get(l_TObjectName[i])
    h8 = file8.Get(l_TObjectName[i])
    h9 = file9.Get(l_TObjectName[i])
    h10 = file10.Get(l_TObjectName[i])
    h11 = file11.Get(l_TObjectName[i])
    
    h1.SetTitle(l_label[i])
    h1.GetXaxis().SetTitle(l_label[i])
    h1.GetYaxis().SetTitle("Entries")
    h1.GetYaxis().SetTitleOffset(1.4)
    h1.SetLineColor(1)
    
    h2.SetTitle(l_label[i])
    h2.GetXaxis().SetTitle(l_label[i])
    h2.GetYaxis().SetTitle("Entries")
    h2.GetYaxis().SetTitleOffset(1.4)
    h2.SetLineColor(2)

    h3.SetTitle(l_label[i])
    h3.GetXaxis().SetTitle(l_label[i])
    h3.GetYaxis().SetTitle("Entries")
    h3.GetYaxis().SetTitleOffset(1.4)
    h3.SetLineColor(3)

    h4.SetTitle(l_label[i])
    h4.GetXaxis().SetTitle(l_label[i])
    h4.GetYaxis().SetTitle("Entries")
    h4.GetYaxis().SetTitleOffset(1.4)
    h4.SetLineColor(4)

    h5.SetTitle(l_label[i])
    h5.GetXaxis().SetTitle(l_label[i])
    h5.GetYaxis().SetTitle("Entries")
    h5.GetYaxis().SetTitleOffset(1.4)
    h5.SetLineColor(5)

    h6.SetTitle(l_label[i])
    h6.GetXaxis().SetTitle(l_label[i])
    h6.GetYaxis().SetTitle("Entries")
    h6.GetYaxis().SetTitleOffset(1.4)
    h6.SetLineColor(6)

    h7.SetTitle(l_label[i])
    h7.GetXaxis().SetTitle(l_label[i])
    h7.GetYaxis().SetTitle("Entries")
    h7.GetYaxis().SetTitleOffset(1.4)
    h7.SetLineColor(7)
    
    h8.SetTitle(l_label[i])
    h8.GetXaxis().SetTitle(l_label[i])
    h8.GetYaxis().SetTitle("Entries")
    h8.GetYaxis().SetTitleOffset(1.4)
    h8.SetLineColor(8)

    h9.SetTitle(l_label[i])
    h9.GetXaxis().SetTitle(l_label[i])
    h9.GetYaxis().SetTitle("Entries")
    h9.GetYaxis().SetTitleOffset(1.4)
    h9.SetLineColor(9)

    h10.SetTitle(l_label[i])
    h10.GetXaxis().SetTitle(l_label[i])
    h10.GetYaxis().SetTitle("Entries")
    h10.GetYaxis().SetTitleOffset(1.4)
    h10.SetLineColor(kCyan-3)

    h11.SetTitle(l_label[i])
    h11.GetXaxis().SetTitle(l_label[i])
    h11.GetYaxis().SetTitle("Entries")
    h11.GetYaxis().SetTitleOffset(1.4)
    h11.SetLineColor(kGreen+2)

    if l_TObjectName[i] == 'h_missingET_NonInt':
        h1.SetMaximum(250)
        h2.SetMaximum(250)
        h3.SetMaximum(250)
        h4.SetMaximum(250)
        h5.SetMaximum(250)
        h6.SetMaximum(250)
        h7.SetMaximum(250)
        h8.SetMaximum(250)
        h9.SetMaximum(250)
        h10.SetMaximum(250)
        h11.SetMaximum(250)

    h1.Draw("hist same")
    h2.Draw("hist same")
    h3.Draw("hist same")
    h4.Draw("hist same")
    h5.Draw("hist same")
    h6.Draw("hist same")
    h7.Draw("hist same")
    h8.Draw("hist same")
    h9.Draw("hist same")
    h10.Draw("hist same")
    h11.Draw("hist same")


    leg = TLegend(.60, .25, .8, .75)
    leg.SetBorderSize(0)
    leg.SetFillColor(0)
    leg.SetFillStyle(9)
    leg.SetTextFont(42)
    leg.SetTextSize(0.04)
    leg.AddEntry(h1, "mH = 300", "f")
    leg.AddEntry(h2, "mH = 350", "f")
    leg.AddEntry(h3, "mH = 400", "f")
    leg.AddEntry(h4, "mH = 450", "f")
    leg.AddEntry(h5, "mH = 500", "f")
    leg.AddEntry(h6, "mH = 550", "f")
    leg.AddEntry(h7, "mH = 600", "f")
    leg.AddEntry(h8, "mH = 650", "f")
    leg.AddEntry(h9, "mH = 700", "f")
    leg.AddEntry(h10, "mH = 750", "f")
    leg.AddEntry(h11, "mH = 800", "f")

    leg.Draw("same")

    c1.Draw()
    c1.SaveAs("plots/" + l_label[i] + ".png")
        #c1.BuildLegend()
        # Set logy for some plots


# tar = tarfile.open("validation_plots.tar.gz","w")
# tar.add("plots")
# tar.close()
#
#
# print("\n\n\n\nscp ilongari@lxplus.cern.ch:"+os.getcwd()+"/validation_plots.tar.gz .\n")
