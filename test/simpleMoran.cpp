//simpleMoran.cpp
// The most simple, linear implementation of the stochastic
// Moran model to set a timing benchmark

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
  unsigned N = 10;
  unsigned nReactions = 2;
  unsigned nRuns = atoi(argv[1]);

  
  vector<double> a(nReactions);  // Propensity value storage for each reaction
  double a0;  // Propensity sum
  double t;  // Time storage
  unsigned n;  // Population state storage
  vector<double> r(2);  // Variables to store random numbers, time step and fired reaction
  double tau,sum;
  unsigned mu;

  srand(time(NULL) );
  
  ofstream output;
  const char filename[99] = "simpleMoran.dat";
  output.open(filename);
  output << "time" << "\t" << "state" << endl;
  output.close();

  for(unsigned i=0; i < nRuns; ++i)
    {
      t = 0.0;  // Initial condition
      n = 1;
      
      while(n>0 && n<N)  // Loop over timesteps until fixation
	{     
	  r[0] = (double)rand()/(double)RAND_MAX; // Generate 2 uniform random numbers in (0,1]
	  r[1] = (double)rand()/(double)RAND_MAX;
      
	  a[0] = (double)n * ( (double)N - (double)n) / (double)N; // Calculate propensity functions and sum
	  a[1] = (double)n * ( (double)N - (double)n) / (double)N;
	  a0 = 0.0;
	  for(unsigned m=0; m < nReactions; ++m) a0 += a[m];
       
	  tau = (1.0/a0) * log(1.0/r[0]);  // Calculate time step
	  t += tau;
	  
	  sum = 0.0;  // Determine which reaction channel has fired
	  for(unsigned m=0; m < nReactions; ++m)
	    {
	      sum += a[m];
	      if(sum > a0*r[1]){mu=m;break;}
	    }

	  if( mu == 0 ) n++;
	  else n--;
	}// End of loop over timesteps
      
      output.open(filename,ios::app);  // Append to file after each run
      output << t << "\t" << n << endl;
      output.close();
    }// End of loop over runs
  
  return(0);
}
