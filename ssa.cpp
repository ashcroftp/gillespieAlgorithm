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
  vector<unsigned> x  = { 50, 38 };

  unsigned N = x[0] + x[1];
  
  double t = 0.0;

  mt19937 mt_rand( time(NULL) );                              // Initialise RNG using seed
  uniform_real_distribution<double> dist(1.0e-9,1.0); // We want RNs in (0,1]

  vector<double> r(2);                                // Variables to store random numbers, time step and fired reaction
  vector<double> a(2);
  double tau,sum,a0;
  unsigned mu;

  while(x[0] > 0 && x[0] < N)  // Loop over timesteps until fixation
    {     
      r[0] = dist(mt_rand); r[1] = dist(mt_rand); // Generate 2 uniform random numbers in (0,1]
	        
      a[0] = (double)x[0] * (double)x[1] / (double)N; // Calculate propensity functions and sum
      a[1] = (double)x[0] * (double)x[1] / (double)N;
      a0 = 0.0;
      for(unsigned m=0; m < 2; ++m) a0 += a[m];
       
      tau = (1.0/a0) * log(1.0/r[0]);  // Calculate time step
      t += tau;
	  
      sum = 0.0;  // Determine which reaction channel has fired
      for(unsigned m=0; m < 2; ++m)
	{
	  sum += a[m];
	  if(sum > a0*r[1]){mu=m;break;}
	}

      if( mu == 0 ) {x[0]++; x[1]--;}
      else {x[0]--; x[1]++;}
    }// End of loop over timesteps

  cout << t << "\t" << x[0] << "\t" << x[1] << endl;
}
