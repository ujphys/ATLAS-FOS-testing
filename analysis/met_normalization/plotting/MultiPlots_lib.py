def SetDrawOptions(h, sample_tag, objName):

    if "deltaPhi" in objName:
        h.Rebin(2)

    # if "Angle" in objName:
    #     h.Rebin(2)

    if "Pt" in objName:
        h.Rebin(2)
        h.GetXaxis().SetRangeUser(0,500000)
        

    if "125" in sample_tag:
        if "nDP2" in sample_tag:
            if objName in ["h_DG_Pt","h_fd2Pt","h_fd1Pt","h_hsPt"]:
                h.GetXaxis().SetRangeUser(0,150000)
            if objName in ["h_subLeadHadPt","h_leadHadPt","h_leadMuonPt","h_subLeadMuonPt","h_leadElecPt","h_subLeadElecPt"]:
                h.GetXaxis().SetRangeUser(0,100000)
        if "nDP4" in sample_tag:
            if objName in ["h_DG_Pt","h_fd2Pt","h_fd1Pt","h_hsPt"]:
                h.GetXaxis().SetRangeUser(0,100000)
            if objName in ["h_subLeadHadPt","h_leadHadPt","h_leadMuonPt","h_subLeadMuonPt","h_leadElecPt","h_subLeadElecPt"]:
                h.GetXaxis().SetRangeUser(0,50000)

    if "800" in sample_tag:
        if "nDP2" in sample_tag:
            if objName in ["h_DG_Pt","h_fd2Pt","h_fd1Pt","h_hsPt"]:
                h.Rebin(10)
                h.GetXaxis().SetRangeUser(0,700000)

            if objName in ["h_subLeadHadPt","h_leadHadPt","h_leadMuonPt","h_subLeadMuonPt","h_leadElecPt","h_subLeadElecPt"]:
                h.Rebin(10)
                h.GetXaxis().SetRangeUser(0,500000)

        if "nDP4" in sample_tag:
            if objName in ["h_DG_Pt","h_fd2Pt","h_fd1Pt","h_hsPt"]:
                h.Rebin(10)
                h.GetXaxis().SetRangeUser(0,700000)
            if objName in ["h_subLeadHadPt","h_leadHadPt","h_leadMuonPt","h_subLeadMuonPt","h_leadElecPt","h_subLeadElecPt"]:
                h.Rebin(10)
                h.GetXaxis().SetRangeUser(0,500000)



