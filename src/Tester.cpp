#include "Tester.h"

//DummyWheel Class
DummyWheel::DummyWheel() {}
DummyWheel::DummyWheel(float argInertia, float argViscousFriction, float argTimeStep)
: inertia(argInertia), viscousFriction(argViscousFriction), timeStep(argTimeStep) {}
void DummyWheel::update(float argTorque, float &argWheelAngularSpeed, float &argFeedbackTorque)
{
	angularSpeed += (argTorque - angularSpeed * viscousFriction) * timeStep / inertia;
	if (angularSpeed < 0.0f) angularSpeed = 0.0f;
	argFeedbackTorque = angularSpeed * viscousFriction;
	argWheelAngularSpeed = angularSpeed;
}

//Tester Class
Tester::Tester()
{

}