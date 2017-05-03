//ssa.h
//=========================================
// Guard
#ifndef __SSA_H_INCLUDED__
#define __SSA_H_INCLUDED__ 
//=========================================
// Dependencies
#include "model.h"
#include "rng.h"
#include "output.h"

#include <iostream>  // remove?
#include <vector>
//=========================================

class SSA
{
 private:
  Model MyModel;
  RNG MyRNG;
  Output MyOutput;

  unsigned nruns;
  
  unsigned nspecies,nreactions;
  bool Output_final_state,Output_timeseries;
  
 public:
  // Constructor (empty -- use default members)
 SSA() : MyModel(), MyRNG(), MyOutput(), nruns(1) {varInit();};
  // Constructor (specified members)
 SSA(Model& model_, RNG& rng_, Output& output_, unsigned& nruns_) : MyModel(model_), MyRNG(rng_), MyOutput(output_), nruns(nruns_) {varInit();};

  // Initialise variables
  void varInit()
  {
    nspecies = MyModel.get_nspecies();
    nreactions = MyModel.get_nreactions();
    Output_final_state = MyOutput.get_output_final_state();
    Output_timeseries = MyOutput.get_output_timeseries();
    MyOutput.set_model_params(MyModel.get_all_parameters());
  };
  
  //=========================================
  // Definitions of access functions
  //=========================================
  RNG get_rng(){return MyRNG;};
  Model get_model(){return MyModel;};
  Output get_output(){return MyOutput;};


  //=========================================
  // Definitions of algorithm functions
  //=========================================
  void run();
  void compute();
  std::vector<double> get_reaction_rates(std::vector<unsigned>& x_);
  unsigned choose_reaction(std::vector<double>& rates_, double& rn_); 
  std::vector<unsigned> update_population(unsigned& reaction_, std::vector<unsigned>& x_);
  
};

#endif 
