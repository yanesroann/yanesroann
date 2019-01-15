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

int Crossboard::getxCoordinate(int i) 
{ return xcoordinate[i]; }

int Crossboard::getyCoordinate(int i) 
{ return ycoordinate[i]; }

void Crossboard::setxCoordinate(int x)
{
  xcoordinate.push_back(x); // adds the x-coordinate to the vector
}

void Crossboard::setyCoordinate(int y)
{ 
  ycoordinate.push_back(y);
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
      cout << currentboard[i][j];
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

void Crossboard::displayBoard()
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
      if (currentboard[i][j] != '*')
      {
        emptyboard[i][j] = ' '; 
      }
      cout << emptyboard[i][j];
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

void Crossboard::addfirst(const char* c)
{
  int csize = strlen(c), empty = 15 - csize;
  empty = empty / 2;
  setxCoordinate(empty);
  setyCoordinate(7);
  for (int i = 0; i < csize; i++)
  {
    currentboard[7][i+empty] = c[i];
  }
}

int Crossboard::findmatch(const char* c)
{
  char one, two;
  int n = 0, nLetters = 0, length = strlen(c); 
  bool match = false, clear = false, isVert = false;       
  for (int m = 0; m < length; m++)
  {
    for (int j = 0; j < 15; j++)
    {
      for (int k = 0; k < 15; k++)
      {
        one = currentboard[j][k];
        two = c[m];
        if (one == two)
        {
          match = true;
          clear = false;
          if ((currentboard[j][k-1] != '*') || (currentboard[j][k+1] != '*'))
          {
            isVert = true;
            for (int i = -1; i <= 1; i++)
            {
              for (int q = -1; q <= length; q++)
              {
               if ((i != 0 && q == -1) || (i != 0 && q == length)) { continue; }
                if ((j-m+q) < 15 && (j-m+q) >= 0 && (k+i) < 15 && (k+i) >= 0)
                { 
                  if ((currentboard[j+q-m][k+i]) != '*') { nLetters = nLetters + 1; }
                }
              }
            }
            if (nLetters <= (3)) 
            { 
              clear = true; 
              setxCoordinate(k);
              setyCoordinate(j-m);
            } 
          }
          else
          {
            for (int i = -1; i <= 1; i++)
            {
              for (int q = -1; q <= length; q++)
              {
              if ((i != 0 && q == -1) || (i != 0 && q == length)) { continue; }
                if ((j+i) < 15 && (j+i) >= 0 && (k+q-m) < 15 && (k+q-m) >= 0)
                {
                  if ((currentboard[j+i][k+q-m]) != '*') { nLetters = nLetters + 1; }
                }
              }
            }
            if (nLetters <= (3)) 
            {
              clear = true; 
              setxCoordinate(j);
              setyCoordinate(k-m);
            } 
          }
          if (match == true && clear == true) { break; }
        //  else { continue; }
        }
        if(match == true && clear == true) { break; }
        //else { continue; }  
      }
      if (match == true && clear == true) { break; } 
      //else { continue; }
    }
  }
  if (match == true && clear == true)
  {
    if (isVert == true)
    {
      return 1;
    }
    else
    {
      return 2;
    }
  }
  else
  {
    return 3;
  }
}

void Crossboard::addmore(const char* c)
{
  char one, two;
  int n = 0, nLetters = 0, length = strlen(c); 
  bool match = false, clear = false;       
  for (int m = 0; m < length; m++)
  {
    for (int j = 0; j < 15; j++)
    {
      for (int k = 0; k < 15; k++)
      {
        one = currentboard[j][k];
        two = c[m];
        if (one == two)
        {
          match = true;
          clear = false;
          if ((currentboard[j][k-1] != '*') || (currentboard[j][k+1] != '*'))
          {
            for (int i = -1; i <= 1; i++)
            {
              for (int q = -1; q <= length; q++)
              {
                if ((i != 0 && q == -1) || (i != 0 && q == length)) { continue; }
                if ((j-m+q) < 15 && (j-m+q) >= 0 && (k+i) < 15 && (k+i) >= 0)
                { 
                  if ((currentboard[j+q-m][k+i]) != '*') { nLetters = nLetters + 1; }
                  cout << "letters: " << nLetters << endl;
                }
              }
            }
            if (nLetters <= (3)) { clear = true; }
            if (match == true && clear == true)
            { 
              for (int z = j - m; z < length + j - m; z++, n++)
              {
                currentboard[z][k] = c[n];
                if (z == j - m )
                {
                  setxCoordinate(k);
                  setyCoordinate(z);
                }
              }
            }        
          }
          else
          {
            for (int i = -1; i <= 1; i++)
            {
              for (int q = -1; q <= length; q++)
              {
                if ((i != 0 && q == -1) || (i != 0 && q == length)) { continue; }
                if ((j+i) < 15 && (j+i) >= 0 && (k+q-m) < 15 && (k+q-m) >= 0)
                {
                  if ((currentboard[j+i][k+q-m]) != '*') { nLetters = nLetters + 1; }
                }
              }
            }
            if (nLetters <= (3)) { clear = true; }
            if (match == true && clear == true)
            {
              for (int z = k - m; z < length + k - m; z++, n++)
              {
                currentboard[j][z] = c[n];
                if (z == k - m)
                {
                  setxCoordinate(z);
                  setyCoordinate(j);
                }
              }
            }           
          }
          if (match == true && clear == true) { break; }
 //         else { continue; }
        }
        if(match == true && clear == true) { break; }
   //     else { continue; }  
      }
      if (match == true && clear == true) { break; } 
     // else { continue; }
    }
  }
}

