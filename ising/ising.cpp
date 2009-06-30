#include <fstream> // for output of results
#include "./IsingSimulation.h"
#include "../tools/string.h" // for conversion of streamable types to string


void do_simulation(const double &rSystemEnergy, const double &rMaxDeamonEnergy, const int &rL, std::ostream &rOutputStream, std::ostream &rDeamonEnergyOutputStream){
	
	IsingSimulation sim(rL,rMaxDeamonEnergy);
	
	//srandom(1); //optionally seed the random generator
	const int MC_MEASUREMENTS = 10000; // Number of wanted decorrelated measurements
	
	sim.heat_up_to(rSystemEnergy);
	sim.run(MC_MEASUREMENTS, rDeamonEnergyOutputStream);
	
	rOutputStream
		<< sim.get_mean_energy() << '\t'
		<< sim.get_mean_magnetization() << '\t'
		<< std::endl;
	//energy_bin.binning_error();
	//magnetization_bin.binning_error();
	
	return;
}

int main(){
	// open output file:
	std::ofstream everything_vs_max_deamon_energy_file("./everything_vs_max_deamon_energy.dat");
	// write title row:
	everything_vs_max_deamon_energy_file << "max_deamon_energy\tenergy\tmagnetization" << std::endl;
	
	// run simulation and write data rows
	for(int max_deamon_energy = 6; max_deamon_energy <= 42; max_deamon_energy+=4){
		// open output file:
		std::ofstream hist_file((char*)("./hist_deamon_" + to_string<int>(max_deamon_energy) + ".dat").c_str());
		everything_vs_max_deamon_energy_file << max_deamon_energy << '\t';
		do_simulation(0.74, max_deamon_energy, 10, everything_vs_max_deamon_energy_file, hist_file);
		hist_file.close();
	}
	//close output file:
	everything_vs_max_deamon_energy_file.close();
	
	// open output file:
	std::ofstream everything_vs_system_energy_file("./everything_vs_system_energy.dat");
	// write title row:
	everything_vs_system_energy_file << "system_energy\tenergy\tmagnetization" << std::endl;
	
	// run simulation and write data rows
	for(double system_energy = 0.1; system_energy <= 1.6; system_energy+=.1){
		// open output file:
		std::ofstream hist_file((char*)("./hist_energy_" + to_string<double>(system_energy,1) + ".dat").c_str());
		everything_vs_system_energy_file << system_energy << '\t';
		do_simulation(system_energy, IsingSimulation::NO_LIMIT, 10, everything_vs_system_energy_file, hist_file);
		hist_file.close();
	}
	//close output file:
	everything_vs_system_energy_file.close();

}
