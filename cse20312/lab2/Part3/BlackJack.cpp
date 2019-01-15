/* Program: BlackJack.cpp
 * Author: Roann Yanes
 * This is the class implementation for the BlackJack class.
 */

#include <cstdlib>
#include <iostream>
#include "BlackJack.h"
#include "CardDeck.h"
using namespace std;

BlackJack::BlackJack() // default constructor
{
  Cards = new CardDeck[52]; // creates space for pointer-based array
}

BlackJack::~BlackJack() // deconstructor
{ 
  delete [] Cards; // release pointer-based array space
}

int BlackJack::deal() // deals out a card to either the dealer or the player when called
{ 
  int randomcard = 0, card = 0, value = 0;
  if (randomcard == 0 || randomcard >= 38)
  {
    Cards[0].shuffle(); // shuffles the cards only at the start of the game or when there are less than 15 cards in the deck (to create a new deck)
    if (randomcard >= 38) // if less than 15 cards remain in the deck
    {
      randomcard = 0;  // resets the counter to zero
    }
  }
  card = Cards[0].getCard(randomcard); // gets a random card from the array
  switch (card%13+2) // divides cards into 13 different values
  {
    case 2: // TWO
      card = 2;
      value = 2;
      cout << card;
      break;
    case 3: // THREE
      card = 3;
      value = 3;
      cout << card;
      break;
    case 4: // FOUR
      card = 4;
      value = 4;
      cout << card;
      break;
    case 5: // FIVE
      card = 5;
      value = 5;
      cout << card;
      break;
    case 6: // SIX
      card = 6;
      value = 6;
      cout << card;
      break;
    case 7: // SEVEN
      card = 7;
      value = 7;
      cout << card;
      break;
    case 8: // EIGHT
      card = 8;
      value = 8;
      cout << card;
      break;
    case 9: // NINE
      card = 9;
      value = 9;
      cout << card;
      break;
    case 10: // TEN
      card = 10;
      value = 10;
      cout << card;
      break;
    case 11: // JACK
      card = 11;
      value = 10;
      cout << "J";
      break;
    case 12: // QUEEN
      card = 12;
      value = 10;
      cout << "Q";
      break;
    case 13: // KING
      card = 13;
      value = 10;
      cout << "K";
      break;
    case 14: // ACE
      card = 14;
      value = 11;
      cout << "A";
      break;
  }
  randomcard++; // pulls a new card from the next position
  return value; // returns the face value of the random card
}

void BlackJack::play() // plays a game of Black Jack according to the rules
{
  int playerwins = 0, dealerwins = 0, decision = 0, dealersum = 0, playersum = 0;
  LOOP:
  {
    cout << "Let's play blackjack!" << endl << endl;
    cout << "Your cards: ";
    playersum = deal(); // first card for player
    cout << " and ";
    playersum = playersum + deal();  // second card for player
    cout << endl;
    cout << "Your sum: " << playersum << endl; // prints the sum of the two cards
    cout << endl;
    cout << "Dealer's cards: ";
    dealersum = deal(); // first card for the dealer
    cout << " and "; 
    dealersum = dealersum + deal(); // second card for the dealer
    cout << endl;
    cout << "Dealer's sum: " << dealersum << endl; // prints the sum of the two cards
    cout << endl;
    cout << "Would you like to hit or stand?" << endl; // asks the player if they would like another card or would like to pass it to the dealer
    cout << "  "  << "Press '1' to hit." << endl;
    cout << "  " << "Press '2' to stand." << endl;
    cout << "Decision: ";
    cin >> decision; // takes in the player's choice
    cout << endl;
  }
  while (decision != 3 || decision != 4) // while the player does not want to start a new game or quit
  {
    if (decision == 1) // if the player wants to hit
    {
      cout << "New card: ";
      playersum = playersum + deal(); // deals out a new card and adds it to the sum of the other two cards
      cout << endl;
      cout << "Your new sum: " << playersum << endl; // prints out new sum
      if (playersum > 21) // if the new sum exceeds 21
      {
        cout << "You lose!" << endl << endl; // player loses
        dealerwins++; // dealer wins
        cout << "Dealer Wins: " << dealerwins << endl; // prints total wins
        cout << "Your Wins: " << playerwins << endl;
        cout << "Would you like to play again?" << endl;
        cout << "  " << "Press '3' to continue." << endl; // continues new game
        cout << "  " << "Press '4' to quit." << endl; // quits the program
        cout << "Decision: ";
        cin >> decision;
        cout << endl;
        if (decision == 3) { goto LOOP; } // exits the while loop to start a new game
        else // quits the program
        {
          cout << "Thanks for playing!" << endl;
          break; 
        }         
      }
      if (playersum == 21) // if sum is equal to 21
      {
        cout << "You win!" << endl << endl; // player wins
        playerwins++; // adds a win for the player
        cout << "Dealer Wins: " << dealerwins << endl; // prints total wins
        cout << "Your Wins: " << playerwins << endl; 
        cout << "Would you like to play again?" << endl;
        cout << "  " << "Press '3' to continue." << endl; // continues a new game
        cout << "  " << "Press '4' to quit." << endl; // exits the program
        cout << "Decision: ";
        cin >> decision;
        cout << endl;
        if (decision == 3) { goto LOOP; } // exits the while loop to start a new game
        else 
        { 
          cout << "Thanks for playing!" << endl; // exits the program
          break; 
        }       
      }
    }    
    if (decision == 2) // if the player wants to stand
    {
      while (dealersum <= 17) // dealer pulls cards until sum is >= 17
      {
        cout << "Dealer's new card: ";
        dealersum = dealersum + deal(); // shows new card and adds its value to the total
        cout << endl;
        cout << "Dealer's new sum: " << dealersum << endl;
      }
      if (dealersum > playersum) // if the dealer's sum is greater than the player's
      {
        cout << "Dealer wins!" << endl << endl; // dealer wins
        dealerwins++; // adds a win to the total
        cout << "Dealer Wins: " << dealerwins << endl; // prints a running total
        cout << "Your Wins: " << playerwins << endl;
        cout << "Would you like to play again?" << endl;
        cout << "  " << "Press '3' to continue." << endl; // continues a new game
        cout << "  " << "Press '4' to quit." << endl; // quits the game
        cout << "Decision: ";
        cin >> decision;
        cout << endl;
        if (decision == 3) { goto LOOP; } // exits the while loop to start a new game
        else // exits the program
        { 
          cout << "Thanks for playing!" << endl;
          break; 
        }         
      }
      if (dealersum < playersum) // if the dealer's sum is less than the player's sum
      {
        cout << "You win!" << endl << endl; // player wins
        playerwins++; // adds a win to the total
        cout << "Dealer Wins: " << dealerwins << endl; // prints a running total of wins
        cout << "Your Wins: " << playerwins << endl;
        cout << "Would you like to play again?" << endl;
        cout << "  " << "Press '3' to continue." << endl; // continues a new game
        cout << "  " << "Press '4' to quit." << endl; // quits the game
        cout << "Decision: ";
        cin >> decision;
        cout << endl;
        if (decision == 3) { goto LOOP; } // exits the while loop to start a new game
        else  // exits the program
        { 
          cout << "Thanks for playing!" << endl;
          break; 
        }         
      }
      if (dealersum == playersum) // if the player's sum and the dealer's sum are equal
      {
        cout << "It's a tie!" << endl << endl; // tie
        cout << "Dealer Wins: " << dealerwins << endl; // prints a running total
        cout << "Your Wins: " << playerwins << endl;
        cout << endl;
        cout << "Would you like to play again?" << endl;
        cout << "  " << "Press '3' to continue." << endl; // continues a new game
        cout << "  " << "Press '4' to quit." << endl; // quits the program
        cout << "Decision: ";
        cin >> decision;
        cout << endl;
        if (decision == 3) { goto LOOP; } // exits the while loop to start a new game
        else // exits the program
        { 
          cout << "Thanks for playing!" << endl;
          break; 
        }     
      }  
    }
    cout << "Would you like to hit or stand?" << endl; // asks the player for a new decision at the end of each action
    cout << "  "  << "Press '1' to hit." << endl;
    cout << "  " << "Press '2' to stand." << endl;
    cout << "Decision: ";
    cin >> decision;
    cout << endl;
  }
} 
  

