# Program: Makefile
# Author: Roann Yanes
#
blackjack: main.o CardDeck.o BlackJack.o
	g++ -o main main.o CardDeck.o BlackJack.o

main.o: main.cpp
	g++ -c main.cpp

CardDeck.o: CardDeck.cpp CardDeck.h
	g++ -c CardDeck.cpp

BlackJack.o: BlackJack.cpp BlackJack.h
	g++ -c BlackJack.cpp

clean:
	rm main *.o
