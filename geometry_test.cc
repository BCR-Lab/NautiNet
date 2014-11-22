#include <iostream>
#include "Point3D.h"
#include "NNGeometryFunctions.h"
using namespace std;

int main()
{
	cout << "The point " << (nn::isPointInCone(Point3D(0, 4, 0), Point3D(0, 0, 0), Point3D(0, 5, 0), 3) ? "is" : "is not") << " in the cone.\n";

	return 0;
}
