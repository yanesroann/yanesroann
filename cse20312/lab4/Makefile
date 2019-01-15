# Program: Makefile
# Author: Roann Yanes
#
main: main.o sudoku.o
	g++ -o main main.o sudoku.o

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

sudoku.o: sudoku.cpp sudoku.h
	g++ -c -std=c++11 sudoku.cpp

cell.o: cell.h cell.cpp
	g++ -c -std=c++11 cell.cpp

clean:
	rm main *.o
