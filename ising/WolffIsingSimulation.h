//
// C++ Interface: WolffIsingSimulation
//
// Description:  Holds the paramemeters for one simulation,
//              gives the option to run it and to query
//              the results.
//
//
// Author: Raphael Das Gupta <raphaeld@ethz.ch>, (C) 2009
//
// Copyright: All rites reversed -- copy what you like.
//
//
#ifndef WOLFFISINGSIMULATION_H
#define WOLFFISINGSIMULATION_H

#include "./IsingSimulation.h" // base class
#include "../lattice_pbc/CLattice.h" // for additional lattice to mark visited sites
#include "../tools/random.h" // for drand()

/**
	@author Raphael Das Gupta
*/
class WolffIsingSimulation : public IsingSimulation
{
public:
	WolffIsingSimulation(const int &rL, const double &rReducedTemp);
	
	/* override */
	~WolffIsingSimulation();
	
private:
	/* override */
	void do_step();
	
	void add_to_cluster(int x, int y, int z, spin_t new_state){
		
		// Mark this size.
		mrAlreadyTried(x,y,z) = true;
		
		// Maybe add neighbouring sites.
		spin_t my_state = mrGrid(x, y, z);
		try_add(x+1,y  ,z  , my_state, new_state);
		try_add(x  ,y+1,z  , my_state, new_state);
		try_add(x  ,y  ,z+1, my_state, new_state);
		try_add(x-1,y  ,z  , my_state, new_state);
		try_add(x  ,y-1,z  , my_state, new_state);
		try_add(x  ,y  ,z-1, my_state, new_state);
		
		// Update cluster (partially ... this is recursive,
		// so updating the current site is sufficient here)
		mrGrid(x, y, z) = new_state;
	}
	
	void try_add(int x, int y, int z, spin_t callerState, spin_t new_state){
		mrAlreadyTried.make_indices_sane(x, y, z);
		if(
		      (not mrAlreadyTried(x, y, z))
		   && (callerState == mrGrid(x, y, z))
		   && (drand() < mWolffProb)
		  ) {
			add_to_cluster(x, y, z, new_state);
		  }
	}
	
	CLattice<bool>& mrAlreadyTried;
	
	const double mWolffProb;
};

#endif //WOLFFISINGSIMULATION_H
