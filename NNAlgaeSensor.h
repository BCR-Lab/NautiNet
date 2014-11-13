#ifndef NN_ALGAE_SENSOR_H
#define NN_ALGAE_SENSOR_H

#include "Matrix.h"

class NNAlgaeSensor
{
	private:
		
		// DATA MEMBERS
		
		// The robot which owns this sensor.
		NNRobot* robot;
		
		// Reference to a world object. Used for simulation.
		NNWorld* world;
	
		double offset;
		Matrix orientation;
		
		// The most recently read sensor value. Starts at 0.
		double lastSensorValue;
		
		// FUNCTIONS
		
		void updateSensorValue();
	
	public:
	
		// CONSTRUCTORS
		
		NNAlgaeSensor(double offset, Matrix orientation);
		
		// FUNCTIONS
		
		double getSensorValue();
};

#endif
