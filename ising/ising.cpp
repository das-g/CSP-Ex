#include "../lattice_pbc/CLattice.h"

typedef int spin_t;
#define spin_up 1
#define spin_down 0

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
	
	return 0;
}
