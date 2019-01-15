#include <iostream>
#include "gfx.h"

int main()
{
  const int xsize = 500, ysize = 300;
  char c;
  gfx_open(xsize, ysize, "Example Graphics Program");
  gfx_color(0,200,100);
  gfx_line(100,100,200,100);
  gfx_line(200,100,150,150);
  gfx_line(150,150,100,100);
  gfx_color(200,100,50);
  gfx_circle(300,150,40);
 
  while(true) 
  {
   c = gfx_wait();
   if(c == 'q') break;
  }

  return 0;
}

