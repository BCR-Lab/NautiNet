#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>
using namespace std;

// A point in 3D space.
struct Point3D
{
	double x;
	double y;
	double z;

	Point3D(double x, double y, double z) : x(x), y(y), z(z) { }
	Point3D() : x(0), y(0), z(0) { }
	
	static double distance(Point3D p, Point3D q);
	
	friend ostream& operator<<(ostream& out, Point3D p);
};

#endif
