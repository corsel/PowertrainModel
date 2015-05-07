#include "Logger.h"

//Logger Class
Logger::Logger() {}
Logger::Logger(char *argLogFileName)
{
	bindDataFile(argLogFileName);
}
void Logger::setDataTags(std::vector<std::string> argDataTags)
{
	dataTags = argDataTags;
}
void Logger::bindDataFile(char *argLogFileName)
{
	logFileName = argLogFileName;
	file.open(logFileName, std::ofstream::out | std::ofstream::trunc);
	for (int i = 0; i < dataTags.size(); i++)
	{
		file << dataTags[i] << ",";
	}
	file << "timestamp:" << time(0) <<  std::endl;
}
void Logger::appendData(float argValue)
{
	value.push_back(argValue);
}
void Logger::flush()
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
		std::cout << "Logger::flush warning: File is not open.\n";
}
void Logger::shutdown()
{
	file.close();
}
