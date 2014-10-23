#ifndef POINT3D_H
#define POINT3D_H

// A point in 3D space.
struct Point3D
{
	double x;
	double y;
	double z;

	Point3D(double x, double y, double z) : x(x), y(y), z(z) { }
	Point3D() : x(0), y(0), z(0) { }
};

#endif
