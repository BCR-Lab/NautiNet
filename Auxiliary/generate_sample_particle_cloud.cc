#include <iostream>
#include "../Point3D.h"
#include <time.h>
#include <cstdlib>
using namespace std;

int main()
{
	srand(time(NULL));
	
	double diameter;
	int desired_num_particles;
	int num_particles = 0;
	
	cout << "Enter particle sphere diameter: ";
	cin >> diameter;

	Point3D corner(10, 10, -10);
	Point3D center(10 + diameter/2, 10 + diameter/2, -10 - diameter/2);
	
	double x, y, z;
	
	cout << "Enter desired number of particles: ";
	cin >> desired_num_particles;
	
	cout << "x\ty\tz\n";
	
	while(num_particles < desired_num_particles)
	{
		x = ((double) rand() / RAND_MAX) * diameter;
		y = ((double) rand() / RAND_MAX) * diameter;
		z = ((double) rand() / RAND_MAX) * diameter;
		
		Point3D point(corner.x + x, corner.y + y, corner.z - z);

		if(Point3D::distance(point, center) < diameter/2)
		{
			num_particles++;
			
			cout << point.x << "\t" << point.y << "\t" << point.z << endl;
		}
	}
	
	return 0;
}
