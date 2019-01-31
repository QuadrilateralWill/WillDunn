//
// Created by Will Dunn on 1/15/19.
//

#include <iostream>
#include "ParallelAndCongruentFunctions.h"

double slopeToCompare1, slopeToCompare2, dx, dy, distanceOfSideOne, distanceOfSideTwo, distanceOfSideThree, distanceOfSideFour;

///returns true if both sides are parallel (in pairs)
bool hasBothSidesParallel(const std::vector<double> &points) {
    return parallelSideCount(points) == 2;
}

///returns true if one of the pair of sides is parallel, but not the other pair
bool hasOneParallelSide(const std::vector<double> &points) {
    return parallelSideCount(points) == 1;
}

///returns true if there is a pair of congruent sides
bool hasTwoCongruentSides(const std::vector<double> &points) {
    return congruentSideCount(points) == 1;
}

///returns true if all sides are congruent
bool hasFourCongruentSides(const std::vector<double> &points) {
    return congruentSideCount(points) == 2;
}

///returns true if the parallelogram in question has four right angles
bool hasFourRightAngles(const std::vector<double> &points) {
    //check if point 1 is a right angle by matching x of second point and y of fourth point
    if (points[6] != 0 || points[3] != 0) return false;

    //check if point 3 is a right angle by matching x of fourth point and y of second point
    if (points[4] != points[2] || points[5] != points[7]) return false;

    return true; //default return if none of if statement triggered
}


/**
 * Slope is okay with division by 0 because 0 will be the result, as it should be.
 * @param points
 * @returns 0, 1, 2 for the number of pairs that are parallel amongst the points passed in
 */
int parallelSideCount(const std::vector<double> &points) {
    int parallelCount = 0;

    //evaluate side 1 and 3 for parallelism
    dx = points[2] - 0;
    dy = points[3] - 0;
    slopeToCompare1 = dy / dx;
    dx = points[6] - points[4];
    dy = points[7] - points[5];
    slopeToCompare2 = dy / dx;
    if (slopeToCompare1 == slopeToCompare2) parallelCount++;

    //evaluate side 2 and 4 for parallelism
    dx = points[4] - points[2];
    dy = points[5] - points[3];
    slopeToCompare1 = dy / dx;
    dx = points[6] - 0;
    dy = points[7] - 0;
    slopeToCompare2 = dy / dx;
    if (slopeToCompare1 == slopeToCompare2) parallelCount++;

    return parallelCount;
}

///counts the number of congruent side pairs
int congruentSideCount(const std::vector<double> &points) {
    int congruentCount = 0;

    //evaluate side 1 for distance  todo redo these to utilize the distance formula function; makes it cleaner
    dx = (points[2] - 0) * (points[2] - 0);
    dy = (points[3] - 0) * (points[3] - 0);
    distanceOfSideOne = sqrt(dx + dy);

    //evaluate side 2 for distance
    dx = (points[4] - points[2]) * (points[4] - points[2]);
    dy = (points[5] - points[3]) * (points[5] - points[3]);
    distanceOfSideTwo = sqrt(dx + dy);

    //evaluate side 3 for distance
    dx = (points[6] - points[4]) * (points[6] - points[4]);
    dy = (points[7] - points[5]) * (points[7] - points[5]);
    distanceOfSideThree = sqrt(dx + dy);

    //evaluate side 4 for distance
    dx = (points[6] - 0) * (points[6] - 0);
    dy = (points[7] - 0) * (points[7] - 0);
    distanceOfSideFour = sqrt(dx + dy);

    //works because you are only dealing with parallelograms at this point
    if (distanceOfSideOne == distanceOfSideTwo) congruentCount++;
    if (distanceOfSideOne == distanceOfSideThree) congruentCount++;
    if (distanceOfSideOne == distanceOfSideFour) congruentCount++;

    return congruentCount;
}
