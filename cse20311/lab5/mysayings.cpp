/* Program: mysayings.cpp
 * Author: Roann Yanes
 * This program will store and manage many of sayings, and will ask the user for a "startup" data file, one that will contain some initial sayings. It will then display a menu of options for the user.
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

void menu(); // prototype
void displaysayings(vector<string> &sayings); // prototype
void newsayings(vector<string> &sayings); // prototype
void stringsearch(vector<string> &sayings); // prototype
void savefile(vector<string> &sayings, string); // prototype

int main()
{
  vector<string> sayings; // initialization of vector
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
  }

  while (choice != 5) // displays menu and runs the program until user decides to quit
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
      case 5: // exits the program (option 5)
      break;
    }
    menu();
    cin >> choice;
    if (choice < 1 || choice > 5) 
    {
      cout << "Error: Invalid Input!" << endl;
      return 0;
    }
  }
  cout << "Thank you!" << endl;
  return 0;
}

// creation of functions to use in function main()

void menu() // function to display menu options to the user
{
  cout << "What would you like to do?" << endl; 
  cout << "1: display sayings currently in the database" << endl;
  cout << "2: enter a new saying into the database" << endl;
  cout << "3: list sayings that contain a given word entered by the user" << endl;
  cout << "4: save all sayings in a new text file" << endl;
  cout << "5: quit the program" << endl;
  cout << "Enter your choice: "; // displays input message to the user
}

void displaysayings(vector<string> &sayings) // function for option 1 of the program (display all sayings)
{ 
  for (int i = 0; i < sayings.size(); i++)
  {
    cout << "> " << sayings[i] << endl;
  }
}
  
void newsayings(vector<string> &sayings) // function for option 2 of the program (input a new saying)
{
  string newphrase;
  cin.ignore();
  getline(cin, newphrase);
  sayings.push_back(newphrase);
}

void stringsearch(vector<string> &sayings) // function for option 3 of the program (list sayings that contain a given word) 
{
  string substring;
  cin.ignore();
  getline(cin, substring);
  for (int i = 0; i < sayings.size(); i++)
  {
    string tempstring;
    tempstring = sayings[i];
    if (tempstring.find(substring) != -1)
    {
      cout << sayings[i] << endl;
    }
  } 
}

void savefile(vector<string> &sayings, string newfile) // function for option 4 of the program (save all sayings in a new text file)
{
  ofstream outputFile;
  outputFile.open(newfile);
  for (int i = 0; i < sayings.size(); i++)
  {
    outputFile << sayings[i] << endl;
  }
  outputFile.close();
}


