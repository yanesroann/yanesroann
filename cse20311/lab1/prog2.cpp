// Program displays and calculates the number of points scored by the football team
#include <iostream> // enables program to output data to the screen
using namespace std;

// function main begins program execution
int main() {

// declaring and initializing variables
int touchdowns = 0;
int extrapoints = 0;
int fieldgoals = 0;
int safeties = 0;
int sum = 0;

cout << "Please enter the number of touchdowns: "; // Prompts user for input
cin >> touchdowns;

cout << "Please enter the number of extra points: ";
cin >> extrapoints;

cout << "Please enter the number of field goals: ";
cin >> fieldgoals;

cout << "Please enter the number of safeties: ";
cin >> safeties;

sum = 6* touchdowns + extrapoints +  3*fieldgoals +  2*safeties; 

cout << "The total number of points scored by the team is " << sum << endl;

}
