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
//todo move all comments from the .cpp files into the .h to mitigate clutter, and i think this is how it's suppose to be
/**
 * Determine what quadrilateral the argument is.  If an input .txt is received, the file will be examined and an output
 * file will be supplied with the output of quadrilateral type.
 * @param argv
 *  -contains four points (the first being 0,0), which make up a quadrilateral, with a space between each point.
 */
int main(int argc, char *argv[]) {
    if(argc < 2) errorType(1);

    //deal with input .txt
    if (argc == 2) {
        examineFile(argc, argv); //arg[0]: name of this program; arg[1]: input file
        return 0;
    }
    std::vector<double> points{0, 0}; //the first point will always be (0, 0)

    //fill vector with points from arguments
    for (int argIter = 1; argIter < argc; argIter++) {
        if(isInvalidCharacter(argv[argIter])) errorType(1);
        std::string strToConvertToDecimal = argv[argIter]; //zero added to ensure a find() result of 0 means unfound '.'
//        std::size_t pos = strToConvertToDecimal.find("."); //uncomment if you want to add precision(2) functionality
//        if(pos != std::string::npos || strToConvertToDecimal[0] == '.'){ //dealing with a decimal number
//            strToConvertToDecimal = strToConvertToDecimal.substr(0, pos) + strToConvertToDecimal.substr(pos, 3);
//        }
        if(std::stod(strToConvertToDecimal) > 100 || std::stod(strToConvertToDecimal) < 0) errorType(1);
        points.push_back(std::stod(strToConvertToDecimal));
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
    std::ifstream inputFile(argv[1]); //grab .txt argument
    std::string currLine;
    while (std::getline(inputFile, currLine)) {
        points.push_back(0); //fill first two points with 0s
        points.push_back(0);
        std::string num = "";

        //loop through the current line to separate numbers
        for (int linePosition = 0; linePosition < currLine.size(); linePosition++) {
            if (isspace(currLine[linePosition])) {
                if(std::stod(num) > 100 || std::stod(num) < 0 ) errorType(1); //the point is out of range
                points.push_back(std::stod(num));
                num = ""; //bookkeeping
                continue; //whitespace, so continue to next number
            } else if (linePosition == currLine.size() - 1) {
                num += currLine[linePosition];
                points.push_back(std::stod(num));
                break;
            }
            num += currLine[linePosition];
            if(isInvalidCharacter(num)) errorType(1);
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
    else if(hasCrossingLineSegments(points)) errorType(3);
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
