#include "Tester.h"

//DummyWheel Class
DummyWheel::DummyWheel() {}
DummyWheel::DummyWheel(float argInertia, float argViscousFriction, float argTimeStep)
: inertia(argInertia), viscousFriction(argViscousFriction), timeStep(argTimeStep) {}
void DummyWheel::update(float argTorque, float *argFeedbackTorque)
{
	angularSpeed += Utils::radPerSecToRpm((argTorque - Utils::rpmToRadPerSec(angularSpeed) * viscousFriction) * timeStep / inertia);
	if (angularSpeed < 0.0f) angularSpeed = 0.0f;
	if (argFeedbackTorque != 0)
		*argFeedbackTorque = angularSpeed * viscousFriction;
}
//Tester Class
Tester::Tester(TestCase argTestCase)
: dummyWheel(argTestCase.dummyWheel)
{
	engine = new Engine(argTestCase.engineProps);
	gearBox = new GearBox(argTestCase.gearBoxProps);
	differential = new Differential(argTestCase.differentialProps);
	powertrain = new Powertrain(engine, gearBox, differential, argTestCase.timestep);
}
Tester::~Tester()
{
	delete[] engine;
	delete[] gearBox;
	delete[] differential;
	delete[] powertrain;
}