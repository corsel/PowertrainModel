#include "Utilities.h"

//ScalarField Class
ScalarField::ScalarField() {}
ScalarField::ScalarField(std::vector<float> argRowDataPoints, std::vector<float> argColumnDataPoints)
:rowDataPoints(argRowDataPoints), columnDataPoints(argColumnDataPoints) {}
void ScalarField::printValueMatrix() //Debug
{
	for (int i = 0; i < value[0].size(); i++)
	{
		std::cout << "\t" << columnDataPoints[i];
	}
	std::cout << "\n\t-----------\n";
	for (int i = 0; i < value.size(); i++)
	{
		std::cout << rowDataPoints[i] << " |\t";
		for (int j = 0; j < value[0].size(); j++)
		{
			std::cout << value[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}
void ScalarField::fetchDataFromFile(const char *filePath) //Ramazan Alper
{
	columnDataPoints.clear();
	rowDataPoints.clear();
	value.clear();

	int	rowCount = 0,
		columnCount = 0,
		totalCount = 0;
	std::vector<float> data;
	std::ifstream inputFile;
	std::string line;
	char buffer[255];

	inputFile.open(filePath);
	if (!inputFile.is_open()) return;
	
	while (std::getline(inputFile, line)){
		strcpy(buffer, line.c_str());
		buffer[line.length()] = '\0';
		rowCount++;
		char *token = strtok(buffer, ",");
		while (token){
			float inVal = 0;
			sscanf(token, "%f", &inVal);
			data.push_back(inVal);
			token = strtok(NULL, ",");
			totalCount++;
		}
	}
	columnCount = totalCount / rowCount;
	for (int i = 1; i < data.size(); i++) //0th data is useless value
	{
		if (i < columnCount)
		{
			columnDataPoints.push_back(data[i]);
			continue;
		}
		if (i%columnCount == 0)
		{
			rowDataPoints.push_back(data[i]);
			continue;
		}
		static std::vector<float> temp;
		temp.push_back(data[i]);
		if (i%columnCount == columnCount-1)
		{
			value.push_back(temp);
			temp.clear();
		}		
	}
}
void ScalarField::appendRow(std::vector<float> argData)
{
	if (argData.size() != columnDataPoints.size())
	{
		std::cout << "ScalarField::appendRow warning: Incompatible column size. \n\tNumber of available columns: " << columnDataPoints.size() << ", entered number of columns: " << argData.size() << std::endl;
		return;
	}
	if (value.size() >= rowDataPoints.size())
	{
		std::cout << "ScalarField::appendRow warning: \n\tValue vector is full. Number of available rows: " << rowDataPoints.size() << std::endl;
		return;
	}
	value.push_back(argData);
}
float ScalarField::getInterpolatedData(float argRowKey, float argColumnKey)
{
	if (rowDataPoints.size() < 2 || columnDataPoints.size() < 2)
	{
		std::cout << "ScalarField::getInterpolatedData warning: Too few data points.\n\trowDataPoints.size(): " << rowDataPoints.size() << "\n\tcolumnDataPoints.size(): " << columnDataPoints.size() << std::endl;
		return 0.0f;
	}
	int	lowRowIndex = 0,
		lowColumnIndex = 0;
	if (argRowKey < rowDataPoints[0] ||
		argRowKey > rowDataPoints.back() ||
		argColumnKey < columnDataPoints[0] ||
		argColumnKey > columnDataPoints.back())
	{
		std::cout << "ScalarField::getInterpolatedData warning: Requested key out of bounds. \n\tkey:<" << argRowKey << ", " << argColumnKey << ">, bound:[<" << rowDataPoints[0] << "," << columnDataPoints[0] << ">, <" << rowDataPoints.back() << "," << columnDataPoints.back() << ">]\n";
		return 0.0f;
	}
	for (int i = 0; i < rowDataPoints.size() - 1; i++)
	{
		if (argRowKey >= rowDataPoints[i] && argRowKey <= rowDataPoints[i + 1])
		{
			lowRowIndex = i;
			break;
		}
	}
	for (int i = 0; i < columnDataPoints.size(); i++)
	{
		if (argColumnKey >= columnDataPoints[i] && argColumnKey <= columnDataPoints[i + 1])
		{
			lowColumnIndex = i;
			break;
		}
	}
	float	rowLow = rowDataPoints[lowRowIndex],
			rowHigh = rowDataPoints[lowRowIndex+1],
			columnLow = columnDataPoints[lowColumnIndex],
			columnHigh = columnDataPoints[lowColumnIndex+1];

	float	value00 = value[lowRowIndex][lowColumnIndex],
			value10 = value[lowRowIndex+1][lowColumnIndex],
			value01 = value[lowRowIndex][lowColumnIndex+1],
			value11 = value[lowRowIndex+1][lowColumnIndex+1];

	float	valueHalf0 = value00 + (value10 - value00) / (rowHigh - rowLow) * (argRowKey - rowLow),
			valueHalf1 = value01 + (value11 - value01) / (rowHigh - rowLow) * (argRowKey - rowLow);

	return valueHalf0 + (valueHalf1 - valueHalf0) / (columnHigh - columnLow) * (argColumnKey - columnLow);
}