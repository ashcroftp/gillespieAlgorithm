//model.cpp
//=========================================
#include "model.h"

using namespace std;

//=========================================
// Functions to be modified for each model
//=========================================

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


// Reaction rates (as a function of x) for each reaction.
// Reactions should be ordered as in the above stoichiometrix matrix
vector<double> Model::reaction_rates(vector<unsigned>& x_)
{  
  vector<double> rates(nreactions + 1);
  // My two reaction rates
  rates[1] = (double)x_[0] * (double)x_[1] / (double)N;
  rates[2] = (double)x_[0] * (double)x_[1] / (double)N;

  // Sum all propensities to return a[0]
  rates[0] = 0.0;
  for(unsigned i = 1; i <= nreactions; ++i) rates[0] += rates[i];

  cout << rates[0] << "\t" << rates[1] << "\t" << rates[2] << endl;
  
  return(rates);
}



//=========================================
// Access functions
//=========================================

// Access each stoichiometric vector
vector<int> Model::get_stoichiometric_vector(unsigned& reaction_)
{
  return(Stoichiometric_matrix[reaction_]);
}

// Access initial condition
vector<unsigned> Model::get_initial_condition()
{
  return(Initial_condition);
}

//=========================================
// Functions related to the algorithm
//=========================================


// Determine which reaction has fired
unsigned Model::choose_reaction(vector<double>& rates_, double& rand_)
{
  unsigned mu;
  double sum = 0.0;
  for(unsigned m = 1; m <= nreactions; ++m)
    {
      sum += rates_[m];
      if(sum > rates_[0] * rand_){mu = m - 1; break;}
    }
  
  return(mu);
}





// Update population based on reaction mu
vector<unsigned> Model::update_population(unsigned& reaction_, vector<unsigned>& x_)
{
  vector<unsigned> x_new(nspecies);
  
  vector<int> delta_x = get_stoichiometric_vector(reaction_);

  for(unsigned i = 0; i < nspecies; ++i) x_new[i] = x_[i] + delta_x[i];

  return(x_new);
}
