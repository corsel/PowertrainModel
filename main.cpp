#include <iostream>
#include "Utilities.h"
#include "Powertrain.h"

int main()
{
	ScalarField torqueMap;
	torqueMap.fetchDataFromFile("data/EngineMap.csv");

	EngineProps engineProps(torqueMap, 10.0f, 3.0f, 0.2f);
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

	Powertrain powertrain(&engine, &gearBox, &differential, 0.003333333f);
	
	PowertrainInput input;
	input.clutch = 0.5f;
	input.throttle = 0.7f;
	input.wheelAngularSpeed= 50.0f;
	input.feedbackTorque = 100.0f;

	return 0;
}