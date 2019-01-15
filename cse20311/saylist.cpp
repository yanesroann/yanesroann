/* Program: saylist.cpp
 * Author: Roann Yanes
 * This program will store and manage many of sayings, and will ask the user for a "startup" data file, one that will contain some initial sayings. It will then display a menu of options for the user.
 */

#include <iostream>
#include <list>
#include <string>
#include <fstream>
using namespace std;

void menu(); // prototype
void displaysayings(list<string> &sayings); // prototype
void newsayings(list<string> &sayings); // prototype
void stringsearch(list<string> &sayings); // prototype
void savefile(list<string> &sayings, string); // prototype

int main()
{
  list<string> sayings; // initialization of array
  int choice;
  string newfile;
  string filename;
  ifstream ifs; 
  string strObject;

  cout << "Enter data file name: "; // asks the user for a data file 
  cin >> filename;
  ifs.open(filename);

  if(!ifs) // checks if the data file is a valid one
  {
    cout << "Error opening file: " << filename << endl;
    return 1;
  }

  getline(ifs, strObject);
  while (!ifs.eof()) // reads in the text file 
  {
    sayings.push_back(strObject);
    getline(ifs, strObject);
  }
 
  menu(); // displays menu
  cin >> choice;

  if (choice < 1 || choice > 5) // displays error message if choice does not equal a number from one through five
  {
    cout << "Error: Invalid Input!" << endl;
    return 0;
