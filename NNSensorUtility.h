#ifndef NN_SENSOR_UTILITY_H
#define NN_SENSOR_UTILITY_H

// Orientation presets, for each of the six cardinal directions (relative to the robot).
// Used by some sensor constructors.
typedef enum
{
	FRONT,
	BACK,
	RIGHT,
	LEFT,
	TOP,
	BOTTOM
} NN_SENSOR_ORIENTATION_PRESET;

#endif
