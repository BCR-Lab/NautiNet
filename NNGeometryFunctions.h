#ifndef NN_GEOMETRY_FUNCTIONS_H
#define NN_GEOMETRY_FUNCTIONS_H

#include "Point3D.h"
#include "Matrix.h"

namespace nn
{
	bool isPointInCone(Point3D point, Point3D cone_apex, Point3D cone_base_center, double cone_base_radius);
	bool isPointInCone(Point3D point, Point3D cone_apex, Point3D cone_base_center, double cone_base_radius, Matrix cone_orientation);
};

#endif
