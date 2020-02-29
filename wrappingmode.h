#include <iostream>

using namespace std;

// Represents which mode should be used to calculate neighbors for cells on grid
// boundaries.
enum WrappingMode {
  // Start the enum values with 1 rather than the default of 0 to more
  // intuitively correspond to having a first choice, second choice, and third
  // choice
  CLASSIC = 1,
  DOUGHNUT = 2,
  MIRROR = 3
};