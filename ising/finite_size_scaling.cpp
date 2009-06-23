#include <fstream> // for output of results
#include "./IsingSimulation.h"
#include "../tools/random.h"

//const int T_C = 4.51;

double do_simulation(const double &r_kT, const int &rL, std::ostream &output_stream){
	
	IsingSimulation sim(rL,r_kT);
	
	//srandom(1); //optionally seed the random generator
	const int MC_STEPS = 1000000; // Number of Monte Carlo steps
	
	sim.termalize(MC_STEPS/10);
	sim.run(MC_STEPS);
	
	output_stream
		<< sim.get_system_size() << '\t'
		<< r_kT << '\t'
		<< sim.get_mean_energy() << '\t'
		<< sim.get_mean_magnetization() << '\t'
		<< sim.get_susceptibility_estimation() << '\t' // susceptibility chi
		<< sim.get_specific_heat_estimation() << std::endl;  // specific heat C_V
	
	return sim.get_susceptibility_estimation();
}

int main(){
	// open output files:
	std::ofstream max_chi_file("./max_chi_vs_N.dat");
	std::ofstream data_collapse_file("./data_collapse.dat");
	
	// write title rows:
	max_chi_file << "system_size\t$T_C_of_L$\tmax_chi" << std::endl;
	data_collapse_file << "system_size\tkT\tenergy\tmagnetization\tsusceptibility\tspecific_heat" << std::endl;
	
	// run simulation and write data rows
	double max_chi;
	double T_C_of_L;
	double chi;
	for(int L = 5; L <= 15; ++L){
		max_chi = -1.;
		T_C_of_L = -1.;
		for (double kT = 3.6; kT <= 5.; kT += 0.05){
			//std::cerr << kT << std::endl;
			chi = do_simulation(kT, L, data_collapse_file);
			if (chi > max_chi){
				T_C_of_L = kT;
				max_chi = chi;
			}
		}
		max_chi_file << L * L * L << '\t' << T_C_of_L << '\t' << max_chi << std::endl;
	}
	
	// more samples for data collapse
	for(int i = 1; i <= 200; ++i){
		do_simulation(0. + drand() * 8., 3 + uirand(17), data_collapse_file);
	}
	
	//close output files:
	max_chi_file.close();
	data_collapse_file.close();
}
