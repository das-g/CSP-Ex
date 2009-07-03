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
	IsingSimulation(rL,rReducedTemp)
{
	//empty
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
		
		// Calculate energy change (divided by 2*J)
	int delta_e = mrGrid.flip_energy(x,y,z);
		
		// flip (or not)
		// using Metropolis probabilities
	if (delta_e <= 0){
			// always flip if energy would decrease
		mrGrid.flip(x,y,z);
	} else {
			// flip with lower probablity the more the energy wour increase
		if (drand() < mProb[delta_e / 2 + 3]){
			mrGrid.flip(x,y,z);
		}
	}
}
