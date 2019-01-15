/* Program: rational.h
 * Author: Roann Yanes
 * This program is the class interface for a Rational.
 */

class Rational {
  public: // behavior (public functions)
    Rational(); // constructor
    Rational(int, int);
    ~Rational(); // destructor
    int getNumer(); // access method
    int getDenom(); 
    void setNumer(int); 
    void setDenom(int);
    void print();
    Rational add(Rational); // utility method
    Rational subtract(Rational); 
    Rational multiply(Rational); 
    Rational divide(Rational); 
  private: // attributes
    int numer;
    int denom;
};

