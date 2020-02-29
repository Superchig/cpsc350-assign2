#include "Grid.h"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  cout << "1. Use a map file of the world." << endl;
  cout << "2. Randomly generate a new world." << endl;
  cout << "Make a choice (1 or 2): ";

  Grid *grid = nullptr;
  string choice;
  getline(cin, choice);
  if (choice == "1") {
    cout << "Enter path to map file: ";

    string path;
    getline(cin, path);

    grid = Grid::readFrom(path);

    // Check if something went wrong while trying to read in from the world
    // file. No error messages are printed because any error messages should
    // already be printed in the readFrom() function.
    if (grid == nullptr) {
      return 2;
    }
  }
  else if (choice == "2") {
    // FIXME: Implement random world generation
    cout << "That is a valid choice, but random generation has not been "
            "implemented yet. Sorry!"
         << endl;
    return 0;
  }
  else {
    cout << "That was an invalid choice." << endl;
    return 1;
  }

  cout << endl;
  cout << "How do you want to evaluate cells on the boundaries of the grid?"
       << endl;
  cout << "1. Classic mode - All cells off the map's boundaries count as dead."
       << endl;
  cout << "2. Doughnut mode - The grid wraps around itself horizontally and "
          "vertically."
       << endl;
  cout << "3. Mirror mode - References off the grid are bounced back as if the "
          "wall were a mirror."
       << endl;

  cout << "Make a choice (1, 2, or 3): ";
  getline(cin, choice);

  if (choice == "1" || choice == "2" || choice == "3") {
    // Because enums have corresponding integer values, we can just cast one of
    // the inputs to an enum.
    int enumValue = stoi(choice);
    grid->setMode((WrappingMode) enumValue);
  } else {
    cout << "That is not a valid choice." << endl;

    // Make sure to deallocate memory for the grid
    delete grid;
    return 3;
  }

  cout << endl;

  grid->printState();

  cout << endl;
  grid->advanceState();
  grid->printState();

  delete grid;
  return 0;
}