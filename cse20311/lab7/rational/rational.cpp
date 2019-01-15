/* Program: rational.cpp
 * Author: Roann Yanes
 * This program is the class implementation for Rational.
 */

#include "rational.h"   // need to include the class interface (prototype)
#include <iostream> // need to include for "cout"
using namespace std; // need to include for "cout"

Rational::Rational() // default case 
{ numer = 1; denom = 1; }

Rational::Rational(int num1, int num2) // constructor
{ numer = num1; denom = num2; }

Rational::~Rational() // destructor
{ }  // nothing to be done (yet)

int Rational::getNumer() 
{ return numer; }

int Rational::getDenom() 
{ return denom; }

void Rational::setNumer(int num1) 
{ numer = num1; }

void Rational::setDenom(int num2) 
{ denom = num2; }

void Rational::print()
{ cout <<  numer << "/" <<  denom << "\n"; }

Rational Rational::add(Rational x) // function for "add" utility
{
  Rational z;
  z.numer = (numer * x.getDenom()) + (denom * x.getNumer());
  z.denom = (denom * x.getDenom());
  return z;
}

Rational Rational::subtract(Rational x) // function for "subtract" utility
{
  Rational z;
  z.numer = (numer * x.getDenom()) - (denom * x.getNumer());
  z.denom = (denom * x.getDenom());
  return z;
}

Rational Rational::multiply(Rational x) // function for "multiply" utility
{
  Rational z;
  z.numer = (numer * x.getNumer());
  z.denom = (denom * x.getDenom());
  return z;
} 

Rational Rational::divide(Rational x) // function for "divide" utility
{
  Rational z;
  z.numer = (numer * x.getDenom());
  z.denom = (denom * x.getNumer());
  return z;
}
