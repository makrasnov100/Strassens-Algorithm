//Strassen Algorithm Implementation
//CS473 Final Project
//Authors: Kostiantyn Makrasnov & Timothy Bruggeman
//Matrix class implementation file - used to store and complete simple matrix operations
//References:
//1) https://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c (random double value generation)
//2) https://stackoverflow.com/questions/25131062/overloading-assignment-operator-with-classes-and-vectors (assignment operator overloading)

#include "Matrix.h"

//[CONSTRUCTORS]
//Minimal Constructors
Matrix::Matrix(int rows, int columns, int groupMax)
{
	this->rows = rows;
	this->columns = columns;
	this->groupMax = groupMax;
	this->maxNeededDim = findSmallestPowTwo(groupMax);
}
//Partition Constructor
Matrix::Matrix(int startRowIdx, int startColumnIdx, int rows, int columns, vector<vector<double>> rawOther)
{
	this->rows = rows;
	this->columns = columns;
	this->groupMax = rows; // technically should be fine for our use but could make more robust
	this->maxNeededDim = findSmallestPowTwo(groupMax);

	//Allocate memory
	createEmptyMatrix();

	//Copy array values
	//cout << "Rows from " << startRowIdx << " to " << (startRowIdx + rows) << endl;
	//cout << "Columns drom " << startColumnIdx << " to " << (startColumnIdx + columns) << endl;
	for (int r = startRowIdx; r < (startRowIdx + rows); r++)
		for (int c = startColumnIdx; c < (startColumnIdx + columns); c++)
			rawMatrix[r - startRowIdx][c - startColumnIdx] = rawOther[r][c];
}

//Copy Constructor (FIX ME: might be uneeded)
Matrix::Matrix(const Matrix &other)
{
	//Copy meta data from other matrix
	this->rows = other.rows;
	this->columns = other.columns;
	this->groupMax = other.groupMax;
	this->maxNeededDim = other.maxNeededDim;

	//Allocate memory
	createEmptyMatrix();

	//Copy raw values from one matrix to another
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
			rawMatrix[r][c] = other.rawMatrix[r][c];
}

//[OPERATOR OVERLOADS]
//- Addition
Matrix operator+(const Matrix& a, const Matrix& b)
{
	if (a.rows != b.rows || a.columns != b.columns)
	{
		cout << "Cannot add matricies of different dimensions!" << endl;
		return a;
	}

	Matrix result(a.rows, a.columns, a.rows);
	result.createEmptyMatrix();

	for (int r = 0; r < a.rows; r++)
		for (int c = 0; c < a.columns; c++)
			result.rawMatrix[r][c] = a.rawMatrix[r][c] + b.rawMatrix[r][c];

	return result;
}
//- Subtraction
Matrix operator-(const Matrix& a, const Matrix& b)
{
	if (a.rows != b.rows || a.columns != b.columns)
	{
		cout << "Cannot subtract matricies of different dimensions!" << endl;
		return a;
	}

	Matrix result(a.rows, a.columns, a.rows);
	result.createEmptyMatrix();

	for (int r = 0; r < a.rows; r++)
		for (int c = 0; c < a.columns; c++)
			result.rawMatrix[r][c] = a.rawMatrix[r][c] - b.rawMatrix[r][c];
	
	return result;
}
//- Multiplication (size 1 matrices only)
Matrix operator*(const Matrix& a, const Matrix& b)
{
	if (a.rows != 1 || b.rows != 1 || a.columns != 1 || b.columns != 1)
	{
		cout << "Matrix multplication supported only for size 1 with * operator!" << endl;
		return a;
	}

	Matrix result(1, 1, 1);
	result.createEmptyMatrix();

	result.rawMatrix[0][0] = a.rawMatrix[0][0] * b.rawMatrix[0][0];

	return result;
}
// - Assignment (2)
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

///[GENERATORS]
// Allows to create matrices with random values -100 to 100
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
// Allows user to enter their own values for a matrix
void Matrix::readNewMatrix(string matrixName)
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
				cout << "Enter value for " << matrixName << " (" << r << "," << c << "): ";
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
// Initializes all raw matrix values to zero
void Matrix::createEmptyMatrix()
{
	//Allocating Memory
	rawMatrix.resize(maxNeededDim);
	for (int i = 0; i < maxNeededDim; i++)
	{
		rawMatrix[i].resize(maxNeededDim);
		for (int x = 0; x < maxNeededDim; x++)
		{
			rawMatrix[i].push_back(0);
		}
	}
}

//[UTILITY]
//Copies the entirety of one matrix into another at given position 
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
//Returns smallest power of two or the given number if already a power of two
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
//Prints matrix contents (no limits to the size printled - handled elsewhere)
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
//Checks if matrices can be multiplied (left for future feature)
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

//[MULTIPLIERS]
//Default ("Highschool")
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
