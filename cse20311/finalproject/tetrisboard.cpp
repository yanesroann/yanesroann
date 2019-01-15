// Final Project
// tetrisboard_gfx.cpp
// Grace Milton and Roann Yanes

#include <iostream>
#include <unistd.h>
#include <cstdlib>
using namespace std;
#include "tetrisboard.h"
#include "gfxnew.h"

int R = 255, G =  255, B = 255;

Tetrisboard::Tetrisboard() // Default constructor
{ orientation = 1; endgame = false; }

Tetrisboard::~Tetrisboard() { } // Destructor

int Tetrisboard::getx() // Returns x-coordinate of tetris piece in array
{ return xcoord; }

int Tetrisboard::gety() // Returns y-coordinate of tetris piece in array
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
   int start;

   switch (shape) {
      case 1:
         start = 1;
         break;
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
         start = 2;
         break;
   } 
   if (currentboard[y+start][x] == 'X' && y == 0){ setEndgame(end); } // Ends the game if there is a piece at the top of board
   else {
      switch (shape) {
         case 1: { // I-piece
            setColor(0,255,255); // Sets the color
            gfx_color(red,green,blue); // Sets the color to cyan
            for (int i = -1; i <= 2; i++) {
               if (orientation == 1 || orientation == 3) { // Based on the orientation of the board
                  currentboard[y][x+i] = 'X'; // Adds the shape on the board in terminal 
                  colorboard[y][x+i] = 1; // Sets its color on the board
               } 
               else if (orientation == 2 || orientation == 4) { // Based on the orientation
                  currentboard[y+i][x] = 'X';  // Adds the piece on the board in terminal
                  colorboard[y+i][x] = 1; // Sets its color on the board
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
                  currentboard[y][x+i] = 'X'; // Adds the piece to the board in terminal
                  colorboard[y][x+i] = 2; // Sets its color on the board
                  if (i == 1) { currentboard[y+1][x+i] = 'X'; colorboard[y+1][x+i] = 2; } // Adds the piece to the board in terminal and sets its color on the board
               }
               else if (orientation == 2) { // Based on the orientation
                  currentboard[y+i][x] = 'X'; // Adds the piece to the board in terminal
                  colorboard[y+i][x] = 2; // Sets its color on the board
                  if (i == 1) { currentboard[y+i][x-1] = 'X'; colorboard[y+i][x-1] = 2; } // Adds the piece to the board in terminal and sets its color on the board
               }
               else if (orientation == 3) { // Based on the orientation
                  currentboard[y][x+i] = 'X'; // Adds the piece to the board in terminal
                  colorboard[y][x+i] = 2; // Sets its color on the board
                  if (i == -1) { currentboard[y-1][x+i] = 'X'; colorboard[y-1][x+i] = 2;} // Adds the piece to the board in terminal and sets its color on the board
               }
               else if (orientation == 4) { // Based on the orientation
                  currentboard[y+i][x] = 'X'; // Adds the piece to the board in terminal
                  colorboard[y+i][x] = 2; // Sets its color on the board
                  if (i == -1) { currentboard[y+i][x+1] = 'X'; colorboard[y+i][x+1] = 2; } // Adds the piece to the board in terminal and sets its color on the board
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
                  currentboard[y][x+i] = 'X'; // Adds the piece to the board in terminal
                  colorboard[y][x+i] = 3; // Sets its color on the board
                  if (i == -1) { currentboard[y+1][x+i] = 'X'; colorboard[y+1][x+i] = 3; } // Adds the piece to the board in terminal and sets its color on the board
               }
               else if (orientation == 2) {  // Based on the orientation
                  currentboard[y+i][x] = 'X'; // Adds the piece to the board in terminal
                  colorboard[y+i][x] = 3; // Sets its color on the board
                  if (i == -1) { currentboard[y+i][x-1] = 'X'; colorboard[y+i][x-1] = 3; } // Adds the piece to the board in terminal and sets its color on the board
               }
               else if (orientation == 3) { // Based on the orientation
                  currentboard[y][x+i] = 'X'; // Adds the piece to the board in terminal
                  colorboard[y][x+i] = 3; // Sets its color on the board 
                  if (i == 1) { currentboard[y-1][x+i] = 'X'; colorboard[y-1][x+i] = 3; } // Adds the piece to the board in terminal and sets its color on the board
               }
               else if (orientation == 4) { // Based on the orientation
                  currentboard[y+i][x] = 'X'; // Adds the piece to the board in terminal
                  colorboard[y+i][x] = 3; // Sets its color on the board
                  if (i == 1) { currentboard[y+i][x+1] = 'X'; colorboard[y+i][x+1] = 3;} // Adds the piece to the board in terminal and sets its color on the board
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
            currentboard[y][x] = 'X'; // Adds the piece to the board in terminal
            colorboard[y][x] = 4; // Sets its color on the board
            currentboard[y][x+1] = 'X'; // Adds the piece to the board in terminal
            colorboard[y][x+1] = 4; // Sets its color in the board
            currentboard[y+1][x] = 'X'; // Adds the piece to the board in terminal
            colorboard[y+1][x] = 4; // Set its color on the board
            currentboard[y+1][x+1] = 'X'; // Adds the piece to the board in terminal
            colorboard[y+1][x+1] = 4; // Sets its color on the board
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
               currentboard[y][x] = 'X'; // Adds the piece to the board in terminal
               colorboard[y][x] = 5; // Sets its color on the board
               currentboard[y][x+1] = 'X'; // Adds the piece to the board in terminal
               colorboard[y][x+1] = 5; // Sets its color on the board
               currentboard[y+1][x-1] = 'X'; // Adds the piece to the board in terminal
               colorboard[y+1][x-1] = 5; // Sets its color on the board
               currentboard[y+1][x] = 'X'; // Adds the piece to the board in terminal
               colorboard[y+1][x] = 5; // Sets its color on the board
            }
            else if (orientation == 2 || orientation == 4) { // Based on the orientation
               currentboard[y-1][x-1] = 'X'; // Adds the piece to the board in terminal
               colorboard[y-1][x-1] = 5; // Sets its color on the board
               currentboard[y][x-1] = 'X'; // Adds the piece to the board in terminal
               colorboard[y][x-1] = 5; // Sets its color on the board
               currentboard[y][x] = 'X'; // Adds the piece to the board in terminal
               colorboard[y][x] = 5; // Sets its color on the board
               currentboard[y+1][x] = 'X'; // Adds the piece to the board in terminal
               colorboard[y+1][x] = 5; // Sets its color on the board
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
                  currentboard[y][x+i] = 'X'; // Adds the piece to the board in terminal
                  colorboard[y][x+i] = 6; // Sets its color on the board
                  if (i == 0) { currentboard[y+1][x+i] = 'X'; colorboard[y+1][x+i] = 6; } // Adds the piece to the board in terminal and sets its color on the board

               }
               else if (orientation == 2) { // Based on the orientation
                  currentboard[y+i][x] = 'X'; // Adds the piece to the board in terminal
                  colorboard[y+i][x] = 6; // Sets its color on the board
                  if (i == 0) { currentboard[y+i][x-1] = 'X'; colorboard[y+i][x-1] = 6; } // Adds the piece to the board in terminal and sets its color on the board

               }
               else if (orientation == 3) { // Based on the orientation
                  currentboard[y][x+i] = 'X'; // Adds the piece to the board in terminal
                  colorboard[y][x+i] = 6; // Sets its color on the board
                  if (i == 0) { currentboard[y-1][x+i] = 'X'; colorboard[y-1][x+i] = 6; } // Adds the piece to the board in terminal and sets its color on the board

               }
               else if (orientation == 4) { // Based on the orientation 
                  currentboard[y+i][x] = 'X'; // Adds the piece to the board in terminal
                  colorboard[y+i][x] = 6; // Sets its color on the board
                  if (i == 0) { currentboard[y+i][x+1] = 'X'; colorboard[y+i][x+1] = 6; } // Adds the piece to the board in terminal and sets its color on the board

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
               currentboard[y+1][x+1] = 'X'; // Adds the piece to the board in terminal
               colorboard[y+1][x+1] = 7;
               currentboard[y][x] = 'X';
               colorboard[y][x] = 7;
               currentboard[y+1][x] = 'X';
               colorboard[y+1][x] = 7;
               currentboard[y][x-1] = 'X';
               colorboard[y][x-1] = 7;
            }
            else if (orientation == 2 || orientation == 4) {
               currentboard[y-1][x] = 'X';
               colorboard[y-1][x] = 7;
               currentboard[y][x-1] = 'X';
               colorboard[y][x-1] = 7;
               currentboard[y][x] = 'X';
               colorboard[y][x] = 7;
               currentboard[y+1][x-1] = 'X';
               colorboard[y+1][x-1] = 7;
            }
            setx(x);
            sety(y);
            if (orientation == 1 || orientation == 3) {
               XPoint mypts7[] = {{30*x-30,30*y},{30*x+30,30*y},{30*x+30,30*y+30},{30*x+60,30*y+30},{30*x+60,30*y+60},{30*x,30*y+60},{30*x,30*y+30},{30*x-30,30*y+30}};
               gfx_fill_polygon(mypts7,8); 
            }
            else if (orientation == 2 || orientation == 4) {
               XPoint mypts7[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y+30},{30*x,30*y+30},{30*x,30*y+60},{30*x-30,30*y+60},{30*x-30,30*y},{30*x,30*y}};
               gfx_fill_polygon(mypts7,8); 
            }
            break;
         }     
      }
   }  
}

void Tetrisboard::removeblock(int x, int y) // Removes the pieces  
{
   setColor(0,0,0); // Sets the color to black
   gfx_flush(); // Flushes output to graphics window
   gfx_color(red,green,blue); // Sets the color to black
   switch (shape) {
      case 1: { // I-piece   
         for (int i = -1; i <= 2; i++) {
            if (orientation == 1 || orientation == 3) { // Based on the orientation of the piece
               currentboard[y][x+i] = ' '; // Removes the piece from the board
               colorboard[y][x+i] = 0;
            }
            else if (orientation == 2 || orientation == 4) {
               currentboard[y+i][x] = ' ';
               colorboard[y+i][x] = 0;
            }
         }
         if (orientation == 1 || orientation == 3){
            XPoint mypts[] = {{30*x-30,30*y},{30*x+90,30*y},{30*x+90,30*y+30},{30*x-30,30*y+30}};
            gfx_fill_polygon(mypts,4);
         }
         else if (orientation == 2 || orientation == 4){
            XPoint mypts[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y+90},{30*x,30*y+90}};
            gfx_fill_polygon(mypts,4); // fills in the I-piece
         }
         break;
      }
      case 2: { // J-piece
         for (int i = -1; i <= 1; i++) {
            if (orientation == 1){
               currentboard[y][x+i] = ' ';
               colorboard[y][x+i] = 0;
               if (i == 1) { currentboard[y+1][x+i] = ' '; colorboard[y+1][x+i] = 0; }
            }
            else if (orientation == 2){
               currentboard[y+i][x] = ' ';
               colorboard[y+i][x] = 0;
               if (i == 1) { currentboard[y+i][x-1] = ' '; colorboard[y+i][x-1] = 0; }
            }
            else if (orientation == 3){
               currentboard[y][x+i] = ' ';
               colorboard[y][x+i] = 0;
               if (i == -1) { currentboard[y-1][x+i] = ' '; colorboard[y-1][x+i] = 0; }
            }
            else if (orientation == 4){
               currentboard[y+i][x] = ' ';
               colorboard[y+i][x] = 0;
               if (i == -1) { currentboard[y+i][x+1] = ' '; colorboard[y+i][x+1] = 0; }
            }
         }
         switch (orientation){
            case 1: {
               XPoint mypts2[] = {{30*x-30,30*y},{30*x+60,30*y},{30*x+60,30*y+60},{30*x+30,30*y+60},{30*x+30,30*y+30},{30*x-30,30*y+30}};
               gfx_fill_polygon(mypts2,6);
               break;
            }
            case 2: {
               XPoint mypts2[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y+60},{30*x-30,30*y+60},{30*x-30,30*y+30},{30*x,30*y+30}};
               gfx_fill_polygon(mypts2,6);
               break;
            }
            case 3: {
               XPoint mypts2[] = {{30*x-30,30*y-30},{30*x,30*y-30},{30*x,30*y},{30*x+60,30*y},{30*x+60,30*y+30},{30*x-30,30*y+30}};
               gfx_fill_polygon(mypts2,6);
               break;
            }
            case 4: {
               XPoint mypts2[] = {{30*x,30*y-30},{30*x+60,30*y-30},{30*x+60,30*y},{30*x+30,30*y},{30*x+30,30*y+60},{30*x,30*y+60}};
               gfx_fill_polygon(mypts2,6);
               break;
            }
         }
         break; 
      }
      case 3: { // L-piece
         for (int i = -1; i <= 1; i++) {
            if (orientation == 1){
               currentboard[y][x+i] = ' ';
               colorboard[y][x+i] = 0;
               if (i == -1) { currentboard[y+1][x+i] = ' '; colorboard[y+1][x+i] = 0; }
            }
            else if (orientation == 2){
               currentboard[y+i][x] = ' ';
               colorboard[y+i][x] = 0;
               if (i == -1) { currentboard[y+i][x-1] = ' '; colorboard[y+i][x-1] = 0; }
            }
            else if (orientation == 3){
               currentboard[y][x+i] = ' ';
               colorboard[y][x+i] = 0;
               if (i == 1) { currentboard[y-1][x+i] = ' '; colorboard[y-1][x+i] = 0; }
            }
            else if (orientation == 4){
               currentboard[y+i][x] = ' ';
               colorboard[y+i][x] = 0;
               if (i == 1) { currentboard[y+i][x+1] = ' '; colorboard[y+i][x+1] = 0; }
            }
         }
         switch (orientation){
            case 1: {
               XPoint mypts3[] = {{30*x-30,30*y},{30*x+60,30*y},{30*x+60,30*y+30},{30*x,30*y+30},{30*x,30*y+60},{30*x-30,30*y+60}};
               gfx_fill_polygon(mypts3,6);
               break;
            }
            case 2: {
               XPoint mypts3[] = {{30*x-30,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y+60},{30*x,30*y+60},{30*x,30*y},{30*x-30,30*y}};
               gfx_fill_polygon(mypts3,6);
               break;
            }
            case 3: {
               XPoint mypts3[] = {{30*x+30,30*y-30},{30*x+60,30*y-30},{30*x+60,30*y+30},{30*x-30,30*y+30},{30*x-30,30*y},{30*x+30,30*y}};
               gfx_fill_polygon(mypts3,6);
               break;
            }
            case 4: {
               XPoint mypts3[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y+30},{30*x+60,30*y+30},{30*x+60,30*y+60},{30*x,30*y+60}};
               gfx_fill_polygon(mypts3,6);
               break;
            }
         }
         break;
      }
      case 4: { // O-piece 
         currentboard[y][x] = ' ';
         colorboard[y][x] = 0;
         currentboard[y][x+1] = ' ';
         colorboard[y][x+1] = 0;
         currentboard[y+1][x] = ' ';
         colorboard[y+1][x] = 0;
         currentboard[y+1][x+1] = ' ';
         colorboard[y+1][x+1] = 0;
         XPoint mypts4[] = {{30*x,30*y},{30*x+60,30*y},{30*x+60,30*y+60},{30*x,30*y+60}};
         gfx_fill_polygon(mypts4,4); // fills in the outline of the O-piece
         break;
      }
      case 5: { // S-piece
         if (orientation == 1 || orientation == 3) {
            currentboard[y][x] = ' ';
            colorboard[y][x] = 0;
            currentboard[y][x+1] = ' ';
            colorboard[y][x+1] = 0;
            currentboard[y+1][x-1] = ' ';
            colorboard[y+1][x-1] = 0;
            currentboard[y+1][x] = ' ';
            colorboard[y+1][x] = 0;
         }
         else if (orientation == 2 || orientation == 4) {
            currentboard[y-1][x-1] = ' ';
            colorboard[y-1][x-1] = 0;
            currentboard[y][x-1] = ' ';
            colorboard[y][x-1] = 0;
            currentboard[y][x] = ' ';
            colorboard[y][x] = 0;
            currentboard[y+1][x] = ' ';
            colorboard[y+1][x] = 0;
         }
         if (orientation == 1 || orientation == 3) {
            XPoint mypts5[] = {{30*x,30*y},{30*x+60,30*y},{30*x+60,30*y+30},{30*x+30,30*y+30},{30*x+30,30*y+60},{30*x-30,30*y+60},{30*x-30,30*y+30},{30*x,30*y+30}};
            gfx_fill_polygon(mypts5,8);
         }
         else if (orientation == 2 || orientation == 4) {
            XPoint mypts5[] = {{30*x-30,30*y-30},{30*x,30*y-30},{30*x,30*y},{30*x+30,30*y},{30*x+30,30*y+60},{30*x,30*y+60},{30*x,30*y+30},{30*x-30,30*y+30}};
            gfx_fill_polygon(mypts5,8);
         }
         break;
      }
      case 6: {  // T-piece
         for (int i = -1; i <= 1; i++) {
            if (orientation == 1){
               currentboard[y][x+i] = ' ';
               colorboard[y][x+i] = 0;
               if (i == 0) { currentboard[y+1][x+i] = ' '; colorboard[y+1][x+i] = 0; }
            } 
            else if (orientation == 2){
               currentboard[y+i][x] = ' ';
               colorboard[y+i][x] = 0;
               if (i == 0) { currentboard[y+i][x-1] = ' '; colorboard[y+i][x-1] = 0; }
            }
            else if (orientation == 3){
               currentboard[y][x+i] = ' ';
               colorboard[y][x+i] = 0;
               if (i == 0) { currentboard[y-1][x+i] = ' '; colorboard[y-1][x+i] = 0; }
            }
            else if (orientation == 4){
               currentboard[y+i][x] = ' ';
               colorboard[y+i][x] = 0;
               if (i == 0) { currentboard[y+i][x+1] = ' '; colorboard[y+i][x+1] = 0; }
            }
         }
         switch (orientation) {
            case 1: {
               XPoint mypts6[] = {{30*x-30,30*y},{30*x+60,30*y},{30*x+60,30*y+30},{30*x+30,30*y+30},{30*x+30,30*y+60},{30*x,30*y+60},{30*x,30*y+30},{30*x-30,30*y+30}};
               gfx_fill_polygon(mypts6,8);
               break;
            }
            case 2: {
               XPoint mypts6[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y+60},{30*x,30*y+60},{30*x,30*y+30},{30*x-30,30*y+30},{30*x-30,30*y},{30*x,30*y}};
               gfx_fill_polygon(mypts6,8);
               break;
            }
            case 3: {
               XPoint mypts6[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y},{30*x+60,30*y},{30*x+60,30*y+30},{30*x-30,30*y+30},{30*x-30,30*y},{30*x,30*y}};
               gfx_fill_polygon(mypts6,8);
               break;
            }
            case 4: {
               XPoint mypts6[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y},{30*x+60,30*y},{30*x+60,30*y+30},{30*x+30,30*y+30},{30*x+30,30*y+60},{30*x,30*y+60}};
               gfx_fill_polygon(mypts6,8);
               break;
            }
         }
         break;
      }
      case 7: { // Z-piece
         if (orientation == 1 || orientation == 3) {
            currentboard[y+1][x+1] = ' ';
            colorboard[y+1][x+1] = 0;
            currentboard[y][x] = ' ';
            colorboard[y][x] = 0;
            currentboard[y+1][x] = ' ';
            colorboard[y+1][x] = 0;
            currentboard[y][x-1] = ' ';
            colorboard[y][x-1] = 0;
         }
         else if (orientation == 2 || orientation == 4) {
            currentboard[y-1][x] = ' ';
            colorboard[y-1][x] = 0;
            currentboard[y][x-1] = ' ';
            colorboard[y][x-1] = 0;
            currentboard[y][x] = ' ';
            colorboard[y][x] = 0;
            currentboard[y+1][x-1] = ' ';
            colorboard[y+1][x-1] = 0;
         }
         if (orientation == 1 || orientation == 3) {
            XPoint mypts7[] = {{30*x-30,30*y},{30*x+30,30*y},{30*x+30,30*y+30},{30*x+60,30*y+30},{30*x+60,30*y+60},{30*x,30*y+60},{30*x,30*y+30},{30*x-30,30*y+30}};
            gfx_fill_polygon(mypts7,8); 
         }
         else if (orientation == 2 || orientation == 4) {
            XPoint mypts7[] = {{30*x,30*y-30},{30*x+30,30*y-30},{30*x+30,30*y+30},{30*x,30*y+30},{30*x,30*y+60},{30*x-30,30*y+60},{30*x-30,30*y},{30*x,30*y}};
            gfx_fill_polygon(mypts7,8); 
         }
         break;
      }
   }
}

void Tetrisboard::fall() // Shifts the current Tetris piece down to make it appear as though it is falling
{
   int x, y;
   x = getx();
   y = gety();
   addblock(x,y); // Adds the current piece at a certain location
   usleep(80000); // Pauses briefly
   gfx_flush();
   gfx_flush();
   gfx_flush();
   removeblock(x,y); // Removes the current piece at the same location
   gfx_flush();
   gfx_flush();
   addblock(x, y+1); // Adds the current piece at the location below its previous location
   gfx_flush();
   gfx_flush();
  // removeblock(x,y);
   setx(x); // Sets the x-coordinate of the piece that corresponds to its current location
   sety(y+1); // Sets the y-coordinate of the piece that corresponds to the location below its previous location
}

void Tetrisboard::moveLeft() // Shifts the current Tetris piece left as it is falling
{
   int x, y, leftbound;
   bool open = true;
   x = getx();
   y = gety(); 
   switch (shape) {
      case 1: // I-piece
         if (orientation == 1 || orientation == 3) { // Based on the orientation of the piece
            if (currentboard[y][x-2] == 'X') { open = false; } // Checks if there is a piece already there
            leftbound = 2; // Left boundary to prevent the piece from going off the board
         }
         else if (orientation == 2 || orientation == 4) { // Based on the orientation of the piece
            if (currentboard[y][x-1] == 'X') { open = false; } // Checks if there is a piece already there
            leftbound = 1; // Left boundary to prevent the piece from going off the board
         }
         break;
      case 2: // J-piece
         switch (orientation) {
            case 1:  
               if (currentboard[y][x-2] == 'X' || currentboard[y+1][x] == 'X') {
                  open = false;
               }
               leftbound = 2; // Left boundary to prevent the piece from going off the board
               break;
            case 2:
               if (currentboard[y-1][x-1] == 'X') { open = false; }
               else if (currentboard[y][x-1] == 'X') { open = false; }               
               else if (currentboard[y+1][x-2] == 'X') { open = false; } 
               leftbound = 2;
               break;
            case 3:
               if (currentboard[y][x-2] == 'X' || currentboard[y-1][x-2] == 'X') { 
                  open = false; 
               }       
               leftbound = 2;
               break;
            case 4:
               if (currentboard[y-1][x-1] == 'X') { open = false; }
               else if (currentboard[y][x-1] == 'X') { open = false; }                 
               else if (currentboard[y+1][x-1] == 'X') { open = false; } 
               leftbound = 1;
               break;
         }
         break;
      case 3: // L-piece
         switch (orientation){
            case 1:
               if (currentboard[y][x-2] == 'X' || currentboard[y+1][x-2] == 'X') {
                  open = false;
               }
               leftbound = 2;
               break;
            case 2:
               if (currentboard[y-1][x-2] == 'X') { open = false; }
               else if (currentboard[y][x-1] == 'X') { open = false; }
               else if (currentboard[y+1][x-1] == 'X') { open = false; }
               leftbound = 2;
               break;
            case 3:
               if (currentboard[y][x-2] == 'X' || currentboard[y-1][x] == 'X') {
                  open = false;
               }
               leftbound = 2;
               break;
            case 4:
               if (currentboard[y-1][x-1] == 'X') { open = false; }
               else if (currentboard[y][x-1] == 'X') { open = false; }
               else if (currentboard[y+1][x-1] == 'X') { open = false; }
               leftbound = 1;
               break;
         }
         break;
      case 4: // O-piece
         if (currentboard[y][x-1] == 'X' || currentboard[y+1][x-1] == 'X') {
            open = false;
         }
         leftbound = 1;
         break;
      case 5: // S-piece
         if (orientation == 1 || orientation == 3) {
            if (currentboard[y][x-1] == 'X' || currentboard[y+1][x-2] == 'X') {
               open = false;
            }
         }
         if (orientation == 2 || orientation == 4) {
            if (currentboard[y-1][x-2] == 'X') { open = false; }
            else if (currentboard[y][x-2] == 'X') { open = false; }
            else if (currentboard[y+1][x-1] == 'X') { open = false; } 
         }
         leftbound = 2;
         break;
      case 6: // T-piece
         switch (orientation){
            case 1:
               if (currentboard[y][x-2] == 'X' || currentboard[y+1][x-1] == 'X') {
                  open = false;
               }
               leftbound = 2;
               break;
            case 2:
               if (currentboard[y-1][x-1] == 'X') { open = false; }
               else if (currentboard[y][x-2] == 'X') { open = false; }
               else if (currentboard[y+1][x-1] == 'X') { open = false; }
               leftbound = 2;
               break;
            case 3:
               if (currentboard[y-1][x-1] == 'X' || currentboard[y][x-2] == 'X') {
                  open = false;
               }
               leftbound = 2;
               break;
            case 4:
               if (currentboard[y-1][x-1] == 'X') { open = false; }
               else if (currentboard[y][x-1] == 'X') { open = false; }
               else if (currentboard[y+1][x-1] == 'X') { open = false; }
               leftbound = 1;
               break;
         }
         break;
      case 7: // Z-piece
         if (orientation == 1 || orientation == 3) {
            if (currentboard[y][x-2] == 'X' || currentboard[y+1][x-1] == 'X') {
               open = false;
            }
         }
         if (orientation == 2 || orientation == 4) {
            if (currentboard[y-1][x-1] == 'X') { open = false; }
            else if (currentboard[y][x-2] == 'X') { open = false; }
            else if (currentboard[y+1][x-2] == 'X') { open = false; } 
         }
         leftbound = 2;
         break;
   }
   if ((x >= leftbound) && (open)) {
      addblock(x,y);
      usleep(80000);
      gfx_flush();
      gfx_flush();
      gfx_flush();
      removeblock(x,y);
      addblock(x-1,y);
      setx(x-1);
      sety(y);
   }
}

void Tetrisboard::moveRight() // Shifts the
{
   int rightbound, x, y;
   bool open = true;
   x = getx();
   y = gety();
   switch (shape) {
      case 1: // I-piece
         if (orientation == 1 || orientation == 3){
            if (currentboard[y][x+3] == 'X') { open = false; }
            rightbound = 6;
         }
         if (orientation == 2 || orientation == 4){
            if (currentboard[y][x+1] == 'X') { open = false; }
            rightbound = 8;
         }
         break;
      case 2: // J-piece
         switch (orientation){
            case 1:
               if (currentboard[y][x+2] == 'X' || currentboard[y+1][x+2] == 'X') {
                  open = false;
               }
               rightbound = 7;
               break;
            case 2:
               for (int i = -1; i <= 1; i++){
                  if (currentboard[y+i][x+1] == 'X') { open = false; }
               }
               rightbound = 8;
               break;
            case 3:
               if (currentboard[y-1][x] == 'X' || currentboard[y][x+2] == 'X') {
                  open = false; 
               }       
               rightbound = 7;
               break;
            case 4:
               if (currentboard[y-1][x+2] == 'X') { open = false; }
               else if (currentboard[y][x+1] == 'X') { open = false; }    
               else if (currentboard[y+1][x+1] == 'X') { open = false; }    
               rightbound = 7;
               break;
         }         
         break;
      case 3: // L-piece
         switch (orientation){
           case 1:
               if (currentboard[y][x+2] == 'X' || currentboard[y+1][x] == 'X') {
                  open = false;
               }
               rightbound = 7;
               break;
            case 2:
               for (int i = -1; i <= 1; i++){
                  if (currentboard[y+i][x+1] == 'X') { open = false; }
               }
               rightbound = 8;
               break;
            case 3:
               if (currentboard[y-1][x+2] == 'X' || currentboard[y][x+2] == 'X') {
                  open = false;
               }
               rightbound = 7;
               break;
            case 4:
               if (currentboard[y-1][x+1] == 'X') { open = false; }
               else if (currentboard[y][x+1] == 'X') { open = false; }
               else if (currentboard[y+1][x+2] == 'X') { open = false; }
               rightbound = 7;
               break;
         }
         break;
      case 4: // O-piece
         if (currentboard[y][x+2] == 'X' || currentboard[y+1][x+2] == 'X') {
            open = false;
         }
         rightbound = 7;
         break;
      case 5: // S-piece
         if (orientation == 1 || orientation == 3) {
            if (currentboard[y][x+2] == 'X' || currentboard[y+1][x+1] == 'X') {
               open = false;
            }
            rightbound = 7;
         }
         if (orientation == 2 || orientation == 4) {
            if (currentboard[y-1][x] == 'X') { open = false; }
            else if (currentboard[y][x+1] == 'X') { open = false; }
            else if (currentboard[y+1][x+1] == 'X') { open = false; } 
            rightbound = 8;
         }
         break;
      case 6: // T-piece
         switch (orientation){
            case 1:
               if (currentboard[y][x+2] == 'X' || currentboard[y+1][x+1] == 'X') {
                  open = false;
               }
               rightbound = 7;
               break;
            case 2:
               for (int i = -1; i <= 1; i++){
                  if (currentboard[y+i][x+1] == 'X') { open = false; }
               }
               rightbound = 8;
               break;
            case 3:
               if (currentboard[y-1][x+1] == 'X' || currentboard[y][x+2] == 'X') {
                  open = false;
               }
               rightbound = 7;
               break;
            case 4:
               if (currentboard[y-1][x+1] == 'X') { open = false; }
               else if (currentboard[y][x+2] == 'X') { open = false; }
               else if (currentboard[y+1][x+1] == 'X') { open = false; }
               rightbound = 7;
               break;
         }
         break;
      case 7: // Z-piece
         if (orientation == 1 || orientation == 3) {
            if (currentboard[y][x+1] == 'X' || currentboard[y+1][x+2] == 'X') {
               open = false;
            }
            rightbound = 7;
         }
         if (orientation == 2 || orientation == 4) {
            if (currentboard[y-1][x+1] == 'X') { open = false; }
            else if (currentboard[y][x+1] == 'X') { open = false; }
            else if (currentboard[y+1][x] == 'X') { open = false; } 
            rightbound = 8;
         }
         break;
   }
   if ((x <= rightbound) && (open)){
      addblock(x,y);
      usleep(80000);
      gfx_flush();
      gfx_flush();
      gfx_flush();
      removeblock(x,y);
      addblock(x+1,y);
      setx(x+1);
      sety(y);
   }
}

bool Tetrisboard::openRotate() // Checks to see if there is space for the current piece to rotate
{
   int x = getx();
   int y = gety();

   switch (shape) {
      case 1: { // I-piece
         if (orientation == 1 || orientation == 3) { // Based on the orientation of the current piece
            // Checks the areas above and below the piece to see if there is room for the piece to rotate without colliding with other pieces
            if (currentboard[y-1][x] == 'X') { return false; }
            else if (currentboard[y+1][x] == 'X') { return false; }
            else if (currentboard[y+2][x] == 'X') {return false; }
            else { return true; }
         }
         else if (orientation == 2 || orientation == 4) { // Based on the orientation of the current piece
            if (x >= 1 || x <= 7) { // Prevents it from going out of bounds
               // Checks the areas left and right of the piece to see if there is room for the piece to rotate without colliding with other pieces
               if (currentboard[y][x-1] == 'X') { return false; }
               else if (currentboard[y][x+1] == 'X') { return false; }
               else if (currentboard[y][x+2] == 'X') { return false; } 
               else { return true; }
            }
            else { return false; }
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
               case 2:  // Based on the orientation of the current piece
                  // Checks the areas around the piece to see if there is room for the piece to rotate without colliding with other pieces
                  if (currentboard[y-1][x-1] == 'X') { return false; }
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
            case 4:  // Based on the orientation of the current piece

               // Checks the areas around the piece to see if there is room for the piece to rotate without colliding with other pieces
               if (currentboard[y][x-1] == 'X') { return false; }
               else if (currentboard[y][x+1] == 'X') { return false; }
               else if (currentboard[y+1][x+1] == 'X') { return false; }
               else { return true; }
               break;
         }
         break;
      }
      case 3: { // L-piece
         switch (orientation) {
            case 1:  // Based on the orientation of the current piece

            // Checks the areas left and right of the piece to see if there is room for the piece to rotate without colliding with other pieces

               if (currentboard[y-1][x-1] == 'X') { return false; }
               else if (currentboard[y-1][x] == 'X') { return false; }
               else if (currentboard[y+1][x] == 'X') { return false; }
               else { return true; }
               break;
            case 2:
               if (currentboard[y-1][x+1] == 'X') { return false; }
               else if (currentboard[y][x-1] == 'X') { return false; }
               else if (currentboard[y][x+1] == 'X') { return false; }
               else { return true; }
               break;
            case 3:
               if (currentboard[y-1][x] == 'X') { return false; }
               else if (currentboard[y+1][x+1] == 'X') { return false; }
               else if (currentboard[y+1][x] == 'X') { return false; }
               else { return true; }
               break;
            case 4:
               if (currentboard[y][x-1] == 'X') { return false; }
               else if (currentboard[y][x+1] == 'X') { return false; }
               else if (currentboard[y+1][x-1] == 'X') { return false; }
               else { return true; }
               break;
         }
         break;
      }
      case 5: { // S-piece
         if (orientation == 1 || orientation == 3) {
            if (currentboard[y-1][x-1] == 'X') { return false; }
            else if (currentboard[y][x-1] == 'X') { return false; }
            else { return true; }
         }
         else if (orientation == 2 || orientation == 4) {
            if (currentboard[y][x+1] == 'X') { return false; }
            else if (currentboard[y+1][x-1] == 'X') { return false; }
            else { return true; }
         }
         break;
      }
      case 6: { // T-piece
         switch (orientation) { // Based on the orientation of the current piece
            case 1:
               if (currentboard[y-1][x] == 'X') { return false; }
               else { return true; }
               break;
            case 2:
               if (currentboard[y][x+1] == 'X') { return false; }
               else { return true; }
               break;
            case 3:
               if (currentboard[y+1][x] == 'X') { return false; }
               else { return true; }
               break;
            case 4:
               if (currentboard[y][x-1] == 'X') { return false; }
               else { return true; }
               break;
         }
         break;
      }
      case 7: { // Z-piece
         if (orientation == 1 || orientation == 3) {
            if (currentboard[y+1][x-1] == 'X') { return false; }
            else if (currentboard[y-1][x] == 'X') { return false; }
            else { return true; }
         }
         else if (orientation == 2 || orientation == 4) {
            if (currentboard[y+1][x] == 'X') { return false; }
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
   if (orientation == 4){ orientation = 1; } // Resets the orientation
   else { orientation++; } // Keeps switching the orientation of the Tetris piece 
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
               if (currentboard[y+1][x+i] == 'X') { count++; }
            }
         }
         else if (orientation == 2 || orientation == 4){
            if (currentboard[y+3][x] == 'X') { count++; }
         }
         if (count != 0) { return true; }
         else { return false; }
         break;
      case 2: // J-piece
         switch (orientation) {
            case 1:
               for (int i = -1; i <= 1; i++) {
                  if (i == -1 || i == 0) {
                     if (currentboard[y+1][x+i] == 'X') { count++; }
                  }
                  else if (i == 1) {
                     if (currentboard[y+2][x+i] == 'X') { count++; }
                  }
               }
               break; 
            case 2:
               if (currentboard[y+2][x-1] == 'X' || currentboard[y+2][x] == 'X'){ count++; }
               break;
            case 3:
               for (int i = -1; i <= 1; i++) {
                  if (currentboard[y+1][x+i] == 'X') { count++; }
               }
               break;
            case 4:
               if (currentboard[y+2][x] == 'X' || currentboard[y][x+1] == 'X'){ count++; }
               break;
         }  
         if (count != 0) { return true; }
         else { return false; }
         break; 
      case 3: // L-piece
         switch (orientation){
            case 1: 
               for (int i = -1; i <= 1; i++) {
                  if (i == 1 || i == 0) {
                     if (currentboard[y+1][x+i] == 'X') { count++; }
                  }
                  else if (i == -1) {
                     if (currentboard[y+2][x+i] == 'X') { count++; }
                  }
               }
               break; 
            case 2:
               if (currentboard[y+2][x] == 'X' || currentboard[y][x-1] == 'X'){ count++; }
               break;
            case 3:
               for (int i = -1; i <= 1; i++) {
                  if (currentboard[y+1][x+i] == 'X') { count++; }
               }
               break;
            case 4:
               if (currentboard[y+2][x] == 'X' || currentboard[y+2][x+1] == 'X'){ count++; }
               break;
         }  
         if (count != 0) { return true; }
         else { return false; }
         break;
      case 4: // O-piece
         if (currentboard[y+2][x] == 'X' || currentboard[y+2][x+1] == 'X') { 
            count++;
         }
         if (count != 0) { return true; }
         else { return false; }
         break;
      case 5: // S-piece
         if (orientation == 1 || orientation == 3) {
            if (currentboard[y+2][x-1] == 'X') { count++; }
            if (currentboard[y+2][x] == 'X') { count++; }
            if (currentboard[y+1][x+1] == 'X') { count++; }
         }
         else if (orientation == 2 || orientation == 4) {
            if (currentboard[y+1][x-1] == 'X') { count++; }
            if (currentboard[y+2][x] == 'X') { count++; }
         }
         if (count != 0) { return true; }
         else { return false; }
         break;
      case 6: // T-piece
         switch (orientation){
            case 1:
               for (int i = -1; i <= 1; i++) {
                  if (i == -1 || i == 1) {
                     if (currentboard[y+1][x+i] == 'X') { count++; }
                  }
                  else if (i == 0) {
                     if (currentboard[y+2][x+i] == 'X') { count++; }
                  }
               }
               break; 
            case 2:
               if (currentboard[y+1][x-1] == 'X' || currentboard[y+2][x] == 'X'){ count++; }
               break;
            case 3:
               for (int i = -1; i <= 1; i++) {
                  if (currentboard[y+1][x+i] == 'X') { count++; }
               }
               break;
            case 4:
               if (currentboard[y+2][x] == 'X' || currentboard[y+1][x+1] == 'X'){ count++; }
               break;
         }  
         if (count != 0) { return true; }
         else { return false; }
         break;  
      case 7: // Z-piece
         if (orientation == 1 || orientation == 3) {
            if (currentboard[y+2][x+1] == 'X') { count++; }
            if (currentboard[y+2][x] == 'X') { count++; }
            if (currentboard[y+1][x-1] == 'X') { count++; }
         }
         else if (orientation == 2 || orientation == 4) {
            if (currentboard[y+2][x-1] == 'X') { count++; }
            if (currentboard[y+1][x] == 'X') { count++; }
         }
         if (count != 0) { return true; }
         else { return false; }
         break;
   }
}

void Tetrisboard::clearLine() // Clears the row that is completely filled  
{
   int count = 0, color, row;
   bool clear = false;
cout << "a" << endl;

   for (int i = 0; i < SIZE1; i++) { cout << "b" << endl;  // Goes through the rows
      for (int j = 0; j < SIZE2; j++) { cout << "c" << endl; // Goes through the columns
         if (currentboard[i][j] == 'X') { count++; cout << "d" << endl; } // Checks to see if there is an 'X' in the row and increments 'count' when there is
         if (count == SIZE2) { row = i; clear = true;  cout << "e" << endl; } // When the row is completely full
         if (clear) { cout << "f" << endl; // If the row should be cleared
            for (int i = 1; i <= row; i++) { cout << "g" << endl; // Goes through the row
               for (int j = 0; j < SIZE2; j++) { cout << "h" << endl; // Goes through the column
                  tempboard[i][j] = currentboard[i-1][j]; // Becomes the row that was above the cleared row
                  tempcolorboard[i][j] = colorboard[i-1][j]; // Becomes the row that was above the cleared row
                  color = tempcolorboard[i][j]; // Sets the color on the board
                  switch (color) { cout << "i" << endl;
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
      count = 0; // Clears count back to zero
   }
   if (clear) { // When the row should be cleared
      for (int i = 0; i <= row; i++) { // Goes through the row
         for (int j = 0; j < SIZE2; j++) { // Goes through the columns
            currentboard[i][j] = tempboard[i][j]; // Shifts the board down
            colorboard[i][j] = tempcolorboard[i][j]; // Shifts the colors/pieces on the board down
         }
      }
   }
}
