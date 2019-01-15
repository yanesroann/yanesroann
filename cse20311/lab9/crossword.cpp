/* Program: crossword.cpp
 * Authors: Grace Milton and Roann Yanes
 * This program, given a list of words, creates a blank crossword anagram puzzle that can be played with paper and pencil. The program will also provide a solution for the player who gets stuck.
 */
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "crossboard.h"
#include <vector>
#include <cstring>
#include <iomanip>

struct sortbysize // sorts the strings in order of size (longest to shortest)
{
  bool operator()(const string &string1, const string &string2) 
  {
    return string1.size() > string2.size();
  }
};

using namespace std;

int main()
{
  Crossboard crossword; // calls the Crossboard class
  vector<string> words; // stores the user-input strings in a vector
  vector<string> direction; // stores the direction of the words placed on the board 
  char words_arr[20][16], anagram[20][16]; // convert the "words" vector to cstrings
  string a; 
  int count = 1, z = 0, valid, x, b = 0;
  const char* word1;
  const char* word2;

  cout << "Either enter 20 words or less than 20 words, followed by a \".\": ";
  cin >> a; // words the user enters are stored as "a"
  words.push_back(a); // "a" is stored in "words" vector
  while (count < 20)  // only stores first 20 words
  {
    cin >> a;
    if (a.length() > 15) // error message if user enters a word with more than 15 letters
    {
      cout << endl;
      cout << "Word omitted because greater than 15 letters: " << a << endl;
      cout << endl;
      continue;
    }
    if ( a == ".") // reads in words until user enters a period
    {
      break;
    }
    words.push_back(a); // adds the word to the vector
    count++; // increases the count to make sure there are less than 20 words
  }
  sortbysize sbs; // calls the struct to sort strings by size
  sort(words.begin(), words.end(), sbs); // sorts the strings by size
  for (auto k = words.begin(); k != words.end(); k++,z++) // converts strings to cstrings 
  {
    strcpy(words_arr[z],k->c_str()); // copies the strings to cstrings
    for ( int i = 0; i < strlen(words_arr[z]); i++) // checks if all the characters in the string are letteres
    {
      if (!isalpha(words_arr[z][i])) // error message if a character is not a letter
      {
        cout << "Please enter only letters." << endl;
        return 1;
      }
      words_arr[z][i] = toupper(words_arr[z][i]); // converts all the letters to uppercase letters
    }
  }
  word1 = words_arr[0]; // calls the first element of the character array
  crossword.addfirst(word1); // adds the longest word to the board
  direction.push_back("Across"); // sets the direction of first word
  for (int i = 1; i < words.size(); i++) // adds the rest of the elements of the character array to the board
  {
    word2 = words_arr[i];
    valid = crossword.findmatch(word2); // finds a match for words in array
    if (valid == 3) // error message if word cannot be placed on the board
    {
      cout << endl;
      cout << "Not all words able to be placed!" << endl;
      cout<< endl;
      break;
    } 
    else if (valid == 1) // adds direction of word placed vertically to "direction vector"
    {
      direction.push_back("Down");
    }
    else if (valid == 2) // adds direction of word placed horizontally to "direction vector"
    {
      direction.push_back("Across");
    }
    crossword.addmore(word2, i, valid); // adds the rest of the words to the board
  }
  cout << "Solution:" << endl;
  cout << endl;
  crossword.displaySolution(); // displays the solution to the crossword puzzle
  cout << endl;
  cout << "Crossword puzzle:" << endl;
  cout << endl;
  crossword.displayBoard(); // displays the crossword puzzle
  cout << endl;
  for (int i = 0; i < words.size(); i++) // creates anagrams for each word on the board
  {
    random_shuffle(words[i].begin(), words[i].end()); // shuffles the letters in each word to make the clues
    boost::to_upper(words[i]); // makes the letters uppercase
  }
  cout << "Clues:" << endl;
  cout << endl;
  for (auto j = direction.begin(); j != direction.end(); j++, b++) // displays the clues in a formatted way
  {
    cout << setw(3) << crossword.getxCoordinate(b) <<  "," << setw(3) << crossword.getyCoordinate(b) << setw(17) << *j << setw(23) << words[b] << endl;
  }
  return 0;
}


