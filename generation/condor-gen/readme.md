`generateASSamplesCondor.py` - script to automate the production of signal samples on condor

Type `python generateASSamplesCondor.py --help` to see available comand line options.

Generation of event fiels and truth-derivation of them are seperate steps, that need to be triggers manualy and individually, and require distinct environments that also need to be triggers manually:

`python generateASSamplesCondor.py` triggers the generation of event files
	**Requires to set the environment `asetup AthGeneration,21.6,latest,here`**

`python truthDAODConversion.py` triggers the truth-derivation of previously generated event files

Optional arguments

- `--signalType` defines the final state of the Additional Scalar decay
- `--workdir` defines the directory where the programm stores the event files and truth-derivation files, along with all the other files that are produced
- `--signalMassCSVFile` defines which .csv file we use for which mass points to genereate event files
- `--nEventsToGenerate` sets the number of events to generate
- `--dryRun` runs the programm but stops at actually submitting the jobs to condor. For practice or debugging purposes.





