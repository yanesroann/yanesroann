# Program: Makefile
# Author: Grace Milton and Roann Yanes

CMP = g++ -std=c++0x
CLASS = crossboard
MAIN = crossword
EXEC = playcrossword

$(EXEC): $(CLASS).o $(MAIN).o
	$(CMP) $(CLASS).o $(MAIN).o -o $(EXEC)

$(CLASS).o: $(CLASS).cpp $(CLASS).h
	$(CMP) -c $(CLASS).cpp -o $(CLASS).o

$(MAIN).o: $(MAIN).cpp $(CLASS).h
	$(CMP) -c $(MAIN).cpp -o $(MAIN).o

clean:
	rm *.o
	rm $(EXEC)

