#include "NNLocomotion.h"
#include "MatrixFunctions.h"
#include "NNRobot.h"

void NNLocomotion::moveAlongVector(Point3D movement_vector)
{
	robot->updatePosition(moveFromPointAlongVector(robot->position(), movement_vector));
}

void NNLocomotion::moveInDirection(Point3D direction_vector, double distance)
{
	cout << " Calculating new position...\n";

	Point3D new_position = moveFromPointInDirection(robot->position(), direction_vector, distance);
	
	cout << " Moving...\n";
	
	robot->updatePosition(new_position);

	cout << " Moved.\n";
}

void NNLocomotion::moveInDirection(Matrix direction_matrix, double distance)
{
	robot->updatePosition(moveFromPointInDirection(robot->position(), direction_matrix, distance));
}

void NNLocomotion::moveToPoint(Point3D target_point)
{
	robot->updatePosition(moveFromPointToPoint(robot->position(), target_point));
}

Point3D NNLocomotion::moveFromPointAlongVector(Point3D start_point, Point3D movement_vector)
{
	return Point3D(start_point.x + movement_vector.x, start_point.y + movement_vector.y, start_point.z + movement_vector.z);
}

Point3D NNLocomotion::moveFromPointInDirection(Point3D start_point, Point3D direction_vector, double distance)
{
	// Create a movement vector from the given direction vector and distance.
	Point3D movement_vector(direction_vector.x * distance, direction_vector.y * distance, direction_vector.z * distance);
	
	return moveFromPointAlongVector(start_point, direction_vector);
}

Point3D NNLocomotion::moveFromPointInDirection(Point3D start_point, Matrix direction_matrix, double distance)
{
	cout << "Moving from point " << start_point << endl;
	
	// Create a new point, shifted from the origin along the x axis, by distance.
	Matrix point = pointVectorFromPoint(Point3D(distance, 0, 0));
	
	cout << "In direction represented by\n";
	direction_matrix.print();
	
	// Rotate the point about the origin with the given rotation matrix...
	point *= direction_matrix;
	
	cout << "Movement vector comes out to\n";
	point.print();
	
	Matrix translation_matrix = translationMatrixFromPoint(start_point);
	cout << "Translation matrix from origin to start point is\n";
	translation_matrix.print();
	
	// Translate the point to the start point (now properly moved by the indicated direction and distance).
	point *= translation_matrix;
	//translationMatrixFromPoint(start_point);
	
	cout << "New point is ";
	point.print();
	
	return pointFromPointVector(point);
}

Point3D NNLocomotion::moveFromPointToPoint(Point3D start_point, Point3D target_point)
{
	return target_point;
}
