#include "NNAlgaeSensorArray.h"
#include "Point3D.h"
#include <cstring>
#include <cmath>

using namespace std;

// CONSTRUCTORS AND DESTRUCTORS

NNAlgaeSensorArray::NNAlgaeSensorArray()
{
	robot = NULL;
}

// FUNCTIONS

NNAlgaeSensorArrayValue NNAlgaeSensorArray::getSensorGradient()
{
	return lastSensorGradientReading;
}

void NNAlgaeSensorArray::updateSensorValues()
{
	if(world == NULL)
		// THROW AN EXCEPTION, RETURN AN ERROR CODE, OR OTHERWISE HANDLE ERROR
		return;

	// Negative X direction.
	sensor_cone_apex.x -= sensor_offset;
	sensor_cone_base_center.x -= sensor_offset + sensor_cone_height;
	lastSensorGradientReading.x_neg_dir_concentration = world->getConcentrationInCone(sensor_cone_apex, sensor_cone_base_center, sensor_cone_radius);
	sensor_cone_base_center.x = sensor_cone_apex.x = position.x;
	
	// Positive Y direction.
	sensor_cone_apex.y += sensor_offset;
	sensor_cone_base_center.y += sensor_offset + sensor_cone_height;
	lastSensorGradientReading.y_pos_dir_concentration = world->getConcentrationInCone(sensor_cone_apex, sensor_cone_base_center, sensor_cone_radius);
	sensor_cone_base_center.y = sensor_cone_apex.y = position.y;
	
	// Negative Y direction.
	sensor_cone_apex.y -= sensor_offset;
	sensor_cone_base_center.y -= sensor_offset + sensor_cone_height;
	lastSensorGradientReading.y_neg_dir_concentration = world->getConcentrationInCone(sensor_cone_apex, sensor_cone_base_center, sensor_cone_radius);
	sensor_cone_base_center.y = sensor_cone_apex.y = position.y;
	
	// Positive Z direction.
	sensor_cone_apex.z += sensor_offset;
	sensor_cone_base_center.z += sensor_offset + sensor_cone_height;
	lastSensorGradientReading.z_pos_dir_concentration = world->getConcentrationInCone(sensor_cone_apex, sensor_cone_base_center, sensor_cone_radius);
	sensor_cone_base_center.z = sensor_cone_apex.z = position.z;
	
	// Negative Z direction.
	sensor_cone_apex.z -= sensor_offset;
	sensor_cone_base_center.z -= sensor_offset + sensor_cone_height;
	lastSensorGradientReading.z_neg_dir_concentration = world->getConcentrationInCone(sensor_cone_apex, sensor_cone_base_center, sensor_cone_radius);
	sensor_cone_base_center.z = sensor_cone_apex.z = position.z;
	
	// Done! All six direction components of the lastSensorGradientReading is now updated.
}

void NNAlgaeSensorArray::setWorld(NNWorld* world)
{
	this->world = world;
}

void NNAlgaeSensorArray::setRobot(NNWRobot* robot)
{
	this->robot = robot;
}

void NNAlgaeSensorArray::printSensorGradient(ostream& out)
{
	out << "Current sensor value is:" << endl;
	out << "Positive x: " << lastSensorGradientReading.x_pos_dir_concentration << endl;
	out << "Negative x: " << lastSensorGradientReading.x_neg_dir_concentration << endl;
	out << "Positive y: " << lastSensorGradientReading.y_pos_dir_concentration << endl;
	out << "Negative y: " << lastSensorGradientReading.y_neg_dir_concentration << endl;
	out << "Positive z: " << lastSensorGradientReading.z_pos_dir_concentration << endl;
	out << "Negative z: " << lastSensorGradientReading.z_neg_dir_concentration << endl;
	
}
