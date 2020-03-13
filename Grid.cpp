#include "Grid.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <thread>

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

Grid::Grid(Grid *other) : Grid(other->maxHeight, other->maxWidth, other->mode)
{
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

int Grid::getHeight()
{
  return maxHeight;
}

int Grid::getWidth()
{
  return maxWidth;
}

WrappingMode Grid::getMode()
{
  return mode;
}

bool Grid::inBounds(int height, int width)
{
  return height >= 0 && height < maxHeight && width >= 0 && width < maxWidth;
}

void Grid::advanceState()
{
  Grid futureState{maxHeight, maxWidth, mode};

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

int Grid::countNeighbors(int height, int width)
{
  // cout << "Counting at " << height << " and " << width << endl;
  switch (mode) {
  case CLASSIC:
    return countNeighborsClassic(height, width);
    break;
  case DOUGHNUT:
    return countNeighborsDoughnut(height, width);
    break;
  case MIRROR:
    return countNeighborsMirror(height, width);
    break;
  default:
    return -1;
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

int Grid::countNeighborsDoughnut(int height, int width)
{
  int count = 0;

  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (i == 0 && j == 0) {
        continue;
      }

      int neighborHeight = height + i;
      int neighborWidth = width + j;

      // If the neighbor would overstep the left or right bound, put them on the
      // opposite side
      if (neighborHeight == -1) {
        neighborHeight = maxHeight - 1;
      }
      else if (neighborHeight == maxHeight) {
        neighborHeight = 0;
      }

      // If the neighbor would overstep the top or bottom bound, put them on the
      // opposite side
      if (neighborWidth == -1) {
        neighborWidth = maxWidth - 1;
      }
      else if (neighborWidth == maxWidth) {
        neighborWidth = 0;
      }

      if (getCell(neighborHeight, neighborWidth) == 'X') {
        ++count;
      }
    }
  }

  return count;
}

int Grid::countNeighborsMirror(int height, int width)
{
  int count = 0;

  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (i == 0 && j == 0) {
        continue;
      }

      int neighborHeight = height + i;
      int neighborWidth = width + j;

      // If the area above and below the bounds would be checked, use the
      // "mirror" cell to the bottom or top
      if (neighborHeight == -1 || neighborHeight == maxHeight) {
        neighborHeight = height;
      }

      // If the area to the left or right of the grid would be checked, use the
      // "mirror" cell to the right or left
      if (neighborWidth == -1 || neighborWidth == maxWidth) {
        neighborWidth = width;
      }

      if (getCell(neighborHeight, neighborWidth) == 'X') {
        ++count;
      }
    }
  }

  return count;
}

void Grid::printState()
{
  writeState(cout);
}

void Grid::writeState(ostream &output)
{
  for (int i = 0; i < maxHeight; ++i) {
    for (int j = 0; j < maxWidth; ++j) {
      output << grid[i][j];
    }
    output << endl;
  }
}

void Grid::setMode(WrappingMode m)
{
  mode = m;
}

Grid *Grid::readFrom(string filePath)
{
  ifstream worldFile{filePath};

  if (!worldFile.is_open()) {
    cerr << "Error: Could not open world file at " << filePath << endl;
    return nullptr;
  }

  // Obtain the height and width from the first two lines
  string heightLine;
  getline(worldFile, heightLine);
  string widthLine;
  getline(worldFile, widthLine);
  int height = stoi(heightLine);
  int width = stoi(widthLine);

  // Read in the grid from the remaining lines
  Grid *result = new Grid(height, width);
  string line;
  int row = 0;
  while (getline(worldFile, line)) {
    for (size_t col = 0; col < line.size(); ++col) {
      const char ch = line.at(col);

      switch (ch) {
      case '-':
        result->setCell(row, col, '-');
        break;
      case 'X':
        result->setCell(row, col, 'X');
        break;
      default:
        // Use row + 1 to represent line number because the rows in the grid
        // start at 0 but the lines in a file start at 1
        cerr << "Error: world file " << filePath << " has invalid character "
             << ch << " at line " << (row + 1) << endl;
        return nullptr;
      }
    }

    ++row;
  }

  worldFile.close();
  return result;
}

Grid *Grid::generateRandom(int height, int width, double density)
{
  Grid *result = new Grid(height, width);
  // Add 0.5 to round the number of living cells up or down, based on whether
  // the decimal part of the floating point number is above or below 0.5
  int livingCells = (height * width) * density + 0.5;

  for (int i = 0; i < livingCells; ++i) {
    int y = rand() % height;
    int x = rand() % width;

    while (result->getCell(y, x) == 'X') {
      y = rand() % height;
      x = rand() % width;
    }

    result->setCell(y, x, 'X');
  }

  return result;
}

void Grid::copyFrom(Grid *other)
{
  // Check that the dimensions are the same
  if (maxHeight != other->maxHeight || maxWidth != other->maxWidth) {
    cerr << "Error: Trying to copy from grid with different dimensions!\n"
         << "\tHeights " << maxHeight << " vs. " << other->maxHeight << '\n'
         << "\tWidths " << maxWidth << " vs. " << other->maxWidth << '\n';
    return;
  }

  for (int i = 0; i < maxHeight; ++i) {
    for (int j = 0; j < maxWidth; ++j) {
      setCell(i, j, other->getCell(i, j));
    }
  }
}

bool Grid::equals(Grid *other)
{
  if (maxHeight != other->maxHeight || maxWidth != other->maxWidth) {
    return false;
  }

  for (int i = 0; i < maxHeight; ++i) {
    for (int j = 0; j < maxWidth; ++j) {
      if (getCell(i, j) != other->getCell(i, j)) {
        return false;
      }
    }
  }

  return true;
}

void Grid::printAndRunGame()
{
  Grid *old = new Grid(this);
  Grid *older = new Grid(this);

  int stabilizeCount = 0;
  string input;
  while (true) {
    older->copyFrom(old);
    old->copyFrom(this);

    printState();
    advanceState();

    // Since empty worlds are "stable" (they don't change), this also catches
    // empty worlds.
    if (equals(old) || equals(older)) {
      ++stabilizeCount;
    }
    else {
      stabilizeCount = 0;
    }

    if (stabilizeCount >= 10) {
      cout << endl;
      printState();
      cout << "The world has stabilized." << endl;
      cout << "Exiting..." << endl;
      break;
    }

    // Require the user to press enter.
    getline(cin, input);
  }

  delete old;
  delete older;
}

void Grid::writeAndRunGame(string filename)
{
  ofstream output{filename};

  Grid *old = new Grid(this);
  Grid *older = new Grid(this);

  int stabilizeCount = 0;
  string input;
  while (true) {
    older->copyFrom(old);
    old->copyFrom(this);

    writeState(output);
    output << endl;
    advanceState();

    // Since empty worlds are "stable" (they don't change), this also catches
    // empty worlds.
    if (equals(old) || equals(older)) {
      ++stabilizeCount;
    }
    else {
      stabilizeCount = 0;
    }

    if (stabilizeCount >= 10) {
      output << endl;
      writeState(output);
      output << "The world has stabilized." << endl;
      cout << "Exiting..." << endl;
      break;
    }
  }

  output.close();
  delete old;
  delete older;
}

void Grid::printAndRunGameWithPause()
{
  Grid *old = new Grid(this);
  Grid *older = new Grid(this);

  int stabilizeCount = 0;
  string input;
  while (true) {
    older->copyFrom(old);
    old->copyFrom(this);

    printState();
    cout << endl;
    advanceState();

    // Since empty worlds are "stable" (they don't change), this also catches
    // empty worlds.
    if (equals(old) || equals(older)) {
      ++stabilizeCount;
    }
    else {
      stabilizeCount = 0;
    }

    if (stabilizeCount >= 10) {
      cout << endl;
      printState();
      cout << "The world has stabilized." << endl;
      cout << "Exiting..." << endl;
      break;
    }

    // Pause between iterations
    this_thread::sleep_for(chrono::milliseconds(500));
  }

  delete old;
  delete older;
}