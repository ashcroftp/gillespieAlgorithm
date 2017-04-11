//ssa.h
//=========================================
// Guard
#ifndef __SSA_H_INCLUDED__
#define __SSA_H_INCLUDED__ 
//=========================================
// Dependencies
#include <iostream>
#include <vector>
#include <random>
//=========================================

class SSA
{
 private:
  int bar;

 public:
  // Constructor
 SSA() : bar(4) {};

  // Execute the SSA algorithm, using index for something...
  void compute(unsigned& runIndex);
  
  int foo();
};

#endif 
