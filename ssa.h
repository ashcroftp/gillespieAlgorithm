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
//=========================================

class SSA
{
 private:
  RNG MyRNG;
  Model MyModel;
  unsigned nspecies,nreactions;
  
 public:
  // Constructor (empty -- No RNG seed, so use default)
 SSA() : MyRNG(), MyModel() {nspecies=MyModel.get_nspecies(); nreactions=MyModel.get_nreactions();};
  // Constructor with specific seed
 SSA(int seed_) : MyRNG(seed_), MyModel() {nspecies=MyModel.get_nspecies(); nreactions=MyModel.get_nreactions();};
  // Constructor with specific model
 SSA(Model& model_) : MyRNG() {MyModel=model_; nspecies=MyModel.get_nspecies(); nreactions=MyModel.get_nreactions();};
  // Constructor with specific seed and model
 SSA(int seed_, Model& model_) : MyRNG(seed_) {MyModel=model_; nspecies=MyModel.get_nspecies(); nreactions=MyModel.get_nreactions();};

  //=========================================
  // Definitions of access functions
  //=========================================
  RNG get_rng(){return MyRNG;};
  Model get_model(){return MyModel;};


  //=========================================
  // Definitions of algorithm functions
  //=========================================
  void compute(unsigned runIndex_);
  std::vector<double> get_reaction_rates(std::vector<unsigned>& x_);
  unsigned choose_reaction(std::vector<double>& rates_, double& rn_); 
  std::vector<unsigned> update_population(unsigned& reaction_, std::vector<unsigned>& x_);
  
};

#endif 
