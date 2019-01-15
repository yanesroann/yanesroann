/* Program: beautybeast.h
 * Author: Roann Yanes
 * This is the interface for a beautybeast derived class. 
 */

#ifndef BEAUTYBEAST_H
#define BEAUTYBEAST_H
#include "disneymovie.h" // includes header of base class
#include <string>
using namespace std;

class Beautybeast : public Disneymovie // inherits from Disneymovie
{
  public:
    Beautybeast();  // constructor 
    virtual void print(); // print function
  private: // private values
    string Prince; 
    string Villain;
    string DressColor;
    string SideKick;
};

#endif
