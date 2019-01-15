/* Program: animate.cpp
 * Author: Roann Yanes
 * This program allows the user to make a stick figure jump over a  rotating wheel, change the speed of the wheel, and change the color of the stick figure.
 */
#include <unistd.h>
#include "gfx.h"
#include <iostream>
#include <cmath>

void person(int, int, int, char); // prototype
void ground(int, int); // prototype
void polygon(int, int, int, int); // prototype
void spokes(float, float, float, float); // protoype
void wheel(float, float, float, float); // prototype
void instructions(); // prototype

using namespace std;

int main()
{
  int wd = 500, ht = 500; // window's width and height
  int x = 175, y = 300, yp = 300, xc = 0, yc = 300, radius = 20, length = 10; // initial dimensions of wheel and stick figure
  float theta = 0; 
  float vx = 1, vy = 1; // velocity vector
  float dt = 3; // multiplication factor
  bool loop = true; 
  char command, color = 'w';

  gfx_open(wd, ht, "Avoid the Wheels!"); // opens a new window for drawing
 
  instructions(); // displays the instructions to the user

  while(loop) // runs until the user quits
  {
    gfx_clear(); // clears the window
    person(x, yp, radius, color); // creates a white stick figure
    ground(y, radius); // creates the ground
    wheel(xc, ((yc + (radius * 5)) - 15), length, theta); // creates the wheel
    gfx_flush(); // flushes all output to graphics window
    usleep(3000); // pauses 
    theta = theta + (vx / 10); // the wheel to rotates
    xc = xc + (vx * dt);  // the wheel moves
    if ((xc) > wd) { xc = 0; } // the wheel moves off and on the screen
    // allows the user to change the speed of the wheel
    // allows the user to make the stick figure to jump or change its color
    if(gfx_event_waiting())
    {     
      command = gfx_wait();  
      switch (command)
      {
        case 'r': // if the user enters 'q'
          color = 'r';
          person(x, y, radius, color); // changes the color of the stick figure to red
          break;
        case 'p': // if the user enters 'p'
          color = 'p';
          person(x, y, radius, color); // changes the color of the stick figure to purple
          break;
        case 'b': // if the user enters 'b'
          color = 'b';
          person(x, y, radius, color); // changes the color of the stick figure to blue
          break;
        case 'y': // if the user enters 'y'
          color = 'y';
          person(x, y, radius, color); // changes the color of the stick figure to yellow
          break;
        case 'q': // if the user enters 'q'
          loop = false;
          break; // quits the program
        case 's': // surprise (if the user presses 's')
          gfx_color(0, 255, 255); // a shade of blue
          gfx_text(220, 75, "KEEP GOING!"); // writes text in the sky
          for (int i = 0; i <= 500; i++)
          {
            for (int j = 0; j <= 150; j++)
            {
              polygon(i, j, 3, 2); // draws triangles in the sky
              j = j + 10;
            }
            i = i + 10;
          }
          for (int i = 0; i <= 500; i++)
          {
            for (int j = 0; j <= 150; j++)
            {
              polygon(i, j, 5, 2); // draws pentagons in the sky
              j = j + 22;
            }
            i = i + 22;
          }
          break;
        case 'S': // RIGHT arrow
          vx = vx + 0.25; // speeds up the wheel
          break;
        case 'Q': // LEFT arrow
          vx = (vx - 0.25 < 0) ? 0 : vx - 0.25; // wheel slows down
          break;
        // allows the stick figure to jump over the wheel
        case 'R': // UP arrow
          int jump = 0;
          while ( jump < 22)
          {
            gfx_clear();
            person(x, yp, radius, color); // stick figure
            ground(y, radius); // ground
            wheel(xc, ((yc + (radius * 5)) - 15), length, theta); // wheel
            gfx_flush();
            usleep(2000);
            theta = theta + (vx / 10); // wheel rotates
            xc = xc + (vx * dt); // wheel keeps moving forward
            yp = yp - (vy * dt); // stick figure moves up horizontally
            jump++;
          }
          jump = 0;
          while ( jump < 22)
          {
            gfx_clear();
            person(x, yp, radius, color); // creates a white stick figure
            ground(y, radius);
            wheel(xc, ((yc + (radius * 5)) - 15), length, theta);
            gfx_flush();
            usleep(2000);
            theta = theta + (vx / 10); // wheel rotates
            xc = xc + (vx * dt); // wheel keeps moving forward
            yp = yp + (vy * dt); // stick figure moves down horizontally
            jump++;
          }
          break; 
      }
    }
  }
  return 0;
}

void person(int x, int y, int rad, char color) // function to create the stick figure
{
  switch (color)
  {
    case 'r':
      gfx_color(204, 0, 0); // sets the color of the stick figure (red)
      break;
    case 'p':
      gfx_color(153, 0, 153); // sets the color of the stick figure (purple)
      break;
    case 'b':
      gfx_color(0, 0, 255); // sets the color of the stick figure (blue)
      break;
    case 'y':
      gfx_color(255, 255, 51); // sets the color of the stick figure (yellow)
      break;
    default:
      gfx_color(255, 255, 255); // sets the color of the stick figure (white)
      break;
  }
  gfx_circle(x, y, rad); // head
  gfx_line(x, (y + rad), x, ((y + rad * 4))); // body
  gfx_line(( x - (rad * 2)), (y + (rad * 2)), (x + (rad * 2)), (y + ((rad * 2)))); // arms
  gfx_line(x, (y + (rad * 4)), (x + rad), (y + (rad * 5))); // right leg
  gfx_line(x, (y + (rad * 4)), (x - rad), (y + (rad * 5))); // left leg
}

void ground(int y, int rad) // function to create the ground
{
  gfx_color(0, 153, 0); // green
  for (int i = (y + (rad * 5)); i <= 500; i++)
  {
    gfx_line(0, i, 500, i); // ground
  }
}

void polygon(int x, int y, int sides, int rad) // function to create different polygons
{
  gfx_color(255, 153, 153);
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

void spokes(float x, float y, float length, float theta) // function to create the spokes of the wheel
{
  int x1, y1, x2, y2;
  x1 = x + (length * cos(theta));
  y1 = y + (length * sin(theta));
  x2 = x - (length * cos(theta));
  y2 = y - (length * sin(theta));
  gfx_line(x1, y1, x2, y2);
} 

void wheel(float x, float y, float length, float theta) // function to create the wheel
{
  gfx_color(255,153,51);
  spokes(x, y, length, (theta - (3.14 / 4)));
  spokes(x, y, length, (theta + (3.14 / 4)));
  spokes(x, y, length, (theta + (3.14 / 2)));
  spokes(x, y, length, theta);
  gfx_circle(x, y, (length + 2));
}

void instructions() // function for the instructions on how to play the game
{
  // tells the user how to play the game
  cout << "Avoid the wheels!" << endl;
  cout << "Jump over the wheel rolling towards you by pressing the UP arrow key." << endl;
  cout << "You can change the color of your stick figure:" << endl;
  cout << "  press 'r' for red" << endl;
  cout << "  press 'b' for blue" << endl;
  cout << "  press 'y' for yellow" << endl;
  cout << "  press 'p' for purple" << endl;
  cout << "Speed up or slow down the wheel by pressing the RIGHT and LEFT arrow keys, respectively." << endl;
  cout << "(For a special surprise, press 's'!)" << endl;
  cout << "Press 'q' to exit." << endl;
}
