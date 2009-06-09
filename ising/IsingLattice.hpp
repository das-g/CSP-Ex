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
		
		int flip_energy(int x, int y, int z);
	
		void flip(int x, int y, int z){
			m_energy += flip_energy(x, y, z);
			(*this)(x,y,z) *= -1;
			m_magnetization += 2 * (*this)(x,y,z);
		}
		
		int get_energy(){
			return m_energy;
		}
		
		int get_magnetization(){
			return m_magnetization / size();
		}
	
	private:
		void initialize();
		int m_energy; // Total energy of the system, devided by 2*J
		int m_magnetization; // Total magnetization of the system
};

#endif //ISING_LATTICE_HPP
