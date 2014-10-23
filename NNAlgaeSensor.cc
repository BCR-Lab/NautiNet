#include "NNAlgaeSensor.h"
#include "Point3D.h"
#include <cstring>
#include <cmath>

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

	// *** NOTE: All measurements are in meters. ***

	// TEMPORARY - once the locomotion class is implemented, the robot will keep track of its own position, which we will query here. For now, a placeholder...
	Point3D position;
	
	// TEMPORARY - once the robot control logic class is implemented, the robot will keep track of its own vital statistics (physical dimensions, etc.), which we will query here. For now, we'll manually define an offset from the robot's center (which is the point specified by its position variable)...
	double sensor_offset = 0.05;	// 5 cm, in meters (robot assumed to be a 10cm diameter sphere).
	
	// The size of the cone in which we get the algae density (that is, the luminescence value in the relevant frequency) is not something we will have to define in an actual, running-on-hardware implementation (it will simply depend on the sensor's capabilities), but for simulation purposes we do have to know it.
	double sensor_cone_height = 0.1;	// 10 cm, in meters.
	double sensor_cone_angle = 54.0 * M_PI / 180.0;	// 54 degrees, in radians.
	double sensor_cone_radius = sensor_cone_height * tan (sensor_cone_angle / 2);	// Also in meters.
	
	// For every one of the six directions, we have to figure out the location of the center of the sensor cone's base; we then pass the three parameters (cone apex (tip); cone base center; cone radius) to the World object's getConcentrationInCone method.
	
	Point3D sensor_cone_apex = position;
	Point3D sensor_cone_base_center(position.x, position.y, position.z);
	
	// Positive X direction.
	sensor_cone_apex.x += sensor_offset;
	sensor_cone_base_center.x += sensor_offset + sensor_cone_height;
//	lastSensorValue.x_pos_dir_concentration = world->getConcentrationInCone(sensor_cone_apex, sensor_cone_base_center, sensor_cone_radius);
	sensor_cone_base_center.x = sensor_cone_apex.x = position.x;
	
	// Negative X direction.
	sensor_cone_apex.x -= sensor_offset;
	sensor_cone_base_center.x -= sensor_offset + sensor_cone_height;
//	lastSensorValue.x_neg_dir_concentration = world->getConcentrationInCone(sensor_cone_apex, sensor_cone_base_center, sensor_cone_radius);
	sensor_cone_base_center.x = sensor_cone_apex.x = position.x;
	
	// Positive Y direction.
	sensor_cone_apex.y += sensor_offset;
	sensor_cone_base_center.y += sensor_offset + sensor_cone_height;
//	lastSensorValue.y_pos_dir_concentration = world->getConcentrationInCone(sensor_cone_apex, sensor_cone_base_center, sensor_cone_radius);
	sensor_cone_base_center.y = sensor_cone_apex.y = position.y;
	
	// Negative Y direction.
	sensor_cone_apex.y -= sensor_offset;
	sensor_cone_base_center.y -= sensor_offset + sensor_cone_height;
//	lastSensorValue.y_neg_dir_concentration = world->getConcentrationInCone(sensor_cone_apex, sensor_cone_base_center, sensor_cone_radius);
	sensor_cone_base_center.y = sensor_cone_apex.y = position.y;
	
	// Positive Z direction.
	sensor_cone_apex.z += sensor_offset;
	sensor_cone_base_center.z += sensor_offset + sensor_cone_height;
//	lastSensorValue.z_pos_dir_concentration = world->getConcentrationInCone(sensor_cone_apex, sensor_cone_base_center, sensor_cone_radius);
	sensor_cone_base_center.z = sensor_cone_apex.z = position.z;
	
	// Negative Z direction.
	sensor_cone_apex.z -= sensor_offset;
	sensor_cone_base_center.z -= sensor_offset + sensor_cone_height;
//	lastSensorValue.z_neg_dir_concentration = world->getConcentrationInCone(sensor_cone_apex, sensor_cone_base_center, sensor_cone_radius);
	sensor_cone_base_center.z = sensor_cone_apex.z = position.z;
	
	// Done! All six direction components of the lastSensorValue is now updated.
}
