#include "NNGeometryFunctions.h"
#include <iostream>
#include "MatrixFunctions.h"
using namespace std;

bool nn::isPointInCone(Point3D point, Point3D cone_apex, Point3D cone_base_center, double cone_base_radius)
{
	// Construct a transformation matrix to represent the orientation of the cone (apex to base center).
	Matrix cone_orientation(rotationMatrixFromPoints(cone_apex, cone_base_center));
	
	return nn::isPointInCone(point, cone_apex, cone_base_center, cone_base_radius, cone_orientation);
}

bool nn::isPointInCone(Point3D point, Point3D cone_apex, Point3D cone_base_center, double cone_base_radius, Matrix cone_orientation)
{
	cout << point << " " << cone_apex << " " << cone_base_center << endl;

	// Construct matrices to hold point vectors representing all three key points.
	Matrix point_vector(pointVectorFromPoint(point));
	Matrix cone_apex_vector(pointVectorFromPoint(cone_apex));
	Matrix cone_base_center_vector(pointVectorFromPoint(cone_base_center));
	
	cout << "The three points as point vectors:\n";
	
	point_vector.print();
	cone_apex_vector.print();
	cone_base_center_vector.print();
	
	cout << "Cone orientation matrix:\n";
	
	cone_orientation.print();
	
	cout << "Now we transpose it:\n";

	// Take the transpose of the cone orientation matrix, to get the inverse rotation.
	cone_orientation.transpose();
	
	cone_orientation.print();
	
	// Construct a transformation matrix consisting of a translation to place the cone's apex at the origin followed by a rotation to place the primary axis of the cone on the x-axis, with the base of the cone facing toward positive x.
	Matrix t(IDENTITY, 4);
	t *= make3DTranslationMatrix(-1 * cone_apex.x, -1 * cone_apex.y, -1 * cone_apex.z);
	t *= cone_orientation;
	
	// Apply the transformation matrix to the point vectors for the three key points.
	point_vector *= t;
	cone_apex_vector *= t;
	cone_base_center_vector *= t;
	
	// NOTE: at this point (hah), the apex of the cone should be at (0, 0, 0).
	
	// Convert the point vectors back into points.
	point = pointFromPointVector(point_vector);
	cone_apex = pointFromPointVector(cone_apex_vector);
	cone_base_center = pointFromPointVector(cone_base_center_vector);
	
	cout << point << " " << cone_apex << " " << cone_base_center << endl;
	
	// Now check to see if the point is between the two ends of the cone in its x-dimension:
	if(point.x < cone_apex.x || point.x > cone_base_center.x)
		return false;
		
	// If it is, see if the point actually falls within the cone by calculating how far away from the cone's primary axis it can be and still be in the cone, and comparing to how far away it actually is...
	// (A conic section parallel to the plane of a cone's base is a circle, and the radius of that circle is proportional to the distance between its center (which lies on the cone's primary axis) and the cone's apex.)
	double permissible_distance = cone_base_radius * (point.x / cone_base_center.x);
	printf("Permissible distance: %f\n", permissible_distance);
	
	// Since the cone's primary axis is collinear with the x-axis, the shortest distance from the point to the cone's primary axis is a line that is parallel to the y-z plane, and its x-coordinate is the same as the point's x-coordinate. Its y and z coordinates are zero (because, again, it is collinear with the x-axis).
	double actual_distance = Point3D::distance(Point3D(point.x, 0, 0), point);
	printf("Actual distance: %f\n", actual_distance);
	
	return (actual_distance <= permissible_distance);
}
