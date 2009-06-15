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

/**
	@author Raphael Das Gupta
*/
class IsingSimulation{
public:
	IsingSimulation(const int &rL, const double &rReducedTemp);

	//~IsingSimulation();
	
	void run(const int &rMcSteps);
	
	double get_mean_energy(){
		return mrEnergyBin.mean();
	}
	
	double get_mean_magnetization(){
		return mrMagnetizationBin.mean();
	}
	
	double get_susceptibility_estimation(){
		return mrMagnetizationBin.variance() * mBeta;
	}
	
	double get_specific_heat_estimation(){
		return mrEnergyBin.variance() * mBeta * mBeta;
	}

private:
	IsingLattice& mrGrid;
	const double mBeta; // 1 / (k * T)
	
	// 2-particle interaction energy between nearest neighbours
	static const double m_TWO_J = 2.;
	
	const double mBetaTwoJ; // 2 * beta * J, where beta=1/kT
	
	// Probablilities of acceptance of proposed MC steps,
	// depending on the change of enegergy delta_e
	double * const mProb;
	
	// Aggregators for statistics and binning analysis
	CStat& mrEnergyBin;
	CStat& mrMagnetizationBin;
};

#endif
