//Strassen Algorithm Implementation
//CS473 Final Project
//Authors: Kostiantyn Makrasnov & Timothy Bruggeman
//Matrix class implementation file - used to store and complete simple matrix operations
//References:
//1) https://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c (random double value generation)

#include "Matrix.h"


//Constructors
Matrix::Matrix(int rows, int columns, int groupMax)
{
    this->rows = rows;
    this->columns = columns;
    this->groupMax = groupMax;
    this->maxNeededDim = findSmallestPowTwo(groupMax);
    srand (time(NULL));
}


//Deconstructors
Matrix::~Matrix()
{
    for(int i = rows - 1; i <= 0; i--)
        delete rawMatrix[i];
    delete rawMatrix;
}


//Generators
void Matrix::generateRandomMatrix()
{
    //Seting up random parameters (1)
    uniform_real_distribution<double> unif(-100,100);
    default_random_engine re;

    //Allocating memory
    createEmptyMatrix();

    //Assigning values
    for(int r = 0; r < maxNeededDim; r++)
    {
        for(int c = 0; c < maxNeededDim; c++)
        {
            if(r < rows && c < columns)
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
            if(r < rows && c < columns)
            {
                cout << "Enter value for (" << r << "," << c << "): ";
                string curInput;
                getline(cin,curInput);
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
    rawMatrix = new double *[maxNeededDim];
    for(int i = 0; i < rows; i++)
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

void Matrix::printMatrix(string title)
{
    cout << title << endl;

    if(rawMatrix == NULL)
    {
        cout << "Cannot print empty matrix!" << endl;
        return;
    }

    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < columns; c++)
            cout << rawMatrix[r][c] << ", ";
        
        cout << endl;
    }

    cout << endl;
}

bool Matrix::checkConditions(const Matrix& other, Matrix& result)
{
    //Cancel (return false) if any of the matricies have issues

    if(rawMatrix == NULL || other.rawMatrix == NULL || result.rawMatrix == NULL)
    {
        cout << "One of the two matricies is empty, unable to multiply!" << endl;
        return false;
    }

    if(columns != other.rows)
    {
        cout << "Invalid matrix dimensions for multiplication!" << endl;
        return false;
    }

    if(rows != result.rows || other.columns != result.columns)
    {
        cout << "Result matrix has incorrect output dimensions!" << endl;
        return false;
    }

    return true;
}

//Multipliers
void Matrix::strassenMult(const Matrix& other, Matrix& result)
{
    checkConditions(other, result);

    //APPLY STATIC STRASSEN FUNCTION HERE OR PASTE YOUR CLASS FUNCTIONS INTO THE MATRIX CLASS

}

void Matrix::bruteForceMult(const Matrix& other, Matrix& result)
{
    checkConditions(other, result);

    for(int r = 0; r < result.rows; r++)
    {   
        for(int c = 0; c < result.columns; c++)
        {
            double sum = 0;
            for(int m = 0; m < rows; m++)
            {
                cout << "bruteForceMult 4 - sum: " << sum << endl;
                sum += rawMatrix[r][m] * other.rawMatrix[m][c]; 
            }
            
            cout << "Result for ROW: " << r << " COLOUMN: " << c << " - "<< sum << endl;

            result.rawMatrix[r][c] = sum;
        }
        cout << endl;
    }

    result.printMatrix("REsult before pass back:");

    return;
}