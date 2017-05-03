//ssa.cpp
//=========================================
#include "ssa.h"

using namespace std;

// Loop over number of runs and execute the algorithm
void SSA::run()
{
  // Output parameters to file
  MyOutput.write_parameters();
  
  unsigned i(0);
  while(i < nruns)
    {
      // Execute the algorithm
      compute();
      
      MyOutput.write_results();
      
      ++i;
    }
}

// Execute the SSA algorithm, using index for something...
void SSA::compute()
{  
  // Initialise the variables and time
  double t = 0.0;
  vector<unsigned> x = MyModel.get_initial_condition(); 

  // Store
  if(Output_timeseries) MyOutput.initialise_timeseries(t,x);
  
  // Declare variable used in algoritm
  double rn,tau;
  vector<double> a(nreactions + 1);
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
      tau = MyRNG.rand_exp(a[nreactions]);
      t += tau;

      // Store
      if(Output_timeseries) MyOutput.store_timeseries(t,x);
    }// End of loop over timesteps

  if(Output_final_state) MyOutput.store_final_state(t,x);
}


// Evaluate propensity functions
vector<double> SSA::get_reaction_rates(vector<unsigned>& x_)
{
  vector<double> rates(nreactions + 1);
  
  for(unsigned i = 0; i < nreactions; ++i)
    {
      rates[i] = MyModel.reaction_rates(i, x_);
    }
  
  // Sum all propensities to return a[nreactions]
  rates[nreactions] = 0.0;
  for(unsigned i = 0; i < nreactions; ++i)
    {
      rates[nreactions] += rates[i];
    }
  
  return rates;
}

// Determine which reaction has fired
unsigned SSA::choose_reaction(vector<double>& rates_, double& rn_)
{
  unsigned mu(0);
  double sum = 0.0;  
  for(unsigned m = 0; m < nreactions; ++m)
    {
      sum += rates_[m];
      if(sum > rates_[nreactions] * rn_)
	{
	  mu = m;
	  break;
	}
    }
  
  return mu;
}

// Update population based on reaction mu
vector<unsigned> SSA::update_population(unsigned& reaction_, vector<unsigned>& x_)
{
  vector<unsigned> x_new(nspecies);
  
  vector<int> delta_x = MyModel.get_stoichiometric_vector(reaction_);

  for(unsigned i = 0; i < nspecies; ++i)
    {
      x_new[i] = x_[i] + delta_x[i];
    }

  return x_new;
}
