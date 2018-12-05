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


Matrix::Matrix(int startRowIdx, int startColumnIdx, int rows, int columns, vector<vector<double>> rawOther)
{
    this->rows = rows;
    this->columns = columns;
    this->groupMax = rows; // technically should be fine for our use but could make more robust
    this->maxNeededDim = findSmallestPowTwo(groupMax);
    srand (time(NULL));
    
    //Allocating memory
    createEmptyMatrix();

    //Copy array values
    //cout << "Rows from " << startRowIdx << " to " << (startRowIdx + rows) << endl;
    //cout << "Columns drom " << startColumnIdx << " to " << (startColumnIdx + columns) << endl;
    for(int r = startRowIdx; r < (startRowIdx + rows); r++)
    {
        for(int c = startColumnIdx; c < (startColumnIdx + columns); c++)
        {
            //cout << "r:" << r-startRowIdx << " c:" << c-startColumnIdx << endl;
            rawMatrix[r-startRowIdx][c-startColumnIdx] = rawOther[r][c];
        }
    }

    printMatrix("Matrix After Copying!");
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
        for(int c = 0; c < maxNeededDim; c++)
            if(r < rows && c < columns)
                rawMatrix[r][c] = unif(re);

    //Uncomment to see that the matrix was padded wwith zeros
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
    rawMatrix.resize(maxNeededDim);
    for(int i = 0; i < maxNeededDim; i++)
    {
        rawMatrix[i].resize(maxNeededDim);
        for(int x = 0; x < maxNeededDim; x++)
        {
            rawMatrix[i].push_back(0);
        }
    }
}

//Utility
bool Matrix::AddToCurrent(const Matrix other)
{
    if(rows != other.rows || columns != other.columns)
    {
        cout << "Cannot add matricies of different dimensions!" << endl;
        return false;
    }

    for(int r = 0; r < rows; r++)
        for(int c = 0; c < columns; c++)
            rawMatrix[r][c] += other.rawMatrix[r][c];
}

bool Matrix::SubtractFromCurrent(const Matrix other)
{
    if(rows != other.rows || columns != other.columns)
    {
        cout << "Cannot add subtract of different dimensions!" << endl;
        return false;
    }

    for(int r = 0; r < rows; r++)
        for(int c = 0; c < columns; c++)
            rawMatrix[r][c] -= other.rawMatrix[r][c];
}


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

    if(rawMatrix.empty())
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

bool Matrix::checkMultConditions(const Matrix& other, Matrix& result)
{
    //Cancel (return false) if any of the matricies have issues
    if(rawMatrix.empty() || other.rawMatrix.empty() || result.rawMatrix.empty())
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
    checkMultConditions(other, result);

    //APPLY STATIC STRASSEN FUNCTION HERE OR PASTE YOUR CLASS FUNCTIONS INTO THE MATRIX CLASS

}

void Matrix::bruteForceMult(const Matrix& other, Matrix& result)
{
    checkMultConditions(other, result);

    for(int r = 0; r < result.rows; r++)
    {   
        for(int c = 0; c < result.columns; c++)
        {
            double sum = 0;
            for(int m = 0; m < rows; m++)
            {
                sum += rawMatrix[r][m] * other.rawMatrix[m][c]; 
            }

            result.rawMatrix[r][c] = sum;
        }
        cout << endl;
    }

    return;
}
