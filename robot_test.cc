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

	world.filesPath("./Auxiliary/");
	world.baseFileName("CoordsTimeInstant");
	world.fileNameScheme(NO_LEADING_ZEROES);	
	world.loadData();
	
	for(int i = 0; i < 100; i++)
	{
		cout << "Creating robot...\n";
		
		NNRobot robot;
		
//		cout << "Creating sensors...\n";
		
		vector <NNAlgaeSensor> algae_sensors;
		
		algae_sensors.push_back(NNAlgaeSensor(TOP, 0.1));
		algae_sensors.push_back(NNAlgaeSensor(BOTTOM, 0.1));
		algae_sensors.push_back(NNAlgaeSensor(FRONT, 0.1));
		algae_sensors.push_back(NNAlgaeSensor(BACK, 0.1));
		algae_sensors.push_back(NNAlgaeSensor(LEFT, 0.1));
		algae_sensors.push_back(NNAlgaeSensor(RIGHT, 0.1));
		
//		cout << "Adding sensors to robot...\n";
		
		for(vector <NNAlgaeSensor>::iterator i = algae_sensors.begin(); i != algae_sensors.end(); i++)
		{
			i->setWorld(&world);
			robot.addSensor(*i);
		}
		
//		cout << "Placing robot in the middle of the algae cloud...\n";
		
		robot.updatePosition(Point3D(15, 15, -15));
		
//		cout << "Running the robots!\n";
		
		robot.run();
		
		cout << robot.position() << endl;
	}
	
	return 0;
}
