#ifndef NN_ALGAE_SENSOR_H
#define NN_ALGAE_SENSOR_H

#include "Matrix.h"
#include <iostream>
using namespace std;

// #include "NNWorld.h"
// #include "NNRobot.h"

class NNWorld;
class NNRobot;

class NNAlgaeSensor
{
	private:
		
		// DATA MEMBERS
		
		// The robot which owns this sensor.
		NNRobot* robot;
		
		// *** FOR SIMULATION ONLY. ***
		// Reference to a world object. The world object is queried by the simulation version of the updateSensorValue method.
		NNWorld* world;
		
		// Offset, in meters, of the sensor from the center of the robot's body.
		double offset;
		
		// Rotation matrix representing orientation of sensor as rotation from reference orientation (facing toward positive X).
		Matrix orientation;
		
		// The most recently read sensor value. Initial value is 0.
		double lastSensorValue;
		
		// FUNCTIONS
		
	public:
	
		// CONSTRUCTORS
		
		// Declares an NNAlgaeSensor with the given orientation and offset.
		NNAlgaeSensor(Matrix orientation, double offset = 0);
		
		// ACCESSORS
		
		// Assigns a robot object as the owner of this sensor.
		// (This should be the object which contains the NNAlgaeSensorArray which contains this sensor.)
		void setRobot(NNRobot* robot);
		
		// *** FOR SIMULATION ONLY. ***
		// Provides the sensor with a reference to an NNWorld object.
		void setWorld(NNWorld* world);
		
		// FUNCTIONS
		
		// Returns the current (i.e. most recently read) sensor value.
		double getSensorValue();
		
		// Updates the sensor value.
		// In the simulation version, this method queries an NNWorld object.
		// In the deployment version, this method calls drivers of a hardware sensor.
		void updateSensorValue();
		
		// Prints a line with the current (i.e. most recently read) sensor value to the provided output stream.
		void printSensorValue(ostream& out = cout);
};

#endif
