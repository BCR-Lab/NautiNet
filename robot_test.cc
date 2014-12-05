#include <iostream>
#include <vector>
#include "Point3D.h"
#include "NNRobot.h"
#include "NNWorld.h"
#include "NNAlgaeSensor.h"
using namespace std;

int main()
{
	NNWorld world;

	world.filesPath("/Users/obormot/Documents/BC Files/2014 Fall/CISC 4900/ParticleDistribution/");
	world.baseFileName("CoordsTimeInstant");
	world.fileNameScheme(NO_LEADING_ZEROES);	
	world.loadData();
	
	cout << "Creating robot...\n";
	
	NNRobot robot;
	
	cout << "Creating sensors...\n";
	
	vector <NNAlgaeSensor> algae_sensors;
	
	algae_sensors.push_back(NNAlgaeSensor(TOP, 0.1));
	algae_sensors.push_back(NNAlgaeSensor(BOTTOM, 0.1));
	algae_sensors.push_back(NNAlgaeSensor(FRONT, 0.1));
	algae_sensors.push_back(NNAlgaeSensor(BACK, 0.1));
	algae_sensors.push_back(NNAlgaeSensor(LEFT, 0.1));
	algae_sensors.push_back(NNAlgaeSensor(RIGHT, 0.1));
	
	cout << "Adding sensors to robot...\n";
	
	for(vector <NNAlgaeSensor>::iterator i = algae_sensors.begin(); i != algae_sensors.end(); i++)
	{
		i->setWorld(&world);
		robot.addSensor(*i);
	}
	
	cout << "Placing robot in the middle of the algae cloud...\n";
	
	robot.updatePosition(Point3D(10000, 5000, -2));
	
	cout << "Running the robot!\n";
	
	robot.run();
	
	return 0;
}
