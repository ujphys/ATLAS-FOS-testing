import re # to do regular expression matching
import os
import csv

def prepEHDecayInputs(scalarMass, ehdecayDir = os.path.dirname(os.path.abspath(__file__))):

    referenceFile = os.path.join(ehdecayDir,"ehdecay.in.reference")

    # read the reference job options
    with open(referenceFile) as readFile: readLines = readFile.readlines()


    # replace the place holders with the relevant values
    readLines_varsInserted = []
    for line in readLines:
        line = re.sub( "<couplingOption>"    ,"0",line) # '0' selects the Standard Model option
        line = re.sub( "<scalarMass>", "%fD0" %scalarMass ,line)
        readLines_varsInserted.append( line )

    targetFile = "ehdecay.in"

    # write out the job options with its place holders replaced
    writeFile = open(targetFile,"w")
    writeFile.writelines(readLines_varsInserted)
    writeFile.close()

    return None


def getWidthFromOutputFile(outputFileName = "br.eff2", ehdecayDir = os.path.dirname(os.path.abspath(__file__))):

    outputContents = []

    outputFile = os.path.join(ehdecayDir,outputFileName)

    with open(outputFile) as csv_file:

        csv_reader = csv.reader(csv_file, delimiter=' ')
        for row in csv_reader: outputContents.extend(row)

    # remove empty strings, empty strings are being evaluated as valse
    outputContents =[ string for string in outputContents if string] 

    width = outputContents[-1] 

    return width


def getScalarDecayWidth( scalarMass , ehdecayDir = os.path.dirname(os.path.abspath(__file__))):
    # uses the 'ehdecay' package to calculate the width the additional scalar
    # see: https://www.itp.kit.edu/~maggie/eHDECAY/

    # we change dirs becasue the ehdecay output files end up in the current working dir
    originalDir = os.getcwd() 
    os.chdir(ehdecayDir)

    # compile the package if it hasn't been compiled yet, 
    # tag on 'ehdecay.o' to infer if it has been compiled before
    if "ehdecay.o" not in os.listdir(ehdecayDir): os.system("make -C %s" %ehdecayDir)

    prepEHDecayInputs(scalarMass)

    os.system(os.path.join(ehdecayDir,"run") )     # run the ehday programm

    width = getWidthFromOutputFile()

    os.chdir(originalDir)

    return width




if __name__ == '__main__':

    width = getScalarDecayWidth( 290)

    print(width)



    import pdb; pdb.set_trace()