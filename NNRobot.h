#ifndef NN_ROBOT_H
#define NN_ROBOT_H

#include "Point3D.h"
#include "Matrix.h"

class NNRobot
{
	private:
		Point3D position_;
		Matrix orientation_;
	
	public:
		Point3D position();
		Matrix orientation();
};

#endif
