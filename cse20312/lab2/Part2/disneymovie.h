/* Program: disneymovie.h
 * Author: Roann Yanes
 * This is the interface for a disneymovie base class. 
 */

#ifndef DISNEYMOVIE_H
#define DISNEYMOVIE_H

#include <string>
using namespace std;

class Disneymovie // base class for a Disney movie
{
  public:
    Disneymovie(string = " ", string = " ");  // constructor 
    void setName(const string); // set method
    void setCharacter(const string); // set method
    virtual void print(); // print function
    string getName(); // get method
    string getCharacter(); // get method
  protected:  // protected values
    string Name;
    string Character;
};
#endif
