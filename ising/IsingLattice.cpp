#include "./IsingLattice.hpp"

IsingLattice::IsingLattice(int N) : grid_t(N,N,N){
	initialize();
}

inline void IsingLattice::initialize(){
	// initialize the grid (all up)
	for (int i=0; i<Nx(); i++) {
		for (int j=0; j<Ny(); j++) {
			for (int k=0; k<Nz(); k++) {
				(*this)(i,j,k)=spin_up;
			}
		}
	}
}

int IsingLattice::flip_energy(int x, int y, int z){
	// Calculate energy change (divided by 2*J)
	return (*this)(x,y,z) * (
				    (*this)(x+1,y  ,z  )
				  + (*this)(x  ,y+1,z  )
				  + (*this)(x  ,y  ,z+1)
				  + (*this)(x-1,y  ,z  )
				  + (*this)(x  ,y-1,z  )
				  + (*this)(x  ,y  ,z-1)
		);
}
