//
// C++ Interface: IsingSimulation
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
#ifndef ISINGSIMULATION_H
#define ISINGSIMULATION_H

#include "./IsingLattice.hpp" // simple wrapper class for CLattice
#include "../binning/CStat.h" // for statistics and binning analysis
#include "../tools/random.h" //for drand() and uirand()

/**
	@author Raphael Das Gupta
*/
class IsingSimulation{
public:
	IsingSimulation(const int &rL, const double &rReducedTemp);

	virtual ~IsingSimulation();
	
	void run(const int &rMcMeasurements);
	
	double get_mean_energy(){
		return mrTotalEnergyBin.mean() / get_system_size();
	}
	
	double get_mean_magnetization(){
		return mrTotalMagnetizationBin.mean() / get_system_size();
	}
	
	double get_susceptibility_estimation(){
		return mrTotalMagnetizationBin.variance() * mBeta / get_system_size();
	}
	
	double get_specific_heat_estimation(){
		return mrTotalEnergyBin.variance() * mBeta * mBeta / get_system_size();
	}

	void termalize(const int &rMcSteps){
		for (int step=0; step < rMcSteps; ++step) {
			do_step();
		}
	}
	
	int get_system_size(){
		return mrGrid.size();
	}

protected:
	IsingLattice& mrGrid;
	const double mBeta; // 1 / (k * T)
	
	// 2-particle interaction energy between nearest neighbours
	static const double m_TWO_J = 2.;
	
	const double mBetaTwoJ; // 2 * beta * J, where beta=1/kT
	
	const int mStepsPerMeasurement;
	
	// Probablilities of acceptance of proposed MC steps,
	// depending on the change of enegergy delta_e
	double * const mProb;

private:
	virtual void do_step(){
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
	
	// Aggregators for statistics and binning analysis
	CStat& mrTotalEnergyBin;
	CStat& mrTotalMagnetizationBin;
};

#endif
