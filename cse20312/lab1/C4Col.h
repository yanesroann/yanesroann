/* Program: C4Col.h
 * Author: Roann Yanes
 * This is the class implementation for the C4Col class. 
 */
#include <iostream>
#ifndef C4COL_H
#define C4COL_H
using namespace std;

class C4Col {
  public:
    C4Col(); // default constructor
    C4Col(const C4Col &); // copy constructor
    ~C4Col(); // deconstructor
    int getMaxDiscs(); // returns the maximum number of discs
    int isFull(); // determines if the column is full
    char getDisc(int); // returns the requested element of the private character array
    void addDisc(char); // adds the character representing a disc to the next open slot in the Disc array
  private:
    int numDiscs; // stores the number of discs currently in the column
    int maxDiscs; // stores the maximum number of discs allowed once the class is constructed	  
    char * Discs; // stores disc info
};

#endif
