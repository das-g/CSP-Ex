//
// C++ Interface: IsingLattice
//
// Description: Wrapper class for CLattice<int>, keeping track of some
//              physical properties of the Ising model.
//
//
// Author: Raphael Das Gupta <raphaeld@ethz.ch>, (C) 2009
//
// Copyright: All rites reversed -- copy what you like.
//
//
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
			m_total_energy += flip_energy(x, y, z);
			(*this)(x,y,z) *= -1;
			m_total_magnetization += 2 * (*this)(x,y,z);
		}
		
		int get_total_energy(){
			return m_total_energy;
		}
		
		int get_total_magnetization(){
			return m_total_magnetization;
		}
		
		// make some methods of the private superclass public
		using grid_t::Nx;
		using grid_t::Ny;
		using grid_t::Nz;
		using grid_t::size;
	
	private:
		void initialize();
		int m_total_energy; // Total energy of the system, devided by 2*J
		int m_total_magnetization; // Total magnetization of the system
};

#endif //ISING_LATTICE_HPP
