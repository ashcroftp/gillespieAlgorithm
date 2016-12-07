// simCoex_cluster.cpp
// Exact SSA (1977) implementation of coordination game

// args=[ gammaIndex betaIndex fpIndex simIndex numRuns ]

// Record fixation state and time
// in file fixationBlock_...

// Designed to be distributable

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

// Class to store all parameters for the model
// and the Gillespie algorithm
class GillespieAlgorithm
{
private:
  // System parameters
  unsigned nReactions;       // Number of reaction channels
  unsigned N0;               // Initial system size parameter

  // Reaction rates
  double A,B,C,D;            // Payoff parameters
  double gamma;              // Growth rate parameter
  double beta;               // Selection strength
  double FP;                 // Fixed point location
    
  // Analysis paramters
  unsigned gammaIndex,betaIndex,fpIndex,simIndex;     // Parameter regime and simulation indices
  unsigned nRuns;                                     // Number of runs
  vector<int> seeds;                                  // Vector for seeds
  ofstream Output;                                    // Ofstream for results
  char fixationFilename[100];                         // Results filename
  char seedsFilename[100];                            // Output file to store RNG seeds
  
public:
  // Constructor (Empty)
  GillespieAlgorithm()
    : gammaIndex(0), betaIndex(0), fpIndex(0), simIndex(0), nRuns(1),
      nReactions(4)
  {  
    seeds.resize(nRuns);      // Resize seed vector and define filenames
    sprintf(fixationFilename, "fixationBlock_%03i_%03i_%03i_%03i.dat", gammaIndex, betaIndex, fpIndex, simIndex);
    sprintf(seedsFilename, "seedsBlock_%03i_%03i_%03i_%03i.dat", gammaIndex, betaIndex, fpIndex, simIndex);
  };

  // Constructor
  GillespieAlgorithm(unsigned& gammaIndex_, unsigned& betaIndex_, unsigned& fpIndex_, unsigned& simIndex_, unsigned& nRuns_)
    : gammaIndex(gammaIndex_), betaIndex(betaIndex_), fpIndex(fpIndex_), simIndex(simIndex_), nRuns(nRuns_),
      nReactions(4)
  {
    seeds.resize(nRuns);      // Resize seed vector and define filenames
    sprintf(fixationFilename, "fixationBlock_%03i_%03i_%03i_%03i.dat", gammaIndex, betaIndex, fpIndex, simIndex);
    sprintf(seedsFilename, "seedsBlock_%03i_%03i_%03i_%03i.dat", gammaIndex, betaIndex, fpIndex, simIndex);
  };
  
  // Member functions
  void initialise_seeds();                                                  // Seed initialisation
  void set_parameters();                                                    // Assign parameters
  void output_parameters();                                                 // Output parameters
  void run();                                                               // Run the nRuns simulations
  double propensity_functions(unsigned& reaction, unsigned& n, unsigned& N, double& t); // Propensity function declaration
  void population_update(unsigned& reaction, unsigned& n, unsigned& N);     // Population update declaration
  void compute(unsigned runIndex);                                          // Execute Gillespie algorithm and output sample data


  // Inline functions for fitnesses
  double payoff(unsigned& n, unsigned& N) { return ( ( ((double)n - 1.) * A + ((double)N - (double)n) * B ) - ( ((double)n) * C + ((double)N - (double)n - 1.) * D ) ) / ((double)N - 1.); }
  double fitnessA(unsigned& n, unsigned& N) { return 1. / (1. + exp( -beta * payoff(n,N) ) ); }
  double fitnessB(unsigned& n, unsigned& N) { return 1. / (1. + exp( beta * payoff(n,N) ) ); }

  // Inline function for growth
  double growth(double& t) { return gamma / t; }
  
}; // End of GillespieAlgorithm class



// Seed initialisation
void GillespieAlgorithm::initialise_seeds()
{
  random_device rd;                                                         // Define random device
  mt19937 my_seed_gen(rd());                                                // Use local machine randomness to initialise the seed generator
  uniform_int_distribution<int> seed_dist;                                  // Assign distribution of seeds (uniform ints)
  for(unsigned i = 0;i<1000;i++) int a = seed_dist(my_seed_gen);            // Burn-in 1000 random numbers
  for(unsigned i = 0; i < nRuns; i++) seeds[i] = seed_dist(my_seed_gen);    // Fill seeds vector

  // Output seeds to file
  Output.open(seedsFilename);
  for(unsigned i = 0; i < nRuns; i++) Output << seeds[i] << endl;
  Output.close();
}// End of GillespieAlgorithm::initialise_seeds()



// Assign model parameters
void GillespieAlgorithm::set_parameters()
{
  N0 = 100;                // Initial system size
  
  gamma = pow(10.0,( (double)gammaIndex / 20.0 ) - 1.0 ) - 0.1;
  
  beta = 0.1;//pow(10.0,( ( (double)betaIndex / 2.0 ) - 2.0 ) );

  FP = 0.5 + (0.1 * (double)fpIndex);

  // Coexistence parameterisation
  A = 1.;                  // Payoff parameters
  B = 1. + FP;
  C = 2. - FP;
  D = 1.;
}// End of GillespieAlgorithm::set_parameters()


// Run simulations
void GillespieAlgorithm::run()
{
  for(unsigned i=0; i<nRuns; i++) compute(i);
}// End of GillespieAlgorithm::run()



// Output model parameters
void GillespieAlgorithm::output_parameters()
{
  // Open fixationBlock... file
  Output.open(fixationFilename);
  Output << gamma << "\t" << beta << "\t" << FP << endl;
  Output.close();
}// End of GillespieAlgorithm::output_parameters()



// Propensity functions for all possible reactions
double GillespieAlgorithm::propensity_functions(unsigned& reaction, unsigned& n, unsigned& N, double& t)
{
  switch(reaction)
    {
    case 0 : // n -> n+1
      return ( (double)n * ((double)N - (double)n) / (double)N ) * fitnessA(n,N);
      break;
     
    case 1 : // n -> n-1
      return ( (double)n * ((double)N - (double)n) / (double)N ) * fitnessB(n,N);
      break;

    case 2 : // n -> n+1, N -> N+1
      return (double) n * growth(t);
      break;

    case 3 : // N -> N+1
      return ( (double)N - (double)n ) * growth(t);
      break;
      
    default :
      return 0.0;
    }// End of switch
}// End of GillespieAlgorithm:propensity_functions()



// Population update for all possible reactions
void GillespieAlgorithm::population_update(unsigned& reaction, unsigned& n, unsigned& N)
{
  switch(reaction)
    {   
    case 0 : // n -> n+1
      n++;
      break;
	   
    case 1 : // n -> n-1
      n--;
      break;
      
    case 2 : // n -> n+1, N -> N+1
      n++;N++;
      break;
      
    case 3 : // N -> N+1
      N++;
      break;

    default :
      n++;n--;
    }// End of switch
}// End of GillespieAlgorithm::population_update()



// Execute Gillespie algorithm and output data
void GillespieAlgorithm::compute(unsigned runIndex)
{
  // Initialisation
  int seed = seeds[runIndex];                         // Get seed from vector
  mt19937 mt_rand(seed);                              // Initialise RNG using seed
  uniform_real_distribution<double> dist(1.0e-9,1.0); // We want RNs in (0,1]
  
  vector<double> aa(nReactions);                      // Propensity value storage for each reaction
  double aa0;                                         // Propensity sum
 
  double t;                                           // Time storage
  unsigned n,N;                                       // Population number storage
 
  vector<double> r(2);                                // Variables to store random numbers, time step and fired reaction
  double tau,sum;
  unsigned mu;

  // Initial condition
  t = 1.0;
  N = N0;
  n = 1;

  // Algorithm
  while(n>0 && n<N && t<20000)                        // Loop over timesteps until fixation
    {      
      r[0] = dist(mt_rand); r[1] = dist(mt_rand);     // Generate 2 uniform random numbers in (0,1]
      
      aa0 = 0.0;                                      // Calculate propensity functions
      for(unsigned m=0; m < nReactions; m++)
	{
	  aa[m] = propensity_functions(m,n,N,t);
	  aa0 += aa[m];
	}
       
      tau = (1.0/aa0) * log(1.0/r[0]);                // Calculate time step

      sum = 0.0;                                      // Determine which reaction channel has fired
      for(unsigned m=0; m < nReactions; m++)
	{
	  sum += aa[m];
	  if(sum > aa0*r[1]){mu=m;break;}
	}

      population_update(mu,n,N); t += tau;             // Update population and time
    }// End of loop over timesteps


  // Output fixation status
  Output.open(fixationFilename,ios::app);             // Append to file after each run
  Output << t << "\t" << n << "\t" << N << endl;
  Output.close();

}// End of GillespieAlgorithm::compute()



// Executable takes arguments in array argv
int main(int argc, char* argv[])
{
  if(argc != 6)    // Argument check
    {
      cout << "ERROR: There should be 5 arguments!" << endl;
      return 1;
    }
  
  unsigned gammaIndex = atoi(argv[1]);     // Index of growth exponent
  unsigned betaIndex = atoi(argv[2]);      // Index of selection strength
  unsigned fpIndex = atoi(argv[3]);        // Index of fixed point
  unsigned simIndex = atoi(argv[4]);       // Growth rate exponent
  unsigned nRuns = atoi(argv[5]);          // Number of runs per node
  
  GillespieAlgorithm gillespie(gammaIndex,betaIndex,fpIndex,simIndex,nRuns);      // Construct the GillespieAlgorithm class with these indices
  gillespie.initialise_seeds();                                 // Initialise seeds vector using local machine randomness
  gillespie.set_parameters();                                   // Assign the model parameters according to paramIndex
  gillespie.output_parameters();                                // Output model parameters to file
  gillespie.run();                                              // Execute this simulation block --
                                                                // results are written to file in real time
  return 0;
}
