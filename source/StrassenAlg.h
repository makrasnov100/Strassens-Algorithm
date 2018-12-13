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
    bool strassenLanding(Matrix first, Matrix second, Matrix result, int dim);

    //Interim Functions
    Matrix m1Compute(Matrix A00, Matrix A11, Matrix B00, Matrix B11);
    Matrix m2Compute(Matrix A10, Matrix A11, Matrix B00);
    Matrix m3Compute(Matrix A00, Matrix B01, Matrix B11);
    Matrix m4Compute(Matrix A11, Matrix B10, Matrix B00);
    Matrix m5Compute(Matrix A00, Matrix A01, Matrix B11);
    Matrix m6Compute(Matrix A10, Matrix A00, Matrix B00, Matrix B01);
    Matrix m7Compute(Matrix A01, Matrix A11, Matrix B10, Matrix B11);

    //Element Output Functions
    //maybe in landing?

};
