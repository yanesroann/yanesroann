# Program: Makefile
# Author: Roann Yanes
#
movies: main.o disneymovie.o beautybeast.o lilo.o
	g++ -o main main.o disneymovie.o beautybeast.o lilo.o

main.o: main.cpp
	g++ -c main.cpp

disneymovie.o: disneymovie.cpp disneymovie.h
	g++ -c disneymovie.cpp

beautybeast.o: beautybeast.cpp beautybeast.h
	g++ -c beautybeast.cpp

lilo.o: lilo.cpp lilo.h
	g++ -c lilo.cpp

clean:
	rm main *.o
