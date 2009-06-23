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

#include "./IsingSimulation.h"

IsingSimulation::IsingSimulation(const int &rL, const double &rReducedTemp)
	:
	mrGrid(*(new IsingLattice(rL))),
	mBeta(1./rReducedTemp),
	mBetaTwoJ(m_TWO_J/rReducedTemp), // 2 * beta * J, where beta == 1 / (k * T)
	mProb(new double[7]),
	mrTotalEnergyBin(*(new CStat())),
	mrTotalMagnetizationBin(*(new CStat()))
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
		
		do_step();
		
		// Sample energy and magnetization
		mrTotalEnergyBin.add(mrGrid.get_total_energy());
		mrTotalMagnetizationBin.add(mrGrid.get_total_magnetization());
		
	} // END of MAIN LOOP of the simulation
}
