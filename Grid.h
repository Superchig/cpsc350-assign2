#include "wrappingmode.h"
#include <iostream>

using namespace std;

class Grid {
public:
  Grid();                      // Default constructor
  Grid(int height, int width); // Overloaded constructor
  Grid(int height, int width, WrappingMode m);
  ~Grid(); // Destructor

  char getCell(int height, int width);
  void setCell(int height, int width, char value);

  // Advance the state of the grid by a generation
  void advanceState();
  void printState();

  // A generic countNeighbors function that will use one of the three modes
  // depending on the grid's mode.
  int countNeighbors(int height, int width);

  // Read in a world from a specified file. Returns nullptr if an error occurs
  // while reading.
  static Grid *readFrom(string filePath);

  // Modifier for wrapping mode.
  void setMode(WrappingMode m);

private:
  char **grid;
  int maxHeight;
  int maxWidth;
  WrappingMode mode; // The wrapping mode - classic, doughnut, or mirror

  // These functions count the number of neighbors surrounding a cell, either in
  // classic, doughnut, or mirror mode.
  int countNeighborsClassic(int height, int width);
  int countNeighborsDoughnut(int height, int width);
  int countNeighborsMirror(int height, int width);

  bool inBounds(int height, int width);
};