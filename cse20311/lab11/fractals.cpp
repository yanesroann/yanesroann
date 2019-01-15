/* Program: fractals.cpp
 * Authors: Grace Milton and Roann Yanes
 * This program generates fractal shapes. The program will first open a large window and wait for user input. When the user presses any of the numbers 1 through 8, the program will clear the screen, and then draw the corresponding fractal shape. Then, for each new number (1-8) pressed, that fractal will be displayed. The program exits when the user presses 'q'.
 */

#include "gfx.h"
#include <cmath>

void menu(); // protoype
void triangle( int x1, int y1, int x2, int y2, int x3, int y3 ); // prototype
void square( double xc, double yc, double length ); // prototype
void spiral( double x, double y, double mradius, double radius, double theta );
void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 ); // prototype
void shrinkingSquares( double xc, double yc, double length ); // prototype
void spiralSquares( double xc, double yc, double length, double theta ); // prototype
void circularLace( double xc, double yc, double radius ); // prototype
void snowflake( double x, double y, double radius, double theta ); // prototype
void tree( double x, double y, double length, double theta ); // prototype
void fern( double x, double y, double length, double theta ); // prototype
void spirals( double x, double y, double radius, double theta ); //prototype

int main() 
{ 
  const float WINDOW_WID = 800; // window size
  const float WINDOW_HGT = 800;
  bool loop = true;
  char command;
 
  gfx_open(WINDOW_WID, WINDOW_HGT, "Fractals");
  gfx_clear();
  menu(); // displays the menu to the user in the graphics window
  while(loop) // runs while loop is true
  {
    if (gfx_event_waiting()) // the program waits until something is pressed
    {
      command = gfx_wait();
      switch (command) 
      {
        case '1':  // sierpinski triangle
          gfx_clear(); // clears the graphics window
          sierpinski( 100, 100, 700, 100, 400, 700 );
          break;

        case '2':  // shrinking squares
          gfx_clear(); // clears the graphics window
          shrinkingSquares( 400, 390, 200 );
          break;

        case '3':  // spiral squares
          gfx_clear(); // clears the graphics window
          spiralSquares( 400, 400, 1, 0 );
          break;

        case '4':  // circular lace
          gfx_clear(); // clears the graphics window
          circularLace( 400, 400, 240 );
          break;

        case '5':  // snowflake
          gfx_clear(); // clears the graphics window
          snowflake( 400, 400, 240, 3*3.14159/10 );
          break;

        case '6':  // tree
          gfx_clear(); // clears the graphics window
          tree( 400, 800, 250, 0 );
          break;

        case '7':  // fern
          gfx_clear(); // clears the graphics window
          fern( 400, 750, 500, 0 );
          break;

        case '8':  // spiral of spirals
          gfx_clear(); // clears the graphics window
          spirals( 400, 400, 0.9, 2*3.14159/3 );
          break;
       
        case 'm': // displays the menu to the user
          gfx_clear(); // clears the graphics window
          menu();
          break;

        case 'q':  // ends program
          loop = false; // sets the loop to false
          break;
      }
    }
  }
  return 0;
}

// creation of functions 

void triangle( int x1, int y1, int x2, int y2, int x3, int y3 ) // function to create a triangle
{
  gfx_line( x1, y1, x2, y2 );
  gfx_line( x2, y2, x3, y3 );
  gfx_line( x3, y3, x1, y1 );
}

void square( double xc, double yc, double length ) // function to create a square
{
  gfx_line( xc-length, yc-length, xc+length, yc-length );
  gfx_line( xc+length, yc-length, xc+length, yc+length );
  gfx_line( xc+length, yc+length, xc-length, yc+length );
  gfx_line( xc-length, yc+length, xc-length, yc-length );
}  

void spiral( double x, double y, double mradius, double radius, double theta ) // function to create a spiral
{
  if ( radius >= mradius/3 ) { return; } // base case

  gfx_point( x, y );
  
  // modify parameters
  radius = 1.1*radius;
  theta = theta-(3.14159/5);
  x = x+3*radius*cos(theta);
  y = y+3*radius*sin(theta); 

  // recursive calls
  spiral( x, y, mradius, radius, theta );
  spiral( x, y, radius, 0.25, 0 );
}

void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 ) // function to create the first fractal shape
{
  gfx_color( 255, 178, 102 ); // sets the color to white

  if( fabs(x2-x1) < 5 ) { return; } // base case

  triangle( x1, y1, x2, y2, x3, y3 ); // triangle drawing function

  // recursive calls
  sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
  sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
  sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}

void shrinkingSquares( double xc, double yc, double length ) // function to create the second fractal shape
{
  gfx_color( 255, 0, 0 ); // sets the color to red

  if( length <= 2 ) { return; } // base case

  square( xc, yc, length ); // square drawing function

  // recursive calls  
  shrinkingSquares( xc-length, yc-length, 0.45*length );
  shrinkingSquares( xc+length, yc-length, 0.45*length );
  shrinkingSquares( xc-length, yc+length, 0.45*length );
  shrinkingSquares( xc+length, yc+length, 0.45*length );
}

void spiralSquares( double xc, double yc, double length, double theta ) // function to create the third fractal shape
{
  gfx_color( 255, 255, 0 ); // sets the color to yellow

  if ( xc >= 800 || xc < 0 ) { return; } // base case

  square( xc, yc, length ); // square drawing function
  
  // modify parameters
  length = 1.1*length;
  theta = theta-(3.14159/5); 
  xc = xc+4*length*cos(theta);
  yc = yc+4*length*sin(theta);

  // recursive calls
  spiralSquares( xc, yc, length, theta );
}

void circularLace( double xc, double yc, double radius ) // function to create the fourth fractal shape
{
  gfx_color( 153, 51, 255 ); // sets the color to purple
  
  if ( radius < 2 ) { return; } // base case

  gfx_circle( xc, yc, radius );

  // recursive calls
  for ( double i = 0; i <= 2*3.14159*5/6; i = i+3.14159/3 )
  {
    circularLace( xc+radius*cos(i), yc+radius*sin(i), radius/3 );
  } 
}

void snowflake( double x, double y, double radius, double theta ) // function to create the fifth fractal shape
{
  double x2, y2;
  gfx_color( 255, 255, 255 ); // sets the color to white

  for ( int i = 0; i < 5; i++ )
  {
    if (radius < 2 ) { return; } // base case

    x2 = x+radius*cos(theta+i*2*3.14159/5); 
    y2 = y-radius*sin(theta+i*2*3.14159/5);
 
    gfx_line( x, y, x2, y2 );
  
    // recursive call
    snowflake( x2, y2, radius/3, theta );
  }
}

void tree ( double x, double y, double length, double theta ) // function to create the sixth fractal shape
{
  double x1, y1;
  gfx_color( 102, 204, 0 ); // sets the color to green
 
  if ( length < 2 ) { return; } // base case
  
  x1 = x+length*sin(theta);
  y1 = y-length*cos(theta);

  gfx_line( x, y, x1, y1 );

  // recursive calls
  tree( x1, y1, length/1.5, theta-3.14159/5 );
  tree( x1, y1, length/1.5, theta+3.14159/5 );
}

void fern( double x, double y, double length, double theta ) // function to  create the seventh fractal shape 
{
  double x2, y2;
 
  gfx_color( 0, 153, 0 ); // sets the color to green
 
  if ( length < 5 ) { return; } // base case

  x2 = x+length*sin(theta);
  y2 = y-length*cos(theta);
 
  gfx_line( x, y, x2, y2 );

  // recursive calls
  for ( int i = 1; i <= 4; i++ )
  {
    fern( x+i*length*sin(theta)/4, y-i*length*cos(theta)/4, length/3, theta+3.14159/6 );
    fern( x+i*length*sin(theta)/4, y-i*length*cos(theta)/4, length/3, theta-3.14159/6 );
   }
}

void spirals( double x, double y, double radius, double theta ) // function to create the eighth fractal shape 
{
  gfx_color( 255, 204, 229 ); // sets color to pink

  if ( radius >= 400 ) { return; } // base case
  
  spiral( x, y, radius, 0.5, 0 ); // spiral drawing function

  // modify parameters
  radius = 1.1*radius;
  theta = theta-(3.14159/5);
  x = x+3*radius*cos(theta);
  y = y+3*radius*sin(theta);

  // recursive call 
  spirals( x, y, radius, theta );
}

void menu() // function to display the options of the program
{
  gfx_color( 255, 255, 255 );
  gfx_text( 335, 350, "PRESS 1 FOR SIERPINSKI TRIANGLE" );
  gfx_text( 335, 365, "PRESS 2 FOR SHRINKING SQUARES" );
  gfx_text( 335, 380, "PRESS 3 FOR SPIRAL SQUARES" );
  gfx_text( 335, 395, "PRESS 4 FOR CIRCULAR LACE" );
  gfx_text( 335, 410, "PRESS 5 FOR SNOWFLAKE" );
  gfx_text( 335, 425, "PRESS 6 FOR TREE" );
  gfx_text( 335, 440, "PRESS 7 FOR FERN" );
  gfx_text( 335, 455, "PRESS 8 FOR SPIRAL OF SPIRALS" );
  gfx_text( 335, 470, "PRESS 'm' FOR MENU" );
  gfx_text( 335, 485, "PRESS 'q' TO QUIT" );
}

