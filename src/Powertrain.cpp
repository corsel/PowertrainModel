#include "Powertrain.h"

//Engine Class
EngineProps::EngineProps() {}
EngineProps::EngineProps(ScalarField argTorqueMap, float argInertia, float argClutchMaxViscosity, float argInternalLoss)
: torqueMap(argTorqueMap), inertia(argInertia), clutchMaxViscosity(argClutchMaxViscosity), internalLoss(argInternalLoss) {}

Engine::Engine(EngineProps argProperties, Powertrain *argParent)
: properties(argProperties), parent(argParent), flywheelAngularSpeed(10.0f) {}

//GearBox Class
GearBoxProps::GearBoxProps() {}
GearBoxProps::GearBoxProps(std::vector<float> argGearRatio, float argInertia, float argInternalLoss)
: gearRatio(argGearRatio), internalLoss(argInternalLoss) {}

GearBox::GearBox(GearBoxProps argProperties, Powertrain *argParent)
: properties(argProperties), parent(argParent), activeGear(0) {}
void GearBox::setGear(int argGear)
{
	activeGear = argGear;
}

//Differential Class
DifferentialProps::DifferentialProps() {}
DifferentialProps::DifferentialProps(float argGearRatio, float argDiffLock)
: gearRatio(argGearRatio), diffLock(argDiffLock) {}

Differential::Differential(DifferentialProps argProperties, Powertrain *argParent)
: properties(argProperties), parent(argParent) {}

//Powertrain Class
PowertrainInput::PowertrainInput() {}
PowertrainInput::PowertrainInput(float argClutch, float argThrottle, float argFeedbackTorque, float argWheelAngularSpeed)
: clutch(argClutch), throttle(argThrottle), feedbackTorque(argFeedbackTorque), wheelAngularSpeed(argWheelAngularSpeed) {}

Powertrain::Powertrain(Engine *argEngine, GearBox *argGearBox, Differential *argDifferential, float argTimeStep)
: engine(argEngine), gearBox(argGearBox), differential(argDifferential), timeStep(argTimeStep), tFlywheelCumulative(0.0f) {}
Powertrain::~Powertrain() {}
float Powertrain::update(PowertrainInput argInput)
{
	if (engine->flywheelAngularSpeed < 10.0f)
	{
		std::cout << "Powertrain::update debug: Engine idle interference.\n";
		argInput.throttle += 0.05f;
	}
	float t_eng = engine->properties.torqueMap.getInterpolatedData(Utils::radPerSecToRpm(engine->flywheelAngularSpeed), argInput.throttle);
	float t_loss = engine->properties.internalLoss * engine->flywheelAngularSpeed;
	float t_flywheel = t_eng - t_loss - argInput.feedbackTorque;
	tFlywheelCumulative += t_flywheel * timeStep;
	engine->flywheelAngularSpeed = tFlywheelCumulative / engine->properties.inertia;
	float torqueOut = (argInput.wheelAngularSpeed - engine->flywheelAngularSpeed) * engine->properties.clutchMaxViscosity * argInput.clutch;

	return torqueOut;
}