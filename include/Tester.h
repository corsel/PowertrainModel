#ifndef TESTER_H_INCLUDED
#define TESTER_H_INCLUDED

#include "Powertrain.h"
#include "Logger.h"

class DummyWheel
{
private:
	float inertia;
	float viscousFriction;
	float timeStep;
	float angularSpeed;

public:
	DummyWheel(void);
	DummyWheel(float argInertia, float argViscousFriction, float argTimeStep = 0.03333333f);
	void update(float argInputTorque, float &argWheelAngularSpeed, float &argFeedbackTorque);
};

class Tester
{
private:
	Engine *engine;
	GearBox *gearbox;
	Differential *differential;
	Powertrain *powertrain;

	Logger logger;

public:
	Tester(void);
};

#endif //TESTER_H_INCLUDED