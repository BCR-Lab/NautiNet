#ifndef NN_ALGAE_SENSOR_H
#define NN_ALGAE_SENSOR_H

/*
 An NNAlgaeSensorValue object represents the gradient of algae concentration around the robonaut. It has six values: concentration in the positive z direction, concentration in the negative z direction, and likewise for x and y.
	
 Note that z is vertical: +z is toward the surface, -z away from the surface. The x and y axes are arbitrary, but might correspond to geographic latitude and longitude, etc.
 */
struct NNAlgaeSensorValue
{
	double x_pos_dir_concentration;
	double x_neg_dir_concentration;
	double y_pos_dir_concentration;
	double y_neg_dir_concentration;
	double z_pos_dir_concentration;
	double z_neg_dir_concentration;

	NNAlgaeSensorValue(double xpos = 0, double xneg = 0, double ypos = 0, double yneg = 0, double zpos = 0, double zneg = 0) :
		x_pos_dir_concentration(xpos),
		x_neg_dir_concentration(xneg),
		y_pos_dir_concentration(ypos),
		y_neg_dir_concentration(yneg),
		z_pos_dir_concentration(zpos),
		z_neg_dir_concentration(zneg)
		{ }
};

// TEMPORARY - forward declaration of NNWorld class, so that NNAlgaeSensor can compile, for testing purposes.
class NNWorld;

/*
 An NNAlgaeSensor keeps and updates an NNAlgaeSensorValue object, which represents the last known value for the gradient of algae concentration around the robonaut.
 */
class NNAlgaeSensor
{
	private:
		NNWorld* world;
		NNAlgaeSensorValue lastSensorValue;
		
		void updateSensorValue();
	
	public:
		
		// CONSTRUCTORS & DESTRUCTORS
		
		// Default constructor.
		NNAlgaeSensor();
		
		// Copy constructor.
		NNAlgaeSensor(const NNAlgaeSensor& right);
		
		// Destructor.
		~NNAlgaeSensor();
		
		// FUNCTIONS
		
		NNAlgaeSensorValue getSensorValue();
};

#endif
