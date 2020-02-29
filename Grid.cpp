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

  // Now delete the overall 2D array
  delete[] grid;
}

char Grid::getCell(int height, int width)
{
  // Check height and width bounds
  if (!inBounds(height, width)) {
    cerr << "Error: Trying to access out-of-bounds cell at " << '(' << height
         << ", " << width << ')' << endl;
    return '\0';
  }

  // cout << "Reading from " << height << " and " << width << endl;
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
  return height >= 0 && height < maxHeight && width >= 0 && width < maxWidth;
}

void Grid::advanceState()
{
  Grid futureState{maxHeight, maxWidth};

  for (int i = 0; i < maxHeight; ++i) {
    for (int j = 0; j < maxWidth; ++j) {
      int neighbors = countNeighbors(i, j);

      if (neighbors <= 1) {
        futureState.setCell(i, j, '-');
      }
      else if (neighbors == 2) {
        futureState.setCell(i, j, getCell(i, j));
      }
      else if (neighbors == 3) {
        futureState.setCell(i, j, 'X');
      }
      else if (neighbors >= 4) {
        futureState.setCell(i, j, '-');
      }
    }
  }

  // Swap the pointers between the future state and the current state
  char **tmp = grid;
  grid = futureState.grid;
  futureState.grid = tmp;
}

// FIXME: Finish implementation
int Grid::countNeighbors(int height, int width)
{
  // cout << "Counting at " << height << " and " << width << endl;
  switch (mode) {
  case CLASSIC:
    return countNeighborsClassic(height, width);
    break;
  default:
    return 0;
  }
}

int Grid::countNeighborsClassic(int height, int width)
{
  int count = 0;

  // Check every cell that is one width and/or height away
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      // Ignore the cell that is 0 width and 0 height away because that is just
      // the original cell. Also, check if all possible neighbor cells are
      // in bounds, in order to avoid trying to access non-existent cells
      if (!(i == 0 && j == 0) && inBounds(height + i, width + j) &&
          getCell(height + i, width + j) == 'X') {
        ++count;
      }
    }
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