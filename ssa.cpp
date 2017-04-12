//ssa.cpp
//=========================================
#include "ssa.h"

using namespace std;

int SSA::foo()
{  
  return(bar);
}

// Execute the SSA algorithm, using index for something...
void SSA::compute(unsigned& runIndex)
{

  // Initialise the variables
  // vector<unsigned> x = get_initial_condition()
  vector<unsigned> x  = { 50, 50 };

  unsigned N = x[0] + x[1];
  
  double t = 0.0;

  mt19937 mt_rand( time(NULL) ); // Initialise RNG using seed
  uniform_real_distribution<double> dist(1.0e-9,1.0); // We want RNs in (0,1]

  vector<double> r(2); // Variables to store random numbers, time step and fired reaction
  vector<double> a(2+1);
  double tau,sum;
  unsigned mu;

  while(x[0] > 0 && x[0] < N)  // Loop over timesteps until fixation
    {
      // Generate 2 uniform random numbers in (0,1]
      r[0] = dist(mt_rand);
      r[1] = dist(mt_rand);
	        
      // Calculate propensity functions
      // Here a[0] = \sum_{i=1}^m a[m]
      a = get_propensities(x);
      
      // Calculate time step
      tau = (1.0 / a[0]) * log(1.0 / r[0]);

      // Determine which reaction channel has fired
      mu = get_reaction(a, r[1]);

      // Update population
      x = update_population(mu, x);

      // Update time
      t += tau;
      
    }// End of loop over timesteps

  cout << t << "\t" << x[0] << "\t" << x[1] << endl;
}


// Evaluate propensity functions
vector<double> SSA::get_propensities(vector<unsigned>& x)
{
  unsigned N = x[0] + x[1];
  
  vector<double> a(2+1);
  a[1] = (double)x[0] * (double)x[1] / (double)N;
  a[2] = (double)x[0] * (double)x[1] / (double)N;

  a[0] = 0.0;
  for(unsigned i=1; i<=2; ++i) a[0] += a[i];
  
  return(a);
}

// Determine which reaction has fired
unsigned SSA::get_reaction(vector<double>& a, double& r)
{
  unsigned mu;
  double sum = 0.0;  
  for(unsigned m=1; m <= 2; ++m)
    {
      sum += a[m];
      if(sum > a[0] * r){mu=m;break;}
    }
  
  return(mu);
}

// Update population based on reaction mu
vector<unsigned> SSA::update_population(unsigned& reaction_, vector<unsigned>& x_)
{
  unsigned n = x_.size();
  vector<unsigned> x_new(n);
  
  vector<int> delta_x;
  if(reaction_ == 1) delta_x = {+1, -1};
  else delta_x = {-1, +1};

  for(unsigned i = 0; i < n; ++i) {x_new[i] = x_[i] + delta_x[i];}
  
  //if( mu_ == 1 ) {x[0]++; x[1]--;}
  //else {x[0]--; x[1]++;}

  return(x_new);
}
