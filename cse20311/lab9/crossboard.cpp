/* Program: crosswords.cpp
 * Author: Grace Milton and Roann Yanes
 * This is the class implementation for Crossboard.
 */

#include <iostream>
#include <cstring>
using namespace std;
#include "crossboard.h"   // need to include the class interface (prototype)


Crossboard::Crossboard() // default constructor
{
  emptyboard[SIZE][SIZE];
  currentboard[SIZE][SIZE]; 
  for (int i = 0; i < SIZE; i++) 
  {
    for (int j = 0; j < SIZE; j++) 
    {
      currentboard[i][j] = '*'; // creates a 15x15 board of asterisks
      emptyboard[i][j] = '#';  // creates a 15x15 board of pound signs
    }
  } 
}

Crossboard::~Crossboard() // destructor
{ }  // nothing to be done (yet)

int Crossboard::getxCoordinate(int i)  // method to return the x-coordinate
{ return xcoordinate[i]; }

int Crossboard::getyCoordinate(int i) // method to return the y-coordinate
{ return ycoordinate[i]; }

void Crossboard::setxCoordinate(int x) // method to set the x-coordinate 
{
  xcoordinate.push_back(x); // adds the x-coordinate to the vector
}

void Crossboard::setyCoordinate(int y) // method to set the y-coordinate
{ 
  ycoordinate.push_back(y); // adds the y-coordinate to the vector
}

void Crossboard::displaySolution() // method to display formatted board
{
  cout << " ";
  for (int k = 0; k < SIZE; k++)
  {
    cout << "-"; // top boundary
  }
  cout << " " << endl;
  for (int i = 0; i < SIZE; i++) 
  {
    cout << "|"; // left boundary
    for (int j = 0; j < SIZE; j++) 
    {
      cout << currentboard[i][j]; // displays 15x15 board of asterisks 
    }
    cout << "|" << endl;  // right boundary
  }
  cout << " ";
  for (int m = 0; m < SIZE; m++)
  {
    cout << "-"; // bottom boundary
  }
  cout << endl;
}

void Crossboard::displayBoard() // method to display the crossword puzzle to the user
{
  cout << " ";
  for (int k = 0; k < SIZE; k++)
  {
    cout << "-"; // top boundary
  }
  cout << endl;
  for (int i = 0; i < SIZE; i++)
  {
    cout << "|"; // left boundary
    for (int j = 0; j < SIZE; j++)
    {
      if (currentboard[i][j] != '*') // if there is a word on the solution board, then the crossword puzzle board will have a blank space at that location
      {
        emptyboard[i][j] = ' '; // sets a blank space
      }
      cout << emptyboard[i][j]; // displays 15x15 board of pound signs
    }
    cout << "|" << endl;  // right boundary
  }
  cout << " ";
  for (int m = 0; m < SIZE; m++)
  {
    cout << "-"; // bottom boundary
  }
  cout << endl;
}

void Crossboard::addfirst(const char* c) // method to add the longest word to the middle of the board
{
  int csize = strlen(c), empty = 15 - csize;
  empty = empty / 2; // calculations to find the middle of the board
  setxCoordinate(empty); // sets the longest word's x-coordinate
  setyCoordinate(7); // sets the longest word's y-coordinate
  for (int i = 0; i < csize; i++)
  {
    currentboard[7][i+empty] = c[i]; // places the longest word in the middle of the board 
  }
}

int Crossboard::findmatch(const char* c) // method to find a valid match and returns a number to determine if it is vertical, horizontal, or can't be placed
{
  char one, two;
  int n = 0, nLetters = 0, length = strlen(c); 
  bool match = false, clear = false, isVert = false, place = false, outofbounds = false;       
  for (int m = 0; m < length; m++) // goes through each letter in a given word
  {
    for (int j = 0; j < 15; j++) // goes through every row
    {
      for (int k = 0; k < 15; k++) // goes through every column
      {
        one = currentboard[j][k];
        two = c[m];
        if (one == two) // if current spot on the board is equal to the current letter being looked at
        {
          match = true;
          if ((currentboard[j][k-1] != '*') || (currentboard[j][k+1] != '*') && (currentboard[j-1][k] == '*') && (currentboard[j+1][k] == '*')) // looks if there is a letter on the left or right of the intersection point, and makes sure if the spot above or below is empty
          {    
            isVert = true; // placed vertically 
            for (int i = -1; i <= 1; i++) // check neighbors to make sure word is clear to be placed
            {
              for (int q = -1; q <= length; q++) // check neighbors to make sure word is clear to be placed
              {
               if ((i != 0 && q == -1) || (i != 0 && q == length)) { continue; } // ignores spots kitty-corner to intersection
                if ((j-m+q) <= 15 && (j-m+q) >= 0 && (k+i) <= 15 && (k+i) >= 0) // makes sure word fits in boundaries of board
                { 
                  if ((currentboard[j+q-m][k+i]) != '*') { nLetters = nLetters + 1; } // counts the number of neighboring spots that contain a letter
                }
                else // accounts for word going out of boundaries
                {
                  clear = false;
                  outofbounds = true;
                }
              }
            }
            if (nLetters <= (3) && outofbounds == false) // allows word to be placed if only neighboring letters are in the word to be intersected and word is in bounds
            { 
              clear = true; 
              setxCoordinate(k); // adds x-coordinates of match and clear spot to the vector
              setyCoordinate(j-m); // adds y-coordinates of match and clear spot to the vector
              place = true; // set to be placed if match is true and clear is true
            }
            else // resets all variables if it cannot be placed
            {
              clear = false;
              match = false;
              place = false;
              nLetters = 0;
              outofbounds = false;
            }  
          }
          else // this is the case for it to be placed horizontally
          {
            isVert = false;
            for (int i = -1; i <= 1; i++) // checks neighbors to make sure word is clear to be placed
            {
              for (int q = -1; q <= length; q++) // checks neighbors to make sure word is clear to be placed
              {
              if ((i != 0 && q == -1) || (i != 0 && q == length)) { continue; } // ignores spots kitty-corner to intersection
                if ((j+i) <= 15 && (j+i) >= 0 && (k+q-m) <= 15 && (k+q-m) >= 0) // makes sure word fits in boundaries of board
                {
                  if ((currentboard[j+i][k+q-m]) != '*') { nLetters = nLetters + 1; } // counts the number of neighboring spots that contain a letter
                }
                else // accounts for word going out of boundaries
                {
                  clear = false;
                  outofbounds = true;
                }
              }
            }
            if (nLetters <= (3) && outofbounds == false) // allows word to be placed if only neighboring letters are in the word to be intersected and word is in boundaries
            {
              clear = true; 
              setxCoordinate(k-m); // adds x-coordinate of match and clear spot to the vector 
              setyCoordinate(j); // adds y-coordinate of match and clear spot to the vector
              place = true; // set to be placed if match is true and clear is true
            } 
            else // resets all variables if word cannot be placed
            {
              clear = false;
              match = false;
              place = false;
              nLetters = 0;
              outofbounds = false;
            }
          }
         // exits all loops if clear match found
         if (place == true) { break; }
         else { continue; }
        }
        if (place == true) { break; }
        else { continue; }  
      }
      if (place == true) { break; } 
      else { continue; }
    }
  }
  if (place == true) // returns value to signify the word is vertical, horizontally, or cannot be placed
  {
    if (isVert == true) { return 1; } // vertical
    else { return 2; } // horizontal
  }
  else { return 3; } // cannot be placed
}

void Crossboard::addmore(const char* c, int i, int dir) // function to add the rest of the words to the board
{
  int length = strlen(c), xstart = getxCoordinate(i), ystart = getyCoordinate(i); // gets coordinates for first letter of word
  
  switch (dir) // switch case if the word is vertical or horizontal
  {
    case 1: // vertical
      for(int j = 0; j < length; j++, ystart++) // goes through the length of the word and increments the row
      {
        currentboard[ystart][xstart] = c[j]; // places the letter into the word
      }
      ystart = getyCoordinate(i); // resets y-coordinate to first letter
      break;
    case 2: // horizontal 
      for(int k = 0; k < length; k++, xstart++) // goes through the length of the word and increments the column
      {
        currentboard[ystart][xstart] = c[k]; // places the letters into the word
      }
      xstart = getxCoordinate(i); // resets x-coordinate to first letter
      break;
  }   
}

