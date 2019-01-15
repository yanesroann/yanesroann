// class implementation for Circle

#include "circle.h"   // need to include the class interface (prototype)

Circle::Circle()
{ radius = 1; }

Circle::Circle(float rd) 
{ radius = rd; }

Circle::~Circle() { }  // nothing to be done (yet)

float Circle::getRadius() 
{ return radius; }

void Circle::setRadius(float rd) 
{ radius = rd; }

float Circle::circumference() 
{ return (2*(radius)*3.14159); }

float Circle::area() 
{ return (3.14159*(radius)*(radius)); }

