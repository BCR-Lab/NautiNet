#include <iostream>
#include "Point3D.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "Algae.h"
using namespace std;

int main()
{
    stringstream filename(stringstream::in | stringstream::out);
    filename<<"CoordsTimeInstant";
    int timestep = 0;
    cout << "Enter a number from 0 to 202"<< endl;
    cin >> timestep;
    filename<<timestep;

        ofstream testoutput;
        testoutput.open("test.txt");// opening of the test file

        fstream stream ((filename.str()).c_str());
        string sent;
        double xval;
        double yval;
        double zval;
        stream.ignore(256,'\n'); // ignores up to 256 characters or until it reaches a new line  skips the first line
        while(getline(stream, sent))
        {
            testoutput.precision(10);// essential to keeping the data accurate to 10 decimal places, otherwise it gets truncated
            stringstream river(sent);
            river >> xval >> yval >> zval;//reads the file in order x, y ,z
            testoutput << xval << " " <<  yval << " " << zval << endl; // writes the test file in order x, y, z,
                cout << xval << " " <<  yval << " " << zval << endl;// outputs in terminal
        }
            testoutput.close();// closing of the test file

    return 0;
}
