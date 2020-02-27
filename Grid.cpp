#include "Grid.h"
#include <iostream>

using namespace std;

Grid::Grid()
{ 
  maxHeight = 25;
  maxWidth = 25;

  grid = new char *[maxHeight];
  for (int i = 0; i < maxHeight; ++i) {
    grid[i] = new char[maxWidth];

    // Initialize each cell in the grid to be empty by default
    for (int j = 0; j < maxWidth; ++j) {
      grid[i][j] = '-';
    }
  }
}

Grid::Grid(int height, int width)
{
  maxHeight = height;
  maxWidth = width;

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
  if (height < 0 || height > maxHeight - 1 || width < 0 ||
      width > maxWidth - 1) {
    cerr << "Error: Trying to access out-of-bounds cell at " << '(' << height
         << ", " << width << ')' << endl;
    return '\0';
  }

  return grid[height][width];
}

void Grid::setCell(int height, int width, char value)
{
  // Check height and width bounds
  if (height < 0 || height > maxHeight - 1 || width < 0 ||
      width > maxWidth - 1) {
    cerr << "Error: Trying to change out-of-bounds cell at " << '(' << height
         << ", " << width << ')' << endl;
    return;
  }

  grid[height][width] = value;
}

// FIXME: Finish implementation
void Grid::advanceState()
{
  Grid futureState{maxHeight, maxWidth};
}

// FIXME: Implement
int Grid::countNeighbors(int height, int width)
{
  return 0;
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