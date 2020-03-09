// This file tests out certain functions.

#include <iostream>
#include <cassert>
#include "Grid.h"

using namespace std;

void testMirror()
{
  Grid *grid = Grid::readFrom("refl.txt");
  grid->setMode(MIRROR);

  cout << endl;
  grid->printState();
  cout << endl;

  int cornerNeighbors = grid->countNeighbors(0, 4);
  cout << "cornerNeighbors: " << cornerNeighbors << endl;
  assert(cornerNeighbors == 3);
  cout << endl;

  int aloneNeighbors = grid->countNeighbors(3, 1);
  cout << "aloneNeighbors: " << aloneNeighbors << endl;
  assert(aloneNeighbors == 0);
  cout << endl;

  cout << "Tests run successfully!" << endl;
  delete grid;
}

void testDoughnut()
{
  Grid *grid = Grid::readFrom("cor.txt");
  grid->setMode(DOUGHNUT);

  cout << endl;
  grid->printState();
  cout << endl;

  int cornerNeighbors = grid->countNeighbors(0, 4);
  cout << "cornerNeighbors: " << cornerNeighbors << endl;
  assert(cornerNeighbors == 8);
  cout << endl;
  delete grid;
}

// Also tests out equals
void testCopyFrom()
{
  Grid *grid = Grid::readFrom("cor.txt");
  Grid *copy = new Grid{grid};
  copy->copyFrom(grid);

  grid->printState();
  cout << endl;
  copy->printState();

  assert(grid->equals(copy));

  delete grid;
  delete copy;
}

int main(int argc, char **argv)
{
  cout << "Testing mirror..." << endl;
  testMirror();

  cout << endl;

  cout << "-----------------------------------" << endl;
  cout << "Testing doughnut..." << endl;
  testDoughnut();

  cout << "-----------------------------------" << endl;
  cout << "Testing copyFrom..." << endl;
  testCopyFrom();

  cout << "Tests run successfully!" << endl;
  return 0;
}