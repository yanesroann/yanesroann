/* Program: lifeboard.h
 * Author: Roann Yanes
 * This program is the interface for Lifeboard class.
 */

#define SIZE1 40
#define SIZE2 40
#include <string>
using namespace std;

class Lifeboard 
{
  public: // methods
   Lifeboard(); // default constructor
   Lifeboard(int, int); // constructor
   void displayBoard(); // utility method to display board
   ~Lifeboard(); // destructor
   void addCell(int, int); // utility method to add a live cell
   void removeCell(int, int); // utility method to remove a cell
   void advance(); // utility method to simulate next iteration
   bool checkBoard(int, int); // utility method to check bounds of board 
  private: // attributes
   int row;
   int col;
   char tempboard[SIZE1][SIZE2];
   char currentboard[SIZE1][SIZE2];
};
