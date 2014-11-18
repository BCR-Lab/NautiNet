#ifndef ALGAE_H
#define ALGAE_H

#include "Point3D.h"
class ALGAE
{
// holds value for locations
private:
	     Point3D position;
            int id;
public:
		inline ALGAE(){
            id = 0;
            position.x = 0;
            position.y = 0;
            position.z = 0;
            }; // constructor
		// Get and set can be overidden by whatever I need the Iterator that will parse the particles for

		Point3D Algaeget()const
		{return position.x;
         return position.y;
         return position.z;}


		void Algaeset(double X, double Y, double Z)
		{
        X = position.x;
        Y = position.y;
        Z = position.z;
        };


		 int getID( )const {return id;}
		void setID(int num){id = num};


	};
	#endif
