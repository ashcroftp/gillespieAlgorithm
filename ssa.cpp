//ssa.cpp
//=========================================
#include "ssa.h"

using namespace std;

// Execute the SSA algorithm, using index for something...
void SSA::compute(unsigned runIndex)
{  
  // Initialise the variables and time
  vector<unsigned> x = MyModel.get_initial_condition(); 
  double t = 0.0;

  // Declare variable used in algoritm
  double rn,tau;
  vector<double> a(MyModel.nreactions+1);
  unsigned mu;
  
  while(MyModel.continue_sim(x,t) )  // Loop over timesteps until fixation
    {	        
      // Calculate propensity functions
      // Here a[nreactions] = \sum_i a[i]
      a = get_reaction_rates(x);

      // Determine which reaction channel has fired
      rn = MyRNG.rand_uni();
      mu = choose_reaction(a, rn);

      // Update population
      x = update_population(mu, x);

      // Update time
      tau = MyRNG.rand_exp(a[MyModel.nreactions]);
      t += tau;
      
    }// End of loop over timesteps

  cout << t << "\t" << x[0] << "\t" << x[1] << endl;
}


// Evaluate propensity functions
vector<double> SSA::get_reaction_rates(vector<unsigned>& x_)
{
  vector<double> rates(MyModel.nreactions + 1);
  
  for(unsigned i = 0; i < MyModel.nreactions; ++i)
    {
      rates[i] = MyModel.reaction_rates(i, x_);
    }
  
  // Sum all propensities to return a[nreactions]
  rates[MyModel.nreactions] = 0.0;
  for(unsigned i = 0; i < MyModel.nreactions; ++i)
    {
      rates[MyModel.nreactions] += rates[i];
    }
  
  return(rates);
}

// Determine which reaction has fired
unsigned SSA::choose_reaction(vector<double>& rates_, double& rn_)
{
  unsigned mu;
  double sum = 0.0;  
  for(unsigned m = 0; m < MyModel.nreactions; ++m)
    {
      sum += rates_[m];
      if(sum > rates_[MyModel.nreactions] * rn_)
	{
	  mu = m;
	  break;
	}
    }
  
  return(mu);
}

// Update population based on reaction mu
vector<unsigned> SSA::update_population(unsigned& reaction_, vector<unsigned>& x_)
{
  vector<unsigned> x_new(MyModel.nspecies);
  
  vector<int> delta_x = MyModel.get_stoichiometric_vector(reaction_);

  for(unsigned i = 0; i < MyModel.nspecies; ++i)
    {
      x_new[i] = x_[i] + delta_x[i];
    }

  return(x_new);
}
