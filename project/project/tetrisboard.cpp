// Final Project
// tetrisboard.cpp
// Grace Milton and Roann Yanes

#include <iostream>
#include <unistd.h>
#include <cstdlib>
using namespace std;
#include "tetrisboard.h"
#include "gfxnew.h"

Tetrisboard::Tetrisboard() // Default constructor
{ orientation = 1; endgame = false; }

Tetrisboard::~Tetrisboard() { } // Destructor

int Tetrisboard::getx() // Returns x-coordinate of Tetris piece in array
{ return xcoord; }

int Tetrisboard::gety() // Returns y-coordinate of Tetris piece in array
{ return ycoord; }

int Tetrisboard::getRed() // Returns R value of color
{ return red; }

int Tetrisboard::getGreen() // Returns G value of color
{ return green; }

int Tetrisboard::getBlue() // Returns B value of color
{ return blue; }

int Tetrisboard::getShape() // Returns number 1-7 corresponding to shape of current piece 
{ return shape; }

int Tetrisboard::getOrientation() // Returns number 1-4 corresponding to orientation of current piece
{ return orientation; }

bool Tetrisboard::getEndgame() // Returns true boolean value when game over
{ return endgame; }

void Tetrisboard::setx(int x) // Sets x-coordinate of tetris piece in array
{ xcoord = x; }

void Tetrisboard::sety(int y) // Sets y-coordinate of tetris piece in array
{ ycoord = y; }

void Tetrisboard::setColor(int r, int g, int b) // Sets RGB color
{ red = r; green = g; blue = b; }

void Tetrisboard::setShape(int s) // Sets number 1-7 corresponding to shape
{ shape = s; }

void Tetrisboard::setOrientation(int o) // Sets number 1-4 corresponding to orientation
{ orientation = o; }

void Tetrisboard::setEndgame(bool truthvalue) // Sets boolean value to true when game over
{ endgame = truthvalue; }

void Tetrisboard::initialize() // Initializes arrays for game play and color tracker
{
   for (int i = 0; i < SIZE2; i++) {
      for (int j = 0; j < SIZE1; j++) {
         currentboard[j][i] = ' '; // Sets board to empty
         tempboard[j][i] = ' '; // Sets board to empty
         colorboard[j][i] = 0; // Sets board to black
         tempcolorboard[j][i] = 0; // Sets board to black
      }
   }
}

void Tetrisboard::drawLines() // Draws evenly spaced lines on board
{
   setColor(255,255,255); // Sets color to white
   gfx_color(red,green,blue);
   for (int i = 0; i < 300; i += 30) {
      for (int j = 0; j < 600; j += 30) {
         gfx_line(i,0,i,600); // Draws vertical lines
         gfx_line(0,j,300,j); // Draws horizontal lines
      }
   } 
}

void Tetrisboard::displayArray() // Displays array of Tetris board in terminal (useful for testing code)
{ 
   cout << " ";
   for (int k = 0; k < SIZE2; k++) { cout << "-"; } // Top border of board
   cout << endl;
   for (int i = 0; i < SIZE1; i++) {
      cout << "|"; // Right border of board
      for (int j = 0; j < SIZE2; j++) {
         cout << currentboard[i][j];
      }
      cout << "|" << endl; // Left border of board
   }
   cout << " "; 
   for (int m = 0; m < SIZE2; m++) { cout << "-"; } // Bottom border of board
   cout << endl;
}

void Tetrisboard::addblock(int x, int y) { // Adds a new Tetris piece to the board
   bool end = true;

   switch (shape) {
      // When a piece is added, checks to see if any other piece is intersecting it. If so, game ends
      case 1: // Checks I-piece
         for (int i = -1; i <= 2; i++) {
            if (currentboard[1][x+i] == 'X' && y == 0) { setEndgame(end); }
         }
         break;
      case 2: // Checks J-piece
          for (int i = -1; i <= 1; i++) {
             if (i == 1) { 
                if (currentboard[2][x+i] == 'X' && y == 0) { setEndgame(end); } 
             }
             else {
                if (currentboard[1][x+i] == 'X' && y == 0) { setEndgame(end); }
             }
          }
          break;
      case 3: // Checks L-piece
         for (int i = -1; i <= 1; i++) {
             if (i == -1) { 
                if (currentboard[2][x+i] == 'X' && y == 0) { setEndgame(end); }
             }
             else {
                if (currentboard[1][x+i] == 'X' && y == 0) { setEndgame(end); }
             }
          }
          break;
      case 4: // Checks O-piece
         for (int i = 0; i <= 1; i++) {
            if (currentboard[2][x+i] == 'X' && y == 0) { setEndgame(end); }
         }
         break;
      case 5: // Checks S-piece
         for (int i = -1; i <= 1; i++) {
            if (i == 1) { 
               if (currentboard[1][x+i] == 'X' && y == 0) { setEndgame(end); } 
            }
            else {
               if (currentboard[2][x+i] == 'X' && y == 0) { setEndgame(end); }
            }
         }
         break;
      case 6: // Checks T-piece
         for (int i = -1; i <= 1; i++) {
            if (i == 0) { 
               if (currentboard[2][x+i] == 'X' && y == 0) { setEndgame(end); } 
            }
            else {
               if (currentboard[1][x+i] == 'X' && y == 0) { setEndgame(end); } 
            }
         }
         break;
      case 7: // Checks Z-piece
         for (int i = -1; i <= 1; i++) {
            if (i == -1) { 
               if (currentboard[1][x+i] == 'X' && y == 0) { setEndgame(end); } 
            }
            else {
               if (currentboard[2][x+i] == 'X' && y == 0) { setEndgame(end); } 
            }
         }
         break;
   } 
   // Actually adds shapes
   switch (shape) {
      case 1: { // I-piece
         setColor(0,255,255); // Sets the color
         gfx_color(red,green,blue); // Sets the color to cyan
         for (int i = -1; i <= 2; i++) {
            if (orientation == 1 || orientation == 3) { // Based on the orientation of the shape
               currentboard[y][x+i] = 'X'; // Adds the piece on the array of the board
               colorboard[y][x+i] = 1; // Adds color of each block to color array
            } 
            else if (orientation == 2 || orientation == 4) { // Based on the orientation of the shape
               currentboard[y+i][x] = 'X';  // Adds the piece on the array of the board
               colorboard[y+i][x] = 1; // Adds color of each block to color array
            }
         }
         setx(x); // Sets its x-coordinate
         sety(y); // Sets its y-coordinate
         if (orientation == 1 || orientation == 3) { // Based on the orientation
            XPoint mypts[] = {{30*x-30,30*y},{30*x+90,30*y},{30*x+90,30*y+30},{30*x-30,30*y+30}}; // Draws the outline of the I-piece
            gfx_fill_polygon(mypts,4); // Fills in the outline of the piece
         }
         else if (orientation == 2 || orientation == 4) { // Based on thr orientation
            XPoint mypts[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y+90},{30*x,30*y+90}}; // Draws the outline of the I-piece
            gfx_fill_polygon(mypts,4); // Fills in the outline of the piece
         }
         break;
      }
      case 2: // J-piece
      {   
         setColor(0,0,255); // Sets the color
         gfx_color(red,green,blue); // Sets the color to blue
         for (int i = -1; i <= 1; i++) {
            if (orientation == 1) { // Based on the orientation
               currentboard[y][x+i] = 'X'; // Adds the piece to the array of the board
               colorboard[y][x+i] = 2; // Adds color of each block to color array
               if (i == 1) { currentboard[y+1][x+i] = 'X'; colorboard[y+1][x+i] = 2; } // Adds the piece to the array of the board and color of block to color board
            }
            else if (orientation == 2) { // Based on the orientation
               currentboard[y+i][x] = 'X'; // Adds the piece to the array of the board
               colorboard[y+i][x] = 2; // Adds color of each block to color array
               if (i == 1) { currentboard[y+i][x-1] = 'X'; colorboard[y+i][x-1] = 2; } // Adds the piece to the array of the board and color of block to color board
            }
            else if (orientation == 3) { // Based on the orientation
               currentboard[y][x+i] = 'X'; // Adds the piece to the array of the board
               colorboard[y][x+i] = 2; // Adds color of each block to color array
               if (i == -1) { currentboard[y-1][x+i] = 'X'; colorboard[y-1][x+i] = 2;} // Adds the piece to the array of the board and color of block to color board
            }
            else if (orientation == 4) { // Based on the orientation
               currentboard[y+i][x] = 'X'; // Adds the piece to the array of the board
               colorboard[y+i][x] = 2; // Adds color of each block to color array
               if (i == -1) { currentboard[y+i][x+1] = 'X'; colorboard[y+i][x+1] = 2; } // Adds the piece to the array of the board and color of block to color board
            }
         }
         setx(x); // Sets its x-coordinate
         sety(y); // Sets its y-coordinate
         switch (orientation) { // Based on the orientation
            case 1: {
               XPoint mypts2[] = {{30*x-30,30*y},{30*x+60,30*y},{30*x+60,30*y+60},{30*x+30,30*y+60},{30*x+30,30*y+30},{30*x-30,30*y+30}}; // Draws the outline of the J-piece
               gfx_fill_polygon(mypts2,6); // Fills in the piece
               break;
            }
            case 2: {
               XPoint mypts2[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y+60},{30*x-30,30*y+60},{30*x-30,30*y+30},{30*x,30*y+30}}; // Draws the outline of the J-piece
               gfx_fill_polygon(mypts2,6); // Fills in the piece
               break;
            }
            case 3: {
               XPoint mypts2[] = {{30*x-30,30*y-30},{30*x,30*y-30},{30*x,30*y},{30*x+60,30*y},{30*x+60,30*y+30},{30*x-30,30*y+30}}; // Draws the outline of the J-piece
               gfx_fill_polygon(mypts2,6); // Fills in the piece
               break;
            }
            case 4: {
               XPoint mypts2[] = {{30*x,30*y-30},{30*x+60,30*y-30},{30*x+60,30*y},{30*x+30,30*y},{30*x+30,30*y+60},{30*x,30*y+60}}; // Draws the ouline of the J-piece
               gfx_fill_polygon(mypts2,6); // Fills in the piece
               break;
            }
         }
         break;
      }
      case 3: { // L-piece
         setColor(255,128,0); // Sets the color
         gfx_color(red,green,blue); // Sets the color to orange
         for (int i = -1; i <= 1; i++) {
            if (orientation == 1) { // Based on the orientation
               currentboard[y][x+i] = 'X'; // Adds the piece to the array of the board
               colorboard[y][x+i] = 3; // Adds color of each block to color array
               if (i == -1) { currentboard[y+1][x+i] = 'X'; colorboard[y+1][x+i] = 3; } // Adds the piece to the array of the board and color of block to color board
            }
            else if (orientation == 2) {  // Based on the orientation
               currentboard[y+i][x] = 'X'; // Adds the piece to the array of the board
               colorboard[y+i][x] = 3; // Adds color of each block to color array
               if (i == -1) { currentboard[y+i][x-1] = 'X'; colorboard[y+i][x-1] = 3; } // Adds the piece to the array of the board and color of block to color board
            }
            else if (orientation == 3) { // Based on the orientation
               currentboard[y][x+i] = 'X'; // Adds the piece to the array of the board
               colorboard[y][x+i] = 3; // Adds color of each block to color array 
               if (i == 1) { currentboard[y-1][x+i] = 'X'; colorboard[y-1][x+i] = 3; } // Adds the piece to the array of the board and color of block to color board
            }
            else if (orientation == 4) { // Based on the orientation
               currentboard[y+i][x] = 'X'; // Adds the piece to the array of the board
               colorboard[y+i][x] = 3; // Adds color of each block to color array
               if (i == 1) { currentboard[y+i][x+1] = 'X'; colorboard[y+i][x+1] = 3;} // Adds the piece to the array of the board and color of block to color board
            }
         }
         setx(x); // Sets its x-coordinate
         sety(y); // Sets its y-coordinate
         switch (orientation) { // Based on the orientation
            case 1: {
               XPoint mypts3[] = {{30*x-30,30*y},{30*x+60,30*y},{30*x+60,30*y+30},{30*x,30*y+30},{30*x,30*y+60},{30*x-30,30*y+60}}; // Draws the outline of the L-piece
               gfx_fill_polygon(mypts3,6); // Fills in the piece
               break;
            }
            case 2: {
               XPoint mypts3[] = {{30*x-30,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y+60},{30*x,30*y+60},{30*x,30*y},{30*x-30,30*y}}; // Draws the outline of the L-piece
               gfx_fill_polygon(mypts3,6); // Fills in the piece
               break;
            }
            case 3: {
               XPoint mypts3[] = {{30*x+30,30*y-30},{30*x+60,30*y-30},{30*x+60,30*y+30},{30*x-30,30*y+30},{30*x-30,30*y},{30*x+30,30*y}}; // Draws the outline of the L-piece
               gfx_fill_polygon(mypts3,6); // Fills in the piece
               break;
            }
            case 4: {
               XPoint mypts3[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y+30},{30*x+60,30*y+30},{30*x+60,30*y+60},{30*x,30*y+60}}; // Draws the outline of the L-piece
               gfx_fill_polygon(mypts3,6); // Fills in the piece
               break;
            }
         }
         break;
      }
      case 4: { // O-piece
         setColor(255,255,0); // Sets the color
         gfx_color(red,green,blue); // Sets the color to yellow
         currentboard[y][x] = 'X'; // Adds the piece to the array of the board
         colorboard[y][x] = 4; // Adds color of each block to color array
         currentboard[y][x+1] = 'X'; // Adds the piece to the array of the board
         colorboard[y][x+1] = 4; // Sets its color in the board
         currentboard[y+1][x] = 'X'; // Adds the piece to the array of the board
         colorboard[y+1][x] = 4; // Set its color on the board
         currentboard[y+1][x+1] = 'X'; // Adds the piece to the array of the board
         colorboard[y+1][x+1] = 4; // Adds color of each block to color array
         setx(x); // Sets its x-coordinate
         sety(y); // Sets its y-coordinate
         XPoint mypts4[] = {{30*x,30*y},{30*x+60,30*y},{30*x+60,30*y+60},{30*x,30*y+60}}; // Draws the outline of the O-piece
         gfx_fill_polygon(mypts4,4); // Fills in the piece
         break;
      }
      case 5: { // S-piece
         setColor(0,255,0); // Sets the color
         gfx_color(red,green,blue); // Sets the color to green
         if (orientation == 1 || orientation == 3) { // Based on the orientation
            currentboard[y][x] = 'X'; // Adds the piece to the array of the board
            colorboard[y][x] = 5; // Adds color of each block to color array
            currentboard[y][x+1] = 'X'; // Adds the piece to the array of the board
            colorboard[y][x+1] = 5; // Adds color of each block to color array
            currentboard[y+1][x-1] = 'X'; // Adds the piece to the array of the board
            colorboard[y+1][x-1] = 5; // Adds color of each block to color array
            currentboard[y+1][x] = 'X'; // Adds the piece to the array of the board
            colorboard[y+1][x] = 5; // Adds color of each block to color array
         }
         else if (orientation == 2 || orientation == 4) { // Based on the orientation
            currentboard[y-1][x-1] = 'X'; // Adds the piece to the array of the board
            colorboard[y-1][x-1] = 5; // Adds color of each block to color array
            currentboard[y][x-1] = 'X'; // Adds the piece to the array of the board
            colorboard[y][x-1] = 5; // Adds color of each block to color array
            currentboard[y][x] = 'X'; // Adds the piece to the array of the board
            colorboard[y][x] = 5; // Adds color of each block to color array
            currentboard[y+1][x] = 'X'; // Adds the piece to the array of the board
            colorboard[y+1][x] = 5; // Adds color of each block to color array
         }
         setx(x); // Sets its x-coordinate
         sety(y); // Sets its y-coordinate
         if (orientation == 1 || orientation == 3) { // Based on the orientation
            XPoint mypts5[] = {{30*x,30*y},{30*x+60,30*y},{30*x+60,30*y+30},{30*x+30,30*y+30},{30*x+30,30*y+60},{30*x-30,30*y+60},{30*x-30,30*y+30},{30*x,30*y+30}}; // Draws the outline of the S-piece
            gfx_fill_polygon(mypts5,8); // Fills in the piece
         }
         else if (orientation == 2 || orientation == 4) { // Based on the orientation
            XPoint mypts5[] = {{30*x-30,30*y-30},{30*x,30*y-30},{30*x,30*y},{30*x+30,30*y},{30*x+30,30*y+60},{30*x,30*y+60},{30*x,30*y+30},{30*x-30,30*y+30}}; // Draws the outline of the S-piece
            gfx_fill_polygon(mypts5,8); // Fills in the piece
         }
         break;
      }
      case 6: {  // T-piece
         setColor(128,0,255); // Sets the color
         gfx_color(red,green,blue); // Sets the color to purple
         for (int i = -1; i <= 1; i++) {
            if (orientation == 1) { // Based on the orientation
               currentboard[y][x+i] = 'X'; // Adds the piece to the array of the board
               colorboard[y][x+i] = 6; // Adds color of each block to color array
               if (i == 0) { currentboard[y+1][x+i] = 'X'; colorboard[y+1][x+i] = 6; } // Adds the piece to the array of the board and color of block to color board
            }
            else if (orientation == 2) { // Based on the orientation
               currentboard[y+i][x] = 'X'; // Adds the piece to the array of the board
               colorboard[y+i][x] = 6; // Adds color of each block to color array
               if (i == 0) { currentboard[y+i][x-1] = 'X'; colorboard[y+i][x-1] = 6; } // Adds the piece to the array of the board and color of block to color board
            }
            else if (orientation == 3) { // Based on the orientation
               currentboard[y][x+i] = 'X'; // Adds the piece to the array of the board
               colorboard[y][x+i] = 6; // Adds color of each block to color array
               if (i == 0) { currentboard[y-1][x+i] = 'X'; colorboard[y-1][x+i] = 6; } // Adds the piece to the array of the board and color of block to color board
            }
            else if (orientation == 4) { // Based on the orientation 
               currentboard[y+i][x] = 'X'; // Adds the piece to the array of the board
               colorboard[y+i][x] = 6; // Adds color of each block to color array
               if (i == 0) { currentboard[y+i][x+1] = 'X'; colorboard[y+i][x+1] = 6; } // Adds the piece to the array of the board and color of block to color board
            }
         }
         setx(x); // Sets its x-coordinate
         sety(y); // Sets its y-coordinate
         switch (orientation) { // Based on the orientation
            case 1: {
               XPoint mypts6[] = {{30*x-30,30*y},{30*x+60,30*y},{30*x+60,30*y+30},{30*x+30,30*y+30},{30*x+30,30*y+60},{30*x,30*y+60},{30*x,30*y+30},{30*x-30,30*y+30}}; // Draws the outline of the S-piece
               gfx_fill_polygon(mypts6,8); // Fills in the piece
               break;
            }
            case 2: {
               XPoint mypts6[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y+60},{30*x,30*y+60},{30*x,30*y+30},{30*x-30,30*y+30},{30*x-30,30*y},{30*x,30*y}}; // Draws the outline of the S-piece
               gfx_fill_polygon(mypts6,8); // Fills in the piece
               break;
            }
            case 3: {
               XPoint mypts6[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y},{30*x+60,30*y},{30*x+60,30*y+30},{30*x-30,30*y+30},{30*x-30,30*y},{30*x,30*y}}; // Draws the outline of the S-piece
               gfx_fill_polygon(mypts6,8); // Fills in the piece
               break;
            }
            case 4: {
               XPoint mypts6[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y},{30*x+60,30*y},{30*x+60,30*y+30},{30*x+30,30*y+30},{30*x+30,30*y+60},{30*x,30*y+60}}; // Draws the outline of the S-piece
               gfx_fill_polygon(mypts6,8); // Fills in the piece
               break;
            }
         }
         break;
      }
      case 7: { // Z-piece
         setColor(255,0,0); // Sets the color
         gfx_color(red,green,blue); // Sets the color to red
         if (orientation == 1 || orientation == 3) { // Based on the orientation
            currentboard[y+1][x+1] = 'X'; // Adds the piece to the array of the board
            colorboard[y+1][x+1] = 7; // Adds color of each block to color array
            currentboard[y][x] = 'X'; // Adds the piece to the array of the board
            colorboard[y][x] = 7; // Adds color of each block to color array
            currentboard[y+1][x] = 'X'; // Adds the piece to the array of the board
            colorboard[y+1][x] = 7; // Adds color of each block to color array
            currentboard[y][x-1] = 'X'; // Adds the piece to the array of the board
            colorboard[y][x-1] = 7; // Adds color of each block to color array
         }
         else if (orientation == 2 || orientation == 4) { // Based on the orientation
            currentboard[y-1][x] = 'X'; // Adds the piece to the array of the board
            colorboard[y-1][x] = 7; // Adds color of each block to color array
            currentboard[y][x-1] = 'X'; // Adds the piece to the array of the board
            colorboard[y][x-1] = 7; // Adds color of each block to color array
            currentboard[y][x] = 'X'; // Adds the piece to the array of the board
            colorboard[y][x] = 7; // Adds color of each block to color array
            currentboard[y+1][x-1] = 'X'; // Adds the piece to the array of the board
            colorboard[y+1][x-1] = 7; // Adds color of each block to color array
         }
         setx(x); // Sets its x-coordinate
         sety(y); // Sets its y-coordinate
         if (orientation == 1 || orientation == 3) { // Based on the orientation
            XPoint mypts7[] = {{30*x-30,30*y},{30*x+30,30*y},{30*x+30,30*y+30},{30*x+60,30*y+30},{30*x+60,30*y+60},{30*x,30*y+60},{30*x,30*y+30},{30*x-30,30*y+30}}; // Draws the outline of the Z-piece
            gfx_fill_polygon(mypts7,8); // Fills in the piece 
         }
         else if (orientation == 2 || orientation == 4) { // Based on the orientation
            XPoint mypts7[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y+30},{30*x,30*y+30},{30*x,30*y+60},{30*x-30,30*y+60},{30*x-30,30*y},{30*x,30*y}}; // Draws the outline of the Z-piece
            gfx_fill_polygon(mypts7,8); // Fills in the piece
         }
         break;
      }     
   }  
}

void Tetrisboard::removeblock(int x, int y) // Removes the pieces when rotating and falling by setting them to black 
{
   setColor(0,0,0); // Sets the color to black
   gfx_flush(); // Flushes output to graphics window
   gfx_color(red,green,blue); // Sets the color to black
   switch (shape) {
      case 1: { // I-piece   
         for (int i = -1; i <= 2; i++) {
            if (orientation == 1 || orientation == 3) { // Based on the orientation of the piece
               currentboard[y][x+i] = ' '; // Removes the piece from the board
               colorboard[y][x+i] = 0; // Sets the color to black on the board
            }
            else if (orientation == 2 || orientation == 4) { // Based on the orientation
               currentboard[y+i][x] = ' '; // Removes the piece from the board
               colorboard[y+i][x] = 0; // Sets the color to black on the board
            }
         }
         if (orientation == 1 || orientation == 3) { // Based on the orientation of the piece
            XPoint mypts[] = {{30*x-30,30*y},{30*x+90,30*y},{30*x+90,30*y+30},{30*x-30,30*y+30}}; // Draws the outline of the I-piece
            gfx_fill_polygon(mypts,4); // Fills in the piece
         }
         else if (orientation == 2 || orientation == 4) { // Based on the orientation of the piece
            XPoint mypts[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y+90},{30*x,30*y+90}}; // Draws the outline of the I-piece
            gfx_fill_polygon(mypts,4); // Fills in the piece
         }
         break;
      }
      case 2: { // J-piece
         for (int i = -1; i <= 1; i++) {
            if (orientation == 1) { // Based on the orientation of the piece
               currentboard[y][x+i] = ' '; // Removes the piece from the board
               colorboard[y][x+i] = 0; // Sets the color to black on the board
               if (i == 1) { currentboard[y+1][x+i] = ' '; colorboard[y+1][x+i] = 0; } // Removes the piece from the array of the board and sets color to black in color board
            }
            else if (orientation == 2) { // Based on the orientation
               currentboard[y+i][x] = ' '; // Removes the piece from the board
               colorboard[y+i][x] = 0; // Sets the color to black on the board
               if (i == 1) { currentboard[y+i][x-1] = ' '; colorboard[y+i][x-1] = 0; } // Removes the piece from the array of the board and sets color to black in color board
            }
            else if (orientation == 3) { // Based on the orientation
               currentboard[y][x+i] = ' '; // Removes the piece from the board
               colorboard[y][x+i] = 0; // Sets the color to black on the board
               if (i == -1) { currentboard[y-1][x+i] = ' '; colorboard[y-1][x+i] = 0; } // Removes the piece from the array of the board and sets color to balck in color board
            }
            else if (orientation == 4) { // Based on the orientation
               currentboard[y+i][x] = ' '; // Removes the piece from the board
               colorboard[y+i][x] = 0; // Sets the color to black on the board
               if (i == -1) { currentboard[y+i][x+1] = ' '; colorboard[y+i][x+1] = 0; } // Removes the piece from the array of the board and sets color to black in color board
            }
         }
         switch (orientation) { // Based on the orientation
            case 1: {
               XPoint mypts2[] = {{30*x-30,30*y},{30*x+60,30*y},{30*x+60,30*y+60},{30*x+30,30*y+60},{30*x+30,30*y+30},{30*x-30,30*y+30}}; // Draws the outline of the J-piece
               gfx_fill_polygon(mypts2,6); // Fills in the piece
               break;
            }
            case 2: {
               XPoint mypts2[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y+60},{30*x-30,30*y+60},{30*x-30,30*y+30},{30*x,30*y+30}}; // Draws the outline of the J-piece
               gfx_fill_polygon(mypts2,6); // Fills in the piece
               break;
            }
            case 3: {
               XPoint mypts2[] = {{30*x-30,30*y-30},{30*x,30*y-30},{30*x,30*y},{30*x+60,30*y},{30*x+60,30*y+30},{30*x-30,30*y+30}}; // Draws the outline of the J-piece
               gfx_fill_polygon(mypts2,6); // Fills in the piece
               break;
            }
            case 4: {
               XPoint mypts2[] = {{30*x,30*y-30},{30*x+60,30*y-30},{30*x+60,30*y},{30*x+30,30*y},{30*x+30,30*y+60},{30*x,30*y+60}}; // Draws the outline of the J-piece
               gfx_fill_polygon(mypts2,6); // Fills in the piece
               break;
            }
         }
         break; 
      }
      case 3: { // L-piece
         for (int i = -1; i <= 1; i++) {
            if (orientation == 1) {  // Based on the orientation
               currentboard[y][x+i] = ' '; // Removes the piece from the board
               colorboard[y][x+i] = 0; // Sets the color to black on the board
               if (i == -1) { currentboard[y+1][x+i] = ' '; colorboard[y+1][x+i] = 0; }
            }
            else if (orientation == 2) { // Based on the orientation
               currentboard[y+i][x] = ' '; // Removes the piece from the board
               colorboard[y+i][x] = 0; // Sets the color to black on the board
               if (i == -1) { currentboard[y+i][x-1] = ' '; colorboard[y+i][x-1] = 0; } // Removes the piece from the array of the board and sets color to black in color board
            }
            else if (orientation == 3) { // Based on the orientation
               currentboard[y][x+i] = ' '; // Removes the piece from the board
               colorboard[y][x+i] = 0; // Sets the color to black on the board
               if (i == 1) { currentboard[y-1][x+i] = ' '; colorboard[y-1][x+i] = 0; } // Removes the piece from the array of the board and sets color to black in color board
            }
            else if (orientation == 4) { // Based on the orientation
               currentboard[y+i][x] = ' '; // Removes the piece from the board
               colorboard[y+i][x] = 0; // Sets the color to black on the board
               if (i == 1) { currentboard[y+i][x+1] = ' '; colorboard[y+i][x+1] = 0; } // Removes the piece from the array of the board and sets color to black in color board
            }
         }
         switch (orientation){ // Based on the orientation
            case 1: {
               XPoint mypts3[] = {{30*x-30,30*y},{30*x+60,30*y},{30*x+60,30*y+30},{30*x,30*y+30},{30*x,30*y+60},{30*x-30,30*y+60}}; // Draws the outline of the L-piece
               gfx_fill_polygon(mypts3,6); // Fills in the piece
               break;
            }
            case 2: {
               XPoint mypts3[] = {{30*x-30,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y+60},{30*x,30*y+60},{30*x,30*y},{30*x-30,30*y}}; // Draws the outline of the L-piece
               gfx_fill_polygon(mypts3,6); // Fills in the piece
               break;
            }
            case 3: {
               XPoint mypts3[] = {{30*x+30,30*y-30},{30*x+60,30*y-30},{30*x+60,30*y+30},{30*x-30,30*y+30},{30*x-30,30*y},{30*x+30,30*y}}; // Draws the outline of the L-piece
               gfx_fill_polygon(mypts3,6); // Fills in the piece
               break;
            }
            case 4: {
               XPoint mypts3[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y+30},{30*x+60,30*y+30},{30*x+60,30*y+60},{30*x,30*y+60}}; // Draws the outline of the L-piece
               gfx_fill_polygon(mypts3,6); // Fills in the piece
               break;
            }
         }
         break;
      }
      case 4: { // O-piece 
         currentboard[y][x] = ' '; // Removes the piece from the board
         colorboard[y][x] = 0; // Sets the color to black on the board
         currentboard[y][x+1] = ' '; // Removes the piece from the board
         colorboard[y][x+1] = 0; // Sets the color to black on the board
         currentboard[y+1][x] = ' '; // Removes the piece from the board
         colorboard[y+1][x] = 0; // Sets the color to black on the board
         currentboard[y+1][x+1] = ' '; // Removes the piece from the board
         colorboard[y+1][x+1] = 0; // Sets the color to black on the board
         XPoint mypts4[] = {{30*x,30*y},{30*x+60,30*y},{30*x+60,30*y+60},{30*x,30*y+60}}; // Draws the outline of the O-piece
         gfx_fill_polygon(mypts4,4); // Fills in the piece
         break;
      }
      case 5: { // S-piece
         if (orientation == 1 || orientation == 3) { // Based on the orientation
            currentboard[y][x] = ' '; // Removes the piece from the board
            colorboard[y][x] = 0; // Sets the color to black on the board
            currentboard[y][x+1] = ' '; // Removes the piece from the board
            colorboard[y][x+1] = 0; // Sets the color to black on the board
            currentboard[y+1][x-1] = ' '; // Removes the piece from the board
            colorboard[y+1][x-1] = 0; // Sets the color to black on the board
            currentboard[y+1][x] = ' '; // Removes the piece from the board
            colorboard[y+1][x] = 0; // Sets the color to black on the board
         }
         else if (orientation == 2 || orientation == 4) { // Based on the orientation
            currentboard[y-1][x-1] = ' '; // Removes the piece from the board
            colorboard[y-1][x-1] = 0; // Sets the color to black on the board
            currentboard[y][x-1] = ' '; // Removes the piece from the board
            colorboard[y][x-1] = 0; // Sets the color to black on the board
            currentboard[y][x] = ' '; // Removes the piece from the board
            colorboard[y][x] = 0; // Sets the color to black on the board
            currentboard[y+1][x] = ' '; // Removes the piece from the board
            colorboard[y+1][x] = 0; // Sets the color to black on the board
         }
         if (orientation == 1 || orientation == 3) { // Based on the orientation
            XPoint mypts5[] = {{30*x,30*y},{30*x+60,30*y},{30*x+60,30*y+30},{30*x+30,30*y+30},{30*x+30,30*y+60},{30*x-30,30*y+60},{30*x-30,30*y+30},{30*x,30*y+30}}; // Draws the outline of the S-piece
            gfx_fill_polygon(mypts5,8); // Fills in the piece
         }
         else if (orientation == 2 || orientation == 4) { // Based on the orientation
            XPoint mypts5[] = {{30*x-30,30*y-30},{30*x,30*y-30},{30*x,30*y},{30*x+30,30*y},{30*x+30,30*y+60},{30*x,30*y+60},{30*x,30*y+30},{30*x-30,30*y+30}}; // Draws the outline of the S-piece
            gfx_fill_polygon(mypts5,8); // Fills in the piece
         }
         break;
      }
      case 6: {  // T-piece
         for (int i = -1; i <= 1; i++) {
            if (orientation == 1) { // Based on the orientation
               currentboard[y][x+i] = ' '; // Removes the piece from the board
               colorboard[y][x+i] = 0; // Sets the color to black on the board
               if (i == 0) { currentboard[y+1][x+i] = ' '; colorboard[y+1][x+i] = 0; } // Removes the piece from the array of the board and sets color to black in color board
            } 
            else if (orientation == 2) { // Based on the orientation
               currentboard[y+i][x] = ' '; // Removes the piece from the board
               colorboard[y+i][x] = 0; // Sets the color to black on the board
               if (i == 0) { currentboard[y+i][x-1] = ' '; colorboard[y+i][x-1] = 0; } // Removes the piece from the array of the board and sets color to black in color board
            }
            else if (orientation == 3) { // Based on the orientation
               currentboard[y][x+i] = ' '; // Removes the piece from the board
               colorboard[y][x+i] = 0; // Sets the color to black on the board
               if (i == 0) { currentboard[y-1][x+i] = ' '; colorboard[y-1][x+i] = 0; } // Removes the piece from the array of the board and sets color to black in color board
            }
            else if (orientation == 4) { // Based on the orientation
               currentboard[y+i][x] = ' '; // Removes the piece from the board
               colorboard[y+i][x] = 0; // Sets the color to black on the board
               if (i == 0) { currentboard[y+i][x+1] = ' '; colorboard[y+i][x+1] = 0; } // Removes the piece from the array of the board and sets color to black in color board
            }
         }
         switch (orientation) { // Based on the orientation
            case 1: {
               XPoint mypts6[] = {{30*x-30,30*y},{30*x+60,30*y},{30*x+60,30*y+30},{30*x+30,30*y+30},{30*x+30,30*y+60},{30*x,30*y+60},{30*x,30*y+30},{30*x-30,30*y+30}}; // Draws the outline of the T-piece
               gfx_fill_polygon(mypts6,8); // Fills in the piece
               break;
            }
            case 2: {
               XPoint mypts6[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y+60},{30*x,30*y+60},{30*x,30*y+30},{30*x-30,30*y+30},{30*x-30,30*y},{30*x,30*y}}; // Draws the outline of the T-piece
               gfx_fill_polygon(mypts6,8); // Fills in the piece
               break;
            }
            case 3: {
               XPoint mypts6[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y},{30*x+60,30*y},{30*x+60,30*y+30},{30*x-30,30*y+30},{30*x-30,30*y},{30*x,30*y}}; // Draws the outline of the T-piece
               gfx_fill_polygon(mypts6,8); // Fills in the piece
               break;
            }
            case 4: {
               XPoint mypts6[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y},{30*x+60,30*y},{30*x+60,30*y+30},{30*x+30,30*y+30},{30*x+30,30*y+60},{30*x,30*y+60}}; // Draws the outline of the T-piece
               gfx_fill_polygon(mypts6,8); // Fills in the piece
               break;
            }
         }
         break;
      }
      case 7: { // Z-piece
         if (orientation == 1 || orientation == 3) { // Based on the orientation
            currentboard[y+1][x+1] = ' '; // Removes the piece from the board
            colorboard[y+1][x+1] = 0; // Sets the color to black on the board
            currentboard[y][x] = ' '; // Removes the piece from the board
            colorboard[y][x] = 0; // Sets the color to black on the board
            currentboard[y+1][x] = ' '; // Removes the piece from the board
            colorboard[y+1][x] = 0; // Sets the color to black on the board
            currentboard[y][x-1] = ' '; // Removes the piece from the board
            colorboard[y][x-1] = 0; // Sets the color to black on the board
         }
         else if (orientation == 2 || orientation == 4) { // Based on the orientation
            currentboard[y-1][x] = ' '; // Removes the piece from the board
            colorboard[y-1][x] = 0; // Sets the color to black on the board
            currentboard[y][x-1] = ' '; // Removes the piece from the board
            colorboard[y][x-1] = 0; // Sets the color to black on the board
            currentboard[y][x] = ' '; // Removes the piece from the board
            colorboard[y][x] = 0; // Sets the color to black on the board
            currentboard[y+1][x-1] = ' '; // Removes the piece from the board
            colorboard[y+1][x-1] = 0; // Sets the color to black on the board
         }
         if (orientation == 1 || orientation == 3) { // Based on the orientation
            XPoint mypts7[] = {{30*x-30,30*y},{30*x+30,30*y},{30*x+30,30*y+30},{30*x+60,30*y+30},{30*x+60,30*y+60},{30*x,30*y+60},{30*x,30*y+30},{30*x-30,30*y+30}}; // Draws the outline of the Z-piece
            gfx_fill_polygon(mypts7,8);  // Fills in the piece
         }
         else if (orientation == 2 || orientation == 4) { // Based on the orientation
            XPoint mypts7[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y+30},{30*x,30*y+30},{30*x,30*y+60},{30*x-30,30*y+60},{30*x-30,30*y},{30*x,30*y}}; // Draws the outline of the Z-piece
            gfx_fill_polygon(mypts7,8); 
         }
         break;
      }
   }
}

void Tetrisboard::fall() // Shifts the current Tetris piece down to make it appear as though it is falling
{
   int x, y;
   x = getx(); // Gets the x-coordinate of the piece
   y = gety(); // Gets the y-coordinate of the piece
   addblock(x,y); // Adds the current piece at a certain location
   usleep(80000); // Pauses briefly
   gfx_flush(); // Flushes output to graphics window
   removeblock(x,y); // Removes the current piece at the same location
   gfx_flush(); // Flushes output to graphics window
   addblock(x, y+1); // Adds the current piece at the location below its previous location
   gfx_flush(); // Flushes output to graphics window
   sety(y+1); // Sets new y-coordinate
}

void Tetrisboard::moveLeft() // Shifts the current Tetris piece left
{
   int x, y, leftbound;
   bool open = true;
   x = getx();
   y = gety();
 
   // Determines if shape is able to move based on a piece or edge of board being next to it
   switch (shape) {
      case 1: // I-piece
         if (orientation == 1 || orientation == 3) { // Based on the orientation of the piece
            if (currentboard[y][x-2] == 'X') { open = false; } // Checks if there is a piece already to the left
            leftbound = 2; // Left boundary to prevent the piece from going off the board
         }
         else if (orientation == 2 || orientation == 4) { // Based on the orientation of the piece
            if (currentboard[y][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left
            leftbound = 1; // Left boundary to prevent the piece from going off the board
         }
         break;
      case 2: // J-piece
         switch (orientation) { // Based on the orientation
            case 1:  
               if (currentboard[y][x-2] == 'X' || currentboard[y+1][x] == 'X') { open = false; } // Checks if there is a piece already to the left
               leftbound = 2; // Left boundary to prevent the piece from going off the board
               break;
            case 2:
               if (currentboard[y-1][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left
               else if (currentboard[y][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left               
               else if (currentboard[y+1][x-2] == 'X') { open = false; } // Checks if there is a piece already to the left
               leftbound = 2; // Left boundary to prevent the piece from going off the board
               break;
            case 3:
               if (currentboard[y][x-2] == 'X' || currentboard[y-1][x-2] == 'X') { open = false; } // Checks if there is a piece already to the left       
               leftbound = 2; // Left boundary to prevent the piece from going off the board
               break;
            case 4:
               if (currentboard[y-1][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left
               else if (currentboard[y][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left                 
               else if (currentboard[y+1][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left 
               leftbound = 1; // Left boundary to prevent the piece from going off the board
               break;
         }
         break;
      case 3: // L-piece
         switch (orientation) { // Based on the orientation
            case 1:
               if (currentboard[y][x-2] == 'X' || currentboard[y+1][x-2] == 'X') { open = false; } // Checks if there is a piece already to the left
               leftbound = 2; // Left boundary to prevent the piece from going off the board
               break;
            case 2:
               if (currentboard[y-1][x-2] == 'X') { open = false; } // Checks if there is a piece already to the left
               else if (currentboard[y][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left
               else if (currentboard[y+1][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left
               leftbound = 2; // Left boundary to prevent the piece from going off the board
               break;
            case 3:
               if (currentboard[y][x-2] == 'X' || currentboard[y-1][x] == 'X') { open = false; } // Checks if there is a piece already to the left
               leftbound = 2; // Left boundary to prevent the piece from going off the board
               break;
            case 4:
               if (currentboard[y-1][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left
               else if (currentboard[y][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left
               else if (currentboard[y+1][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left
               leftbound = 1; // Left boundary to prevent the piece from going off the board
               break;
         }
         break;
      case 4: // O-piece
         if (currentboard[y][x-1] == 'X' || currentboard[y+1][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left
         leftbound = 1; // Left boundary to prevent the piece from going off the board
         break;
      case 5: // S-piece
         if (orientation == 1 || orientation == 3) {
            if (currentboard[y][x-1] == 'X' || currentboard[y+1][x-2] == 'X') { open = false; } // Checks if there is a piece already to the left
         }
         if (orientation == 2 || orientation == 4) {
            if (currentboard[y-1][x-2] == 'X') { open = false; } // Checks if there is a piece already to the left
            else if (currentboard[y][x-2] == 'X') { open = false; } // Checks if there is a piece already to the left
            else if (currentboard[y+1][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left 
         }
         leftbound = 2; // Left boundary to prevent the piece from going off the board
         break;
      case 6: // T-piece
         switch (orientation) { // Based on the orientation
            case 1:
               if (currentboard[y][x-2] == 'X' || currentboard[y+1][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left
               leftbound = 2; // Left boundary to prevent the piece from going off the board
               break;
            case 2:
               if (currentboard[y-1][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left
               else if (currentboard[y][x-2] == 'X') { open = false; } // Checks if there is a piece already to the left
               else if (currentboard[y+1][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left
               leftbound = 2; // Left boundary to prevent the piece from going off the board
               break;
            case 3:
               if (currentboard[y-1][x-1] == 'X' || currentboard[y][x-2] == 'X') { open = false; } // Checks if there is a piece already to the left
               leftbound = 2; // Left boundary to prevent the piece from going off the board
               break;
            case 4:
               if (currentboard[y-1][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left
               else if (currentboard[y][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left
               else if (currentboard[y+1][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left
               leftbound = 1; // Left boundary to prevent the piece from going off the board
               break;
         }
         break;
      case 7: // Z-piece
         if (orientation == 1 || orientation == 3) { // Based on the orientation
            if (currentboard[y][x-2] == 'X' || currentboard[y+1][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left
         }
         if (orientation == 2 || orientation == 4) { // Based on the orientation
            if (currentboard[y-1][x-1] == 'X') { open = false; } // Checks if there is a piece already to the left
            else if (currentboard[y][x-2] == 'X') { open = false; } // Checks if there is a piece already to the left
            else if (currentboard[y+1][x-2] == 'X') { open = false; } // Checks if there is a piece already to the left 
         }
         leftbound = 2; // Left boundary to prevent the piece from going off the board
         break;
   }
   if ((x >= leftbound) && (open)) { // Piece is added if it will not go out of bounds and the space is clear
      addblock(x,y); // Adds the piece to the board
      usleep(80000);
      gfx_flush(); // Flushes the output to graphics window
      removeblock(x,y); // Removes the piece from the board
      addblock(x-1,y); // Places the piece on the board one space left of its previous position
      setx(x-1); // Sets new x-coordinate
   }
}

void Tetrisboard::moveRight() // Shifts the current Tetris piece right
{
   int rightbound, x, y;
   bool open = true;
   x = getx();
   y = gety();
   
   // Determines if piece can move right by checking if there is another piece or the edge of the board to its right
   switch (shape) {
      case 1: // I-piece
         if (orientation == 1 || orientation == 3) { // Based on the orientation
            if (currentboard[y][x+3] == 'X') { open = false; } // Checks if there is a piece already to the right
            rightbound = 6; // Right boundary to prevent the piece from going off the board
         }
         if (orientation == 2 || orientation == 4) {
            if (currentboard[y][x+1] == 'X') { open = false; } // Checks if there is a piece already to the right
            rightbound = 8; // Right boundary to prevent the piece from going off the board
         }
         break;
      case 2: // J-piece
         switch (orientation) { // Based on the orientation
            case 1:
               if (currentboard[y][x+2] == 'X' || currentboard[y+1][x+2] == 'X') { open = false; } // Checks if there is a piece already to the right
               rightbound = 7; // Right boundary to prevent the piece from going off the board
               break;
            case 2:
               for (int i = -1; i <= 1; i++) {
                  if (currentboard[y+i][x+1] == 'X') { open = false; } // Checks if there is a piece already to the right
               }
               rightbound = 8; // Right boundary to prevent the piece from going off the board
               break;
            case 3:
               if (currentboard[y-1][x] == 'X' || currentboard[y][x+2] == 'X') { open = false; } // Checks if there is a piece already to the right       
               rightbound = 7; // Right boundary to prevent the piece from going off the board
               break;
            case 4:
               if (currentboard[y-1][x+2] == 'X') { open = false; } // Checks if there is a piece already to the right
               else if (currentboard[y][x+1] == 'X') { open = false; } // Checks if there is a piece already to the right    
               else if (currentboard[y+1][x+1] == 'X') { open = false; } // Checks if there is a piece already to the right    
               rightbound = 7; // Right boundary to prevent the piece from going off the board
               break;
         }         
         break;
      case 3: // L-piece
         switch (orientation) { // Based on the orientation
           case 1:
               if (currentboard[y][x+2] == 'X' || currentboard[y+1][x] == 'X') { open = false; } // Checks if there is a piece already to the right
               rightbound = 7; // Right boundary to prevent the piece from going off the board
               break;
            case 2:
               for (int i = -1; i <= 1; i++) {
                  if (currentboard[y+i][x+1] == 'X') { open = false; } // Checks if there is a piece already to the right
               }
               rightbound = 8; // Right boundary to prevent the piece from going off the board
               break;
            case 3:
               if (currentboard[y-1][x+2] == 'X' || currentboard[y][x+2] == 'X') { open = false; } // Checks if there is a piece already to the right
               rightbound = 7; // Right boundary to prevent the piece from going off the board
               break;
            case 4:
               if (currentboard[y-1][x+1] == 'X') { open = false; } // Checks if there is a piece already to the right
               else if (currentboard[y][x+1] == 'X') { open = false; } // Checks if there is a piece already to the right
               else if (currentboard[y+1][x+2] == 'X') { open = false; } // Checks if there is a piece already to the right
               rightbound = 7; // Right boundary to prevent the piece from going off the board
               break;
         }
         break;
      case 4: // O-piece
         if (currentboard[y][x+2] == 'X' || currentboard[y+1][x+2] == 'X') { open = false; } // Checks if there is a piece already to the right
         rightbound = 7; // Right boundary to prevent the piece from going off the board
         break;
      case 5: // S-piece
         if (orientation == 1 || orientation == 3) { // Based on the orientation
            if (currentboard[y][x+2] == 'X' || currentboard[y+1][x+1] == 'X') { open = false; } // Checks if there is a piece already to the right
            rightbound = 7; // Right boundary to prevent the piece from going off the board
         }
         if (orientation == 2 || orientation == 4) { // Based on the orientation
            if (currentboard[y-1][x] == 'X') { open = false; } // Checks if there is a piece already to the right
            else if (currentboard[y][x+1] == 'X') { open = false; } // Checks if there is a piece already to the right
            else if (currentboard[y+1][x+1] == 'X') { open = false; } // Checks if there is a piece already to the right 
            rightbound = 8; // Right boundary to prevent the piece from going off the board
         }
         break;
      case 6: // T-piece
         switch (orientation) { // Based on the orientation
            case 1:
               if (currentboard[y][x+2] == 'X' || currentboard[y+1][x+1] == 'X') { open = false; } // Checks if there is a piece already to the right
               rightbound = 7; // Right boundary to prevent the piece from going off the board
               break;
            case 2:
               for (int i = -1; i <= 1; i++) {
                  if (currentboard[y+i][x+1] == 'X') { open = false; } // Checks if there is a piece already to the right
               }
               rightbound = 8; // Right boundary to prevent the piece from going off the board
               break;
            case 3:
               if (currentboard[y-1][x+1] == 'X' || currentboard[y][x+2] == 'X') { open = false; } // Checks if there is a piece already to the right
               rightbound = 7; // Right boundary to prevent the piece from going off the board
               break;
            case 4:
               if (currentboard[y-1][x+1] == 'X') { open = false; } // Checks if there is a piece already to the right
               else if (currentboard[y][x+2] == 'X') { open = false; } // Checks if there is a piece already to the right
               else if (currentboard[y+1][x+1] == 'X') { open = false; } // Checks if there is a piece already to the right
               rightbound = 7; // Right boundary to prevent the piece from going off the board
               break;
         }
         break;
      case 7: // Z-piece
         if (orientation == 1 || orientation == 3) { // Based on the orientation
            if (currentboard[y][x+1] == 'X' || currentboard[y+1][x+2] == 'X') { open = false; } // Checks if there is a piece already to the right
            rightbound = 7; // Right boundary to prevent the piece from going off the board
         }
         if (orientation == 2 || orientation == 4) { // Based on the orientation
            if (currentboard[y-1][x+1] == 'X') { open = false; } // Checks if there is a piece already to the right
            else if (currentboard[y][x+1] == 'X') { open = false; } // Checks if there is a piece already to the right
            else if (currentboard[y+1][x] == 'X') { open = false; } // Checks if there is a piece already to the right 
            rightbound = 8; // Right boundary to prevent the piece from going off the board
         }
         break;
   }
   if ((x <= rightbound) && (open)) { // Piece is added if it will not go out of bounds and the space is clear 
      addblock(x,y); // Adds the piece to the board
      usleep(80000);
      gfx_flush(); // Flushes output to the graphics window
      removeblock(x,y); // Removes the piece from the board
      addblock(x+1,y); // Places the piece on the board one space right of its previous position
      setx(x+1); // Sets new x-coordinate
   }
}

bool Tetrisboard::openRotate() // Checks to see if there is space for the current piece to rotate
{
   int x = getx();
   int y = gety();

   switch (shape) {
      case 1: { // I-piece
         if (x < 1 || x > 7) { return false; } // Prevents it from going out of bounds
         else if (orientation == 1 || orientation == 3) { // Based on the orientation of the current piece
            // Checks the areas above and below the piece to see if there is room for the piece to rotate without colliding with other pieces
            if (currentboard[y-1][x] == 'X') { return false; }
            else if (currentboard[y+1][x] == 'X') { return false; }
            else if (currentboard[y+2][x] == 'X') {return false; }
            else { return true; }
         }
         else if (orientation == 2 || orientation == 4) { // Based on the orientation of the current piece
            // Checks the areas left and right of the piece to see if there is room for the piece to rotate without colliding with other pieces
            if (currentboard[y][x-1] == 'X') { return false; }
            else if (currentboard[y][x+1] == 'X') { return false; }
            else if (currentboard[y][x+2] == 'X') { return false; } 
            else { return true; }
         }
         break;
      }
      case 2: { // J-piece 
         switch (orientation) {
            case 1: // Based on the orientation of the current piece
               // Checks the areas around the piece to see if there is room for the piece to rotate without colliding with other pieces
               if (currentboard[y-1][x] == 'X') { return false; }
               else if (currentboard[y+1][x] == 'X') { return false; }
               else if (currentboard[y+1][x-1] == 'X') { return false; }
               else { return true; }
               break;
            case 2: // Based on the orientation of the current piece
               // Checks the areas around the piece to see if there is room for the piece to rotate without colliding with other piece
               if (x < 1 || x > 8) { return false; } // Prevents the piece from going out of bounds
               else if (currentboard[y-1][x-1] == 'X') { return false; }
               else if (currentboard[y][x-1] == 'X') { return false; }
               else if (currentboard[y][x+1] == 'X') { return false; }
               else { return true; }
               break;
            case 3: // Based on the orientation of the current piece
              // Checks the areas around the piece to see if there is room for the piece to rotate without colliding with other pieces
              if (currentboard[y-1][x] == 'X') { return false; }
              else if (currentboard[y-1][x+1] == 'X') { return false; }
              else if (currentboard[y+1][x] == 'X') { return false; }
              else { return true; }
              break;
            case 4: // Based on the orientation of the current piece
               if (x < 0 || x > 7) { return false; } // Prevents the piece from going out of bounds
               // Checks the areas around the piece to see if there is room for the piece to rotate without colliding with other pieces
               else if (currentboard[y][x-1] == 'X') { return false; }
               else if (currentboard[y][x+1] == 'X') { return false; }
               else if (currentboard[y+1][x+1] == 'X') { return false; }
               else { return true; }
               break;
         }
         break;
      }
      case 3: { // L-piece
         switch (orientation) {
            case 1: // Based on the orientation of the current piece
               // Checks the areas around the piece to see if there is room for the piece to rotate without colliding with other pieces
               if (currentboard[y-1][x-1] == 'X') { return false; }
               else if (currentboard[y-1][x] == 'X') { return false; }
               else if (currentboard[y+1][x] == 'X') { return false; }
               else { return true; }
               break;
            case 2: // Based on the orientation of the current piece
               // Checks the areas around the piece to see if there is room for the piece to rotate without colliding with other pieces
               if (x < 1 || x > 8) { return false; } // Prevents the piece from going out of bounds
               else if (currentboard[y-1][x+1] == 'X') { return false; }
               else if (currentboard[y][x-1] == 'X') { return false; }
               else if (currentboard[y][x+1] == 'X') { return false; }
               else { return true; }
               break;
            case 3: // Based on the orientation of the current piece
               // Checks the areas around the piece to see if there is room for the piece to rotate without colliding with other pieces
               if (currentboard[y-1][x] == 'X') { return false; }
               else if (currentboard[y+1][x+1] == 'X') { return false; }
               else if (currentboard[y+1][x] == 'X') { return false; }
               else { return true; }
               break;
            case 4: // Based on the orientation of the current piece
               // Checks the areas around the piece to see if there is room for the piece to rotate without colliding with other pieces
               if (x < 0 || x > 7) { return false; } // Prevents the piece from going out of bounds
               else if (currentboard[y][x-1] == 'X') { return false; }
               else if (currentboard[y][x+1] == 'X') { return false; }
               else if (currentboard[y+1][x-1] == 'X') { return false; }
               else { return true; }
               break;
         }
         break;
      }
      case 5: { // S-piece
            if (orientation == 1 || orientation == 3) { // Based on the orientation of the current piece
            // Checks the areas around the piece to see if there is room for the piece to rotate without colliding with other pieces
            if (currentboard[y-1][x-1] == 'X') { return false; }
            else if (currentboard[y][x-1] == 'X') { return false; }
            else { return true; }
         }
         else if (orientation == 2 || orientation == 4) { // Based on the orientation of the current piece
            // Checks the areas around the piece to see if there is room for the piece to rotate without colliding with other pieces
            if (x > 8) { return false; } // Prevents the piece from going out of bounds
            else if (currentboard[y][x+1] == 'X') { return false; }
            else if (currentboard[y+1][x-1] == 'X') { return false; }
            else { return true; }
         }
         break;
      }
      case 6: { // T-piece
         switch (orientation) {
            case 1: // Based on the orientation of the current piece
               // Checks the areas around the piece to see if there is room for the piece to rotate without colliding with other pieces
               if (currentboard[y-1][x] == 'X') { return false; }
               else { return true; }
               break;
            case 2: // Based on the orientation of the current piece
               // Checks the areas around the piece to see if there is room for the piece to rotate without colliding with other pieces
               if (x > 8) { return false; } // Prevents the piece from going out of bounds
               else if (currentboard[y][x+1] == 'X') { return false; }
               else { return true; }
               break;
            case 3: // Based on the orientation of the current piece
               // Checks the areas around the piece to see if there is room for the piece to rotate without colliding with other pieces
               if (currentboard[y+1][x] == 'X') { return false; }
               else { return true; }
               break;
            case 4: // Based on the orientation of the current piece
               // Checks the areas around the piece to see if there is room for the piece to rotate without colliding with other pieces
               if (x < 0) { return false; } // Prevents the piece from going out of bounds
               else if (currentboard[y][x-1] == 'X') { return false; }
               else { return true; }
               break;
         }
         break;
      }
      case 7: { // Z-piece
         if (orientation == 1 || orientation == 3) { // Based on the orientation of the current piece
            // Checks the areas around the piece to see if there is room for the piece to rotate without colliding with other pieces
            if (currentboard[y+1][x-1] == 'X') { return false; }
            else if (currentboard[y-1][x] == 'X') { return false; }
            else { return true; }
         }
         else if (orientation == 2 || orientation == 4) { // Based on the orientation of the current piece
            // Checks the areas around the piece to see if there is room for the piece to rotate without colliding with other pieces
            if (x > 8) { return false; } // Prevents the piece from going out of bounds
            else if (currentboard[y+1][x] == 'X') { return false; }
            else if (currentboard[y+1][x+1] == 'X') { return false; }
            else { return true; }
         }
         break;
      }
   }
}

void Tetrisboard::rotate() // Rotates the current Tetris piece
{
   removeblock(xcoord,ycoord); // Removes the current Tetris piece 
   if (orientation == 4) { orientation = 1; } // Rotates piece to orientation 1 from orientation 4
   else { orientation++; } // Rotates piece to next orientation for all other orientations 
   addblock(xcoord,ycoord); // Adds the Tetris piece with its new orientation to the board 
}

bool Tetrisboard::checkbelow() // Checks if and where there is space for the current piece to be added to the board 
{
   int x, y, count = 0;
   x = getx();
   y = gety();

   switch (shape) {
      case 1: // I-piece
         if (orientation == 1 || orientation == 3) { // Based on the orientation of the piece 
            for (int i = -1; i <= 2; i++) {
               if (currentboard[y+1][x+i] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
            }
         }
         else if (orientation == 2 || orientation == 4) { // Based on the orientation of the piece
            if (currentboard[y+3][x] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
         }
         if (count != 0) { return true; } // There is a piece below
         else { return false; } // There is not a piece below
         break;
      case 2: // J-piece
         switch (orientation) { // Based on the orientation
            case 1:
               for (int i = -1; i <= 1; i++) {
                  if (i == -1 || i == 0) {
                     if (currentboard[y+1][x+i] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
                  }
                  else if (i == 1) {
                     if (currentboard[y+2][x+i] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
                  }
               }
               break; 
            case 2:
               if (currentboard[y+2][x-1] == 'X' || currentboard[y+2][x] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
               break;
            case 3:
               for (int i = -1; i <= 1; i++) {
                  if (currentboard[y+1][x+i] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
               }
               break;
            case 4:
               if (currentboard[y+2][x] == 'X' || currentboard[y][x+1] == 'X'){ count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
               break;
         }  
         if (count != 0) { return true; } // There is a piece below
         else { return false; } // There is not a piece below
         break; 
      case 3: // L-piece
         switch (orientation) { // Based on orientation
            case 1: 
               for (int i = -1; i <= 1; i++) {
                  if (i == 1 || i == 0) {
                     if (currentboard[y+1][x+i] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
                  }
                  else if (i == -1) {
                     if (currentboard[y+2][x+i] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
                  }
               }
               break; 
            case 2:
               if (currentboard[y+2][x] == 'X' || currentboard[y][x-1] == 'X'){ count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
               break;
            case 3:
               for (int i = -1; i <= 1; i++) {
                  if (currentboard[y+1][x+i] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
               }
               break;
            case 4:
               if (currentboard[y+2][x] == 'X' || currentboard[y+2][x+1] == 'X'){ count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
               break;
         }  
         if (count != 0) { return true; } // There is a piece below
         else { return false; } // There is not a piece below
         break;
      case 4: // O-piece
         if (currentboard[y+2][x] == 'X' || currentboard[y+2][x+1] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
         if (count != 0) { return true; } // There is a piece below
         else { return false; } // There is not a piece below
         break;
      case 5: // S-piece
         if (orientation == 1 || orientation == 3) { // Based on orientation
            if (currentboard[y+2][x-1] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
            if (currentboard[y+2][x] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
            if (currentboard[y+1][x+1] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
         }
         else if (orientation == 2 || orientation == 4) { // Based on orientation
            if (currentboard[y+1][x-1] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
            if (currentboard[y+2][x] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
         }
         if (count != 0) { return true; } // There is a piece below
         else { return false; } // There is not a piece below
         break;
      case 6: // T-piece
         switch (orientation) { // Based on orientation
            case 1:
               for (int i = -1; i <= 1; i++) {
                  if (i == -1 || i == 1) {
                     if (currentboard[y+1][x+i] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
                  }
                  else if (i == 0) {
                     if (currentboard[y+2][x+i] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
                  }
               }
               break; 
            case 2:
               if (currentboard[y+1][x-1] == 'X' || currentboard[y+2][x] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
               break;
            case 3:
               for (int i = -1; i <= 1; i++) {
                  if (currentboard[y+1][x+i] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
               }
               break;
            case 4:
               if (currentboard[y+2][x] == 'X' || currentboard[y+1][x+1] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
               break;
         }  
         if (count != 0) { return true; } // There is a piece below
         else { return false; } // There is not a piece below
         break;  
      case 7: // Z-piece
         if (orientation == 1 || orientation == 3) { // Based on orientation
            if (currentboard[y+2][x+1] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
            if (currentboard[y+2][x] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
            if (currentboard[y+1][x-1] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
         }
         else if (orientation == 2 || orientation == 4) { // Based on orientation
            if (currentboard[y+2][x-1] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
            if (currentboard[y+1][x] == 'X') { count++; } // Checks if there is an 'X' at the location below and increments 'count' if there is an 'X'
         }
         if (count != 0) { return true; } // There is a piece below
         else { return false; } // There is not a piece below
         break;
   }
}

void Tetrisboard::clearLine() // Clears the row that is completely filled  
{
   int count = 0, color, row;
   bool clear = false;

   for (int i = 0; i < SIZE1; i++) { // Goes through the rows
      for (int j = 0; j < SIZE2; j++) { // Goes through the columns
         if (currentboard[i][j] == 'X') { count++; } // Increments count when there is an 'X' in the row
         if (count == SIZE2) { row = i; clear = true; } // Stores row and sets clear to true when whole row is full
         if (clear) { // Enters when row needs to be cleared
            for (int i = 1; i <= row; i++) { // Goes through the rows until row that needs to be cleared
               for (int j = 0; j < SIZE2; j++) { // Goes through the columns
                  tempboard[i][j] = currentboard[i-1][j]; // Moves rows down one until row that needs to be cleared and stores in tempboard
                  tempcolorboard[i][j] = colorboard[i-1][j]; // Moves colors of blocks down one row until row to be cleared and stores in tempcolorboard
                  color = tempcolorboard[i][j]; // Set for color of each block
                  switch (color) { // Makes each block correct new color on gfx window
                     case 1: // I-piece
                        setColor(0,255,255); // Sets the color
                        gfx_color(red,green,blue); // Sets the color to cyan
                        gfx_fill_rectangle(30*j,30*i,30,30); // Fills in a square on the board
                        break;
                     case 2: // J-piece
                        setColor(0,0,255); // Sets the color
                        gfx_color(red,green,blue); // Sets the color to blue
                        gfx_fill_rectangle(30*j,30*i,30,30); // Fills in a square on the board
                        break;
                     case 3: // L-piece
                        setColor(255,128,0); // Sets the color
                        gfx_color(red,green,blue); // Sets the color to orange
                        gfx_fill_rectangle(30*j,30*i,30,30); // Fills in a square on the board
                        break;
                     case 4: // O-piece
                        setColor(255,255,0); // Sets the color
                        gfx_color(red,green,blue); // Sets the color to yellow
                        gfx_fill_rectangle(30*j,30*i,30,30); // Fills in a square on the board
                        break;
                     case 5: // S-piece
                        setColor(0,255,0); // Sets the color
                        gfx_color(red,green,blue); // Sets the color to green
                        gfx_fill_rectangle(30*j,30*i,30,30); // Fills in a square on the board
                        break;
                     case 6: // T-piece
                        setColor(128,0,255); // Sets color
                        gfx_color(red,green,blue); // Sets color to purple
                        gfx_fill_rectangle(30*j,30*i,30,30); // Fills in a square on the board
                        break;
                     case 7: // Z-piece
                        setColor(255,0,0); // Sets color
                        gfx_color(red,green,blue); // Sets color to red
                        gfx_fill_rectangle(30*j,30*i,30,30); // Fills in a square on the board
                        break;
                     default: 
                        setColor(0,0,0); // Sets color
                        gfx_color(red,green,blue); // Sets color to black
                        gfx_fill_rectangle(30*j,30*i,30,30); // Fills in a square on a board
                        break;
                  }
               }
            }
         }
      }
      count = 0; // Clears count back to zero at end of each row
   }
   if (clear) { // Sets pieces and colors on array to new position (down one row)
      for (int i = 0; i <= row; i++) {
         for (int j = 0; j < SIZE2; j++) { 
            currentboard[i][j] = tempboard[i][j]; 
            colorboard[i][j] = tempcolorboard[i][j];
         }
      }
   }
}
