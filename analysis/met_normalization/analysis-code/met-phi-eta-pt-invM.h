#ifndef MyAnalysis_MyxAODAnalysis_H
#define MyAnalysis_MyxAODAnalysis_H

#include <AnaAlgorithm/AnaAlgorithm.h>
#include <TrigConfxAOD/xAODConfigTool.h>
#include <AsgTools/AnaToolHandle.h>

#include <TH1D.h>
#include <set>

#define DARK_PHOTON_PDGID 3000001
#define FD1_PDGID 1000022
#define FD2_PDGID 3000016
#define HS_PDGID 3000005
#define HIGGS_PDGID 25
class MyxAODAnalysis : public EL::AnaAlgorithm
{
public:
    // this is a standard algorithm constructor
    MyxAODAnalysis (const std::string& name, ISvcLocator* pSvcLocator);

    // these are the functions inherited from Algorithm
    int n_events;//!

    std::set<int> pdg_harvest; //!
    
    // variables that don't get filled at submission time should be
    // protected from being send from the submission node to the worker
    // node (done by the //!)
public:
    //Mass hists
    TH1D* h_mH = new TH1D();
    TH1D* h_mS = new TH1D();
    TH1D* h_mZd = new TH1D();
    TH1D* h_m4l = new TH1D();
    TH1D* h_m2l = new TH1D();
    TH1D* h_m2l_leading = new TH1D();
    TH1D* h_m2l_subleading = new TH1D();
    //pT hists
    TH1D* h_pT_H = new TH1D();
    // TH1D* h_pT_S = new TH1D();
    TH1D* h_pT_S1 = new TH1D();
    TH1D* h_pT_S2 = new TH1D();
    // TH1D* h_pT_Zd = new TH1D();
    TH1D* h_pT_Zd1 = new TH1D();
    TH1D* h_pT_Zd2 = new TH1D();
    TH1D* h_pT_Zd3 = new TH1D();
    TH1D* h_pT_Zd4 = new TH1D();
    // TH1D* h_pT_4l = new TH1D();            //All leptons
    // TH1D* h_pT_2l = new TH1D();
    // TH1D* h_pT_2l_leading = new TH1D();
    // TH1D* h_pT_2l_subleading = new TH1D();
    // TH1D* h_pT_4e = new TH1D();            //Electrons
    // TH1D* h_pT_2e = new TH1D();
    TH1D* h_pT_2e_leading = new TH1D();
    TH1D* h_pT_2e_subleading = new TH1D();
    // TH1D* h_pT_4u = new TH1D();            //Muons
    // TH1D* h_pT_2u = new TH1D();
    TH1D* h_pT_2u_leading = new TH1D();
    TH1D* h_pT_2u_subleading = new TH1D();
    //Eta hists
    TH1D* h_eta_H = new TH1D();
    // TH1D* h_eta_S = new TH1D();
    TH1D* h_eta_S1 = new TH1D();
    TH1D* h_eta_S2 = new TH1D();
    // TH1D* h_eta_Zd = new TH1D();
    TH1D* h_eta_Zd1 = new TH1D();
    TH1D* h_eta_Zd2 = new TH1D();
    TH1D* h_eta_Zd3 = new TH1D();
    TH1D* h_eta_Zd4 = new TH1D();
    // TH1D* h_eta_4l = new TH1D();            //All leptons
    // TH1D* h_eta_2l = new TH1D();
    // TH1D* h_eta_2l_leading = new TH1D();
    // TH1D* h_eta_2l_subleading = new TH1D();
    // TH1D* h_eta_4e = new TH1D();            //Electrons
    // TH1D* h_eta_2e = new TH1D();
    TH1D* h_eta_2e_leading = new TH1D();
    TH1D* h_eta_2e_subleading = new TH1D();
    // TH1D* h_eta_4u = new TH1D();            //Muons
    // TH1D* h_eta_2u = new TH1D();
    TH1D* h_eta_2u_leading = new TH1D();
    TH1D* h_eta_2u_subleading = new TH1D();
    //Phi hists
    TH1D* h_phi_H = new TH1D();
    // TH1D* h_phi_S = new TH1D();
    TH1D* h_phi_S1 = new TH1D();
    TH1D* h_phi_S2 = new TH1D();
    // TH1D* h_phi_Zd = new TH1D();
    TH1D* h_phi_Zd1 = new TH1D();
    TH1D* h_phi_Zd2 = new TH1D();
    TH1D* h_phi_Zd3 = new TH1D();
    TH1D* h_phi_Zd4 = new TH1D();
    // TH1D* h_phi_4l = new TH1D();            //All leptons
    // TH1D* h_phi_2l = new TH1D();
    // TH1D* h_phi_2l_leading = new TH1D();
    // TH1D* h_phi_2l_subleading = new TH1D();
    // TH1D* h_phi_4e = new TH1D();            //Electrons
    // TH1D* h_phi_2e = new TH1D();
    TH1D* h_phi_2e_leading = new TH1D();
    TH1D* h_phi_2e_subleading = new TH1D();
    // TH1D* h_phi_4u = new TH1D();            //Muons
    // TH1D* h_phi_2u = new TH1D();
    TH1D* h_phi_2u_leading = new TH1D();
    TH1D* h_phi_2u_subleading = new TH1D();
    //MET hists
    TH1* h_missingET;
    TH1* h_missingET_Xscaled;
    TH1D* h_missingET_NonInt = new TH1D();
    TH1D* h_missingET_Yscaled1 = new TH1D();
    TH1D* h_missingET_Yscaled2 = new TH1D();
    
//    // this is a standard constructor
//
    virtual StatusCode initialize () override;
    virtual StatusCode execute () override;
    virtual StatusCode finalize () override;

    // this is needed to distribute the algorithm to the workers
//    ClassDef(MyxAODAnalysis, 1);

private:
    // Configuration, and any other types of variables go here.
    //float m_cutValue;
    //TTree *m_myTree;
    //TH1 *m_myHist;
};

#endif

