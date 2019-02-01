//
// Created by Will Dunn on 2019-01-29.
//

#pragma once
#include <vector>
#include <string>
/**
 * This routine serves as a list of error types which will have different behaviors based on the argument passed in.
 * @param errorNumber
 */
void errorType(int errorNumber); //todo possibly change the return value of this function
bool hasPointsThatCoincide(const std::vector<double> &points);
bool hasCrossingLineSegments(int aX, int aY, int bX, int bY, int cX, int cY, int dX, int dY);
bool hasThreeColinearPoints(const std::vector<double> &points);


