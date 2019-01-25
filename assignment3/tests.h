//
// Created by Will Dunn on 1/24/19.
//
#include <string>
#include <vector>
#include <fstream>
#include "main.cpp"

#pragma once

bool exhaustiveTest();
bool quadTest();
bool parallelogramTest();
bool squareTest();
bool rectangleTest();
bool kiteTest();
bool trapTest();
bool outputTest(); //todo examine whether this should take a file name and do the test or run a method and get results
//because you are using Travis, you will need to run the program to create an output because it will do this each time you
//try and commit something to github.

//you can also use freopen() to capture the output of the main() and then use the output file created from the routine to
//compare against a known answer file
//insert test file -> capture output -> compare if output files are the same and if so, return true