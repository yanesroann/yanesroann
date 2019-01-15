// myint.cpp
#include <iostream>
using namespace std;
#include "myint.h"

MyInt::MyInt() { value = 0; }

MyInt::MyInt(int n) { value = n; }

MyInt::~MyInt() { }

int MyInt::getValue() { return value; }

void MyInt::setValue(int n) { value = n; }

void MyInt::display()
 { cout << "value is: " << value << endl; } 

// code for operator+ goes here:

MyInt MyInt::operator+(MyInt x) 
{
  return MyInt( value + x.value );
}


