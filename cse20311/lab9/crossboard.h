/* Program: crosswords.h
 * Author: Grace Milton and Roann Yanes
 * This program is the interface for Crossboard class.
 */

const int SIZE = 15; // sets size of board
#include <string>
#include <vector>
#include <cstring>
using namespace std;

class Crossboard
{
  public: // methods
   Crossboard(); // default constructor
   void displaySolution(); // utility method to display the solution to the crpuzzle
   void displayBoard(); // utility method to display the crossword puzzle
   ~Crossboard(); // destructor
   int getxCoordinate(int); // method to find x-coordinate of a word on the board
   int getyCoordinate(int); // method to find the y-coordinate of a word on the board
   void setxCoordinate(int); // method to set the x-ccordinate of a word
   void setyCoordinate(int); // method to 
   void addfirst(const char*); // utility method to add the first word to the board
   int findmatch(const char*); // method to 
   void addmore(const char*, int, int); //methdo to add the rest of the words to the board
  private: // attributes
   char currentboard[SIZE][SIZE]; // solution board
   char emptyboard[SIZE][SIZE]; // crossword puzzle board
   vector<int> xcoordinate; // vector of x-coordinates
   vector<int> ycoordinate; // vector of y-coordinates
};
