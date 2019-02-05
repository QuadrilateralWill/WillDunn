#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "ParallelAndCongruentFunctions.h"
#include "FilterFunctions.h"
#include "Errors.h"

//prototyping
void examineFile(int argc, char *argv[]);
std::string processPoints(const std::vector<double> &points);

/**
 * Determine what quadrilateral the argument is.  If an input .txt is received, the file will be examined and an output
 * file will be supplied with the output of quadrilateral type.
 * @param argv
 *  -contains four points (the first being 0,0), which make up a quadrilateral, with a space between each point.
 */
int main(int argc, char *argv[]) {
    //if(argc < 2) errorType(1); //todo was causing issues with the bashscript triggering here at almost every test

    //deal with input < .txt
    if (argc == 3) {
        examineFile(argc, argv); //arg[0]: name of this program; arg[1]: input file
        return 0;
    }
    std::vector<double> points{0, 0}; //the first point will always be (0, 0)

    //fill vector with points from arguments
    for (int argIter = 1; argIter < argc; argIter++) {
//        if(isInvalidCharacter(argv[argIter])) errorType(1);
//        std::string strToConvertToDecimal = argv[argIter]; //zero added to ensure a find() result of 0 means unfound '.'
        try {
            std::string strToConvertToDecimal = argv[argIter]; //zero added to ensure a find() result of 0 means unfound '.'
            if (std::stod(strToConvertToDecimal) > 100 || std::stod(strToConvertToDecimal) < 0) errorType(1); //the point is out of range
            else if(std::stod(strToConvertToDecimal) - (int) std::stod(strToConvertToDecimal) != 0) errorType(1); //checks to ensure it's an int
            points.push_back(std::stod(strToConvertToDecimal));
        } catch (const std::exception& e){
            errorType(1);
        }
    }
    if(points.size() != 8) errorType(1);

    std::cout << processPoints(points) << std::endl;
    return 0;
}

/**
 * Looks at a file and pulls the arguments from within, which are used to be classified on an individual basis on which
 * type of quadrilateral they are.  The outputs are all written to a file called results.txt
 * @param argc
 * @param argv
 */
void examineFile(int argc, char *argv[]) {
    std::vector<double> points; //the first point will always be (0, 0)
    std::ofstream outputFile;
    outputFile.open("results.txt");

    //get the points from the .txt
    std::ifstream inputFile(argv[2]); //grab .txt argument
    std::string currLine;
    while (std::getline(inputFile, currLine)) {
        points.push_back(0); //fill first two points with 0s
        points.push_back(0);
        std::string num = "";

        //loop through the current line to separate numbers
        for (int linePosition = 0; linePosition < currLine.size(); linePosition++) {
            if (isspace(currLine[linePosition])) {
                try {
                    if (std::stod(num) > 100 || std::stod(num) < 0) errorType(1); //the point is out of range
                } catch (const std::exception& e){
                    errorType(1);
                }
                points.push_back(std::stod(num));
                num = ""; //bookkeeping
                continue; //whitespace, so continue to next number
            } else if (linePosition == currLine.size() - 1) {
                num += currLine[linePosition];
                points.push_back(std::stod(num));
                break;
            }
            num += currLine[linePosition];
        }
        if(points.size() != 8) errorType(1); //the input doesn't contain the correct number of points

        //process the points and write result to output file as well as outputting to the user
        outputFile << processPoints(points) << std::endl;
        std::cout << processPoints(points) << std::endl;
        points.clear(); //reset points so it doesn't fill with the points from the last argument line
    }
    inputFile.close();
    outputFile.close();
}

/**
 * Processes the input and assigns it a state, based on hierarchy of quadrilaterals and the finite states they can take.
 * @param points
 * @return
 *  -the type of quadrilateral the points are based on which state they reached
 */
std::string processPoints(const std::vector<double> &points) {

    if(hasPointsThatCoincide(points)) errorType(2);
    else if (hasCrossingLineSegments(0, 0, points[2], points[3], points[4], points[5], points[6], points[7]) ||
            hasCrossingLineSegments(0, 0, points[6], points[7], points[4], points[5], points[2], points[3])) {
        errorType(3);
    }
    //else if(hasCrossingLineSegments(points)) errorType(3);
    else if(hasThreeColinearPoints(points)) errorType(4);

    //go through hierarchy of determining which type of quadrilateral the input is utilizing finite states
    int quadState = 0;

    //state check for parallelogram, trap, or kite route
    if (hasBothSidesParallel(points)) quadState = 1;
    else if (hasOneParallelSide(points)) quadState = 5;
    else if (hasTwoCongruentSides(points)) quadState = 6;
    //else the state remains at 0;

    //further change the state, if necessary, based on further checks to the hierarchy of parallelograms
    if (quadState == 1) quadState = parallelogramFilter(points);

    //output based on the state
    std::vector<std::string> typeOfQuad{"quadrilateral", "parallelogram", "rectangle", "rhombus", "square",
                                        "trapezoid", "kite"};
    //std::cout << typeOfQuad[quadState] << std::endl;
    return typeOfQuad[quadState];
}
