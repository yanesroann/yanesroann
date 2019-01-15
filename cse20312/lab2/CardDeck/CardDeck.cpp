/* Program: CardDeck.cpp
 * Author: Roann Yanes
 * This is the class implementation for the CardDeck class. 
 */

#include <iostream>
#include <cstdlib>
#include "CardDeck.h"
using namespace std;

CardDeck::CardDeck(int n) // non-default constructor
{
  deckSize = n; // sets the size of the deck
  Deck = new int[n]; // dynamic memory allocation 
  for (int i = 0; i <= n-1; i++)
  {
    Deck[i] = i; // initializes the deck in numerical order
  }
}

CardDeck::~CardDeck() // deconstructor
{ delete [] Deck; } // releases pointer

int CardDeck::getSize() // returns the size of the current deck
{ return deckSize; } // number of elements in the array

void CardDeck::shuffle() // performs a shuffle using Knuth's algorithm
{
  int j;
  for (int i = deckSize - 1; i > 0; i--) // Knuth's algorithm
  {
    j = rand() % i; // randomizes the deck
    int temp = Deck[i];
    Deck[i] = Deck[j];
    Deck[j] = temp;
  }
}

ostream &operator<<(ostream &output, const CardDeck &deck) // overloads the output operator
{
  output << deck.Deck[0];
  for (int i = 1; i < deck.deckSize; i++) 
  {
    output << ", " << deck.Deck[i]; // prints the deck with commas in-between
  }
  output << endl; // enables cout << x << y;
  return output;
}
