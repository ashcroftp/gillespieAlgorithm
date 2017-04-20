//output.cpp
//=========================================
#include "output.h"

using namespace std;

//=========================================
// Output functions
//=========================================

// Record final state and time
void Output::store_final_state(double& t_, vector<unsigned>& x_)
{
  // Assign
  Final_time = t_;
  Final_state = x_;
}

// Record the instantaneous time and state by adding to vectors
void Output::initialise_timeseries(double& t_, vector<unsigned>& x_)
{
  //Initialise
  Timeseries_time.resize(1);
  Timeseries_state.resize(1);
  
  // Assign
  Timeseries_time[0] = t_;
  Timeseries_state[0] = x_;
}

// Record the instantaneous time and state by adding to vectors
void Output::store_timeseries(double& t_, vector<unsigned>& x_)
{
  Timeseries_time.push_back(t_);
  Timeseries_state.push_back(x_);
}

// Write parameters to first line of file
void Output::write_parameters()
{
  if(Output_final_state)
    {
      // Output parameter vector
      for(unsigned i = 0; i < Params.size(); ++i) cout << Params[i] << "\t";
      cout << endl;
    }
 
  if(Output_timeseries)
    {
      // Output parameter vector
      for(unsigned i = 0; i < Params.size(); ++i) cout << Params[i] << "\t";
      cout << endl;
    }
}

// Write results to file
void Output::write_results()
{
  if(Output_final_state) cout << Final_time << endl;

  if(Output_timeseries) cout << Timeseries_time.back() << endl;
}
