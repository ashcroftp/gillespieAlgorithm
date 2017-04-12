//ssa.h
//=========================================
// Guard
#ifndef __SSA_H_INCLUDED__
#define __SSA_H_INCLUDED__ 
//=========================================
// Dependencies
#include <iostream>  // remove?
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

  int foo();
  
  // Execute the SSA algorithm, using index for something...
  void compute(unsigned& runIndex);

  // Evaluate propensity functions
  std::vector<double> get_propensities(std::vector<unsigned>& x);

  // Determine which reaction has fired
  unsigned get_reaction(std::vector<double>& a, double& r);
  
  std::vector<unsigned> update_population(unsigned& reaction_, std::vector<unsigned>& x_);
  
};

#endif 
