#!/bin/bash
#find the path the file that is testByLines.txt
./quadrilateralClassifier testCasesByLine.txt >> var.txt 

#use the results to compare a difference between an accurate answers file
cmp --silent var.txt answers.txt && echo '### SUCCESS! ###' || echo '### WARNING: You failed tests! ###'
