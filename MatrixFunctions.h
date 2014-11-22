#ifndef MATRIX_FUNCTIONS_H
#define MATRIX_FUNCTIONS_H

#include "Matrix.h"
#include "Point3D.h"

typedef enum
{
	X,
	Y,
	Z
} ROTATION_AXIS;

// Which rotation direction corresponds to rotation about which axis?
#define ROLL X
#define PITCH Y
#define YAW Z

Matrix make3DRotationMatrix(ROTATION_AXIS axis, double angle);
Matrix make3DTranslationMatrix(double deltaX, double deltaY, double deltaZ);
Matrix make3DScaleMatrix(double xScale, double yScale, double zScale);

Matrix translationMatrixFromPoint(Point3D p);

Matrix rotationMatrixFromPoints(Point3D p, Point3D q);

Matrix pointVectorFromPoint(Point3D p);
Point3D pointFromPointVector(Matrix m);

#endif
