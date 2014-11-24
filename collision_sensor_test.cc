#include <iostream>
#include <cmath>
#include "NNCollisionSensor.h"
#include "Matrix.h"
#include "MatrixFunctions.h"
using namespace std;

int main()
{
	NNWorld* world;
	NNRobot* robot;
	
	Matrix orientation = make3DRotationMatrix(PITCH, M_PI/2);
	double offset = 0.1;	// 10 cm.
	
	NNCollisionSensor sensor(orientation, offset);
	sensor.setWorld(world);
	sensor.setRobot(robot);
	
	sensor.printSensorValue();
	cout << "Updating sensor value...\n";
	sensor.updateSensorValue();
	sensor.printSensorValue();
	
	return 0;
}
