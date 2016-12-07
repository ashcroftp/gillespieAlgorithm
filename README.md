# gillespieAlgorithm
My basic template for a c++ implementation of the Gillespie stochastic simulation algorithm.

## Why c++?
Because it's fast, portable, and easy to run on clusters/supercomputers!

## How does it work?
`main.cpp` contains the workflow

`ssa.h/cpp` contains the machinery for updating the state of the system.
This file should **not** be edited!

`myProcess.h/cpp` contains information about the population, the reaction rates (propensity functions) and the effects of each reaction (stoichiometry).
This file should be modified for each project.

`outputData.h/cpp` contains different output functions.
Whether we record just the final result, or the full timeseries is determined by this file.
