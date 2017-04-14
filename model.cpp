//model.cpp
//=========================================
#include "model.h"

using namespace std;

//=========================================
// Functions to be modified for each model
//=========================================

// Assign the model parameters to a single vector
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

// Initial condition for each species
void Model::set_initial_condition()
{
  // Define
  vector<unsigned> x = {50, 50};
  
  // Assign
  Initial_condition = x;
}

// Stoichiometry of each reaction
// Each row of the matrix corresponds to a reaction, and each column is the species.
void Model::set_stoichiometry()
{
  vector<vector<int> > stoich_mat(nreactions);

  stoich_mat[0] = {+1, -1};
  stoich_mat[1] = {-1, +1};

  // Assign
  Stoichiometric_matrix = stoich_mat;
}


// Reaction rates (as a function of x_) for each reaction.
// Reactions should be ordered as in the above stoichiometrix matrix
double Model::reaction_rates(unsigned& reaction_, vector<unsigned>& x_)
{
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

// Test used to determine if we continue simulating (true)
// or stop the simulation (false) due to extinction of one
// species or reaching the time limit
bool Model::continue_sim(vector<unsigned>& x_, double& t)
{
  bool b(true);

  if(x_[0] == 0 || x_[0] == Params[0]) b = false;
  
  return b;
}
