/* Program: sudoku.cpp
 * Author: Roann Yanes
 * This program is the implementation of the Sudoku class.
 */

#include <vector>
#include "sudoku.h"
#include <iostream>
#include <fstream>
using namespace std;

Sudoku::Sudoku() // default constructor
{
  fstream ifs;
  string infilename;
  char number_s;
  int array[81]; // stores the input from file into char array
  cout << "Enter the file name: "; // asks the user for a data file name
  cin >> infilename;
  ifs.open(infilename.c_str());
  if (!ifs) // checks if the data file is a valid one
  {
    cout << "Error opening file: " << infilename << endl;
  }
  int i = 0;
  while(!ifs.eof()) // reads in the file
  {
    ifs >> number_s; // puts the elements in the file
    array[i] = number_s - '0'; // converts the chars to int
    i++;
  }
  int k = 0;
  for (int j = 0; j < 9; j++)
  {
    for (int p = 0; p < 9; p++)
    {
      Cell cell; // calls the Cell class
      cell.cellContent = array[k]; // stores it as the contents of the cell
      Board[j][p] = cell; // stores that value in the board
      k++;
     }
   }
}

Sudoku::~Sudoku() // deconstructor
{}

void Sudoku::getBoard() // prints out the Sudoku board
{
  for (int i = 0; i <= 8; i++)
  {
    for (int j = 0; j <= 8; j++)
    {
      cout << (Board[i][j]).cellContent; // prints out the number that is in the board
      if (j !=0 && j % 8 == 0) { cout << endl; }
    }
  }
}

void Sudoku::elimination() // finds cases where only one possibility exists
{
  	int content;
	for (int i = 0; i < 9; i++)
  	{
		for (int j = 0; j < 9; j++)
    		{
      			if ((Board[i][j]).cellContent == 0) // when the board doesn't have a value
      			{
        			for (int k = 0; k < 9; k++) // checks the rows
        			{
          				content = (Board[i][k]).cellContent;
          				if (content != 0)
          				{
            					(Board[i][j]).Possible[content-1] = 0; // sets surrounding areas equal to zero
          				}
        			}
        			for (int m = 0; m < 9; m++) // checks the columns
        			{
          				content = (Board[m][j]).cellContent;
          				if (content != 0)
          				{
            					(Board[i][j]).Possible[content-1] = 0; // sets surrounding areas equal to zero
          				}
        			} 
				for (int y = 0; y < 3; y++) // checks mini grid
				{
					for (int q = 0; q < 3; q++)
					{
						content = (Board[y][q]).cellContent;
						if (content != 0)
						{
							if ((i < 3) && (j < 3)) { (Board[i][j]).Possible[content-1] = 0; }  // sets surrounding areas equal to zero
						}
					}
				}
				for (int y = 3; y < 6; y++) // checks mini grid
				{
					for (int q = 0; q < 3; q++)
					{
						content = (Board[y][q]).cellContent;
						if (content != 0)
						{
							if ((i > 2) && (i < 6) && (j < 3)) { (Board[i][j]).Possible[content-1] = 0; } // sets surrounding areas equal to zero
						}
					}
				}
				for (int y = 6; y < 9; y++) // checks mini grid
				{
					for (int q = 0; q < 3; q++)
					{
						content = (Board[y][q]).cellContent;
						if (content != 0)
						{
							if ((i > 5) && (j < 3)) { (Board[i][j]).Possible[content-1] = 0; } // sets surrounding areas equal to zero
						}
					}
				}
				for (int y = 0; y < 3; y++) // checks mini grid
				{
					for (int q = 3; q < 6; q++)
					{
						content = (Board[y][q]).cellContent;
						if (content != 0)
						{
							if ((i < 3) && (j < 6) && (j > 2)) { (Board[i][j]).Possible[content-1] = 0; } // sets surrounding areas equal to zero
						}
					}
				}
				for (int y = 3; y < 6; y++) // checks mini grid
				{
					for (int q = 3; q < 6; q++)
					{
						content = (Board[y][q]).cellContent;
						if (content != 0)
						{
							if ((i > 2) && (i < 6) && (j < 6) && (j > 2)) { (Board[i][j]).Possible[content-1] = 0; } // sets surrounding areas equal to zero
						}
					}
				}
				for (int y = 6; y < 9; y++) // checks mini grid
				{
					for (int q = 3; q < 6; q++)
					{
						content = (Board[y][q]).cellContent;
						if (content != 0)
						{
							if ((i > 5) && (j < 6) && (j > 2)) { (Board[i][j]).Possible[content-1] = 0; } // sets surrounding areas equal to zero
						}
					}
				}
				for (int y = 0; y < 3; y++) // checks mini grid
				{
					for (int q = 6; q < 9; q++)
					{
						content = (Board[y][q]).cellContent;
						if (content != 0)
						{
							if ((i < 3) && (j > 5)) { (Board[i][j]).Possible[content-1] = 0; } // sets surrounding areas equal to zero
						}
					}
				}
				for (int y = 3; y < 6; y++) // checks mini grid
				{
					for (int q = 6; q < 9; q++)
					{
						content = (Board[y][q]).cellContent;
						if (content != 0)
						{
							if ((i > 2) && (i < 6) && (j > 5)) { (Board[i][j]).Possible[content-1] = 0; } // sets surrounding areas equal to zero
						}
					}
				}
				for (int y = 6; y < 9; y++) // checks mini grid
				{
					for (int q = 6; q < 9; q++)
					{
						content = (Board[y][q]).cellContent;
						if (content != 0)
						{
							if ((i > 5) && (j > 5)) { (Board[i][j]).Possible[content-1] = 0; } // sets surrounding areas equal to zero
						}
					}
				}
      			}
    		}		
	}
}

void Sudoku::checkRow() // implements singleton algorithm
{
	int check[9] = {0,0,0,0,0,0,0,0,0}; // array to store frequency of possibilities
        int count = 0;
        	for(int i = 0; i < 9; i++) 
		{
                	if(Board[0][i].cellContent == 0) // if there is no value on the board
			{
                                for(int j = 0; j < 9; j++) 
				{
                                        if(Board[0][i].Possible[j] != 0) 
					{
                                                int x = Board[0][i].Possible[j];
                                                check[i]++; // increments the frequency array
                                        }
                        	}
                	}

        		int num = 0;
        		for(int q = 0; q < 9; q++)
        		{
                		if(check[q] == 1 && Board[0][i].cellContent == 0) // if the number only appears once
                		{

                        		num = Board[0][i].Possible[q];
                		}
                		Board[0][i].cellContent = num; // sets the board
        		}
        	}	
	elimination(); // calls the elimination function
}

void Sudoku::checkCol() // implements singleton algorithm
{
        int check[9] = {0,0,0,0,0,0,0,0,0}; // array to store frequency of possibilities
        int count = 0;
                for(int i = 0; i < 9; i++) 
		{
                        if(Board[i][0].cellContent == 0) // if there is no value on the board
			{
                                for(int j = 0; j < 9; j++) 
				{
                                        if(Board[i][0].Possible[j] != 0) 
					{
                                                int x = Board[i][0].Possible[j];
                                                check[i]++; // increments the frequency array
                                        }
                        	}
                	}
        		int num = 0;
        		for(int q = 1; q < 10; q++)
        		{
                		if(check[q] == 1 && Board[i][0].cellContent == 0) // if the number only appears once
                		{
                        		num = Board[i][0].Possible[q];
                        	}
                        	Board[i][0].cellContent = num; // sets the board
        		}
        	}
	elimination(); // calls the elimination function
}

void Sudoku::setCells() // sets the cells that only have one possibility
{
  int poss;
  int num;
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if ((Board[i][j]).cellContent == 0) // if there is not a value already assigned
      {
        poss = 0;
        for (int g = 0; g < 9; g++)
        {
          if (Board[i][j].Possible[g] != 0) { poss++; num = Board[i][j].Possible[g]; } // assigns the value to num
        }
        if (poss == 1) { Board[i][j].cellContent = num; } // pushes the value to the board
      }
    }
  }
}

bool Sudoku::checkFull() // checks for a value at every location
{
  int counter = 0;
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (Board[i][j].cellContent != 0) { counter++; } // if there is a value present
      
    }
  }
  if (counter == 81) { return true; } // the board is full
  else { return false; } // the board is not full
} 
