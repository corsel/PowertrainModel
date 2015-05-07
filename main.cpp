#include <iostream>
#include "Utilities.h"
#include "Powertrain.h"
#include "PowertrainSimple.h"
#include "Tester.h"

#define SIMPLE_MODEL

int main()
{
#ifdef SIMPLE_MODEL
	ScalarField torqueMap;
	torqueMap.fetchDataFromFile("data/EngineMap.csv");
	std::vector<float> gearRatio;
	//TODO: Find actual doblo gear ratios.
	gearRatio.push_back(1.8f);
	gearRatio.push_back(2.1f);
	gearRatio.push_back(2.4f);
	gearRatio.push_back(2.7f);
	gearRatio.push_back(3.0f);
	PowertrainSimple powertrainSimple(torqueMap, gearRatio);

	DummyWheel dummyWheel(5.0f, 0.1f, 0.3f);
	dummyWheel.angularSpeed = 10.0f;

	powertrainSimple.setClutchPressed(1);
	powertrainSimple.shiftGear(1);
	powertrainSimple.setClutchPressed(0);

	Logger logger;
	std::vector<std::string> dataTags;
	dataTags.push_back("iteration");
	dataTags.push_back("wheel torque output");
	dataTags.push_back("engine rpm");
	dataTags.push_back("wheel rpm");
	logger.setDataTags(dataTags);
	logger.bindDataFile("data/PowertrainSimple_test.csv");
	int iteration = 0;
	for (int gear = 1; gear < 5; gear++)
	{
		powertrainSimple.setClutchPressed(1);
		powertrainSimple.shiftGear(gear);
		powertrainSimple.setClutchPressed(0);
		float torqueOutput = powertrainSimple.getTorqueOutput(PowertrainSimpleInput(0.8f, dummyWheel.angularSpeed));
		dummyWheel.update(torqueOutput);
		while (powertrainSimple.getEngineRpm() < Utils::rpmToRadPerSec(4000.0f) && iteration < 99999)
		{
			logger.appendData(iteration);
			float torqueOutput = powertrainSimple.getTorqueOutput(PowertrainSimpleInput(0.8f, dummyWheel.angularSpeed));
			logger.appendData(torqueOutput);
			dummyWheel.update(torqueOutput);
			logger.appendData(powertrainSimple.getEngineRpm());
			logger.appendData(dummyWheel.angularSpeed);
			logger.flush();
			iteration++;
		}
	}
#else
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
#endif
	return 0;
}