/* Program: rational.h
 * Author: Roann Yanes
 * This program is the class interface for a Rational.
 */
#include <iostream>
using namespace std;

class Rational {
  public: // behavior (public functions)
    friend istream& operator>>(istream&, Rational&); // overload the ">>" operator for cin
    friend ostream& operator<<(ostream&, const Rational&); // overload the "<<" operator for cout
    Rational(); // constructor
    Rational(int, int);
    ~Rational(); // destructor
    int getNumer(); // access method
    int getDenom();
    void setRational(int, int); // instead of having to set each element individually 
    void setNumer(int); 
    void setDenom(int);
    void print();
    Rational operator+(Rational); // overload "+" operator to add
    Rational operator-(Rational); // overload "-" operator to subtract
    Rational operator*(Rational); // overload "*" operator to multiply
    Rational operator/(Rational); // overload "/" operator to divide
  private: // attributes
    int numer;
    int denom;
};
