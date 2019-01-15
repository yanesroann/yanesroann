/* Program: sudoku.h
 * Author: Roann Yanes
 * This program is the interface of the Sudoku class.
 */

#include <vector>
#include "cell.h"
#ifndef SUDOKU_H
#define SUDOKU_H
#include <iostream> 
using namespace std;

class Sudoku
{
  public:
    Sudoku(); // default constructor
    ~Sudoku(); // default deconstructor
    void elimination(); // implements single elimination
    void getBoard(); // displays the board to the user
    void setCells(); // sets the value of the cells
    void checkRow(); // implements singleton method
    void checkCol(); // implements singleton method
    bool checkFull(); // checks of there is no more zeros on the board
    Cell Board[9][9]; // 3D Array of Cells
};

#endif

