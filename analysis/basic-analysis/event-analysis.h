#ifndef MyAnalysis_MyxAODAnalysis_H
#define MyAnalysis_MyxAODAnalysis_H

#include <AnaAlgorithm/AnaAlgorithm.h>
#include <TrigConfxAOD/xAODConfigTool.h>
#include <AsgTools/AnaToolHandle.h>

#include <TH1D.h>
#include <set>

#define DARK_PHOTON_PDGID 3000001
#define FD1_PDGID 1000022
#define FD2_PDGID 3000012
#define HS_PDGID 3000001
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
    /*
    Histogram names should follow this format
    h_ + variable + _ particle type + particle number
    E.g. h_m_Zd2 for the mass histogram of the 2nd dark vector boson (Zd2)
    */

    //Mass hists //
    TH1D* h_m_H = new TH1D();
    TH1D* h_m_S1 = new TH1D();
    TH1D* h_m_S2 = new TH1D();
    TH1D* h_m_Zd1 = new TH1D(); //Zd
    TH1D* h_m_Zd2 = new TH1D();
    TH1D* h_m_Zd3 = new TH1D();
    TH1D* h_m_Zd4 = new TH1D();
    //pT hists //
    TH1D* h_pT_H = new TH1D();
    TH1D* h_pT_S1 = new TH1D();
    TH1D* h_pT_S2 = new TH1D();
    TH1D* h_pT_Zd1 = new TH1D(); //Zd
    TH1D* h_pT_Zd2 = new TH1D();
    TH1D* h_pT_Zd3 = new TH1D();
    TH1D* h_pT_Zd4 = new TH1D();
    TH1D* h_pT_e1 = new TH1D(); //Electrons
    TH1D* h_pT_e2 = new TH1D();
    TH1D* h_pT_e3 = new TH1D();
    TH1D* h_pT_e4 = new TH1D();
    TH1D* h_pT_u1 = new TH1D(); //Muons
    TH1D* h_pT_u2 = new TH1D();
    TH1D* h_pT_u3 = new TH1D();
    TH1D* h_pT_u4 = new TH1D();
    //Eta hists //
    TH1D* h_eta_H = new TH1D();
    TH1D* h_eta_S1 = new TH1D();
    TH1D* h_eta_S2 = new TH1D();
    TH1D* h_eta_Zd1 = new TH1D(); //Zd
    TH1D* h_eta_Zd2 = new TH1D();
    TH1D* h_eta_Zd3 = new TH1D();
    TH1D* h_eta_Zd4 = new TH1D();
    TH1D* h_eta_e1 = new TH1D(); //Electrons
    TH1D* h_eta_e2 = new TH1D();
    TH1D* h_eta_e3 = new TH1D();
    TH1D* h_eta_e4 = new TH1D();
    TH1D* h_eta_u1 = new TH1D(); //Muones
    TH1D* h_eta_u2 = new TH1D();
    TH1D* h_eta_u3 = new TH1D();
    TH1D* h_eta_u4 = new TH1D();
    //Phi hists //
    TH1D* h_phi_H = new TH1D();
    TH1D* h_phi_S1 = new TH1D();
    TH1D* h_phi_S2 = new TH1D();
    TH1D* h_phi_Zd1 = new TH1D(); //Zd
    TH1D* h_phi_Zd2 = new TH1D();
    TH1D* h_phi_Zd3 = new TH1D();
    TH1D* h_phi_Zd4 = new TH1D();
    TH1D* h_phi_e1 = new TH1D(); //Electrons
    TH1D* h_phi_e2 = new TH1D();
    TH1D* h_phi_e3 = new TH1D();
    TH1D* h_phi_e4 = new TH1D();
    TH1D* h_phi_u1 = new TH1D(); //Muons
    TH1D* h_phi_u2 = new TH1D();
    TH1D* h_phi_u3 = new TH1D();
    TH1D* h_phi_u4 = new TH1D();
    //Energy hists //
    TH1D* h_e_e1 = new TH1D(); //Electrons
    TH1D* h_e_e2 = new TH1D();
    TH1D* h_e_e3 = new TH1D();
    TH1D* h_e_e4 = new TH1D();
    TH1D* h_e_u1 = new TH1D(); //Muons
    TH1D* h_e_u2 = new TH1D();
    TH1D* h_e_u3 = new TH1D();
    TH1D* h_e_u4 = new TH1D();
    //Multi lepton hists //
    TH1D* h_pT_ee12 = new TH1D();
    TH1D* h_pT_ee34 = new TH1D();
    TH1D* h_pT_uu12 = new TH1D();
    TH1D* h_pT_uu34 = new TH1D();
    //Leading and subleading lepton hists //
    TH1D* h_pT_ee_lead = new TH1D();
    TH1D* h_pT_ee_sublead = new TH1D();
    TH1D* h_pT_uu_lead = new TH1D();
    TH1D* h_pT_uu_sublead = new TH1D();
    TH1D* h_pT_lead = new TH1D();
    TH1D* h_pT_sublead = new TH1D();
    //MET hists //
    TH1* h_missingET;
    TH1* h_missingET_NonInt;

    //Test these
    // TH1D* h_M_S1 = new TH1D();
    // TH1D* h_M_Zd1 = new TH1D();
    // TH1D* h_invMass_l1l2 = new TH1D();
    // TH1D* h_invMass_l3l4 = new TH1D();
    // TH1D* h_invMass_4l = new TH1D();
    // TH1D* h_vectorInvMass_l1l2 = new TH1D();
    // TH1D* h_vectorInvMass_l3l4 = new TH1D();
    // TH1D* h_vectorInvMass_4l = new TH1D();
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

