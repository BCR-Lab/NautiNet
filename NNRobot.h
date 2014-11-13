#ifndef NN_ROBOT_H
#define NN_ROBOT_H

#include "Point3D.h"
#include "Matrix.h"

class NNRobot
{
	private:
		Point3D position;
		Matrix orientation;
	
	public:
		Point3D getPosition();
		Matrix getOrientation();
}

#endif
