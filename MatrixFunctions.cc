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
	
	t(3,0) = deltaX;
	t(3,1) = deltaY;
	t(3,2) = deltaZ;
	
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

Matrix translationMatrixFromPoint(Point3D p)
{
	return make3DTranslationMatrix(p.x, p.y, p.z);
}

Matrix rotationMatrixFromPoints(Point3D p, Point3D q)
{
	Matrix r(IDENTITY, 4);
	
	// Compute the deltas along each axis.
	double deltaX = q.x - p.x;
	double deltaY = q.y - p.y;
	double deltaZ = q.z - p.z;
	
	// Compute the linear distance.
	double distance = Point3D::distance(p, q);

	// Compute the angles of rotation around each axis.
	double angleX = deltaY > 0 ? asin(deltaZ / distance) : -1 * asin(deltaZ / distance) + M_PI;
	double angleY = deltaZ > 0 ? asin(deltaX / distance) : -1 * asin(deltaX / distance) + M_PI;
	double angleZ = deltaX > 0 ? asin(deltaY / distance) : -1 * asin(deltaY / distance) + M_PI;
	
	// Create unified rotation matrix.
	r *= make3DRotationMatrix(X, angleX) * make3DRotationMatrix(Y, angleY) * make3DRotationMatrix(Z, angleZ);
	
	return r;
}

Matrix pointVectorFromPoint(Point3D p)
{
	Matrix m(1, 4);

	m(0,0) = p.x;
	m(0,1) = p.y;
	m(0,2) = p.z;
	m(0,3) = 1.0;
	
	return m;
}

Point3D pointFromPointVector(Matrix m)
{
	return Point3D(m(0,0), m(0,1), m(0,2));
}
