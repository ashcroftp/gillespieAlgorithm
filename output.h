//output.h
//=========================================
// Guard
#ifndef __OUTPUT_H_INCLUDED__
#define __OUTPUT_H_INCLUDED__ 
//=========================================
// Dependencies

#include <vector>
#include <iostream>
#include <fstream>
//=========================================

class Output
{
 private:
  bool Output_final_state,Output_timeseries;
  
  double Final_time;
  std::vector<unsigned> Final_state; 

  std::vector<double> Timeseries_time;
  std::vector<std::vector<unsigned> > Timeseries_state;
  
 public:
  // Constructor -- default is to output final state
 Output() : Output_final_state(true), Output_timeseries(false) {};
  // Constructor -- outpur arguments
 Output(bool& Output_final_state_, bool& Output_timeseries_) : Output_final_state(Output_final_state_), Output_timeseries(Output_timeseries_) {};

  //=========================================
  // Definitions of access functions
  //=========================================
  bool get_output_final_state(){return Output_final_state;};
  bool get_output_timeseries(){return Output_timeseries;};
  
  //=========================================
  // Definitions of output functions
  //=========================================
  void store_final_state(double& t_, std::vector<unsigned>& x_);
  void initialise_timeseries(double& t_, std::vector<unsigned>& x_);
  void store_timeseries(double& t_, std::vector<unsigned>& x_);
  void write_to_file();
  
};

#endif 