//Strassen Algorithm Implementation
//CS473 Final Project
//Authors: Kostiantyn Makrasnov & Timothy Bruggeman
//Matrix class implementation file - used to store and complete simple matrix operations
//References:
//1) https://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c (random double value generation)
//2) https://stackoverflow.com/questions/25131062/overloading-assignment-operator-with-classes-and-vectors (assignment operator overloading)

#include "Matrix.h"

int strassenLanding(Matrix A, Matrix B, Matrix C, int dim);

//Constructors
Matrix::Matrix(int rows, int columns, int groupMax)
{
	this->rows = rows;
	this->columns = columns;
	this->groupMax = groupMax;
	this->maxNeededDim = findSmallestPowTwo(groupMax);
}

Matrix::Matrix(int startRowIdx, int startColumnIdx, int rows, int columns, vector<vector<double>> rawOther)
{
	this->rows = rows;
	this->columns = columns;
	this->groupMax = rows; // technically should be fine for our use but could make more robust
	this->maxNeededDim = findSmallestPowTwo(groupMax);

	//Allocating memory
	createEmptyMatrix();

	//Copy array values
	//cout << "Rows from " << startRowIdx << " to " << (startRowIdx + rows) << endl;
	//cout << "Columns drom " << startColumnIdx << " to " << (startColumnIdx + columns) << endl;
	for (int r = startRowIdx; r < (startRowIdx + rows); r++)
	{
		for (int c = startColumnIdx; c < (startColumnIdx + columns); c++)
		{
			//cout << "r:" << r-startRowIdx << " c:" << c-startColumnIdx << endl;
			rawMatrix[r - startRowIdx][c - startColumnIdx] = rawOther[r][c];
		}
	}
}

//Copy Constructor
Matrix::Matrix(const Matrix &other)
{
	//Copy meta data from other matrix
	this->rows = other.rows;
	this->columns = other.columns;
	this->groupMax = other.groupMax;
	this->maxNeededDim = other.maxNeededDim;

	//Allocating memory
	createEmptyMatrix();

	//Copy raw values from one matrix to another
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
			rawMatrix[r][c] = other.rawMatrix[r][c];
}

//Operator overloads definition
Matrix operator+(const Matrix& a, const Matrix& b)
{
	if (a.rows != b.rows || a.columns != b.columns)
	{
		cout << "Cannot add matricies of different dimensions!" << endl;
		return a; //FIX ME: return a 0 matrix instead
	}

	Matrix result(a.rows, a.columns, a.rows); // FIX ME: should be thesame size but could take max still
	result.createEmptyMatrix();

	for (int r = 0; r < a.rows; r++)
		for (int c = 0; c < a.columns; c++)
			result.rawMatrix[r][c] = a.rawMatrix[r][c] + b.rawMatrix[r][c];

	return result;
}

Matrix operator-(const Matrix& a, const Matrix& b)
{
	if (a.rows != b.rows || a.columns != b.columns)
	{
		cout << "Cannot subtract matricies of different dimensions!" << endl;
		return a; //FIX ME: return a 0 matrix instead
	}

	Matrix result(a.rows, a.columns, a.rows); // FIX ME: should be thesame size but could take max still
	result.createEmptyMatrix();

	for (int r = 0; r < a.rows; r++)
		for (int c = 0; c < a.columns; c++)
			result.rawMatrix[r][c] = a.rawMatrix[r][c] - b.rawMatrix[r][c];
	
	return result;
}

Matrix operator*(const Matrix& a, const Matrix& b)
{
	if (a.rows != 1 || b.rows != 1 || a.columns != 1 || b.columns != 1) //FIX ME: most likely can use only one comparison
	{
		cout << "Matrix multplication supported only for size 1 with * operator!" << endl;
		return a; //FIX ME: return a 0 matrix instead
	}

	Matrix result(1, 1, 1); // FIX ME: should be thesame size but could take max still
	result.createEmptyMatrix();

	result.rawMatrix[0][0] = a.rawMatrix[0][0] * b.rawMatrix[0][0];

	return result;
}


//Assignment overloading (2)
Matrix& Matrix::operator=(const Matrix& other)
{
	this->rows = other.rows;
	this->columns = other.columns;
	this->groupMax = other.groupMax;
	this->maxNeededDim = other.maxNeededDim;

	createEmptyMatrix();

	//Copy raw values from one matrix to another
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
			rawMatrix[r][c] = other.rawMatrix[r][c];

	return *this;
}

//Generators
void Matrix::generateRandomMatrix(int seed)
{
	//Seting up random parameters (1)
	uniform_real_distribution<double> unif(-100, 100);
	default_random_engine re(seed);

	//Allocating memory
	createEmptyMatrix();

	//Assigning values
	for (int r = 0; r < maxNeededDim; r++)
		for (int c = 0; c < maxNeededDim; c++)
			if (r < rows && c < columns)
				rawMatrix[r][c] = unif(re);

	//Uncomment to see that the matrix was padded with zeros
	/*cout << "Padded Matrix " << maxNeededDim << endl;
	for(int a = 0; a < maxNeededDim; a++)
	{
		for(int b = 0; b < maxNeededDim; b++)
			cout << rawMatrix[a][b] << ", ";

		cout << endl;
	}*/

}
void Matrix::readNewMatrix()
{
	//Allocating memory
	createEmptyMatrix();

	//Assigning values
	for (int r = 0; r < maxNeededDim; r++)
	{
		for (int c = 0; c < maxNeededDim; c++)
		{
			if (r < rows && c < columns)
			{
				cout << "Enter value for (" << r << "," << c << "): ";
				string curInput;
				getline(cin, curInput);
				rawMatrix[r][c] = stod(curInput);
			}
			else
			{
				rawMatrix[r][c] = 0;
			}
		}
	}
}
void Matrix::createEmptyMatrix()
{
	//Allocating Memory
	//cout << "Creating Empty Matrix 1 - " << maxNeededDim << endl;
	rawMatrix.resize(maxNeededDim);
	//cout << "Creating Empty Matrix 2" << endl;
	for (int i = 0; i < maxNeededDim; i++)
	{
		//cout << "Creating Empty Matrix 3" << endl;
		rawMatrix[i].resize(maxNeededDim);
		for (int x = 0; x < maxNeededDim; x++)
		{
			rawMatrix[i].push_back(0);
		}
	}
	//cout << "Creating Empty Matrix 4" << endl;
}

//Utility
void Matrix::copyIntoMatrix(int startRow, int startColumn, Matrix other)
{
	//check for space avalibility
	if((startRow + other.rawMatrix.size()) > rawMatrix.size() || (startColumn + other.rawMatrix[0].size()) > rawMatrix[0].size())
	{
		cout << "Cannot copy INTO matrix because the size is too big!" << endl;
		return;
	}

	//copy values into matrix
	for (int r = 0; r < other.rawMatrix.size(); r++)
		for (int c = 0; c < other.rawMatrix[0].size(); c++)
			rawMatrix[r + startRow][c + startColumn] = other.rawMatrix[r][c];
}

int Matrix::findSmallestPowTwo(int init)
{
	if (ceil(log2(init)) == floor(log2(init)))
		return init;
	else
	{
		int lowExp = log2(init);
		lowExp++;
		return pow(2, lowExp);
	}
}

void Matrix::printMatrix(string title)
{
	cout << title << endl;

	if (rawMatrix.empty())
	{
		cout << "Cannot print empty matrix!" << endl;
		return;
	}

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < columns; c++)
			cout << rawMatrix[r][c] << ", ";

		cout << endl;
	}

	cout << endl;
}

bool Matrix::checkMultConditions(const Matrix& other, Matrix& result)
{
	//Cancel (return false) if any of the matricies have issues
	if (rawMatrix.empty() || other.rawMatrix.empty() || result.rawMatrix.empty())
	{
		cout << "One of the two matricies is empty, unable to multiply!" << endl;
		return false;
	}

	if (columns != other.rows)
	{
		cout << "Invalid matrix dimensions for multiplication!" << endl;
		return false;
	}

	if (rows != result.rows || other.columns != result.columns)
	{
		cout << "Result matrix has incorrect output dimensions!" << endl;
		return false;
	}

	return true;
}

//Multipliers
void Matrix::bruteForceMult(const Matrix& other, Matrix& result)
{
	checkMultConditions(other, result);

	for (int r = 0; r < result.rows; r++)
	{
		for (int c = 0; c < result.columns; c++)
		{
			double sum = 0;
			for (int m = 0; m < rows; m++)
			{
				sum += rawMatrix[r][m] * other.rawMatrix[m][c];
			}

			result.rawMatrix[r][c] = sum;
		}
	}

	return;
}
