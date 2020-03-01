CPPFLAGS=-Wall -g
CXX=g++

all: assignment2

assignment2: Grid.o main.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

run: assignment2
	./assignment2

clean:
	rm *.o assignment2

test: Grid.o test.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@
	./test
