#include <iostream>

#define TEST_MODE

#ifdef TEST_MODE
#include "Tester.h"
#endif

#include "Utilities.h"
#include "Powertrain.h"

int main()
{
	
	ScalarField torqueMap;
	torqueMap.fetchDataFromFile("data/EngineMap.csv");

	EngineProps engineProps(torqueMap, 1.0f);
	Engine engine(engineProps);

	std::vector<float> gearRatio;
	gearRatio.push_back(-1.0f);
	gearRatio.push_back(1.0f);
	gearRatio.push_back(1.5f);
	gearRatio.push_back(2.0f);
	GearBoxProps gearBoxProps(gearRatio, 1.0f);
	GearBox gearBox(gearBoxProps);

	DifferentialProps differentialProps(0.5f);
	Differential differential(differentialProps);

	Powertrain powertrain(&engine, &gearBox, &differential);
	
	for (int i = 0; i < 1000; i++)
	{
		powertrain.update(PowertrainInput(1.0f, 1.0f, 0.0f, 1000.0f));
	}
	
	#ifdef TEST_MODE
	std::cout << "test mode.\n";
	#endif
	
	int a; std::cin >> a;

	return 0;
}