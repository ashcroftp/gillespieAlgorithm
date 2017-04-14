// main.cpp

#include <iostream>

#include "ssa.h"

using namespace std;


int main(int argc, char* argv[])
{
  SSA ssa;
  ssa.compute(0);
  
  return 0;
}
