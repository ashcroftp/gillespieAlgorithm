// main.cpp

// #include <cmath>
// #include <cstdlib>
// #include <ctime>
#include <iostream>
// #include <fstream>
#include <vector>
//#include <random>

//#include "ssa.h"
//#include "model.h"
#include "rng.h"

using namespace std;


int main(int argc, char* argv[])
{
  //  SSA ssa;

  //unsigned kk = 3;
  //ssa.compute(kk);


  RNG rng;
  cout << rng.get_seed() << "\n" << endl;

  cout << rng.rand_uni() << endl;
  cout << rng.rand_uni() << endl;
  cout << rng.rand_uni() << endl;

  int seed = rng.get_seed();

  RNG rng2(seed);
  cout << rng2.get_seed() << "\n" << endl;

  cout << rng2.rand_uni() << endl;
  cout << rng2.rand_uni() << endl;
  cout << rng2.rand_uni() << endl;

  cout << "\n" << rng2.rand_exp(10) << endl;
  
  //random_device rd;
  //cout << rd() << endl;
  return 0;
}
