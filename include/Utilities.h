#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct Power
{
	float angularSpeed, torque;
};
class ScalarField
{
private:
	std::vector<std::vector<float>>	value;
	std::vector<float>	rowDataPoints,
						columnDataPoints;

public:
	ScalarField(void);
	ScalarField(std::vector<float> argRowDataPoints, std::vector<float> argColumnDataPoints);
	void printValueMatrix(void); //Debug
	void fetchDataFromFile(const char *argFileName);
	void appendRow(std::vector<float> argData);
	float getInterpolatedData(float argRowKey, float argColumnKey);
};

#endif //UTILITIES_H_INCLUDED