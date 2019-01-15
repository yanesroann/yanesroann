// This program will display two solutions (factors/solutions) of a quadratic equation (ax^2 + bx + c) using the quadratic formula.

#include <iostream>
#include <cmath>
using namespace std;

// function main begins program execution
int main() {

// declaring and initializing variables 
float a = 0;
float b = 0;
float c = 0;
float root1 = 0;
float root2 = 0;
float square = 0;
float root = 0;

cout << "Enter the value of a: ";
cin >> a;

cout << "Enter the value of b: ";
cin >> b;

cout << "Enter the value of c: ";
cin >> c;

// Calculations and Quadratic Formula

square = pow(b,2);
root = square - (4*a*c); 
root1 = (-b + (sqrt(root))) / (2*a);
root2= (-b - (sqrt(root))) / (2*a);

cout << "One solution to the quadratic equation is: " << root1 << endl;
cout << "The other solution to the quadratic equation is: " << root2 << endl;

return 0;

}
