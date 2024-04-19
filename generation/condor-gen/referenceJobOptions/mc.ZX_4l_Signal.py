mzd = <ZdMass_Gev>
mh = <scalarMass_Gev>

# JO for Release 21 based on the template: https://gitlab.cern.ch/atlas-physics/pmg/mcjoboptions/blob/master/950xxx/950116/mc.MGPy8EG_A14NNPDF23_ttbar_Incl_valid.py
# Additional doc included in: https://twiki.cern.ch/twiki/bin/view/AtlasProtected/MadGraph5aMCatNLOForAtlas#LO_Pythia8_Showering

import MadGraphControl.MadGraph_NNPDF30NLOnf4_Base_Fragment
from MadGraphControl.MadGraphUtils import *

nevents = runArgs.maxEvents*1.1 if runArgs.maxEvents>0 else 1.1*evgenConfig.nEventsPerJob

process = """
import model HAHM_variableMW_v3_UFO
define l+ = e+ mu+
define l- = e- mu-
define j = u c d s b u~ c~ d~ s~ b~
generate g g > h HIG=1 HIW=0 QED=0 QCD=0, (h > Z Zp, Z > l+ l-, Zp > l+ l-)
output -f"""

#define j = u c d s u~ c~ d~ s~ b b~
#generate g g > h HIG=1 HIW=0 QED=0 QCD=0, (h > Zp Zp, Zp > l+ l-, Zp > j j)
#generate g g > h HIG=1 HIW=0 QED=0 QCD=0, (h > Zp Zp > l+ l- j j)
#define intermediateboson = h Z Zp

process_dir = new_process(process)

#Fetch default LO run_card.dat and set parameters
settings = {'lhe_version':'2.0',
            'cut_decays' :'F',
                   'ptj':'0',
                   'ptb':'0',
                   'pta':'0',
                   'ptl':'0',
                   'etaj':'-1',
                   'etab':'-1',
                   'etaa':'-1',
                   'etal':'-1',
                   'drjj':'0',
                   'drbb':'0',
                   'drll':'0',
                   'draa':'0',
                   'drbj':'0',
                   'draj':'0',
                   'drjl':'0',
                   'drab':'0',
                   'drbl':'0',
                   'dral':'0',
            'nevents':int(nevents)}

settings_param_card = { "HIDDEN": { 'epsilon': '1e-4', #kinetic mixing parameter
                                 'kap': '1e-10', #higgs mixing parameter
                                 'mzdinput': mzd, #Zd mass
                                 'mhsinput': '200.0' }, #dark higgs mass
                     "HIGGS": { 'mhinput': mh }, #higgs mass
                     "DECAY": { 'wzp':'Auto', 'wh':'Auto', 'wt':'Auto' } #auto-calculate decay widths and BR of Zp, H, t
                  }

modify_param_card(process_dir=process_dir,params=settings_param_card)

modify_run_card(process_dir=process_dir,runArgs=runArgs,settings=settings)
            
generate(process_dir=process_dir,runArgs=runArgs)

arrange_output(process_dir=process_dir,runArgs=runArgs,lhe_version=3,saveProcDir=True)

#### Shower
evgenConfig.description="MadGraph Hidden Abelian Higgs Model (HAHM): gg -> H -> ZdZd -> 4l (l=e,mu) , with mZd=<ZdMass_Gev>GeV"
evgenConfig.keywords+=['exotic','BSMHiggs']
evgenConfig.contact = ['c.weber@cern.ch']

include("Pythia8_i/Pythia8_A14_NNPDF23LO_EvtGen_Common.py")
include("Pythia8_i/Pythia8_MadGraph.py")
#include("Pythia8_i/Pythia8_aMcAtNlo.py")
