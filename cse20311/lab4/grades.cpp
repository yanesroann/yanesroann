/* Program: grades.cpp
Author: Roann Yanes
This program reads grade values from a data file into an array, and then computes their average and standard deviation.
*/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;


int main()
{
   int grades[50];
   int sum = 0;
   int value, size = 0;
   float average, stddev, subandsquare = 0;
   
   cin >> value;

	while(value != -1) // obtains the grades from the data file until the sentinel value is read
	{
	  grades[size] = value;
	  size++;
	  cin >> value;
	}

	for (int j=0; j < size; j++) // stores the values in an array called "grades"
	{
	  cout << grades[j] << endl;
	}

	for (int k=0; k < size; k++) // sums all of the elements in the array
	{
	  sum += grades[k];	
	}
        average = sum /(float)size;

	for (int m=0; m < size; m++) // standard deviation calculation 
	{
	  subandsquare += pow((grades[m] - average),2); // calculation under tha square
	}
	stddev = sqrt(subandsquare/size);

   cout << fixed << setprecision(4) << "The average of the grades is: " << average << endl;
   cout << fixed << setprecision(4) << "The standard deviation of the grades is: " << stddev << endl; 

   return 0;
}
