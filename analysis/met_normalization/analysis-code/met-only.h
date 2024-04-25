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

