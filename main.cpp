#include "Grid.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  Grid grid{10, 10};
  grid.setCell(0, 0, 'X');
  // grid.setCell(-1, 0, 'X'); // Invalid bounds will be checked
  // grid.setCell(10, 0, '-'); // Invalid bounds will be checked

  cout << "Cell at (h = 0, w = 0): " << grid.cellAt(0, 0) << endl;
  cout << "Cell at (h = 3, w = 3): " << grid.cellAt(3, 3) << endl;
  cout << endl;
  grid.printState();

  return 0;
}