# Program: Makefile
# Author: Roann Yanes
# Makefile for the State class

state: statemain.o state.o
	g++ statemain.o state.o -o runstate

statemain.o: statemain.cpp state.h
	g++ -c -std=c++0x statemain.cpp -o statemain.o

state.o: state.cpp state.h
	g++ -c state.cpp -o state.o

clean:
	rm *.o runstate

