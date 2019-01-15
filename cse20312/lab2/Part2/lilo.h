/* Program: beautybeast.h
 * Author: Roann Yanes
 * This is the interface for a beautybeast derived class. 
 */

#ifndef LILO_H
#define LILO_H
#include "disneymovie.h"
#include <string>
using namespace std;

class Lilo : public Disneymovie
{
  public:
    Lilo();  // constructor 
    virtual void print(); // print function
  private:
    string Guardian; 
    string Antagonist;
    string Phrase;
    string SideKick;
};

#endif
