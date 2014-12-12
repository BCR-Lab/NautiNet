#include "NNWorld.h"
#include "NNGeometryFunctions.h"

NNWorld::NNWorld() :
	current_time_instant(0),
	flag_reload(false),
	file_name_scheme(NO_LEADING_ZEROES),
	region_size(1.0)
{ }
	
void NNWorld::loadData()
{
	cout << "Loading data...\n";

	// If data is already loaded, and reload flag is not set, generate some error and return.
	if(!particle_positions.empty() && flag_reload == false)
	{
		return;
	}
		
	// If reload flag is set, discard existing data.
	if(!particle_positions.empty())	// Which means that the reload flag MUST be set, else the conditional above would have triggered...
	{
		particle_positions.clear();
	}
		
	// Variables to hold input.
	double x, y, z;
	
	// File stream for input files.
	fstream time_instant_file;
	
	// String to hold the complete path for each file.
	string file_path;
	
	// String to hold the file name suffix (the time instant number).
	char* time_instant_file_name_suffix = new char[20];
	
	// Counter to keep track of which time instant we're loading...
	int time_instant_index = 0;
	
	// Pointer that will point to the volume bounds struct for the current time instant...
	NNVolumeBounds* volume_bounds = NULL;
	
	// Start trying to read time instant files until we encounter one that's nonexistent or unreadable.
	while(true)
	{
		// Open time instant data file for reading.
		switch(file_name_scheme)
		{
			case NO_LEADING_ZEROES:
				sprintf(time_instant_file_name_suffix, "%d", time_instant_index);
				file_path = time_instant_files_path + time_instant_base_file_name + time_instant_file_name_suffix;
				break;
			case LEADING_ZEROES:
				// TO BE IMPLEMENTED!!
				break;
			default:
				break;
		}
		cout << "Attempting to open file at " << file_path << " ...\n";
		time_instant_file.open((file_path).data(), ios::in);
		if(!time_instant_file)
		{
			// The file doesn't exist or couldn't be opened; either way, we're done. Exit the loop.
			break;
		}
		
		// Create the next vector of points (for the new time instant).
		particle_positions.push_back(vector <Point3D> ());
		
		// Create the next volume bounds object (for the new time instant).
		particle_cloud_volume_bounds.push_back(NNVolumeBounds());

		// Update the pointer.
		volume_bounds = &(particle_cloud_volume_bounds[time_instant_index]);
				
		// Read and discard first line (column headers).
		string dummy;
		getline(time_instant_file, dummy);
		
		// Read in points in this time instant, while there remain points to be read in the file.
		do
		{
			time_instant_file >> x >> y >> z;
			
			if(!time_instant_file.eof())
			{
				particle_positions[time_instant_index].push_back(Point3D(x, y, z));
				
				// If this is the first particle, set the volume bounds to their initial values (describing a point volume which contains this first particle only).
				if(particle_positions[time_instant_index].size() == 1)
				{
					volume_bounds->minX = volume_bounds->maxX = x;
					volume_bounds->minY = volume_bounds->maxY = y;
					volume_bounds->minZ = volume_bounds->maxZ = z;
				}
				// Otherwise, check to see if the current particle "pushes out" the boundary of the minimal enclosing rectilinear volume; if so, update the bounds to include it.
				else
				{
					if(x < volume_bounds->minX)
						volume_bounds->minX = x;
					else if(x > volume_bounds->maxX)
						volume_bounds->maxX = x;
						
					if(y < volume_bounds->minY)
						volume_bounds->minY = y;
					else if(y > volume_bounds->maxY)
						volume_bounds->maxY = y;
						
					if(z < volume_bounds->minZ)
						volume_bounds->minZ = z;
					else if(z > volume_bounds->maxZ)
						volume_bounds->maxZ = z;
				}
			}
		} while(!time_instant_file.eof());
		
		// Close the file (so we can open the next one).
		time_instant_file.close();
		
		// Increment the time instant.
		time_instant_index++;
	}
	
	// Free allocated memory.
	delete time_instant_file_name_suffix;
	
	cout << "Finished loading data.\n";
	
	cout << "Loaded " << numTimeInstants() << " time instants." << endl;
	
	// Print the volume bounds of the particle cloud at each time instant.
	printVolumeBoundsForAllTimeInstants();

	// Assuming we've loaded any time instants, check to see if all the time instants have the same number of particles.
	// If we haven't, print out a DIRE WARNING!!!, then exit.
	if(numTimeInstants() > 0)
	{
		bool mismatch = false;
		
		for(int i = 1; i < numTimeInstants(); i++)
		{
			if(numParticlesAtInstant(i) != numParticlesAtInstant(0))
			{
				cout << "*** WARNING!!! ***" << endl;
				cout << "Number of particles in time instant " << i;
				cout << " doesn't match number of particles in time instant 0! ";
				cout << "This is probably very bad!\n";
				
				mismatch = true;
			}
		}
		
		if(mismatch)
		{
			"Due to the aforementioned particle count mismatch, this program will now exit.\n";
			exit(1);
		}
	}
	
	constructHashFunctionTable();
	constructHashTable();

//	printHashValuesForParticlesAtTimeInstant(0);
//	printHashValuesForParticlesAtTimeInstant(172);
//	printHashValuesForParticlesAtTimeInstant(numTimeInstants() - 1);
}

void NNWorld::printParticlesForAllTimeInstants() const
{
	for(int i = 0; i < numTimeInstants(); i++)
	{
		printParticlesForTimeInstant(i);
	}
}

void NNWorld::printParticlesForTimeInstant(int t) const
{
	if(t >= numTimeInstants())
	{
		// If we're asking for a nonexistent time instant...
		cout << "Time instant " << t << " does not exist!\n";
		return;
	}
	
	cout << "Printing particle position data for time instant " << t << "...\n";
	cout << "x" << "\t\t\t" << "y" << "\t\t\t" << "z" << endl;
	
	int precision = cout.precision();
	cout.precision(10);

	for(vector <Point3D>::const_iterator i = particle_positions[t].begin(); i != particle_positions[t].end(); i++)
	{
		cout << (*i).x << "\t\t" << (*i).y << "\t\t" << (*i).z << "\n";
	}
	
	// Set precision back to whatever it was before.
	cout.precision(precision);
}

double NNWorld::getConcentrationInCone(Point3D sensor_cone_apex, Point3D sensor_cone_base_center, double sensor_cone_base_radius) const
{
	double algae_particles = 0;
	
	double algae_particles_not_in_cone = 0;

	// Get all of the possible hash values (i.e. indices of spatial region) which this cone intersects, i.e. in which spatial regions might there be points within the cone.
	vector <unsigned long long int> possible_hash_values = possibleHashValuesForCone(sensor_cone_apex, sensor_cone_base_center, sensor_cone_base_radius);

	// For each hash value (spatial region)...
	for(vector<unsigned long long int>::const_iterator i = possible_hash_values.begin(); i != possible_hash_values.end(); i++)
	{
		// ... get all the points in that region...
		pair <multimap<unsigned long long int, Point3D>::const_iterator, multimap<unsigned long long int, Point3D>::const_iterator> range = particle_hash_table[current_time_instant].equal_range(*i);
		
		// ... then look through each point in the region...
		for(multimap<unsigned long long int, Point3D>::const_iterator j = range.first; j != range.second; j++)
		{
			// ... and test whether that point is within the cone.
			if(nn::isPointInCone((*j).second, sensor_cone_apex, sensor_cone_base_center, sensor_cone_base_radius))
				algae_particles++;
			else
				algae_particles_not_in_cone++;
		}
	}
	
	return algae_particles;
}

bool NNWorld::isObstacleAtPoint(Point3D point) const
{
	// NOT YET IMPLEMENTED!

	return true;
}

double NNWorld::lightIntensityAtPoint(Point3D point) const
{
	// NOT YET IMPLEMENTED!
	
	return 0.0;
}

ostream& operator<<(ostream& out, NNVolumeBounds b)
{
	out << "( X: " << b.minX << " to " << b.maxX << "; ";
	out <<   "Y: " << b.minY << " to " << b.maxY << "; ";
	out <<   "Z: " << b.minZ << " to " << b.maxZ << " )";
	return out;
}

void NNWorld::constructHashTable()
{
	// Discard existing data.
	if(!particle_hash_table.empty())
	{
		particle_hash_table.clear();
	}
	
	// For each time instant of particle position data...
	for(int t = 0; t < numTimeInstants(); t++)
	{
		// Create a hash table (implemented as multimap) for that time instant.
		particle_hash_table.push_back(multimap <unsigned long long int, Point3D> ());
			
		// Go through each particle in that time instant... 
		for(vector<Point3D>::iterator point_p = particle_positions[t].begin(); point_p != particle_positions[t].end(); point_p++)
		{
			// ... and insert it into the hash table, under the appropriate hash value.
			particle_hash_table[t].insert(pair <int, Point3D> (hashValueForPointAtTimeInstant(*point_p, t), *point_p));
		}
	}
}

void NNWorld::constructHashFunctionTable()
{
	// Discard existing data.
	if(!particle_hash_functions.empty())
	{
		particle_hash_functions.clear();
	}
	
	cout << "Constructing hash function tables...\n";
	
	for(vector <NNVolumeBounds>::iterator bounds = particle_cloud_volume_bounds.begin(); bounds != particle_cloud_volume_bounds.end(); bounds++)
	{
		cout << " Computing x and y grid span for particle cloud at time instant ";
		cout << particle_hash_functions.size() << endl;
		
		particle_hash_functions.push_back(ParticleHashFunctor());

		// Compute the parameters (x and y grid span for that time instant) of the functor.		
		particle_hash_functions.back().grid_span_x = ceil((bounds->maxX - bounds->minX) / region_size);
		particle_hash_functions.back().grid_span_y = ceil((bounds->maxY - bounds->minY) / region_size);	
		
		printf("  Grid span is %lld by %lld meters.\n", particle_hash_functions.back().grid_span_x, particle_hash_functions.back().grid_span_y);
	}
	
	cout << "Finished constructing hash function tables.\n";
}

unsigned long long int NNWorld::hashValueForPoint(Point3D point) const
{
	return particle_hash_functions[current_time_instant](point, particle_cloud_volume_bounds[current_time_instant], region_size);
}

unsigned long long int NNWorld::hashValueForPointAtTimeInstant(Point3D point, int time_instant) const
{
	return particle_hash_functions[time_instant](point, particle_cloud_volume_bounds[time_instant], region_size);
}

vector <unsigned long long int> NNWorld::possibleHashValuesForCone(Point3D cone_apex, Point3D cone_base_center, double cone_base_radius) const
{
	vector <unsigned long long int> possible_hash_values;
	
	// Calculate the "slant height" of the sensor cone, i.e. the distance from the apex to any cone on the circumference of the base.
	double height = Point3D::distance(cone_apex, cone_base_center);
	double slant_height = sqrt(pow(height, 2) + pow(cone_base_radius, 2));
	
	// We say "supermax" and not "max" because what we're computing here is the value of "maximum x plus one region_size further", so we can use it as an upper bound.
	// (We don't want to do <= max_x, because our values are doubles and thus checking for equality is bad times.)
	double min_x = cone_apex.x - slant_height;
	double supermax_x = cone_apex.x + slant_height + region_size;
	double min_y = cone_apex.y - slant_height;
	double supermax_y = cone_apex.y + slant_height + region_size;
	double min_z = cone_apex.z - slant_height;
	double supermax_z = cone_apex.z + slant_height + region_size;
	
	// Loop through the entire cubical region that encompasses the sphere which just circumscribes the sensor cone, whose center is the cone's apex.
	for(double x = min_x; x < supermax_x; x+= region_size)
	{
		for(double y = min_y; y < supermax_y; y+= region_size)
		{
			for(double z = min_z; z < supermax_z; z+= region_size)
			{
				possible_hash_values.push_back(hashValueForPoint(Point3D(x, y, z)));
			}
		}
	}
	
	return possible_hash_values;
}

void NNWorld::printVolumeBoundsForAllTimeInstants() const
{
	for(int i = 0; i < numTimeInstants(); i++)
	{
		printVolumeBoundsForTimeInstant(i);
	}
}

void NNWorld::printVolumeBoundsForTimeInstant(int t) const
{
	if(t >= numTimeInstants())
	{
		// If we're asking for a nonexistent time instant...
		cout << "Time instant " << t << " does not exist!\n";
		return;
	}
	
	int precision = cout.precision();
	cout.precision(10);

	cout << "Particle cloud volume bounds at time instant " << t << ": " << particle_cloud_volume_bounds[t] << endl;
	
	// Set precision back to whatever it was before.
	cout.precision(precision);
}

void NNWorld::printHashValuesForParticlesAtTimeInstant(int t) const
{
	cout << "Listing particle hash values for points at time instant " << t << ":\n";
	
	for(vector <Point3D>::const_iterator p = particle_positions[t].begin(); p != particle_positions[t].end(); p++)
	{
		cout << hashValueForPointAtTimeInstant(*p, t) << endl;
	}
}