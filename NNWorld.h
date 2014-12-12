#ifndef NNWORLD_H
#define NNWORLD_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include "Point3D.h"
using namespace std;

typedef enum
{
	NO_LEADING_ZEROES,
	LEADING_ZEROES
} FILE_NAME_SCHEME_TYPE;

struct NNVolumeBounds
{
	double minX;
	double maxX;
	double minY;
	double maxY;
	double minZ;
	double maxZ;
	
	friend ostream& operator<<(ostream& out, NNVolumeBounds b);
};

class NNWorld
{
	private:
	
		// Positions of all particles at all time instants.
		// First array dimension is time; second array dimension is particle index number.
		vector <vector <Point3D> > particle_positions;
		
		// The "current" time instant (the one from which particle data is pulled on request).
		int current_time_instant;
		
		// Minimal rectilinear bounds of the volumes occupied by the total set of particles at each time instant.
		vector <NNVolumeBounds> particle_cloud_volume_bounds;
		
		
		// ********************************************************
		// *** VARIABLES AND FUNCTIONS FOR PARTICLE HASH TABLES ***
		// ********************************************************
				
		struct ParticleHashFunctor
		{
			unsigned long long int grid_span_x;
			unsigned long long int grid_span_y;
			
			unsigned long long int operator()(const Point3D& point, const NNVolumeBounds& bounds, const double& region_size) const
			{
				unsigned long long int complete_z_layers = (unsigned long long int) floor((point.z - bounds.minZ) / region_size);
				unsigned long long int complete_y_lines = (unsigned long long int) floor((point.y - bounds.minY) / region_size);
				unsigned long long int complete_x_regions = (unsigned long long int) floor((point.x - bounds.minX) / region_size);
				
				return 
					complete_z_layers * (grid_span_y * grid_span_x) +
					complete_y_lines * (grid_span_x) +
					complete_x_regions;
			}
		};
		
		// Size of a spatial region (i.e. length of an edge of the cubical region) into which the space is partitioned for the hash function
		double region_size;
		
		// Hash function objects for each time instant.
		vector <ParticleHashFunctor> particle_hash_functions;
		
		// Function to construct the hash function objects.
		void constructHashFunctionTable();
		
		// Hash tables of particle positions at each time instant.
		vector <multimap <unsigned long long int, Point3D> > particle_hash_table;
		
		// Function to construct the hash table.
		void constructHashTable();
		
		// Hash function (actually a wrapper around a call to the appropriate hash function object for the current time instant).
		unsigned long long int hashValueForPoint(Point3D point) const;
		
		// Hash function (actually a wrapper around a call to the appropriate hash function object for the given time instant).
		unsigned long long int hashValueForPointAtTimeInstant(Point3D point, int time_instant) const;
		
		// Function to determine the set of hash values under which the points that may potentially fall within a given cone may be found.
		vector <unsigned long long int> possibleHashValuesForCone(Point3D cone_apex, Point3D cone_base_center, double cone_base_radius) const;
		
		// For debugging purposes only. Print out hash values for all particles in a given time instant.
		void printHashValuesForParticlesAtTimeInstant(int t) const;
		
		// *************************************
		// *** END PARTICLE HASH TABLE STUFF ***
		// *************************************
		

		// The reload flag controls whether we attempt to reload the data, if it's already been loaded. If set to false, calling loadData() a second time (after at least one time instant file has successfully been loaded) does absolutely nothing.
		// Default is false.
		bool flag_reload;
		
		// Variables for reading the files.
		string time_instant_files_path;
		string time_instant_base_file_name;
		FILE_NAME_SCHEME_TYPE file_name_scheme;
		int pad_width;
		
	public:
		
		// CONSTRUCTORS
		
		// Default constructor.
		NNWorld();
		
		
		// ACCESSORS
		
		void flagReload(bool flag_value)
			{ flag_reload = flag_value; }

		bool flagReload() const
			{ return flag_reload; }
			
		int numTimeInstants() const
			{ return particle_positions.size(); }

		int numParticlesAtInstant(int time_instant) const
			{ return particle_positions[time_instant].size(); }
			
		void currentTimeInstant(int instant)
			{ current_time_instant = ( instant > 0  &&  instant < numTimeInstants() ) ? instant : 0; }
			
		int currentTimeInstant() const
			{ return current_time_instant; }

			
		void filesPath(string path)
			{ time_instant_files_path = path; }

		string filesPath() const
			{ return time_instant_files_path; }
			
		void baseFileName(string name)
			{ time_instant_base_file_name = name; }
			
		string baseFileName() const
			{ return time_instant_base_file_name; }
			
		void fileNameScheme(FILE_NAME_SCHEME_TYPE scheme)
			{ file_name_scheme = scheme; }
			
		FILE_NAME_SCHEME_TYPE fileNameScheme() const
			{ return file_name_scheme; }
			
		void padWidth(int width)
			{ pad_width = width > 1 ? width : 1; }
			
		int padWidth() const
			{ return pad_width; }
		
		
		// FUNCTIONS
		
		void loadData();
		
		void printParticlesForAllTimeInstants() const;
		void printParticlesForTimeInstant(int t) const;
		
		void printVolumeBoundsForAllTimeInstants() const;
		void printVolumeBoundsForTimeInstant(int t) const;
		
		double getConcentrationInCone(Point3D sensor_cone_apex, Point3D sensor_cone_base_center, double sensor_cone_base_radius) const;
		bool isObstacleAtPoint(Point3D point) const;
		double lightIntensityAtPoint(Point3D point) const;
};

#endif
