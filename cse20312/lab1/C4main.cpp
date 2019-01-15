/* Program: main.cpp
 * Author: Roann Yanes
 * This program is the driver for C4Col and C4Board; it also allows the user to play Connect 4 with another user or the computer.
 */

#include <iostream>
#include "C4Col.h"
#include "C4Board.h" // class definition for C4Board used below
using namespace std;

int main() 
{ 
  C4Board C4; // instantiate an instance of C4Board
  C4.play(); // play game!!
  return 0;
}
