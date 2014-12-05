#ifndef NN_SENSOR_UTILITY_H
#define NN_SENSOR_UTILITY_H

#include <string>
using namespace std;

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

static string orientation_preset_strings[] = 
	{	"FRONT",
		"BACK",
		"RIGHT",
		"LEFT",
		"TOP",
		"BOTTOM" };

string stringify(NN_SENSOR_ORIENTATION_PRESET orientation_preset);

#endif
