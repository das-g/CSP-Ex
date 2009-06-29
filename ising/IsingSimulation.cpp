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

IsingSimulation::IsingSimulation(const int &rL, const int &rMaxDeamonEnergy)
	:
	mrGrid(*(new IsingLattice(rL))),
	mDeamonEnergy(0.),
	mMaxDeamonEnergy(rMaxDeamonEnergy),
	mrTotalEnergyBin(*(new CStat())),
	mrTotalMagnetizationBin(*(new CStat())),
	mStepsPerMeasurement((int)(3. * (pow((double)rL, 3.32) + 1.)))
{
	// empty
}


//IsingSimulation::~IsingSimulation()
//{
//}

void IsingSimulation::run(const int &rMcMeasurements, std::ostream &output_stream){
	// MAIN LOOP of the simulation
	for (int measurement=0; measurement < rMcMeasurements; ++measurement) {
		for (int step=0; step < mStepsPerMeasurement; ++step) {
			do_step();
		}
		
		// Sample energy and magnetization
		mrTotalEnergyBin.add(mrGrid.get_total_energy());
		mrTotalMagnetizationBin.add(mrGrid.get_total_magnetization());
		output_stream << mDeamonEnergy << std::endl;
		
	} // END of MAIN LOOP of the simulation
}
