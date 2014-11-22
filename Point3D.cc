#include "Point3D.h"
#include <cmath>
using namespace std;

double Point3D::distance(Point3D p, Point3D q)
{
	return sqrt(pow(q.x - p.x, 2) + pow(q.y - p.y, 2) + pow(q.z - p.z, 2));
}

ostream& operator<<(ostream& out, Point3D p)
{
	out << "(" << p.x << ", " << p.y << ", " << p.z << ")";
	return out;
}
