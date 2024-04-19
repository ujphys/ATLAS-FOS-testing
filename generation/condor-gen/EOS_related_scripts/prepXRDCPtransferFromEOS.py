import re
import os
import argparse # to parse command line options


def makeXRDCPFile( commandLines, fileName ="xrdcpTransferToFromEOS.sh" ):

    with open(fileName, "w") as submitWrite:
        submitWrite.write('#!/bin/bash\n')
        for command in commandLines: submitWrite.write(command +'\n')

    return fileName


def initilizeArgParser( parser = argparse.ArgumentParser(    description=
    "A script that helpes to transfer files from or to the EOS space on LXPlus\
    Useage: run the script with the mandarotory arguments\
    make sure to use to '--transferToEOS' flag if transferring to EOS\
    other wise transfer from EOS is assumed.\
    \
    Outputs a script 'xrdcpTransferToFromEOS.sh'\
    Execute this one to actually transfer the files.\
    Make sure to have the target folder structure in place,\
    as the 'xrdcpTransferToFromEOS.sh' will name create it\
    Also get the necessary authorization by running\
        kinit <cern user name>@CERN.CH\
    to get the necessary authorization.\
    \
    In my experice the created script needs the be run on the cluster that is not LXPlus.\
    I.e. when transferring files between Cluster_A and LXPlus,\
    the 'xrdcpTransferToFromEOS.sh' needs to be executed on Cluster_A.") ):

    parser.add_argument("sourceDir", type=str, default=None , 
        help="Mandatory option. Directory where the files are located that we want to transfer." )

    parser.add_argument("targetDir", type=str, default=None , help=
        "Mandatory option. Directory on the other machine where to want to transfer the files to.\
        The 'xrdcpTransferToFromEOS.sh' does not create the folder substructure, so it needs to be created manually.\
        Running the present script will inform you which folders need to be created though." )

    parser.add_argument("--requiredEnding", type=str, help=
        "We might only want to transfer files with a specific ending. In that case use this option.\
        For example, if we want to transfer files only with the ending '.root' use the option '--requiredEnding .root'")

    parser.add_argument( "--transferToEOS", default=False, action='store_true' , help = 
        "The script needs to know if we transfer files from EOS or to EOS.\
        The default is to transfer files from EOS. In this case no other action is needed.\
        If we want to transfer files to EOS, use the '--transferToEOS' argument to signify that." ) 

    parser.add_argument( "--ignoreSubfolders", default=False, action='store_true' , help = 
        "By default we will also go through all the subfolders in the sourceDir' \
        and prepare the to transfer the files within.\
        (We will do that recursively, i.e. also for the sub-subfolders etc.)\
        If we don't want that, and want only to transfer the files directly in the 'sourceDir' \
        and do not want to consider any files in any subfolders\
        call with the option '--ignoreSubfolders'" ) 

    return parser


if __name__ == '__main__':

    parser = initilizeArgParser()
    args = parser.parse_args()


    realpath = os.path.realpath(args.sourceDir)
    newDestinationPaths = set()
    xrdcpCommandLines = []

    for (root,dirs,files) in os.walk(realpath): 
        for file in files:

            if args.requiredEnding and not file.endswith(args.requiredEnding): continue

            subdirMatch = re.search("(?<=%s/).*" %realpath ,root)

            if subdirMatch:

                subdir = subdirMatch.group()
                newDestinationPaths.add( os.path.join( args.targetDir,subdir ) )

            else: subdir = ""

            source = os.path.join(root,file)
            target = os.path.join(args.targetDir,subdir,file)

            if args.transferToEOS: xrdcpCommand = "xrdcp  %s   root://eosuser.cern.ch/%s"  %(source, target)
            else:                  xrdcpCommand = "xrdcp  root://eosuser.cern.ch/%s   %s"  %(source, target)

            xrdcpCommandLines.append(xrdcpCommand)  
        if args.ignoreSubfolders: break

    XRDCPScript = makeXRDCPFile( xrdcpCommandLines )

    if newDestinationPaths: print( "make sure the necessary subfolders have been created at the target location")
    for subdir in newDestinationPaths: print("mkdir " + subdir )

    print( "\nFile %s has been created. \nTo transfer files to / from EOS execute the script:\n\tsource %s" %(XRDCPScript,XRDCPScript))
    print( "\nDon't forget to get access rights to EOS via executing:\n\tkinit <your cern username>@CERN.CH")

    #import pdb; pdb.set_trace() # import the debugger and instruct it to stop here
