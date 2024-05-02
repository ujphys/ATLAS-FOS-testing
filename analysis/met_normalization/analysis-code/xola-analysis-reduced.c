#include <AsgMessaging/MessageCheck.h>
#include <MyAnalysis/MyxAODAnalysis.h>
#include <xAODEventInfo/EventInfo.h>
#include <EventLoop/Worker.h>
#include <TMath.h>
#include "xAODTruth/TruthEvent.h"
#include "xAODTruth/TruthEventContainer.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthVertexContainer.h"
#include <xAODMissingET/MissingETContainer.h>
#include <EventLoopAlgs/NTupleSvc.h>
#include <EventLoopAlgs/AlgSelect.h>
#include <iostream>
//#include <iomanip>
#include <fstream>

// EDM include(s):
#include "AthLinks/ElementLink.h"

// xAOD include(s):
#include "xAODBase/IParticle.h"
#include "xAODBase/ObjectType.h"

// Local include(s):
#include "xAODTruth/TruthVertexContainerFwd.h"

#include "xAODTruth/TruthParticleContainerFwd.h"



#include <typeinfo>

//auto m_runNumber ; ///< Run number
//auto m_eventNumber ; ///< Event number

MyxAODAnalysis :: MyxAODAnalysis (const std::string& name,
                                  ISvcLocator *pSvcLocator)
        : EL::AnaAlgorithm (name, pSvcLocator)
{
    // Here you put any code for the base initialization of variables,
    // e.g. initialize all pointers to 0.  This is also where you
    // declare all properties for your algorithm.  Note that things like
    // resetting statistics variables or booking histograms should
    // rather go into the initialize() function.
}



StatusCode MyxAODAnalysis :: initialize ()
{
    // Here you do everything that needs to be done at the very
    // beginning on each worker node, e.g. create histograms and output
    // trees.  This method gets called before any input files are
    // connected.
    n_events=0;
    nDarkPhoton=0;
    nToElectrons = 0;
    nToMuons = 0;
    nToQuarks = 0;
    nParentsProcessed=0;
    nfd2=0;
    nfd1=0;
    nhs=0;
    nmet=0;
    events_44=0;
    events_2222=0;
    ele_count = 0;
    muon_count = 0;
    ele_tot = 0;
    lep_stat = 0;
    muon_matched = 0;
    ele_matched = 0;

    photon_energy1 = 0;
    electron_pt1 = 0;
    electron_e1 = 0;
    energy_sum1 = 0;
    photon_energy2 = 0;
    electron_pt2 = 0;
    electron_e2 = 0;
    energy_sum2 = 0;
    photon_energy3 = 0;
    electron_pt3 = 0;
    electron_e3 = 0;
    energy_sum3 = 0;
    photon_energy4 = 0;
    electron_pt4 = 0;
    electron_e4 = 0;
    energy_sum4 = 0;
    photon_energy_tot = 0;
    electron_pt_tot = 0;
    electron_e_tot = 0;
    energy_sum_tot = 0;

    lep_rapidity[0] = 0; lep_rapidity[1] = 0; lep_rapidity[2] = 0; lep_rapidity[3] = 0; lep_rapidity[4] = 0; lep_rapidity[5] = 0; lep_rapidity[6] = 0; lep_rapidity[7] = 0;
    lep_barcode[0] = 0; lep_barcode[1] = 0; lep_barcode[2] = 0; lep_barcode[3] = 0; lep_barcode[4] = 0; lep_barcode[5] = 0; lep_barcode[6] = 0; lep_barcode[7] = 0;
    eta_truth[0] = 0; eta_truth[1] = 0; eta_truth[2] = 0; eta_truth[3] = 0; eta_truth[4] = 0; eta_truth[5] = 0; eta_truth[6] = 0; eta_truth[7] = 0;
    lep_stability[0] = 0; lep_stability[1] = 0; lep_stability[2] = 0; lep_stability[3] = 0; lep_stability[4] = 0; lep_stability[5] = 0; lep_stability[6] = 0; lep_stability[7] = 0;
    phi_truth[0] = 0; phi_truth[1] = 0; phi_truth[2] = 0; phi_truth[3] = 0; phi_truth[4] = 0; phi_truth[5] = 0; phi_truth[6] = 0; phi_truth[7] = 0;
    pt_truth[0] = 0; pt_truth[1] = 0; pt_truth[2] = 0; pt_truth[3] = 0; pt_truth[4] = 0; pt_truth[5] = 0; pt_truth[6] = 0; pt_truth[7] = 0;

    barcode_file.open("barcode.txt");
    electron_match_file.open("electron_match.txt");
    muon_match_file.open("muon_match.txt");
    lepton_children.open("lepton_child.txt");
    deltaR = 0;


    double pi = TMath::Pi();


//    xAOD::TEvent* event = wk()->xaodEvent();
//


    // Muonic child
    ANA_CHECK (book (TH1F("h_leadMuonPt","h_leadMuonPt",100,0,100)));
    ANA_CHECK (book (TH1F("h_subLeadMuonPt","h_subLeadMuonPt",100,0,100)));
    ANA_CHECK (book (TH1F("h_muonPhi","h_muonPhi",100,-4,4)));
    ANA_CHECK (book (TH1F("h_muonEta","h_muonEta",80,-8.0,8.0)));
    ANA_CHECK (book (TH1F("h_muonPairInvMass","h_muonPairInvMass",160,0.05,16.05)));
    ANA_CHECK (book (TH1F("h_muonPairOpenAngle","h_muonPairOpenAngle",100,0,2)));
    ANA_CHECK (book (TH1F("h_muonDilepMass","h_muonDilepMass",1,0,100)));



    // electron child
    ANA_CHECK (book (TH1F("h_leadElecPt","h_leadElecPt",100,0,100)));
    ANA_CHECK (book (TH1F("h_subLeadElecPt","h_subLeadElecPt",100,0,100)));
    ANA_CHECK (book (TH1F("h_elecPhi","h_elecPhi",100,-4,4)));
    ANA_CHECK (book (TH1F("h_elecEta","h_elecEta",80,-8.0,8.0)));
    ANA_CHECK (book (TH1F("h_elecPairInvMass","h_elecPairInvMass",160,0.05,16.05)));
    ANA_CHECK (book (TH1F("h_elecPairOpenAngle","h_elecPairOpenAngle",100,0,2)));
    ANA_CHECK (book (TH1F("h_electronDilepMass","h_electronDilepMass",1,0,100)));

    //missingET
    ANA_CHECK (book (TH1F("h_missingET_44","h_missingET_44",250,0,500)));
    ANA_CHECK (book (TH1F("h_missingET_2222","h_missingET_2222",102,0,300)));
    ANA_CHECK (book (TH1F("h_missingET_higgs_angle_44","h_missingET_higgs_angle_44",100,5,0)));
    ANA_CHECK (book (TH1F("h_missingET_higgs_angle_2222","h_missingET_higgs_angle_2222",100,5,0)));
    ANA_CHECK (book (TH1F("h_missingET_dilep1_angle_2222","h_missingET_dilep1_angle_2222",100,5,0)));
    ANA_CHECK (book (TH1F("h_missingET_dilep2_angle_2222","h_missingET_dilep2_angle_2222",100,5,0)));
    ANA_CHECK (book (TH1F("h_missingET_dilep1_angle_44","h_missingET_dilep1_angle_44",100,5,0)));
    ANA_CHECK (book (TH1F("h_missingET_dilep2_angle_44","h_missingET_dilep2_angle_44",100,5,0)));

    ANA_CHECK (book (TH1F("h_missingET_higgs_phi_angle_44","h_missingET_higgs_phi_angle_44",100,-4,4)));
    ANA_CHECK (book (TH1F("h_missingET_higgs_phi_angle_2222","h_missingET_higgs_phi_angle_2222",100,-4,4)));
    ANA_CHECK (book (TH1F("h_missingET_dilep1_phi_angle_2222","h_missingET_dilep1_phi_angle_2222",100,-4,4)));
    ANA_CHECK (book (TH1F("h_missingET_dilep2_phi_angle_2222","h_missingET_dilep2_phi_angle_2222",100,-4,4)));
    ANA_CHECK (book (TH1F("h_missingET_dilep1_phi_angle_44","h_missingET_dilep1_phi_angle_44",100,-4,4)));
    ANA_CHECK (book (TH1F("h_missingET_dilep2_phi_angle_44","h_missingET_dilep2_phi_angle_44",100,-4,4)));





    // quadruplet and dilepton masses
    ANA_CHECK (book (TH1F("h_4lInvMass","h_4lInvMass",240,60,180)));
    ANA_CHECK (book (TH1F("h_4lInvMass_2222","h_4lInvMass_2222",100,115,80)));
    ANA_CHECK (book (TH1F("h_4lInvMass_44","h_4lInvMass_44",80,60,180)));
    ANA_CHECK (book (TH1F("h_4lInvMass_44_4e","h_4lInvMass_44_e",100,115,80)));
    ANA_CHECK (book (TH1F("h_4lInvMass_44_4mu","h_4lInvMass_44_4mu",100,115,80)));
    ANA_CHECK (book (TH1F("h_4lInvMass_44_2e2mu","h_4lInvMass_44_2e2mu",100,115,80)));


    ANA_CHECK (book (TH1F("h_m4l_pt_44","h_m4l_pt_44",100,115,80)));
    ANA_CHECK (book (TH1F("h_m4l_pt_44_4e","h_m4l_pt_44_4e",100,115,80)));
    ANA_CHECK (book (TH1F("h_m4l_pt_44_4mu","h_m4l_pt_44_4mu",100,115,80)));
    ANA_CHECK (book (TH1F("h_m4l_pt_44_2e2mu","h_m4l_pt_44_2e2mu",100,115,80)));
    ANA_CHECK (book (TH1F("h_m4l_eta_44","h_m4l_eta_44",100,6,0)));
    ANA_CHECK (book (TH1F("h_m4l_phi_44","h_m4l_phi_44",100,-4,4)));
    ANA_CHECK (book (TH1F("h_m4l_eta_44_4e","h_m4l_eta_44_4e",100,6,0)));
    ANA_CHECK (book (TH1F("h_m4l_phi_44_4e","h_m4l_phi_44_4e",100,-4,4)));
    ANA_CHECK (book (TH1F("h_m4l_eta_44_4mu","h_m4l_eta_44_4mu",100,6,0)));
    ANA_CHECK (book (TH1F("h_m4l_phi_44_4mu","h_m4l_phi_44_4mu",100,-4,4)));
    ANA_CHECK (book (TH1F("h_m4l_eta_44_2e2mu","h_m4l_eta_44_2e2mu",100,6,0)));
    ANA_CHECK (book (TH1F("h_m4l_phi_44_2e2mu","h_m4l_phi_44_2e2mu",100,-4,4)));


    ANA_CHECK (book (TH1F("h_mll1InvMass_all","h_mll1InvMass_all",500,0.05,100.05)));
    ANA_CHECK (book (TH1F("h_mll1InvMass_44","h_mll1InvMass_44",500,0.05,100.05)));
    ANA_CHECK (book (TH1F("h_mll1InvMass_44_4e","h_mll1InvMass_44_4e",500,0.05,100.05)));
    ANA_CHECK (book (TH1F("h_mll1InvMass_44_4mu","h_mll1InvMass_44_4mu",500,0.05,100.05)));
    ANA_CHECK (book (TH1F("h_mll1InvMass_44_2e2mu","h_mll1InvMass_44_2e2mu",500,0.05,100.05)));
    ANA_CHECK (book (TH1F("h_mll1InvMass_2222","h_mll1InvMass_2222",500,0.05,100.05)));
    ANA_CHECK (book (TH1F("h_mll2InvMass_all","h_mll2InvMass_all",500,0.05,100.05)));
    ANA_CHECK (book (TH1F("h_mll2InvMass_44","h_mll2InvMass_44",500,0.05,100.05)));
    ANA_CHECK (book (TH1F("h_mll2InvMass_2222","h_mll2InvMass_2222",500,0.05,100.05)));
    ANA_CHECK (book (TH1F("h_higgs1InvMass_44","h_higgs1InvMass_44",50,0,500)));
    ANA_CHECK (book (TH1F("h_higgs1InvMass_2222","h_higgs1InvMass_2222",50,0,500)));
    ANA_CHECK (book (TH1F("h_higgs2InvMass_44","h_higgs2InvMass_44",50,0,500)));
    ANA_CHECK (book (TH1F("h_higgs2InvMass_2222","h_higgs2InvMass_2222",50,0,500)));


    ANA_CHECK (book (TH1F("h_higgs_pt_44","h_higgs_pt_44",50,0,500)));
    ANA_CHECK (book (TH1F("h_higgs_pt_2222","h_higgs_pt_2222",50,0,500)));
    ANA_CHECK (book (TH1F("h_zdark1_pt_2222","h_zdark1_pt_2222",50,0,500)));
    ANA_CHECK (book (TH1F("h_zdark2_pt_2222","h_zdark2_pt_2222",50,0,500)));
    ANA_CHECK (book (TH1F("h_zdark3_pt_2222","h_zdark3_pt_2222",50,0,500)));
    ANA_CHECK (book (TH1F("h_zdark4_pt_2222","h_zdark4_pt_2222",50,0,500)));

    ANA_CHECK (book (TH1F("h_mll1_pt","h_mll1_pt",50,0,500)));
    ANA_CHECK (book (TH1F("h_mll2_pt","h_mll2_pt",50,0,500)));
    ANA_CHECK (book (TH1F("h_mll1_eta","h_mll1_eta",120,-6,6)));
    ANA_CHECK (book (TH1F("h_mll2_eta","h_mll2_eta",120,-6,6)));
    ANA_CHECK (book (TH1F("h_mll1_phi","h_mll1_phi",100,-4,4)));
    ANA_CHECK (book (TH1F("h_mll2_phi","h_mll2_phi",100,-4,4)));

    ANA_CHECK (book (TH1F("h_mll1_pt_4e","h_mll1_pt_4e",50,0,500)));
    ANA_CHECK (book (TH1F("h_mll2_pt_4e","h_mll2_pt_4e",50,0,500)));
    ANA_CHECK (book (TH1F("h_mll1_eta_4e","h_mll1_eta_4e",120,-6,6)));
    ANA_CHECK (book (TH1F("h_mll2_eta_4e","h_mll2_eta_4e",120,-6,6)));
    ANA_CHECK (book (TH1F("h_mll1_phi_4e","h_mll1_phi_4e",100,-4,4)));
    ANA_CHECK (book (TH1F("h_mll2_phi_4e","h_mll2_phi_4e",100,-4,4)));

    ANA_CHECK (book (TH1F("h_mll1_pt_4mu","h_mll1_pt_4mu",50,0,500)));
    ANA_CHECK (book (TH1F("h_mll2_pt_4mu","h_mll2_pt_4mu",50,0,500)));
    ANA_CHECK (book (TH1F("h_mll1_eta_4mu","h_mll1_eta_4mu",120,-6,6)));
    ANA_CHECK (book (TH1F("h_mll2_eta_4mu","h_mll2_eta_4mu",120,-6,6)));
    ANA_CHECK (book (TH1F("h_mll1_phi_4mu","h_mll1_phi_4mu",100,-4,4)));
    ANA_CHECK (book (TH1F("h_mll2_phi_4mu","h_mll2_phi_4mu",100,-4,4)));

    ANA_CHECK (book (TH1F("h_mll1_pt_2e2mu","h_mll1_pt_2e2mu",50,0,500)));
    ANA_CHECK (book (TH1F("h_mll2_pt_2e2mu","h_mll2_pt_2e2mu",50,0,500)));
    ANA_CHECK (book (TH1F("h_mll1_eta_2e2mu","h_mll1_eta_2e2mu",120,-6,6)));
    ANA_CHECK (book (TH1F("h_mll2_eta_2e2mu","h_mll2_eta_2e2mu",120,-6,6)));
    ANA_CHECK (book (TH1F("h_mll1_phi_2e2mu","h_mll1_phi_2e2mu",100,-4,4)));
    ANA_CHECK (book (TH1F("h_mll2_phi_2e2mu","h_mll2_phi_2e2mu",100,-4,4)));

    ANA_CHECK (book (TH1F("h_zdark3_pt_44","h_zdark3_pt_44",50,0,500)));
    ANA_CHECK (book (TH1F("h_zdark4_pt_44","h_zdark4_pt_44",50,0,500)));

    ANA_CHECK (book (TH1F("h_totInvMass","h_totInvMass",100,0,1)));
    ANA_CHECK (book (TH1F("h_phi_44","h_phi_56",100,-4,4)));
    ANA_CHECK (book (TH1F("h_phi_2222","h_phi_78",100,-4,4)));


    // phi angle between leptons
    ANA_CHECK (book (TH1F("h_avg_phi_boosted_all","h_avg_phi_boosted_all",500,5,0)));
    ANA_CHECK (book (TH1F("h_delta_phi_boosted_all","h_delta_phi_boosted_all",500,5,0)));
    ANA_CHECK (book (TH1F("h_avg_phi_nonboosted_all","h_avg_phi_nonboosted_all",500,5,0)));
    ANA_CHECK (book (TH1F("h_delta_phi_nonboosted_all","h_delta_phi_nonboosted_all",500,5,0)));
    ANA_CHECK (book (TH1F("h_avg_phi_boosted_44","h_avg_phi_boosted_44",500,5,0)));
    ANA_CHECK (book (TH1F("h_delta_phi_boosted_44","h_delta_phi_boosted_44",500,5,0)));
    ANA_CHECK (book (TH1F("h_avg_phi_nonboosted_44","h_avg_phi_nonboosted_44",500,5,0)));
    ANA_CHECK (book (TH1F("h_delta_phi_nonboosted_44","h_delta_phi_nonboosted_44",500,5,0)));
    ANA_CHECK (book (TH1F("h_avg_phi_boosted_2222","h_avg_phi_boosted_2222",500,5,0)));
    ANA_CHECK (book (TH1F("h_delta_phi_boosted_2222","h_delta_phi_boosted_2222",500,5,0)));
    ANA_CHECK (book (TH1F("h_avg_phi_nonboosted_2222","h_avg_phi_nonboosted_2222",500,5,0)));
    ANA_CHECK (book (TH1F("h_delta_phi_nonboosted_2222","h_delta_phi_nonboosted_2222",500,5,0)));
    ANA_CHECK (book (TH1F("h_theta1_44","h_theta1_44",50,5,0)));
    ANA_CHECK (book (TH1F("h_theta2_44","h_theta2_44",50,5,0)));
    ANA_CHECK (book (TH1F("h_theta1_2222","h_theta1_2222",50,5,0)));
    ANA_CHECK (book (TH1F("h_theta2_2222","h_theta2_2222",50,5,0)));
    ANA_CHECK (book (TH1F("h_theta_diff_2222","h_theta_diff_2222",50,5,0)));
    ANA_CHECK (book (TH1F("h_theta_diff_44","h_theta_diff_44",50,5,0)));
    ANA_CHECK (book (TH2F("h_theta_diff_2D_44","h_theta_diff_2D_44",50,5,0,50,5,0)));
    ANA_CHECK (book (TH2F("h_theta_diff_2D_2222","h_theta_diff_2D_2222",50,5,0,50,5,0)));
    ANA_CHECK (book (TH1F("h_theta_star_44","h_theta_star_44",50,5,0)));
    ANA_CHECK (book (TH1F("h_theta_star_2222","h_theta_star_2222",50,5,0)));
    ANA_CHECK (book (TH1F("h_phi1_44","h_phi1_44",50,5,0)));
    ANA_CHECK (book (TH1F("h_phi1_2222","h_phi1_2222",50,5,0)));

    ANA_CHECK (book (TH1F("h_deltaR_56_44","h_deltaR_56_44",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_57_44","h_deltaR_57_44",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_58_44","h_deltaR_58_44",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_67_44","h_deltaR_67_44",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_68_44","h_deltaR_68_44",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_78_44","h_deltaR_78_44",50,0,10)));
    ANA_CHECK (book (TH1F("h_delta_Zd1_Zd2_44","h_delta_Zd1_Zd2_44",50,0,10)));


    ANA_CHECK (book (TH1F("h_deltaR_56_44_4e","h_deltaR_56_44_4e",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_57_44_4e","h_deltaR_57_44_4e",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_58_44_4e","h_deltaR_58_44_4e",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_67_44_4e","h_deltaR_67_44_4e",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_68_44_4e","h_deltaR_68_44_4e",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_78_44_4e","h_deltaR_78_44_4e",50,0,10)));

    ANA_CHECK (book (TH1F("h_deltaR_56_44_4m","h_deltaR_56_44_4m",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_57_44_4m","h_deltaR_57_44_4m",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_58_44_4m","h_deltaR_58_44_4m",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_67_44_4m","h_deltaR_67_44_4m",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_68_44_4m","h_deltaR_68_44_4m",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_78_44_4m","h_deltaR_78_44_4m",50,0,10)));




    ANA_CHECK (book (TH1F("h_deltaR_34_2222","h_deltaR_34_2222",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_37_2222","h_deltaR_37_2222",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_38_2222","h_deltaR_38_2222",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_47_2222","h_deltaR_47_2222",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_48_2222","h_deltaR_48_2222",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_78_2222","h_deltaR_78_2222",50,0,10)));
    ANA_CHECK (book (TH1F("h_delta_Zd1_Zd2_2222","h_delta_Zd1_Zd2_2222",50,0,10)));

    ANA_CHECK (book (TH1F("h_deltaR_34_2222_4e","h_deltaR_34_2222_4e",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_37_2222_4e","h_deltaR_37_2222_4e",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_38_2222_4e","h_deltaR_38_2222_4e",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_47_2222_4e","h_deltaR_47_2222_4e",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_48_2222_4e","h_deltaR_48_2222_4e",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_78_2222_4e","h_deltaR_78_2222_4e",50,0,10)));

    ANA_CHECK (book (TH1F("h_deltaR_34_2222_4m","h_deltaR_34_2222_4m",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_37_2222_4m","h_deltaR_37_2222_4m",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_38_2222_4m","h_deltaR_38_2222_4m",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_47_2222_4m","h_deltaR_47_2222_4m",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_48_2222_4m","h_deltaR_48_2222_4m",50,0,10)));
    ANA_CHECK (book (TH1F("h_deltaR_78_2222_4m","h_deltaR_78_2222_4m",50,0,10)));


    ANA_CHECK (book (TH1F("h_sum_charge_12","h_sum_charge_12",50,0,10)));
    ANA_CHECK (book (TH1F("h_sum_charge_34","h_sum_charge_34",50,0,10)));

    ANA_CHECK (book (TH1F("h_lep_unstable_e","h_lep1_unstable_e",100,0,1000)));
    ANA_CHECK (book (TH1F("h_lep_unstable_pt","h_lep1_unstable_pt",50,0,500)));
    ANA_CHECK (book (TH1F("h_lep_unstable_photon_e","h_lep1_unstable_photon_e",30,0,300)));
    ANA_CHECK (book (TH1F("h_lep_unstable_pt_sum","h_lep1_unstable_pt_sum",100,0,1000)));

    ANA_CHECK (book (TH1F("h_MET_peak_distribution","h_MET_peak_distribution",150,0,300)));
    ANA_CHECK (book (TH1F("h_missingET_normalized_44","h_missingET_normalized_44",50,0,1)));
    ANA_CHECK (book (TH1F("h_mS_truth","h_mS_truth",125,50,200)));
    ANA_CHECK (book (TH1F("h_mH_truth","h_mH_truth",125,50,200)));
    ANA_CHECK (book (TH1F("h_MET_peak_event_by_event","h_MET_peak_event_by_event",500,0,100)));





    return StatusCode::SUCCESS;
}



StatusCode MyxAODAnalysis :: execute ()
{
    // Here you do everything that needs to be done on every single
    // events, e.g. read input variables, apply cuts, and fill
    // histograms and trees.  This is where most of your actual analysis
    // code will go.

    //event processed


    leptons=0;
    // retrieve the eventInfo object from the event store
    const xAOD::EventInfo *eventInfo = nullptr;
    ANA_CHECK (evtStore()->retrieve (eventInfo, "EventInfo"));
//    uint64_t m_runNumber = eventInfo->runNumber();
//    uint64_t m_eventNumber = eventInfo->eventNumber;


    const xAOD::TruthParticleContainer* truthContainer = nullptr;
    ANA_CHECK (evtStore()->retrieve (truthContainer, "TruthParticles"));

    xAOD::TruthParticleContainer::const_iterator truth_itr = truthContainer->begin();
    xAOD::TruthParticleContainer::const_iterator truth_end = truthContainer->end();



    std::vector<int> *knownPart = new std::vector<int>;

    const xAOD::TruthParticle* DG_1 = nullptr;
    const xAOD::TruthParticle* DG_2 = nullptr;

    int truth_count = 0;
    int count = 0;
    // Loop over TruthParticle
//    leptons = 0;
    for( ; truth_itr != truth_end ; ++truth_itr){
        const xAOD::TruthParticle* truth = *truth_itr;

        leptons=0;
        bool lep1_vis = false;
        bool lep2_vis = false;
        bool lep3_vis = false;
        bool lep4_vis = false;
        bool lep5_vis = false;
        bool lep6_vis = false;
        bool lep7_vis = false;
        bool lep8_vis = false;
        float phi_zd1, phi_zd2, phi_zd1_nonboosted, phi_zd2_nonboosted;
        if(truth->pdgId()==25){

            if(truth->hasDecayVtx()){

                const xAOD::TruthVertex *decayVtx = truth->decayVtx();
                if(decayVtx->nOutgoingParticles()==2){
                    const xAOD::TruthParticle *progenitor = truth;
                    const xAOD::TruthParticle *additional_scalar1 = decayVtx->outgoingParticle(0);
                    const xAOD::TruthParticle *additional_scalar2 = decayVtx->outgoingParticle(1);

                    if((additional_scalar1->pdgId()==35) && (additional_scalar2->pdgId()==35)){
                        if(additional_scalar1->hasDecayVtx() && additional_scalar2->hasDecayVtx()){
                            const xAOD::TruthVertex *g_decayVtx_1 = additional_scalar1->decayVtx();
                            const xAOD::TruthVertex *g_decayVtx_2 = additional_scalar2->decayVtx();
                            const xAOD::TruthParticle *z_dark1 = g_decayVtx_1->outgoingParticle(0);
                            const xAOD::TruthParticle *z_dark2 = g_decayVtx_1->outgoingParticle(1);
                            const xAOD::TruthParticle *z_dark3 = g_decayVtx_2->outgoingParticle(0);
                            const xAOD::TruthParticle *z_dark4 = g_decayVtx_2->outgoingParticle(1);


                            if(z_dark1->hasDecayVtx() && z_dark2->hasDecayVtx() && z_dark3->hasDecayVtx() && z_dark4->hasDecayVtx()){
                                const xAOD::TruthVertex *lep_decayVtx_1 = z_dark1->decayVtx();
                                const xAOD::TruthVertex *lep_decayVtx_2 = z_dark2->decayVtx();
                                const xAOD::TruthVertex *lep_decayVtx_3 = z_dark3->decayVtx();
                                const xAOD::TruthVertex *lep_decayVtx_4 = z_dark4->decayVtx();
                                const xAOD::TruthParticle *lep1 = lep_decayVtx_1->outgoingParticle(0);
                                const xAOD::TruthParticle *lep2 = lep_decayVtx_1->outgoingParticle(1);
                                const xAOD::TruthParticle *lep3 = lep_decayVtx_2->outgoingParticle(0);
                                const xAOD::TruthParticle *lep4 = lep_decayVtx_2->outgoingParticle(1);
                                const xAOD::TruthParticle *lep5 = lep_decayVtx_3->outgoingParticle(0);
                                const xAOD::TruthParticle *lep6 = lep_decayVtx_3->outgoingParticle(1);
                                const xAOD::TruthParticle *lep7 = lep_decayVtx_4->outgoingParticle(0);
                                const xAOD::TruthParticle *lep8 = lep_decayVtx_4->outgoingParticle(1);


                                if(lep1->status()==1 && lep2->status()==1 && lep3->status()==1 && lep4->status()==1
                                && lep5->status()==1 && lep6->status()==1 && lep7->status()==1 && lep8->status()==1)
                                {
                                    lep_stat++;
                                }
                                if(lep1->absPdgId()==11 || lep1->absPdgId()==13){
                                    leptons++;
                                    ANA_MSG_INFO ("lep1 pdgid "<<lep1->absPdgId()<<" lep1 barcode "<<lep1->barcode());
//                                    barcode_file << "lep1 pdgid "<<lep1->absPdgId()<<" lep1 barcode "<<lep1->barcode()<<std::endl;
                                    lep_rapidity[0] = lep1->rapidity();
                                    eta_truth[0] = lep1->eta();
                                    phi_truth[0] = lep1->phi();
                                    pt_truth[0] = lep1->pt();
                                    lep_barcode[0] = lep1->barcode();
                                    lep_stability[0] = lep1->status();

                                    lep1_vis = true;
                                }
                                if(lep2->absPdgId()==11 || lep2->absPdgId()==13){
                                    leptons++;
                                    lep_rapidity[1] = lep2->rapidity();
                                    eta_truth[1] = lep2->eta();
                                    phi_truth[1] = lep2->phi();
                                    pt_truth[1] = lep2->pt();
                                    lep_barcode[1] = lep2->barcode();
                                    lep_stability[1] = lep2->status();
                                    lep2_vis = true;
                                }
                                if(lep3->absPdgId()==11 || lep3->absPdgId()==13){
                                    leptons++;
                                    lep_rapidity[2] = lep3->rapidity();
                                    eta_truth[2] = lep3->eta();
                                    phi_truth[2] = lep3->phi();
                                    pt_truth[2] = lep3->pt();
                                    lep_barcode[2] = lep3->barcode();
                                    lep_stability[2] = lep3->status();
                                    lep3_vis = true;
                                }
                                if(lep4->absPdgId()==11 || lep4->absPdgId()==13){
                                    leptons++;
                                    lep_rapidity[3] = lep4->rapidity();
                                    eta_truth[3] = lep4->eta();
                                    phi_truth[3] = lep4->phi();
                                    lep_barcode[3] = lep4->barcode();
                                    pt_truth[3] = lep4->pt();
                                    lep_stability[3] = lep4->status();
                                    lep4_vis = true;
                                }
                                if(lep5->absPdgId()==11 || lep5->absPdgId()==13){
                                    leptons++;
                                    lep_rapidity[4] = lep5->rapidity();
                                    eta_truth[4] = lep5->eta();
                                    phi_truth[4] = lep5->phi();
                                    pt_truth[4] = lep5->pt();
                                    lep_barcode[4] = lep5->barcode();
                                    lep_stability[4] = lep5->status();
                                    lep5_vis = true;
                                }
                                if(lep6->absPdgId()==11 || lep6->absPdgId()==13){
                                    leptons++;
                                    lep_rapidity[5] = lep6->rapidity();
                                    eta_truth[5] = lep6->eta();
                                    phi_truth[5] = lep6->phi();
                                    lep_barcode[5] = lep6->barcode();
                                    pt_truth[5] = lep6->pt();
                                    lep_stability[5] = lep6->status();
                                    lep6_vis = true;
                                }
                                if(lep7->absPdgId()==11 || lep7->absPdgId()==13){
                                    leptons++;
                                    lep_rapidity[6] = lep7->rapidity();
                                    eta_truth[6] = lep7->eta();
                                    phi_truth[6] = lep7->phi();
                                    lep_barcode[6] = lep7->barcode();
                                    pt_truth[6] = lep7->pt();
                                    lep_stability[6] = lep7->status();
                                    lep7_vis = true;
                                }
                                if(lep8->absPdgId()==11 || lep8->absPdgId()==13){
                                    leptons++;
                                     lep_rapidity[7] = lep8->rapidity();
                                    eta_truth[7] = lep8->eta();
                                    phi_truth[7] = lep8->phi();
                                    lep_barcode[7] = lep8->barcode();
                                    pt_truth[7] = lep8->pt();
                                    lep_stability[7] = lep8->status();
                                    lep8_vis = true;
                                }
//                                if(lep1->absPdgId()==11){
//                                    lep_rapidity = lep1->rapidity();
//                                    ATH_MSG_INFO( "Rapidity of electron corresponding to lepton 1 " << lep1->rapidity() );
//                                }



                                ANA_MSG_INFO ("lep1 "<< " "<< lep1_vis<< " "<<"lep2 "<< " "<< lep2_vis<< " "<<"lep3 "<< " "<< lep3_vis<<" "<< "lep4 "<< " "<< lep4_vis);
                                ANA_MSG_INFO ("lep5 "<< " "<< lep5_vis<< " "<<"lep6 "<< " "<< lep6_vis<< " "<<"lep7 "<< " "<< lep7_vis<<" "<< "lep8 "<< " "<< lep8_vis);
                                int bitmask = pow(2,3)*lep1_vis + pow(2,2)*lep3_vis + pow(2,1)*lep5_vis + pow(2,0)*lep7_vis;

//                              BBGG this one is correct
//           			        0011 = 3; 1100 = 12
                                TLorentzVector llll_44,ll_1_44,ll_2_44;
                                const xAOD::MissingETContainer* truth_MET = nullptr;
                                ANA_CHECK (evtStore()->retrieve (truth_MET, "MET_Truth"));
                                const xAOD::MissingET* truthMET_NonInt = nullptr;
                                truthMET_NonInt = (*truth_MET)["NonInt"];

                                TLorentzVector met_TLV;
                                float Etmiss_Etx = truthMET_NonInt->mpx();
                                float Etmiss_Ety = truthMET_NonInt->mpy();
                                float Etmiss_Et  = sqrt(Etmiss_Etx * Etmiss_Etx + Etmiss_Ety * Etmiss_Ety);
                                bool status_h1_44 = lep1->status()==1 && lep2->status()==1 && lep3->status()==1 && lep4->status()==1;
                                bool status_h2_44 = lep5->status()==1 && lep6->status()==1 && lep7->status()==1 && lep8->status()==1;
                                bool status_h3_2222 = lep3->status()==1 && lep4->status()==1 && lep7->status()==1 && lep8->status()==1;
                                met_TLV.SetPxPyPzE(Etmiss_Etx, Etmiss_Ety, 0., Etmiss_Et);
//                                if(status_h1_44 || status_h2_44 ) {
//                                ANA_MSG_INFO("lepton1 "<<lep1->pdgId()<<" lepton2 "<<lep2->pdgId()<<" lepton3 "<<lep3->pdgId()<<" lepton4 "<<lep4->pdgId());
//                                ANA_MSG_INFO("lepton5 "<<lep5->pdgId()<<" lepton6 "<<lep6->pdgId()<<" lepton7 "<<lep7->pdgId()<<" lepton8 "<<lep8->pdgId());

                                    if (bitmask == 3 || bitmask == 12) {
//                                        ANA_MSG_INFO("EVENT NUMBER "<< " "<< eventInfo->eventNumber());
//                                        ANA_MSG_INFO("RUN NUMBER "<< " "<< eventInfo->runNumber());
                                        events_44++;
                                        n_events++;
                                        event_44 = true;
//                                        ANA_MSG_INFO("Bitmask value" << bitmask);
                                        double progenitor_mass = progenitor->m();
                                        ANA_MSG_INFO("the truth mass  " << " " << progenitor_mass);
                                        double additional_scalar1_pt = additional_scalar1->pt();
                                        double additional_scalar2_pt = additional_scalar2->pt();
                                        double additional_scalar1_mass = additional_scalar1->m();
                                        double additional_scalar2_mass = additional_scalar2->m();

                                        hist("h_mS_truth")->Fill(additional_scalar2_mass / 1000);
                                        hist("h_mH_truth")->Fill(progenitor_mass / 1000);

                                        double met_peak = TMath::Sqrt((progenitor_mass*progenitor_mass)/4 - additional_scalar1_mass*additional_scalar1_mass);
                                        double met_benchmark = TMath::Sqrt((300*300)/4 - 110*110);
                                        double met_peak_event_by_event = met_benchmark/truthMET_NonInt->met();
//                                        ANA_MSG_INFO("The event peak event by event "<<met_peak_event_by_event);

                                        hist("h_MET_peak_distribution")->Fill(met_peak / 1000);
                                        hist("h_MET_peak_event_by_event")->Fill(met_peak_event_by_event*1000);

//                                        hist("h_higgs_pt_44")->Fill(met_peak / 1000);

                                        double zdark1_pt = z_dark1->pt();
                                        double zdark2_pt = z_dark2->pt();
                                        double zdark3_pt = z_dark3->pt();
                                        double zdark4_pt = z_dark4->pt();
//                                    hist("h_zdark1_pt_44")->Fill(zdark1_pt/1000);
//                                    hist("h_zdark2_pt_44")->Fill(zdark2_pt/1000);
                                        hist("h_zdark3_pt_44")->Fill(zdark3_pt / 1000);
                                        hist("h_zdark4_pt_44")->Fill(zdark4_pt / 1000);


//				bitmask == 12 does not exist because of the way the generator works, neutrinos are always named in the 8 leptons
//                                    std::cout << "have a quadruplet BBGG" << std::endl;
                                        double energy_4l = lep5->e() + lep6->e() + lep7->e() + lep8->e();
                                        double energy_ll1 = lep5->e() + lep6->e();
                                        double energy_ll2 = lep7->e() + lep8->e();
                                        double px_4l = lep5->px() + lep6->px() + lep7->px() + lep8->px();
                                        double py_4l = lep5->py() + lep6->py() + lep7->py() + lep8->py();
                                        double pz_4l = lep5->pz() + lep6->pz() + lep7->pz() + lep8->pz();
                                        double e_4l = lep5->e() + lep6->e() + lep7->e() + lep8->e();
                                        double px_ll1 = lep5->px() + lep6->px();
                                        double py_ll1 = lep5->py() + lep6->py();
                                        double pz_ll1 = lep5->pz() + lep6->pz();
                                        double px_ll2 = lep7->px() + lep8->px();
                                        double py_ll2 = lep7->py() + lep8->py();
                                        double pz_ll2 = lep7->pz() + lep8->pz();



                                        double pt1 = lep1->pt();
                                        double pt2 = lep2->pt();
                                        double pt3 = lep3->pt();
                                        double pt4 = lep4->pt();
                                        double pt5 = lep5->pt();
                                        double pt6 = lep6->pt();
                                        double pt7 = lep7->pt();
                                        double pt8 = lep8->pt();

                                        llll_44.SetPxPyPzE(px_4l, py_4l, pz_4l, e_4l);
                                        ll_1_44.SetPxPyPzE(px_ll1, py_ll1, pz_ll1, energy_ll1);
                                        ll_2_44.SetPxPyPzE(px_ll2, py_ll2, pz_ll2, energy_ll2);
                                        // Doing calculations for delta R
                                        double delta_eta56_44 = lep5->eta() - lep6->eta();
                                        double delta_eta57_44 = lep5->eta() - lep7->eta();
                                        double delta_eta58_44 = lep5->eta() - lep8->eta();
                                        double delta_eta67_44 = lep6->eta() - lep7->eta();
                                        double delta_eta68_44 = lep6->eta() - lep8->eta();
                                        double delta_eta78_44 = lep7->eta() - lep8->eta();
                                        double delta_eta_Zd1_Zd2_44 = ll_1_44.Eta() - ll_2_44.Eta();


                                        double delta_phi56_44 = lep5->phi() - lep6->phi();
                                        double delta_phi57_44 = lep5->phi() - lep7->phi();
                                        double delta_phi58_44 = lep5->phi() - lep8->phi();
                                        double delta_phi67_44 = lep6->phi() - lep7->phi();
                                        double delta_phi68_44 = lep6->phi() - lep8->phi();
                                        double delta_phi78_44 = lep7->phi() - lep8->phi();
                                        double delta_phi_Zd1_Zd2_44 = ll_1_44.Phi() - ll_2_44.Phi();

                                        double delta_R56_44 = TMath::Sqrt(
                                                delta_eta56_44 * delta_eta56_44 + delta_phi56_44 * delta_phi56_44);
                                        double delta_R57_44 = TMath::Sqrt(
                                                delta_eta57_44 * delta_eta57_44 + delta_phi57_44 * delta_phi57_44);
                                        double delta_R58_44 = TMath::Sqrt(
                                                delta_eta58_44 * delta_eta58_44 + delta_phi58_44 * delta_phi58_44);
                                        double delta_R67_44 = TMath::Sqrt(
                                                delta_eta67_44 * delta_eta67_44 + delta_phi67_44 * delta_phi67_44);
                                        double delta_R68_44 = TMath::Sqrt(
                                                delta_eta68_44 * delta_eta68_44 + delta_phi68_44 * delta_phi68_44);
                                        double delta_R78_44 = TMath::Sqrt(
                                                delta_eta78_44 * delta_eta78_44 + delta_phi78_44 * delta_phi78_44);
                                        double delta_Zd1_Zd2_44 = TMath::Sqrt(
                                                delta_eta_Zd1_Zd2_44 * delta_eta_Zd1_Zd2_44 + delta_phi_Zd1_Zd2_44 * delta_phi_Zd1_Zd2_44);

                                        // Get 4m case
                                        if (lep1->absPdgId() == 13 && lep2->absPdgId() == 13 && lep3->absPdgId() == 13 && lep8->absPdgId() == 13 ){
                                            hist("h_deltaR_56_44_4m")->Fill(delta_R56_44);
                                            hist("h_deltaR_57_44_4m")->Fill(delta_R57_44);
                                            hist("h_deltaR_58_44_4m")->Fill(delta_R58_44);
                                            hist("h_deltaR_67_44_4m")->Fill(delta_R67_44);
                                            hist("h_deltaR_68_44_4m")->Fill(delta_R68_44);
                                            hist("h_deltaR_78_44_4m")->Fill(delta_R78_44);

                                        }
                                        // Get 4e case
                                        if (lep1->absPdgId() == 11 && lep2->absPdgId() == 11 && lep3->absPdgId() == 11 && lep8->absPdgId() == 11 ){
                                            hist("h_deltaR_56_44_4e")->Fill(delta_R56_44);
                                            hist("h_deltaR_57_44_4e")->Fill(delta_R57_44);
                                            hist("h_deltaR_58_44_4e")->Fill(delta_R58_44);
                                            hist("h_deltaR_67_44_4e")->Fill(delta_R67_44);
                                            hist("h_deltaR_68_44_4e")->Fill(delta_R68_44);
                                            hist("h_deltaR_78_44_4e")->Fill(delta_R78_44);

                                        }

                                        hist("h_deltaR_56_44")->Fill(delta_R56_44);
                                        hist("h_deltaR_57_44")->Fill(delta_R57_44);
                                        hist("h_deltaR_58_44")->Fill(delta_R58_44);
                                        hist("h_deltaR_67_44")->Fill(delta_R67_44);
                                        hist("h_deltaR_68_44")->Fill(delta_R68_44);
                                        hist("h_deltaR_78_44")->Fill(delta_R78_44);
                                        hist("h_delta_Zd1_Zd2_44")->Fill(delta_Zd1_Zd2_44);


//                                        ANA_MSG_INFO("the delta R: " << " " << delta_R56_44);

                                        // Calculating the quadruplet and dilepton mass using the mass energy equivalence equation
                                        double m4lInvMass = TMath::Sqrt(energy_4l * energy_4l -
                                                                        (px_4l * px_4l + py_4l * py_4l +
                                                                         pz_4l * pz_4l));
                                        double mll1InvMass = TMath::Sqrt(energy_ll1 * energy_ll1 -
                                                                         (px_ll1 * px_ll1 + py_ll1 * py_ll1 +
                                                                          pz_ll1 * pz_ll1));
                                        double mll2InvMass = TMath::Sqrt(energy_ll2 * energy_ll2 -
                                                                         (px_ll2 * px_ll2 + py_ll2 * py_ll2 +
                                                                          pz_ll2 * pz_ll2));



//                                  Missing ET calculations

                                        double met_higgs_44_angle = met_TLV.Angle(llll_44.Vect());
                                        double met_zd1_44_angle = met_TLV.Angle(ll_1_44.Vect());
                                        double met_zd2_44_angle = met_TLV.Angle(ll_2_44.Vect());
                                        double m4l_44_phi_angle = llll_44.Phi();
                                        double mll1_44_phi_angle = ll_1_44.Phi();
                                        double mll2_44_phi_angle = ll_2_44.Phi();
                                        double m4l_44_Eta = llll_44.Eta();
                                        double mll1_44_Eta = ll_1_44.Eta();
                                        double mll2_44_Eta = ll_2_44.Eta();
                                        double m4l_e,m4l_mu;
                                        double m4l_44_Eta_e,m4l_44_Eta_mu;
                                        double m4l_44_phi_angle_e,m4l_44_phi_angle_mu;
                                        double m4l_2e2mu;
                                        double m4l_44_Eta_2e2mu;
                                        double m4l_44_phi_angle_2e2mu;
                                        // get eta/phi for 4mu
                                        if (lep1->absPdgId() == 13 && lep2->absPdgId() == 13 && lep3->absPdgId() == 13 && lep4->absPdgId() == 13 ) {
                                            m4l_44_Eta_mu = llll_44.Eta();
                                            m4l_44_phi_angle_mu = llll_44.Phi();
                                            m4l_mu = llll_44.M();
                                            hist("h_4lInvMass_44_4mu")->Fill(m4l_mu / 1000);
                                            hist("h_m4l_eta_44_4mu")->Fill(m4l_44_Eta_mu / 1000);
                                            hist("h_mll1_pt_4mu")->Fill(ll_1_44.Pt() / 1000);
                                            hist("h_mll2_pt_4mu")->Fill(ll_2_44.Pt() / 1000);
                                            hist("h_mll1_eta_4mu")->Fill(ll_1_44.Eta());
                                            hist("h_mll2_eta_4mu")->Fill(ll_2_44.Eta());
                                            hist("h_mll1_phi_4mu")->Fill(ll_1_44.Phi());
                                            hist("h_mll2_phi_4mu")->Fill(ll_2_44.Phi());
                                            hist("h_m4l_pt_44_4mu")->Fill(llll_44.Pt() / 1000);
                                            hist("h_m4l_eta_44_4mu")->Fill(llll_44.Eta());
                                            hist("h_m4l_phi_44_4mu")->Fill(llll_44.Phi());
                                        }

                                        // get eta/phi for 4e
                                        if (lep1->absPdgId() == 11 && lep2->absPdgId() == 11 && lep3->absPdgId() == 11 && lep4->absPdgId() == 11 ) {
                                             m4l_44_Eta_e = llll_44.Eta();
                                             m4l_44_phi_angle_e = llll_44.Phi();
                                             m4l_e = llll_44.M();
                                             hist("h_4lInvMass_44_4e")->Fill(m4l_e / 1000);
                                            hist("h_mll1_pt_4e")->Fill(ll_1_44.Pt() / 1000);
                                            hist("h_mll2_pt_4e")->Fill(ll_2_44.Pt() / 1000);
                                            hist("h_mll1_eta_4e")->Fill(ll_1_44.Eta());
                                            hist("h_mll2_eta_4e")->Fill(ll_2_44.Eta());
                                            hist("h_mll1_phi_4e")->Fill(ll_1_44.Phi());
                                            hist("h_mll2_phi_4e")->Fill(ll_2_44.Phi());
                                            hist("h_m4l_pt_44_4e")->Fill(llll_44.Pt() / 1000);
                                            hist("h_m4l_eta_44_4e")->Fill(llll_44.Eta());
                                            hist("h_m4l_phi_44_4e")->Fill(llll_44.Phi());
                                        }

                                        if (lep1->absPdgId() == 11 && lep2->absPdgId() == 11 && lep3->absPdgId() == 13 && lep4->absPdgId() == 13 ) {
                                            m4l_44_Eta_2e2mu = llll_44.Eta();
                                            m4l_44_phi_angle_2e2mu = llll_44.Phi();
                                            m4l_2e2mu = llll_44.M();
                                            hist("h_4lInvMass_44_2e2mu")->Fill(m4l_2e2mu / 1000);
                                            hist("h_mll1_pt_2e2mu")->Fill(ll_1_44.Pt() / 1000);
                                            hist("h_mll2_pt_2e2mu")->Fill(ll_2_44.Pt() / 1000);
                                            hist("h_mll1_eta_2e2mu")->Fill(ll_1_44.Eta());
                                            hist("h_mll2_eta_2e2mu")->Fill(ll_2_44.Eta());
                                            hist("h_mll1_phi_2e2mu")->Fill(ll_1_44.Phi());
                                            hist("h_mll2_phi_2e2mu")->Fill(ll_2_44.Phi());
                                            hist("h_m4l_pt_44_2e2mu")->Fill(llll_44.Pt() / 1000);
                                            hist("h_m4l_eta_44_2e2mu")->Fill(llll_44.Eta());
                                            hist("h_m4l_phi_44_2e2mu")->Fill(llll_44.Phi());

                                        }


                                        // add the sum of the charges
                                        double sum_charge_12 = lep1->charge() + lep2->charge();
                                        double sum_charge_34 = lep3->charge() + lep4->charge();
                                        hist("h_sum_charge_12")->Fill(sum_charge_12);
                                        hist("h_sum_charge_34")->Fill(sum_charge_34);

                                        double met_phi_angle = truthMET_NonInt->phi();

                                        double deltaPhi_m4lMet = abs(m4l_44_phi_angle - met_phi_angle);
                                        double deltaPhi_mll1Met = abs(mll1_44_phi_angle - met_phi_angle);
                                        double deltaPhi_mll2Met = abs(mll2_44_phi_angle - met_phi_angle);

                                        hist("h_missingET_higgs_phi_angle_44")->Fill(deltaPhi_m4lMet);
                                        hist("h_missingET_dilep1_phi_angle_44")->Fill(deltaPhi_mll1Met);
                                        hist("h_missingET_dilep2_phi_angle_44")->Fill(deltaPhi_mll2Met);
                                        hist("h_missingET_higgs_angle_44")->Fill(met_higgs_44_angle);
                                        hist("h_missingET_dilep1_angle_44")->Fill(met_zd1_44_angle);
                                        hist("h_missingET_dilep2_angle_44")->Fill(met_zd1_44_angle);
                                        hist("h_missingET_44")->Fill(truthMET_NonInt->met() / 1000);
                                        hist("h_missingET_normalized_44")->Fill(truthMET_NonInt->met() /(met_peak_event_by_event));

                                        ANA_MSG_INFO("the angle: " << " " << met_higgs_44_angle);

                                        // kinematics for the lepton system in the 44 case
                                        hist("h_4lInvMass_44")->Fill(llll_44.M() / 1000);\
                                        hist("h_m4l_pt_44")->Fill(llll_44.Pt() / 1000);
                                        hist("h_m4l_eta_44")->Fill(llll_44.Eta());
                                        hist("h_m4l_phi_44")->Fill(llll_44.Phi());





                                        hist("h_mll1InvMass_44")->Fill(ll_1_44.M() / 1000);
                                        ANA_MSG_INFO("here is the dilepton mass: " << " " << ll_1_44.M() / 1000);

                                        hist("h_mll1InvMass_all")->Fill(ll_1_44.M() / 1000);
                                        hist("h_mll2InvMass_44")->Fill(ll_1_44.M() / 1000);
                                        ANA_MSG_INFO("dilepton mass" << ll_2_44.M() / 1000);

                                        hist("h_mll2InvMass_all")->Fill(ll_2_44.M() / 1000);
                                        hist("h_mll1_pt")->Fill(ll_1_44.Pt() / 1000);
                                        hist("h_mll2_pt")->Fill(ll_2_44.Pt() / 1000);
                                        hist("h_mll1_eta")->Fill(ll_1_44.Eta());
                                        hist("h_mll2_eta")->Fill(ll_2_44.Eta());
                                        hist("h_mll1_phi")->Fill(ll_1_44.Phi());
                                        hist("h_mll2_phi")->Fill(ll_2_44.Phi());


                                        TLorentzVector S_p, S_p_boosted;
                                        float S_pz, S_py, S_px, S_e;
                                        S_px = lep5->px() + lep6->px() + lep7->px() + lep8->px();
                                        S_py = lep5->py() + lep6->py() + lep7->py() + lep8->py();
                                        S_pz = lep5->pz() + lep6->pz() + lep7->pz() + lep8->pz();
                                        S_e = lep5->e() + lep6->e() + lep7->e() + lep8->e();

                                        S_p.SetPxPyPzE(S_px, S_py, S_pz, S_e);
                                        //Get boost from Higgs
                                        TVector3 S2_boostVector;
                                        S2_boostVector = S_p.BoostVector();
//                                    ANA_MSG_INFO ("Higgs boost vector (X) is "<< higgs_boostVector.X());
                                        S_p_boosted = S_p;
                                        S_p_boosted.Boost(-S2_boostVector);
                                        ANA_MSG_INFO("the boosted vector: " << " " << S_p_boosted.Px() << " "
                                                                            << S_p_boosted.Py() << " "
                                                                            << S_p_boosted.Pz());
                                        TLorentzVector l5_p, l6_p, l7_p, l8_p, l5_p_boosted, l6_p_boosted, l7_p_boosted, l8_p_boosted;
                                        TLorentzVector z3_p, z4_p, z3_p_boosted, z4_p_boosted;

                                        TVector3 lep5_vec3_boosted, lep6_vec3_boosted, lep7_vec3_boosted, lep8_vec3_boosted;
                                        TVector3 z3_vec3_boosted, z4_vec3_boosted;

                                        l5_p.SetPxPyPzE(lep5->px(), lep5->py(), lep5->pz(), lep5->e());
                                        l6_p.SetPxPyPzE(lep6->px(), lep6->py(), lep6->pz(), lep6->e());
                                        l7_p.SetPxPyPzE(lep7->px(), lep7->py(), lep7->pz(), lep7->e());
                                        l8_p.SetPxPyPzE(lep8->px(), lep8->py(), lep8->pz(), lep8->e());

                                        z3_p.SetPxPyPzE(z_dark3->px(), z_dark3->py(), z_dark3->pz(), z_dark3->e());
                                        z4_p.SetPxPyPzE(z_dark4->px(), z_dark4->py(), z_dark4->pz(), z_dark4->e());


                                        TVector3 zDarkVect1, zDarkVect2, zDarkVect3, zDarkVect4, z_axis_not_boosted_44;
                                        zDarkVect1.SetXYZ(z_dark1->px(), z_dark1->py(), z_dark1->pz());
                                        zDarkVect2.SetXYZ(z_dark2->px(), z_dark2->py(), z_dark2->pz());
                                        zDarkVect3.SetXYZ(z_dark3->px(), z_dark3->py(), z_dark3->pz());
                                        zDarkVect4.SetXYZ(z_dark4->px(), z_dark4->py(), z_dark4->pz());


                                        l5_p_boosted = l5_p;
                                        l6_p_boosted = l6_p;
                                        l7_p_boosted = l7_p;
                                        l8_p_boosted = l8_p;

                                        z3_p_boosted = z3_p;
                                        z4_p_boosted = z4_p;


                                        l5_p_boosted.Boost(-S2_boostVector);
                                        l6_p_boosted.Boost(-S2_boostVector);
                                        l7_p_boosted.Boost(-S2_boostVector);
                                        l8_p_boosted.Boost(-S2_boostVector);

                                        z3_p_boosted.Boost(-S2_boostVector);
                                        z4_p_boosted.Boost(-S2_boostVector);
//                                    ANA_MSG_INFO ("the boosted boson vector: "<< " "<<z3_p_boosted.Px()<<" "<<z3_p_boosted.Py()<<" "<<z3_p_boosted.Pz());




                                        lep5_vec3_boosted.SetXYZ(l5_p_boosted.Px(), l5_p_boosted.Py(),
                                                                 l5_p_boosted.Pz());
                                        lep6_vec3_boosted.SetXYZ(l6_p_boosted.Px(), l6_p_boosted.Py(),
                                                                 l6_p_boosted.Pz());
                                        lep7_vec3_boosted.SetXYZ(l7_p_boosted.Px(), l7_p_boosted.Py(),
                                                                 l7_p_boosted.Pz());
                                        lep8_vec3_boosted.SetXYZ(l8_p_boosted.Px(), l8_p_boosted.Py(),
                                                                 l8_p_boosted.Pz());

                                        z3_vec3_boosted.SetXYZ(z3_p_boosted.Px(), z3_p_boosted.Py(), z3_p_boosted.Pz());
                                        z4_vec3_boosted.SetXYZ(z4_p_boosted.Px(), z4_p_boosted.Py(), z4_p_boosted.Pz());

                                        z_axis_not_boosted_44.SetXYZ(0, 0, 1);


                                        double theta1_44, theta2_44, theta_star_44;
                                        theta_star_44 = z3_vec3_boosted.Angle(z_axis_not_boosted_44);
                                        hist("h_theta_star_44")->Fill(theta_star_44);

                                        // lepton 5 is always positive charge. therefore we use lepton 6 for the BBGG case
                                        if (lep6->charge() < 0) {
                                            theta1_44 = z3_vec3_boosted.Angle(lep6_vec3_boosted);
                                            ANA_MSG_INFO("theta1 44: " << " " << theta1_44);
                                            hist("h_theta1_44")->Fill(theta1_44);

                                        }

                                        if (lep8->charge() < 0) {
                                            theta2_44 = z4_vec3_boosted.Angle(lep8_vec3_boosted);
                                            ANA_MSG_INFO("theta2 44: " << " " << theta2_44);
                                            hist("h_theta2_44")->Fill(theta2_44);

                                        }
                                        double theta_diff_44 = abs(theta1_44 - theta2_44);
                                        hist("h_theta_diff_44")->Fill(theta_diff_44);
                                        hist("h_theta_diff_2D_44")->Fill(theta1_44, theta2_44);

                                        TVector3 perp56 = lep5_vec3_boosted.Cross(lep6_vec3_boosted);
                                        TVector3 perp78 = lep7_vec3_boosted.Cross(lep8_vec3_boosted);
                                        TVector3 perp_z_44 = z3_vec3_boosted.Cross(z_axis_not_boosted_44);


                                        double phi = perp56.Angle(perp78);
//                                    double scalar_product = perp56.Dot(perp78);
//                                    double magnitude = perp56.Mag()*perp78.Mag();
//                                    double cosine = scalar_product/magnitude;
//                                    double phi = TMath::ACos(scalar_product/magnitude);
                                        hist("h_phi_44")->Fill(phi);

                                        double phi1 = perp56.Angle(perp_z_44);
//                                    double scalar_product_phi1 = perp56.Dot(perp_z_44);
//                                    double magnitude_phi1 = perp56.Mag()*perp_z_44.Mag();
//                                    double phi1 = TMath::ACos(scalar_product_phi1/magnitude_phi1);
                                        hist("h_phi1_44")->Fill(phi1);


                                        phi_zd1 = TMath::ATan2(l5_p_boosted.Py() + l6_p_boosted.Py(),
                                                               l5_p_boosted.Px() + l6_p_boosted.Px());
                                        phi_zd2 = TMath::ATan2(l7_p_boosted.Py() + l8_p_boosted.Py(),
                                                               l7_p_boosted.Px() + l8_p_boosted.Px());
                                        phi_zd1_nonboosted = TMath::ATan2(lep5->py() + lep6->py(),
                                                                          lep5->px() + lep6->px());
                                        phi_zd2_nonboosted = TMath::ATan2(lep7->py() + lep8->py(),
                                                                          lep7->px() + lep8->px());
                                        ANA_MSG_INFO("----- 4+4 case ------");
//                                    std::cout<<" the cosine value 44: "<<cosine<<std::endl;
//                                    std::cout<<" the phi angle 44: "<<phi<<std::endl;
//                                    ANA_MSG_INFO("Angle difference :     " << phi_zd2 - phi_zd1);
//                                    ANA_MSG_INFO("Angle difference nonboosted:     " << phi_zd2_nonboosted - phi_zd1_nonboosted);
//                                    ANA_MSG_INFO("Angles boosted:     " << phi_zd1 << " "<< phi_zd2);
//                                    ANA_MSG_INFO("Angles nonboosted:     " << phi_zd1_nonboosted << " "<< phi_zd2_nonboosted);
                                        hist("h_avg_phi_boosted_all")->Fill((phi_zd2 + phi_zd1) / 2);
                                        hist("h_delta_phi_boosted_all")->Fill(phi_zd2 - phi_zd1);
                                        hist("h_avg_phi_nonboosted_all")->Fill(
                                                (phi_zd2_nonboosted + phi_zd1_nonboosted) / 2);
                                        hist("h_delta_phi_nonboosted_all")->Fill(
                                                phi_zd2_nonboosted - phi_zd1_nonboosted);
                                        hist("h_avg_phi_boosted_44")->Fill((phi_zd2 + phi_zd1) / 2);
                                        hist("h_delta_phi_boosted_44")->Fill(phi_zd2 - phi_zd1);
                                        hist("h_avg_phi_nonboosted_44")->Fill(
                                                (phi_zd2_nonboosted + phi_zd1_nonboosted) / 2);
                                        hist("h_delta_phi_nonboosted_44")->Fill(
                                                phi_zd2_nonboosted - phi_zd1_nonboosted);


                                    }
//                                }

//                                 //BGBG this one is correct
                                TLorentzVector llll_2222,ll_1_2222,ll_2_2222;
//                                if(status_h1_44 || status_h2_44 ) {

                                    if (bitmask == 5 || bitmask == 6 || bitmask == 9 || bitmask == 10) {
//                                        ANA_MSG_INFO("EVENT NUMBER "<< " "<< eventInfo->eventNumber());
//                                        ANA_MSG_INFO("RUN NUMBER "<< " "<< eventInfo->runNumber());
//                                        ANA_MSG_INFO("lepton3 "<<lep3->pdgId()<<" lepton4 "<<lep4->pdgId()<<" lepton7 "<<lep7->pdgId()<<" lepton8 "<<lep8->pdgId());

                                        events_2222++;
//                                        ANA_MSG_INFO("Bitmask value" << bitmask);

                                        double additional_scalar1_pt = additional_scalar1->pt();
                                        double additional_scalar2_pt = additional_scalar2->pt();
                                        hist("h_higgs_pt_2222")->Fill(additional_scalar2_pt / 1000);

                                        double zdark1_pt = z_dark1->pt();
                                        double zdark2_pt = z_dark2->pt();
                                        double zdark3_pt = z_dark3->pt();
                                        double zdark4_pt = z_dark4->pt();


                                        double energy_4l = lep3->e() + lep4->e() + lep7->e() + lep8->e();
                                        double energy_ll1 = lep3->e() + lep4->e();
                                        double energy_ll2 = lep7->e() + lep8->e();
                                        double px_4l = lep3->px() + lep4->px() + lep7->px() + lep8->px();
                                        double py_4l = lep3->py() + lep4->py() + lep7->py() + lep8->py();
                                        double pz_4l = lep3->pz() + lep4->pz() + lep7->pz() + lep8->pz();
                                        double e_4l = lep3->e() + lep4->e() + lep7->e() + lep8->e();
                                        double px1_ll1 = lep3->px() + lep4->px();
                                        double py1_ll1 = lep3->py() + lep4->py();
                                        double pz1_ll1 = lep3->pz() + lep4->pz();
                                        double px1_ll2 = lep7->px() + lep8->px();
                                        double py1_ll2 = lep7->py() + lep8->py();
                                        double pz1_ll2 = lep7->pz() + lep8->pz();
                                        double e1_ll2 = lep7->e() + lep8->e();
                                        double e1_ll1 = lep3->e() + lep4->e();

                                        double pt1 = lep1->pt();
                                        double pt2 = lep2->pt();
                                        double pt3 = lep3->pt();
                                        double pt4 = lep4->pt();
                                        double pt5 = lep5->pt();
                                        double pt6 = lep6->pt();
                                        double pt7 = lep7->pt();
                                        double pt8 = lep8->pt();

                                        llll_2222.SetPxPyPzE(px_4l, py_4l, pz_4l, e_4l);
                                        ll_1_2222.SetPxPyPzE(px1_ll1, py1_ll1, pz1_ll1, e1_ll1);
                                        ll_2_2222.SetPxPyPzE(px1_ll2, py1_ll2, pz1_ll2, e1_ll2);

                                        // Doing calculations for delta R
                                        double delta_eta34_2222 = lep3->eta() - lep4->eta();
                                        double delta_eta37_2222 = lep3->eta() - lep7->eta();
                                        double delta_eta38_2222 = lep3->eta() - lep8->eta();
                                        double delta_eta47_2222 = lep4->eta() - lep7->eta();
                                        double delta_eta48_2222 = lep4->eta() - lep8->eta();
                                        double delta_eta78_2222 = lep7->eta() - lep8->eta();
                                        double delta_eta_Zd1_Zd2_2222 = ll_1_2222.Eta() - ll_2_2222.Eta();

                                        double delta_phi34_2222 = lep3->phi() - lep4->phi();
                                        double delta_phi37_2222 = lep3->phi() - lep7->phi();
                                        double delta_phi38_2222 = lep3->phi() - lep8->phi();
                                        double delta_phi47_2222 = lep4->phi() - lep7->phi();
                                        double delta_phi48_2222 = lep4->phi() - lep8->phi();
                                        double delta_phi78_2222 = lep7->phi() - lep8->phi();
                                        double delta_phi_Zd1_Zd2_2222 = ll_1_2222.Phi() - ll_2_2222.Phi();

                                        double delta_R34_2222 = TMath::Sqrt(delta_eta34_2222 * delta_eta34_2222 +
                                                                            delta_phi34_2222 * delta_phi34_2222);
                                        double delta_R37_2222 = TMath::Sqrt(delta_eta37_2222 * delta_eta37_2222 +
                                                                            delta_phi37_2222 * delta_phi37_2222);
                                        double delta_R38_2222 = TMath::Sqrt(delta_eta38_2222 * delta_eta38_2222 +
                                                                            delta_phi38_2222 * delta_phi38_2222);
                                        double delta_R47_2222 = TMath::Sqrt(delta_eta47_2222 * delta_eta47_2222 +
                                                                            delta_phi47_2222 * delta_phi47_2222);
                                        double delta_R48_2222 = TMath::Sqrt(delta_eta48_2222 * delta_eta48_2222 +
                                                                            delta_phi48_2222 * delta_phi48_2222);
                                        double delta_R78_2222 = TMath::Sqrt(delta_eta78_2222 * delta_eta78_2222 +
                                                                            delta_phi78_2222 * delta_phi78_2222);
                                        double delta_Zd1_Zd2_2222 = TMath::Sqrt(delta_eta_Zd1_Zd2_2222 * delta_eta_Zd1_Zd2_2222 +
                                                                                        delta_phi_Zd1_Zd2_2222 * delta_phi_Zd1_Zd2_2222);
                                        // Get 4m case
                                        if (lep3->absPdgId() == 13 && lep4->absPdgId() == 13 && lep3->absPdgId() == 13 && lep4->absPdgId() == 13 ){
                                            hist("h_deltaR_34_2222_4e")->Fill(delta_R34_2222);
                                            hist("h_deltaR_37_2222_4e")->Fill(delta_R37_2222);
                                            hist("h_deltaR_38_2222_4e")->Fill(delta_R38_2222);
                                            hist("h_deltaR_47_2222_4e")->Fill(delta_R47_2222);
                                            hist("h_deltaR_48_2222_4e")->Fill(delta_R48_2222);
                                            hist("h_deltaR_78_2222_4e")->Fill(delta_R78_2222);

                                        }
                                        // Get 4e case
                                        if (lep3->absPdgId() == 11 && lep4->absPdgId() == 11 && lep3->absPdgId() == 11 && lep4->absPdgId() == 11 ){
                                            hist("h_deltaR_34_2222_4m")->Fill(delta_R34_2222);
                                            hist("h_deltaR_37_2222_4m")->Fill(delta_R37_2222);
                                            hist("h_deltaR_38_2222_4m")->Fill(delta_R38_2222);
                                            hist("h_deltaR_47_2222_4m")->Fill(delta_R47_2222);
                                            hist("h_deltaR_48_2222_4m")->Fill(delta_R48_2222);
                                            hist("h_deltaR_78_2222_4m")->Fill(delta_R78_2222);

                                        }

                                        hist("h_deltaR_34_2222")->Fill(delta_R34_2222);
                                        hist("h_deltaR_37_2222")->Fill(delta_R37_2222);
                                        hist("h_deltaR_38_2222")->Fill(delta_R38_2222);
                                        hist("h_deltaR_47_2222")->Fill(delta_R47_2222);
                                        hist("h_deltaR_48_2222")->Fill(delta_R48_2222);
                                        hist("h_deltaR_78_2222")->Fill(delta_R78_2222);
                                        hist("h_delta_Zd1_Zd2_2222")->Fill(delta_Zd1_Zd2_2222);




                                        double m4lInvMass = TMath::Sqrt(energy_4l * energy_4l -
                                                                        (px_4l * px_4l + py_4l * py_4l +
                                                                         pz_4l * pz_4l));
                                        double mll1InvMass = TMath::Sqrt(energy_ll1 * energy_ll1 -
                                                                         (px1_ll1 * px1_ll1 + py1_ll1 * py1_ll1 +
                                                                          pz1_ll1 * pz1_ll1));
                                        double mll2InvMass = TMath::Sqrt(energy_ll2 * energy_ll2 -
                                                                         (px1_ll2 * px1_ll2 + py1_ll2 * py1_ll2 +
                                                                          pz1_ll2 * pz1_ll2));
//                                    hist("h_4lInvMass_all")->Fill(m4lInvMass/1000);
                                        hist("h_4lInvMass_2222")->Fill(llll_2222.M() / 1000);
                                        hist("h_mll1InvMass_2222")->Fill(ll_1_2222.M() / 1000);
                                        hist("h_mll1InvMass_all")->Fill(mll1InvMass / 1000);
                                        hist("h_mll2InvMass_2222")->Fill(ll_2_2222.M() / 1000);

                                        hist("h_mll2InvMass_all")->Fill(mll2InvMass / 1000);
                                        hist("h_zdark1_pt_2222")->Fill(ll_1_2222.Pt() / 1000);
                                        hist("h_zdark2_pt_2222")->Fill(ll_2_2222.Pt() / 1000);

                                        double met_higgs_2222_angle = met_TLV.Angle(llll_2222.Vect());
                                        double met_zd1_2222_angle = met_TLV.Angle(ll_1_2222.Vect());
                                        double met_zd2_2222_angle = met_TLV.Angle(ll_2_2222.Vect());
                                        double m4l_2222_phi_angle = llll_2222.Phi();
                                        double mll1_2222_phi_angle = ll_1_2222.Phi();
                                        double mll2_2222_phi_angle = ll_2_2222.Phi();
                                        double m4l_2222_Eta = llll_2222.Eta();
                                        double mll1_2222_Eta = ll_1_2222.Eta();
                                        double mll2_2222_Eta = ll_2_2222.Eta();
                                        double m4l_2222 = llll_2222.M();
                                        double mll1_2222 = ll_1_2222.M();
                                        double mll2_2222 = ll_2_2222.M();
                                        double met_phi_angle = truthMET_NonInt->phi();





                                        double deltaPhi_m4lMet = abs(m4l_2222_phi_angle - met_phi_angle);
                                        double deltaPhi_mll1Met = abs(mll1_2222_phi_angle - met_phi_angle);
                                        double deltaPhi_mll2Met = abs(mll2_2222_phi_angle - met_phi_angle);

                                        hist("h_missingET_higgs_phi_angle_2222")->Fill(deltaPhi_m4lMet);
                                        hist("h_missingET_dilep1_phi_angle_2222")->Fill(deltaPhi_mll1Met);
                                        hist("h_missingET_dilep2_phi_angle_2222")->Fill(deltaPhi_mll2Met);
                                        hist("h_missingET_higgs_angle_2222")->Fill(met_higgs_2222_angle);
                                        hist("h_missingET_dilep1_angle_2222")->Fill(met_zd1_2222_angle);
                                        hist("h_missingET_dilep2_angle_2222")->Fill(met_zd1_2222_angle);

                                        hist("h_missingET_higgs_phi_angle_2222")->Fill(deltaPhi_m4lMet);
                                        hist("h_missingET_dilep1_phi_angle_2222")->Fill(deltaPhi_mll1Met);
                                        hist("h_missingET_dilep2_phi_angle_2222")->Fill(deltaPhi_mll2Met);

                                        hist("h_missingET_2222")->Fill(truthMET_NonInt->met() / 1000);


                                        //boosting to four lepton rest frame using reconstructed objects
                                        TLorentzVector S_p, S_p_boosted;
                                        float S_pz, S_py, S_px, S_e;
                                        S_px = lep3->px() + lep4->px() + lep7->px() + lep8->px();
                                        S_py = lep3->py() + lep4->py() + lep7->py() + lep8->py();
                                        S_pz = lep3->pz() + lep4->pz() + lep7->pz() + lep8->pz();
                                        S_e = lep3->e() + lep4->e() + lep7->e() + lep8->e();

                                        S_p.SetPxPyPzE(S_px, S_py, S_pz, S_e);
                                        //Get boost from Higgs
                                        TVector3 S2_boostVector;
                                        // method takes information from TLorentzVector to form boost vector. This vector will then be used to
                                        S2_boostVector = S_p.BoostVector();
                                        // prevent overriding S_p (lab frame)
                                        S_p_boosted = S_p;
                                        // Boost using TVector3 S2_boostVector
                                        S_p_boosted.Boost(-S2_boostVector);
                                        // Checking if S_p_boosted is at rest, meaning that we only have energy and no momnetum
//                                    ANA_MSG_INFO ("the boosted vector: "<< " "<<S_p_boosted.Px()<<" "<<S_p_boosted.Py()<<" "<<S_p_boosted.Pz());

                                        TLorentzVector l3_p, l4_p, l7_p, l8_p, l3_p_boosted, l4_p_boosted, l7_p_boosted, l8_p_boosted, z_axis;
                                        TLorentzVector z2_p, z4_p, z2_p_boosted, z4_p_boosted;

                                        TVector3 lep3_vec3_boosted, lep4_vec3_boosted, lep7_vec3_boosted, lep8_vec3_boosted;
                                        TVector3 z2_vec3_boosted, z4_vec3_boosted, z_axis_not_boosted, z_axis_boosted;

                                        l3_p.SetPxPyPzE(lep3->px(), lep3->py(), lep3->pz(), lep3->e());
                                        l4_p.SetPxPyPzE(lep4->px(), lep4->py(), lep4->pz(), lep4->e());
                                        l7_p.SetPxPyPzE(lep7->px(), lep7->py(), lep7->pz(), lep7->e());
                                        l8_p.SetPxPyPzE(lep8->px(), lep8->py(), lep8->pz(), lep8->e());

                                        z_axis_not_boosted.SetXYZ(0, 0, 1);

                                        z2_p.SetPxPyPzE(z_dark2->px(), z_dark2->py(), z_dark2->pz(), z_dark2->e());
                                        z4_p.SetPxPyPzE(z_dark4->px(), z_dark4->py(), z_dark4->pz(), z_dark4->e());

                                        l3_p_boosted = l3_p;
                                        l4_p_boosted = l4_p;
                                        l7_p_boosted = l7_p;
                                        l8_p_boosted = l8_p;

                                        z2_p_boosted = z2_p;
                                        z4_p_boosted = z4_p;


                                        l3_p_boosted.Boost(-S2_boostVector);
                                        l4_p_boosted.Boost(-S2_boostVector);
                                        l7_p_boosted.Boost(-S2_boostVector);
                                        l8_p_boosted.Boost(-S2_boostVector);

                                        z2_p_boosted.Boost(-S2_boostVector);
                                        z4_p_boosted.Boost(-S2_boostVector);

                                        // using these to form normal vectors
                                        lep3_vec3_boosted.SetXYZ(l3_p_boosted.Px(), l3_p_boosted.Py(),
                                                                 l3_p_boosted.Pz());
                                        lep4_vec3_boosted.SetXYZ(l4_p_boosted.Px(), l4_p_boosted.Py(),
                                                                 l4_p_boosted.Pz());
                                        lep7_vec3_boosted.SetXYZ(l7_p_boosted.Px(), l7_p_boosted.Py(),
                                                                 l7_p_boosted.Pz());
                                        lep8_vec3_boosted.SetXYZ(l8_p_boosted.Px(), l8_p_boosted.Py(),
                                                                 l8_p_boosted.Pz());

                                        z2_vec3_boosted.SetXYZ(z2_p_boosted.Px(), z2_p_boosted.Py(), z2_p_boosted.Pz());
                                        z4_vec3_boosted.SetXYZ(z4_p_boosted.Px(), z4_p_boosted.Py(), z4_p_boosted.Pz());

                                        double theta1_2222, theta2_2222, theta_star_2222;
                                        theta_star_2222 = z2_vec3_boosted.Angle(z_axis_not_boosted);
                                        hist("h_theta_star_2222")->Fill(theta_star_2222);

                                        // lepton 5 is always positive charge. therefore we use lepton 6 for the BBGG case
                                        if (lep4->charge() < 0) {
                                            theta1_2222 = z2_vec3_boosted.Angle(lep4_vec3_boosted);
                                            ANA_MSG_INFO("theta1_44 2222: " << " " << theta1_2222);
                                            hist("h_theta1_2222")->Fill(theta1_2222);

                                        }

                                        if (lep8->charge() < 0) {
                                            theta2_2222 = z4_vec3_boosted.Angle(lep8_vec3_boosted);
                                            ANA_MSG_INFO("theta2 2222: " << " " << theta2_2222);
                                            hist("h_theta2_2222")->Fill(theta2_2222);

                                        }
                                        double theta_diff_2222 = abs(theta1_2222 - theta2_2222);
                                        hist("h_theta_diff_2222")->Fill(theta_diff_2222);
                                        hist("h_theta_diff_2D_2222")->Fill(theta1_2222, theta2_2222);
                                        // Get the normal vector for the plane formed by the 3-momenta of the two leptons
                                        TVector3 perp34 = lep3_vec3_boosted.Cross(lep4_vec3_boosted);
                                        TVector3 perp78 = lep7_vec3_boosted.Cross(lep8_vec3_boosted);
                                        TVector3 perp_z_2222 = z2_vec3_boosted.Cross(z_axis_not_boosted);

                                        // do the scalar product so that we can get the angle between the planes

                                        double phi = perp34.Angle(perp78);
//                                    double scalar_product = perp34.Dot(perp78);
//                                    double magnitude = perp34.Mag()*perp78.Mag();
//                                    double cosine = scalar_product/magnitude;
//                                    double phi = TMath::ACos(scalar_product/magnitude);
                                        hist("h_phi_2222")->Fill(phi);

                                        double phi1 = perp34.Angle(perp_z_2222);
//                                    double scalar_product_phi1 = perp34.Dot(perp_z_2222);
//                                    double magnitude_phi1 = perp34.Mag()*perp_z_2222.Mag();
//                                    double phi1 = TMath::ACos(scalar_product_phi1/magnitude_phi1);
                                        hist("h_phi1_2222")->Fill(phi1);

                                        phi_zd1 = TMath::ATan2(l3_p_boosted.Py() + l4_p_boosted.Py(),
                                                               l3_p_boosted.Px() + l4_p_boosted.Px());
                                        phi_zd2 = TMath::ATan2(l7_p_boosted.Py() + l8_p_boosted.Py(),
                                                               l7_p_boosted.Px() + l8_p_boosted.Px());
                                        phi_zd1_nonboosted = TMath::ATan2(lep5->py() + lep6->py(),
                                                                          lep5->px() + lep6->px());
                                        phi_zd2_nonboosted = TMath::ATan2(lep7->py() + lep8->py(),
                                                                          lep7->px() + lep8->px());

                                        ANA_MSG_INFO("----- 2-2-2-2 ------");
//                                    std::cout<<" the cosine value 2222: "<<cosine<<std::endl;
//                                    std::cout<<" the phi angle 2222: "<<phi<<std::endl;

                                        ANA_MSG_INFO("Angle difference boosted:     " << phi_zd2 - phi_zd1);
                                        ANA_MSG_INFO("Angle difference nonboosted:     "
                                                             << phi_zd2_nonboosted - phi_zd1_nonboosted);
                                        ANA_MSG_INFO("Angles :     " << phi_zd1 << " " << phi_zd2);
                                        ANA_MSG_INFO("Angles nonboosted:     " << phi_zd1_nonboosted << " "
                                                                               << phi_zd2_nonboosted);
                                        hist("h_avg_phi_boosted_all")->Fill((phi_zd2 + phi_zd1) / 2);
                                        hist("h_delta_phi_boosted_all")->Fill(phi_zd2 - phi_zd1);
                                        hist("h_avg_phi_nonboosted_all")->Fill(
                                                (phi_zd2_nonboosted + phi_zd1_nonboosted) / 2);
                                        hist("h_delta_phi_nonboosted_all")->Fill(
                                                phi_zd2_nonboosted - phi_zd1_nonboosted);
                                        hist("h_avg_phi_boosted_2222")->Fill((phi_zd2 + phi_zd1) / 2);
                                        hist("h_delta_phi_boosted_2222")->Fill(phi_zd2 - phi_zd1);
                                        hist("h_avg_phi_nonboosted_2222")->Fill(
                                                (phi_zd2_nonboosted + phi_zd1_nonboosted) / 2);
                                        hist("h_delta_phi_nonboosted_2222")->Fill(
                                                phi_zd2_nonboosted - phi_zd1_nonboosted);


                                    }
                                if(lep1->hasDecayVtx()){
                                    const xAOD::TruthVertex *unstable_decayVtx_1 = lep1->decayVtx();
                                    if(lep1->nChildren() > 1 && lep1->absPdgId()==11) {
                                        const xAOD::TruthParticle *unstable_lep1 = unstable_decayVtx_1->outgoingParticle(0);
                                        const xAOD::TruthParticle *unstable_lep2 = unstable_decayVtx_1->outgoingParticle(1);
                                        photon_energy1 = unstable_lep2->e();
                                        electron_pt1 = lep1->pt();
                                        electron_e1 = lep1->e();
                                        energy_sum1 = lep1->e() + unstable_lep2->e();
                                        lepton_children << " unstable lep1 pdgid " << unstable_lep1->pdgId()<< " unstable lep2 pdgid " << unstable_lep2->pdgId()<< std::endl;

                                    }
                                }
                                if(lep2->hasDecayVtx()){
                                    const xAOD::TruthVertex *unstable_decayVtx_1 = lep2->decayVtx();
                                    if(lep2->nChildren() > 1 && lep2->absPdgId()==11) {
                                        const xAOD::TruthParticle *unstable_lep1 = unstable_decayVtx_1->outgoingParticle(0);
                                        const xAOD::TruthParticle *unstable_lep2 = unstable_decayVtx_1->outgoingParticle(1);
                                        photon_energy2 = unstable_lep2->e();
                                        electron_pt2 = lep2->pt();
                                        electron_e2 = lep2->e();
                                        energy_sum2 = lep2->e() + unstable_lep2->e();

                                    }
                                }
                                if(lep3->hasDecayVtx()){
                                    const xAOD::TruthVertex *unstable_decayVtx_1 = lep3->decayVtx();
                                    if(lep3->nChildren() > 1 && lep3->absPdgId()==11) {
                                        const xAOD::TruthParticle *unstable_lep1 = unstable_decayVtx_1->outgoingParticle(0);
                                        const xAOD::TruthParticle *unstable_lep2 = unstable_decayVtx_1->outgoingParticle(1);
                                        photon_energy3 = unstable_lep2->e();
                                        electron_pt3 = lep3->pt();
                                        electron_e3 = lep3->e();
                                        energy_sum3 = lep3->e() + unstable_lep2->e();
                                        lepton_children << " unstable lep1 pdgid " << unstable_lep1->pdgId()<< " unstable lep2 pdgid " << unstable_lep2->pdgId()<< std::endl;

                                    }
                                }
                                if(lep4->hasDecayVtx()){
                                    const xAOD::TruthVertex *unstable_decayVtx_1 = lep4->decayVtx();
                                    if(lep4->nChildren() > 1 && lep4->absPdgId()==11) {
                                        const xAOD::TruthParticle *unstable_lep1 = unstable_decayVtx_1->outgoingParticle(0);
                                        const xAOD::TruthParticle *unstable_lep2 = unstable_decayVtx_1->outgoingParticle(1);
                                        photon_energy4 = unstable_lep2->e();
                                        electron_pt4 = lep4->pt();
                                        electron_e4 = lep4->e();
                                        energy_sum4 = lep4->e() + unstable_lep2->e();
                                        lepton_children << " unstable lep1 pdgid " << unstable_lep1->pdgId()<< " unstable lep2 pdgid " << unstable_lep2->pdgId()<< std::endl;

                                    }
                                }
                                photon_energy_tot = photon_energy1 + photon_energy2 + photon_energy3 + photon_energy4;
                                //  ATH_MSG_INFO("PHOTON ENERGY "<<photon_energy_tot);
                                electron_pt_tot = electron_pt1 + electron_pt2 + electron_pt3 + electron_pt4;
                                electron_e_tot = electron_e1 + electron_e2 + electron_e3 + electron_e4;
                                energy_sum_tot = energy_sum1 + energy_sum1 + energy_sum1 + energy_sum1;
                                hist("h_lep_unstable_pt")->Fill(electron_pt_tot/1000);
                                hist("h_lep_unstable_e")->Fill(electron_e_tot/1000);
                                hist("h_lep_unstable_photon_e")->Fill(photon_energy_tot /1000);
                                hist("h_lep_unstable_pt_sum")->Fill(energy_sum_tot/1000);
                            }

//
                        }

                    }
                }

            }
        }

    }

    const xAOD::TruthParticleContainer* truthElectron = nullptr;
    ANA_CHECK (evtStore()->retrieve (truthElectron, "TruthElectrons"));

    xAOD::TruthParticleContainer::const_iterator truth_electron_itr = truthElectron->begin();
    xAOD::TruthParticleContainer::const_iterator truth_electron_end = truthElectron->end();
    int e_count = 0;
    for( ; truth_electron_itr != truth_electron_end ; ++truth_electron_itr){
        e_count++;
        const xAOD::TruthParticle* truth_ele = *truth_electron_itr;
        if(truth_ele->absPdgId()==11)
        {
            ele_tot++;
            if (truth_ele->nParents()>0 && truth_ele->status() == 1)  ele_count++;

            ANA_MSG_INFO("is electron "<< " number of parents " <<truth_ele->nParents());
        }
        else
        {
            ANA_MSG_INFO("is NOT electron"<<truth_ele->pdgId());
        }
        for(int i=0; i<8; i++)
        {
            double delta_eta = truth_ele->eta() - eta_truth[i];
            double delta_phi = truth_ele->phi() - phi_truth[i];
            double delta_pt  = truth_ele->pt() - pt_truth[i];
            deltaR = TMath::Sqrt(delta_eta*delta_eta + delta_phi*delta_phi);

            if(deltaR < 0.1){
//               ANA_MSG_INFO("The deltaR "<<deltaR);
            }
            if(truth_ele->rapidity() == lep_rapidity[i]){
                ele_matched++;                              
                ANA_MSG_INFO("lepton"<<i+1<<" matches the TruthElectron particle");
            }
            if( truth_ele->barcode()==lep_barcode[i])           {
//                    ATH_MSG_INFO("FOUND THE MATCHING TRUTH ELECTRON");
                if(truth_ele->status()){
//                    ATH_MSG_INFO("IT IS STABLE");
//                    ATH_MSG_INFO("THE RAPIDITY DIFFERENCE "<<deltaR);
//                    ATH_MSG_INFO("THE PT DIFFERENCE "<<delta_pt);
                }

                if(lep_stability[i]){

//                    ATH_MSG_INFO("TRUTH PARTICLE IS STABLE "<< lep_stability[i]);
                    electron_match_file << " THE PT DIFFERENCE "<<delta_pt<<" THE RAPIDITY DIFFERENCE "<<deltaR<<" TRUTH ELECTRON IS STABLE "<<truth_ele->status()<<" TRUTH IS STABLE "<<lep_stability[i]<<std::endl;

                }
                else{
                      //  ATH_MSG_INFO("TRUTH PARTICLE IS NOT STABLE");
                }
            }
            if(truth_ele->hasDecayVtx()){
                //  ATH_MSG_INFO("NOT STABLE");
                const xAOD::TruthVertex *electron_decayVtx_1 = truth_ele->decayVtx();
                const xAOD::TruthParticle *electron_child1 = electron_decayVtx_1->outgoingParticle(0);
                const xAOD::TruthParticle *electron_child2 = electron_decayVtx_1->outgoingParticle(1);
//                ATH_MSG_INFO("CHILD 1 PDGID "<<electron_child1->absPdgId()<<" CHILD 2 PDGID "<<electron_child2->absPdgId());
            }

        }
    }
    //  ATH_MSG_INFO("the e_count "<<e_count);

    const xAOD::TruthParticleContainer* truthMuon = nullptr;
    ANA_CHECK (evtStore()->retrieve (truthMuon, "TruthMuons"));

    xAOD::TruthParticleContainer::const_iterator truth_muon_itr = truthMuon->begin();
    xAOD::TruthParticleContainer::const_iterator truth_muon_end = truthMuon->end();

    for( ; truth_muon_itr != truth_muon_end ; ++truth_muon_itr){
        const xAOD::TruthParticle* truth_muon = *truth_muon_itr;
        if(truth_muon->absPdgId()==11)
        {
            muon_tot++;
            if (truth_muon->nParents()>0 )  muon_count++;

            ANA_MSG_INFO("is muon "<< " number of parents " <<truth_muon->nParents());
        }
        else
        {
            ANA_MSG_INFO("is NOT muon"<<truth_muon->pdgId());
        }
        for(int i=0; i<8; i++)
        {
            double delta_eta = truth_muon->eta() - eta_truth[i];
            double delta_phi = truth_muon->phi() - phi_truth[i];
            double delta_pt  = truth_muon->pt() - pt_truth[i];
            deltaR = TMath::Sqrt(delta_eta*delta_eta + delta_phi*delta_phi);

            if(deltaR < 0.1){
                ANA_MSG_INFO("The deltaR "<<deltaR);

            }
            if(truth_muon->rapidity() == lep_rapidity[i]){
                muon_matched++;
                ANA_MSG_INFO("lepton"<<i<<" matches the TruthMuon particle");
            }
            if( truth_muon->barcode()==lep_barcode[i])           {

                //  ATH_MSG_INFO("FOUND THE MATCHING TRUTH MUON");
                if(truth_muon->status()){
                    //  ATH_MSG_INFO("IT IS STABLE");
                    //  ATH_MSG_INFO("THE RAPIDITY DIFFERENCE "<<deltaR);
                    //  ATH_MSG_INFO("THE PT DIFFERENCE "<<delta_pt);



                }
                else{
                    //  ATH_MSG_INFO("NOT STABLE");
                }
                if(lep_stability[i]){

                    //  ATH_MSG_INFO("TRUTH PARTICLE IS STABLE "<< lep_stability[i]);
                    muon_match_file << " THE PT DIFFERENCE "<<delta_pt<<" THE RAPIDITY DIFFERENCE "<<deltaR<<" TRUTH MUON IS STABLE "<<truth_muon->status()<<" TRUTH IS STABLE "<<lep_stability[i]<<std::endl;

                }
                else{
                    //  ATH_MSG_INFO("TRUTH PARTICLE IS NOT STABLE");
                }
            }

        }
    }


    return StatusCode::SUCCESS;
}



StatusCode MyxAODAnalysis :: finalize ()
{
    // This method is the mirror image of initialize(), meaning it gets
    // called after the last event has been processed on the worker node
    // and allows you to finish up any objects you created in
    // initialize() before they are written to disk.  This is actually
    // fairly rare, since this happens separately for each worker node.
    // Most of the time you want to do your post-processing on the
    // submission node after all your histogram outputs have been
    // merged.

//    ATH_MSG_ INFO( "STAT Statistics on " << n_events << " processed events" );
//    std::cout << "\n\n\n\n\n\n -------------------------------------------\n";
    std::cout << "44 Events found:\t" <<     events_44<< "\n";
    std::cout << "2222 Events found:\t" <<     events_2222<< "\n";
    ANA_MSG_INFO("Total number of electrons "<<ele_tot<<" total number of electrons with parents "<< ele_count);
    ANA_MSG_INFO("Total number of muons "<<ele_tot<<" total number of electrons with parents "<< muon_count);
    ANA_MSG_INFO("Total number of stable leptons "<<lep_stat);
    ANA_MSG_INFO("Total number of matched electrons "<<ele_matched);
    ANA_MSG_INFO("Total number of matched muons "<<muon_matched);



//    std::cout << "Events processed:\t" << n_events << "\n";
//    std::cout << "fd2 found:\t" << nfd1 << "\n";
//    std::cout << "fd1 found:\t" << nfd1 << "\n";
//    std::cout << "met found:\t" << nmet << "\n";
//    std::cout << "leptons found:\t" << leptons << "\n";
//    std::cout << "hs found:\t" << nhs << "\n";
//    std::cout << "Decaying to electrons:\t" << nToElectrons << " (" << 100 * nToElectrons/nDarkPhoton << "%)\n";
//    std::cout << "Decaying to muons:\t" << nToMuons << " (" << 100 * nToMuons/nDarkPhoton << "%)\n";
//    std::cout << "Decaying to taus:\t" << nToTaus << " (" << 100 * nToTaus/nDarkPhoton << "%)\n";
//    std::cout << "Decaying to quarks:\t" << nToQuarks << " (" << 100 * nToQuarks/nDarkPhoton << "%)\n";


    std::cout << "\n\n\n";
//    tree ("analysis")->Write ();
    return StatusCode::SUCCESS;
}

MyxAODAnalysis :: ~MyxAODAnalysis () {
    delete m_DG_Pt;
    delete m_DG_eta;
    delete m_DG_phi;
    delete m_DG_Lxy;
    delete m_DG_deltaPhi;

    delete m_fd2Pt;
    delete m_fd2Eta;
    delete m_fd2Phi;
    delete m_fd2M;

    delete m_fd1Eta;
    delete m_fd1Phi;
    delete m_fd1M;
    delete m_fd1Pt;

    delete m_leadingMuonPt;
    delete m_subLeadingMuonPt;
    delete m_muonPhi;
    delete m_muonEta;
    delete m_muonPairInvMass;
    delete m_muonPairOpenAngle;

    delete m_leadingElectPt;
    delete m_subLeadingElectPt;
    delete m_electPhi;
    delete m_electEta;
    delete m_electPairInvMass;
    delete m_electPairOpenAngle;

    delete m_missingET;
    barcode_file.close();
    lepton_children.close();


}
//
