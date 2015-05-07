#include "PowertrainSimple.h"

bool printDebugMessages = false;

PowertrainSimpleInput::PowertrainSimpleInput(float argThrottle, float argWheelAngularSpeed)
: throttle(argThrottle), wheelAngularSpeed(argWheelAngularSpeed) {}
PowertrainSimple::PowertrainSimple(ScalarField argEngineTorqueMap, std::vector<float> argGearRatio)
: torqueMap(argEngineTorqueMap), gearRatio(argGearRatio) {}
float PowertrainSimple::getTorqueOutput(PowertrainSimpleInput argInput)
{
	if (activeGear == 0)
		return 0.0f;
	engineRpm = argInput.wheelAngularSpeed / gearRatio[activeGear - 1];
	return (torqueMap.getInterpolatedData(engineRpm, argInput.throttle) / gearRatio[activeGear - 1]);
}
void PowertrainSimple::setClutchPressed(bool argClutchPressed)
{
	clutchPressed = argClutchPressed;
}
void PowertrainSimple::shiftGear(int argGear)
{
	if (!clutchPressed)
	{
		if (printDebugMessages)
			std::cout << "PowertrainSimple::shiftGear Debug: Gear shift attempt with unpressed clutch.\n";
		return;
	}
	else if (argGear >= gearRatio.size() || argGear < -1)
	{
		if (printDebugMessages)
			std::cout << "PowertrainSimple::shiftGear Debug: Invalid gear value.\n";
		return;
	}
	else
		activeGear = argGear;
}
float PowertrainSimple::getEngineRpm()
{
	return engineRpm;
}