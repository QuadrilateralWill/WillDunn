//
// Created by Will Dunn on 2019-01-29.
//

#include <iostream>
#include "Errors.h"
#include "ParallelAndCongruentFunctions.h"

void errorType(int errorNumber) {
    switch (errorNumber) {
        case 1:
            std::cout
                    << "Error 1 - the line contains the wrong number of points, contains invalid characters, has coordinates out "
                       "of the range 0..100, or otherwise fails to describe three points (six integer values).\n";
            exit(-1);
        case 2:
            std::cout << "Error 2 - two points collide.\n";
            exit(-1);
        case 3:
            std::cout << "Error 3 - two line segments representing sides cross each other.\n";
            exit(-1);
        case 4:
            std::cout << "Error 4 - three points are colinear\n";
            exit(-1);
    }
}

bool hasPointsThatCoincide(const std::vector<double> &points) {
    for (int i = 0; i < points.size() - 1; i += 2) {
        for (int j = 2; j < points.size() - 1; j += 2) { //starting at two because you will start on the second point
            //check if the x-coordinate overlaps
            if (points[i] == points[j] && i != j) {
                //if so, check for an overlapping y-coordinate
                if (points[i + 1] == points[j + 1]) return true;
            }
        }
    }
    return false;
}

bool hasCrossingLineSegments(int aX, int aY, int bX, int bY, int cX, int cY, int dX, int dY) {
    return (((cX-aX)*(bY-aY) - (cY-aY)*(bX-aX))
            * ((dX-aX)*(bY-aY) - (dY-aY)*(bX-aX)) < 0)
           &&
           (((aX-cX)*(dY-cY) - (aY-cY)*(dX-cX))
            * ((bX-cX)*(dY-cY) - (bY-cY)*(dX-cX)) < 0);
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