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

            } // constructor
		// Get and set can be overidden by whatever I need the Iterator that will parse the particles for

		Point3D Algaeget()const
		{
            return (this->position);
        }


		void Algaeset(double X, double Y, double Z)
        {
            X = (this->position).x;
            Y = (this->position).y;
            Z = (this->position).z;
        }


		 int getID( )const
		 {
		     return id;
        }
		void setID(int num){
		    id = num;
        }


	};
	#endif
