#include "NNAlgaeSensor.h"
#include <cstring>

using namespace std;

// CONSTRUCTORS AND DESTRUCTORS

NNAlgaeSensor::NNAlgaeSensor()
{
	world = NULL;
}

NNAlgaeSensor::NNAlgaeSensor(const NNAlgaeSensor& right)
{
	lastSensorValue = right.lastSensorValue;
	world = right.world;
}

NNAlgaeSensor::~NNAlgaeSensor()
{
	world = NULL;
}


// FUNCTIONS

NNAlgaeSensorValue NNAlgaeSensor::getSensorValue()
{
	return lastSensorValue;
}

void NNAlgaeSensor::updateSensorValue()
{
	if(world == NULL)
		// THROW AN EXCEPTION, RETURN AN ERROR CODE, OR OTHERWISE HANDLE ERROR
		return;
		
	// TEMPORARY - once the locomotion class is implemented, the robot will keep track of its own position, which we will query here. For now, a placeholder...
	struct Point3D
	{
		double x;
		double y;
		double z;
		
		Point3D(double x, double y, double z) : x(x), y(y), z(z) { }
		Point3D() : x(0), y(0), z(0) { }
	} position;
	
	// The size of the cone in which we get the algae density (that is, the luminescene value in the relevant frequency) is not something we will have to define in an actual, running-on-hardware implementation (it will simply depend on the sensor's capabilities), but for simulation purposes we do have to know it.
	double sensor_cone_height = 5;
	double sensor_cone_radius = 5;
	
	// For every one of the six directions, we have to figure out the location of the center of the sensor cone's base; we then pass the three parameters (cone tip, i.e. robot position; cone base center; cone radius) to the World object's getConcentrationInCone method.
	
	Point3D sensor_cone_base_center(position.x, position.y, position.z);
	
	// Positive X direction.
	sensor_cone_base_center.x += sensor_cone_height;
//	lastSensorValue.x_pos_dir_concentration = world->getConcentrationInCone(position, sensor_cone_base_center, sensor_cone_radius);
	sensor_cone_base_center.x = position.x;
	
	// Negative X direction.
	sensor_cone_base_center.x -= sensor_cone_height;
//	lastSensorValue.x_neg_dir_concentration = world->getConcentrationInCone(position, sensor_cone_base_center, sensor_cone_radius);
	sensor_cone_base_center.x = position.x;
	
	// Positive Y direction.
	sensor_cone_base_center.y += sensor_cone_height;
//	lastSensorValue.y_pos_dir_concentration = world->getConcentrationInCone(position, sensor_cone_base_center, sensor_cone_radius);
	sensor_cone_base_center.y = position.y;
	
	// Negative Y direction.
	sensor_cone_base_center.y -= sensor_cone_height;
//	lastSensorValue.y_neg_dir_concentration = world->getConcentrationInCone(position, sensor_cone_base_center, sensor_cone_radius);
	sensor_cone_base_center.y = position.y;
	
	// Positive Z direction.
	sensor_cone_base_center.z += sensor_cone_height;
//	lastSensorValue.z_pos_dir_concentration = world->getConcentrationInCone(position, sensor_cone_base_center, sensor_cone_radius);
	sensor_cone_base_center.z = position.z;
	
	// Negative Z direction.
	sensor_cone_base_center.z -= sensor_cone_height;
//	lastSensorValue.z_neg_dir_concentration = world->getConcentrationInCone(position, sensor_cone_base_center, sensor_cone_radius);
	sensor_cone_base_center.z = position.z;
	
	// Done! All six direction components of the lastSensorValue is now updated.
}
