#ifndef ISING_LATTICE_HPP
#define ISING_LATTICE_HPP

#include "../lattice_pbc/CLattice.h"

typedef int spin_t;
#define spin_up 1
#define spin_down -1

typedef CLattice<spin_t> grid_t;

class IsingLattice : private grid_t
{
	public:
		IsingLattice(int side_length);
		//~IsingLattice();
		
		double flip_energy(int x, int y, int z);
		void flip(int x, int y, int z){
			(*this)(x,y,z) *= -1;
		}
	private:
		void initialize();
		
};

#endif //ISING_LATTICE_HPP
