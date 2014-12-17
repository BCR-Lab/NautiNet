#include "NNRobot.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "MatrixFunctions.h"

NNRobot::NNRobot() :
	position_ (Point3D(0, 0, 0)),
	orientation_ (IDENTITY, 4),
	current_state (START),
	direction_ (IDENTITY, 4)
{
	algae_sensor_array.setRobot(this);
	locomotion.setRobot(this);
}
	
void NNRobot::updatePosition(Point3D new_position)
{
	position_ = new_position;
}

NN_ROBOT_STATE NNRobot::stateTransitionFromStart()
{
	// Check if we're at the cloud edge.
	if(atCloudEdge())
	{
		return HOLD_CLOUD_EDGE;
	}
	else
	{
		// Pick a random direction...
 		srand(time(NULL));
 		double angleX = ((double) rand() / RAND_MAX) * M_PI * 2;
 		double angleY = ((double) rand() / RAND_MAX) * M_PI * 2;
 		double angleZ = ((double) rand() / RAND_MAX) * M_PI * 2;
 		direction_ *= make3DRotationMatrix(X, angleX);
 		direction_ *= make3DRotationMatrix(Y, angleY);
 		direction_ *= make3DRotationMatrix(Z, angleZ);
				
		return FIND_CLOUD_EDGE;
	}	
}

NN_ROBOT_STATE NNRobot::stateTransitionFromFindCloudEdge()
{
	// Check if we're at the cloud edge.
	if(atCloudEdge())
	{
		return HOLD_CLOUD_EDGE;
	}
	else
	{
		// Find where the most algae is.
// 		cout << "Determing direction of greatest algae concentration in vicinity...\n";
// 		Matrix most_algae = algae_sensor_array.greatestAlgaeConcentrationBearing();
// 		cout << "That direction is:\n";
// 		most_algae.print();
		
		// Get the opposite direction.
// 		cout << "Determing reverse direction...\n";
// 		most_algae.transpose();
// 		cout << "Reverse direction is:\n";
// 		most_algae.print();
		
		// Move away from there.
//		cout << "Moving...\n";
// 		locomotion.moveInDirection(most_algae, 0.1);
		
//		cout << "Robot position: " << this->position_ << endl;
		
		locomotion.moveInDirection(this->direction_, 0.1);

		return FIND_CLOUD_EDGE;
	}
}

NN_ROBOT_STATE NNRobot::stateTransitionFromHoldCloudEdge()
{
	// Check if we're at the cloud edge.
	if(atCloudEdge())
	{
//		return HOLD_CLOUD_EDGE;
		return END;
	}
	else
	{
		return FIND_CLOUD_EDGE;
	}
}

bool NNRobot::atCloudEdge()
{
	// Count how many algae sensors report algae. If it's more than one, we're not quite at the edge yet.
	vector <NNAlgaeSensorInfo> sensor_values = algae_sensor_array.sensorInfo();
	
	int num_sensors_showing_algae = 0;
	
	for(vector <NNAlgaeSensorInfo>::iterator sensor = sensor_values.begin(); sensor != sensor_values.end(); sensor++)
	{
		if(sensor->sensor_value > 0)
		{
//			cout << "Sensor pointing in\n";
//			sensor->orientation.print();
//			cout << " senses algae.\n";
			num_sensors_showing_algae++;
		}
	}
	
//	printf("Out of %d sensors, %d sense algae.\n", sensor_values.size(), num_sensors_showing_algae);
	
	return num_sensors_showing_algae <= 1;
}

void NNRobot::run()
{
	int time_tick = 0;

	while(current_state != END)
	{
		// Have all sensor arrays update their values.
//		cout << "Updating sensor values...\n";
		algae_sensor_array.updateSensorValues();
		
		// Check current state, and call appropriate state transition method.
		switch(current_state)
		{
			case START:
			default:
				current_state = stateTransitionFromStart();
				break;
			case FIND_CLOUD_EDGE:
				current_state = stateTransitionFromFindCloudEdge();
				break;
			case HOLD_CLOUD_EDGE:
				current_state = stateTransitionFromHoldCloudEdge();
				break;
			case END:
				break;
		}
		
//		cout << "Robot position: " << this->position_ << endl;
		
//		cout << ".";
		time_tick++;
//		sleep(0.1);
	}
	
	cout << endl << "Time ticks passed: " << time_tick << endl;
//	cout << this->position_ << endl;
}
