//Strassen Algorithm Implementation
//CS473 Final Project
//Authors: Kostiantyn Makrasnov & Timothy Bruggeman
//Matrix class header file - used to store and complete simple matrix operations

#include <iostream> //cout, cin
#include <time.h>
#include <random>

class Matrix
{
public:
    double ** rawMatrix; 
    int rows;
    int columns;
    int maxNeededDim;


    //Constructors
    Matrix(int rows, int columns, int groupMax);

    //Deconstructors
    ~Matrix();

    //Generators
    void generateNewRandomMatrix();
    void readNewMatrix();
    void createEmptyMatrix();
    
    //Utility
    int findSmallestPowTwo(int init);
    void printMatrix();

    //Multiplication Functionality
    Matrix strassenMult(const Matrix& other);
    Matrix bruteForceMult(const Matrix& other);
}
