//
// C++ Implementation: binning_analysis
//
// Description: Run a simulation for both single flip and Wolff, both at T_C
//
//
// Author: Raphael Das Gupta <raphaeld@ethz.ch>, (C) 2009
//
// Copyright: All rites reversed -- copy what you like.
//
//
#include <fstream> // for output of results
#include "./IsingSimulation.h"
#include "./WolffIsingSimulation.h"

int main(){
	// single flip
	// ===========
	
	// open output file:
	std::ofstream binning_file_sf("./binning_single_flip.dat");
	
	// run simulation
	IsingSimulation sim_sf(10, 4.51);
	sim_sf.termalize(1000000);
	sim_sf.run(100000000);
	sim_sf.get_total_energy_bin().binning_error(binning_file_sf);
	
	//close output file:
	binning_file_sf.close();
	
	// Wolff
	// =====
	
	// open output file:
	std::ofstream binning_file_w("./binning_wolff.dat");
	
	// run simulation
	WolffIsingSimulation sim_w(10, 4.51);
	sim_w.termalize(10000);
	sim_w.run(1000000);
	sim_w.get_total_energy_bin().binning_error(binning_file_w);
	
	//close output file:
	binning_file_w.close();
}
