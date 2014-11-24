#ifndef NN_ROBOT_H
#define NN_ROBOT_H

#include <queue>
#include "Point3D.h"
#include "Matrix.h"
using namespace std;

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
	
	public:
	
		// CONSTRUCTORS
		
		// ACCESSORS
		
		Point3D position() const
			{ return position_; }
			
		Point3D lastPosition() const
			{ return ( position_history.empty() ? position_ : position_history.back() ); }
			
		queue <Point3D> positionHistory() const
			{ return position_history; }
		
		Matrix orientation() const
			{ return orientation_; }
};

#endif
