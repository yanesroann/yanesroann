/* Program: polar.cpp
Author: Roann Yanes
This program prompts the user for the x and y coordinates for a point in a 
Cartesian coordinate system, and then finds and displays the point's 
corresponding polar coordinates and the quadrant that the point is in; or the
axis it is on; or the origin. */

#include <iostream> // enables program to output data to the screen
#include <cmath>
#include <iomanip>
using namespace std;

float polarradius(float, float); // prototype
float polarangle(float, float); // prototype
int quadrant(float, float); // prototype

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
	// Begin creation of polarradius() function

	float polarradius(float x, float y)
	{
		float r;
		r = pow(x, 2) + pow(y, 2);
		r = sqrt(r);
		return r; 
	}

	// Begin creation of polarangle() function

	float polarangle(float x, float y) //returns theta in radians
	{
		float theta;
		theta = atan2(y, x);
		return theta;
	}

	// Begin creation of quadrant() function

	int quadrant(float x, float y)
	{
		int q; // "q" will be assigned a number associated to an axis, quadrant, or the origin

		if (x>0 && y>0) // quadrant one
		{
			q = 1;
		}
		else if (x<0 && y>0) // quadrant two
		{
			q = 2;
		}
		else if (x<0 && y<0) // quadrant three
		{
			q = 3;
		}
		else if (x>0 && y<0) // quadrant four
		{
			q = 4;
		}
		else if (x==0 && y==0) // origin
		{
			q = 5;
		}
		else if (y == 0) // x-axis
		{
			q = 6;
		}
		else // y-axis
		{
			q = 7;
		}

	return q;

	}

// end of program
