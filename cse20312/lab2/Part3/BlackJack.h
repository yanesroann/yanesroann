/* Program: BlackJack.h
 * Author: Roann Yanes
 * This is the class interface for the BlackJack class. 
 */

#include "CardDeck.h"
#include <iostream>
#ifndef BLACKJACK_H
#define BLACKJACK_H
using namespace std;

class BlackJack 
{
  public:
    BlackJack(); // default constructor
    ~BlackJack(); // deconstructor
    int deal(); // gets cards from the deck for the game
    void play(); // plays blackjack
  private:
    CardDeck *Cards; // creates an object of the CardDeck class
};

#endif
