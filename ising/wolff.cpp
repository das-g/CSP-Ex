#include <fstream> // for output of results
#include "./WolffIsingSimulation.h"


void do_simulation(const double &r_kT, const int &rL, std::ostream &output_stream){
	
	WolffIsingSimulation sim(rL,r_kT);
	
	//srandom(1); //optionally seed the random generator
	const int MC_STEPS = (int)(4.78401 * (pow((double)rL, 3.32) + 1.)); // Number of Monte Carlo steps
	
	sim.termalize(MC_STEPS/10);
	sim.run(MC_STEPS);
	
	output_stream
		<< sim.get_mean_energy() << '\t'
		<< sim.get_mean_magnetization() << '\t'
		<< sim.get_susceptibility_estimation() << '\t' // susceptibility chi
		<< sim.get_specific_heat_estimation() << std::endl;  // specific heat C_V
	//sim.get_total_energy_bin().binning_error();
	//sim.get_total_magnetization_bin().binning_error();
	
	return;
}

int main(){
	
	// open output file:
	std::ofstream everything_vs_kT_file("./everything_vs_kT_wolff.dat");
	// write title row:
	everything_vs_kT_file << "kT\tenergy\tmagnetization\tsusceptibility\tspecific_heat" << std::endl;
	
	// run simulation and write data rows
	for(double kT = 0.1; kT <= 10.; kT += 0.3){
		everything_vs_kT_file << kT << '\t';
		do_simulation(kT, 10, everything_vs_kT_file);
	}
	//close output file:
	everything_vs_kT_file.close();
	
	// open output file:
	std::ofstream everything_vs_system_size_file("./everything_vs_system_size_wolff.dat");
	// write title row:
	everything_vs_system_size_file << "system_size\tenergy\tmagnetization\tsusceptibility\tspecific_heat" << std::endl;
	
	// run simulation and write data rows
	for(int L = 5; L <= 15; ++L){
		everything_vs_system_size_file << L * L * L << '\t';
		do_simulation(4., L, everything_vs_system_size_file);
	}
	//close output file:
	everything_vs_system_size_file.close();
}
