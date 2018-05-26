#ifndef NGE_MATHS_H
#define NGE_MATHS_H

using namespace std;

#include "NGE_Master.h"
#include <cmath>
#include <string>
#include <sstream>

//Convert degrees to radians
#define RADIANS(n)(n*(M_PI/180))
//Convert radians to degrees
#define DEGREES(n)(static_cast<int>(n*180/M_PI))
//Calculate the magintude of a number
#define MAGNITUDE(n)(sqrt(n*n))

//Calculate the number of solutions to a quadratic equation a^2x+bx+c
int NGE_Discriminant(float a, float b, float c);

//Calculate the solutions to a quadratic equation a^2x+bx+c
//bPositive sets whether to add or subtract in the quadric formula e.g. which, if there exists 2 solutions, do you want
float NGE_QuadraticSolver(float a, float b, float c, bool bPositive);

//Generates a random number in the provided range with the given spacing between potential values
float NGE_Random(int lowerBound, int upperBound, float spacing);

//Converts a double to a String
string NGE_DoubleToString(double value);

//Converts a String to a double
double NGE_StringToDouble(string value);

//Calculates the bearing of a line with the given right and down magnitudes
//It is given in degree between 0 and 360
//Down is 0, Right is 90, Up is 180 and Left is 270
int NGE_CalculateBearing(float right, float down);

//Calculates the resultant to 2 values
float NGE_CalculateResultant(float x, float y);

//Calculates the right directional magnitude of a line with a given beaing and resultant/total magnitude
double NGE_CalcualteRightValue(int bearing, float resultant);

//Calculates the down directional magnitude of a line with a given beaing and resultant/total magnitude
double NGE_CalcualteDownValue(int bearing, float resultant);

#endif