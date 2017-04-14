// main.cpp

// #include <cmath>
// #include <cstdlib>
// #include <ctime>
#include <iostream>
// #include <fstream>
#include <vector>
//#include <random>

#include "ssa.h"
//#include "model.h"
#include "rng.h"

using namespace std;


int main(int argc, char* argv[])
{
  SSA ssa;
  RNG rng = ssa.get_rng();
  cout << rng.get_seed() << endl;
  
  ssa.compute(0);
  
  return 0;
}
