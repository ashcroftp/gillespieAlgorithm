//rng.h
//=========================================
// Guard
#ifndef __RNG_H_INCLUDED__
#define __RNG_H_INCLUDED__ 
//=========================================
// Dependencies
#include <random>
//=========================================

class RNG
{
 private:
  int Seed;
  std::mt19937 MT_engine;
  std::uniform_real_distribution<double> uniform_distribution;
  
 public:
  // Constructor (empty -- uses random device as seed)
 RNG() : Seed( (std::random_device())() ), MT_engine(Seed), uniform_distribution(0.0, 1.0)  {};
  // Constructor which passes seed
 RNG(int Seed_) : Seed(Seed_), MT_engine(Seed_), uniform_distribution(0.0, 1.0) {};

  //=========================================
  // Definitions of access functions
  //=========================================
  int get_seed();


  //=========================================
  // Definitions of random number functions
  //=========================================

  double rand_uni();
  double rand_exp(double lambda_);
  
};

#endif 
