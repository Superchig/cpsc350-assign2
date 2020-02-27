#include "Grid.h"
#include <iostream>

using namespace std;

Grid::Grid() : Grid(25, 25, CLASSIC)
{
}

Grid::Grid(int height, int width) : Grid(height, width, CLASSIC)
{
}

Grid::Grid(int height, int width, WrappingMode m)
{
  maxHeight = height;
  maxWidth = width;
  mode = m;

  grid = new char *[maxHeight];
  for (int i = 0; i < maxHeight; ++i) {
    grid[i] = new char[maxWidth];

    // Initialize each cell in the grid to be empty by default
    for (int j = 0; j < maxWidth; ++j) {
      grid[i][j] = '-';
    }
  }
}

Grid::~Grid()
{
  // Delete each of the rows
  for (int i = 0; i < maxHeight; ++i) {
    delete[] grid[i];
  }

  // Now delete the pointer to the 2D array
  delete[] grid;
}

char Grid::cellAt(int height, int width)
{
  // Check height and width bounds
  if (!inBounds(height, width)) {
    cerr << "Error: Trying to access out-of-bounds cell at " << '(' << height
         << ", " << width << ')' << endl;
    return '\0';
  }

  return grid[height][width];
}

void Grid::setCell(int height, int width, char value)
{
  // Check height and width bounds
  if (!inBounds(height, width)) {
    cerr << "Error: Trying to change out-of-bounds cell at " << '(' << height
         << ", " << width << ')' << endl;
    return;
  }

  grid[height][width] = value;
}

bool Grid::inBounds(int height, int width)
{
  return height >= 0 && height < maxHeight && width >=0 && width <= maxWidth;
}

// FIXME: Finish implementation
void Grid::advanceState()
{
  Grid futureState{maxHeight, maxWidth};
}

int Grid::countNeighbors(int height, int width)
{
  switch (mode) {
    case CLASSIC:
      return countNeighborsClassic(height, width);
      break;
    default:
      return 0;
  }
}

// FIXME: Implement
int Grid::countNeighborsClassic(int height, int width)
{
  int count = 0;
  
  // Check up
  if (inBounds(height - 1, width) && cellAt(height - 1, width) == 'X') {
    ++count;
  }
  // Check up-right
  if (inBounds(height - 1, width + 1) && cellAt(height - 1, width + 1) == 'X') {
    ++count;
  }
  // Check right
  if (inBounds(height, width + 1) && cellAt(height, width + 1) == 'X') {
    ++count;
  }
  // Check down-right
  if (inBounds(height + 1, width + 1) && cellAt(height + 1, width + 1) == 'X') {
    ++count;
  }
  // Check down
  if (inBounds(height + 1, width) && cellAt(height + 1, width) == 'X') {
    ++count;
  }
  // Check down-left
  if (inBounds(height + 1, width - 1) && cellAt(height + 1, width - 1) == 'X') {
    ++count;
  }
  // Check left
  if (inBounds(height, width - 1) && cellAt(height, width - 1) == 'X') {
    ++count;
  }
  // Check up-left
  if (inBounds(height - 1, width - 1) && cellAt(height - 1, width - 1) == 'X') {
    ++count;
  }

  return count;
}

void Grid::printState()
{
  for (int i = 0; i < maxHeight; ++i) {
    for (int j = 0; j < maxWidth; ++j) {
      cout << grid[i][j];
    }
    cout << endl;
  }
}