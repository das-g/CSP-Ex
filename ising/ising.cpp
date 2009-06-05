#include "../tools/random.h" //for drand() and uirand()
#include <iostream> // for output of results
#include <cmath> // for exp()

#include "./IsingLattice.hpp" // simple wrapper class for CLattice
#include "../binning/CStat.h" // for statistics and binning analysis

void do_simulation(const double &kT /* Boltzmann constant * temperature */){
	
	const int N = 10;
	IsingLattice grid(N);
	
	//srandom(1); //optionally seed the random generator
	const int MC_STEPS = 1000000; // Number of Monte Carlo steps
	
	const double two_J = 2.; // 2-particle interaction energy between nearest neighbours
	const double beta_two_J = two_J / kT; // 2 * beta * J, where beta=1/kT
	
	// Probablilities of acceptance of proposed MC steps,
	// depending on the change of enegergy delta_e
	double *prob = new double[7];
	for(int i = 0; i <= 6; ++i){
		// The relation between the index of the array and delta_e is:
		// index i == delta_e / 2 + 3
		
		prob[i] = exp(-beta_two_J * (double)(2 * i - 6));
	}
	
	// Aggregators for statistics and binning analysis
	CStat energy_bin;
	CStat magnetization_bin;
	
	// MAIN LOOP of the simulation
	for (int step=0; step < MC_STEPS; ++step) {
		
		// choose a random site
		int x = uirand(N);
		int y = uirand(N);
		int z = uirand(N); 
		
		// Calculate energy change (divided by 2*J)
		int delta_e = grid.flip_energy(x,y,z);
		
		// flip (or not)
		// using Metropolis probabilities
		if (delta_e <= 0){
			// always flip if energy would decrease
			grid.flip(x,y,z);
		} else {
			// flip with lower probablity the more the energy wour increase
			if (drand() < prob[delta_e / 2 + 3]){
				grid.flip(x,y,z);
			}
		}
		
		// Sample energy and magnetization
		energy_bin.add(grid.get_energy());
		magnetization_bin.add(grid.get_magnetization());
		
	} // END of MAIN LOOP of the simulation
	
	std::cout
		<< kT << '\t'
		<< energy_bin.mean() << '\t'
		<< magnetization_bin.mean() << '\t'
		<< magnetization_bin.variance() * kT << '\t' // susceptibility \xi
		<< energy_bin.variance() * kT * kT << std::endl;  // specific heat C_V
	//energy_bin.binning_error();
	//magnetization_bin.binning_error();
	
	return;
}

int main(){
	std::cout << "kT\tenergy\tmagnetization\tsusceptibility\tspecific_heat" << std::endl;
	for(double kT = 0.1; kT <= 20.; kT += 0.3){
		do_simulation(kT);
	}
}
