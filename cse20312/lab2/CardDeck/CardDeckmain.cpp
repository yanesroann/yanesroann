/* Program: CardDeckmain.cpp
 * Author: Roann Yanes
 * This program initializes an array of ten cards, and then prints the deck before and after a shuffle.
 */
#include "CardDeck.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
  srand((time(NULL))); // changes the random number seed for the shuffle
  CardDeck deck(10); // instantiates an instance of the CardDeck class
  cout << deck; // prints out the deck
  deck.shuffle(); // performs a shuffle
  cout << deck; // prints out the shuffled deck
  return 0;
}
