#ifndef NN_LOCOMOTION_H
#define NN_LOCOMOTION_H

#include "Point3D.h"
#include "Matrix.h"

// Forward declarations of world and robot classes, for compiler efficiency.
class NNRobot;

class NNLocomotion
{
	private:
		
		// DATA MEMBERS
		
		// The robot which owns this locomotion mechanism.
		NNRobot* robot;
		
		// FUNCTIONS
		
		// Second argument is vector representing direction and distance (linear displacement) of movement.
		Point3D moveFromPointAlongVector(Point3D start_point, Point3D movement_vector);
		
		// Second argument is a unit vector representing direction of movement; third argument is distance (linear displacement).
		Point3D moveFromPointInDirection(Point3D start_point, Point3D direction_vector, double distance);
		
		// Second argument is a rotation matrix representing direction of movement; third argument is distance (linear displacement).
		Point3D moveFromPointInDirection(Point3D start_point, Matrix direction_matrix, double distance);
		
		// Second argument is a target point (at which the movement should end).
		Point3D moveFromPointToPoint(Point3D start_point, Point3D target_point);
	
	public:
		
		// CONSTRUCTORS
		
		// ACCESSORS
		
		void setRobot(NNRobot* robot)
			{ this->robot = robot; }
		
		// FUNCTIONS
		
		void moveAlongVector(Point3D movement_vector);
		void moveInDirection(Point3D direction_vector, double distance);
		void moveInDirection(Matrix direction_matrix, double distance);
		void moveToPoint(Point3D target_point);
};

#endif
