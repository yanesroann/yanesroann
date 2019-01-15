/* Program: main.cpp
 * Author: Roann Yanes
 * This program tests the base class and inheritance in the two derived classes. 
 */

#include "disneymovie.h" // include base class header file
#include "lilo.h"
#include "beautybeast.h"

int main()
{
  Beautybeast princess; // instantiates derived class
  Lilo person; // instantiates derived class
  Beautybeast * princess_ptr = &princess; // creates pointer for the beautybeast derived class
  Lilo * person_ptr = &person; // creates pointer for the lilo derived class
  person_ptr->print(); // prints the Lilo and Stitch movie info
  princess_ptr->print(); // prints the Beauty and Beast movie info
  return 0;
}
