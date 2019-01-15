/* Program: statemain.cpp
 * Author: Roann Yanes
 * This program is a driver to test the State class, and it reads the data into a vector, and then displays it all; it also informs a user of basic information on US states.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

#include "state.h" // includes the class interface 

void displayall(vector<State> &); // prototype
void menu(); // prototype
void statesearch(vector<State> &, string); // prototype
void populationsearch(vector<State> &, int); // prototype
void yearsearch(vector<State> &, int); // prototype
void capitalsearch(vector<State> &, string); // prototype
 
int main()
{
  ifstream ifs;
  string infilename;
  string abbrev, name, cap, pop_s, yr_s, rep_s, abbsearch, cpsearch;
  int pop, yr, rep, choice, popsearch, yrsearch;
  vector<State> states; // initialization of vector
  State sta; // makes use of the State class

  cout << "Enter the data file name: "; // asks the user for a data file name
  cin >> infilename;
  ifs.open(infilename);
  if (!ifs) // checks if the data file is a valid one 
  {
    cout << "Error opening file: " << infilename << endl;
    return 1;
  }

  char c = ifs.peek(); // peeks next character
  while(c != EOF) // reads in the ".csv" file
  {
    getline(ifs, abbrev, ','); // "," is the delimiter
    getline(ifs, name, ',');
    getline(ifs, cap, ',');
    getline(ifs, pop_s, ','); // stores population as string
    getline(ifs, yr_s, ',');
    getline(ifs, rep_s, '\n'); 
    pop = stoi(pop_s); // converts the population from str to int
    yr = stoi(yr_s); // converts the year from str to int
    rep = stoi(rep_s); // converts the representatives from str to int
    sta = State(abbrev, name, cap, pop, yr, rep);
    states.push_back(sta); // adds the state and its data to the vector
    c = ifs.peek();
  }
  
  menu(); // displays menu
  cin >> choice;
  if (choice < 1 || choice > 6) // displays error message if choice does not equal a number from one through six
  {
    cout << "Error: Invalid Input!" << endl;
    return 0;
  }
  while (choice != 6) // displays menu and runs the program until user decides to quit
  {
    switch (choice) // corresponds to the options in the menu
    {
      case 1: // runs the function for option 1 of the program
      cout << "The states in the file are:" << endl;
      displayall(states);
      break;
      case 2: // runs the function for option 2 of the program
      cout << "Enter the abbreviation of the state you want to search for: ";
      cin >> abbsearch;
      statesearch(states, abbsearch);
      break;
      case 3: // runs the function for option 3 of the program
      cout << "Enter the population size to search for in the database: ";
      cin >> popsearch;
      populationsearch(states, popsearch);
      break;
      case 4: // runs the function for option 4 of the program
      cout << "Enter the year to search for in the database: ";
      cin >> yrsearch;
      yearsearch(states, yrsearch);
      break;
      case 5: // runs the function for option 5 of the program
      cout << "Enter the abbreviation of the state you want to search for: ";
      cin >> cpsearch;
      capitalsearch(states, cpsearch);
      break;
      case 6: // exits the program (option 6)
      break;
    }
    menu();
    cin >> choice;
    if (choice < 1 || choice > 6) 
    {
      cout << "Error: Invalid Input!" << endl;
      return 0;
    }
  }

  cout << "Thank you!" << endl;
  return 0;

}

// creation of functions to use in main()

void menu()
{ 
  cout << endl;
  cout << "Welcome to the U.S. States Database!" << endl;
  cout << "What would you like to do?" << endl; 
  cout << "    " << "1: display all states and their data currently in the database" << endl;
  cout << "    " << "2: display all the data for a given state" << endl;
  cout << "    " << "3: display states with at least \"N\" population size" << endl;
  cout << "    " << "4: display states that were given statehood in a given year" << endl;
  cout << "    " << "5: display the capital of a given state" << endl;
  cout << "    " << "6: quit the program" << endl;
  cout << "Enter your choice: "; // displays input message to the user
}

void displayall(vector<State> &s) // displays all states and their stats (option 1 of the program)
{
  for (auto it = s.begin(); it != s.end(); ++it) 
  {
    cout << endl;
    it->print(); // utility method in State class
  }
}

void statesearch(vector<State> &s, string abbsearch) // function for option 2 of the program (search for a given state) 
{
  int matches = 0;
  for (auto it = s.begin(); it != s.end(); it++)
  {
    string tempabb;
    tempabb = it->getAbbrev(); // same as (*it).getAbbrev() pointer
    if (tempabb == abbsearch) // abbreviation user enters must be equal to abbreviation in database
    {
      cout << endl;
      it->print(); // utility method in State class
      matches = 1;
    }
  } 
  if (matches == 0) // message if there are no matches found (incorrect abbreviation)
  {
    cout << endl;
    cout << "Error: There are no states that match this abbreviation in the database." << endl;
    cout << "Please enter a valid abbrevation (must be uppercase letters)." << endl;
  }
}

void populationsearch(vector<State> &s, int popsearch) // function for option 3 of the program (search for states by population size)
{
  int matches = 0;
  for (auto it = s.begin(); it != s.end(); it++)
  {
    int temppop;
    temppop = it->getPopulation();
    if (temppop >= popsearch)
    {
      cout << endl;
      it->printPopulation(); // utility method for population     
      matches = 1;
    }
  } 
  if (matches == 0) // message if there are no matches found (and/or if there is an incorrect input)
  {
    cout << endl;
    cout << "There are no states that match this population size in the database." << endl;
  }
}

void yearsearch(vector<State> &s, int yrsearch) // function for option 4 of the program (search for states by statehood)
{
  int matches = 0;
  for (auto it = s.begin(); it != s.end(); it++)
  {
    int tempyear;
    tempyear = it->getYear(); // pointer
    if (tempyear == yrsearch)
    {
      cout << endl;
      it->printYear(); // utility method for year 
      matches = 1;
    }
  } 
  if (matches == 0) // message if there are no matches found (and/or if there is an incorrect input)
  {
    cout << endl;
    cout << "No states were admitted to the union in " << yrsearch << "." << endl;
  }
}

void capitalsearch(vector<State> &s, string cpsearch) // function for option 5 of the program (search for the capital of a state)
{
  int matches = 0;
  for (auto it = s.begin(); it != s.end(); it++)
  {
    string tempcp;
    tempcp = it->getAbbrev();
    if (tempcp == cpsearch) // abbreviation user enters must be equal to abbreviation in database
    {
      cout << endl;
      it->printCapital();
      matches = 1;
    }
  } 
  if (matches == 0) // message if there are no matches found (and/or if there is an incorrect input)
  {
    cout << endl;
    cout << "Error: no states match this abbreviation." << endl;
    cout << "Please enter a valid abbreviation (must be uppercase letters)." << endl;
  }
}
