#include <cmath>
#include "NNAlgaeSensor.h"
#include "Point3D.h"
#include "MatrixFunctions.h"
#include "NNRobot.h"

NNAlgaeSensor::NNAlgaeSensor(Matrix orientation, double offset) :
	orientation(orientation),
	offset(offset)
{
	lastSensorValue = 0.0;
}

void NNAlgaeSensor::setRobot(NNRobot* robot)
{
	this->robot = robot;
}

void NNAlgaeSensor::setWorld(NNWorld* world)
{
	this->world = world;
}

void NNAlgaeSensor::updateSensorValue()
{
	// *** NOTE: All measurements are in meters. ***
	
	// Create a point vector to represent the sensor's position.
	// (This will serve as the base of our sensor cone.)
	Matrix sensor_position(pointVectorFromPoint(Point3D(0, 0, 0)));
	
	// We also need a point vector for the center of the sensor cone base.
	Matrix sensor_cone_base_center_matrix(pointVectorFromPoint(Point3D(SENSOR_CONE_HEIGHT, 0, 0)));

	// Get the robot's current position and convert robot position into translation matrix.
	Matrix robot_position(translationMatrixFromPoint(robot->getPosition()));
	
	// Get the robot's current orientation (a rotation matrix).
	Matrix robot_orientation(robot->getOrientation());
	
	// Generate translation matrix representing the sensor's offset (from the robot center).
	Matrix sensor_offset(translationMatrixFromPoint(Point3D(offset, 0, 0)));
	
	// Apply all relevant transformations to the two key points of the sensor cone (apex and base center).
	sensor_position *= Matrix(IDENTITY, 4) * sensor_offset * orientation * robot_orientation * robot_position;
	sensor_cone_base_center_matrix *= Matrix(IDENTITY, 4) * sensor_offset * orientation * robot_orientation * robot_position;

	// The radius of the (base of the) sensor cone is derived from the height and angle.
	double sensor_cone_radius = SENSOR_CONE_HEIGHT * tan (SENSOR_CONE_ANGLE / 2);

	// Convert back to points, for passing to the world object.
	Point3D sensor_cone_apex(pointFromPointVector(sensor_position));
	Point3D sensor_cone_base_center(pointFromPointVector(sensor_cone_base_center_matrix));
	
	// Get the algae concentration in the specified cone.
//	lastSensorValue = world->getConcentrationInCone(sensor_cone_apex, sensor_cone_base_center, sensor_cone_radius);
}

double NNAlgaeSensor::getSensorValue()
{
	return lastSensorValue;
}

void NNAlgaeSensor::printSensorValue(ostream& out)
{
	out << "Current sensor value is: " << lastSensorValue << endl;
}
