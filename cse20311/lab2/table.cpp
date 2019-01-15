/* Asks the user for the size of the table on the X and Y axes, then displays a
 exactly that big */
 
#include <iostream>
#include <iomanip>
using namespace std;

//function main begins program execution
int main() {

// declare and initialize variables
	int x=0;
	int y=0;
	int i=0;
	int j=0;
	
	cout << "Enter the size of the matrix (x-value): ";
	cin >> x;

	cout << "Enter the size of the matrix (y-value): ";
	cin >> y;

// begin integer multiplication table

	for (i=0; i<y+1; i++) {
		for (j=0; j<x+1; j++) {
			if ((i==0) && (j==0)) {
			cout << setw(4) << "*" << setw(4);
			}
			else if (i==0) { 
			cout << j << setw(4);
			}
			else if (j==0) {
			cout << i << setw(4);
			}
			else {
			cout << j*i << setw(4);
			}
		}
	cout <<endl;
	}
}


