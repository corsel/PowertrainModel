#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED
//#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#ifdef _WIN32
#include <string>
#else
#include <string.h>
#endif
#include <vector>
#include <fstream>

struct Power
{
	float angularSpeed, torque;
};
class ScalarField
{
private:
	std::vector< std::vector<float> >	value;
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

namespace Utils
{
const float pi = 3.141593f;

inline float radPerSecToRpm(float argRadPerSec)
{
	return (argRadPerSec / 2.0f / pi * 60.0f);
}
inline float rpmToRadPerSec(float argRpm)
{
	return (argRpm / 60.0f * 2.0f * pi);
}
}
#endif //UTILITIES_H_INCLUDED