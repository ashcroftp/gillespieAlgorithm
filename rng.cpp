//rng.cpp
//=========================================
#include "rng.h"

using namespace std;

//=========================================
// Access functions
//=========================================
int RNG::get_seed()
{
  return(Seed);
}


//=========================================
// Random number functions
//=========================================
double RNG::rand_uni()
{
  // Draw uniform random number
  double uni_rn = uniform_distribution(MT_engine);
  
  return(uni_rn);
}

//=========================================
double RNG::rand_exp(double lambda_)
{
  // Draw uniform random number
  double uni_rn = uniform_distribution(MT_engine);
  // Convert uniform to exponential rn with parameter lambda_
  double exp_rn = (1.0 / lambda_) * log(1.0 / uni_rn);
  
  return(exp_rn);
}
