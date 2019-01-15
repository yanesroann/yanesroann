// testcircle.cpp
// // a main program to test the Circle class
 
#include <iostream>
using namespace std;
#include "circle.h"

void display(Circle &);

int main()
{
  Circle c1(7), c2;

  cout << "circle 1:" << endl;
  display(c1);

  cout << "circle 2:" << endl;
  c2.setRadius(5.2);
  display(c2);

  return 0;
}

void display(Circle &c)
{
  cout << "  radius: " << c.getRadius() << endl;
  cout << "  circumference: " << c.circumference() << endl;
  cout << "  area: " << c.area() << endl;
}

