#ifndef MATRIX_H
#define MATRIX_H

#include <cstring>
using namespace std;

typedef double matrix_data_type;

class Matrix
{
	private:
		matrix_data_type** data;
		
		int rows;
		int cols;
	
	public:
	
		// CONSTRUCTORS & DESTRUCTOR
		
		Matrix(int rows, int cols);
		Matrix(int rows, int cols, const double** values);
		Matrix(const Matrix& right);
		
		~Matrix();
				
		// OPERATORS
		
		// Assignment operator.
		Matrix& operator=(const Matrix& right);
		
		// Arithmetic operators.
		Matrix& operator*=(const Matrix& right);
		Matrix operator*(const Matrix& right) const;
		
		// Boolean operators.
		bool operator==(const Matrix& right) const;
		bool operator!=(const Matrix& right) const;
		
		// Access operator (and const version).
		matrix_data_type& operator()(const unsigned int& row, const unsigned int& col);
		const matrix_data_type& operator()(const unsigned int& row, const unsigned int& col) const;
		
		// ACCESSORS
		
		int getNumRows() { return rows; }
		int getNumCols() { return cols; }
		
		// FUNCTIONS
		
		void transpose();
};

#endif
