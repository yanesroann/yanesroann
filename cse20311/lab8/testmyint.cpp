// testmyint.cpp
#include <iostream>
using namespace std;
#include "myint.h"

int main()
{
  MyInt a, b(5);

  cout << "a is " << a.getValue() << endl;
  cout << "b is " << b.getValue() << endl;
  b.setValue(44);
  cout << "b is now " << b.getValue() << endl;

  MyInt c = a + b;  //  "+" is overoaded
  cout << "a+b is " << c.getValue() << endl;

  return 0;
}
