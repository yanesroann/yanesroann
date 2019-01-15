/* Program: main.cpp
 * Author: Roann Yanes
 * This is a driver for the BlackJack class.
 */

#include <iostream>
#include <stdio.h> // necessary for "time" and "srand"
#include <time.h> // necessary for "time" and "srand" 
#include <stdlib.h>
#include "CardDeck.h"
#include "BlackJack.h" // class definition for BlackJack used below
using namespace std;

int main() 
{
  srand(time(NULL)); // makes the shuffle more random
  BlackJack game; // instantiate an instance of BlackJack
  game.play(); // play game!!
  return 0;
}
