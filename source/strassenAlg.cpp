//Strassen Algorithm Implementation
//CS473 Final Project
//Authors: Kostiantyn Makrasnov & Timothy Bruggeman
//Strassen class implementations file - used to perform the strassen algorithm functions

#include "StrassenAlg.h"

//Entry Point
bool StrassenAlg::strassenLanding(Matrix first, Matrix second, Matrix& result) 
{
    //Perform compatibility check
    if(first.rawMatrix.size() != second.rawMatrix.size())
    {
        cout << "Invalid Matrices were attempted to be multiplied by Strassen Function!" << endl;
        return false;
    }

    //Seperate into component matrices
    int subMatrixSize = first.rawMatrix.size()/2;
    Matrix A00(0, 0, subMatrixSize, subMatrixSize, first.rawMatrix);
    Matrix A01(0, subMatrixSize, subMatrixSize, subMatrixSize, first.rawMatrix);
    Matrix A10(subMatrixSize, 0, subMatrixSize, subMatrixSize, first.rawMatrix);
    Matrix A11(subMatrixSize, subMatrixSize, subMatrixSize, subMatrixSize, first.rawMatrix);
    Matrix B00(0, 0, subMatrixSize, subMatrixSize, second.rawMatrix);
    Matrix B01(0, subMatrixSize, subMatrixSize, subMatrixSize, second.rawMatrix);
    Matrix B10(subMatrixSize, 0, subMatrixSize, subMatrixSize, second.rawMatrix);
    Matrix B11(subMatrixSize, subMatrixSize, subMatrixSize, subMatrixSize, second.rawMatrix);

    //Perform Interim Calculations (Recursively Using Strassen)
    Matrix M1 = m1Compute(A00, A11, B00, B11);
    Matrix M2 = m2Compute(A10, A11, B00);
    Matrix M3 = m3Compute(A00, B01, B11);
    Matrix M4 = m4Compute(A11, B10, B00);
    Matrix M5 = m5Compute(A00, A01, B11);
    Matrix M6 = m6Compute(A10, A00, B00, B01);
    Matrix M7 = m7Compute(A01, A11, B10, B11);

    //Merge Solutions
    Matrix topLeft = M1 + M4 - M5 + M7;
    result.copyIntoMatrix(0,0,topLeft);
    Matrix topRight = M3 + M5;
    result.copyIntoMatrix(0,subMatrixSize,topRight);
    Matrix bottomLeft = M2 + M4;
    result.copyIntoMatrix(subMatrixSize,0,bottomLeft);
    Matrix bottomRight = M1 + M3 - M2 + M6;
    result.copyIntoMatrix(subMatrixSize,subMatrixSize,bottomRight);

	return true; //Algorthm Completed Succesfuly
}

//Interim Functions m1 - m7 (page 190 of levitin)
Matrix StrassenAlg::m1Compute(Matrix A00, Matrix A11, Matrix B00, Matrix B11)
{
    //cout << "M1 - 1" << endl;
    if(A00.rawMatrix.size() == 1)
    {
        Matrix result = (A00 + A11) * (B00 + B11);
        return result;
    }
    else
    {
        Matrix first = A00 + A11;
        Matrix second = B00 + B11;
        Matrix result(first.rows, first.columns, first.rows);
        result.createEmptyMatrix();
        StrassenAlg::strassenLanding(first, second, result);
        return result;
    }
}

Matrix StrassenAlg::m2Compute(Matrix A10, Matrix A11, Matrix B00)
{
    if(A10.rawMatrix.size() == 1)
    {
        Matrix result = (A10 + A11) * B00;
        return result;
    }
    else
    {
        Matrix first = A10 + A11;
        Matrix result(first.rows, first.columns, first.rows);
        result.createEmptyMatrix();
        strassenLanding(first, B00, result);
        return result;
    }
}

Matrix StrassenAlg::m3Compute(Matrix A00, Matrix B01, Matrix B11)
{
    if(A00.rawMatrix.size() == 1)
    {
        Matrix result = A00 * (B01 - B11);
        return result;
    }
    else
    {
        Matrix second = B01 - B11;
        Matrix result(second.rows, second.columns, second.rows);
        result.createEmptyMatrix();
        strassenLanding(A00, second, result);
        return result;
    }
}

Matrix StrassenAlg::m4Compute(Matrix A11, Matrix B10, Matrix B00)
{
    if(A11.rawMatrix.size() == 1)
    {
        Matrix result = A11 * (B10 - B00);
        return result;
    }
    else
    {
        Matrix second = B10 - B00;
        Matrix result(second.rows, second.columns, second.rows);
        result.createEmptyMatrix();
        strassenLanding(A11, second, result);
        return result;
    }
}

Matrix StrassenAlg::m5Compute(Matrix A00, Matrix A01, Matrix B11)
{
    if(A00.rawMatrix.size() == 1)
    {
        Matrix result = (A00 + A01) * B11;
        return result;
    }
    else
    {
        Matrix first = A00 + A01;
        Matrix result(first.rows, first.columns, first.rows);
        result.createEmptyMatrix();
        strassenLanding(first, B11, result);
        return result;
    }
}

Matrix StrassenAlg::m6Compute(Matrix A10, Matrix A00, Matrix B00, Matrix B01)
{
    if(A10.rawMatrix.size() == 1)
    {
        Matrix result = (A10 - A00) * (B00 + B01);
        return result;
    }
    else
    {
        Matrix first = A10 - A00;
        Matrix second = B00 + B01;
        Matrix result(first.rows, first.columns, first.rows);
        result.createEmptyMatrix();
        strassenLanding(first, second, result);
        return result;
    }
}

Matrix StrassenAlg::m7Compute(Matrix A01, Matrix A11, Matrix B10, Matrix B11)
{
    if(A01.rawMatrix.size() == 1)
    {
        Matrix result = (A01 - A11) * (B10 + B11);
        return result;
    }
    else
    {
        Matrix first = A01 - A11;
        Matrix second = B10 + B11;
        Matrix result(second.rows, second.columns, second.rows);
        result.createEmptyMatrix();
        strassenLanding(first, second, result);
        return result;
    }
}