/* Program: C4Board.h
 * Author: Roann Yanes
 * This is the class interface for the C4Board class.
 */
#include <iostream>
#ifndef C4BOARD_H
#define C4BOARD_H
#include "C4Col.h"
using namespace std;

class C4Board {
  public:
    C4Board(); // default constructor
    ~C4Board(); // deconstructor
    void display(); // returns the maximum number of discs
    void play(); // plays Connect 4 with two-players
    bool inBounds(int, int); // checks to see if "checkNeighbors" is in bounds 
  private:
    int checkNeighbors(char); // checks the board in various locations to see if there is a winner
    int numColumns; // stores the number of columns
    C4Col * Board; // creates an object of the C4Col class
};

#endif
