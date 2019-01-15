/* Program: lifeboard.cpp
 * Author: Roann Yanes
 * This is the class implementation for Lifeboard.
 */

#include <iostream>
using namespace std;
#include "lifeboard.h"   // need to include the class interface (prototype)
#define SIZE1 40
#define SIZE2 40

Lifeboard::Lifeboard() // default constructor
{
  currentboard[SIZE1][SIZE2];
  for (int i = 0; i < SIZE1; i++) 
  {
    for (int j = 0; j < SIZE2; j++) 
    {
      currentboard[i][j] = ' '; // creates a 40x40 of blanks
    }
  } 
}

Lifeboard::Lifeboard(int x, int y) // if size of board is changed
{ 
  row = x; 
  col = y;
  currentboard[row][col];
  for (int i = 0; i < row; i++) 
  {
    for (int j = 0; j < col; j++) 
    {
      currentboard[i][j] = ' ';
    }
  } 
}

Lifeboard::~Lifeboard() // destructor
{ }  // nothing to be done (yet)

void Lifeboard::displayBoard() // method to display formatted board
{
  cout << " ";
  for (int k = 0; k < SIZE1; k++)
  {
    cout << "-"; // top boundary
  }
  cout << " " << endl;
    for (int i = 0; i < SIZE1; i++) 
    {
      cout << "|"; // left boundary
      for (int j = 0; j < SIZE1; j++) 
      {
        cout << currentboard[i][j];
      }
      cout << "|" << endl;  // right boundary
    }
    cout << " ";
    for (int m = 0; m < SIZE1; m++)
    {
      cout << "-"; // bottom boundary
    }
  cout << endl;
}

void Lifeboard::addCell(int x, int y) // method to add a new cell at certain spot on the board
{
  currentboard[x][y] = 'X';
}

void Lifeboard::removeCell(int x, int y) // method to remove a cell at a certain spot on the board
{
  currentboard[x][y] = ' '; 
}

void Lifeboard::advance() // method to advance to next iteration
{
  tempboard[SIZE1][SIZE2];
  for (int i = 0; i < SIZE1; i++) 
  {
    for (int j = 0; j < SIZE2; j++) 
    {
      tempboard[i][j] = currentboard[i][j]; // assign temporary board to current board
    }
  } 
  for (int i = 0; i < SIZE1; i++)
  {
    for (int j = 0; j < SIZE1; j++) // checks the neighbors of the live cell at all eight possible locations to see if there is a live cell or dead cell surrounding it
    {
      int liveNeighbors = 0;
      if (tempboard[i-1][j-1] == 'X' && checkBoard(i-1, j-1))
      {
        liveNeighbors++;
      } 
      if (tempboard[i-1][j] == 'X' && checkBoard(i-1, j))
      {
        liveNeighbors++;
      }
      if (tempboard[i-1][j+1] == 'X' && checkBoard(i-1, j+1))
      {
        liveNeighbors++;
      }
      if (tempboard[i][j-1] == 'X' && checkBoard(i, j-1))
      {
        liveNeighbors++;
      }
      if (tempboard[i][j+1] == 'X' && checkBoard(i, j+1))
      {
        liveNeighbors++;
      }
      if (tempboard[i+1][j-1] == 'X' && checkBoard(i+1, j-1))
      {
        liveNeighbors++;
      }
      if (tempboard[i+1][j] == 'X' && checkBoard(i+1, j))
      {
        liveNeighbors++;
      }
      if (tempboard[i+1][j+1] == 'X' && checkBoard(i+1, j+1))
      {
        liveNeighbors++;
      }
      if (liveNeighbors < 2 || liveNeighbors > 3) // death of cell with fewer than two live neighbours or more than three live neighbours
      {
        currentboard[i][j] = ' ';
      }
      if (liveNeighbors == 2) // any live cell with two or three live neighbours lives on to the next generation
      {
        currentboard[i][j] = tempboard[i][j];
      }
      if (liveNeighbors == 3) // any dead cell with exactly three live neighbours becomes a live cell
      {
        currentboard[i][j] = 'X';
      }
    }
  }  
}

bool Lifeboard::checkBoard(int x, int y) // method to check the bounds of board
{
  bool on = false;
  if ( x >= 0 && x < SIZE1 && y >= 0 && y < SIZE1)
  {
    on = true; 
  }
  return on;
}
