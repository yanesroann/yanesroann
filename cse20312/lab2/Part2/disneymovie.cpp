/* Program: disneymovie.cpp
 * Author: Roann Yanes
 * This is the class implementation for the disneymovie base class.
 */

#include "disneymovie.h"
#include <iostream>

using namespace std;

Disneymovie::Disneymovie(string NameVal, string CharVal) // constructor for disneymovie class
{
  Name = NameVal;
  Character = CharVal;
}

void Disneymovie::print() // simple print function
{
  cout << "Disney Movie Name: " << Name << endl;
  cout << "Disney Movie Protagonist: " << Character << endl << endl;
}

void Disneymovie::setName(const string val) // set the disneymovie name
{
  Name = val;
}
void Disneymovie::setCharacter(const string val) // set the disneymovie character
{
  Character = val;
}

string Disneymovie::getName() // get the disneymovie name
{
  return (Name); // accessor function
}

string Disneymovie::getCharacter() // get the dineymovie character
{
  return (Character); // accessor function
}

