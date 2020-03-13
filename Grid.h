#include "wrappingmode.h"
#include <iostream>

using namespace std;

class Grid {
public:
  Grid();                      // Default constructor
  Grid(int height, int width); // Overloaded constructor
  Grid(int height, int width, WrappingMode m);
  // Copy constructor. Only copies over height, width, and wrapping mode. Does
  // NOT copy individual cells in grid.
  Grid(Grid *other);
  ~Grid(); // Destructor

  char getCell(int height, int width);
  void setCell(int height, int width, char value);
  int getHeight();
  int getWidth();
  WrappingMode getMode();

  // Advance the state of the grid by a generation
  void advanceState();
  void printState();
  void writeState(ostream &output);

  // A generic countNeighbors function that will use one of the three modes
  // depending on the grid's mode.
  int countNeighbors(int height, int width);

  // Copy the contents of one grid into this one
  void copyFrom(Grid *other);

  // Read in a world from a specified file. Returns nullptr if an error occurs
  // while reading.
  static Grid *readFrom(string filePath);

  // Generate a random grid of given maximum height and width. The population
  // density should be greater than 0 and less than or equal to 1
  static Grid *generateRandom(int height, int width, double density);

  // Modifier for wrapping mode.
  void setMode(WrappingMode m);

  // Returns true if they both have the same cells at the same positions.
  // Returns false otherwise.
  bool equals(Grid *other);

  // Handle printing out the various states of the game to standard output or a
  // file.
  void printAndRunGame();
  void writeAndRunGame(string filename);

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