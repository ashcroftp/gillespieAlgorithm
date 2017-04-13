//model.h
//=========================================
// Guard
#ifndef __MODEL_H_INCLUDED__
#define __MODEL_H_INCLUDED__ 
//=========================================
// Dependencies
#include <vector>
#include <iostream>
//=========================================

class Model
{
 private:
  int Bar;
  unsigned N;
  unsigned nspecies;
  unsigned nreactions;
  std::vector<std::vector<int> > Stoichiometric_matrix;
  std::vector<unsigned> Initial_condition;
  
 public:
  // Constructor
 Model() : Bar(99), N(100), nreactions(2), nspecies(2) {};

  //=========================================
  // Definitions of functions to be modified
  //=========================================
  void set_initial_condition();
  void set_stoichiometry();
  double reaction_rates(unsigned& reaction_, std::vector<unsigned>& x_);

  //=========================================
  // Definitions of access functions
  //=========================================
  std::vector<int> get_stoichiometric_vector(unsigned& reaction_);
  std::vector<unsigned> get_initial_condition();
  std::vector<double> get_reaction_rates(std::vector<unsigned>& x_);

  //=========================================
  // Definitions of other functions
  //=========================================
  unsigned choose_reaction(std::vector<double>& rates_, double& rand_);
  std::vector<unsigned> update_population(unsigned& reaction_, std::vector<unsigned>& x_);  
};

#endif 
