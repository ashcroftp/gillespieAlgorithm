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
  unsigned ParamIndex,SimIndex;
  bool Output_final_state,Output_timeseries;
  char Filename_final_state[99],Filename_timeseries[99];
  
  std::vector<double> Params;
  
  double Final_time;
  std::vector<unsigned> Final_state; 

  std::vector<double> Timeseries_time;
  std::vector<std::vector<unsigned> > Timeseries_state;
  
 public:
  // Constructor -- default is to output final state only
 Output() : ParamIndex(0), SimIndex(0), Output_final_state(true), Output_timeseries(false) {nameFiles();};
  // Constructor -- specified file labels, default output
 Output(unsigned& ParamIndex_, unsigned& SimIndex_) : ParamIndex(ParamIndex_), SimIndex(SimIndex_), Output_final_state(true), Output_timeseries(false) {nameFiles();};
  // Constructor -- default file labels, specified outputs
 Output(bool& Output_final_state_, bool& Output_timeseries_) : ParamIndex(0), SimIndex(0), Output_final_state(Output_final_state_), Output_timeseries(Output_timeseries_) {nameFiles();};
  // Constructor -- specified file labels, specified outputs
 Output(unsigned& ParamIndex_, unsigned& SimIndex_, bool& Output_final_state_, bool& Output_timeseries_) : ParamIndex(ParamIndex_), SimIndex(SimIndex_), Output_final_state(Output_final_state_), Output_timeseries(Output_timeseries_) {nameFiles();};

  // Name the output files
  void nameFiles()
  {
    sprintf(Filename_final_state, "final.dat");
    sprintf(Filename_timeseries, "timeseries.dat");
  }
  
  //=========================================
  // Definitions of access functions
  //=========================================
  bool get_output_final_state(){return Output_final_state;};
  bool get_output_timeseries(){return Output_timeseries;};
  void set_model_params(std::vector<double> Params_){Params = Params_;};
  
  //=========================================
  // Definitions of output functions
  //=========================================
  void store_final_state(double& t_, std::vector<unsigned>& x_);
  void initialise_timeseries(double& t_, std::vector<unsigned>& x_);
  void store_timeseries(double& t_, std::vector<unsigned>& x_);
  void write_parameters();
  void write_results();
  
};

#endif 
