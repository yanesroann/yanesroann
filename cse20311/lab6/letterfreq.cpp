/* Program: letterfreq.cpp
 * Author: Roann Yanes
 * This program counts the frequency of each letter of the alphabet as they occur in text contained in a text file.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
  int frequency[26] = {0}; // initialization of array
  char letter;
  ifstream file;
  string filename;

  cout << "Enter data file name: "; // asks the user for a data file 
  cin >> filename;
  file.open(filename);

  if(!file) // checks if the data file is a valid one and ends if it is not
  {
    cout << "Error opening file: " << filename << endl;
    return 1;
  }
  
 
  int whitespaces; // intitialization of all variables
  float sumofspaces = 0;
  float percentofspace = 0;
  float characters = 0;

  
  letter = file.get(); // gets a single character
  while(!file.eof()) // runs until the end of file is reached
  {
    whitespaces = letter;
    if (isspace(whitespaces)) // checks if the character is a white space
    {
      sumofspaces++; // sums the number of white spaces
    }
    else if (isalpha(letter)) // checks if the character is letter 
    {
      letter = tolower(letter); // lowers the characters that are uppercase so that the ASCII values are in a row
      frequency[letter - 97]++; // to start at 'a'
    }
  characters++; // sums the number of characters in the file at the end of the while loop
  letter = file.get(); // gets a single character value
  }    
   
 
  letter = 'a';
  int sumofletters = 0;
  for (int k = 0; k < 26; k++) // outputs a counter for all letters in the alphabet 
  {
    cout << letter << ": " << frequency[k] << endl;
    sumofletters += frequency[k];
    letter++;
  }
  
  // messages to display to the user at the end of reading

  percentofspace = (sumofspaces)/(characters) * 100; // calculation to find the percentage of space in the file
  cout << endl;
  cout << "There were " << fixed << setprecision(0) << sumofletters << " total letters." << endl;
  cout << "There were " << fixed << setprecision(0)<< characters << " total characters." << endl;
  cout << "There were " << fixed << setprecision(0) << sumofspaces << " white space characters." << endl;
  cout << "The space percentage is: " << setprecision(3) << percentofspace << "%" << endl;

  return 0;
}
