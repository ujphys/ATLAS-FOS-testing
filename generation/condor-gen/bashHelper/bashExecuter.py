import os
import subprocess

from datetime import datetime


def getCurrentDataAndTime():
    now = datetime.now()

    return now.strftime("%d%m%Y_%H%M%S")

def submitBashCommandToAffectOuterShell( bashStrings, shellScriptName = None, 
    deleteShellScript = False, executeShellScript = True):
    # We want to execute a set of bash commands, with the goal to affect the shell from which we called python
    # Best way to do that I could figure out is this one here:
    # We Write the commands to a shell script and let them be executed via python
    # Once that is done, we delete the script

    if not isinstance(bashStrings,list): bashStrings = [bashStrings]


    stringsToWriteOut = ["#!/bin/sh"]
    stringsToWriteOut.extend(bashStrings)

    if shellScriptName is None:
        shellScriptName = "tempBashScript_%s.sh" %getCurrentDataAndTime()

    with open(shellScriptName, "w") as shellWrite:
        for submitLine in stringsToWriteOut: shellWrite.write('%s\n' %submitLine)

    os.chmod(shellScriptName, 0o755) # make the shell script executable

    #subprocess.run("source %s" %shellScriptName, shell=True) # this only works in python 3+, so let's use the verision below

    if executeShellScript: subprocess.Popen(["source %s" %shellScriptName], shell=True)

    if os.path.exists( shellScriptName ) and deleteShellScript:  
        os.remove( shellScriptName )


    return None



if __name__ == '__main__':


    derivationEnvironment = ["source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh", "asetup AthDerivation,21.2.64.0" ]


    submitBashCommandToAffectOuterShell( derivationEnvironment )

    #import pdb; pdb.set_trace()