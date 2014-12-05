#include "NNRobot.h"
#include <stdlib.h>
using namespace std;

NNRobot::NNRobot() :
	orientation_(IDENTITY, 4)
{
	algae_sensor_array.setRobot(this);
	locomotion.setRobot(this);
}
	
void NNRobot::updatePosition(Point3D new_position)
{
	position_ = new_position;
}

void NNRobot::timeTick()
{
	// Have all sensor arrays update their values.
	cout << "Updating sensor values...\n";
	algae_sensor_array.updateSensorValues();
	
	// Find where the most algae is.
	cout << "Determing direction of greatest algae concentration in vicinity...\n";
	Matrix most_algae = algae_sensor_array.greatestAlgaeConcentrationBearing();
	cout << "That direction is:\n";
	most_algae.print();
	
	// Get the opposite direction.
	cout << "Determing reverse direction...\n";
	most_algae.transpose();
	cout << "Reverse direction is:\n";
	most_algae.print();
	
	// Move away from there.
	cout << "Moving...\n";
	locomotion.moveInDirection(most_algae, 0.1);
}

void NNRobot::run()
{
	static int time_tick = 0;

	while(1)
	{
		timeTick();
		
		cout << "Robot position: " << position_ << endl;
		
		sleep(1);
	}
}