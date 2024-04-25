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

    //Mass
    // ANA_CHECK (book (TH1F("h_H_Mass","h_H_Mass",100,0,1000)));

    //MET
    //ANA_CHECK (book (TH1F("h_missingET_other","h_missingET_other",100,0,1000)));
    //ANA_CHECK (book (TH1F("h_MET_boost","h_MET_boost",100,0,500)));
    ANA_CHECK (book (TH1F("h_missingET","h_missingET",100,0,1000)));
    ANA_CHECK (book (TH1F("h_missingET_Xscaled","h_missingET_Xscaled",100,0,25)));

    ANA_CHECK (book (TH1D("h_missingET_NonInt","h_missingET_NonInt",100,0,1000)));
    ANA_CHECK (book (TH1D("h_missingET_Yscaled1","h_missingET_Yscaled1",100,0,1000)));
    ANA_CHECK (book (TH1D("h_missingET_Yscaled2","h_missingET_Yscaled2",100,0,1000)));

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

const double norm_factor = 0.068729566; //300GeV
// const double norm_factor = 0.221057757; //350GeV
// const double norm_factor = 0.237594439; //400GeV
// const double norm_factor = 0.169728543; //450GeV
// const double norm_factor = 0.109833669; //500GeV
// const double norm_factor = 0.069514033; //550GeV
// const double norm_factor = 0.04661499; //600GeV
// const double norm_factor = 0.030499267; //650GeV
// const double norm_factor = 0.021510573; //700GeV
// const double norm_factor = 0.014793756; //750GeV
// const double norm_factor = 0.010123407; //800GeV

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

        /*------------------------ SECTION 1 - FIND PARTICLES, GET KINEMATICS ------------------------*/
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
                //Fill mass histogram for Higgs
                // hist ("h_H_Mass")->Fill (truth->mass());

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
                                const xAOD::TruthParticle* childl2 = Zd1_decayVtx->outgoingParticle(1);
                                const xAOD::TruthParticle* childl3 = Zd2_decayVtx->outgoingParticle(0);
                                const xAOD::TruthParticle* childl4 = Zd2_decayVtx->outgoingParticle(1);
                                const xAOD::TruthParticle* childl5 = Zd3_decayVtx->outgoingParticle(0);
                                const xAOD::TruthParticle* childl6 = Zd3_decayVtx->outgoingParticle(1);
                                const xAOD::TruthParticle* childl7 = Zd4_decayVtx->outgoingParticle(0);
                                const xAOD::TruthParticle* childl8 = Zd4_decayVtx->outgoingParticle(1);
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
                                    /**/
                                }//close lepton stability check
                            }//close Zd decay check
                        }//close Zd check
                    }//close S decay check                 
                    
                }//close S check
            }//close Higgs decay check
        }//close Higgs check


        
        /*------------------------ SECTION 2 - BITMASK AND FILL HISTOGRAMS ------------------------*/
        //for ( auto MissingET : *truth_MET ){hist ("h_missingET")->Fill (MissingET->sumet()/1000);} //Get simple MET

        //Separating 44 and 22 cases
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

            //Non-interacting MET
            const xAOD::MissingET* truthMET_NonInt = nullptr;
            truthMET_NonInt = (*truth_MET)["NonInt"];
            hist ("h_missingET_NonInt")->Fill (truthMET_NonInt->met()/1000);
            hist ("h_missingET_Yscaled1")->Fill (truthMET_NonInt->met()/1000);
            //Basic MET try
            for ( auto MissingET : *truth_MET )
                {double MET_GeV = MissingET->sumet()/1000;
                double scaled_MET = MET_GeV * norm_factor;
                hist ("h_missingET")->Fill (MET_GeV);
                std::cout << "Filling-44-case, NF = " << norm_factor << std::endl;
                hist ("h_missingET_Xscaled")->Fill (scaled_MET);
                // hist ("h_missingET_Yscaled")->Fill (scaled_MET);
                }//Close MET loop
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

    std::cout << "\n\n\n";
    return StatusCode::SUCCESS;
}
