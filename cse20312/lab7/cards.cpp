/* Program: cards.cpp
 * Author: Roann Yanes
 * This program reads in a series of cardholders and their corresponding cards, and then display the cardholders in the order of highest card value to lowest.
 */

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


class CardHolders
{
  public:
    CardHolders(string = " ", int = 0, char = ' '); // constructor with default values
    ~CardHolders(); // deconstructor
    char suit; // variable to store the suit
    int rank; // variable to store that rank
    string name; // variable to store the name
    int personRank; // assigns the cardholder a value based on the card value he/she has    
};

CardHolders::CardHolders(string n, int r, char s) // constructor with default values
{
  name = n; // sets the name variable
  rank = r; // sets the rank variable
  suit = s; // sets the suit variable

  if (rank > 10) // checks to see if a J, Q, K, or A was entered
  {
    switch (rank)
    {
      case 74: // ASCII value for J
        rank = 11; // assigns new rank value
        break;
      case 81: // ASCII value for Q
	rank = 12; // assigns new rank value
	break;
      case 75: // ASCII value for K
	rank = 13; // assigns new rank value
	break;
      case 65: // ASCII value for A
	rank = 14; // assigns new rank value
	break;
    }
  }
  int suit_num; // variable to store suit value based on the suit entered
  switch (suit) // assigns a numerical suit value based on the suit value the user entered
  {
    case 'S':
	suit_num = 4; // highest suit
	break;
    case 'H':
	suit_num = 3;
	break;
    case 'D':
	suit_num = 2;
	break;
    case 'C':
	suit_num = 1; // lowest suit
	break;
  }
  personRank = rank * rank + suit_num; // assigns the cardholder a value (eventually used for ranking) based on the card value he/she has by completing simple math operation (adding the rank^2 + the suit_num value)
}

CardHolders::~CardHolders() { } // deconstructor

void sortCardHolders(vector<CardHolders> &, int); // function that uses bubble sort to sort the vector of CardHolders objects from highest to lowest

bool is_rank_num(const string &str); // function to check if the rank entered is an integer

int main(int argc, char *argv[])
{
  int numholders; // stores number of cardholders
  while (cin >> numholders && numholders > -1) // asks for input until the user enters -1
  {
    string name, s_rank;
    char suit;
    int rank;
    vector<CardHolders> cardholders; // declares a new vector that stores objects of the CardHolders class
    for(int it = 0; it < numholders; it++) // continues to add objects of the CardHolders class to the vector until the user enters a '-1'
    { 
      cin >> name; // reads in the value for the name
      cin >> s_rank; // reads in the value for the rank as a string
      if (is_rank_num(s_rank)) { rank = stoi(s_rank); } // converts the rank to a number if the user entered a number for the rank
      else { rank = int(s_rank[0]); } // typecast the string to act like an integer so that its ASCII value is used if J, Q, K, or A are entered
      cin >> suit; // reads in the value for the rank as a string
      CardHolders person(name, rank, suit); // adds these values to an instantiation of the CardHolders class
      cardholders.push_back(person); // adds the instantiated object to the vector of CardHolders objects
    }
    sortCardHolders(cardholders, numholders); // sorts the CardHolders objects vector using bubble sort
  } 
  return 0;
}

bool is_rank_num(const string &str) // function to check if the rank entered is an integer
{ return str.find_first_not_of("0123456789") == string::npos; } // uses the find_first_not_of() function

void sortCardHolders(vector<CardHolders> &cardHolders, int numholders) // function that uses bubble sort to sort the vector of CardHolders objects from highest to lowest
{
  int num_switch = 1; // value to enter the while loop
  CardHolders temp; 
  while (num_switch != 0)
  {
    num_switch = 0; // sets the value to exit the while loop
    for (int i = 0; i < numholders - 1; i++)
    {
      CardHolders a = cardHolders[i]; // variable that stores first CardHolders object in the vector
      CardHolders b = cardHolders[i+1]; // variable that stores second CardHolders object in the vector
      if (a.personRank < b.personRank) // uses bubble sort to sort the vector of cardholders in decreasing order
      {
        temp = cardHolders[i]; // stores the first CardHolders object in the vector in the temporary CardHolders object
	cardHolders[i] = cardHolders[i+1]; // shifts the location of the second CardHolders object
	cardHolders[i+1] = temp; // moves the object stored in the temporary CardHolders object to the second position in the array
	num_switch++; // increments to ensure that the while loop keeps running while the cardholders are not sorted in decreasing order
      }
    }
  }
  for (int i = 0; i < numholders - 1; i++) // prints out the cardholders in order of highest to lowest
  {
    cout << cardHolders[i].name << ", "; // prints out only the names of the cardholders
  }
  
  cout << cardHolders[numholders-1].name << endl; // prints out the final name
}
