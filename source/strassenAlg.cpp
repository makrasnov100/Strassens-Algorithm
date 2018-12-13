//Strassen Algorithm Implementation
//CS473 Final Project
//Authors: Kostiantyn Makrasnov & Timothy Bruggeman
//Strassen class implementations file - used to perform the strassen algorithm functions

#include "StrassenAlg.h"

//Entry Point
bool StrassenAlg::strassenLanding(Matrix first, Matrix second, Matrix& result) 
{

    //Perform Interim Calculations (Recursively Using Strassen)
    Matrix originalTopLeft();
    Matrix originalTopRight();
    Matrix originalBotomLeft();
    Matrix originalBottomRight();

    Matrix M1 = m1Compute();
    Matrix M2 = m2Compute();
    Matrix M3 = m2Compute();
    Matrix M4 = m2Compute();
    Matrix M5 = m2Compute();
    Matrix M6 = m2Compute();
    Matrix M7 = m2Compute();

    //Merge Solutions
    //Create Operator Overaloaders!
    //Matrix topLeft = M1 + M4 - M5 + M7;
    //Matrix topRight = M3 + M5;
    //Matrix bottomLeft = M2 + M4;
    //Matrix bottomRight = M1 + M3 - M2 + M6;

	return true; //Algorthm Completed Succesfuly
}

//Interim Functions
Matrix StrassenAlg::m1Compute(Matrix A00, Matrix A11, Matrix B00, Matrix B11)
{

}

Matrix StrassenAlg::m2Compute(Matrix A10, Matrix A11, Matrix B00)
{

}

Matrix StrassenAlg::m3Compute(Matrix A00, Matrix B01, Matrix B11)
{

}

Matrix StrassenAlg::m4Compute(Matrix A11, Matrix B10, Matrix B00)
{


}

Matrix StrassenAlg::m5Compute(Matrix A00, Matrix A01, Matrix B11)
{

}

Matrix StrassenAlg::m6Compute(Matrix A10, Matrix A00, Matrix B00, Matrix B01)
{

}

Matrix StrassenAlg::m7Compute(Matrix A01, Matrix A11, Matrix B10, Matrix B11)
{

}

//Matrix StrassenAlg::Strassen()
//{
//
//}
