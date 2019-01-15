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
void deletesaying(list<string> &sayings, int); // prototype
void sortlist(list<string> &sayings, string); // prototype

int main()
{
  list<string> sayings; // initialization of array 
  int choice, removechoice;
  string newfile, newphrase, substring;
  string filename;
  ifstream ifs; 
  string strObject;

  cout << "Enter data file name: "; // asks the user for a data file 
  cin >> filename;
  ifs.open(filename);

  if(!ifs) // checks if the data file is a valid one and ends if it is not
  {
    cout << "Error opening file: " << filename << endl;
    return 1;
  }

 
  while (!ifs.eof()) // reads in the text file and sorts it in alphabetical order
  {
    getline(ifs, strObject);  
    if (strObject.empty()) 
    {
      continue;  
    }
    sortlist(sayings, strObject);
  }
 
  menu(); // displays menu
  cin >> choice;

  if (choice < 1 || choice > 6) // displays error message if choice does not equal a number from one through five
  {
    cout << "Error: Invalid Input!" << endl;
    return 0;
  }

  while (choice != 6) // displays menu and runs the program until user decides to quit
  {
    switch (choice)
    {
      case 1: // runs the function for option 1 of the program
      cout << "The sayings in the file are:" << endl;
      displaysayings(sayings);
      cout << endl;
      break;
      case 2: // runs the function for option 2 of the program
      cout << "Enter a new phrase to input into the file: ";
      newsayings(sayings);
      cout << "Added!" << endl;
      cout << endl;
      break;
      case 3: // runs the function for option 3 of the program
      cout << "Enter a word (substring) to search for in the data file: ";
      stringsearch(sayings);
      cout << endl;
      break;
      case 4: // runs the function for option 4 of the program
      cout << "Enter the name of the file to save the phrases: ";
      cin >> newfile;
      savefile(sayings, newfile);
      cout << "Saved!" << endl;
      cout << endl;
      break;
      case 5: // runs the function for option 5 of the program
      cout << "Enter the number of the saying you would like to delete: ";
      cin >> removechoice;
      deletesaying(sayings, removechoice);
      cout << "Removed!" << endl;
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

void menu() // function to display menu options to the user
{
  cout << "What would you like to do?" << endl; 
  cout << "1: display sayings currently in the database" << endl;
  cout << "2: enter a new saying into the database" << endl;
  cout << "3: search sayings that contain a given word" << endl;
  cout << "4: save all sayings in a new text file" << endl;
  cout << "5: remove a saying" << endl;
  cout << "6: quit the program" << endl;
  cout << "Enter your choice: "; // displays input message to the user
}

void displaysayings(list<string> &sayings) // function for option 1 of the program (display all sayings)
{
  int counter = 0;
  auto it = sayings.begin();
  for (it = sayings.begin(); it != sayings.end(); it++)
  {
    cout << ++counter << "  " <<  *it << endl;
  }
}
  
void newsayings(list<string> &sayings) // function for option 2 of the program (input a new saying)
{
  string newphrase;
  cin.ignore();
  getline(cin, newphrase);
  sortlist(sayings, newphrase);
}

void stringsearch(list<string> &sayings) // function for option 3 of the program (list sayings that contain a given word) 
{
  string substring;
  cin.ignore();
  getline(cin, substring);
  int matches = 0;
  auto it = sayings.begin();
  for (it = sayings.begin(); it != sayings.end(); it++)
  {
    string tempstring;
    tempstring = *it;
    if (tempstring.find(substring) != string::npos)
    {
      cout << "> " << *it << endl;
      matches = 1;
    }
  } 
  if (matches == 0) // message if there are no matches are found
  {
    cout << "There are no phrases that match this term in the database." << endl;
  }
}

void savefile(list<string> &sayings, string newfile) // function for option 4 of the program (save all sayings in a new text file)
{
  ofstream outputFile;
  outputFile.open(newfile);
  for (auto it = sayings.begin(); it != sayings.end(); ++it)
  {
    outputFile << *it << endl;
  }
  outputFile.close();
}

void deletesaying(list<string> &sayings, int removechoice) // function for option 5 (delete saying from list)
{
  displaysayings(sayings);
  cout << endl;
  string removephrase;
  removechoice = removechoice - 1;
  auto it = sayings.begin();
  advance(it, removechoice);
  for (auto k = sayings.begin(); k != sayings.end(); ++k)
  {
    if (k == it)
    {
      removephrase = *k;
    }
  }
  sayings.remove(removephrase);
  cout << "'" << removephrase << "'" << " is being removed from the database." << endl;
}

void sortlist(list<string> &sayings, string newphrase) // function to insert sayings into alphabetical order
{
  auto it = sayings.begin();
  while(newphrase.compare(*it) > 0 && it != sayings.end())
  {
    it++;
  }
  sayings.insert(it, newphrase);
}
