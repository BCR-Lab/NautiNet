#include <cmath>
#include "NNAlgaeSensor.h"
#include "Point3D.h"
#include "MatrixFunctions.h"
#include "NNRobot.h"
#include "NNWorld.h"

NNAlgaeSensor::NNAlgaeSensor(Matrix orientation, double offset) :
	orientation_ (orientation),
	offset_ (offset),
	last_sensor_value (0.0),
	robot (NULL),
	world (NULL)
	{ }

NNAlgaeSensor::NNAlgaeSensor(NN_SENSOR_ORIENTATION_PRESET orientation, double offset) :
	orientation_ (Matrix(IDENTITY, 4)),
	offset_ (offset),
	last_sensor_value (0.0),
	robot (NULL),
	world (NULL)
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
			this->orientation_ = make3DRotationMatrix(YAW, M_PI);
			break;
		case RIGHT:
			// Represented as rotation of 3*pi/2 radians (270 degrees) around vertical axis,
			// or three-quarter-circle yaw.
			this->orientation_ = make3DRotationMatrix(YAW, 3*M_PI/2);
			break;
		case LEFT:
			// Represented as rotation of pi/2 radians (90 degrees) around vertical axis,
			// or quarter-circle yaw.
			this->orientation_ = make3DRotationMatrix(YAW, M_PI/2);
			break;
		case TOP:
			// Represented as rotation of pi/2 radians (90 degrees) around lateral axis,
			// or quarter-circle pitch.
			this->orientation_ = make3DRotationMatrix(PITCH, M_PI/2);
			break;
		case BOTTOM:
			// Represented as rotation of 3*pi/2 radians (270 degrees) around lateral axis,
			// or three-quarter-circle pitch.
			this->orientation_ = make3DRotationMatrix(PITCH, 3*M_PI/2);
			break;
	}
}

void NNAlgaeSensor::updateSensorValue()
{	
	cout << "Computing sensor cone...\n";
	// *** NOTE: All measurements are in meters. ***
	
	// Create a point vector to represent the sensor's position.
	// (This will serve as the base of our sensor cone.)
	Matrix sensor_position(pointVectorFromPoint(Point3D(0, 0, 0)));
	
	// We also need a point vector for the center of the sensor cone base.
	Matrix sensor_cone_base_center_matrix(pointVectorFromPoint(Point3D(SENSOR_CONE_HEIGHT, 0, 0)));

	// Get the robot's current position and convert robot position into translation matrix.
	Matrix robot_position(translationMatrixFromPoint(robot->position()));
	
	// Get the robot's current orientation (a rotation matrix).
	Matrix robot_orientation(robot->orientation());
	
	// Generate translation matrix representing the sensor's offset (from the robot center).
	Matrix sensor_offset(translationMatrixFromPoint(Point3D(offset_, 0, 0)));
	
	// Apply all relevant transformations to the two key points of the sensor cone (apex and base center).
	sensor_position *= Matrix(IDENTITY, 4) * sensor_offset * this->orientation_ * robot_orientation * robot_position;
	sensor_cone_base_center_matrix *= Matrix(IDENTITY, 4) * sensor_offset * this->orientation_ * robot_orientation * robot_position;

	// The radius of the (base of the) sensor cone is derived from the height and angle.
	double sensor_cone_base_radius = SENSOR_CONE_HEIGHT * tan (SENSOR_CONE_ANGLE / 2);

	// Convert back to points, for passing to the world object.
	Point3D sensor_cone_apex(pointFromPointVector(sensor_position));
	Point3D sensor_cone_base_center(pointFromPointVector(sensor_cone_base_center_matrix));
	
	// Get the algae concentration in the specified cone.
	cout << "Querying world for algae concentration in sensor cone...\n";
	last_sensor_value = world->getConcentrationInCone(sensor_cone_apex, sensor_cone_base_center, sensor_cone_base_radius);
}

double NNAlgaeSensor::sensorValue() const
{
	return last_sensor_value;
}

void NNAlgaeSensor::printSensorValue(ostream& out) const
{
	out << "Current sensor value is: " << last_sensor_value << endl;
}
