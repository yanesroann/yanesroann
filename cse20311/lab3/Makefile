polar: polarmain.o polarfn.o
	g++ polarmain.o polarfn.o -lm -o polar

polarmain.o: polarmain.cpp polarfn.h
	g++ -c polarmain.cpp -o polarmain.o

polarfn.o: polarfn.cpp
	g++ -c polarfn.cpp -o polarfn.o

clean:
	rm *.o polar 


