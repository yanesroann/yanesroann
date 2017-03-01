// Final Project
// tetrisboard.h
// Grace Milton and Roann Yanes

const int SIZE1 = 20; // number of rows
const int SIZE2 = 10; // number of columns

class Tetrisboard {
  public: // methods
     Tetrisboard(); // default constructor
     ~Tetrisboard(); // destructor

     // get and set methods 
     int getx(); // Returns x-coordinate of tetris piece in array
     int gety(); // Returns x-coordinate of tetris piece in array
     int getRed(); // Returns R value of color
     int getGreen(); // Returns B value of color
     int getBlue(); // Returns G value of color
     int getShape(); // Returns number 1-7 corresponding to shape of current piece 
     int getOrientation(); // Returns number 1-4 corresponding to orientation of current piece
     bool getEndgame(); // Returns true boolean value when game over
     void setx(int); // Sets x-coordinate of tetris piece in array
     void sety(int); // Sets y-coordinate of tetris piece in array     
     void setColor(int, int, int); // Sets RGB color
     void setShape(int); // Sets number 1-7 corresponding to shape
     void setOrientation(int); // Sets number 1-4 corresponding to orientation
     void setEndgame(bool); // Sets boolean value to true when game over

     // utility methods
     void initialize(); // Initializes arrays for game play and color tracker
     void drawLines(); // Draws evenly spaced lines on board
     void displayArray(); // Displays array of Tetris board in terminal (useful for testing code)
     void addblock(int, int); // Adds a new Tetris piece to the board
     void removeblock(int, int); // Removes the pieces when rotating and falling by setting them to black
     void fall(); // Shifts the current Tetris piece down to make it appear as though it is falling
     void moveLeft(); // Shifts the current Tetris piece left as it is falling
     void moveRight(); // Shifts the current Tetris piece right as it is falling
     bool openRotate(); // Checks to see if there is space for the current piece to rotate
     void rotate(); // Rotates the current Tetris piece
     bool checkbelow(); // Checks if and where there is space for the current piece to be added to the board
     void clearLine(); // Clears the row that is completely filled
  private:  // attributes
     char currentboard[SIZE1][SIZE2];
     char tempboard[SIZE1][SIZE2];
     int colorboard[SIZE1][SIZE2];
     int tempcolorboard[SIZE1][SIZE2];
     int xcoord, ycoord;
     int red, green, blue;
     int shape, orientation;
     bool endgame;
};
