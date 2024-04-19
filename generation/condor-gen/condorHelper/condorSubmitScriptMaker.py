import re # to do regular expression matching
import os
import socket

# helper script to facility the submission of jobs to condor
# presumes that the job to be submitted is a single bash script
# Uses the 'condorReferenceSubmitScript.sub' as a template submission script

if "lxplus" in socket.gethostname(): 
     print("run on lxplus")
     referenceSubmitScript = "condorReferenceSubmitScriptlxplus.sub"

else:
     print("run on BNL")
     referenceSubmitScript = "condorReferenceSubmitScript.sub"
 
def makeSubmitScript( shellScriptName, submitScriptName = None, referenceSubmitScriptName= referenceSubmitScript):

       # make sure we have the absolute path to our reference submit script
       locationOfThisFunctionsFile = os.path.dirname(os.path.abspath(__file__))
       referenceSubmitScriptName = os.path.join(locationOfThisFunctionsFile,referenceSubmitScriptName)

       with open(referenceSubmitScriptName) as readFile: readLines = readFile.readlines()

       shellScriptPlaceHolder = "<executionScript.sh>"

       # replace shellScriptPlaceHolder with shellScriptName in line
       outputLines = [re.sub(shellScriptPlaceHolder,shellScriptName,line) for line in readLines]

       # make sure submit script and shell script have different names
       if submitScriptName is None: submitScriptName = re.sub(".sh",".sub",shellScriptName)
       if not submitScriptName.endswith(".sub"): submitScriptName += ".sub"

       # write submit script
       writeFile = open(submitScriptName,"w")
       writeFile.writelines(outputLines)
       writeFile.close()

       os.chmod(submitScriptName, 0o755) # make sure submit script is executable
       os.chmod(shellScriptName, 0o755) # do the same for the shell script

       return submitScriptName

def submitToCondorFromSubmitScriptLocation(submitScript, changeDir = True, actuallySubmit = True):

    originalDir = os.getcwd()

    targetDir = os.path.dirname( submitScript )

    if changeDir and len(targetDir) > 0 : os.chdir(targetDir) # change directory to the target dir, so that the log and error files 
    if actuallySubmit: os.system( "condor_submit " + submitScript)

    os.chdir(originalDir)

    return None

def makeSubmitScriptAndSubmit( shellScriptName, changeDir = True, actuallySubmit = True):

    submitScript = makeSubmitScript( shellScriptName )
    submitToCondorFromSubmitScriptLocation(submitScript, changeDir = changeDir, actuallySubmit = actuallySubmit)

    return None

def writeShellScript(shellScriptName , shellCommands):

    if not isinstance(shellCommands, list): shellCommands = [shellCommands]

    shellScriptPath = os.path.dirname(shellScriptName)
    if not os.path.exists(shellScriptPath): os.makedirs(shellScriptPath)

    with open(shellScriptName, "w") as shellWrite:
        shellWrite.write('#!/bin/bash\n')

        for submitLine in shellCommands: shellWrite.write('%s\n' %submitLine)
        #b.write(gangacmd)

    os.chmod(shellScriptName, 0o755)

    return None


if __name__ == '__main__':

    import pdb; pdb.set_trace()
