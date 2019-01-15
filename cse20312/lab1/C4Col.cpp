/* Program: C4Col.cpp
 * Author: Roann Yanes
 * This is the class implementation for the C4Col class. 
 */

#include <iostream>
#include "C4Col.h"
using namespace std;

C4Col::C4Col() // default constructor
{ 
  maxDiscs = 6; 
  numDiscs = 0;
  Discs = new char[maxDiscs]; 
  for (int i = 0; i <= maxDiscs; i++)
  {
    Discs[i] = ' '; 
  }
}

C4Col::C4Col(const C4Col &copy) : maxDiscs(copy.maxDiscs) // copy constructor
{
  Discs = new char[maxDiscs]; // create space for pointer-based array
  for ( int i = 0; i <= maxDiscs; i++ )
  {
    Discs[maxDiscs] = copy.Discs[i]; // copy into object 
  }
}

C4Col::~C4Col() // deconstructor
{ delete [] Discs; }

int C4Col::isFull() // checks to see if the column is full
{
  if (numDiscs == maxDiscs) { return 1; }
  else { return 0; }
}

int C4Col::getMaxDiscs() // returns the maximum number of discs that can fit in a column
{ return maxDiscs; }

char C4Col::getDisc(int disc) // returns the character that is at the location specified
{
  if (disc < 0 || disc > 6) { cout << "The parameter given is invalid." << endl; } // error message if invalid input
  else { return Discs[disc]; } 
}
 
void C4Col::addDisc(char newDisc) // adds a new disc to the board
{
  if (isFull() == 1) { cout << "The column is full!" << endl; } // checks to see if the column is full before adding
  else Discs[numDiscs++] = newDisc; // adds the new disc in the next available space in the column
}
