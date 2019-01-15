/* Program: life.cpp
 * Author: Roann Yanes
 * This program simulates the game of Life on a 40-by-40 board, displayed as Xs (live cells) and blank spaces (dead cells).
 */

#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include "lifeboard.h" // need to include class interface
#include <unistd.h> // required for usleep
#include <cstdlib> // required for system
using namespace std;

#define SIZE1 40
#define SIZE2 40


int main(int argc, char* argv[]) // to check if file was input at the command line
{
  char choice;
  int x, y;
  Lifeboard life; // calls the Lifeboard class
  if (argc == 1) // if user just types the executable, nothing else (interactive mode)
  {
    life.displayBoard(); // displays the board to the user first
    cout << "a: enter 'a' followed by the coordinates to add a new live cell" << endl; // menu
    cout << "r: enter 'r' followed by the coordinates to remove a cell" << endl;
    cout << "n: advance the simulation to the next iteration" << endl;
    cout << "q: quit the program" << endl;
    cout << "p: play the game continuously" << endl;
    cout << "COMMAND: ";
    cin >> choice;

    while (choice != 'q') // program runs until the user quits
    {
      switch (choice)
      {
        case 'a': // adds a live cell
        cin >> x >> y;
        if (x < 0 || x > 39) // checks for valid point
        {
          cout << "Invalid point!" << endl;
          return 0;
        }
        else if (y < 0 || y > 39) // checks for valid point
        {
          cout << "Invalid point!" << endl;
          return 0;
        }
        life.addCell(x, y); // method of Lifeboard class
        break;
        case 'r': // removes a cell
        cin >> x >> y;
        if (x < 0 || x > 39) // checks for valid point
        {
          cout << "Invalid point!" << endl;
          return 0;
        }
        else if (y < 0 || y > 39) // checks for valid point
        {
          cout << "Invalid point!" << endl;
          return 0;
        }
        life.removeCell(x, y); // method of Lifeboard class
        break;
        case 'n': // advances to the next iteration
        life.advance(); // method of Lifeboard class
        break;
        case 'q': // quits the program
        return 1;
        break;
        case 'p': // runs endlessly
        int i = 1;
        while (i > 0) // will always be true; must enter "CTRL-C" to quit
        {
          system("clear"); // clears the screen
          life.advance(); // method of Lifeboard class
          life.displayBoard(); // method of Lifeboard class
          usleep(200000); // pauses the simulation
        }
        break;
      }
      life.displayBoard(); // method to display the board to the user
      cout << "a: enter 'a' followed by the coordinates to add a new live cell" << endl; // menu
      cout << "r: enter 'r' followed by the coordinates to remove a cell" << endl;
      cout << "n: advance the simulation to the next iteration" << endl;
      cout << "q: quit the program" << endl;
      cout << "p: play the game continuously" << endl;
      cout << "COMMAND: ";
      cin >> choice;
    }
    cout << "Thank you!" << endl; // displays when user quits
    return 0;
  }

  else if (argc == 2) // if user enters a text file at the command line (batch mode)
  {
    ifstream file(argv[1]);
    if (!file.is_open()) // checks if the data file is a valid one 
    {
      cout << "Error opening file!" << endl;
      return 1;
    }
     string arg_s, x_s, y_s;
     char arg;
     int x1, y1;
     while (!file.eof()) // reads in the commands from the text file into the program
     {
       getline(file, arg_s, ' '); // " " is the delimiter (gets command)
       getline(file, x_s, ' ');
       getline(file, y_s, '\n');
       arg = arg_s[0]; // calls the first character of the string
       x1 = stoi(x_s); // converts string to int
       y1 = stoi(y_s); // converts string to int
       if (arg == 'a') // adds points to the board      
       { 
         life.addCell(x1, y1); // method of Lifeboard class
       }
       else if (arg == 'p') // simulation runs endlessly; last input in file
       {
         int i = 1;
         while (i > 0) // will always be true; must exit by entering "CTRL-C"
         {
           system("clear"); // clears the screen
           life.advance(); // method of Lifeboard class
           life.displayBoard(); // method of Lifeboard class
           usleep(100000); // pause simulation
         }
       }
     }
  }
  return 3;
}
