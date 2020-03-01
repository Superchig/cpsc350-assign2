#include <iostream>
#include <cassert>
#include "Grid.h"

using namespace std;

int main(int argc, char **argv)
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

  cout << "Tests run successfully!" << endl;
  
  delete grid;
  return 0;
}