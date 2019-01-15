/* Program: cell.h
 * Author: Roann Yanes
 * This is the interface for the Cell class.
 */

#ifndef CELL_H
#define CELL_H

class Cell
{
  public:
    int cellContent; // the value of the cell
    int Possible[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9}; // stores the possibilities for each cell
};

#endif
