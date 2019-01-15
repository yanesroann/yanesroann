/* Program: menucalc.cpp
Author: Roann Yanes
This program acts as a text menu driven basic calculator for addition,
subtraction, multiplication, and division.*/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

float addition(float, float);
float subtraction(float, float);
float multiplication(float, float);
float division(float, float);

int main()
{
int choice;
	float num1, num2, sum, difference, product, quotient;

	cout << "What would you like to do?" << endl; // display input message to user
	cout << "	" << "1 for addition" << endl;
	cout << "	" << "2 for subtraction" << endl;
	cout << "	" << "3 for multiplication" << endl;
	cout << "	" << "4 for division" << endl;
	cout << "	" << "5 to exit" << endl;
	cout << "Enter your choice: ";
	cin >> choice;

	if (choice != 5)
	{
		cout << "Enter two numbers: ";
		cin >> num1 >> num2;
		cout << setprecision(6) << fixed;
		cout << "Inputs: " << num1 << ", " << num2 << endl;
	}

	while (choice != 5) // loops until sentinel value is read from user
	{
		if (choice == 1) // addition function
		{
			sum = addition(num1, num2); // execution of function
			cout << setprecision(6) << fixed;
			cout << "(" << num1 << ")" << " + " << "(" << num2 << ")" << " = " << sum << endl; 

			cout << "What would you like to do?" << endl; // display input message to user
			cout << "	" << "1 for addition" << endl;
			cout << "	" << "2 for subtraction" << endl;
			cout << "	" << "3 for multiplication" << endl;
			cout << "	" << "4 for division" << endl;
			cout << "	" << "5 to exit" << endl;
			cout << "Enter your choice: ";
			cin >> choice;

			if (choice != 5)
			{
				cout << "Enter two numbers: ";
				cin >> num1 >> num2;
				cout << setprecision(6) << fixed;
				cout << "Inputs: " << num1 << ", " << num2 << endl;
			}

		}
		else if (choice == 2) // subtraction
		{
			difference = subtraction(num1, num2); // execution of function
			cout << setprecision(6) << fixed;
			cout << "(" << num1 << ")" << " - " << "(" << num2 << ")" << " = " << difference << endl; 

			cout << "What would you like to do?" << endl; // display input message to user
			cout << "	" << "1 for addition" << endl;
			cout << "	" << "2 for subtraction" << endl;
			cout << "	" << "3 for multiplication" << endl;
			cout << "	" << "4 for division" << endl;
			cout << "	" << "5 to exit" << endl;
			cout << "Enter your choice: ";
			cin >> choice;

			if (choice != 5)
			{
				cout << "Enter two numbers: ";
				cin >> num1 >> num2;
				cout << setprecision(6) << fixed;
				cout << "Inputs: " << num1 << ", " << num2 << endl;
			}

		}
		else if (choice == 3) // multiplication
		{
			product = multiplication(num1, num2); // execution of function
			cout << setprecision(6) << fixed;
			cout << "(" << num1 << ")" << " * " << "(" << num2 << ")" << " = " << product << endl; 

			cout << "What would you like to do?" << endl; // display input message to user
			cout << "	" << "1 for addition" << endl;
			cout << "	" << "2 for subtraction" << endl;
			cout << "	" << "3 for multiplication" << endl;
			cout << "	" << "4 for division" << endl;
			cout << "	" << "5 to exit" << endl;
			cout << "Enter your choice: ";
			cin >> choice;

			if (choice != 5)
			{
				cout << "Enter two numbers: ";
				cin >> num1 >> num2;
				cout << setprecision(6) << fixed;
				cout << "Inputs: " << num1 << ", " << num2 << endl;
			}

		}
		else // division
		{
			quotient = division(num1, num2); // execution of function
			cout << setprecision(6) << fixed;

			if (num2 != 0)
			{
				cout << "(" << num1 << ")" << " / " << "(" << num2 << ")" << " = " << quotient << endl;
			}

			cout << "What would you like to do?" << endl; // display input message to user
			cout << "	" << "1 for addition" << endl;
			cout << "	" << "2 for subtraction" << endl;
			cout << "	" << "3 for multiplication" << endl;
			cout << "	" << "4 for division" << endl;
			cout << "	" << "5 to exit" << endl;
			cout << "Enter your choice: ";
			cin >> choice;

			if (choice != 5)
			{
				cout << "Enter two numbers: ";
				cin >> num1 >> num2;
				cout << setprecision(6) << fixed;
				cout << "Inputs: " << num1 << ", " << num2 << endl;
			}
		}
	}

cout << "Thank you!" << endl; 
return 0;
}

	// Begin creation of addition() function

	float addition(float num1, float num2)
	{
		float sum;
		sum = num1 + num2;
		return sum;
	}

	// Begin creation of subtraction() function

	float subtraction(float num1, float num2)
	{
		float difference;
		difference = num1 - num2;
		return difference;
	}

	// Begin creation of multiplication() function

	float multiplication(float num1, float num2)
	{
		float product;
		product = num1 * num2;
		return product;
	}

	// Begin creation of division() function

	float division(float num1, float num2)
	{
		float quotient;
		if (num2 == 0)
		{
			cout << "Cannot divide by zero!" << endl;
		}
		else
		{
			quotient = num1 / num2;
		}
		return quotient;
	}

// end program
