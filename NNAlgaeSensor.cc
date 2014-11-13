#include "NNAlgaeSensor.h"

NNAlgaeSensor::NNAlgaeSensor(double offset, Matrix orientation) :
	offset(offset),
	orientation(orientation)
{
	lastSensorValue = 0.0;
}

void NNAlgaeSensor::updateSensorValue()
{
	// *** NOTE: All measurements are in meters. ***

	// Get the robot's current position.
	Point3D position = robot->getPosition();
	
	// The size of the cone in which we get the algae density (that is, the luminescence value in the relevant frequency) is not something we will have to define in an actual, running-on-hardware implementation (it will simply depend on the sensor's capabilities), but for simulation purposes we do have to know it.
	double sensor_cone_height = 0.1;	// 10 cm, in meters.
	double sensor_cone_angle = 54.0 * M_PI / 180.0;	// 54 degrees, in radians.
	double sensor_cone_radius = sensor_cone_height * tan (sensor_cone_angle / 2);	// Also in meters.
	
	// We have to figure out the location of the center of the sensor cone's base; we then pass the three parameters (cone apex (tip); cone base center; cone radius) to the World object's getConcentrationInCone method.
	
	Point3D sensor_cone_apex = position;
	Point3D sensor_cone_base_center(position.x, position.y, position.z);
	
	// Positive X direction.
	sensor_cone_apex.x += sensor_offset;
	sensor_cone_base_center.x += sensor_offset + sensor_cone_height;
	lastSensorGradientReading.x_pos_dir_concentration = world->getConcentrationInCone(sensor_cone_apex, sensor_cone_base_center, sensor_cone_radius);
	sensor_cone_base_center.x = sensor_cone_apex.x = position.x;
	

}

double NNAlgaeSensor::getSensorValue()
{
	return lastSensorValue;
}
