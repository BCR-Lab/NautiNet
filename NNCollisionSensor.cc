#include <cmath>
#include "NNCollisionSensor.h"
#include "Point3D.h"
#include "MatrixFunctions.h"
#include "NNRobot.h"
#include "NNWorld.h"

NNCollisionSensor::NNCollisionSensor(Matrix orientation, double offset) :
	orientation (orientation),
	offset (offset),
	lastSensorValue (false)
	{ }

NNCollisionSensor::NNCollisionSensor(NN_SENSOR_ORIENTATION_PRESET orientation, double offset) :
	orientation (Matrix(IDENTITY, 4)),
	offset (offset),
	lastSensorValue (false)
{
	switch(orientation)
	{
		case FRONT:
		default:
			// Front-facing sensor is the default case and is represented by the identity matrix.
			// (Front = facing toward positive X, no rotation around any axis.)
			break;
		case BACK:
			// Represented as rotation of pi radians (180 degrees) around vertical axis,
			// or half-circle yaw.
			this->orientation = make3DRotationMatrix(YAW, M_PI);
			break;
		case RIGHT:
			// Represented as rotation of 3*pi/2 radians (270 degrees) around vertical axis,
			// or three-quarter-circle yaw.
			this->orientation = make3DRotationMatrix(YAW, 3*M_PI/2);
			break;
		case LEFT:
			// Represented as rotation of pi/2 radians (90 degrees) around vertical axis,
			// or quarter-circle yaw.
			this->orientation = make3DRotationMatrix(YAW, M_PI/2);
			break;
		case TOP:
			// Represented as rotation of pi/2 radians (90 degrees) around lateral axis,
			// or quarter-circle pitch.
			this->orientation = make3DRotationMatrix(PITCH, M_PI/2);
			break;
		case BOTTOM:
			// Represented as rotation of 3*pi/2 radians (270 degrees) around lateral axis,
			// or three-quarter-circle pitch.
			this->orientation = make3DRotationMatrix(PITCH, 3*M_PI/2);
			break;
	}
}

void NNCollisionSensor::setRobot(NNRobot* robot)
{
	this->robot = robot;
}

void NNCollisionSensor::setWorld(NNWorld* world)
{
	this->world = world;
}

void NNCollisionSensor::updateSensorValue()
{
	// *** NOTE: All measurements are in meters. ***
	
	// Create a point vector to represent the sensor's position.
	// (This will serve as the base of our sensor cone.)
	Matrix sensor_position(pointVectorFromPoint(Point3D(0, 0, 0)));
	
	// Get the robot's current position and convert robot position into translation matrix.
	Matrix robot_position(translationMatrixFromPoint(robot->position()));
	
	// Get the robot's current orientation (a rotation matrix).
	Matrix robot_orientation(robot->orientation());
	
	// Generate translation matrix representing the sensor's offset (from the robot center).
	Matrix sensor_offset(translationMatrixFromPoint(Point3D(offset, 0, 0)));
	
	// Apply all relevant transformations to the point representing the position of the sensor.
	sensor_position *= Matrix(IDENTITY, 4) * sensor_offset * orientation * robot_orientation * robot_position;

	// Convert back to points, for passing to the world object.
	Point3D sensor_point(pointFromPointVector(sensor_position));
	
	// Check for obstacle presence within the specified cone.
	lastSensorValue = world->isObstacleAtPoint(sensor_point);
}

bool NNCollisionSensor::sensorValue()
{
	return lastSensorValue;
}

void NNCollisionSensor::printSensorValue(ostream& out)
{
	out << "Current sensor value is: " << ( lastSensorValue == true ? "true (obstacle detected in sensor cone)" : "false (obstacle NOT detected in sensor cone)" ) << endl;
}
