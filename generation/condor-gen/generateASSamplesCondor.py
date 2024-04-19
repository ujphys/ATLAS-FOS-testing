import re # to do regular expression matching
import os
import time
import subprocess   # for executing bash commands
import datetime
import csv

from collections import defaultdict


#import difflib
# os.sys.path.append('/afs/cern.ch/user/x/xmapekul/mc_prod_validation/MCProd_scripts/r21/automatedSignalGenerator')
os.sys.path.append('/afs/cern.ch/user/c/connell/public/diH-condor/events1')
import argparse # to parse command line options

import condorHelper.condorSubmitScriptMaker as condorSubmitScriptMaker

import calculateDecayWidths.calculateScalarWidthHelper as calculateScalarWidthHelper
 
#import bashHelper.bashExecuter as bashExecuter

def getEnvironmentSetupCommands(operationMode, signalType):

    setupATLAS = "source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh"

    environmentDict = defaultdict(dict)
    # use as environmentDict[operationMode][signalType]

    environmentDict["generateEvents"     ]['default'] =  "asetup Athena,main,latest"
    #environmentDict["generateEvents"     ]['default'] =  "asetup AthGeneration,22.6.6,here"
    #environmentDict["generateEvents"     ]['default'] =  "asetup AthGeneration,23.6.6,here"

    #environmentDict["truthDAODConversion"]['default'] =  "asetup 21.2.86.0,AthDerivation"
    environmentDict["truthDAODConversion"]['default'] =  "asetup Athena,main,latest"
    # we will call the defaults if we don't have a special setup for the given signal type
    environmentDict["truthDAODConversion"]['di_higgs'] = \
     "export AtlasSetup=/afs/cern.ch/atlas/software/dist/AtlasSetup; \
      alias asetup='source $AtlasSetup/scripts/asetup.sh'; \
      asetup 21.2.53.0,AthDerivation,here"

    environmentDict["generateEvents"     ]['FRVZ'] =  \
    "export AtlasSetup=/afs/cern.ch/atlas/software/dist/AtlasSetup; \
    alias asetup='source $AtlasSetup/scripts/asetup.sh'; \
    asetup 21.6.12,AthGeneration"

#    environmentDict["generateEvents"     ]['di_higgs'] =  \
#    "export AtlasSetup=/afs/cern.ch/atlas/software/dist/AtlasSetup; \
#    alias asetup='source $AtlasSetup/scripts/asetup.sh'; \
#    asetup 19.2.5.26"

    defaultCommand = environmentDict[operationMode]['default']

    environmentCommands = environmentDict[operationMode].get(signalType,  defaultCommand)

    return [setupATLAS, environmentCommands]

def parseMassesFromCSV(csvFileName):

    massList = []

    with open(csvFileName) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')

        for row in csv_reader:

            if not re.match("\d+",row[0]): continue # skip line if it does not start with some digits, e.g. skip header
            massList.append(tuple(float(x) for x in row))

    return massList


def makeJobOptions(targetFile, mS_GeV, mZd_GeV,mH_GeV, signalType,
    widthDict = {}, # define the dict here, so that it is persistent after defining the function
    # get absolute path of the reference job options when the function is defined, to preempt any changes in directory within the script
    referenceJobOptionPath  = os.path.join(os.path.dirname(os.path.abspath(__file__)),"referenceJobOptions") ):
    jobOptionFiles = [file for file in os.listdir(referenceJobOptionPath) if signalType in file]

    for jobOptionFile in jobOptionFiles: 
        referenceJobOptions = os.path.join(referenceJobOptionPath,jobOptionFile)
        targetFolder = os.path.dirname(targetFile)
        if len(targetFolder):
            createFolder( targetFolder  ) # make sure we have directory where we want to save the targetFile

        with open(referenceJobOptions) as readFile: readLines = readFile.readlines()


        if not mS_GeV in widthDict: # calculate scalar decay width
            widthDict[mS_GeV] = calculateScalarWidthHelper.getScalarDecayWidth(mS_GeV)

        # replace the place holders with the relevant values
        readLines_massesInserted = []
        for line in readLines:
            line = re.sub( "<ZdMass_Gev>"    ,str(mZd_GeV),line)
            line = re.sub( "<higgs_Mass_Gev>",str(mH_GeV), line)
            line = re.sub( "<scalarMass_Gev>",str(mS_GeV) ,line)
            line = re.sub( "<scalarDecayWidth>",str(widthDict[mS_GeV]) ,line)

            readLines_massesInserted.append( line )
        #import pdb; pdb.set_trace()

        # write out the job options with its place holders replaced
        if not jobOptionFile.startswith("mc."): targetFileForWrite  = os.path.join( os.path.dirname(targetFile), jobOptionFile)
        else:                                   targetFileForWrite  = targetFile     

        writeFile = open(targetFileForWrite,"w")
        writeFile.writelines(readLines_massesInserted)
        writeFile.close()
        # dst = f"MadGraph_param_card_FRVZdisplaced_mZd{mZd_GeV}_mH{mS_GeV}.dat"

    return None


def createFolder(path):
    if not os.path.exists(path): os.makedirs(path)
    return None



def genereateSignalEventFiles(targetParentFolder , mSmZdMassList, nEventsToGenerate, signalType ,EventGenerationOutputName = "EVNT.root", doTruthConversionToo = False):

    for signalType in args.signalType:
        for mH, mS, mZd in mSmZdMassList:

            targetFolder = os.path.join(targetPrefix, signalType+"_mH%s_mS%s_mZd%s" %(mH,mS,mZd))
            # generationFolder = os.path.join(targetFolder,"genDir")
            # createFolder(generationFolder)
            targetFolder = os.path.abspath(targetFolder)
            createFolder(targetFolder) # this folder will contain the generated samples

            # setup job options
            jobOptionNumber = "999999"
            if(signalType == 'FRVZ'):
                jobOptionFileName = "mc.MGPy8EG_A14NN23LO_FRVZ_long.py"
            elif(signalType == 'di_higgs'):
                jobOptionFileName = "mc.MGPy8EG_di_higgs.py"
            else:
                #jobOptionFileName = "mc.MGPy8EG_A14NNPDF23LO_HAHMggfZdZd%s_%s_%s.py" %(signalType,mS,mZd)
                jobOptionFileName = "mc.MGPy8EG_A14NNPDF23LO_HAHMggfZdZd%s.py" %(signalType)
            targetJobOption = os.path.join(targetFolder, jobOptionNumber, jobOptionFileName )
            makeJobOptions(targetJobOption, mS, mZd, mH, signalType)

            runCommmand  = getEnvironmentSetupCommands("generateEvents", signalType)

            # make shell script that executes the generation
            runCommmand.append("Gen_tf.py --ecmEnergy=13000. --maxEvents=%i --firstEvent=1 --randomSeed=732595 --outputEVNTFile=%s \
            --jobConfig=%s" %(nEventsToGenerate, EventGenerationOutputName ,os.path.dirname(targetJobOption)) )

            if doTruthConversionToo:
                runCommmand.extend(getEnvironmentSetupCommands("truthDAODConversion", signalType) )
                runCommmand.append( "Reco_tf.py --inputEVNTFile %s --outputDAODFile truthDAOD_%s_mS%s_mZd%s.pool.root --reductionConf TRUTH1" 
                                    %( os.path.join(targetFolder,EventGenerationOutputName), signalType ,mS,mZd) )

            shellScriptName = os.path.join(targetFolder,"generate_%s_mH%i_mS%i_mZd%i.sh" %(signalType,mH,mS,mZd))
            condorSubmitScriptMaker.writeShellScript(shellScriptName , runCommmand)

            submitScript = condorSubmitScriptMaker.makeSubmitScript(shellScriptName) # make a submit script for condor
            #submit the job to condor
            condorSubmitScriptMaker.submitToCondorFromSubmitScriptLocation(submitScript, changeDir = True, actuallySubmit = not args.dryRun)

    return None

def truthDAODReconstruction(targetParentFolder , EventGenerationOutputName = "EVNT.root"):
    # print(targetParentFolder)
    for folder in os.listdir(targetParentFolder):
        print(folder)
        subdir = os.path.join(targetParentFolder,folder)
        print(subdir)
        if not os.path.isdir(subdir):
            continue

        if not EventGenerationOutputName in os.listdir(subdir):
            continue # tag on the event generation output file

        mS_GeV = re.search("(?<=mS)\d+", subdir).group() # look for one or more digits after 'mS'
        mZd_GeV = re.search("(?<=mZd)\d+", subdir).group() # look for one or more digits after 'mZd'
        mH_GeV = re.search("(?<=mH)\d+", subdir).group() # look for one or more digits after 'mH'
        inferredSignalType = folder.split("_")[0]

        ## make shell script that executes the generation
        #runCommmand = "Reco_tf.py --inputEVNTFile %s --outputDAODFile truthDAOD_%s_mS%s_mZd%s.pool.root --reductionConf TRUTH1" \
        #              %( os.path.join(subdir,eventGenerationFileName), inferredSignalType,mS_GeV,mZd_GeV)


        runCommmand = getEnvironmentSetupCommands("truthDAODConversion", inferredSignalType)
        runCommmand.append( "Derivation_tf.py --CA True --inputEVNTFile %s --outputDAODFile truthDAOD_%s_mS%s_mZd%s.pool.root --formats TRUTH1"
                            %( os.path.join(subdir,eventGenerationFileName), inferredSignalType ,mS_GeV,mZd_GeV) )

        #runCommmand = getEnvironmentSetupCommands("truthDAODConversion", inferredSignalType) 
        #runCommmand.append( "Reco_tf.py --inputEVNTFile %s --outputDAODFile truthDAOD_%s_mS%s_mZd%s.pool.root --reductionConf TRUTH1" 
        #                    %( os.path.join(subdir,eventGenerationFileName), inferredSignalType ,mS_GeV,mZd_GeV) )



        shellScriptName = os.path.join(subdir,"truthDAOD_%s_mS%s_mZd%s.sh" %(inferredSignalType,mS_GeV,mZd_GeV))
        condorSubmitScriptMaker.writeShellScript(shellScriptName , runCommmand)

        submitScript = condorSubmitScriptMaker.makeSubmitScript(shellScriptName) # make a submit script for condor
        #submit the job to condor
        condorSubmitScriptMaker.submitToCondorFromSubmitScriptLocation(submitScript, changeDir = True, actuallySubmit = not args.dryRun)

    return None



def initilizeArgParser( parser = argparse.ArgumentParser(
    description="Script to produce truth level Additional Scalar signal samples automatically on a Condor batch system.\
    Pick whether to generate signal event files or to make truth derivation files by running\
    'python generateASSamplesCondor.py' or 'python truthDAODConversion.py' \
    See option arguments for selecting directory to place the generated files, define final states, etc.") ):

    parser.add_argument("operationMode", type=str, default= "generateEventsAndDoTruthDerivation" , 
        choices=["generateEvents","truthDAODConversion", "generateEventsAndDoTruthDerivation"],
        help="Mandatory option.\
        Signal sample generation here involves two steps.\
        1) Generation of event files - 'generateEvents' \
        2) Truth derivation of the generated event files - 'truthDAODConversion' \
        Each one requires a different environment that is set automatically.\
        The 'generateEvents' requires the \
        asetup AthGeneration,21.6,latest,here'    \
        environment.\
        Event files are saved in the folder defined by the '--workdir XYZ' argument. \
        'truthDAODConversion' requires the \
        asetup 21.2.86.0,AthDerivation      \
        environment.\
        Use option 'generateEndsAndDoTruthDerivation' do to generation of events\
        and truth derivation in one submission. (This is the recommended option" )

    parser.add_argument("--signalType",nargs='*', type=str, required = True , 
        choices=["2l2nu","2l2j","FRVZ", "ZX_4l", "di_higgs"], 
        help="Determines the final state and model we want to generate.\
        We can either make 2l2nu signal samples, or 2l2j ones.")

    parser.add_argument("--workdir", type=str, default="AS_signalSamples" ,
        help="Directory in which we generate and truth-derive signal samples.\
        Make sure to use the same folder for event generation and truth derivation.")

    parser.add_argument("--signalMassCSVFile", type=str, default="defaultSignalMassPoints.csv" ,
        help="CSV file that defines the signal mass points to generate / truth-derive. Expects structure like 'mS [GeV], mZd [GeV]'")

    parser.add_argument("--nEventsToGenerate", type=int, default=10 ,
        help="Number of events that we want to generate")


    parser.add_argument( "--dryRun", default=False, action='store_true' ,
    help = "With this option we skip the step of actually submitting to the grid. Usefull for debugging and development" )

    return parser



if __name__ == '__main__':

    # parse command line arguments
    parser = initilizeArgParser()
    args = parser.parse_args()

    # setup the folder where we want to work at
    if os.path.isabs(args.workdir): targetPrefix= args.workdir
    else:                           targetPrefix= os.path.join( os.getcwd(), args.workdir)


    eventGenerationFileName = "EVNT.root" # save generated files under this name, and use to tag on it for truth derivation


    if args.operationMode == "generateEvents" or args.operationMode == "generateEventsAndDoTruthDerivation": # if we want to generate the signal event files

        #print( "Did you enable the right environment with: 'asetup AthGeneration,21.6,latest,here' ?")

        massList = parseMassesFromCSV(args.signalMassCSVFile)
        genereateSignalEventFiles(targetPrefix , massList, args.nEventsToGenerate, args.signalType, EventGenerationOutputName = eventGenerationFileName, 
            doTruthConversionToo = args.operationMode == "generateEventsAndDoTruthDerivation")

    elif args.operationMode == "truthDAODConversion":

        #print( "Did you enable the right environment with: 'asetup 21.2.86.0,AthDerivation' ?")

        truthDAODReconstruction(targetPrefix , EventGenerationOutputName = eventGenerationFileName)

        print("Done")

    #import pdb; pdb.set_trace()



