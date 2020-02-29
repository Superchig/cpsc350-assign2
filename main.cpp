#include "Grid.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  Grid grid{10, 10};
  grid.setCell(1, 1, 'X');
  grid.setCell(2, 1, 'X');
  grid.setCell(3, 1, 'X');
  // grid.setCell(-1, 0, 'X'); // Invalid bounds will be checked
  // grid.setCell(10, 0, '-'); // Invalid bounds will be checked

  // cout << "Cell at (h = 1, w = 0): " << grid.getCell(1, 0) << endl;
  // cout << "Cell at (h = 3, w = 3): " << grid.getCell(3, 3) << endl;

  cout << endl;
  grid.printState();
  cout << endl;

  cout << "Number of neighboring cells: " << grid.countNeighbors(2, 1) << endl;

  grid.advanceState();
  grid.printState();

  return 0;
}