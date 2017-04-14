# gillespieAlgorithm
My basic template for a c++ implementation of the Gillespie stochastic simulation algorithm.

## Why c++?
Because it's fast, portable, and easy to run on clusters/supercomputers!

## What files do we have?
* `main.cpp` contains the workflow

* `ssa.h/cpp` contains the machinery for updating the state of the system.
This file should **not** be edited!

* `rng.cpp` contains our definition of the random number generator.
The default is to use the Mersenne Twister *mt19937* generator, which is included in the `<random>` header.
Note that this requires `c++11`, and compilation may require an explicit `g++ -std=c++11 ...`.
Again this file should **not** be modified per-project, but may be edited if different random number generators/functions are required.

* `outputData.h/cpp` contains different output functions.
Whether we record just the final result, or the full timeseries is determined by this file.
**Yet to be created**

* `model.h/cpp` contains information about the population and reaction dynamics.
The `model.cpp` file should be modified for each project.
There are *three* functions that need to be modified:
	+ `set_initial_condition()`: This function assigns the initial population values using the following line of code to assign two species with 50 individuals each:

		```
		vector<unsigned> x = {50, 50};
		```
		
	+ `set_stoichiometry()`: This assigns a matrix, where each row corresponds to a reaction and each column to a species.
Each row $i$ represents the change to the number of each species following the firing of reaction $i$.
If we have two reactions, the first increases species 1 and decreases species 2 by one unit, and the second vice-versa, we need to assign:

		```
		stoich_mat[0] = {+1, -1};
  		stoich_mat[1] = {-1, +1};
		```
		
	+ `reaction_rates(index, x)`: The reaction rates are a function of the state of the population (and maybe later they can be a function of time, too).
This function returns the rate of reaction `index`, which is selected from the list using the `switch(index)` function.
This should take the form:

		```
		switch(index)
    			{
    				case 0 :
      				return (double)x_[0] * (double)x_[1] / (double)N;
      				break;

    				case 1 :
      				return (double)x_[0] * (double)x_[1] / (double)N;
      				break;

    				default :
      				return 0.0;
    			}
		```

## Compilation
For now compilation requires the following command:

```
g++ main.cpp ssa.cpp rng.cpp model.cpp
```

One day I'll turn this into a makefile...