#ifndef POWERTRAIN_H_INCLUDED
#define POWERTRAIN_H_INCLUDED

#include "Utilities.h"

class Powertrain; //forward decleration 

struct EngineProps
{
	ScalarField torqueMap;
	float inertia;
	float internalLoss;

	EngineProps(void);
	EngineProps(ScalarField argTorqueMap, float argInertia, float argInternalLoss = 0.0f);
};
class Engine
{
private:
	EngineProps properties;
	Powertrain *parent;

public:
	Engine(EngineProps argProperties, Powertrain *argParent = 0);
};

struct GearBoxProps
{
	std::vector<float> gearRatio;
	float internalLoss;

	GearBoxProps(void);
	GearBoxProps(std::vector<float> argGearRatio, float argInternalLoss = 0.0f);
};
class GearBox
{
private:
	GearBoxProps properties;
	Powertrain *parent;

public:
	GearBox(GearBoxProps argProperties, Powertrain *argParent = 0);
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
	DifferentialProps properties;
	Powertrain *parent;

public:
	Differential(DifferentialProps argProperties, Powertrain *argParent = 0);
};

class Powertrain
{
private:
	Engine *engine;
	GearBox *gearBox;
	Differential *differential;

	float timeStep;

public:
	Powertrain(Engine *argEngine, GearBox *argGearBox, Differential *argDifferential, float argTimeStep = 0.0333333f); //default to 30fps
};

#endif //POWERTRAINELEMENTS_H_INCLUDED