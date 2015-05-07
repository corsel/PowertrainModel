#ifndef POWERTRAINSIMPLE_H_INCLUDED
#define POWERTRAINSIMPLE_H_INCLUDED

#include <iostream>
#include <vector>
#include "Utilities.h"

//TODO: Implement reverse gear.

extern bool printDebugMessages;

struct PowertrainSimpleInput
{
	float throttle;
	float wheelAngularSpeed;

	PowertrainSimpleInput(float argThrottle, float argWheelAngularSpeed);
};
class PowertrainSimple
{
private:
	ScalarField torqueMap;
	std::vector<float> gearRatio;

	bool clutchPressed;
	float engineRpm;
	int activeGear;

public:
	PowertrainSimple(ScalarField argEngineTorqueMap, std::vector<float> argGearRatio);
	float getTorqueOutput(PowertrainSimpleInput argInput);
	void setClutchPressed(bool argClutchPressed);
	void shiftGear(int argGear);
	float getEngineRpm(void);
};

#endif //POWERTRAINSIMPLE_H_INCLUDED