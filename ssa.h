//ssa.h
//=========================================
// Guard
#ifndef __SSA_H_INCLUDED__
#define __SSA_H_INCLUDED__ 
//=========================================
// Dependencies
#include "rng.h"
#include "model.h"

#include <iostream>  // remove?
#include <vector>
#include <random>
//=========================================

class SSA
{
 private:
  RNG MyRNG;
  Model MyModel;
  
 public:
  // Constructor (empty -- No RNG seed, so use default)
 SSA() : MyRNG(), MyModel() {};
  // Constructor with specific seed
 SSA(int seed_) : MyRNG(seed_), MyModel() {};
  // Constructor with specific model
 SSA(Model& model_) : MyRNG() {MyModel=model_;};
  // Constructor with specific seed and model
 SSA(int seed_, Model& model_) : MyRNG(seed_) {MyModel=model_;};
  
  //=========================================
  // Definitions of access functions
  //=========================================
  RNG get_rng(){return(MyRNG);};
  Model get_model(){return(MyModel);};


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
