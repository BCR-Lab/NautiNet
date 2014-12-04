#include <iostream>
#include "NNProximitySensor.h"
#include "NNRobot.h"
#include "NNWorld.h"
using namespace std;

int main()
{
	NNWorld world;
	NNRobot robot;
	
	NNProximitySensor sensor;
	sensor.setWorld(&world);
	sensor.setRobot(&robot);
	
	sensor.printSensorValue();
	cout << "Updating sensor value...\n";
	sensor.updateSensorValue();
	sensor.printSensorValue();
	
	return 0;
}
