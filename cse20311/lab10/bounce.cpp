/* Program: bounce.cpp
 * Author: Roann Yanes
 * This program animates a ball at a random direction and speed and makes it bounce against the walls. (Adapted from Prof. Bualuan's code).
 */ 

#include <unistd.h>
#include "gfx.h"
#include <cstdlib>

int main() 
{
  int win_wd = 600, win_ht = 600; // window width and height
  float xc = 100, yc = 100; // ball's initial center
  int rad = 20; // ball radius
  float vx = 1, vy = 1; // velocity vector
  float dt = 3; // multiplication factor
  char command = ' ';
 
  gfx_open (win_wd, win_ht, "Bouncing Ball"); // opens a window

  while(command != 'q') // until the user presses 'q'
  {
    gfx_clear(); // clears the window
    gfx_color(255,255,255); // white
    gfx_circle(xc, yc, rad); // creation of circle
    gfx_flush(); // flushes all output to the graphics window

    xc = xc + vx*dt; // x-coordinate
    yc = yc + vy*dt; // y-coordinate

    // walls collision detection
    if(xc >= win_wd-rad) // right wall
    { 
      xc = xc - 1; // prevents the ball from getting stuck
      vx = -vx;
    }
    else if(xc <= rad) // left wall
    {
      xc = xc + 1; // prevents the ball from getting stuck
      vx = -vx;
    }
    if(yc >= win_ht-rad)  // bottom wall
    {
      yc = yc - 1; // prevents the ball from getting stuck
      vy = -vy;
    }
    else if(yc <= rad) // top wall
    {
      yc = yc + 1; // prevents the ball from getting stuck   
      vy = -vy;
    }
    gfx_flush(); // flushes output to graphics window
    usleep(20000); // slows bouncing down
    if(gfx_event_waiting()) // to see if the user has pressed a key
    {
       command = gfx_wait(); // waits for a click from the user
       if (command == 1) // if the user clicks the mouse
       {  
         xc = gfx_xpos(); // sets position of ball at mouse click
         yc = gfx_ypos(); // sets position of ball at mouse click
         vx = rand() % 10 + 1; // makes the velocity random
         vy = rand() % 10 + 1; // makes the velocity random
         int direction = rand() % 4 + 1;
         if (direction == 1) // changes direction to make ball's movement random
         {
           vx = -vx;
         }
         if (direction == 2)
         {
           vy = -vy;
         }
         if (direction == 3)
         {
           vx = -vx;
           vy = -vy;
         }
       }     
    }
  }
  return 0;
}

