# Final Project
# Grace Milton and Roann Yanes

CMP = g++ -std=c++11 -lX11
CLASS = tetrisboard
MAIN = final
EXEC = final

$(EXEC): $(CLASS).o $(MAIN).o
	$(CMP) $(CLASS).o gfxnew.o $(MAIN).o -o $(EXEC)

$(CLASS).o: $(CLASS).cpp $(CLASS).h
	$(CMP) -c $(CLASS).cpp -o $(CLASS).o

$(MAIN).o: $(MAIN).cpp $(CLASS).h
	$(CMP) -c $(MAIN).cpp -o $(MAIN).o

clean:
	rm $(CLASS).o $(MAIN).o
	rm $(EXEC)

