//
// Created by Will Dunn on 2019-01-29.
//

#include <iostream>
#include "Errors.h"
#include "ParallelAndCongruentFunctions.h"

void errorType(int errorNumber) {
    switch (errorNumber) {
        case 1:
            std::cout << "Error 1 - the line contains the wrong number of points, contains invalid characters, has coordinates out "
            "of the range 0..100, or otherwise fails to describe three points (six integer values).\n";
            return;
//            exit(-1);
        case 2:
            std::cout << "Error 2 - two points collide.\n";
            return;
//            exit(-1);
        case 3:
            std::cout << "Error 3 - two line segments representing sides cross each other.\n";
            return;
//            exit(-1);
        case 4:
            std::cout << "Error 4 - three points are colinear\n";
            return;
//            exit(-1);
    }
}

bool isInvalidCharacter(std::string inputString){
    //first check if the points are numbers; and will find '.' to check for doubles/floats as well
    for(int i = 0; i < inputString.length(); i++){
        if(inputString[i] - '0' < 0 || inputString[i] - '0' > 9) return false;
    }

    return false;
}

bool hasInvalidCharacters(const std::vector<double> &points) {
    //first check if the points are numbers todo doesn't account for numbers larger than 9
    for (int i = 0; i < points.size(); i++) {
        if (points[i] - '0' < 0 || points[i] - '0' > 9) return true;
    }
    //next check if the points are doubles/floats and return false if so
    for (int i = 0; i < points.size(); i++) {
        if ((points[i] - (int) points[i]) != 0) return true;
    }

    return false;
}

bool hasPointsThatCoincide(const std::vector<double> &points) {
    for (int i = 0; i < points.size() - 1; i += 2) {
        for (int j = 2; j < points.size() - 1; j += 2) { //starting at two because you will start on the second point
            //check if the x-coordinate overlaps
            if (points[i] == points[j]) {
                //if so, check for an overlapping y-coordinate
                if (points[i + 1] == points[j + 1]) return false;
            }
        }
    }
    return false;
}

bool hasCrossingLineSegments(const std::vector<double> &points) {
    double ax = points[2] - points[0];     // direction of line a
    double ay = points[3] - points[1];     // ax and ay as above

    double bx = points[4] - points[6];     // direction of line b, reversed
    double by = points[5] - points[7];     // really -by and -by as above

    double dx = points[4] - points[0];   // right-hand side
    double dy = points[5] - points[1];

    double det = ax * by - ay * bx;

    if (det == 0) return false;

    double r = (dx * by - dy * bx) / det;
    double s = (ax * dy - ay * dx) / det;

    return !(r < 0 || r > 1 || s < 0 || s > 1);
}

/**
 * See if the
 * @param points
 * @return
 */
bool hasThreeColinearPoints(const std::vector<double> &points) {
    //check if co-linearity of 1,2,3 is same and 2,3,4.  If either is true, return true.
    double val = (points[3] - points[1]) * (points[4] - points[2]) - (points[2] - points[0]) * (points[5] - points[3]);
    if (val == 0) {
        return ((points[5] - points[3]) * (points[6] - points[4]) -
                (points[4] - points[2]) * (points[7] - points[5])) == 0;
    }

    return false;

}