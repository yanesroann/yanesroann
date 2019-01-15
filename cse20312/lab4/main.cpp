/* Program: main.cpp
 * Author: Roann Yanes
 * This is a driver that tests the Sudoku class, which is a sudoku puzzle solver.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "cell.h"
using namespace std;
#include "sudoku.h"


int main()
{
  bool full = false;
  Sudoku sudo; // calls instantiation of the Sudoku class
  sudo.getBoard(); // displays board the user input
  cout << endl;
  while(full == sudo.checkFull()) // runs the proper algorithms
  {
    sudo.elimination(); // implements the elimination algorithm
    //sudo.setRow(); // supposed to implement singleton algorithm
    //sudo.setCol(); // supposed to implement singleton algorithm
    sudo.setCells();
  }
  sudo.getBoard(); // displays the solution to the user
}

