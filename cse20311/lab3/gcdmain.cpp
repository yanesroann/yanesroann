/* Program: gcdmain.cpp
Author: Roann Yanes
This program asks the user to input two integer numbers and finds and displays
the greatest common divisor between them. */

#include <iostream> // enables program to output data to the screen
#include <stdio.h>
using namespace std;

int getgcd(int, int); // prototype

// function main begins program execution

int main() 
{
	int a, b, c; // initialization of variables

	cout << "Please enter two integers: "; // prompts user for data and stores the integers from user into "a" and "b"
	cin >> a >> b;

	c = getgcd(a,b); // execution of function

	cout << "The greatest common divisor is: " << c << endl; // displays the GCD to the user and the function returns a value that gets assigned to "c"
	return 0;
}

	// Begin creation of getgcd() function in order for it to be used in the program

	int getgcd(int a, int b) // Euclid's algorithm for GCD 
	{
		int c;
			while (a != 0)
			{
				c = a;
				a = b%a;
				b = c;
			}
		return b;
	}

// end of program
