#include <iostream>
#include "NNAlgaeSensor.h"
#include "Point3D.h"

using namespace std;

int main()
{
	NNWorld world;
	
	NNAlgaeSensor sensor;
	sensor.setWorld(&world);
	
	sensor.printSensorValue();
	cout << "Updating sensor value...\n";
	sensor.updateSensorValue();
	sensor.printSensorValue();
	
	return 0;
}
