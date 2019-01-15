/* Program: polarmain.cpp
 * Author: Roann Yanes
 */

#include <iostream> // enables program to output data to the screen
#include <cmath>
#include <iomanip>
#include "polarfn.h"
using namespace std;

// function main begins program execution

int main()
{
	float x, y, r, theta, q; // initialization of variables

	cout << "Please enter the x and y coordinates: "; // prompts user for data and stores the values from the user in "x" and "y"
	cin >> x >> y;

	r =  polarradius(x,y); // execution of function
	theta = polarangle(x,y); // execution of function 
	q = quadrant(x, y); // execution of function

	cout << "The point's corresponding polar coordinates are: " << "(" << r << ", " << theta << ")" << endl; // displays the polar coordinates to the user

	// Beginning of if statements to show where the point is

	if (q==1)
	{
		cout << "The point lies in the first quadrant." << endl;
	}
	else if (q==2)
	{
		cout << "The point lies in the second quadrant." << endl;
	}
	else if (q==3)
	{
		cout << "The point lies in the third quadrant." << endl;
	}
	else if (q==4)
	{
		cout << "The point lies in the fourth quadrant." << endl;
	}
	else if (q==5)
	{
		cout << "The point is at the origin." << endl;
	}
	else if (q==6)
	{
		cout << "The point lies on the x-axis." << endl;
	}
	else 
	{
		cout << "The point lies on the y-axis." << endl;
	}

	return 0;
}
