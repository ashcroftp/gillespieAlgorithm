// main.cpp

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>

#include "ssa.h"
#include "myProcess.h"

using namespace std;


int main(int argc, char* argv[])
{
  SSA ssa;

  cout << ssa.foo() << endl;

  unsigned kk = 3;

  ssa.compute(kk);
  
  return 0;
}
