import os

#delete all old tests
os.chdir('/Users/willdunn/WillDunn/quadTestGen/tests'); #change the directory to the location holding the old tests todo might not be needed
os.system('rm /Users/willdunn/WillDunn/quadTestGen/tests/*') #delete all the files in the folder

#run the test generator for the quadrilaterals
os.chdir('/Users/willdunn/WillDunn/quadTestGen/') #start by going to the directory where the program is located
os.system('clang++ -std=c++14 -c main.cpp')
os.system('clang++ -O3 -o testGen main.o ')
os.system("rm -f *.profdata")
os.system('./testGen')
#todo you might be able to do the different optimizations at this step and simply give them different names

#create the profiling for the actual quadrilateralClassifier being run
os.chdir('/Users/willdunn/WillDunn') #go back to the higher folder to build the quadrilateralClassifer
os.system('clang++ -fprofile-instr-generate -fcoverage-mapping main.cpp ParallelAndCongruentFunctions.cpp Errors.cpp '
          'FilterFunctions.cpp -o quadrilateralClassifier')

os.system("touch ./coverage/quadrilateralClassifier.profdata")
os.system("touch ./default.profraw")
lastFile = "quadrilateralClassifier"
os.system("LLVM_PROFILE_FILE=\"./coverage/" + lastFile + ".profraw\" ./quadrilateralClassifier")

#loop through each file in the test directory and create the profraws
for file in os.listdir("/Users/willdunn/WillDunn/quadTestGen/tests"):
    filename = os.path.splitext(os.fsdecode(file))[0]
    os.system("LLVM_PROFILE_FILE=\"./coverage/" + filename + ".profraw\" ./quadrilateralClassifier quadTestGen/tests/" + filename + ".txt")
    os.system("xcrun llvm-profdata merge -sparse ./coverage/" + lastFile + ".profdata ./coverage/" + filename + ".profraw -o ./coverage/" + filename + ".profdata")
    lastFile = filename

os.system("xcrun llvm-cov show ./quadrilateralClassifier -instr-profile=./coverage/" + lastFile + ".profdata > coverage.txt")

#do this again, with different coverage and results file names, but run under the different optimization O1-O3



