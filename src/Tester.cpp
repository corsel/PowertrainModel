#include "Tester.h"

Tester::Tester() {}
Tester::Tester(char *argLogFileName)
{
	bindDataFile(argLogFileName);
}
void Tester::setDataTags(std::vector<std::string> argDataTags)
{
	dataTags = argDataTags;
}
void Tester::bindDataFile(char *argLogFileName)
{
	logFileName = argLogFileName;
	file.open(logFileName, std::ofstream::out | std::ofstream::trunc);
	for (int i = 0; i < dataTags.size(); i++)
	{
		file << dataTags[i] << ",";
	}
	file << "timestamp:" << time(0) <<  std::endl;
}
void Tester::appendData(float argValue)
{
	value.push_back(argValue);
}
void Tester::flush()
{
	if (file.is_open())
	{
		for (int i = 0; i < value.size(); i++)
		{
			file << value[i] << ",";
		}
		file << std::endl;
		value.clear();
	}
	else
		std::cout << "Tester::flush warning: File is not open.\n";
}
void Tester::shutdown()
{
	file.close();
}