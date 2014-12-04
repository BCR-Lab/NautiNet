#ifndef NN_PROXIMITY_SENSOR_H
#define NN_PROXIMITY_SENSOR_H

#include <iostream>
using namespace std;

// Forward declarations of world and robot classes, for compiler efficiency.
class NNWorld;
class NNRobot;

class NNProximitySensor
{
	private:
		// DATA MEMBERS
		
		// Reference to the robot which owns this sensor.
		NNRobot* robot;
		
		// *** FOR SIMULATION ONLY. ***
		// Reference to a world object. The world object is queried by the simulation version of the updateSensorValue method.
		NNWorld* world;
		
		// The most recently read sensor value. Initial value is 0.0.
		double lastSensorValue;
		
		// FUNCTIONS
	
	public:
		
		// CONSTRUCTORS
		
		// Default constructor.
		NNProximitySensor();
		
		// ACCESSORS
		
		// Assigns a robot object as the owner of this sensor.
		// (This should be the object which contains the NNProximitySensorArray that contains this sensor.)
		void setRobot(NNRobot* robot);
		
		// *** FOR SIMULATION ONLY. ***
		void setWorld(NNWorld* world);
		
		// Returns the current (i.e. most recently read) sensor value.
		double sensorValue();
		
		// FUNCTIONS
		
		// Updates the sensor value.
		// In the simulation version, this method queries an NNWorld object.
		// In the deployment version, this method calls drivers of a hardware sensor.
		void updateSensorValue();
		
		// Prints a line with the current (i.e. most recently read) sensor value to the provided output stream.
		void printSensorValue(ostream& out = cout);
};

#endif
