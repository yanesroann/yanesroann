/* Program: beautybeast.cpp
 * Author: Roann Yanes
 * This is the class implementation of the derived class for beautybeast.
 */

#include <iostream>
#include <string>
#include "disneymovie.h" // includes header file for base class
#include "beautybeast.h"

using namespace std;

Beautybeast::Beautybeast() : Prince("Adam"), Villain("Gaston"), DressColor("Yellow"), SideKick("Chip"), Disneymovie("Beauty And The Beast", "Belle") // uses inheritance for data in base class
{ 
  Prince = "Adam"; // sets all of the private values
  Villain = "Gaston";
  DressColor = "Yellow";
  SideKick = "Chip";
}

void Beautybeast::print() // prints the attributes in a formatted manner
{ 
  cout << "------------------------------" << endl; // prints all of the private data
  cout << "Princess Disney Movie Name: " << Name << endl;
  cout << "Princess Disney Movie Character: " << Character << endl;
  cout << "Villain: " << Villain << endl;
  cout << "Dress Color: " << DressColor << endl;
  cout << "Side Kick: " << SideKick << endl;
}
