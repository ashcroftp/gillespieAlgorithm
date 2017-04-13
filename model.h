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
  unsigned N;
  unsigned nspecies;
  unsigned nreactions;
  std::vector<std::vector<int> > Stoichiometric_matrix;
  std::vector<unsigned> Initial_condition;
  
 public:
  // Constructor
 Model() : N(100), nreactions(2), nspecies(2)
    {
      set_initial_condition();
      set_stoichiometry();
    };

  // Allow the SSA class to see Model private data
  friend class SSA;
  
  //=========================================
  // Definitions of functions to be modified
  //=========================================
  void set_initial_condition();
  void set_stoichiometry();
  double reaction_rates(unsigned& reaction_, std::vector<unsigned>& x_);

  //=========================================
  // Definitions of access functions
  //=========================================
  std::vector<unsigned> get_initial_condition();
  std::vector<int> get_stoichiometric_vector(unsigned& reaction_);

};
#endif 
