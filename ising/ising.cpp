#include "../lattice_pbc/CLattice.h"
#include "../tools/random.h" //for drand() and uirand()
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
	
	double *prob = new double[7];
	for(int i = 0; i <= 6; ++i){
		// index i == delta_e / 2 + 3
		prob[i] = exp(-betaTwoJ * (double)(2 * i - 6));
	}
	
	for (int step=0; step < MC_STEPS; ++step) {
		
		// choose a random site
		int x = uirand(grid.Nx());
		int y = uirand(grid.Ny());
		int z = uirand(grid.Nz()); 
		
		// Calculate energy change (divided by 2*J)
		int delta_e = grid(x,y,z) * (
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
			if (drand() < prob[delta_e / 2 + 3]){
				grid(x,y,z) *= -1;
			}
		}
	}
	
	return 0;
}
