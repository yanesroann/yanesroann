// Final Project
// tetrisboard_gfx.h
// Grace Milton and Roann Yanes

#

const int SIZE1 = 20; // number of rows
const int SIZE2 = 10; // number of columns
extern int R, G, B;

class Tetrisboard {
  public: // methods
     Tetrisboard(); // default constructor
     ~Tetrisboard(); // destructor

     // get and set methods 
     int getx();
     int gety();
     int getRed();
     int getGreen();
     int getBlue();
     int getShape();
     int getOrientation();
     bool getEndgame();
     void setx(int);
     void sety(int);     
     void setColor(int, int, int);
     void setShape(int);
     void setOrientation(int);
     void setEndgame(bool);

     // utility methods
     void initialize();
     void drawLines();
     void displayArray();
     void addblock(int, int);
     void removeblock(int, int);
     void fall();
     void moveLeft();
     void moveRight();
     bool openRotate();
     void rotate();
     bool checkbelow();
     void clearLine();
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
