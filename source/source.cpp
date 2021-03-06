//Strassen Algorithm Implementation
//CS473 Final Project
//Authors: Kostiantyn Makrasnov & Timothy Bruggeman
//Main program driver - contains the majority of operations
//References:
//1) https://www.geeksforgeeks.org/measure-execution-time-function-cpp/ (timing technique)

#include <iostream>     //cout, cin, endl
#include <ctype.h>      //isdigit
#include <random>
#include <time.h>
#include <string>       //string
#include <limits>       //numeric_limits
#include <chrono>		//used for timing the function runtime
#include "StrassenAlg.h"

using namespace std;

///[UTILITY]
//isInt: finds if given string is an integer
//@param num - string that is checked to be a number or not
//@return - TRUE if an integer, FALSE if not
bool isInt(string num)
{
	//Check for an empty string
	if (num == "")
		return false;

	//Determine start( if negative starts checking form second charecter)
	int startCheck = 0;
	if (num[0] == '-' && num.length() != 1)
		startCheck = 1;

	//Checks every char to be an integer
	for (int i = startCheck; i < num.length(); i++)
	{
		if (!isdigit(num[i]))
			return false;
	}

	return true;
}

//[USER INPUT]
//getNumberInRange: asks user for number until (-1) or within range
int getNumberInRange(string initMsg, string resetMsg, int start, int end)
{
	//Initial message
	cout << initMsg;

	//Repeated attempts to get number in range
	bool isValid = false;
	string choice = "-1";
	while (!isValid)
	{
		isValid = true;
		cin >> choice;

		if (!isInt(choice) || stoi(choice) < start || stoi(choice) > end)
		{
			isValid = false;
			cout << resetMsg;
		}
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return stoi(choice);
}

//enterMenu: allows user to select which typ of matrix multipleciation needs to be done
//return - choice in the main menu (# only)
int enterMenu()
{
	cout << "Main Menu:" << endl;
	cout << "1. Generate random matrices" << endl;
	cout << "2. Input matrices manually" << endl;
	cout << "3. Exit" << endl;

	return getNumberInRange("Please select an option (1 to 3): ", "Invalid Input! Please enter a number 1, 2 or 3: ", 1, 3);
}

//findBounds: allows user to enter the dimensions of the matricies that are going to used
void findBounds(int& r1, int& c1, int& r2, int& c2)
{
	int dimension = getNumberInRange("Please enter the dimension of the two square matrices (4 to 256): ",
		"Invalid Input! Enter a value from 4 to 256: ", 4, 256);

	cout << endl;

	r1 = dimension;
	c1 = dimension;
	r2 = dimension;
	c2 = dimension;

	/*r1 = getNumberInRange("Please enter the amount of ROWS in the FIRST matrix (4 to 256): ",
		"Invalid Input! Enter a value from 4 to 256: ", 4, 256);
	c1 = getNumberInRange("Please enter the amount of COLUMNS in the FIRST matrix (4 to 256): ",
		"Invalid Input! Enter a value from 4 to 256: ", 4, 256);
	r2 = getNumberInRange("Please enter the amount of ROWS in the SECOND matrix (4 to 256): ",
		"Invalid Input! Enter a value from 4 to 256: ", 4, 256);
	c2 = getNumberInRange("Please enter the amount of COLUMNS in the SECOND matrix (4 to 256): ",
		"Invalid Input! Enter a value from 4 to 256: ", 4, 256);*/
}


///[MAIN]
//Main Driver for the program allows 
int main()
{
	srand(time(NULL));

	int lastMenuChoice = enterMenu();
	while (lastMenuChoice != 3)
	{
		//Find Matrix Dimensions
		int r1, c1, r2, c2;
		findBounds(r1, c1, r2, c2);

		//Find the Largest Dimension (left here for future development)
		int max1 = max(r1, c1);
		int max2 = max(r2, c2);
		int maxFinal = max(max1, max2);

		//Setup initial matrix values
		Matrix matrix1(r1, c1, maxFinal);
		Matrix matrix2(r2, c2, maxFinal);

		if (lastMenuChoice == 1)
		{
			cout << "Generating random [" << r1 << "X" << c1 << "] and [" << r2 << "X" << c2 << "] matricies!" << endl;

			//Generate Random Matricies
			matrix1.generateRandomMatrix(rand());
			matrix2.generateRandomMatrix(rand());

			//Print Random Matrices (if small enough)
			if(maxFinal <= 16)
			{
				matrix1.printMatrix("Matrix 1:");
				matrix2.printMatrix("Matrix 2:");
			}
		}
		else
		{
			cout << "Reading a [" << r1 << "X" << c1 << "] and [" << r2 << "X" << c2 << "] matrix!" << endl;
			matrix1.readNewMatrix("A");
			matrix2.readNewMatrix("B");
			matrix1.printMatrix("Matrix 1:");
			matrix2.printMatrix("Matrix 2:");
		}

		//Tests
		/*Matrix portionMatrix(0, 0, 2, 2, matrix1.rawMatrix);
		portionMatrix.printMatrix("Portion Matrix:");
		Matrix portionMatrix2(1, 1, 2, 2, matrix1.rawMatrix);
		portionMatrix2.printMatrix("Portion2 Matrix:");
		portionMatrix.AddToCurrent(portionMatrix2);
		portionMatrix.printMatrix("Added Matrix:");
		portionMatrix2.printMatrix("Portion2 Matrix:");
		portionMatrix.SubtractFromCurrent(portionMatrix2);
		portionMatrix.printMatrix("Subtracted Matrix:");*/

		//Apply Highschool 
		Matrix bfMult(matrix1.rows, matrix2.columns, maxFinal);
		bfMult.createEmptyMatrix();

		using namespace std::chrono;

		auto startHS = high_resolution_clock::now();
		matrix1.bruteForceMult(matrix2, bfMult);
		auto stopHS = high_resolution_clock::now();

		//Apply Strassen
		Matrix strassenMult(matrix1.rows, matrix2.columns, maxFinal);
		strassenMult.createEmptyMatrix();

		auto startStrassen = high_resolution_clock::now();
		StrassenAlg::strassenLanding(matrix1, matrix2, strassenMult);
		auto stopStrassen = high_resolution_clock::now();

		//Print Final Results
		// - Multiplication Results (if size less than 16)
		if(maxFinal <= 16)
		{
			bfMult.printMatrix("Results of Highschool Multiplication: ");
			strassenMult.printMatrix("Multiplied Strassen Matrix: ");
		}
		// - Timing Results
		auto durationHS = duration_cast<milliseconds>(stopHS - startHS); 
		auto durationStrassen = duration_cast<milliseconds>(stopStrassen - startStrassen);
		cout << "Highschool Multiplication took - " << durationHS.count() << " milli sec" << endl;
		cout << "Strassen Multiplication took - " << durationStrassen.count() << " milli sec" << endl;
		cout << endl;

		lastMenuChoice = enterMenu();
	}


	cout << "Thank You for using the Strassen Multiplier!" << endl;
	return 0;
}
