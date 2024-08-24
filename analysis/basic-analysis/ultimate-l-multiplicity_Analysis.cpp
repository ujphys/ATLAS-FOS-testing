/*
The purpose of this analysis code is to check for the decay process: H -> 2S -> 4Zd -> 8l
And also to count the number and type of final state leptons
*/

// EDM include(s):
#include "AthLinks/ElementLink.h"

// xAOD include(s):
#include "xAODBase/IParticle.h"
#include "xAODBase/ObjectType.h"

// Local include(s):
#include "xAODTruth/TruthVertexContainerFwd.h"

#include "xAODTruth/TruthParticleContainerFwd.h"


#include <AsgMessaging/MessageCheck.h>
#include <MyAnalysis/MyxAODAnalysis.h>
#include <xAODEventInfo/EventInfo.h>
#include <EventLoop/Worker.h>
#include <TMath.h>

//Truth containers
#include "xAODTruth/TruthEvent.h"
#include "xAODTruth/TruthEventContainer.h"
#include "xAODTruth/TruthParticle.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthVertexContainer.h"
#include <xAODMissingET/MissingETContainer.h>
#include <EventLoopAlgs/NTupleSvc.h>
#include <EventLoopAlgs/AlgSelect.h>


//#include <xAODEgamma/ElectronContainer.h>

#include "TLorentzRotation.h"
#include "TLorentzVector.h"
#include "TVector3.h"


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



//    xAOD::TEvent* event = wk()->xaodEvent();
//
//    TFile *file = wk()->getOutputFile ("outputLabel");
//    ANA_CHECK(event->writeTo(file));

    //----R (angular distance)----//
    //R 44 case - 1234 pairs
    ANA_CHECK (book (TH1F("h_R44_12","h_R44_12",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R44_13","h_R44_13",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R44_14","h_R44_14",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R44_23","h_R44_23",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R44_24","h_R44_24",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R44_34","h_R44_34",50,-0.5,9.5)));
    //R 44 case - 5678 pairs
    ANA_CHECK (book (TH1F("h_R44_56","h_R44_12",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R44_57","h_R44_13",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R44_58","h_R44_14",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R44_67","h_R44_23",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R44_68","h_R44_24",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R44_78","h_R44_34",50,-0.5,9.5)));
    //R 22 case - 3478 pairs
    ANA_CHECK (book (TH1F("h_R22_34","h_R22_34",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R22_37","h_R22_37",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R22_38","h_R22_38",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R22_47","h_R22_47",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R22_48","h_R22_48",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R22_78","h_R22_78",50,-0.5,9.5)));
    //R 44 case - abcd pairs
    ANA_CHECK (book (TH1F("h_R44_ab","h_R44_ab",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R44_ac","h_R44_ac",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R44_ad","h_R44_ad",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R44_bc","h_R44_bc",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R44_bd","h_R44_bd",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R44_cd","h_R44_cd",50,-0.5,9.5)));
    //R 22 case - abcd pairs
    ANA_CHECK (book (TH1F("h_R22_ab","h_R22_ab",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R22_ac","h_R22_ac",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R22_ad","h_R22_ad",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R22_bc","h_R22_bc",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R22_bd","h_R22_bd",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_R22_cd","h_R22_cd",50,-0.5,9.5)));
    //R combined case - abcd pairs
    ANA_CHECK (book (TH1F("h_Rcomb_ab","h_Rcomb_ab",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_Rcomb_ac","h_Rcomb_ac",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_Rcomb_ad","h_Rcomb_ad",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_Rcomb_bc","h_Rcomb_bc",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_Rcomb_bd","h_Rcomb_bd",50,-0.5,9.5)));
    ANA_CHECK (book (TH1F("h_Rcomb_cd","h_Rcomb_cd",50,-0.5,9.5)));

    //Lepton eta and phi for 44 and 22 cases
    ANA_CHECK (book (TH1F("h_44_leptonEta","h_44_leptonEta",100,-8.0,8.0)));
    ANA_CHECK (book (TH1F("h_22_leptonEta","h_22_leptonEta",100,-8.0,8.0)));
    ANA_CHECK (book (TH1F("h_combined_leptonEta","h_combined_leptonEta",100,-8.0,8.0)));
    ANA_CHECK (book (TH1F("h_44_leptonPhi","h_44_leptonPhi",100,-8.0,8.0)));
    ANA_CHECK (book (TH1F("h_22_leptonPhi","h_22_leptonPhi",100,-8.0,8.0)));
    ANA_CHECK (book (TH1F("h_combined_leptonPhi","h_combined_leptonPhi",100,-8.0,8.0)));

    //ANA_CHECK (book (TH1F("h_missingET_other","h_missingET_other",100,0,1000)));
    //ANA_CHECK (book (TH1F("h_MET_boost","h_MET_boost",100,0,500)));

    return StatusCode::SUCCESS;
}

//Lepton multiplicity
float l_multiplicity = 0;
float l_multiplicity_44 = 0;
float l_multiplicity_3 = 0;
float l_multiplicity_5 = 0;
float l_multiplicity_12 = 0;
float l_multiplicity_22 = 0;

int n_Higgs = 0;
int n_S = 0;
int n_Zd = 0;
int n_childl1, n_childl2, n_childl3, n_childl4, n_childl5, n_childl6, n_childl7, n_childl8 = 0;
// Initialize 16 int variables as bit_0 to bit_15, all set to 0
int bit_0 = 0, bit_1 = 0, bit_2 = 0, bit_3 = 0, bit_4 = 0, bit_5 = 0, bit_6 = 0, bit_7 = 0, bit_8 = 0, bit_9 = 0, bit_10 = 0, bit_11 = 0, bit_12 = 0, bit_13 = 0, bit_14 = 0, bit_15 = 0;

//Function to calculate delta_R
float calc_delta_R(float eta1, float eta2, float phi1, float phi2){ //Returns a float representing delta_R between two particles
    float delta_R = sqrt( pow((eta1 - eta2), 2) + pow((phi1 - phi2), 2));
    return delta_R;
}

StatusCode MyxAODAnalysis :: execute ()
{
    // Here you do everything that needs to be done on every single
    // events, e.g. read input variables, apply cuts, and fill
    // histograms and trees.  This is where most of your actual analysis
    // code will go.

    //event processed
    n_events++;
    //ANA_MSG_INFO("__________________begin loop " << n_events << "____________________"); //show what number loop you're in

    // retrieve the eventInfo object from the event store
    const xAOD::EventInfo *eventInfo = nullptr;
    ANA_CHECK (evtStore()->retrieve (eventInfo, "EventInfo"));

    const xAOD::TruthParticleContainer* truthContainer = nullptr;
    ANA_CHECK (evtStore()->retrieve (truthContainer, "TruthParticles"));

    const xAOD::MissingETContainer* truth_MET = nullptr;
    ANA_CHECK (evtStore()->retrieve (truth_MET, "MET_Truth"));

    //const xAOD::MissingETContainer_v1  metContainer = nullptr;
    //ANA_CHECK (evtStore()->retrieve (metContainer, "MET_Truth"))

    //xAOD::MissingETContainer::const_iterator et_itr = truth_MET->begin();
    //xAOD::MissingETContainer::const_iterator et_end = truth_MET->end();


    xAOD::TruthParticleContainer::const_iterator truth_itr = truthContainer->begin();
    xAOD::TruthParticleContainer::const_iterator truth_end = truthContainer->end();


    // Loop over TruthParticle
    for( ; truth_itr != truth_end ; ++truth_itr){
        //ANA_MSG_INFO("__________________begin loop " << n_events << "____________________");

        const xAOD::TruthParticle* truth = *truth_itr;
        //Initialize bitmask variables
        bool l1_bool = false;
        //bool l2_bool = false;
        bool l3_bool = false;
        //bool l4_bool = false;
        bool l5_bool = false;
        //bool l6_bool = false;
        bool l7_bool = false;
        //bool l8_bool = false;

        //Initialize kinematic variables
        //float lepton1_phi, lepton2_phi, lepton3_phi, lepton4_phi, lepton5_phi, lepton6_phi, lepton7_phi, lepton8_phi; //phi
        //float lepton1_eta, lepton2_eta, lepton3_eta, lepton4_eta, lepton5_eta, lepton6_eta, lepton7_eta, lepton8_eta; //eta
        //float R_12, R_13, R_14, R_23, R_24, R_34; //R for 44 case - 1234 pairs
        //float R_56, R_57, R_58, R_67, R_68, R_78; //R for 44 case - 5678 pairs
        //float /*R_34*/ R_37, R_38, R_47, R_48 /*R_78*/; //R for 22 case - 3478 pairs
        
        //float test_R_56;

        //float R44_12, R44_13, R44_14, R44_23, R44_24, R44_34; //R for 44 case - 1234 pairs
        //float R44_56, R44_57, R44_58, R44_67, R44_68, R44_78; //R for 44 case - 5678 pairs
        //float R22_34, R22_37, R22_38, R22_47, R22_48, R22_78; //R for 22 case - 3478 pairs

        //float R44_ab, R44_ac, R44_ad, R44_bc, R44_bd, R44_cd; //R for 44 case - abcd pairs
        //float R22_ab, R22_ac, R22_ad, R22_bc, R22_bd, R22_cd; //R for 22 case - abcd pairs
        //float Rcomb_ab, Rcomb_ac, Rcomb_ad, Rcomb_bc, Rcomb_bd, Rcomb_cd; //R for combined case - abcd pairs

        //float pair1_phi, pair2_phi, pair_angle;
        //float pair1_phi_avg, pair2_phi_avg, pair_angle_avg;

        // Find Higgs and then the rest
        if(truth->pdgId()==25){
            //Access Higgs decay vertex
            if (truth->hasDecayVtx()){
                const xAOD::TruthVertex* decayVtx = truth->decayVtx();
                if ( !(decayVtx -> nOutgoingParticles() == 2)){
                    ANA_MSG_INFO("Higgs decaying in " << decayVtx->nOutgoingParticles() << " particles");

                    const xAOD::TruthParticle* H_child = decayVtx->outgoingParticle(0);
                    std::cout << "H_child pdgID: " << H_child->pdgId() << " ___ ";

                    continue;
                }
                //ANA_MSG_INFO("Higgs found");
                n_Higgs++;

                //------------Label the 1st gen childen (dark Higgs)------------
                const xAOD::TruthParticle* childS1 = decayVtx->outgoingParticle(0);
                const xAOD::TruthParticle* childS2 = decayVtx->outgoingParticle(1);
                //Check the Higgs has decayed to dark Higgs
                if ( (childS1->absPdgId() == 35) && (childS2->absPdgId() == 35)){
                    
                    //ANA_MSG_INFO("Dark Higgs found, child of the Higgs");
                    //Check childS1 decay vertex
                    if (childS1->hasDecayVtx() && childS2->hasDecayVtx()){ 
                        //ANA_MSG_INFO("Dark Higgs 1 decays");
                        const xAOD::TruthVertex* S1_decayVtx = childS1->decayVtx();
                        const xAOD::TruthVertex* S2_decayVtx = childS2->decayVtx();
                        ANA_MSG_INFO("Two S found");
                        n_S++;

                        //------------Label the 2nd gen children (Zd 1-4)------------
                        const xAOD::TruthParticle* childZd1 = S1_decayVtx->outgoingParticle(0);
                        const xAOD::TruthParticle* childZd2 = S1_decayVtx->outgoingParticle(1);
                        const xAOD::TruthParticle* childZd3 = S2_decayVtx->outgoingParticle(0);
                        const xAOD::TruthParticle* childZd4 = S2_decayVtx->outgoingParticle(1);
                        //Check S1 and S2 have decayed to dark photons
                        if ( (childZd1->absPdgId() == 32) && (childZd2->absPdgId() == 32) && (childZd3->absPdgId() == 32) && (childZd4->absPdgId() == 32)){
                            //ANA_MSG_INFO("Dark photon found, child of the dark Higgs");
                            //Check both Zd children have decay verteces
                            if ( childZd1->hasDecayVtx() && childZd2->hasDecayVtx() && childZd3->hasDecayVtx() && childZd4->hasDecayVtx() ){
                                const xAOD::TruthVertex* Zd1_decayVtx = childZd1->decayVtx();
                                const xAOD::TruthVertex* Zd2_decayVtx = childZd2->decayVtx();
                                const xAOD::TruthVertex* Zd3_decayVtx = childZd3->decayVtx();
                                const xAOD::TruthVertex* Zd4_decayVtx = childZd4->decayVtx();
                                ANA_MSG_INFO("Four Zd found");
                                n_Zd++;

                                //------------Label the 3rd gen children (leptons)------------
                                //---------------Lepton check starts----------------//
                                const xAOD::TruthParticle* childl1 = Zd1_decayVtx->outgoingParticle(0);
                                if (childl1 -> status() != 1){
                                    //ANA_MSG_INFO("Not stable");
                                    n_childl1++;
                                    if (childl1->hasDecayVtx()){
                                        ANA_MSG_INFO("Childl1 unstable, pdgID: " << childl1->pdgId());
                                        const xAOD::TruthVertex* childl1_decayVtx = childl1->decayVtx();
                                        int n_Vtx1 = childl1_decayVtx -> nOutgoingParticles();
                                        for (int i=0; i < n_Vtx1; i++){
                                            const xAOD::TruthParticle* gchildl1 = childl1_decayVtx->outgoingParticle(i);
                                            std::cout << "grandchild1 pdgID: " << gchildl1->pdgId() << " ___ ";
                                            if (gchildl1 -> status() != 1){
                                                std::cout << "grandchild1 UNSTABLE";
                                            }
                                        }
                                        std::cout << std::endl;
                                    }
                                }
                                const xAOD::TruthParticle* childl2 = Zd1_decayVtx->outgoingParticle(1);
                                if (childl2 -> status() != 1){
                                    //ANA_MSG_INFO("Not stable");
                                    n_childl2++;
                                    if (childl2->hasDecayVtx()){
                                        ANA_MSG_INFO("childl2 unstable, pdgID: " << childl2->pdgId());
                                        const xAOD::TruthVertex* childl2_decayVtx = childl2->decayVtx();
                                        int n_Vtx2 = childl2_decayVtx -> nOutgoingParticles();
                                        for (int i=0; i < n_Vtx2; i++){
                                            const xAOD::TruthParticle* gchildl2 = childl2_decayVtx->outgoingParticle(i);
                                            std::cout << "grandchild2 pdgID: " << gchildl2->pdgId() << " ___ ";
                                            if (gchildl2 -> status() != 1){
                                                std::cout << "grandchild2 UNSTABLE";
                                            }
                                        }
                                        std::cout << std::endl;
                                    }
                                }
                                const xAOD::TruthParticle* childl3 = Zd2_decayVtx->outgoingParticle(0);
                                if (childl3 -> status() != 1){
                                    //ANA_MSG_INFO("Not stable");
                                    n_childl3++;
                                    if (childl3->hasDecayVtx()){
                                        ANA_MSG_INFO("childl3 unstable, pdgID: " << childl3->pdgId());
                                        const xAOD::TruthVertex* childl3_decayVtx = childl3->decayVtx();
                                        int n_Vtx3 = childl3_decayVtx -> nOutgoingParticles();
                                        for (int i=0; i < n_Vtx3; i++){
                                            const xAOD::TruthParticle* gchildl3 = childl3_decayVtx->outgoingParticle(i);
                                            std::cout << "grandchild3 pdgID: " << gchildl3->pdgId() << " ___ ";
                                            if (gchildl3 -> status() != 1){
                                                std::cout << "grandchild3 UNSTABLE";
                                            }
                                        }
                                        std::cout << std::endl;
                                    }
                                }
                                const xAOD::TruthParticle* childl4 = Zd2_decayVtx->outgoingParticle(1);
                                if (childl4 -> status() != 1){
                                    //ANA_MSG_INFO("Not stable");
                                    n_childl4++;
                                    if (childl4->hasDecayVtx()){
                                        ANA_MSG_INFO("childl4 unstable, pdgID: " << childl4->pdgId());
                                        const xAOD::TruthVertex* childl4_decayVtx = childl4->decayVtx();
                                        int n_Vtx4 = childl4_decayVtx -> nOutgoingParticles();
                                        for (int i=0; i < n_Vtx4; i++){
                                            const xAOD::TruthParticle* gchildl4 = childl4_decayVtx->outgoingParticle(i);
                                            std::cout << "grandchild4 pdgID: " << gchildl4->pdgId() << " ___ ";
                                            if (gchildl4 -> status() != 1){
                                                std::cout << "grandchild4 UNSTABLE";
                                            }
                                        }
                                        std::cout << std::endl;
                                    }
                                }
                                const xAOD::TruthParticle* childl5 = Zd3_decayVtx->outgoingParticle(0);
                                if (childl5 -> status() != 1){
                                    //ANA_MSG_INFO("Not stable");
                                    n_childl5++;
                                    if (childl5->hasDecayVtx()){
                                        ANA_MSG_INFO("childl5 unstable, pdgID: " << childl5->pdgId());
                                        const xAOD::TruthVertex* childl5_decayVtx = childl5->decayVtx();
                                        int n_Vtx5 = childl5_decayVtx -> nOutgoingParticles();
                                        for (int i=0; i < n_Vtx5; i++){
                                            const xAOD::TruthParticle* gchildl5 = childl5_decayVtx->outgoingParticle(i);
                                            std::cout << "grandchild5 pdgID: " << gchildl5->pdgId() << " ___ ";
                                            if (gchildl5 -> status() != 1){
                                                std::cout << "grandchild5 UNSTABLE";
                                            }
                                        }
                                        std::cout << std::endl;
                                    }
                                }
                                const xAOD::TruthParticle* childl6 = Zd3_decayVtx->outgoingParticle(1);
                                if (childl6 -> status() != 1){
                                    //ANA_MSG_INFO("Not stable");
                                    n_childl6++;
                                    if (childl6->hasDecayVtx()){
                                        ANA_MSG_INFO("childl6 unstable, pdgID: " << childl6->pdgId());
                                        const xAOD::TruthVertex* childl6_decayVtx = childl6->decayVtx();
                                        int n_Vtx6 = childl6_decayVtx -> nOutgoingParticles();
                                        for (int i=0; i < n_Vtx6; i++){
                                            const xAOD::TruthParticle* gchildl6 = childl6_decayVtx->outgoingParticle(i);
                                            std::cout << "grandchild6 pdgID: " << gchildl6->pdgId() << " ___ ";
                                            if (gchildl6 -> status() != 1){
                                                std::cout << "grandchild6 UNSTABLE";
                                            }
                                        }
                                        std::cout << std::endl;
                                    }
                                }
                                const xAOD::TruthParticle* childl7 = Zd4_decayVtx->outgoingParticle(0);
                                if (childl7 -> status() != 1){
                                    //ANA_MSG_INFO("Not stable");
                                    n_childl7++;
                                    if (childl7->hasDecayVtx()){
                                        ANA_MSG_INFO("childl7 unstable, pdgID: " << childl7->pdgId());
                                        const xAOD::TruthVertex* childl7_decayVtx = childl7->decayVtx();
                                        int n_Vtx7 = childl7_decayVtx -> nOutgoingParticles();
                                        for (int i=0; i < n_Vtx7; i++){
                                            const xAOD::TruthParticle* gchildl7 = childl7_decayVtx->outgoingParticle(i);
                                            std::cout << "grandchild7 pdgID: " << gchildl7->pdgId() << " ___ ";
                                            if (gchildl7 -> status() != 1){
                                                std::cout << "grandchild7 UNSTABLE";
                                            }
                                        }
                                        std::cout << std::endl;
                                    }
                                }
                                const xAOD::TruthParticle* childl8 = Zd4_decayVtx->outgoingParticle(1);
                                if (childl8 -> status() != 1){
                                    //ANA_MSG_INFO("Not stable");
                                    n_childl8++;
                                    if (childl8->hasDecayVtx()){
                                        ANA_MSG_INFO("childl8 unstable, pdgID: " << childl8->pdgId());
                                        const xAOD::TruthVertex* childl8_decayVtx = childl8->decayVtx();
                                        int n_Vtx8 = childl8_decayVtx -> nOutgoingParticles();
                                        for (int i=0; i < n_Vtx8; i++){
                                            const xAOD::TruthParticle* gchildl8 = childl8_decayVtx->outgoingParticle(i);
                                            std::cout << "grandchild8 pdgID: " << gchildl8->pdgId() << " ___ ";
                                            if (gchildl8 -> status() != 1){
                                                //std::cout << "grandchild8 UNSTABLE";
                                            }
                                        }
                                        std::cout << std::endl;
                                    }
                                }
                                //---------------Lepton check ends----------------//


                                //Check all leptons are stable
                                if (true){
                                //( (childl1->status()==1) && (childl2->status()==1) && (childl3->status()==1) && (childl4->status()==1)
                                  //&& (childl5->status()==1) && (childl6->status()==1)&& (childl7->status()==1)&& (childl8->status()==1) ){
                                    //ANA_MSG_INFO("All leptons stable");

                                    //Set bitmask
                                    if (childl1->absPdgId()==11 || childl1->absPdgId()==13){l1_bool = true;}
                                    //if (childl2->absPdgId()==11 || childl2->absPdgId()==13){l2_bool = true;}
                                    if (childl3->absPdgId()==11 || childl3->absPdgId()==13){l3_bool = true;}
                                    //if (childl4->absPdgId()==11 || childl4->absPdgId()==13){l4_bool = true;}
                                    if (childl5->absPdgId()==11 || childl5->absPdgId()==13){l5_bool = true;}
                                    //if (childl6->absPdgId()==11 || childl6->absPdgId()==13){l6_bool = true;}
                                    if (childl7->absPdgId()==11 || childl7->absPdgId()==13){l7_bool = true;}
                                    //if (childl8->absPdgId()==11 || childl8->absPdgId()==13){l8_bool = true;}

                                    //Kinematics
                                    /*
                                    lepton1_eta = childl1->eta();
                                    lepton1_phi = childl1->phi();
                                    lepton2_eta = childl2->eta();
                                    lepton2_phi = childl2->phi();
                                    lepton3_eta = childl3->eta();
                                    lepton3_phi = childl3->phi();
                                    lepton4_eta = childl4->eta();
                                    lepton4_phi = childl4->phi();
                                    lepton5_eta = childl5->eta();
                                    lepton6_phi = childl5->phi();
                                    lepton6_eta = childl6->eta();
                                    lepton6_phi = childl6->phi();
                                    lepton7_eta = childl7->eta();
                                    lepton7_phi = childl7->phi();
                                    lepton8_eta = childl8->eta();
                                    lepton8_phi = childl8->phi();
                                    */
                                }//close lepton stability check
                            }//close Zd decay check
                        }//close Zd check
                    }//close S decay check                 
                    
                }//close S check
            }//close Higgs decay check
        }//close Higgs check

        //Stats for all cases combined
        //Basic MET try
        //for ( auto MissingET : *truth_MET ){hist ("h_missingET")->Fill (MissingET->sumet()/1000);}
        
        //Separating 44 and 22 cases
        int bitmask = pow(2,3)*l1_bool + pow(2,2)*l3_bool + pow(2,1)*l5_bool + pow(2,0)*l7_bool;

        // Iterate through numbers 0 to 15
        for (int i = 0; i <= 15; ++i) {
            // If i is equal to bitmask, increment the corresponding bit_i variable
            if (i == bitmask) {
                switch (i) {
                    case 0: bit_0++; break;
                    case 1: bit_1++; break;
                    case 2: bit_2++; break;
                    case 3: bit_3++; break;
                    case 4: bit_4++; break;
                    case 5: bit_5++; break;
                    case 6: bit_6++; break;
                    case 7: bit_7++; break;
                    case 8: bit_8++; break;
                    case 9: bit_9++; break;
                    case 10: bit_10++; break;
                    case 11: bit_11++; break;
                    case 12: bit_12++; break;
                    case 13: bit_13++; break;
                    case 14: bit_14++; break;
                    case 15: bit_15++; break;
                    default:
                        std::cerr << "Invalid value of i: " << i << std::endl;
                }
            }
        }


        //ANA_MSG_INFO(l1_bool << l2_bool << l3_bool << l4_bool << l5_bool << l6_bool << l7_bool << l8_bool);
        //check 44 case
        if (bitmask == 3 || bitmask == 12 ){
            l_multiplicity ++;
            l_multiplicity_44 ++;
            //ANA_MSG_INFO("----- 44 case ------ " << bitmask);
            //R_56 = calc_delta_R(lepton5_eta, lepton6_eta, lepton5_phi, lepton6_phi);
            //R_57 = calc_delta_R(lepton5_eta, lepton7_eta, lepton5_phi, lepton7_phi);
            //R_58 = calc_delta_R(lepton5_eta, lepton8_eta, lepton5_phi, lepton8_phi);
            //R_67 = calc_delta_R(lepton6_eta, lepton7_eta, lepton6_phi, lepton7_phi);
            //R_68 = calc_delta_R(lepton6_eta, lepton8_eta, lepton6_phi, lepton8_phi);
            //R_78 = calc_delta_R(lepton7_eta, lepton8_eta, lepton7_phi, lepton8_phi);
            
            /*
            Leptons are: 
            childl1, childl2, childl3, childl4
            childl3, childl4, childl7, childl8
            Pairings are 12, 13, 14, 23, 24, 34
                            56, 57, 58, 67, 68, 78
            */
            //Check for 1234 case
            if (bitmask == 3){
                l_multiplicity_3 ++;

            }
            //Check for 5678 case. Pairs are: 56, 57, 58, 67, 68, 78
            if (bitmask == 12){
                l_multiplicity_12 ++;
                
            }// close 5678 check
            
        }// Close 44 bitmask

        //check 22 case
        if (bitmask == 5 || bitmask == 6 || bitmask == 9 || bitmask == 10 ){
            l_multiplicity ++;
            l_multiplicity_22 ++;
            l_multiplicity_5 ++;
            //ANA_MSG_INFO("----- 22 ------ " << bitmask);
            /*
            R_34 = calc_delta_R(lepton5_eta, lepton6_eta, lepton5_phi, lepton6_phi);
            R_57 = calc_delta_R(lepton5_eta, lepton7_eta, lepton5_phi, lepton7_phi);
            R_58 = calc_delta_R(lepton5_eta, lepton8_eta, lepton5_phi, lepton8_phi);
            R_67 = calc_delta_R(lepton6_eta, lepton7_eta, lepton6_phi, lepton7_phi);
            R_68 = calc_delta_R(lepton6_eta, lepton8_eta, lepton6_phi, lepton8_phi);
            R_78 = calc_delta_R(lepton7_eta, lepton8_eta, lepton7_phi, lepton8_phi);
            
            Leptons are: 
            childl3
            childl4
            childl7
            childl8
            Pairings are 34, 37, 38, 47, 48, 78
            *This may end up being different at non-truth level*
            */

            
        }//Close 22 bitmask
        
    }//close for loop


    return StatusCode::SUCCESS;
}//close execute loop



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

//    ATH_MSG_INFO( "STAT Statistics on " << n_events << " processed events" );
//    std::cout << "\n\n\n\n\n\n -------------------------------------------\n";
//    std::cout << "Dark Photons found:\t" << nDarkPhoton << "\n";
//    std::cout << "Parents processed:\t" << nParentsProcessed << "\n";
//    std::cout << "fd2 found:\t" << nfd1 << "\n";
//    std::cout << "fd1 found:\t" << nfd1 << "\n";
//    std::cout << "hs found:\t" << nhs << "\n";
//    std::cout << "higgs found:\t" << nhiggs << "\n";
//    std::cout << "Decaying to electrons:\t" << nToElectrons << " (" << 100 * nToElectrons/nDarkPhoton << "%)\n";
//    std::cout << "Decaying to muons:\t" << nToMuons << " (" << 100 * nToMuons/nDarkPhoton << "%)\n";
//    std::cout << "Decaying to taus:\t" << nToTaus << " (" << 100 * nToTaus/nDarkPhoton << "%)\n";
//    std::cout << "Decaying to quarks:\t" << nToQuarks << " (" << 100 * nToQuarks/nDarkPhoton << "%)\n";
// ANA_MSG_INFO(n_events << " Events found");
ANA_MSG_INFO("44 case total events " << l_multiplicity_44);
ANA_MSG_INFO("44-12 case events " << l_multiplicity_12);
ANA_MSG_INFO("44-3 case events " << l_multiplicity_3);
ANA_MSG_INFO("22-5 case events " << l_multiplicity_5);
ANA_MSG_INFO("22 case total events " << l_multiplicity_22);
ANA_MSG_INFO("44 and 22 combined events " << l_multiplicity);
ANA_MSG_INFO(n_Higgs << " Higgs found");
ANA_MSG_INFO(n_S << " times two S found");
ANA_MSG_INFO(n_Zd << " times four S found");
ANA_MSG_INFO(n_childl1 << " Childl1's found");
ANA_MSG_INFO(n_childl2 << " childl2's found");
ANA_MSG_INFO(n_childl3 << " childl3's found");
ANA_MSG_INFO(n_childl4 << " childl4's found");
ANA_MSG_INFO(n_childl5 << " childl5's found");
ANA_MSG_INFO(n_childl6 << " childl6's found");
ANA_MSG_INFO(n_childl7 << " childl7's found");
ANA_MSG_INFO(n_childl8 << " childl8's found");

// Output the values of the variables
std::cout << "bit_0: " << bit_0 << std::endl;
std::cout << "bit_1: " << bit_1 << std::endl;
std::cout << "bit_2: " << bit_2 << std::endl;
std::cout << "bit_3: " << bit_3 << std::endl;
std::cout << "bit_4: " << bit_4 << std::endl;
std::cout << "bit_5: " << bit_5 << std::endl;
std::cout << "bit_6: " << bit_6 << std::endl;
std::cout << "bit_7: " << bit_7 << std::endl;
std::cout << "bit_8: " << bit_8 << std::endl;
std::cout << "bit_9: " << bit_9 << std::endl;
std::cout << "bit_10: " << bit_10 << std::endl;
std::cout << "bit_11: " << bit_11 << std::endl;
std::cout << "bit_12: " << bit_12 << std::endl;
std::cout << "bit_13: " << bit_13 << std::endl;
std::cout << "bit_14: " << bit_14 << std::endl;
std::cout << "bit_15: " << bit_15 << std::endl;

    std::cout << "\n\n\n";
    return StatusCode::SUCCESS;
}