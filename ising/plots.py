#!/usr/bin/env python

from __future__ import division

import pylab as pl

stat_data = pl.csv2rec("./everything_vs_max_deamon_energy.dat", delimiter='\t')
max_deamon_energies = stat_data["max_deamon_energy"]

data_files = ["./hist_deamon_" + max_deamon_energy.__str__() + ".dat" for max_deamon_energy in max_deamon_energies]

for data_file in data_files:
	pl.figure()
	data = pl.load(data_file)
	## Data is only even integers, and we don't want gaps in the histogram.
	## Devide by 4 instead of 2 to have 2 values per bin (for smoothing).
	number_of_bins = (data.max() - data.min()) / 4
	pdf, bins, patches = pl.hist(data, log=True, normed=True, bins=number_of_bins)
	pl.savefig(data_file + ".png")

stat_data = pl.csv2rec("./everything_vs_system_energy.dat", delimiter='\t')
system_energies = stat_data["system_energy"] ## set values
magnetizations = stat_data["magnetization"]
data_files = ["./hist_energy_" + system_energy.__str__() + ".dat" for system_energy in system_energies]
system_energies = stat_data["energy"] ## overwrite with mean measured values

betas = pl.ndarray(stat_data["system_energy"].shape)
i = 0

for data_file in data_files:
	pl.figure()
	data = pl.load(data_file)
	## Data is only even integers, and we don't want gaps in the histogram.
	## Devide by 4 instead of 2 to have 2 values per bin (for smoothing).
	number_of_bins = (data.max() - data.min()) / 4
	pdf, bins, patches = pl.hist(data, log=True, normed=True, bins=number_of_bins)
	pl.savefig(data_file + ".png")
	
	## We still have to take the log() of the probability density function,
	## here, as log=True in hist() only affects the rendering, not the return values.
	## 
	## Take the second but last entry of bins, because we want the lower border of the last bin.
	## 
	## The multiplication by 2 is because all energies are in 2J units.
	## (For this calculation, we want it in J)
	betas[i] = - (pl.log(pdf[-1]) - pl.log(pdf[0])) / ((bins[-2] - bins[0]) * 2)
	i += 1

pl.figure()
pl.plot(1 / betas, system_energies, 'r')
pl.plot(1 / betas, magnetizations, 'b')
pl.xlabel("$k_B\cdot T$")
pl.ylabel("$E_\mathrm{system}$ (red) and Magnetization (blue), both normalized")
pl.savefig("everything_vs_kT.png")

## same, but skipping the probably bogus measurements
pl.figure()
pl.plot(1 / betas[:-2], system_energies[:-2], 'r')
pl.plot(1 / betas[:-2], magnetizations[:-2], 'b')
pl.xlabel("$k_B\cdot T$")
pl.ylabel("$E_\mathrm{system}$ (red) and Magnetization (blue), both normalized")
pl.savefig("everything_vs_kT_2.png")
