CPPFLAGS=-Wall
CXX=g++

all: assignment2.exe

assignment2.exe: Grid.o main.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

run: assignment2.exe
	./assignment2.exe

clean:
	rm *.o assignment2.exe

test: Grid.o test.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@
	./test
