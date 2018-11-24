//Strassen Algorithm Implementation
//CS473 Final Project
//Authors: Kostiantyn Makrasnov & Timothy Bruggeman
//Main program driver - contains the majority of operations

#include <iostream>     //cout, cin, endl
#include <ctype.h>      //isdigit
#include <string>       //string
#include <limits>       //numeric_limits

using namespace std;

///[UTILITY]
//isInt: finds if given string is an integer
//@param num - string that is checked to be a number or not
//@return - TRUE if an integer, FALSE if not
bool isInt(string num)
{
    //Check for an empty string
    if(num == "")
        return false;

    //Determine start( if negative starts checking form second charecter)
    int startCheck = 0;
    if(num[0] == '-' && num.length() != 1)
        startCheck = 1;

    //Checks every char to be an integer
    for(int i = startCheck; i < num.length(); i++)
    {
        if(!isdigit(num[i]))
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
    while(!isValid)
    {
        isValid = true;
        cin >> choice;

        if(!isInt(choice) || stoi(choice) < start || stoi(choice) > end)
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
    r1 = getNumberInRange("Please enter the amount of ROWS in the FIRST matrix (4 to 256): ", 
                          "Invalid Input! Enter a value from 4 to 256: ", 4, 256);
    c1 = getNumberInRange("Please enter the amount of COLUMNS in the FIRST matrix (4 to 256): ", 
                          "Invalid Input! Enter a value from 4 to 256: ", 4, 256);
    r2 = getNumberInRange("Please enter the amount of ROWS in the SECOND matrix (4 to 256): ", 
                          "Invalid Input! Enter a value from 4 to 256: ", 4, 256);
    c2 = getNumberInRange("Please enter the amount of COLUMNS in the SECOND matrix (4 to 256): ", 
                          "Invalid Input! Enter a value from 4 to 256: ", 4, 256);
}


///[MAIN]
int main()
{
    int lastMenuChoice = enterMenu();
    while(lastMenuChoice != 3)
    {
        int r1, c1, r2, c2;
        findBounds(r1, c1, r2, c2);



        if(c1 != r2)
        {
            cout << "Cannot multiply [" << r1 << "X" << c1 << "] by [" << r2 << "X" << c2 << "]!" << endl << endl;
            lastMenuChoice = enterMenu();
            continue;
        }

        if(lastMenuChoice == 1)
        {   
            cout << "Generating random [" << r1 << "X" << c1 << "] and [" << r2 << "X" << c2 << "] matricies!" << endl;
        }
        else
        {
        }

        lastMenuChoice = enterMenu();
    }


    cout << "Thank You for using the Strassen Multiplier!" << endl;
    return 0;
}