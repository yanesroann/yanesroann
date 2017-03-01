// Final Project
// final.cpp
// Grace Milton and Roann Yanes

#include <iostream>
#include <unistd.h>
#include <time.h>
using namespace std;
#include "tetrisboard.h"
#include "gfxnew.h"

void title();
void goodjob();

int main()
{
   Tetrisboard board;
   bool run = true, check;
   int count = 0; 
   int event, r, g, b, shape, bottom, o;
   char command, junk;
   bool end, open;
   srand(time(NULL));

   gfx_open(600,600,"Tetris"); // Opens window
   gfx_clear();

   board.initialize(); // Initializes all arrays
   board.drawLines(); // Draws lines on gfx window
   while(run) {
      gfx_color(0,255,255);
      gfx_fill_rectangle(300,0,5,600); // Draws cyan barrier between board and right side of window
      title(); // displays "TETRIS"
      gfx_text(330,260, "Brought to you by G$ and the Cicada Menace!"); // Displays text
      gfx_color(255,0,0);
      // Displays instructions
      gfx_text(370,310, "Press left arrow to move left");
      gfx_text(366,330, "Press right arrow to move right");
      gfx_text(403,350, "Press 'r' to rotate");
      gfx_text(410,370, "Press 'q' to quit");
      board.setOrientation(1); // Starts all shapes in orientation 1
      shape = rand() % 7 + 1; // Randomly chooses shape
      board.setShape(shape); // Sets shape
      board.addblock(5,0); // Adds block at same starting position each time
      board.drawLines(); // Draws lines on board
      o = board.getOrientation(); // Gets orientation of piece
      switch (shape) { // Makes sure piece stops at bottom boundary based on its shape
         case 1:
            bottom = SIZE1 - 1;
            break;
         case 2:
         case 3:
         case 4:
         case 5:
         case 6:
         case 7:
            bottom = SIZE1 - 2;
            break;
      }
      // Piece falls until it reaches bottom boundary
      for (int i = 0; i < bottom; i++) {
         check = board.checkbelow(); // Checks if there is a piece below current piece
         if (check) { 
            // Checks if row needs to be cleared four times (max amount of rows that can be cleared at once)
            for (int i = 0; i < 4; i++) {
               board.clearLine();
            }
            end = board.getEndgame(); // Checks if game over
            if (end) { // Displays "Good job" for 10 seconds if game over
               gfx_clear();
               for (int j = 0; j < 10; j++) {
                  goodjob();
                  usleep(1000000);
               }
               run = false; // Sets run to false close window 
            }
            break; 
         }       
         board.fall(); // Makes piece fall
         usleep(160000); // Pauses
         board.drawLines(); // Draws lines on screen
         if (i == bottom - 1) { // Also checks if row needs to be cleared if piece reaches bottom boundary
            for (int i = 0; i < 4; i++) {
               board.clearLine(); 
            }
         }
         open = board.openRotate(); // Checks to see if piece has room to rotate
         switch (shape) { // Accounts for piece rotating off screen at bottom
            case 1:
               if (o == 1 || o == 3) { 
                  if (i >= bottom - 3) { open = false; } 
               }
               break;
            case 2:
            case 3:
            case 6:
               if (o == 3) { 
                  if (i >= bottom - 1) { open = false; }
               }
               break;        
         }
         event = gfx_event_waiting(); // Waits for user input of some kind in the graphics window
         switch (event) {
            case 1:
               command = gfx_wait();   
               switch (command) {
                  case 'Q': // Shifts the current piece left when left arrow key pressed
                     board.moveLeft();
                     break;
                  case 'S': // Shifts the current piece right when right arrow key pressed
                     board.moveRight();
                     break;
                  case 'r': // Rotates piece when 'r' pressed
                     if (open) {
                        board.rotate(); // Rotates piece
                        o = board.getOrientation(); // Gets orientation
                        switch (shape) { // Changes how far piece can fall based on orientation
                           case 1:
                              if (o == 1 || o == 3) { bottom = SIZE1 - 1; }
                              else if (o == 2 || o == 4) { bottom = SIZE1 - 3; }
                              break;
                           case 2:
                           case 3: 
                           case 6:
                              if (o == 3) { bottom = SIZE1 - 1; }
                              else { bottom = SIZE1 - 2; }
                              break;
                           case 5:
                           case 7:
                              bottom = SIZE1 - 2;
                              break;
                        }
                     }
                     break;
                  case 'q': // Quits when 'q' is pressed
                     run = false; // Exits while loop
                     break;
               }
               break;
            case 2:
            case 3:
            case 4:
            case 5:
               junk = gfx_wait(); // Makes sure unwanted inputs don't queue up
               break; 
         }
      }
   }
   return 0;
}

// Creates TETRIS in polygons
void title()
{
   // T
   gfx_color(255,0,0);
   XPoint letter1[] = {{315,200}, {360,200}, {360,215}, {345,215}, {345,245},{330,245},{330,215},{315,215}};
   gfx_fill_polygon(letter1,8);
   // E
   gfx_color(255,128,0);
   XPoint letter2[] = {{360,200}, {405,200}, {405,215}, {375,215}, {375,220}, {390,220}, {390,225},{375,225},{375,230},{405,230},{405,245},{360,245}};
   gfx_fill_polygon(letter2,12);
   // T
   gfx_color(255,255,0);
   XPoint letter3[] = {{405,200}, {450,200}, {450,215}, {435,215}, {435,245},{420,245},{420,215},{405,215}};
   gfx_fill_polygon(letter3,8);
   // R
   gfx_color(0,255,0);
   XPoint letter4[] = {{450,200}, {495,200}, {495,222}, {480,222}, {495,245},{480,245},{465,230},{465,245},{450,245}};
   gfx_fill_polygon(letter4,9);
   // I
   gfx_color(0,255,255);
   XPoint letter5[] = {{495,200}, {540,200}, {540,215}, {525,215}, {525,230},{540,230},{540,245},{495,245},{495,230},{510,230},{510,215},{495,215}};
   gfx_fill_polygon(letter5,12);
   // S
   gfx_color(255,0,255);
   XPoint letter6[] = {{540,200}, {585,200}, {585,215}, {555,215}, {585,230},{585,245},{540,245},{540,230},{555,230},{540,215}};
   gfx_fill_polygon(letter6,10);
}

// Creates GOOD JOB in polygons
void goodjob()
{
   // G
   gfx_color(255,0,0);
   XPoint letter7[] = {{100,200}, {145,200}, {145,215}, {115,215}, {115,230},{130,230},{130,225},{120,225},{120,220},{145,220},{145,245},{100,245}};
   gfx_fill_polygon(letter7,12);
   // O
   gfx_color(255,128,0);
   gfx_fill_rectangle(145,200,45,45);
   gfx_color(0,0,0);
   gfx_fill_rectangle(160,215,15,15);
   // O
   gfx_color(255,255,0);
   gfx_fill_rectangle(190,200,45,45);
   gfx_color(0,0,0);
   gfx_fill_rectangle(205,215,15,15);
   // D
   gfx_color(0,255,0);
   XPoint letter8[] = {{235,200}, {265,200}, {280,215}, {280,230}, {265,245},{235,245}};
   gfx_fill_polygon(letter8,6);
   gfx_color(0,0,0);
   XPoint letter9[] = {{250,215}, {265,215}, {270,220}, {270,225}, {265,230},{250,230}};
   gfx_fill_polygon(letter9,6);
   // J
   gfx_color(0,255,255);
   XPoint letter10[] = {{280,230}, {310,230}, {310,200}, {325,200}, {325,245},{280,245}};
   gfx_fill_polygon(letter10,6);
   // O
   gfx_color(255,0,255);
   gfx_fill_rectangle(325,200,45,45);
   gfx_color(0,0,0);
   gfx_fill_rectangle(340,215,15,15);
   // B
   gfx_color(128,0,255);
   gfx_fill_rectangle(370,200,45,45);
   gfx_color(0,0,0);
   gfx_fill_rectangle(385,209,15,9);
   gfx_fill_rectangle(385,227,15,9);
}
