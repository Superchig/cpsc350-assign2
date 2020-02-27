#include <iostream>

using namespace std;

class Grid {
public:
  Grid(); // Default constructor
  Grid(int height, int width); // Overloaded constructor
  ~Grid(); // Destructor

  char cellAt(int height, int width);
  void setCell(int height, int width, char value);

  // Advance the state of the grid by a generation
  void advanceState();
  void printState();

private:
  char **grid;
  int maxHeight;
  int maxWidth;

  int countNeighbors(int height, int width);
};