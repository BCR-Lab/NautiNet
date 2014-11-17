#include "MatrixFunctions.h"
#include <cmath>
using namespace std;

Matrix make3DRotationMatrix(ROTATION_AXIS axis, double angle)
{
	Matrix r(IDENTITY, 4);
	
	switch(axis)
	{
		case X:
			r(1,1) = cos(angle);
			r(1,2) = -1 * sin(angle);
			r(2,1) = sin(angle);
			r(2,2) = cos(angle);
			break;
		case Y:
			r(0,0) = cos(angle);
			r(0,2) = sin(angle);
			r(2,0) = -1 * sin(angle);
			r(2,2) = cos(angle);
			break;
		case Z:
			r(0,0) = cos(angle);
			r(0,1) = -1 * sin(angle);
			r(1,0) = sin(angle);
			r(1,1) = cos(angle);
			break;
		default:
			// This is an error! Handle it somehow.
			;
			break;
	}
	
	return r;
}

Matrix make3DTranslationMatrix(double deltaX, double deltaY, double deltaZ)
{
	Matrix t(IDENTITY, 4);
	
	t(0,3) = deltaX;
	t(1,3) = deltaY;
	t(2,3) = deltaZ;
	
	return t;
}

Matrix make3DScaleMatrix(double xScale, double yScale, double zScale)
{
	Matrix s(IDENTITY, 4);
	
	s(0,0) = xScale;
	s(1,1) = yScale;
	s(2,2) = zScale;
	
	return s;
}
