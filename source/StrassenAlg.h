//Strassen Algorithm Implementation
//CS473 Final Project
//Authors: Kostiantyn Makrasnov & Timothy Bruggeman
//Strassen class header file - used to perform the strassen algorithm functions

#include <iostream>
#include <vector>
#include "Matrix.h"

class StrassenAlg
{
public:

    //Entry Point
    static bool strassenLanding(Matrix first, Matrix second, Matrix& result);

    //Interim Functions
    static Matrix m1Compute(Matrix A00, Matrix A11, Matrix B00, Matrix B11);
    static Matrix m2Compute(Matrix A10, Matrix A11, Matrix B00);
    static Matrix m3Compute(Matrix A00, Matrix B01, Matrix B11);
    static Matrix m4Compute(Matrix A11, Matrix B10, Matrix B00);
    static Matrix m5Compute(Matrix A00, Matrix A01, Matrix B11);
    static Matrix m6Compute(Matrix A10, Matrix A00, Matrix B00, Matrix B01);
    static Matrix m7Compute(Matrix A01, Matrix A11, Matrix B10, Matrix B11);
};
