#ifndef NN_ROBOT_H
#define NN_ROBOT_H

#include <queue>
#include <string>
#include "Point3D.h"
#include "Matrix.h"
#include "NNAlgaeSensorArray.h"
//#include "NNCollisionSensorArray.h"
//#include "NNProximitySensorArray.h"
#include "NNLocomotion.h"
using namespace std;

typedef enum
{
	START,
	FIND_CLOUD_EDGE,
	HOLD_CLOUD_EDGE,
	END
} NN_ROBOT_STATE;

class NNRobot
{
	private:
	
		// DATA MEMBERS
		
		// Current position of the robot.
		Point3D position_;
		
		// History of the robot's positions. Back of the queue is the last known position of the robot.
		queue <Point3D> position_history;
		
		// Orientation of the robot in space, relative to the absolute Cartesian coordinate axes.
		Matrix orientation_;
		
		// Current state of the robot (on the FSA control diagram).
		NN_ROBOT_STATE current_state;
		
		// Direction of movement.
		Matrix direction_;
		
		// Sensor arrays:
		
		NNAlgaeSensorArray algae_sensor_array;
//		NNCollisionSensorArray collision_sensor_array;
//		NNProximitySensorArray proximity_sensor_array;

		// Locomotion setups:
		
		NNLocomotion locomotion;
		
		// FUNCTIONS
		
		NN_ROBOT_STATE stateTransitionFromStart();
		NN_ROBOT_STATE stateTransitionFromFindCloudEdge();
		NN_ROBOT_STATE stateTransitionFromHoldCloudEdge();
		
		bool atCloudEdge();
		
	public:
	
		// CONSTRUCTORS
		
		NNRobot();
		
		// ACCESSORS
		
		Point3D position() const
			{ return position_; }
			
		Point3D lastPosition() const
			{ return ( position_history.empty() ? position_ : position_history.back() ); }
			
		queue <Point3D> positionHistory() const
			{ return position_history; }
		
		Matrix orientation() const
			{ return orientation_; }
			
		string status()
			{ return "Robot is OK."; }
			
		NN_ROBOT_STATE state()
			{ return current_state; }
			
		// FUNCTIONS
		
		void addSensor(NNAlgaeSensor sensor)
		{
			sensor.setRobot(this);
			algae_sensor_array.addSensor(sensor);
		}
			
//		void addSensor(NNCollisionSensor sensor)
//		{
//			sensor.setRobot(this);
//			collision_sensor_array.addSensor(sensor);
//		}
			
//		void addSensor(NNProximitySensor sensor)
//		{
//			sensor.setRobot(this);
//			proximity_sensor_array.addSensor(senosr);
//		}
		
		void updatePosition(Point3D new_position);
		
		void run();
};

#endif
