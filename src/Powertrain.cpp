#include "PowerTrain.h"

//Engine Class
EngineProps::EngineProps() {}
EngineProps::EngineProps(ScalarField argTorqueMap, float argInertia, float argInternalLoss)
: torqueMap(argTorqueMap), inertia(argInertia), internalLoss(argInternalLoss) {}

Engine::Engine(EngineProps argProperties, Powertrain *argParent)
: properties(argProperties), parent(argParent) {}

//GearBox Class
GearBoxProps::GearBoxProps() {}
GearBoxProps::GearBoxProps(std::vector<float> argGearRatio, float argInternalLoss)
: gearRatio(argGearRatio), internalLoss(argInternalLoss) {}

GearBox::GearBox(GearBoxProps argProperties, Powertrain *argParent)
: properties(argProperties), parent(argParent) {}

//Differential Class
DifferentialProps::DifferentialProps() {}
DifferentialProps::DifferentialProps(float argGearRatio, float argDiffLock)
: gearRatio(argGearRatio), diffLock(argDiffLock) {}

Differential::Differential(DifferentialProps argProperties, Powertrain *argParent)
: properties(argProperties), parent(argParent) {}

//Powertrain Class
Powertrain::Powertrain(Engine *argEngine, GearBox *argGearBox, Differential *argDifferential, float argTimeStep)
: engine(argEngine), gearBox(argGearBox), differential(argDifferential), timeStep(argTimeStep) {}