#include "NGE_Maths.h"
using namespace std;

int NGE_Discriminant(float a, float b, float c)
{
	//Calculate discrimiant
	double discrimiant = pow(b, 2) - (4 * a * c);

	//Number of solutions is based off whether the discrimiant is positive, negative or 0
	if (discrimiant > 0)
	{
		return 2;
	}
	else if (discrimiant == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

float NGE_QuadraticSolver(float a, float b, float c, bool bPositive)
{
	//Checks solutions exist
	if (NGE_Discriminant(a, b, c) == 0)
	{
		return -1;
	}
	else if (bPositive == true) //If there are mutiple solutions a solution is chosen via the boolean bPositive
	{
		return (-b + sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
	}
	else
	{
		return (-b - sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
	}
}

float NGE_Random(int lowerBound, int upperBound, float spacing)
{
	//TODO
	return 0;
}

string NGE_DoubleToString(double value)
{
	stringstream stream;
	stream << value;
	string valueAsString;
	stream >> valueAsString;
	return valueAsString;
}

double NGE_StringToDouble(string value)
{
	stringstream stream;
	stream << value;
	double valueAsDouble;
	stream >> valueAsDouble;
	return valueAsDouble;
}

int NGE_CalculateBearing(float right, float down)
{
	//If one direction has a legth of 0, we cannot use tan correctly
	if (right == 0 && down <= 0)
	{
		return 0;
	}
	else if (right == 0 && down > 0)
	{
		return 180;
	}
	else if (right > 0 && down == 0)
	{
		return 90;
	}
	else if (right < 0 && down == 0)
	{
		return 270;
	}
	else if (right > 0 && down > 0)
	{
		return DEGREES(atan(down / right)) + 90;
	}
	else if (right < 0 && down > 0)
	{
		return DEGREES(atan(MAGNITUDE(right) / down)) + 180;
	}
	else if (right > 0 && down < 0)
	{
		return DEGREES(atan(right / MAGNITUDE(down)));
	}
	else if (right < 0 && down < 0)
	{
		return DEGREES(atan(MAGNITUDE(down) / MAGNITUDE(right))) + 270;
	}
}

float NGE_CalculateResultant(float x, float y)
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

float NGE_CalcualteRightValue(int bearing, float resultant)
{
	return sin(RADIANS(bearing))*resultant;
}

float NGE_CalcualteDownValue(int bearing, float resultant)
{
	return -cos(RADIANS(bearing))*resultant;
}