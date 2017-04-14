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
There are *five* functions that need to be modified:
	+ `set_parameters()': First we declare how many parameters, species, and reactions are present in our model.
We then store all model parameters, such as reaction rates, population size, time limits, etc. in a single vector for easy access.
This is asigned as follows:
		```
		// Define numbers of parameters, species and reactions
		nparams = 1;
		nspecies = 2;
 		nreactions = 2;

		// Assign temp vector and fill in parameters
		vector<double> params(nparams);
		params[0] = 100; // N
		```

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
      				return (double)x_[0] * (double)x_[1] / Params[0];
      				break;

    				case 1 :
      				return (double)x_[0] * (double)x_[1] / Params[0];
      				break;

    				default :
      				return 0.0;
    			}
		```

	+ `continue_sim(x, t)`: This function determines the end-condition of our simulation. For example, if we stop the simulation once a species has reached fixation or extonction we have:
		```
		bool b(true);

		if(x_[0] == 0 || x_[0] == Params[0]) b = false;
  
		return(b);
		```

## Compilation
To compile the executable `gillespie`, simply run the `make` command.
Basically, this runs the following command:
```
g++ main.cpp ssa.cpp rng.cpp model.cpp
```
It also includes the `make clean` option to tidy up the directory.
