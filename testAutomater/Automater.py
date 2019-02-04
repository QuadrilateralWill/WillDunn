import subprocess
import os

#subprocess.call('cd ..', shell=True)
#subprocess.call('ls  "/Users/willdunn/WillDunn/quadTestGen"', shell=True)

#delete all old tests
os.chdir('/Users/willdunn/WillDunn/quadTestGen/tests'); #change the directory to the location holding the old tests todo might not be needed
os.system('rm /Users/willdunn/WillDunn/quadTestGen/tests/*') #delete all the files in the folder

#run the test generator for the quadrilaterals
os.system('cd /Users/willdunn/WillDunn/quadTestGen') #start by going to the directory where the program is located
os.system('clang++ -c main.cpp')
os.system('clang++ -std')
#todo you might be able to do the different optimizations at this step and simply give them different names

#create the profiling for the actual quadrilateralClassifier being run

#run the tests and ensure that all pass while also getting coverage


#do this again, with different coverage and results file names, but run under the different optimization O1-O3
