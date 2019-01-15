/* Program: CardDeck.h
 * Author: Roann Yanes
 * This is the class interface for the CardDeck class. 
 */
#include <iostream>
#ifndef CARDDECK_H
#define CARDDECK_H
using namespace std;

class CardDeck 
{
  friend ostream &operator<<( ostream &, const CardDeck & ); // overloads the output operator
  public:
    CardDeck(int = 52); // non-default constructor
    ~CardDeck(); // deconstructor
    int getSize(); // returns the size of the current deck
    void shuffle(); // performs a shuffle using Knuth's algorithm
  private:
    int deckSize; // stores the deck size
    int * Deck; // creates a deck
};

#endif
