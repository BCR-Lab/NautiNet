#ifndef MATRIX_H
#define MATRIX_H

#include <cstring>
#include <iostream>
using namespace std;

typedef double matrix_data_t;

typedef enum
{
	IDENTITY,
	ZERO,
} MATRIX_PRESET_VALUE;

class Matrix
{
	private:
		matrix_data_t** data;
		
		size_t rows;
		size_t cols;
		
		void allocate();
		void zeroOutData();
	
	public:
	
		// CONSTRUCTORS & DESTRUCTOR
		
		Matrix(size_t rows, size_t cols);
		Matrix(size_t rows, size_t cols, double* values);
		Matrix(const Matrix& right);
		Matrix(MATRIX_PRESET_VALUE preset, size_t size);
				
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
		
		// Cell access operator (and const version).
		matrix_data_t& operator()(const size_t& row, const size_t& col);
		const matrix_data_t& operator()(const size_t& row, const size_t& col) const;
		
		// Stream insertion operator.
		friend ostream& operator<<(ostream& out, Matrix m);
		
		// ACCESSORS
		
		int numRows() { return rows; }
		int numCols() { return cols; }
		
		// FUNCTIONS
		
		void transpose();
		
		void print(ostream& out = cout);
};

#endif
