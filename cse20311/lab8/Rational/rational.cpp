/* Program: rational.cpp
 * Author: Roann Yanes
 * This program is the class implementation for Rational.
 */

#include "rational.h"   // need to include the class interface (prototype)
#include <iostream> // need to include for "cout"
#include <cmath>
using namespace std; // need to include for "cout"

Rational::Rational() // default case 
{ setRational(1, 1); }

Rational::Rational(int num1, int num2) // constructor
{ setRational(num1, num2); }

Rational::~Rational() // destructor
{ }  // nothing to be done (yet)

void Rational::setRational(int num1, int num2) // to set both elements at once
{
  setNumer(num1);
  setDenom(num2);
}

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

Rational Rational::operator+(Rational x) // function for "add" utility
{
  Rational z;
  z.numer = (numer * x.getDenom()) + (denom * x.getNumer());
  z.denom = (denom * x.getDenom());
  return z;
}

Rational Rational::operator-(Rational x) // function for "subtract" utility
{
  Rational z;
  z.numer = (numer * x.getDenom()) - (denom * x.getNumer());
  z.denom = (denom * x.getDenom());
  return z;
}

Rational Rational::operator*(Rational x) // function for "multiply" utility
{
  Rational z;
  z.numer = (numer * x.getNumer());
  z.denom = (denom * x.getDenom());
  return z;
} 

Rational Rational::operator/(Rational x) // function for "divide" utility
{
  Rational z;
  z.numer = (numer * x.getDenom());
  z.denom = (denom * x.getNumer());
  return z;
}

istream& operator>>(istream& in, Rational& x) // overload istream
{
  int n, d;
  
  cout << "Enter the numerator and denominator: ";
  in >> n >> d; // reads in the numerator and denominator
  x.setRational(n, d);
  return in;
}

ostream& operator<<(ostream& out, const Rational& x) // overload ostream
{
  char sign = (x.numer >= 0) ? '+' : '-'; // to make output look nice
  out << x.numer << "/" << x.denom; // output when "<<" is used to output rational numbers
  return out;
}
