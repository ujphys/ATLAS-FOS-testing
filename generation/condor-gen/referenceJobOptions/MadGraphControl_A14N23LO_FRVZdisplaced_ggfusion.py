from MadGraphControl.MadGraphUtils import *

if hasattr(runArgs,'ecmEnergy'):
    beamEnergy = runArgs.ecmEnergy / 2.
else:
    beamEnergy = 6500.

# MadGraph info
process = {
    2:  'generate g g > h > chi2 chi2, (chi2 > chi1 zp, zp > f- f+), (chi2 > chi1 zp, zp > f- f+)' ,
    4:  'generate g g > h > chi2 chi2, (chi2 > chi1 hs, (hs > zp zp, zp > f- f+)), (chi2 > chi1 hs, (hs > zp zp, zp > f- f+))'
    }
modelcode = 'iDM'
rcard='MadGraph_run_card_FRVZdisplaced.dat'
pcard='MadGraph_param_card_FRVZdisplaced_mZd_mH.dat' 
rname = 'run_lj'

# initialise random number generator/sequence
import random
random.seed(runArgs.randomSeed)

# lifetime function
def lifetime(avgtau = 21):
    import math
    t = random.random()
    return -1.0 * avgtau * math.log(t)

# do not run MadGraph if config only is requested
if not opts.config_only:
    # writing proc card for MG
    fcard = open('proc_card_mg5.dat','w')
    if decayMode == "normal":
        fcard.write("""
import model --modelname %s
define f- = e- m- 
define f+ = e+ m+ 
%s
output -f
""" % (modelcode, process[nGamma]))
    elif decayMode == "quarks":
        fcard.write("""
import model --modelname %s
define f- = d s u~ c~
define f+ = d~ s~ u c
%s
output -f
""" % (modelcode, process[nGamma]))
    elif decayMode == "electrons":
        fcard.write("""
import model --modelname %s
define f- = e-
define f+ = e+
%s
output -f
""" % (modelcode, process[nGamma]))

    fcard.close()

    # getting run cards
    from PyJobTransformsCore.trfutil import get_files
    import subprocess
    get_dat_file = subprocess.Popen(['get_files','-jo', rcard])
    get_dat_file.wait()
    get_dat_file = subprocess.Popen(['get_files','-jo', pcard])
    get_dat_file.wait()

    # generating events in MG
    process_dir = new_process()
    generate(run_card_loc=rcard,param_card_loc=pcard,mode=0,njobs=1,run_name=rname,proc_dir=process_dir)

    # hacking LHE file
    unzip1 = subprocess.Popen(['gunzip',process_dir+'/Events/'+rname+'/unweighted_events.lhe.gz'])
    unzip1.wait()
    oldlhe = open(process_dir+'/Events/'+rname+'/unweighted_events.lhe','r')
    newlhe = open(process_dir+'/Events/'+rname+'/unweighted_events2.lhe','w')

    init = True

    for line in oldlhe:
        if init==True:
            if '30000016' in line:
                line = line.replace('30000016','3000016')
            elif '30000015' in line:
                line = line.replace('30000015','1000022')
            newlhe.write(line)
            if '</init>' in line:
                init = False
        else:
            newline=line.rstrip('\n')
            columns=newline.split()
            pdgid=columns[0]

            if pdgid == '3000001' and avgtau>0:
                part1 = line[:-22]
                part2 = "%.5e" % (lifetime(avgtau))
                part3 = line[-12:]
                newlhe.write(part1+part2+part3)

            elif (pdgid == '-30000016') :
                part1 = ' -3000016'
                part2 = line[10:]
                newlhe.write(part1+part2)
            elif (pdgid == '30000016') :
                part1 = '  3000016'
                part2 = line[10:]
                newlhe.write(part1+part2)
            elif (pdgid == '-30000015') :
                part1 = ' -1000022'
                part2 = line[10:]
                newlhe.write(part1+part2)
            elif (pdgid == '30000015') :
                part1 = '  1000022'
                part2 = line[10:]
                newlhe.write(part1+part2)
            else:
                newlhe.write(line)
        
    oldlhe.close()
    newlhe.close()
    
    # re-zipping hacked LHE
    zip1 = subprocess.Popen(['gzip',process_dir+'/Events/'+rname+'/unweighted_events2.lhe'])
    zip1.wait()
    shutil.move(process_dir+'/Events/'+rname+'/unweighted_events2.lhe.gz',process_dir+'/Events/'+rname+'/unweighted_events.lhe.gz')
    os.remove(process_dir+'/Events/'+rname+'/unweighted_events.lhe')

    arrange_output(run_name=rname,proc_dir=process_dir,outputDS=rname+'._00001.events.tar.gz')

import os
if 'ATHENA_PROC_NUMBER' in os.environ:
    opts.nprocs = 0
runArgs.inputGeneratorFile=rname+'._00001.events.tar.gz'

#--------------------------------------------------------------
# Private Application Configuration options
#--------------------------------------------------------------
include("Pythia8_i/Pythia8_A14_NNPDF23LO_EvtGen_Common.py")

#--------------------------------------------------------------
# Algorithms Private Options
#--------------------------------------------------------------
include("Pythia8_i/Pythia8_MadGraph.py")

genSeq.Pythia8.Commands += ["Main:timesAllowErrors = 60000"]

#relax the cuts on displaced vertices and non G4 particles
testSeq.TestHepMC.MaxTransVtxDisp = 100000000 #in mm
testSeq.TestHepMC.MaxVtxDisp = 100000000 #in mm
testSeq.TestHepMC.MaxNonG4Energy = 100000000 #in MeV

#--------------------------------------------------------------
# Configuration for EvgenJobTransforms
#--------------------------------------------------------------
evgenConfig.description = 'displaced FRVZ gg -> H -> %sgamma_d + X, mZd=%s, mH=%s' % (nGamma, mZd, mH)
evgenConfig.contact  = ['iacopo.longarini@cern.ch']
evgenConfig.process="LJ_FRVZdisplaced_ggfusion"
evgenConfig.inputfilecheck = rname
runArgs.inputGeneratorFile=rname+'._00001.events.tar.gz'

