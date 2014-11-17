#include "Matrix.h"
#include "MatrixUtility.h"
#include <cmath>
using namespace std;

int main()
{
	double values[3][3] = { { 1, 2, 3 },
							{ 4, 5, 6 },
							{ 7, 8, 9 } };
							
	Matrix m(3, 3, (double*) values);
	
	m.print();
	
	Matrix n(IDENTITY, 4);
	
	n.print();
	
	make3DRotationMatrix(X, M_PI/4).print();
	make3DTranslationMatrix(4, 5, 6).print();
	make3DScaleMatrix(4, 5, 6).print();

	return 0;
}
