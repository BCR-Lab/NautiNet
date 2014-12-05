#include <algorithm>
#include "Matrix.h"
using namespace std;

void Matrix::allocate()
{
	// Check for proper matrix size.
	if(rows <= 0 || cols <= 0)
	{
		// This is an error! Handle it somehow.
		;
	}
	
	// Deallocate existing data grid.
	if(data != NULL)
	{
		for(size_t i = 0; i < rows; i++)
			delete [ ] data[i];
			
		delete [ ] data;
		
		data = NULL;
	}

	// Allocate new data grid.
	data = new matrix_data_t*[rows];
	
	for(size_t i = 0; i < rows; i++)
	{
		data[i] = new matrix_data_t[cols];
	}
}

void Matrix::zeroOutData()
{
	if(data == NULL)
	{
		// This is an error! Handle it somehow.
		;
	}

	for(size_t i = 0; i < rows; i++)
	{
		// Zero out all matrix values.
		for(size_t j = 0; j < cols; j++)
		{
			data[i][j] = 0;
		}
	}
}

Matrix::Matrix(MATRIX_PRESET_VALUE preset, size_t size) :
	rows(size),
	cols(size),
	data(NULL)
{
	allocate();
	
	switch(preset)
	{
		case IDENTITY:
			zeroOutData();
			for(size_t i = 0; i < size; i++)
				data[i][i] = 1;
			break;
		case ZERO:
		default:
			zeroOutData();
			break;
	}
}

Matrix::Matrix(size_t rows, size_t cols) :
	rows(rows),
	cols(cols),
	data(NULL)
{
	allocate();
}

Matrix::Matrix(size_t rows, size_t cols, double* values) :
	rows(rows),
	cols(cols),
	data(NULL)
{
	allocate();
	
	for(size_t i = 0; i < rows; i++)
	{
		for(size_t j = 0; j < cols; j++)
		{
			data[i][j] = values[rows*i + j];
		}
	}
}

Matrix::Matrix(const Matrix& right) :
	rows(right.rows),
	cols(right.cols),
	data(NULL)
{
	allocate();
	
	for(size_t i = 0; i < rows; i++)
	{
		for(size_t j = 0; j < cols; j++)
		{
			data[i][j] = right.data[i][j];
		}
	}
}

Matrix::~Matrix()
{
	for(size_t i = 0; i < rows; i++)
		delete [ ] data[i];
		
	delete [ ] data;
	
	data = NULL;
}

Matrix& Matrix::operator=(const Matrix& right)
{
	// Check for self-assignment.
	if(this == &right)
		return *this;
		
	// Check for matching matrix dimensions.
	// If the matrix dimensions don't match, throw an exception!
	if(this->rows != right.rows || this->cols != right.cols)
		;
	
	// Deallocate existing matrix data array.
	for(size_t i = 0; i < rows; i++)
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
		data = new matrix_data_t*[rows];
		
		// Copy matrix contents from right into *this.
		for(size_t i = 0; i < rows; i++)
		{
			data[i] = new matrix_data_t[cols];
			
			for(size_t j = 0; j < cols; j++)
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
	matrix_data_t** new_data = new matrix_data_t*[this->rows];
	for(size_t i = 0; i < this->rows; i++)
	{
		new_data[i] = new matrix_data_t[right.cols];
		
		for(size_t j = 0; j < right.cols; j++)
			new_data[i][j] = 0;
	}
		
	// Calculate the values of the result matrix.
	for(size_t i = 0; i < this->rows; i++)
		for(size_t j = 0; j < right.cols; j++)
			for(size_t k = 0; k < right.rows; k++)
				new_data[i][j] += this->data[i][k] * right.data[k][j];
				
	// Deallocate old array.
	for(size_t i = 0; i < rows; i++)
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
		
	for(size_t i = 0; i < rows; i++)
		for(size_t j = 0; j < cols; j++)
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
	
	for(size_t i = 1; i < rows; i++)
		for(size_t j = 0; j < i; j++)
			swap(data[i][j], data[j][i]);
}

matrix_data_t& Matrix::operator()(const size_t& row, const size_t& col)
{
	// Check for out-of-bounds.
	if(row >= rows || col >= cols)
	{
		// This is an error! Handle it somehow.
		;
	}
	
	return data[row][col];
}

const matrix_data_t& Matrix::operator()(const size_t& row, const size_t& col) const
{
	// Check for out-of-bounds.
	if(row >= rows || col >= cols)
	{
		// This is an error! Handle it somehow.
		;
	}
	
	return data[row][col];
}

void Matrix::print(ostream& out) const
{
	for(size_t i = 0; i < rows; i++)
	{
		for(size_t j = 0; j < cols; j++)
		{
			out << data[i][j] << ( j < cols-1 ? " " : "" );
		}
		out << endl;
	}
}

ostream& operator<<(ostream& out, Matrix m)
{
	// NOT YET IMPLEMENTED!!!
}
