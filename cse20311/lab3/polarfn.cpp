/* Program: polarfn.cpp
Author: Roann Yanes
*/

#include <iostream> // enables program to output data to the screen
#include <cmath>
#include <iomanip>
using namespace std;


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
