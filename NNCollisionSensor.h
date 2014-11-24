#ifndef NN_COLLISION_SENSOR_H
#define NN_COLLISION_SENSOR_H

#include <iostream>
#include "Matrix.h"
#include "NNSensorUtility.h"
using namespace std;

// Forward declarations of world and robot classes, for compiler efficiency.
class NNWorld;
class NNRobot;

// #define SENSOR_CONE_HEIGHT 0.1	// 10 cm, in meters.
// #define SENSOR_CONE_ANGLE 54.0 * M_PI / 180.0	// 54 degrees, in radians.

class NNCollisionSensor
{
	private:
		
		// DATA MEMBERS
		
		// Reference to the robot which owns this sensor.
		NNRobot* robot;
		
		// *** FOR SIMULATION ONLY. ***
		// Reference to a world object. The world object is queried by the simulation version of the updateSensorValue method.
		NNWorld* world;
		
		// Offset, in meters, of the sensor from the center of the robot's body.
		double offset;
		
		// Rotation matrix representing orientation of sensor as rotation from reference orientation (facing toward positive X).
		Matrix orientation;
		
		// The most recently read sensor value. Initial value is false.
		bool lastSensorValue;
		
		// FUNCTIONS
	
	public:
		
		// CONSTRUCTORS
		
		// Declares an NNCollisionSensor with the given orientation and offset.
		NNCollisionSensor(Matrix orientation, double offset = 0);
		
		// Declares an NNCollisionSensor with a preset orientation and the given offset.
		NNCollisionSensor(NN_SENSOR_ORIENTATION_PRESET orientation, double offset = 0);
		
		// ACCESSORS
		
		// Assigns a robot object as the owner of this sensor.
		// (This should be the object which contains the NNCollisionSensorArray which contains this sensor.)
		void setRobot(NNRobot* robot);
		
		// *** FOR SIMULATION ONLY. ***
		// Provides the sensor with a reference to an NNWorld object.
		void setWorld(NNWorld* world);
		
		// Returns the current (i.e. most recently read) sensor value.
		bool sensorValue();
		
		// FUNCTIONS
		
		// Updates the sensor value.
		// In the simulation version, this method queries an NNWorld object.
		// In the deployment version, this method calls drivers of a hardware sensor.
		void updateSensorValue();
		
		// Prints a line with the current (i.e. most recently read) sensor value to the provided output stream.
		void printSensorValue(ostream& out = cout);
};

#endif
