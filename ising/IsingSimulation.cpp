//
// C++ Implementation: IsingSimulation
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

#include <cmath> // for exp()
#include "../tools/random.h" //for drand() and uirand()

#include "./IsingSimulation.h"

IsingSimulation::IsingSimulation(const int &rL, const double &rReducedTemp)
	:
	mrGrid(*(new IsingLattice(rL))),
	mBeta(1./rReducedTemp),
	mBetaTwoJ(m_TWO_J/rReducedTemp), // 2 * beta * J, where beta == 1 / (k * T)
	mProb(new double[7]),
	mrEnergyBin(*(new CStat())),
	mrMagnetizationBin(*(new CStat()))
{
	// Probablilities of acceptance of proposed MC steps,
	// depending on the change of enegergy delta_e
	for(int i = 0; i <= 6; ++i){
		// The relation between the index of the array and delta_e is:
		// index i == delta_e / 2 + 3
		
		mProb[i] = exp(-mBetaTwoJ * (double)(2 * i - 6));
	}
}


//IsingSimulation::~IsingSimulation()
//{
//}

void IsingSimulation::run(const int &rMcSteps){
	// MAIN LOOP of the simulation
	for (int step=0; step < rMcSteps; ++step) {
		
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
		
		// Sample energy and magnetization
		mrEnergyBin.add(mrGrid.get_energy());
		mrMagnetizationBin.add(mrGrid.get_magnetization());
		
	} // END of MAIN LOOP of the simulation
}
