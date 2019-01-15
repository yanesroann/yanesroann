/* This program generates a ASCII Art graph of the mathematical 
function (6*(sin(2x) + cos(x)+2)) */

#include <iostream>
#include <math.h>
#include <iomanip> 
using namespace std;

// Begin main function 

int main() {

// Declare and initialize variables

float x;
float y;
float xmin;
float xmax;
float ymin;
float ymax;
int j;
int k;
int yrounded;

// Display messages

cout << "A plot of y=(sin(2x)+cos(x)) from x=0 to 20." << endl;
cout << setw(5) << "X" << setw(6) << "Y" << endl;

// Start graphing function

	ymin = (6*(sin(2*0) + cos(0)+2));
	for (j=0; j<=100; j++) {
		x = j * 0.20;
		y = (6*(sin(2*x) + cos(x)+2));
		yrounded = floor (y + 0.5);
		cout << fixed << setprecision(2) << setw(6) << x << setw(7) << y << setw(3);
		for (k=0; k<=yrounded; k++) {
			cout << "#";
			}
			cout << endl;
			if (y>ymax) {
				ymax = y;
				xmax = x;
			}
			if (y<ymin){
				ymin = y;
				xmin = x;
			}
}
cout << "The maximum of " << ymax << " was at x = " << xmax << endl;
cout << "The minimum of " << ymin << " was at x = " << xmin << endl; 
}

