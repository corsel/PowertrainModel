#include <iostream>
#include "Utilities.h"
#include "Powertrain.h"

int main()
{
	ScalarField torqueMap;
	torqueMap.getDataFromFile("data/EngineMap.csv");

	EngineProps engineProps(torqueMap, 1.0f);
	Engine engine(engineProps);

	std::vector<float> gearRatio;
	gearRatio.push_back(-1.0f);
	gearRatio.push_back(1.0f);
	gearRatio.push_back(1.5f);
	gearRatio.push_back(2.0f);
	GearBoxProps gearBoxProps(gearRatio);
	GearBox gearBox(gearBoxProps);

	DifferentialProps differentialProps(0.5f);
	Differential differential(differentialProps);

	Powertrain powertrain(&engine, &gearBox, &differential);

	int a; std::cin >> a;

	return 0;
}