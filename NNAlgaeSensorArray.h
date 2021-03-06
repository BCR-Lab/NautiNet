#ifndef NN_ALGAE_SENSOR_ARRAY_H
#define NN_ALGAE_SENSOR_ARRAY_H

#include <iostream>
#include <vector>
#include "NNAlgaeSensor.h"
using namespace std;

// Forward declarations of robot class, for compiler efficiency.
class NNRobot;

/*
 An NNAlgaeSensorGradient object represents the gradient of algae concentration around the robonaut. It has six values: concentration in the positive z direction, concentration in the negative z direction, and likewise for x and y.
	
 Note that z is vertical: +z is toward the surface, -z away from the surface. The x and y axes are arbitrary, but might correspond to geographic latitude and longitude, etc.
 */
struct NNAlgaeSensorGradient
{
	double x_pos_dir_concentration;
	double x_neg_dir_concentration;
	double y_pos_dir_concentration;
	double y_neg_dir_concentration;
	double z_pos_dir_concentration;
	double z_neg_dir_concentration;

	NNAlgaeSensorGradient(double xpos = 0, double xneg = 0, double ypos = 0, double yneg = 0, double zpos = 0, double zneg = 0) :
		x_pos_dir_concentration(xpos),
		x_neg_dir_concentration(xneg),
		y_pos_dir_concentration(ypos),
		y_neg_dir_concentration(yneg),
		z_pos_dir_concentration(zpos),
		z_neg_dir_concentration(zneg)
		{ }
};

struct NNAlgaeSensorInfo
{
	Matrix orientation;
	double sensor_value;
	
	NNAlgaeSensorInfo() :
		orientation (IDENTITY, 4),
		sensor_value (0.0)
		{ }
		
	NNAlgaeSensorInfo(Matrix orientation, double sensor_value) :
		orientation (orientation),
		sensor_value (sensor_value)
		{ }
};

/*
 An NNAlgaeSensorArray keeps and updates an NNAlgaeSensorGradient object, which represents the last known value for the gradient of algae concentration around the robonaut.
 */
class NNAlgaeSensorArray
{
	private:
		
		// DATA MEMBERS
		
		// The robot which owns this sensor array.
		NNRobot* robot;
		
		// The most recent sensor value.
		NNAlgaeSensorGradient lastAlgaeGradientReading;
		
		// The array of sensors.
		vector <NNAlgaeSensor> sensor_array;
		
		// FUNCTIONS
		
	public:
		
		// CONSTRUCTORS & DESTRUCTORS
		
		NNAlgaeSensorArray();
		
		// ACCESSORS
		
		NNAlgaeSensorGradient algaeGradient() const;
		
		Matrix greatestAlgaeConcentrationBearing() const;
		
		vector <NNAlgaeSensorInfo> sensorInfo() const;
		
		// FUNCTIONS
		
		void updateSensorValues();
	
		void setRobot(NNRobot* robot);
		
		void addSensor(const NNAlgaeSensor& sensor);
		
		void printSensorGradient(ostream& out = cout) const;
};

#endif
