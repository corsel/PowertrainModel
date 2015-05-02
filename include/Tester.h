#ifndef TESTER_H_INCLUDED
#define TESTER_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>

class Tester
{
private:
	std::vector<float> value;
	std::string logFileName;
	std::vector<std::string> dataTags;
	std::ofstream file;

public:
	Tester(void);
	Tester(char *argLogFileName);
	void setDataTags(std::vector<std::string> argDataTags);
	void bindDataFile(char *argLogFileName);
	void appendData(float argValue);
	void flush(void);
	void shutdown(void);
};

#endif