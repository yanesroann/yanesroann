/* Program: rationalmain.cpp
 * Author: Roann Yanes
 * This program is a driver to test the Rational class.
 */

#include <iostream>
#include "rational.h" // includes the class interface
using namespace std;

int main()
{
  Rational a(5,6), b(3,7), c, s, p, q, d, usernum;

  cout << "*** display a and b ***\n"; // tests the "print" utility method
  a.print(); // tests the print utility method
  b.print();
  cout << endl;

  cout << "*** display c ***\n";
  c.print();  // recall that c was instantiated with the default constructor
  cout << endl;
  
  // 'mathematically' add a and b
  cout << "*** compute s as the math sum of a and b, and display s ***\n"; // tests the "add" utility method
  s = a + b; // overloaded operator
  cout << s << endl; // tests the overloaded "<<" operator

  // 'mathematically' multiply a and b
  cout << "*** compute p as the math product of a and b, and display p ***\n"; // tests the "multiply" utility method
  p = a * b; // overloaded operator
  cout << p << endl;

  // 'mathematically' subtract a and b
  cout << "*** compute d as the math difference of a and b, and display d ***\n"; // tests the "subtract" utility method
  d = a - b; // overloaded operator
  cout << d << endl;

  // 'mathematically' divide a and b
  cout << "*** compute q as the math quotient of a and b, and display q ***\n"; // tests the "quotient" utility method
  q = a / b; // overloaded operator
  cout << q << endl;

  cout << "*** display the numerators and denominators of a and b ***\n"; // tests the "get" access method
  cout << "numerator of a: " << a.getNumer() << endl;
  cout << "denominator of a: " << a.getDenom() << endl;
  cout << "numerator of b: " << b.getNumer() << endl;
  cout << "denominator of b: " << b.getDenom() << endl;
  cout << endl;
 
  cout << "*** set the numerators and denominators of a and b to different values, and display the new a and b ***\n"; // tests the "set" access method
  a.setNumer(6);
  a.setDenom(9); 
  b.setNumer(2);
  b.setDenom(5);
  cout << "new numerator of a: " << a.getNumer() << endl;
  cout << "new denominator of a: " << a.getDenom() << endl;
  cout << "new numerator of b: " << b.getNumer() << endl;
  cout << "new denominator of b: " << b.getDenom() << endl;
  cout << a << endl;
  cout << b << endl;
  cout << endl; 

  cout << "*** set the numerator and denominator of b to different values, and display the new b ***\n"; // tests the "setRational" access method
  cout << "numerator of b: " << b.getNumer() << endl;
  cout << "denominator of b: " << b.getDenom() << endl;
  b.setRational(5, 7);
  cout << "new numerator of b: " << b.getNumer() << endl;
  cout << "new denominator of b: " << b.getDenom() << endl;
  cout << b << endl;


  cin >> usernum; // tests the overloaded ">>" operator
  cout << "The number you entered is " << usernum << "." << endl; 
  return 0;
}
