#ifndef POWERTRAIN_H_INCLUDED
#define POWERTRAIN_H_INCLUDED

#include "Utilities.h"

class Powertrain; //forward decleration 

struct EngineProps
{
	ScalarField torqueMap;
	float inertia;
	float internalLoss;
	float clutchMaxViscosity;

	EngineProps(void);
	EngineProps(ScalarField argTorqueMap, float argInertia, float argClutchMaxViscosity = 1.0f,  float argInternalLoss = 0.0f);
};
class Engine
{
private:
	friend class Powertrain;
	EngineProps properties;
	Powertrain *parent;

	float flywheelAngularSpeed;

public:
	Engine(EngineProps argProperties, Powertrain *argParent = 0);
};

struct GearBoxProps
{
	std::vector<float> gearRatio;
	float internalLoss;
	float inertia;

	GearBoxProps(void);
	GearBoxProps(std::vector<float> argGearRatio, float argInertia, float argInternalLoss = 0.0f);
};
class GearBox
{
private:
	friend class Powertrain;
	GearBoxProps properties;
	Powertrain *parent;
	int activeGear;

public:
	GearBox(GearBoxProps argProperties, Powertrain *argParent = 0);
	void setGear(int argGear);
};

struct DifferentialProps
{
	float gearRatio;
	float diffLock;

	DifferentialProps(void);
	DifferentialProps(float argGearRatio, float argDiffLock = 0.0f);
};
class Differential
{
private:
	friend class Powertrain;
	DifferentialProps properties;
	Powertrain *parent;

public:
	Differential(DifferentialProps argProperties, Powertrain *argParent = 0);
};

struct PowertrainInput
{
	float clutch;
	float throttle;
	float feedbackTorque;
	float wheelAngularSpeed;

	PowertrainInput();
	PowertrainInput(float argClutch, float argThrottle, float argFeedbackTorque, float argWheelAngularSpeed);
};
class Powertrain
{
private:
	Engine *engine;
	GearBox *gearBox;
	Differential *differential;
	float timeStep;
	float tFlywheelCumulative; //integration
	float frozenTFlywheelCumulative;

public:
	Powertrain(Engine *argEngine, GearBox *argGearBox, Differential *argDifferential, float argTimeStep = 0.0333333f); //default to 30fps
	~Powertrain(void);
	float update(PowertrainInput argInput);
};

#endif //POWERTRAINELEMENTS_H_INCLUDED