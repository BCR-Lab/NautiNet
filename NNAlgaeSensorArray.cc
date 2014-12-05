#include "NNAlgaeSensorArray.h"
#include "Point3D.h"
#include <cstring>
#include <cmath>
using namespace std;

// CONSTRUCTORS AND DESTRUCTORS

NNAlgaeSensorArray::NNAlgaeSensorArray() :
	robot (NULL)
	{ }

// FUNCTIONS

NNAlgaeSensorGradient NNAlgaeSensorArray::algaeGradient() const
{
	return lastAlgaeGradientReading;
}

void NNAlgaeSensorArray::updateSensorValues()
{
	// First, update the sensor values for all the individual sensors.
	int i = 1;
	for(vector <NNAlgaeSensor>::iterator sensor = sensor_array.begin(); sensor != sensor_array.end(); sensor++)
	{
		cout << "Updating sensor value for sensor # " << i++ << "...\n";
		(*sensor).updateSensorValue();
	}
	
	// Aggregate the data from the sensors into the NNAlgaeSensorGradient object.
	// NOT YET IMPLEMENTED!!!
	;
}

Matrix NNAlgaeSensorArray::greatestAlgaeConcentrationBearing() const
{
	// Index of sensor showing greatest algae concentration.
	int index = 0;
	
	cout << "Orientation of sensor #1:\n";
	sensor_array[0].orientation().print();
	cout << "Algae concentration from sensor #1: " << sensor_array[0].sensorValue() << endl;
	
	// Look through all the sensor arrays, find the one with the highest value (i.e. reading algae concentration reading), return its orientation.
	for(int i = 1; i < sensor_array.size(); i++)
	{
		cout << "Orientation of sensor #" << i+1 << ":\n";
		sensor_array[i].orientation().print();

		cout << "Algae concentration from sensor #" << i+1 << ": " << sensor_array[i].sensorValue() << endl;
	
		if(sensor_array[i].sensorValue() > sensor_array[index].sensorValue())
			index = i;
	}
	
	return sensor_array[index].orientation();
}

void NNAlgaeSensorArray::setRobot(NNRobot* robot)
{
	this->robot = robot;
}

void NNAlgaeSensorArray::addSensor(const NNAlgaeSensor& sensor)
{
	// In the deployment version, NNAlgaeSensor should have some sort of hardware ID that may be queried, to test whether two sensor objects refer to the same physical sensor. In such a case, we may want to prevent the user of the NNAlgaeSensorArray class to add redundant NNAlgaeSensor objects to the sensor array.
	// For the simulation version, we assume that any two NNAlgaeSensor objects always refer to different physical sensors (even if they are, in fact, the same object in memory), and perform no checks.
	
	sensor_array.push_back(sensor);
}

void NNAlgaeSensorArray::printSensorGradient(ostream& out) const
{
	out << "Current sensor value is:" << endl;
	out << "Positive x: " << lastAlgaeGradientReading.x_pos_dir_concentration << endl;
	out << "Negative x: " << lastAlgaeGradientReading.x_neg_dir_concentration << endl;
	out << "Positive y: " << lastAlgaeGradientReading.y_pos_dir_concentration << endl;
	out << "Negative y: " << lastAlgaeGradientReading.y_neg_dir_concentration << endl;
	out << "Positive z: " << lastAlgaeGradientReading.z_pos_dir_concentration << endl;
	out << "Negative z: " << lastAlgaeGradientReading.z_neg_dir_concentration << endl;
	
}
