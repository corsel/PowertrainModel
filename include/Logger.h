#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include "Utilities.h"
#include "Powertrain.h"

class Engine;
class GearBox;
class Differential;
class Powertrain;

class Logger
{
private:
	std::vector<float> value;
	char* logFileName;
	std::vector<std::string> dataTags;
	std::ofstream file;

public:
	Logger(void);
	Logger(char *argLogFileName);
	void setDataTags(std::vector<std::string> argDataTags);
	void bindDataFile(char *argLogFileName);
	void appendData(float argValue);
	void flush(void);
	void shutdown(void);
};

#endif