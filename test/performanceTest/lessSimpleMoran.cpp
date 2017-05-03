//lessSimpleMoran.cpp
// Still a simple Moran model, but implements classes and functions

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Class to store all parameters for the model
// and the Gillespie algorithm
class GillespieAlgorithm
{
private:
  // System parameters
  unsigned nReactions;  // Number of reaction channels
  unsigned N;  // System size parameter

  // Analysis paramters
  unsigned nRuns;
  ofstream Output;
  char filename[99];
  
public:
  // Constructor
  GillespieAlgorithm(unsigned& N_, unsigned& nReactions_, unsigned& nRuns_)
    : N(N_), nReactions(nReactions_), nRuns(nRuns_)
  {
    sprintf(filename, "lessSimpleMoran.dat");
  };
  
  // Member functions
  void run();  // Run the nRuns simulations
  double propensity_functions(unsigned& reaction, unsigned& n);  // Propensity function declaration
  void population_update(unsigned& reaction, unsigned& n); // Population update declaration
  void compute(unsigned runIndex);  // Execute Gillespie algorithm and output sample data
  
}; // End of GillespieAlgorithm class


// Run simulations
void GillespieAlgorithm::run()
{
  for(unsigned i=0; i<nRuns; i++) compute(i);
}// End of GillespieAlgorithm::run()


// Propensity functions for all possible reactions
double GillespieAlgorithm::propensity_functions(unsigned& reaction, unsigned& n)
{
  switch(reaction)
    {
    case 0 : // n -> n+1
      return (double)n * ( (double)N - (double)n ) / (double)N;
      break;
     
    case 1 : // n -> n-1
      return (double)n * ( (double)N - (double)n ) / (double)N;
      break;
      
    default :
      return 0.0;
    }// End of switch
}// End of GillespieAlgorithm:propensity_functions()


// Population update for all possible reactions
void GillespieAlgorithm::population_update(unsigned& reaction, unsigned& n)
{
  switch(reaction)
    {   
    case 0 : // n -> n+1
      n++;
      break;
	   
    case 1 : // n -> n-1
      n--;
      break;

    default :
      n++;n--;
    }// End of switch
}// End of GillespieAlgorithm::population_update()



// Execute Gillespie algorithm and output data
void GillespieAlgorithm::compute(unsigned runIndex)
{
  // Initialisation
  vector<double> a(nReactions);  // Propensity value storage for each reaction
  double a0;  // Propensity sum
 
  double t;  // Time storage
  unsigned n;  // Population number storage
 
  vector<double> r(2);  // Variables to store random numbers, time step and fired reaction
  double tau,sum;
  unsigned mu;

  // Initial condition
  t = 0.0;
  n = 1;

  // Algorithm
  while(n>0 && n<N)  // Loop over timesteps until fixation
    {
      r[0] = (double)rand()/(double)RAND_MAX;  // Generate 2 uniform random numbers in (0,1]
      r[1] = (double)rand()/(double)RAND_MAX;
      
      a0 = 0.0;  // Calculate propensity functions
      for(unsigned m=0; m < nReactions; ++m)
	{
	  a[m] = propensity_functions(m,n);
	  a0 += a[m];
	}
       
      tau = (1.0/a0) * log(1.0/r[0]);  // Calculate time step

      sum = 0.0;  // Determine which reaction channel has fired
      for(unsigned m=0; m < nReactions; ++m)
	{
	  sum += a[m];
	  if(sum > a0*r[1]){mu=m;break;}
	}

      population_update(mu,n); t += tau;  // Update population and time
    }// End of loop over timesteps


  // Output fixation status
  Output.open(filename,ios::app); // Append to file after each run
  Output << t << "\t" << n << endl;
  Output.close();

}// End of GillespieAlgorithm::compute()



// Executable takes arguments in array argv
int main(int argc, char* argv[])
{
  unsigned N = 10;
  unsigned nReactions = 2;
  unsigned nRuns = atoi(argv[1]);
  
  GillespieAlgorithm gillespie(N,nReactions,nRuns);  // Construct the GillespieAlgorithm class with these indices
  gillespie.run();  // Execute this simulation block
  return 0;
}
