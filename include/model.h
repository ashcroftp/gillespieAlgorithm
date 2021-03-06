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
  unsigned ParamIndex;
  unsigned nparams,nspecies,nreactions;

  std::vector<double> Params;
  std::vector<unsigned> Initial_condition;
  std::vector<std::vector<int> > Stoichiometric_matrix;
  
 public:
  // Constructor
 Model() : ParamIndex(0) {modelInit();};
  // Constructor with paramIndex
 Model(unsigned& ParamIndex_) : ParamIndex(ParamIndex_) {modelInit();};
  
  // initialiser function
  void modelInit()
  {
    set_parameters();
    set_initial_condition();
    set_stoichiometry();
  };
  
  //=========================================
  // Definitions of access functions
  //=========================================
  unsigned get_nspecies(){return nspecies;};
  unsigned get_nreactions(){return nreactions;};
  std::vector<double> get_all_parameters(){return Params;};
  double get_parameter(unsigned index_){return Params[index_];};
  std::vector<unsigned> get_initial_condition(){return Initial_condition;};
  std::vector<int> get_stoichiometric_vector(unsigned reaction_){return Stoichiometric_matrix[reaction_];};


  //=========================================
  // Definitions of functions to be modified
  //=========================================
  void set_parameters();
  void set_initial_condition();
  void set_stoichiometry();
  double reaction_rates(unsigned& reaction_, std::vector<unsigned>& x_);
  bool continue_sim(std::vector<unsigned>& x_, double& t);

  //=========================================
  // Problem specific functions
  //=========================================
  
};
#endif 
