/*
Program: ndfootball.cpp
Author: Roann Yanes
This program will store the wins and losses data into arrays and will then 
provide a user with a menu of questions on the data. 
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int wins[] =
 { 6, 8, 6, 8, 5, 5, 6, 6, 8, 7, 4,
   6, 7, 7, 6, 7, 8, 6, 3, 9, 9, 10,
   8, 9, 10, 7, 9, 7, 5, 9, 10, 6, 6,
   3, 6, 7, 6, 6, 8, 7, 7, 8, 7, 9,
   8, 7, 8, 9, 9, 10, 4, 7, 7, 9, 9,
   8, 2, 7, 6, 5, 2, 5, 5, 2, 9, 7,
   9, 8, 7, 8, 10, 8, 8, 11, 10, 8, 9,
   11, 9, 7, 9, 5, 6, 7, 7, 5, 5, 8,
   12, 12, 9, 10, 10, 11, 6, 9, 8, 7, 9,
   5, 9, 5, 10, 5, 6, 9, 10, 3, 7, 6,
   8, 8, 12, 9, 8, 10 };

int losses[] = 
 { 3, 1, 2, 0, 3, 4, 1, 0, 1, 0, 1,
   0, 0, 0, 2, 1, 1, 1, 1, 0, 0, 1,
   1, 1, 0, 2, 1, 1, 4, 0, 0, 2, 2,
   5, 3, 1, 2, 2, 1, 2, 2, 0, 2, 1,
   2, 2, 0, 0, 0, 0, 4, 2, 2, 0, 1,
   2, 8, 3, 4, 5, 8, 5, 5, 7, 1, 2,
   0, 2, 2, 2, 1, 2, 3, 0, 2, 3, 3,
   1, 3, 4, 2, 6, 4, 5, 5, 6, 6, 4,
   0, 1, 3, 3, 1, 1, 5, 3, 3, 6, 3,
   7, 3, 6, 3, 7, 6, 3, 3, 9, 6, 6,
   5, 5, 1, 4, 5, 3 };

void givenyear(int); // prototype
void lossesfunction(int); // prototype
void winsfunction(int); // prototype

int main()
{

int choice, winchoice, losseschoice, yearchoice, size, sizeint;


	cout << "What would you like to do?" << endl; // displays input message to user
	cout << "1: display the record for a given year" << endl;
	cout << "2: display the years with at least ""x"" losses" << endl;
	cout << "3: display the years with at least ""x"" wins" << endl;
	cout << "4: display all years with more wins than losses" << endl;
	cout << "5: display all years with more losses than wins" << endl;
	cout << "6: exit" << endl;
	cout << "Enter your choice: ";
	cin >> choice;

	size = sizeof(wins)/sizeof(sizeint); //finds size of wins and losses arrays

	if (choice < 1 && choice > 6)
	{
	  cout << "Error: Invalid Input!" <<endl;
	  return 0;
	}

	while (choice != 6)
	{
	  if (choice == 1) // prompts the user for the year and displays the years
	  {
	    cout << "Enter the year: ";
	    cin >> yearchoice;
	    if (yearchoice < 1900) // displays error for years less than 1900
	    {
	      cout << "Please enter a year between 1900 and 2015: ";
	      cin >> yearchoice;
	      givenyear(yearchoice);
	    }
	    else
	    {
	      givenyear(yearchoice);
	    }
	  }
	  else if (choice == 2) // prompts the user for the number of losses and displays the losses
	  {
	    cout << "Enter the minimum number of losses: ";
	    cin >> losseschoice;
	    if (losseschoice < 0) // displays error for negative numbers and asks for valid input
	    {
	      cout << "Please enter a valid number: ";
	      cin >> losseschoice;
	      lossesfunction(losseschoice);
	    }
	    else
	    {
	      lossesfunction(losseschoice);
	    }
	  }
	  else if (choice == 3) // prompts the user for the number of wins and displays the wins
	  {
	    cout << "Enter minimum number of wins: ";
	    cin >> winchoice;
	    if (winchoice < 0) //displays error for negative numbers and asks for valid input
	    {
	      cout << "Please enter a valid number: ";
	      cin >> winchoice;
	      winsfunction(winchoice);
	    }
	    else
	    {
	      winsfunction(winchoice);
	    }
	  }
 	  else if (choice == 4) // displays the years with a winning record
	  {
	    cout << "Years with more wins than losses:" << endl;
	    for (int j = 0; j <= size; j++)
	    {
	      if (wins[j] > losses[j])
	      {
	        cout << (j + 1900) << endl;
	      }
	    }
	  }
	  else if (choice == 5) // displays the years with a losing record
	  {
        cout << "Years with more losses than wins:" << endl;
	    for (int j = 0; j <= size; j++)
	    {
	      if (losses[j] > wins[j])
	      {
	        cout << (j + 1900) << endl;
	      }
	    }
	  }
	  else // exits the program
	  {
	    return 0;
	  }
	  cout << "What would you like to do?" << endl; // displays input message to user again
	  cout << "1: display the record for a given year" << endl;
	  cout << "2: display the years with at least ""x"" losses" << endl;
	  cout << "3: display the years with at least ""x"" wins" << endl;
	  cout << "4: display all the years with more wins than losses" << endl;
	  cout << "5: display all the years with more losses than wins" << endl;
	  cout << "6: exit" << endl;
	  cout << "Enter your choice: ";
	  cin >> choice;
	}
	cout << "Bye!" << endl;
	return 0;
}

void givenyear(int yearchoice) // function for option 1 (record for a given year)
{
	cout << "Wins: " << wins[yearchoice-1900] << endl;
	cout << "Losses: " << losses[yearchoice-1900] << endl;
}

void lossesfunction(int losseschoice) // function for option 2 (years with "x" losses)
{
	int sizeint;
	int size = sizeof(wins)/sizeof(sizeint);
	cout << "Years with at least " << losseschoice << " losses:" << endl;
	for (int k = 0; k <= size; k++)
	{
	  if (losses[k] >= losseschoice)
	 {
	    cout << (k + 1900) << endl;
	 }
	}
}

void winsfunction(int winchoice) // function for option 3 (years with "x" wins)
{
	int sizeint;
	int size = sizeof(wins)/sizeof(sizeint);
	cout << "Years with at least " << winchoice << " wins:" << endl;
	for (int k = 0; k <= size; k++)
	{
	  if (wins[k] >= winchoice)
	  {
	    cout << (k + 1900) << endl;
	  }
	}
}
