/*
Program: primes.cpp
Author: Roann Yanes
This program finds all prime numbers between 1 and 1,000.
 */
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{

int primes[1000]; // initializes the array
int counter = 0;

	for (int count = 0; count < 1000; count++) // sets all of the elements in the array to "true"
	{
		primes[count] = 1;
	}

	for (int i = 2; i < sqrt(1000); i++)
	{
		if (primes[i] == 1) // stores all of the values that are not changed to "false" in an array, as those are the prime numbers
		{
			for (int j = (i * 2); j < 1000; j += i)
			{
				primes[j] = 0; // sets the values that are not prime numbers to false
			}
		}
	}

	for (int k = 2; k < 1000; k++) // prints out the prime numbers
	{
		if (primes[k])
		{
			cout << setw(5) << k;
			counter++;
			if (counter % 10 == 0)
			{
				cout << endl;
			}
		}
	}
cout << endl;
return 0;
}
