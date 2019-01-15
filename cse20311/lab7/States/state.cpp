/* Program: state.cpp
 * Author: Roann Yanes
 * This program is the implementation for the State class.
 */
#include <iostream>
#include "state.h"
using namespace std;

State::State() { } // constructor

State::State(string ab, string sn, string cp, int pop, int yr, int rp) 
{ abbrev = ab, statename = sn; capital = cp; population = pop; year = yr; reps = rp; }

State::~State() { } // destructor

void State::setAbbrev(string ab) // "set" access method
{ abbrev = ab; }

void State::setStatename(string sn) 
{ statename = sn; }

void State::setCapital(string cp) 
{ capital = cp; }

void State::setPopulation(int pop) 
{ population = pop; }

void State::setYear(int yr) 
{ year = yr; }

void State::setReps(int rp) 
{ reps = rp; }

string State::getAbbrev() 
{ return abbrev; }

string State::getStatename() // "get" access method 
{ return statename; }

string State::getCapital() 
{ return capital; }

int State::getPopulation() 
{ return population; }

int State::getYear() 
{ return year; }

int State::getReps() 
{ return reps; }

void State::print() // utility method to print a state and its data
{
  cout << statename << " (";
  cout << abbrev << "):" << endl;
  cout << "Capital: " << capital << endl;
  cout << "Population: " << population << endl;
  cout << "Year it became a state: " << year << endl;
  cout << "Number of representatives in Congress: " << reps << endl;
}

void State::printYear() // utility method to print the name of a state and its year of statehood 
{
  cout << "Year: " << year << "   " << statename << endl;
}

void State::printPopulation() // utility method to print the name and populationof a state
{
  cout << statename << endl; 
  cout << "Population: " << population << endl;
}

void State::printCapital() // utility method to print the capital, abbreviation, and name of a state
{
  cout << abbrev << ": " << capital << ", " << statename << endl;  
}

