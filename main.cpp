// main.cpp
//=========================================
// Dependencies
#include "model.h"
#include "rng.h"
#include "output.h"
#include "ssa.h"


#include <iostream>
//=========================================
using namespace std;

//=========================================
// Model functions to be modified
//=========================================
void Model::set_parameters()
{
  // Define numbers of parameters, species and reactions
  nparams = 1;
  nspecies = 2;
  nreactions = 2;

  // Assign temp vector and fill in parameters
  vector<double> params(nparams);
  params[0] = 100; // N
  
  // Assign
  Params = params;
}


void Model::set_initial_condition()
{
  // Define the initial number of individuals of each species
  vector<unsigned> x = {50, 50};
  
  // Assign
  Initial_condition = x;
}


void Model::set_stoichiometry()
{
  // Stoichiometry of each reaction
  // Each row of the matrix corresponds to a reaction, and each column is the species.
  vector<vector<int> > stoich_mat(nreactions);

  stoich_mat[0] = {+1, -1};
  stoich_mat[1] = {-1, +1};

  // Assign
  Stoichiometric_matrix = stoich_mat;
}


double Model::reaction_rates(unsigned& reaction_, vector<unsigned>& x_)
{
  // Reaction rates (as a function of x_) for each reaction.
  // Should be ordered as in the above stoichiometrix matrix
  switch(reaction_)
    {
    case 0 :
      return (double)x_[0] * (double)x_[1] / Params[0];
      break;

    case 1 :
      return (double)x_[0] * (double)x_[1] / Params[0];
      break;

    default :
      return 0.0;
    }
}


bool Model::continue_sim(vector<unsigned>& x_, double& t)
{
  // Test used to determine if we continue simulating (true)
  // or stop the simulation (false) due to extinction of one
  // species or reaching the time limit
  bool b(true);

  if(x_[0] == 0 || x_[0] == Params[0]) b = false;
  
  return b;
}
// End of model function definitions
//=========================================
//=========================================


// Main function containing the workflow
int main(int argc, char* argv[])
{
  unsigned nruns(1);
  if(argc > 1) nruns = atoi(argv[1]);

  
  // Special model or default?
  Model model;

  // Special random number generator or default?
  RNG rng;
 
  // Special output or default?
  // bool output_final_state(true);
  // bool output_timeseries(false);
  // Output output(output_final_state, output_timeseries);
  Output output;
  
  SSA ssa(model,rng,output,nruns);
  ssa.run();
  
  return 0;
}
