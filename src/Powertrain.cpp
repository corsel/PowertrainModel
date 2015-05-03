#include "Powertrain.h"

//Engine Class
EngineProps::EngineProps() {}
EngineProps::EngineProps(ScalarField argTorqueMap, float argInertia, float argClutchViscosity, float argInternalLoss)
: torqueMap(argTorqueMap), inertia(argInertia), clutchViscosity(argClutchViscosity), internalLoss(argInternalLoss) {}

Engine::Engine(EngineProps argProperties, Powertrain *argParent)
: properties(argProperties), parent(argParent) {}

//GearBox Class
GearBoxProps::GearBoxProps() {}
GearBoxProps::GearBoxProps(std::vector<float> argGearRatio, float argInertia, float argInternalLoss)
: gearRatio(argGearRatio), internalLoss(argInternalLoss) {}

GearBox::GearBox(GearBoxProps argProperties, Powertrain *argParent)
: properties(argProperties), parent(argParent), activeGear(0) {}
void GearBox::setGear(int argGear)
{

}

//Differential Class
DifferentialProps::DifferentialProps() {}
DifferentialProps::DifferentialProps(float argGearRatio, float argDiffLock)
: gearRatio(argGearRatio), diffLock(argDiffLock) {}

Differential::Differential(DifferentialProps argProperties, Powertrain *argParent)
: properties(argProperties), parent(argParent) {}

//Powertrain Class
PowertrainInput::PowertrainInput() {}
PowertrainInput::PowertrainInput(float argClutch, float argThrottle, float argWheelFriction, float argWheelRpm)
: clutch(argClutch), throttle(argThrottle), wheelFriction(argWheelFriction), wheelRpm(argWheelRpm) {}

Powertrain::Powertrain(Engine *argEngine, GearBox *argGearBox, Differential *argDifferential, float argTimeStep)
: engine(argEngine), gearBox(argGearBox), differential(argDifferential), timeStep(argTimeStep) 
{
#ifdef TEST_MODE
	std::vector<std::string> dataTags;
	dataTags.push_back("throttle");
	dataTags.push_back("clutch");
	dataTags.push_back("t_wheel");
	dataTags.push_back("t_flywheel");
	dataTags.push_back("flywheelRpm");
	dataTags.push_back("torqueOut");
	tester.setDataTags(dataTags);
	tester.bindDataFile("data/EngineTestData.csv");
#endif
}
float Powertrain::update(PowertrainInput argInput)
{
	static float	w_w_prev = 0.0f,	//rpm of wheel and engine in previous frame,
					w_e_prev = 0.0f;	//used to calculate derivatives.
	
	float t_wheel = (argInput.wheelRpm - w_w_prev) / gearBox->properties.inertia / timeStep;
	float t_flywheel = (engine->flywheelRpm - w_e_prev) / engine->properties.inertia / timeStep;
	w_w_prev = argInput.wheelRpm;
	w_e_prev = engine->flywheelRpm;
	//update engine flywheel rpm
	engine->flywheelRpm = engine->properties.clutchViscosity * (engine->properties.torqueMap.getInterpolatedData(engine->flywheelRpm, argInput.throttle) - t_flywheel) + argInput.wheelRpm;
	//return torque output
	float torqueOut = -t_wheel - t_flywheel + engine->properties.torqueMap.getInterpolatedData(engine->flywheelRpm, argInput.throttle);
#ifdef TEST_MODE
	tester.appendData(argInput.throttle);
	tester.appendData(argInput.clutch);
	tester.appendData(t_wheel);
	tester.appendData(t_flywheel);
	tester.appendData(engine->flywheelRpm);
	tester.appendData(torqueOut);
	tester.flush();
#endif
	return torqueOut;
}
