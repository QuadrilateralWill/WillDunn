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
bool isInvalidCharacter(std::string inputString);
bool hasInvalidCharacters(const std::vector<double> &points);
bool hasPointsThatCoincide(const std::vector<double> &points);
bool hasCrossingLineSegments(const std::vector<double> &points);
bool hasThreeColinearPoints(const std::vector<double> &points);


