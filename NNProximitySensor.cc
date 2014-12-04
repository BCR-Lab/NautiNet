#include "NNProximitySensor.h"
#include "Point3D.h"
#include "NNRobot.h"
#include "NNWorld.h"

NNProximitySensor::NNProximitySensor() :
	lastSensorValue(0.0),
	robot (NULL),
	world (NULL)
	{ }
	
void NNProximitySensor::setRobot(NNRobot* robot)
{
	this->robot = robot;
}

void NNProximitySensor::setWorld(NNWorld* world)
{
	this->world = world;
}

double NNProximitySensor::sensorValue()
{
	return lastSensorValue;
}

void NNProximitySensor::updateSensorValue()
{
	lastSensorValue = world->lightIntensityAtPoint(robot->position());
}

void NNProximitySensor::printSensorValue(ostream& out)
{
	out << "Current sensor value is: " << lastSensorValue << "\n";
}