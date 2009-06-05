#include "../tools/random.h" //for drand() and uirand()
#include <iostream>
#include <cmath> // for exp()

#include "./IsingLattice.hpp"
#include "../binning/CStat.h" // for statistics and binning analysis

int main(){
	
	const int N = 10;
	IsingLattice grid(N);
	
	//srandom(1); //optionally seed the random generator
	const int MC_STEPS = 1000000;
	const double betaTwoJ = 0.2;
	
	double *prob = new double[7];
	for(int i = 0; i <= 6; ++i){
		// index i == delta_e / 2 + 3
		prob[i] = exp(-betaTwoJ * (double)(2 * i - 6));
	}
	
	// Aggregators for statistics and binning analysis
	CStat energy_bin;
	CStat magnetization_bin;
	
	for (int step=0; step < MC_STEPS; ++step) {
		
		// choose a random site
		int x = uirand(N);
		int y = uirand(N);
		int z = uirand(N); 
		
		// Calculate energy change (divided by 2*J)
		int delta_e = grid.flip_energy(x,y,z);
		
		// flip (or not)
		if (delta_e <= 0){
			grid.flip(x,y,z);
		} else {
			if (drand() < prob[delta_e / 2 + 3]){
				grid.flip(x,y,z);
			}
		}
		
		energy_bin.add(grid.get_energy());
		magnetization_bin.add(grid.get_magnetization());
	}
	
	std::cout
		<< energy_bin.mean() << '\t'
		<< magnetization_bin.mean() << '\t'
		<< magnetization_bin.variance() << '\t' // susceptebility \xi * \beta
		<< energy_bin.variance() << std::endl;  // specific heat C_V * \beta^2
	//energy_bin.binning_error();
	//magnetization_bin.binning_error();
	
	return 0;
}
