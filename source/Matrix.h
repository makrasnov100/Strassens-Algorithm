//Strassen Algorithm Implementation
//CS473 Final Project
//Authors: Kostiantyn Makrasnov & Timothy Bruggeman
//Matrix class header file - used to store and complete simple matrix operations
//References:
//1) https://stackoverflow.com/questions/11161541/overloaded-addition-assignment-operator-in-c-for-two-more-than-two-objects (operator overloading)

#include <iostream> //cout, cin
#include <string>
#include <vector>
#include <time.h>
#include <random>
#include <math.h>

using namespace std;

class Matrix
{
public:
	vector<vector<double>> rawMatrix;
	int rows;
	int columns;
	int maxNeededDim;
	int groupMax;

	//Constructors
	Matrix(const Matrix& matrix);
	Matrix(int rows, int columns, int groupMax);
	Matrix(int startRowIdx, int StartColumnIdx, int rows, int columns, vector<vector<double>> rawOther);

	//Operator Overloaders (1)
	friend Matrix operator*(const Matrix& a, const Matrix& b);
	friend Matrix operator+(const Matrix& a, const Matrix& b);
	friend Matrix operator-(const Matrix& a, const Matrix& b);
	Matrix& operator=(const Matrix& input);

	//Generators
	void generateRandomMatrix(int seed);
	void readNewMatrix(string matrixName);
	void createEmptyMatrix();

	//Utility
	int findSmallestPowTwo(int init);
	void printMatrix(string title);
	bool checkMultConditions(const Matrix& other, Matrix& result);
	void copyIntoMatrix(int startRow, int startColumn, Matrix other);

	//Multiplication Functionality
	void bruteForceMult(const Matrix& other, Matrix& result);
};