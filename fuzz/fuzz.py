import os

# delete all old tests
os.system('rm /Users/willdunn/WillDunn/quadTestGen/tests/*')  # delete all the files in the folder

# run the test generator for the quadrilaterals
os.chdir('/Users/willdunn/WillDunn/quadTestGen/')  # start by going to the directory where the program is located
os.system('clang++ -std=c++14 -c main.cpp')
os.system('clang++ -o testGen main.o ')
os.system("rm -f *.profdata")
os.system('./testGen')
# todo you might be able to do the different optimizations at this step and simply give them different names

# create the profiling for the actual quadrilateralClassifier being run
os.chdir('/Users/willdunn/WillDunn')  # go back to the higher folder to build the quadrilateralClassifer


def generateTestCoverage(optimizationNum):
    failedTests = "";
    correctResults = {'NullSpace': 'Error 1 - invalid input', 'ASCII': 'Error 1 - invalid input',
                      'Scalene': 'quadrilateral',
                      'Quadrilateral': 'quadrilateral',
                      'Square': 'square', 'Rhombus': 'rhombus', 'Rectangle': 'rectangle',
                      'Parallelogram': 'parallelogram',
                      'Trapezoid': 'trapezoid', 'Kite': 'kite', }
    os.system(
        'clang++ -fprofile-instr-generate -fcoverage-mapping main.cpp ParallelAndCongruentFunctions.cpp Errors.cpp '
        'FilterFunctions.cpp -O' + optimizationNum + ' -o quadrilateralClassifier')
    os.system("touch ./coverage/quadrilateralClassifier.profdata")
    os.system("touch ./default.profraw")
    lastFile = "quadrilateralClassifier"
    os.system("LLVM_PROFILE_FILE=\"./coverage/" + lastFile + ".profraw\" ./quadrilateralClassifier")
    # loop through each file in the test directory and create the profraws
    for file in os.listdir("/Users/willdunn/WillDunn/quadTestGen/tests"):
        filename = os.path.splitext(os.fsdecode(file))[0]
        os.system(
            "LLVM_PROFILE_FILE=\"./coverage/" + filename + ".profraw\" ./quadrilateralClassifier quadTestGen/tests/" + filename + ".txt > compare.txt")
        nuFilename = ''.join(i for i in filename if not i.isdigit())  # removes digits from test name
        diff = os.system('cmp --silent compare.txt /correctResults/' + nuFilename)
        if(diff == 1):
        os.system(
            "xcrun llvm-profdata merge -sparse ./coverage/" + lastFile + ".profdata ./coverage/" + filename + ".profraw -o ./coverage/" + filename + ".profdata")
        lastFile = filename
        os.system(
            "xcrun llvm-cov show ./quadrilateralClassifier -instr-profile=./coverage/" + lastFile + ".profdata > coverage" +
            optimizationNum + ".txt")
        # see if the test came out the way it should have using a dictionary
        nuFilename = ''.join(i for i in filename if not i.isdigit())  # removes digits from test name
        if (nuFilename == '.DS_Store'): continue
        if (nuFilename != 'NullSpace' or nuFilename != 'ASCII'):  # normal shape
            if (correctResults[nuFilename] != os.system('cat compare.txt')):
                failedTests += filename + " "
        elif (nuFilename == 'NullSpace'):
            if (correctResults[nuFilename] == result):
                failedTests += filename + " "
        elif (nuFilename == 'ASCII'):
            if (correctResults[nuFilename] != result):
                failedTests += filename + " "
    # if a test didn't arrive at the correct result, print 'ERROR' at the base of the program.  Else, print 'OK'
    if (failedTests == ""):
        with open("coverage" + optimizationNum + ".txt", "a+") as myfile:
            myfile.write("OK")
        myfile.close()
    elif (failedTests != ""):
        with open("coverage" + optimizationNum + ".txt", "a+") as myfile:
            myfile.write("ERROR: " + failedTests)
        myfile.close()


# run in 3 different optimizations and ensure the same answer is returned
generateTestCoverage('1')
generateTestCoverage('2')
generateTestCoverage('3')
os.system(
    'cmp --silent coverage1.txt coverage2.txt && echo "Optimization is the same" || echo "Coverage 1 and 2 differ!\n"')
os.system(
    'cmp --silent coverage1.txt coverage3.txt && echo "Optimization is the same" || echo "Coverage 1 and 3 differ!\n"')
