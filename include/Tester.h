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

public:
	float angularSpeed;

	DummyWheel(void);
	DummyWheel(float argInertia, float argViscousFriction, float argTimeStep = 0.03333333f);
	void update(float argInputTorque, float *argFeedbackTorque = 0);
};

struct TestCase
{
	EngineProps engineProps;
	GearBoxProps gearBoxProps;
	DifferentialProps differentialProps;
	DummyWheel dummyWheel;

	float timestep = 0.03333333f;
};
class Tester
{
private:
	Engine *engine;
	GearBox *gearBox;
	Differential *differential;
	Powertrain *powertrain;
	DummyWheel dummyWheel;

	Logger logger;

public:
	Tester(TestCase argTestCase);
	~Tester(void);
};

#endif //TESTER_H_INCLUDED