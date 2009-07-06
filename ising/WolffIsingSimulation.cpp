//
// C++ Implementation: WolffIsingSimulation
//
// Description: Holds the paramemeters for one simulation,
//              gives the option to run it and to query
//              the results.
//
//
// Author: Raphael Das Gupta <raphaeld@ethz.ch>, (C) 2009
//
// Copyright: All rites reversed -- copy what you like.
//
//
#include "WolffIsingSimulation.h"

WolffIsingSimulation::WolffIsingSimulation(const int &rL, const double &rReducedTemp)
	:
	IsingSimulation(rL,rReducedTemp),
	mrAlreadyTried(*(new CLattice<bool>(rL,rL,rL))),
	mWolffProb(1. - exp(-mBeta)) // should be (1. - exp(-mBeta * J)), but J == 1.
{
	// empty
}

/* override */
WolffIsingSimulation::~WolffIsingSimulation()
{
	//empty
}

/* override */
void WolffIsingSimulation::do_step(){
	// choose a random site
	int x = uirand(mrGrid.Nx());
	int y = uirand(mrGrid.Ny());
	int z = uirand(mrGrid.Nz());
	
	// Choose random new state for the cluster.
	// We do this already here, so we can apply it on the fly
	// without having to save the added sites.
	spin_t new_state = uirand(2) * (spin_up - spin_down) + spin_down;
	
	// clear markers of sites tried to add to any previous steps' clusters
	mrAlreadyTried.set_all(false);
	
	add_to_cluster(x, y, z, new_state); // this actually adds the site chosen above unconditionally, because we pass it's own state.
}
