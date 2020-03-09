#include "Grid.h"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  //// Allow the user to choose how to read in/create the world.

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
    int height;
    cout << "Input desired height of grid: ";
    cin >> height;

    int width;
    cout << "Input desired width of grid: ";
    cin >> width;

    double density;
    cout << "Input population density (decimal value between 0 and 1): ";
    cin >> density;

    srand(time(nullptr));
    grid = Grid::generateRandom(height, width, density);

    // Clear out the input buffer so that future input will work
    getline(cin, choice);
  }
  else {
    cout << "That was an invalid choice." << endl;
    return 1;
  }

  //// Allow the user to choose which boundary mode to use.

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
    grid->setMode((WrappingMode)enumValue);
  }
  else {
    cout << "That is not a valid choice." << endl;

    // Make sure to deallocate memory for the grid
    delete grid;
    return 3;
  }

  //// Ask the user how they want to see the simulation's output.

  cout << endl;
  cout << "How do you want to see the simulation's output?" << endl;
  cout << "1. See a brief pause between generations." << endl;
  cout << "2. Press the enter key in between each generation." << endl;
  cout << "3. Write the output to a file." << endl;

  cout << "Make a choice (1, 2, or 3): ";
  getline(cin, choice);

  if (choice == "1") {
    // FIXME: Implement pausing between generations.
    cout << "That's a valid choice. But pausing between generations has not "
            "been implemented yet, sorry."
         << endl;

    delete grid;
    return 0;
  }
  else if (choice == "2") {
    // FIXME: Add some sort of distinction between pausing and pressing enter?
  }
  else if (choice == "3") {
    // FIXME: Implement writing output to a file.
    cout << "That's a valid choice. But writing output to a file has not been "
            "implemented yet, sorry."
         << endl;
    
    delete grid;
    return 0;
  }
  else {
    cout << "That's an invalid choice." << endl;
  }

  Grid *old = new Grid(grid);
  Grid *older = new Grid(grid);

  // FIXME: May want to remove the ability to quit by typing quit in the future
  while (choice != "quit") {
    older->copyFrom(old);
    old->copyFrom(grid);

    grid->printState();
    grid->advanceState();

    // Since empty worlds are "stable" (they don't change), this also catches
    // empty worlds.
    if (grid->equals(old) || grid->equals(older)) {
      cout << endl;
      grid->printState();
      cout << "The world has stabilized." << endl;
      cout << "Exiting..." << endl;
      break;
    }

    // Require the user to press enter.
    getline(cin, choice);
  }

  delete old;
  delete older;
  delete grid;
  return 0;
}