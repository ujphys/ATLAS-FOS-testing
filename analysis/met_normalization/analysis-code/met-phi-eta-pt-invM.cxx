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

    //Progenitor (H)
    ANA_CHECK (book (TH1D("h_m_H", "h_m_H", 100, 0, 900)));
    ANA_CHECK (book (TH1D("h_pT_H", "h_pT_H", 100, 0, 500)));
    ANA_CHECK (book (TH1D("h_eta_H","h_eta_H", 100, -4.5, 4.5)));
    ANA_CHECK (book (TH1D("h_phi_H", "h_phi_H", 100, -4.5, 4.5)));
    //Additional Scalar (S)
    ANA_CHECK (book (TH1D("h_m_S1", "h_m_S1", 100, 0, 200)));
    ANA_CHECK (book (TH1D("h_m_S2", "h_m_S2", 100, 0, 200)));
    ANA_CHECK (book (TH1D("h_pT_S1", "h_pT_S1", 100, 0, 500)));
    ANA_CHECK (book (TH1D("h_pT_S2", "h_pT_S2", 100, 0, 500)));
    ANA_CHECK (book (TH1D("h_eta_S1","h_eta_S1", 100, -4.5, 4.5)));
    ANA_CHECK (book (TH1D("h_eta_S2","h_eta_S2", 100, -4.5, 4.5)));
    ANA_CHECK (book (TH1D("h_phi_S1", "h_phi_S1", 100, -4.5, 4.5)));
    ANA_CHECK (book (TH1D("h_phi_S2", "h_phi_S2", 100, -4.5, 4.5)));
    //Dark Vector Boson (Zd)
    ANA_CHECK (book (TH1D("h_m_Zd1", "h_m_Zd1", 100, 0, 200)));
    ANA_CHECK (book (TH1D("h_m_Zd2", "h_m_Zd2", 100, 0, 200)));
    ANA_CHECK (book (TH1D("h_m_Zd3", "h_m_Zd3", 100, 0, 200)));
    ANA_CHECK (book (TH1D("h_m_Zd4", "h_m_Zd4", 100, 0, 200)));
    ANA_CHECK (book (TH1D("h_pT_Zd1", "h_pT_Zd1", 100, 0, 500)));
    ANA_CHECK (book (TH1D("h_pT_Zd2", "h_pT_Zd2", 100, 0, 500)));
    ANA_CHECK (book (TH1D("h_pT_Zd3", "h_pT_Zd3", 100, 0, 500)));
    ANA_CHECK (book (TH1D("h_pT_Zd4", "h_pT_Zd4", 100, 0, 500)));
    ANA_CHECK (book (TH1D("h_eta_Zd1","h_eta_Zd1", 100, -4.5, 4.5)));
    ANA_CHECK (book (TH1D("h_eta_Zd2","h_eta_Zd2", 100, -4.5, 4.5)));
    ANA_CHECK (book (TH1D("h_eta_Zd3","h_eta_Zd3", 100, -4.5, 4.5)));
    ANA_CHECK (book (TH1D("h_eta_Zd4","h_eta_Zd4", 100, -4.5, 4.5)));
    ANA_CHECK (book (TH1D("h_phi_Zd1", "h_phi_Zd1", 100, -4.5, 4.5)));
    ANA_CHECK (book (TH1D("h_phi_Zd2", "h_phi_Zd2", 100, -4.5, 4.5)));
    ANA_CHECK (book (TH1D("h_phi_Zd3", "h_phi_Zd3", 100, -4.5, 4.5)));
    ANA_CHECK (book (TH1D("h_phi_Zd4", "h_phi_Zd4", 100, -4.5, 4.5)));
    //Visible leptons (l/e/u)
    ANA_CHECK (book (TH1D("h_pT_e1", "h_pT_e1", 100, 0, 500))); ANA_CHECK (book (TH1D("h_pT_u1", "h_pT_u1", 100, 0, 500)));
    ANA_CHECK (book (TH1D("h_pT_e2", "h_pT_e2", 100, 0, 500))); ANA_CHECK (book (TH1D("h_pT_u2", "h_pT_u2", 100, 0, 500)));
    ANA_CHECK (book (TH1D("h_pT_e3", "h_pT_e3", 100, 0, 500))); ANA_CHECK (book (TH1D("h_pT_u3", "h_pT_u3", 100, 0, 500)));
    ANA_CHECK (book (TH1D("h_pT_e4", "h_pT_e4", 100, 0, 500))); ANA_CHECK (book (TH1D("h_pT_u4", "h_pT_u4", 100, 0, 500)));
    ANA_CHECK (book (TH1D("h_eta_e1","h_eta_e1", 100, -4.5, 4.5))); ANA_CHECK (book (TH1D("h_eta_u1","h_eta_u1", 100, -4.5, 4.5)));
    ANA_CHECK (book (TH1D("h_eta_e2","h_eta_e2", 100, -4.5, 4.5))); ANA_CHECK (book (TH1D("h_eta_u2","h_eta_u2", 100, -4.5, 4.5)));
    ANA_CHECK (book (TH1D("h_eta_e3","h_eta_e3", 100, -4.5, 4.5))); ANA_CHECK (book (TH1D("h_eta_u3","h_eta_u3", 100, -4.5, 4.5)));
    ANA_CHECK (book (TH1D("h_eta_e4","h_eta_e4", 100, -4.5, 4.5))); ANA_CHECK (book (TH1D("h_eta_u4","h_eta_u4", 100, -4.5, 4.5)));
    ANA_CHECK (book (TH1D("h_phi_e1","h_phi_e1", 100, -4.5, 4.5))); ANA_CHECK (book (TH1D("h_phi_u1","h_phi_u1", 100, -4.5, 4.5)));
    ANA_CHECK (book (TH1D("h_phi_e2","h_phi_e2", 100, -4.5, 4.5))); ANA_CHECK (book (TH1D("h_phi_u2","h_phi_u2", 100, -4.5, 4.5)));
    ANA_CHECK (book (TH1D("h_phi_e3","h_phi_e3", 100, -4.5, 4.5))); ANA_CHECK (book (TH1D("h_phi_u3","h_phi_u3", 100, -4.5, 4.5)));
    ANA_CHECK (book (TH1D("h_phi_e4","h_phi_e4", 100, -4.5, 4.5))); ANA_CHECK (book (TH1D("h_phi_u4","h_phi_u4", 100, -4.5, 4.5)));
    //MET
    ANA_CHECK (book (TH1F("h_missingET","h_missingET",100,0,1000)));
    ANA_CHECK (book (TH1D("h_missingET_NonInt","h_missingET_NonInt",100,0,1000)));

    return StatusCode::SUCCESS;
}

// Initialize counting variables
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

// Initialize Kinematic variables //
double m_H, pT_H, eta_H, phi_H;
double m_S1, m_S2, pT_S1, pT_S2, eta_S1, eta_S2, phi_S1, phi_S2;
double m_Zd1, m_Zd2, m_Zd3, m_Zd4, pT_Zd1, pT_Zd2, pT_Zd3, pT_Zd4, eta_Zd1, eta_Zd2, eta_Zd3, eta_Zd4, phi_Zd1, phi_Zd2, phi_Zd3, phi_Zd4;
double pT_e1, pT_e2, pT_e3, pT_e4, eta_e1, eta_e2, eta_e3, eta_e4, phi_e1, phi_e2, phi_e3, phi_e4;
double pT_u1, pT_u2, pT_u3, pT_u4, eta_u1, eta_u2, eta_u3, eta_u4, phi_u1, phi_u2, phi_u3, phi_u4;

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

    xAOD::TruthParticleContainer::const_iterator truth_itr = truthContainer->begin();
    xAOD::TruthParticleContainer::const_iterator truth_end = truthContainer->end();


    // Loop over TruthParticle
    for( ; truth_itr != truth_end ; ++truth_itr){

        /*------------------------ SECTION 1 - FIND PARTICLES, GET KINEMATICS ------------------------*/
        const xAOD::TruthParticle* truth = *truth_itr;
        //Initialize bitmask variables
        bool l1_bool, l3_bool, l5_bool, l7_bool = false;

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

                //------------Label the 1st gen children (dark Higgs)------------
                const xAOD::TruthParticle* childS1 = decayVtx->outgoingParticle(0);
                const xAOD::TruthParticle* childS2 = decayVtx->outgoingParticle(1);
                //Check the Higgs has decayed to dark Higgs
                if ( (childS1->absPdgId() == 35) && (childS2->absPdgId() == 35)){
                    //ANA_MSG_INFO("Dark Higgs found, child of the Higgs");
                    //Once we know the Higgs decays to two S, we store its kinematics
                    m_H = truth -> m();
                    pT_H = truth -> pt();
                    eta_H = truth -> eta();
                    phi_H = truth -> phi();
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
                            //Once we know each S decays to two Zd, we store their kinematics
                            m_S1 = childS1 -> m(); m_S2 = childS2 -> m();
                            pT_S1 = childS1 -> pt(); pT_S2 = childS2 -> pt();
                            eta_S1 = childS1 -> eta(); eta_S2 = childS2 -> eta();
                            phi_S1 = childS1 -> phi(); phi_S2 = childS2 -> phi();
                            //Check both Zd children have decay verteces
                            if ( childZd1->hasDecayVtx() && childZd2->hasDecayVtx() && childZd3->hasDecayVtx() && childZd4->hasDecayVtx() ){
                                const xAOD::TruthVertex* Zd1_decayVtx = childZd1->decayVtx();
                                const xAOD::TruthVertex* Zd2_decayVtx = childZd2->decayVtx();
                                const xAOD::TruthVertex* Zd3_decayVtx = childZd3->decayVtx();
                                const xAOD::TruthVertex* Zd4_decayVtx = childZd4->decayVtx();
                                ANA_MSG_INFO("Four Zd found");
                                n_Zd++;

                                m_Zd1 = childZd1 -> m(); m_Zd2 = childZd2 -> m(); m_Zd3 = childZd3 -> m(); m_Zd4 = childZd4 -> m();
                                pT_Zd1 = childZd1 -> pt(); pT_Zd2 = childZd2 -> pt(); pT_Zd3 = childZd3 -> pt(); pT_Zd4 = childZd4 -> pt();
                                eta_Zd1 = childZd1 -> eta(); eta_Zd2 = childZd2 -> eta(); eta_Zd3 = childZd3 -> eta(); eta_Zd4 = childZd4 -> eta();
                                phi_Zd1 = childZd1 -> phi(); phi_Zd2 = childZd2 -> phi(); phi_Zd3 = childZd3 -> phi(); phi_Zd4 = childZd4 -> phi();
                                //------------Label the 3rd gen children (leptons)------------
                                const xAOD::TruthParticle* childl1 = Zd1_decayVtx->outgoingParticle(0);
                                const xAOD::TruthParticle* childl2 = Zd1_decayVtx->outgoingParticle(1);
                                const xAOD::TruthParticle* childl3 = Zd2_decayVtx->outgoingParticle(0);
                                const xAOD::TruthParticle* childl4 = Zd2_decayVtx->outgoingParticle(1);
                                const xAOD::TruthParticle* childl5 = Zd3_decayVtx->outgoingParticle(0);
                                const xAOD::TruthParticle* childl6 = Zd3_decayVtx->outgoingParticle(1);
                                const xAOD::TruthParticle* childl7 = Zd4_decayVtx->outgoingParticle(0);
                                const xAOD::TruthParticle* childl8 = Zd4_decayVtx->outgoingParticle(1);

                                //We know these leptons will always be OSSF pairs, we only need to check 1 of each pair
                                //Set bitmask
                                if (childl1->absPdgId()==11 || childl1->absPdgId()==13){l1_bool = true;}
                                //if (childl2->absPdgId()==11 || childl2->absPdgId()==13){l2_bool = true;}
                                if (childl3->absPdgId()==11 || childl3->absPdgId()==13){l3_bool = true;}
                                //if (childl4->absPdgId()==11 || childl4->absPdgId()==13){l4_bool = true;}
                                if (childl5->absPdgId()==11 || childl5->absPdgId()==13){l5_bool = true;}
                                //if (childl6->absPdgId()==11 || childl6->absPdgId()==13){l6_bool = true;}
                                if (childl7->absPdgId()==11 || childl7->absPdgId()==13){l7_bool = true;}
                                //if (childl8->absPdgId()==11 || childl8->absPdgId()==13){l8_bool = true;}

                                //Visible lepton kinematics
                                //We also know that only leptons 1-4 will be e/u, while 5-8 while be v
                                if (childl1->absPdgId()==11){
                                    pT_e1 = childl1 -> pt(); pT_e2 = childl2 -> pt();
                                    eta_e1 = childl1 -> eta(); eta_e2 = childl2 -> eta();
                                    phi_e1 = childl1 -> phi(); phi_e2 = childl2 -> phi();
                                }
                                if (childl3->absPdgId()==11){
                                    pT_e3 = childl3 -> pt(); pT_e4 = childl4 -> pt();
                                    eta_e3 = childl3 -> eta(); eta_e4 = childl4 -> eta();
                                    phi_e3 = childl3 -> phi(); phi_e4 = childl4 -> phi();
                                }
                                if (childl1->absPdgId()==13){
                                    pT_u1 = childl1 -> pt(); pT_u2 = childl2 -> pt();
                                    eta_u1 = childl1 -> eta(); eta_u2 = childl2 -> eta();
                                    phi_u1 = childl1 -> phi(); phi_u2 = childl2 -> phi();
                                }
                                if (childl3->absPdgId()==13){
                                    pT_u3 = childl3 -> pt(); pT_u4 = childl4 -> pt();
                                    eta_u3 = childl3 -> eta(); eta_u4 = childl4 -> eta();
                                    phi_u3 = childl3 -> phi(); phi_u4 = childl4 -> phi();
                                }
                            }//close Zd decay check
                        }//close Zd check
                    }//close S decay check                 
                    
                }//close S check
            }//close Higgs decay check
        }//close Higgs check
        
        /*------------------------ SECTION 2 - BITMASK AND FILL HISTOGRAMS ------------------------*/

        //Calculate bitmask value: allows us to separate 44 and 22 cases
        int bitmask = pow(2,3)*l1_bool + pow(2,2)*l3_bool + pow(2,1)*l5_bool + pow(2,0)*l7_bool;

        //ANA_MSG_INFO(l1_bool << l2_bool << l3_bool << l4_bool << l5_bool << l6_bool << l7_bool << l8_bool);
        //check 44 case
        if (bitmask == 3 || bitmask == 12 ){
            l_multiplicity ++;
            l_multiplicity_44 ++;
            if (bitmask == 3){
                l_multiplicity_3 ++;
            }
            //Check for 5678 case. Pairs are: 56, 57, 58, 67, 68, 78
            if (bitmask == 12){
                l_multiplicity_12 ++;    
            }// close 5678 check

            //------------ Fill Kinematic Hists ------------//
            //H
            hist ("h_m_H")->Fill (m_H/1000);
            hist ("h_phi_H")->Fill (phi_H);
            hist ("h_eta_H")->Fill (eta_H);
            hist ("h_pT_H")->Fill (pT_H/1000);
            //S
            hist ("h_m_S1")->Fill (m_S1/1000); hist ("h_m_S2")->Fill (m_S2/1000);
            hist ("h_phi_S1")->Fill (phi_S1); hist ("h_phi_S2")->Fill (phi_S2);
            hist ("h_eta_S1")->Fill (eta_S1); hist ("h_eta_S2")->Fill (eta_S2);
            hist ("h_pT_S1")->Fill (pT_S1/1000); hist ("h_pT_S2")->Fill (pT_S2/1000);
            //Zd
            hist ("h_m_Zd1")->Fill (m_Zd1/1000); hist ("h_m_Zd2")->Fill (m_Zd2/1000); hist ("h_m_Zd3")->Fill (m_Zd3/1000); hist ("h_m_Zd4")->Fill (m_Zd4/1000);
            hist ("h_phi_Zd1")->Fill (phi_Zd1); hist ("h_phi_Zd2")->Fill (phi_Zd2); hist ("h_phi_Zd3")->Fill (phi_Zd3); hist ("h_phi_Zd4")->Fill (phi_Zd4);
            hist ("h_eta_Zd1")->Fill (eta_Zd1); hist ("h_eta_Zd2")->Fill (eta_Zd2); hist ("h_eta_Zd3")->Fill (eta_Zd3); hist ("h_eta_Zd4")->Fill (eta_Zd4);
            hist ("h_pT_Zd1")->Fill (pT_Zd1/1000); hist ("h_pT_Zd2")->Fill (pT_Zd2/1000); hist ("h_pT_Zd3")->Fill (pT_Zd3/1000); hist ("h_pT_Zd4")->Fill (pT_Zd4/1000);
            //Electrons
            hist ("h_phi_e1")->Fill (phi_e1); hist ("h_phi_e2")->Fill (phi_e2); hist ("h_phi_e3")->Fill (phi_e3); hist ("h_phi_e4")->Fill (phi_e4);
            hist ("h_eta_e1")->Fill (eta_e1); hist ("h_eta_e2")->Fill (eta_e2); hist ("h_eta_e3")->Fill (eta_e3); hist ("h_eta_e4")->Fill (eta_e4);
            hist ("h_pT_e1")->Fill (pT_e1/1000); hist ("h_pT_e2")->Fill (pT_e2/1000); hist ("h_pT_e3")->Fill (pT_e3/1000); hist ("h_pT_e4")->Fill (pT_e4/1000);
            //Muons
            hist ("h_phi_u1")->Fill (phi_u1); hist ("h_phi_u2")->Fill (phi_u2); hist ("h_phi_u3")->Fill (phi_u3); hist ("h_phi_u4")->Fill (phi_u4);
            hist ("h_eta_u1")->Fill (eta_u1); hist ("h_eta_u2")->Fill (eta_u2); hist ("h_eta_u3")->Fill (eta_u3); hist ("h_eta_u4")->Fill (eta_u4);
            hist ("h_pT_u1")->Fill (pT_u1/1000); hist ("h_pT_u2")->Fill (pT_u2/1000); hist ("h_pT_u3")->Fill (pT_u3/1000); hist ("h_pT_u4")->Fill (pT_u4/1000);
            //Non-interacting MET
            const xAOD::MissingET* truthMET_NonInt = nullptr;
            truthMET_NonInt = (*truth_MET)["NonInt"];
            hist ("h_missingET_NonInt")->Fill (truthMET_NonInt->met()/1000);
            for ( auto MissingET : *truth_MET ){ hist ("h_missingET")->Fill (MissingET->sumet()/1000); } //Basic MET
        }// Close 44 bitmask

        //check 22 case
        if (bitmask == 5 || bitmask == 6 || bitmask == 9 || bitmask == 10 ){
            l_multiplicity ++;
            l_multiplicity_22 ++;
            l_multiplicity_5 ++;            
        }//Close 22 bitmask
        
    }//close for loop

    //Scaling Histograms
    // std::cout << "Method 1: fill then scale" << std::endl; //The scaled histogram doesn't seem to save so we are left with the original
    // h_missingET_Yscaled1->Scale(norm_factor);
    // std::cout << "Method 2: set to NonInt then scale" << std::endl;
    // h_missingET_Yscaled2 = h_missingET_NonInt; //This histogram ends up empty
    // h_missingET_Yscaled2->Scale(norm_factor);
    // std::cout << "Scaling Done" << std::endl;

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

    std::cout << "Bitmask 3:\t" << l_multiplicity_3 << "\n";
    std::cout << "Bitmask 12:\t" << l_multiplicity_12 << "\n";
    std::cout << "Total 44:\t" << l_multiplicity_44 << "\n";

    std::cout << "\n\n\n";
    return StatusCode::SUCCESS;
}
