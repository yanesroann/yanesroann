/* Program: C4Board.cpp
 * Author: Roann Yanes
 * The is the class implementation for the C4Board class.
 */
#include <stdio.h> // necessary for "time" and "srand"
#include <time.h> // necessary for "time" and "srand" 
#include <stdlib.h>     
#include <iostream>
#include "C4Board.h"
#include "C4Col.h"
using namespace std;

C4Board::C4Board() // default constructor
{ 
  numColumns = 7; 
  Board = new C4Col[8]; // create space for pointer-based array
}

C4Board::~C4Board() // deconstructor
{ delete [] Board; } // release pointer-based array space 

void C4Board::display() // displays the Connect4 Board
{
  for (int k = 1; k <= 7; k++) // prints out column numbers at the top of the board
  {
    cout << " " << k << " ";
  }
  cout << endl;
  for (int i = Board[0].getMaxDiscs()-1; i >= 0; i--) // prints out 6x7 array
  {
    for (int j = 0; j < numColumns+1; j++)
    { 
      cout << "|" << Board[j].getDisc(i) << " "; // prints out the board with the pieces (eventually)
    }
    cout << endl;
  }
}

bool C4Board::inBounds(int i, int j) // ensures that the "checkNeighbors" function does not check in locations that are non-existent
{
  if (j >= 0 && j <= Board[0].getMaxDiscs() && i >= 0 && i <= numColumns) // in the bounds of the board
  {
    return true;
  }
  else 
  {
    return false;
  }
}

int C4Board::checkNeighbors(char piece) // checks different locations to determine if there is a winner 
{
  int winner = 0;
  for (int i = 0; i < Board[0].getMaxDiscs(); i++) // checks the rows of the board
  {
    for (int j = 0; j < numColumns; j++) // checks the columns of the board
    {
      if (inBounds(i-1, j-1) && Board[j-1].getDisc(i-1) == piece) // checks for a win diagonally 
      {
        if ((inBounds(i-2, j-2) && Board[j-2].getDisc(i-2) == piece))
        {
          if ((inBounds(i-3, j-3) && Board[j-3].getDisc(i-3) == piece))
          {
            if ((inBounds(i-4, j-4) && Board[j-4].getDisc(i-4) == piece))
            {
              winner = 1;
            }    
          }    
        }    
      }
      if ((inBounds(i-1, j) && Board[j].getDisc(i-1) == piece)) // checks for a win vertically
      {
        if ((inBounds(i-2, j) && Board[j].getDisc(i-2) == piece))
        {
          if ((inBounds(i-3, j) && Board[j].getDisc(i-3) == piece))
          {
            if ((inBounds(i-4, j) && Board[j].getDisc(i-4) == piece))
            {
              winner = 1;
            }    
          }    
        }    
      }    
      if ((inBounds(i-1, j+1) && Board[j+1].getDisc(i-1) == piece)) // checks for a win diagonally
      {
        if ((inBounds(i-2, j+2) && Board[j+2].getDisc(i-2) == piece))
        {
          if ((inBounds(i-3, j+3) && Board[j+3].getDisc(i-3) == piece))
          {
            if ((inBounds(i-4, j+4) && Board[j+4].getDisc(i-4) == piece))
            {
              winner = 1;
            }    
          }    
        }    
      }    
      if ((inBounds(i, j-1) && Board[j-1].getDisc(i) == piece)) // checks for a win horizontally
      {
        if ((inBounds(i, j-2) && Board[j-2].getDisc(i) == piece))
        {
          if ((inBounds(i, j-3) && Board[j-3].getDisc(i) == piece))
          {
            if ((inBounds(i, j-4) && Board[j-4].getDisc(i) == piece))
            {
              winner = 1;
            }    
          }    
        }    
      }    
    }
  }
  return winner;
}

void C4Board::play() // plays the game 
{
  int fullboard = 0, numDiscs = 0, turn = 0, choice = 0, game;
  cout << "Who would you like to play Connect 4 with?" << endl;
  cout << "  " << "Press '1' to play with a friend!" << endl;
  cout << "  " << "Press '2' to play against the computer!" << endl;
  cout << "Choice: ";
  cin >> game;
  cout << endl;
  switch (game) // switches based on who user wants to play against
  {
    case 1: // player vs. player
    {
      display(); // displays the board to the user
      while (fullboard != 1 || choice != -1) // runs while the board is not full and the user does not enter '-1' to quit
      {
        if ((turn%2) == 0) // Player 1
        {
          cout << "It is Player 1's turn! Enter the number of the column you would like to place your disc in, or enter '-1' to quit the game: ";
          cin >> choice;
          cout << endl;
          if (choice == -1) { break; }
          if (choice < -1 || choice == 0 || choice > 7) // error message for invalid input
          { 
            cout << "The parameter given is invalid." << endl; 
          }
          else
          { 
            Board[choice-1].addDisc('X'); // adds Player 1's piece to the board
            numDiscs++; // keeps a running tally
            if (checkNeighbors('X') == 1) // if checkNeighbors finds a winner
            { 
              cout << "PLAYER 1 WINS!" << endl;
              display(); // displays board before ending the game
              break; 
            }
            turn++;
          }
        }
        else // Player 2
        {
          cout << "It is Player 2's turn! Enter the number of the column you would like to place your disc in, or enter '-1' to quit the game: ";
          cin >> choice;
          cout << endl;
          if (choice == -1) { break; }
          if (choice < -1 || choice == 0 || choice > 7) // error message for invalid input
          { 
            cout << "The parameter given is invalid." << endl; 
          }
          else // adds Player 2's piece to the board
          {
            Board[choice-1].addDisc('O');
            numDiscs++; // keeps a running tally
            if (checkNeighbors('O') == 1) // if checkNeighbors is true
            { 
              cout << "PLAYER 2 WINS!" << endl;
              display(); // displays the board before ending the game
              break;
            }
            turn++;
          }
        }
        if ( turn == 42) // ends the game if the board is full of pieces
        {
          fullboard = 1;
          cout << "The board is full! The game is a tie!" << endl;
          break;
        }
        display(); // displays the board at the end of each turn
      }
    }
    case 2: // player vs. computer
    {
      display();
      while (fullboard != 1 || choice != -1) // runs while the board is not full and the user does not enter '-1' to quit
      {
        if ((turn%2) == 0) // Player 1
        {
          cout << "It is your turn! Enter the number of the column you would like to place your disc in, or enter '-1' to quit the game: ";
          cin >> choice;
          cout << endl;
          if (choice == -1) { break; }
          if (choice < -1 || choice == 0 || choice > 7) // error message for invalid input
          { 
            cout << "The parameter given is invalid." << endl; 
          }
          else
          { 
            Board[choice-1].addDisc('X'); // adds Player 1's piece to the board
            numDiscs++; // keeps a running tally
            if (checkNeighbors('X') == 1) // if checkNeighbors is true
            { 
              cout << "YOU WIN!" << endl;
              display(); // displays board before ending the game
              break;
            }
            turn++;
          }
        }
        else // Computer
        {
          srand(time(NULL)); // randomly picks a column to place the piece
          int aidisc = rand() % 6 + 1;
          cout << "It is the computer's turn!" << endl;
          Board[aidisc].addDisc('O');
          numDiscs++; // keeps a running tally
          if (checkNeighbors('O') == 1) // if checkNeighbors is true
          { 
            cout << "COMPUTER WINS!" << endl;
            display(); // displays board before ending the game
            break;
          }
          turn++;
        }
        if ( turn == 42) // ends the game if the board is full of pieces
        {
          fullboard = 1;
          cout << "The board is full! The game is a tie!" << endl;
          break;
        }
        display(); // displays the board at the end of each turn
      }
    }
  }
}

