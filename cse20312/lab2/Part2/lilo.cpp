/* Program: lilo.cpp
 * Author: Roann Yanes
 * This is the class implementation for the lilo derived class.
 */

#include <iostream>
#include <string>
#include "disneymovie.h" // includes header file for base class
#include "lilo.h"

using namespace std;

Lilo::Lilo() : Guardian("Nani"), Antagonist("Dr. Jumba Jookiba"), Phrase("Ohana means family."), SideKick("Stitch"), Disneymovie("Lilo And Stitch", "Lilo") // uses inheritance for data in base class

{ 
  Guardian = "Nani"; // sets all of the private values
  Antagonist = "Dr. Jumba Jookiba (at first)";
  Phrase = "Ohana means family.";
  SideKick = "Stitch";
}

void Lilo::print() // prints the attributes in a formatted manner
{ 
  cout << "------------------------------" << endl; // prints all of the private data
  cout << "Family Disney Movie Name: " << Name << endl;
  cout << "Family Disney Movie Character: " << Character << endl;
  cout << "Guardian: " << Guardian << endl;
  cout << "Antagonist: " << Antagonist << endl;
  cout << "Phrase: " << Phrase << endl;
  cout << "Side Kick: " << SideKick << endl;
}
