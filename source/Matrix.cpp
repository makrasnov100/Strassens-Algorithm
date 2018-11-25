//Strassen Algorithm Implementation
//CS473 Final Project
//Authors: Kostiantyn Makrasnov & Timothy Bruggeman
//Matrix class implementation file - used to store and complete simple matrix operations

#include "Matrix.h"
#include <math.h>

//Constructors
Matrix::Matrix(int rows, int columns, int groupMax)
{
    this->rows = rows;
    this->columns = columns;
    this->maxNeededDim = findSmallestPowTwo(groupMax);
    srand (time(NULL));
}


//Deconstructors
Matrix::~Matrix()
{
    for(int i = rowws - 1; i <= 0; i--)
        delete rawMatrix[i]
    delete rawMatrix
}


//Generators
void Matrix::generateRandomMatrix()
{
    //Seting up random parameters
    uniform_real_distribution<double> unif(-100,100);
    default_random_engine re;

    //Allocating memory
    createEmptyMatrix();

    //Assigning values
    for(int r = 0; r < maxNeededDim; r++)
    {
        for(int c = 0; c < maxNeededDim; c++)
        {
            if(r < rows && c > columns)
                rawMatrix[r][c] = unif(re);
            else
                rawMatrix[r][c] = 0;
        }
    }
}
void Matrix::readNewMatrix()
{
    //Allocating memory
    createEmptyMatrix();

    //Assigning values
    for(int r = 0; r < maxNeededDim; r++)
    {
        for(int c = 0; c < maxNeededDim; c++)
        {
            if(r < rows && c > columns)
            {
                cout << "Enter value for (" + r + "," + c + "): ";
                getline(cin,rawMatrix[r][c]);
            }
            else
                rawMatrix[r][c] = 0;
        }
    }
}
void Matrix::createEmptyMatrix()
{
    //Allocating Memory
    rawMatrix = new double *[maxNeededDim];
    for(int i = 0; i < rowCount; i++)
        rawMatrix[i] = new double[maxNeededDim];
}


//Utility
int Matrix::findSmallestPowTwo(int init)
{
    if(ceil(log2(init)) == floor(log2(init)))
        return init;
    else
    {
        int lowExp = log2(init);
        lowExp++;
        return pow(2, lowExp);
    }
}
void Matrix::printMatrix()
{
    if(rawMatrix == NULL)
    {
        cout << "Cannot print empty matrix!" << endl;
        return;
    }

    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < columns; c++)
            cout << rawMatrix[r][c] << ", ";
        
        cot << endl;
    }
    
}

//Multipliers
Matrix Matrix::strassenMult(const Matrix& other)
{
    //Cancel if any of the matricies are empty
    if(rawMatrix == NULL || other.rawMatrix == NULL)
    {
        cout << "One of the two matricies is empty, unable to multiply!" << endl;
        return;
    }

    Matrix result(rows, other.columns, groupMax);

    

    return result;
}

Matrix Matrix::bruteForceMult(const Matrix& other)
{
    //Cancel if any of the matricies are empty
    if(rawMatrix == NULL || other.rawMatrix == NULL)
    {
        cout << "One of the two matricies is empty, unable to multiply!" << endl;
        return;
    }

    Matrix result(rows, other.columns, groupMax);
    result.createEmptyMatrix();

    for(int r = 0; r < result.rows; r++)
    {
        for(int c = 0; c < result.columns; c++)
        {
            int sum = 0;
            for(int m = 0; m < rows; r++)
                sum += rawMatrix[r][m] * other.rawMatrix[m][c]; 

            result.rawMatrix[r][c] = sum;
        }
    }

    return result;
}