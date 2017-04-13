//ssa.h
//=========================================
// Guard
#ifndef __SSA_H_INCLUDED__
#define __SSA_H_INCLUDED__ 
//=========================================
// Dependencies
#include "rng.h"

#include <iostream>  // remove?
#include <vector>
#include <random>
//=========================================

class SSA
{
 private:
  RNG RanNumGen;
  
 public:
  // Constructor (empty -- No RNG seed, so use default)
 SSA() : RanNumGen() {};
  // Constructor with specific seed
 SSA(int seed_) : RanNumGen(seed_) {};

  //=========================================
  // Definitions of access functions
  //=========================================
  RNG get_rng(){return(RanNumGen);};


  //=========================================
  // Definitions of algorithm functions
  //=========================================
  // Execute the SSA algorithm, using index for something...
  void compute(unsigned runIndex);

  // Evaluate propensity functions
  std::vector<double> get_propensities(std::vector<unsigned>& x);

  // Determine which reaction has fired
  unsigned get_reaction(std::vector<double>& a, double& r);
  
  std::vector<unsigned> update_population(unsigned& reaction_, std::vector<unsigned>& x_);
  
};

#endif 
