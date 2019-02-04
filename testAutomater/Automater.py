import subprocess
import os

#subprocess.call('cd ..', shell=True)
#subprocess.call('ls  "/Users/willdunn/WillDunn/quadTestGen"', shell=True)

#delete all old tests
os.chdir('/Users/willdunn/WillDunn/quadTestGen/tests'); #change the directory to the location holding the old tests todo might not be needed
os.system('rm /Users/willdunn/WillDunn/quadTestGen/tests/*') #delete all the files in the folder

#run the test generator for the quadrilaterals
os.chdir('/Users/willdunn/WillDunn/quadTestGen/') #start by going to the directory where the program is located
os.system('clang++ -std=c++14 -c main.cpp')
os.system('clang++ -o testGen main.o ')
os.system("rm -f *.profdata")
os.system('./testGen')
#todo you might be able to do the different optimizations at this step and simply give them different names

#create the profiling for the actual quadrilateralClassifier being run
os.chdir('/Users/willdunn/WillDunn') #go back to the higher folder to build the quadrilateralClassifer
os.system('clang++ -fprofile-instr-generate -fcoverage-mapping main.cpp ParallelAndCongruentFunctions.cpp Errors.cpp '
          'FilterFunctions.cpp -o quadrilateralClassifier')

#loop through each file in the test directory and create the profraws
for filename in os.curdir:
    currentFile = filename;
    os.system('LLVM_PROFILE_FILE="coverage/$(currentFile).profraw" ./quadrilateralClassifier tests/$(currentFile).txt')
    os.system('xcrun llvm-profdata merge -sparse coverage/$(lastFile).profraw coverage/$(currentFile).profraw -o quadrilateralClassifier.profdata')
    lastFile = filename;

os.system('xcrun llvm-cov show ./quadrilateralClassifier -instr-profile=./coverage/$(lastFile).profdata')

#todo if this shtuff doesn't run, mayhap remove the ./ from the non executable files

#run the tests and ensure that all pass while also getting coverage


#do this again, with different coverage and results file names, but run under the different optimization O1-O3


