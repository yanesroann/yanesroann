/* Program: symbol.cpp
 * Author: Roann Yanes
 * This program opens up a window, and waits for the user to press a key or a mouse button. On each key or button press, the program displays a small symbol centered at the current mouse location.
 */

#include <iostream>
#include <cmath>
using namespace std;
#include "gfx.h"

void triangle(int, int); // prototype
void circle(int, int); // prototype
void polygon(int, int, int, int); // prototype

int main()
{
  int wd = 500;  // window width
  int ht = 500;  // window height
  int x, y, radius = 25;
  bool loop = true;
  char command;
 
  gfx_open(wd, ht, "Symbolic Typewriter"); // opens a new window for drawing
  gfx_clear(); // clears the window
  gfx_flush; // flushs all output to the window
 
  while(loop) 
  {
    command = gfx_wait(); // waits for user input
    int click = command;
    x = gfx_xpos();    // get mouse click's x coordinate
    y = gfx_ypos();    // get mouse click's y coordinate
    if (click == 1) // if the mouse is clicked, a blue square is created
    {
      gfx_color(0, 0, 255); // blue
      polygon(x, y, 4, radius); // square
    }
    if (command == 't') // if the user presses 't'
    {
      triangle(x,y); // creates a triangle
    }
    else if (command == 'c') // if the user presses 'c'
    {
      circle(x,y); // creates a circle
    }
    else if (command == 'q') // if the user presses 'q'
    {
      break; // the program quits
    }
    else if (isdigit(command))
    {
      gfx_color(153, 0, 153); // purple
      if (command == '3') { polygon(x, y, 3, radius); } // triangle
      if (command == '4') { polygon(x, y, 4, radius); } // square
      if (command == '5') { polygon(x, y, 5, radius); } // pentagon
      if (command == '6') { polygon(x, y, 6, radius); } // hexagon
      if (command == '7') { polygon(x, y, 7, radius); } // heptagon
      if (command == '8') { polygon(x, y, 8, radius); } // octagon
      if (command == '9') { polygon(x, y, 9, radius); } // nonagon
    }
  }
  return 0;
}

void circle(int x, int y) // function to create a circle
{
  gfx_color(255,255,255); // white
  gfx_circle(x,y,25); // circle
}

void triangle(int x, int y) // function to create a triangle
{
  gfx_color(0,255,0); // sets the color to green
  gfx_line(x-25, y-25, x+25, y-25); // triangle
  gfx_line(x-25, y-25, x, y+25);
  gfx_line(x, y+25, x+25, y-25);
}

void polygon(int x, int y, int sides, int rad) // function to create different polygons
{
  double xC[sides], yC[sides];
  double sidez = sides;
  for (int i = 0; i < sides; i++)
  {
    xC[i] = rad * cos((2*3.14) * (i/sidez) + (sidez*45)) + x;
    yC[i] = rad * sin((2*3.14) * (i/sidez) + (sidez*45)) + y;
  }
  gfx_line(xC[0], yC[0], xC[sides-1], yC[sides-1]);
  for (int k = 0; k < sidez-1; k++)
  {
    gfx_line(xC[k],yC[k],xC[k+1],yC[k+1]);
  }
} 
