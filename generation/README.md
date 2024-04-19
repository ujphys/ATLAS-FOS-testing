Code is currently generated using the Hidden Abelian Higgs Model in MadGraph+Pythia.

Condor instructions for AFS:
!!!!!!!! NEED TO UPDATE CODE TO RUN DIRECTLY ON EOS !!!!!!!!
There are ongoing permission issues with running HTCondor on EOS - in the meantime we use a workaround to produce the events code in AFS, move the file to EOS, then run reconstruction code in EOS.
- First, copy the condor-gen directory to both EOS and AFS
- Setup environments in each folder:
    - setupATLAS
    - asetup Athena,main,latest
- Go to your AFS directory for the code:
- In generateASSamplesCondor.py, check that:
- - On line 12/13, os.sys.path.append() should be set to the events1 directory
- Create a CSV file for the mass points:
- In condor-gen/, run the command to submit event-generation job to Condor:
python generateASSamplesCondor.py operationMode --signalMassCSVFile test.csv --nEventsToGenerate 100 --workdir /afs/cern.ch/user/c/connell/public/diH-condor/events1/ --signalType di_higgs
- - operationMode tells Condor whether to generate events, make truth files etc. Should be replaced with generateEvents here.
- - signalMassCSVFile set the CSV file which gives the mass points.
- - nEventsToGenerate choose number of events to generate.
- - workdir choose working directory.
- - signalType choose type of decay you want to generate.
- It should take <35 minutes for 1 job of 10k events
- - Use condor_q to check the status of the command.
- - Your jobs should show as either ‘idle’ or ‘running’ (there should be 1 job submitted per mass point).
- - If your job gets held, this could be due to running out of space in the output area. Once space is cleared, use condor_release user1 to release held jobs for user1.
    - Finished correctly if:
        - There are files named according to each mass point (e.g. di_higgs_mH400.0_mS1000.0_mZd20.0)
- - - Each of these folders has a large EVNT.root file (>100Mb)
- Move these ‘di_higgs…’ folders to the EOS diH-condor/ directory.
- In the EOS condor-gen/ directory, run the command to submit truth-reconstruction job to Condor:
python generateASSamplesCondor.py operationMode --signalMassCSVFile test.csv --nEventsToGenerate 100 --workdir /eos/user/c/connell/met4l-analysis/xola-gen-code/diH-condor/events1 --signalType di_higgs --dryRun
- - operationMode tells Condor whether to generate events, make truth files etc. Should be replaced with truthDAODConversion here.
- - signalMassCSVFile same as generation command.
- - nEventsToGenerate same as generation command.
- - workdir set to the folder to which the ‘di_higgs…’ folders were copied.
- - signalType make sure you have --dryRun on the end.
- - Finished correctly if:
- - - There are two scripts in each ‘di_higgs…’ folder, e.g.:
- - - - truthDAOD_di_mS110_mZd20.sh
- - - - truthDAOD_di_mS110_mZd20.sub
- In events1/ run the .sh script
- - Working if you see output like “AthenaEventLoopMgr … x events processed so far”
- - Takes 5 minutes for 100 events (makes 4Mb DAOD file)
- - Finished correctly if:
- - - - There is a large DAOD_TRUTH1 file (>100Mb – should be slightly larger than the EVNT.root file it was created from)
- Make reco/ in the ‘di-higgs…’ folder you’ve just run the script for and move all the files produced by the script to this folder (should be 11 files – the largest and most important is the DAOD_TRUTH1 file).
- Move the output folders to a folder that can be shared in CERNBox
