CPPFLAGS=-Wall
CXX=g++

all: assignment2

assignment2: Grid.o main.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

clean:
	rm *.o assignment2
