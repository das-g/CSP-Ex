#include "../tools/random.h" //for drand() and uirand()
#include <iostream>
#include <cmath> // for exp()

#include "./IsingLattice.hpp"

int main(){
	
	const int N = 10;
	IsingLattice grid(N);
	
	//srandom(1); //optionally seed the random generator
	const int MC_STEPS = 1000000;
	const double betaTwoJ = 1.;
	
	for (int step=0; step < MC_STEPS; ++step) {
		
		// choose a random site
		int x = uirand(N);
		int y = uirand(N);
		int z = uirand(N); 
		
		double delta_e = grid.flip_energy(x,y,z);
		
		// flip (or not)
		if (delta_e <= 0){
			grid.flip(x,y,z);
		} else {
			double probability = (exp(-betaTwoJ * delta_e));
			//std::cerr << probability  << std::endl;
			if (drand() < probability){
				grid.flip(x,y,z);
			}
		}
	}
	
	return 0;
}
