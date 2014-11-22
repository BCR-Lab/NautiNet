#include <iostream>
#include "NNWorld.h"
using namespace std;

int main()
{
	NNWorld world;
	world.filesPath("/Users/obormot/Documents/BC Files/2014 Fall/CISC 4900/ParticleDistribution/");
	world.baseFileName("CoordsTimeInstant");
	world.fileNameScheme(NO_LEADING_ZEROES);
	
	world.loadData();
	
	world.printTimeInstant(0);

	return 0;
}
