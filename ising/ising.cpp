#include "../lattice_pbc/CLattice.h"
#include <cstdlib> // for random()
#include <iostream>
#include <cmath> // for exp()

typedef int spin_t;
#define spin_up 1
#define spin_down -1

int main(){
	
	const int N = 10;
	CLattice<spin_t> grid(N,N,N);
	
	// initialize the grid (all up)
	for (int i=0; i<grid.Nx(); i++) {
		for (int j=0; j<grid.Ny(); j++) {
			for (int k=0; k<grid.Nz(); k++) {
				grid(i,j,k)=spin_up;
			}
		}
	}
	
	//srandom(1); //optionally seed the random generator
	const int MC_STEPS = 1000000;
	const double betaTwoJ = 1.;
	
	for (int step=0; step < MC_STEPS; ++step) {
		
		// choose a random site
		int x = (random() * grid.Nx()) / ((unsigned int)RAND_MAX + 1u);
		int y = (random() * grid.Ny()) / ((unsigned int)RAND_MAX + 1u);
		int z = (random() * grid.Nz()) / ((unsigned int)RAND_MAX + 1u);
		
		// Calculate energy change (divided by 2*J)
		double delta_e = grid(x,y,z) * (
						    grid(x+1,y  ,z  )
						  + grid(x  ,y+1,z  )
						  + grid(x  ,y  ,z+1)
						  + grid(x-1,y  ,z  )
						  + grid(x  ,y-1,z  )
						  + grid(x  ,y  ,z-1)
			);
		
		// flip (or not)
		if (delta_e <= 0){
			grid(x,y,z) *= -1;
		} else {
			double probability = (exp(-betaTwoJ * delta_e));
			//std::cerr << probability  << std::endl;
			if ((double)random()/ (double)(RAND_MAX+1) < probability){
				grid(x,y,z) *= -1;
			}
		}
	}
	
	return 0;
}
