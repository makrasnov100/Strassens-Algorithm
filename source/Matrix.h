//Strassen Algorithm Implementation
//CS473 Final Project
//Authors: Kostiantyn Makrasnov & Timothy Bruggeman
//Matrix class header file - used to store and complete simple matrix operations

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
    Matrix(int rows, int columns, int groupMax);
    Matrix(int startRowIdx, int StartColumnIdx, int rows, int columns, vector<vector<double>> rawOther);

    //Generators
    void generateRandomMatrix();
    void readNewMatrix();
    void createEmptyMatrix();
    
    //Utility
    int findSmallestPowTwo(int init);
    void printMatrix(string title);
    bool checkMultConditions(const Matrix& other, Matrix& result);
    bool AddToCurrent(Matrix other);
    bool SubtractFromCurrent(Matrix other);



    //Multiplication Functionality
    void strassenMult(const Matrix& other, Matrix& result);
    void bruteForceMult(const Matrix& other, Matrix& result);
};
