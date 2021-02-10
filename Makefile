#Name: Wafa Salah (wss9fb)
#Date: 10/12/20
#Makefile

CXX = clang++ $(CXXFLAGS)
CXXFLAGS = -Wall -O2
DEBUG = -g
OBJECTS = Hashtable.o wordPuzzle.o timer.o


a.out: $(OBJECTS)
	$(CXX) $(DEBUG) $(OBJECTS) -o a.out
	@echo "Let's solve the word Puzzle :)"

.PHONY: clean
clean:
	-rm -f *.o *~

Hashtable.o: Hashtable.cpp Hashtable.h

timer.o: timer.cpp timer.h

wordPuzzle.o: wordPuzzle.cpp Hashtable.h
