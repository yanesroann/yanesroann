// Final Project
// final.cpp
// Grace Milton and Roann Yanes

#include <iostream>
#include <unistd.h>
#include <time.h>
using namespace std;
#include "tetrisboard.h"
#include "gfxnew.h"

int main()
{
   Tetrisboard board;
   bool run = true, check;
   int count = 0;
   int event, r, g, b, shape, bottom, o;
   char command, junk;
   bool end, open;
   srand(time(NULL));

   gfx_open(600,600,"Tetris");
   gfx_clear();

   board.initialize();
   board.drawLines();
   board.displayArray();
   while(run) {
      board.setOrientation(1);
      shape = rand() % 7 + 1;
      board.setShape(shape);
      board.addblock(5,0);
      board.drawLines();
      board.displayArray();
      o = board.getOrientation();
      switch (shape) {
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
      for (int i = 0; i < bottom; i++) {
         check = board.checkbelow();
         if (check) { 
            end = board.getEndgame();
            if (end) { run = false; }
            break; 
         }       
         board.fall(); // Shifts the  
         usleep(160000);
         board.drawLines();
         board.displayArray();
         event = gfx_event_waiting(); // Waits for user input of some kind in the graphics window
         switch (event) {
            case 1:
               command = gfx_wait();   
               switch (command) {
                  case 'Q': // When the user presses the left arrow key
                     board.moveLeft(); // shifts the current piece left
                     break;
                  case 'S': // When the user presses the right arrow key
                     board.moveRight(); // shifts the current piece right
                     break;
                  case 'r': // When the user presses the 'r' key
                     open = board.openRotate(); // checks to see if the current piece has room to rotate
                     if (open) { // Enters the sitch case if the current piece is able to rotate              
                        board.rotate(); // rotates the current piece
                        o = board.getOrientation(); // determines the orientation of the shape
                        switch (shape) {
                           case 1:
                              if (o == 1 || o == 3) { bottom = SIZE1 - 1; }
                              else if (o == 2 || o == 4) { bottom = SIZE1 - 3; }
                              break;
                           case 2:
                              if (o == 3) { bottom = SIZE1 - 1; }
                              else { bottom = SIZE1 - 2; }
                              break;
                           case 3:
                              if (o == 3) { bottom = SIZE1 - 1; }
                              else { bottom = SIZE1 - 2; }
                              break; 
                           case 5:
                              bottom = SIZE1 - 2;
                              break;
                           case 6:
                              if (o == 3) { bottom = SIZE1 - 1; }
                              else { bottom = SIZE1 - 2; }
                              break;
                           case 7:
                              bottom = SIZE1 - 2;
                              break;
                        }
                     }
                     break;
                  case 'q':
                     run = false;
                     break;
               }
               break;
            case 2:
            case 3:
            case 4:
            case 5:
               junk = gfx_wait();
               break; 
         }
         if (i == bottom - 1) { board.clearLine(); }
      }
   }

   return 0;
}
