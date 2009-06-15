#include <fstream> // for output of results
#include "./IsingSimulation.h"


void do_simulation(const double &kT, const int &N, std::ostream &output_stream){
	
	IsingSimulation sim(N,kT);
	
	//srandom(1); //optionally seed the random generator
	const int MC_STEPS = 1000000; // Number of Monte Carlo steps
	
	sim.run(MC_STEPS);
	
	output_stream
		<< sim.get_mean_energy() << '\t'
		<< sim.get_mean_magnetization() << '\t'
		<< sim.get_susceptibility_estimation() << '\t' // susceptibility \xi
		<< sim.get_specific_heat_estimation() << std::endl;  // specific heat C_V
	//energy_bin.binning_error();
	//magnetization_bin.binning_error();
	
	return;
}

int main(){
	// open output file:
	std::ofstream everything_vs_kT_file("./everything_vs_kT.dat");
	// write title row:
	everything_vs_kT_file << "kT\tenergy\tmagnetization\tsusceptibility\tspecific_heat" << std::endl;
	
	// run simulation and write data rows
	for(double kT = 0.1; kT <= 20.; kT += 0.3){
		everything_vs_kT_file << kT << '\t';
		do_simulation(kT, 10, everything_vs_kT_file);
	}
	//close output file:
	everything_vs_kT_file.close();
	
	// open output file:
	std::ofstream everything_vs_system_size_file("./everything_vs_system_size.dat");
	// write title row:
	everything_vs_system_size_file << "system_size\tenergy\tmagnetization\tsusceptibility\tspecific_heat" << std::endl;
	
	// run simulation and write data rows
	for(int N = 5; N <= 15; ++N){
		everything_vs_system_size_file << N * N * N << '\t';
		do_simulation(4., N, everything_vs_system_size_file);
	}
	//close output file:
	everything_vs_system_size_file.close();
}
