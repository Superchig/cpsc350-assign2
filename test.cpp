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

  cout << "Tests run successfully!" << endl;
  delete grid;
}

int main(int argc, char **argv)
{
  cout << "Testing mirror..." << endl;
  testMirror();

  cout << endl;

  cout << "Testing doughnut..." << endl;
  testDoughnut();

  return 0;
}