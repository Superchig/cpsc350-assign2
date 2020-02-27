#include <iostream>

using namespace std;

// Represents which mode should be used to calculate neighbors for cells on grid
// boundaries.
enum WrappingMode {
  CLASSIC, DOUGHNUT, MIRROR
};