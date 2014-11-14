#include <algorithm>
#include "Matrix.h"
using namespace std;

Matrix::Matrix(int rows, int cols) :
	rows(rows),
	cols(cols)
{
	// Check for proper matrix size.
	if(rows <= 0 || cols <= 0)
	{
		// This is an error! Handle it somehow.
		;
	}

	data = new matrix_data_type*[rows];
	
	for(int i = 0; i < rows; i++)
	{
		data[i] = new matrix_data_type[cols];
	}
}

Matrix::Matrix(int rows, int cols, const double** values) :
	rows(rows),
	cols(cols)
{
	// Check for proper matrix size.
	if(rows <= 0 || cols <= 0)
	{
		// This is an error! Handle it somehow.
		;
	}

	data = new matrix_data_type*[rows];
	
	for(int i = 0; i < rows; i++)
	{
		data[i] = new matrix_data_type[cols];
		
		for(int j = 0; j < cols; j++)
		{
			data[i][j] = values[i][j];
		}
	}
}

Matrix::Matrix(const Matrix& right) :
	rows(right.rows),
	cols(right.cols)
{
	if(rows == 0 || cols == 0)
	{
		// This is an error! Handle it somehow.
		;
	}
	else
	{
		// Allocate matrix data array.
		data = new matrix_data_type*[rows];
		
		// Copy matrix contents from right into *this.
		for(int i = 0; i < rows; i++)
		{
			data[i] = new matrix_data_type[cols];
			
			for(int j = 0; j < cols; j++)
			{
				data[i][j] = right.data[i][j];
			}
		}
	}
}

Matrix::~Matrix()
{
	for(int i = 0; i < rows; i++)
		delete [ ] data[i];
		
	delete [ ] data;
	
	data = NULL;
}

Matrix& Matrix::operator=(const Matrix& right)
{
	// Check for self-assignment.
	if(this == &right)
		return *this;
	
	// Deallocate existing matrix data array.
	for(int i = 0; i < rows; i++)
		delete [ ] data[i];
		
	delete [ ] data;
	
	// Set new variable values.
	data = NULL;
	rows = right.rows;
	cols = right.cols;
	
	if(rows == 0 || cols == 0)
	{
		// This is an error! Handle it somehow.
		;
	}
	else
	{
		// Allocate matrix data array.
		data = new matrix_data_type*[rows];
		
		// Copy matrix contents from right into *this.
		for(int i = 0; i < rows; i++)
		{
			data[i] = new matrix_data_type[cols];
			
			for(int j = 0; j < cols; j++)
			{
				data[i][j] = right.data[i][j];
			}
		}
	}
	
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& right)
{
	if(this->cols != right.rows)
	{
		// This is an error! Handle it somehow!
		;
	}
	
	// Create new data array to store the result.
	// Result will be a this.rows x right.cols size matrix.
	matrix_data_type** new_data = new matrix_data_type*[this->rows];
	for(int i = 0; i < this->rows; i++)
	{
		new_data[i] = new matrix_data_type[right.cols];
		
		for(int j = 0; j < right.cols; j++)
			new_data[i][j] = 0;
	}
		
	// Calculate the values of the result matrix.
	for(int i = 0; i < this->rows; i++)
		for(int j = 0; j < right.cols; j++)
			for(int k = 0; k < right.rows; k++)
				new_data[i][j] += this->data[i][k] * right.data[k][j];
				
	// Deallocate old array.
	for(int i = 0; i < rows; i++)
		delete [ ] data[i];
		
	delete [ ] data;
	
	// Set new variable values.
	data = new_data;
	// Rows stay the same...
	cols = right.cols;
	
	return *this;
}

Matrix Matrix::operator*(const Matrix& right) const
{
	Matrix result(*this);
	result *= right;
	return right;
}

bool Matrix::operator==(const Matrix& right) const
{
	// If the dimensions of the matrices don't match, clearly they can't be equal.
	if(this->rows != right.rows || this->cols != right.cols)
		return false;
		
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			if(data[i][j] != right.data[i][j])
				return false;
				
	return true;
}


bool Matrix::operator!=(const Matrix& right) const
{
	return !(*this == right);
}

void Matrix::transpose()
{
	// If the matrix isn't square, can't transpose!
	// Throw an exception or something.
	if(rows != cols)
		;
	
	for(int i = 0; i < rows/2; i++)
		for(int j = 0; j < cols/2; j++)
			swap(data[i][j], data[j][i]);
}

matrix_data_type& Matrix::operator()(const unsigned int& row, const unsigned int& col)
{
	// Check for out-of-bounds.
	if(row >= rows || col >= cols)
	{
		// This is an error! Handle it somehow.
		;
	}
	
	return data[row][col];
}

const matrix_data_type& Matrix::operator()(const unsigned int& row, const unsigned int& col) const
{
	// Check for out-of-bounds.
	if(row >= rows || col >= cols)
	{
		// This is an error! Handle it somehow.
		;
	}
	
	return data[row][col];
}
