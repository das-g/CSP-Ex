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
	IsingSimulation(const int &rL, const int &rMaxDeamonEnergy);

	//~IsingSimulation();
	
	void run(const int &rMcMeasurements);
	
	double get_mean_energy(){
		return mrTotalEnergyBin.mean() / get_system_size();
	}
	
	double get_mean_magnetization(){
		return mrTotalMagnetizationBin.mean() / get_system_size();
	}
	
/*
	double get_susceptibility_estimation(){
		return mrTotalMagnetizationBin.variance() * mBeta / get_system_size();
	}
	
	double get_specific_heat_estimation(){
		return mrTotalEnergyBin.variance() * mBeta * mBeta / get_system_size();
	}
*/
	
	void heat_up_to(double wanted_energy){
		int total_wanted_energy = wanted_energy * get_system_size();
		while(mrGrid.get_total_energy() < total_wanted_energy){
			// choose a random site
			int x = uirand(mrGrid.Nx());
			int y = uirand(mrGrid.Ny());
			int z = uirand(mrGrid.Nz());
			
			// flip
			mrGrid.flip(x,y,z);
		}
	}
	
	int get_system_size(){
		return mrGrid.size();
	}

private:
	void do_step(){		
		// choose a random site
		int x = uirand(mrGrid.Nx());
		int y = uirand(mrGrid.Ny());
		int z = uirand(mrGrid.Nz()); 
		
		// Calculate energy change (divided by 2*J)
		int delta_e = mrGrid.flip_energy(x,y,z);
		
		// flip (or not)
		// using Creutz algorithm
		int new_deamon_energy = mDeamonEnergy + delta_e;
		if ((new_deamon_energy  >= 0.) && (new_deamon_energy <= mMaxDeamonEnergy)){
			mrGrid.flip(x,y,z);
			mDeamonEnergy = new_deamon_energy;
		}
	}
	
	IsingLattice& mrGrid;
	
	const int mStepsPerMeasurement;
	
	// Creutz deamon
	int mDeamonEnergy;
	int mMaxDeamonEnergy;
	
	// Aggregators for statistics and binning analysis
	CStat& mrTotalEnergyBin;
	CStat& mrTotalMagnetizationBin;
};

#endif
