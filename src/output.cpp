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
      ofstream output;
      output.open(Filename_final_state);
      for(unsigned i = 0; i < Params.size(); ++i) output << Params[i] << "\t";
      output << endl;
      output.close();
    }
 
  if(Output_timeseries)
    {
      // Output parameter vector
      ofstream output;
      output.open(Filename_timeseries);
      for(unsigned i = 0; i < Params.size(); ++i) output << Params[i] << "\t";
      output << endl;
      output.close();
    }
}

// Write results to file
void Output::write_results()
{
  if(Output_final_state)
    {
      ofstream output;
      output.open(Filename_final_state, ios::app);

      // Output time and state(s) to one line
      output << Final_time;
      for(unsigned i = 0; i < Final_state.size(); ++i) output << "\t" << Final_state[i];
      output << endl;
      
      output.close();
    }

  if(Output_timeseries)
    {
      ofstream output;
      output.open(Filename_timeseries, ios::app);

      // Output time vector to one line
      for(unsigned j = 0; j < Timeseries_time.size(); ++j) output << Timeseries_time[j] << "\t";
      output << endl;

      // Output state of one variable over time to each line
      for(unsigned i = 0; i < Timeseries_state[0].size(); ++i)
	{
	  for(unsigned j = 0; j < Timeseries_state.size(); ++j) output << Timeseries_state[j][i] << "\t";
	  output << endl;
	}
      
      output.close();
    }
  
}
