//model.h
//=========================================
// Guard
#ifndef __MODEL_H_INCLUDED__
#define __MODEL_H_INCLUDED__ 
//=========================================
// Dependencies
#include <vector>
//=========================================

class Model
{
 private:
  int Bar;
  unsigned nparams,nspecies,nreactions;

  std::vector<double> Params;
  std::vector<unsigned> Initial_condition;
  std::vector<std::vector<int> > Stoichiometric_matrix;
  
 public:
  // Constructor
 Model() : Bar(0)
    {
      set_parameters();
      set_initial_condition();
      set_stoichiometry();
    };

  // Allow the SSA class to see Model private data
  friend class SSA;
  
  //=========================================
  // Definitions of functions to be modified
  //=========================================
  void set_parameters();
  void set_initial_condition();
  void set_stoichiometry();
  double reaction_rates(unsigned& reaction_, std::vector<unsigned>& x_);
  bool continue_sim(std::vector<unsigned>& x_, double& t);

  //=========================================
  // Definitions of access functions
  //=========================================
  std::vector<double> get_all_parameters();
  double get_parameter(unsigned index_);
  std::vector<unsigned> get_initial_condition();
  std::vector<int> get_stoichiometric_vector(unsigned& reaction_);

};
#endif 
