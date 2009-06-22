#include <fstream> // for output of results
#include "./IsingSimulation.h"

//const int T_C = 4.51;

double do_simulation(const double &r_kT, const int &rL){
	
	IsingSimulation sim(rL,r_kT);
	
	//srandom(1); //optionally seed the random generator
	const int MC_STEPS = 1000000; // Number of Monte Carlo steps
	
	sim.termalize(MC_STEPS/10);
	sim.run(MC_STEPS);
	
	return sim.get_susceptibility_estimation();
}

int main(){
	// open output file:
	std::ofstream max_chi_file("./max_chi_vs_N.dat");
	// write title row:
	max_chi_file << "system_size\t$T_C_of_L$\tmax_chi" << std::endl;
	
	// run simulation and write data rows
	double max_chi;
	double T_C_of_L;
	double chi;
	for(int L = 5; L <= 15; ++L){
		max_chi = -1.;
		T_C_of_L = -1.;
		for (double kT = 4.; kT <= 5.; kT += 0.05){
			//std::cerr << kT << std::endl;
			chi = do_simulation(kT, L);
			if (chi > max_chi){
				T_C_of_L = kT;
				max_chi = chi;
			}
		}
		max_chi_file << L * L * L << '\t' << T_C_of_L << '\t' << max_chi << std::endl;
	}
	//close output file:
	max_chi_file.close();
}
