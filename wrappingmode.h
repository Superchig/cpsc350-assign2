#include <iostream>

using namespace std;

// Represents which mode should be used to calculate neighbors for cells on grid
// boundaries.
enum WrappingMode {
  // Explicitly specify which int values correspond to which enum, even though
  // it's not necessary
  CLASSIC = 0,
  DOUGHNUT = 1,
  MIRROR = 2
};