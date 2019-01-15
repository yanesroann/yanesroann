/* Program: state.h
 * Author: Roann Yanes
 * This program is the interface for a State class.
 */

#include <string>
using namespace std;

class State 
{
  public: // methods 
   State(); // default constructor
   State(string, string, string, int, int, int); // constructor
   ~State(); // destructor
   void setAbbrev(string); // access method for state abbreviation
   void setStatename(string); 
   void setCapital(string); 
   void setPopulation(int); 
   void setYear(int); 
   void setReps(int);
   string getAbbrev(); // access method
   string getStatename();
   string getCapital();
   int getPopulation();
   int getYear();
   int getReps();
   void print(); // utility method
   void printYear(); // utility method
   void printPopulation(); // utility method
   void printCapital(); // utility method
  private: // attributes
   string abbrev;
   string statename;
   string capital;
   int population;
   int year;
   int reps;
};
