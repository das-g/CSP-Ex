#!/usr/bin/env python

from __future__ import division

import pylab as pl

stat_data = pl.csv2rec("./everything_vs_MaxDeamonEnergy.dat", delimiter='\t')
max_deamon_energies = stat_data["maxdeamonenergy"]

data_files = ["./hist_" + max_deamon_energy.__str__() + ".dat" for max_deamon_energy in max_deamon_energies]

for data_file in data_files:
	pl.figure()
	data = pl.load(data_file)
	number_of_bins = (data.max() - data.min()) / 2 ## data is only even integers, and we don't want gaps in the histogram
	pdf, bins, patches = pl.hist(data, log=True, normed=True, bins=number_of_bins)
	pl.savefig(data_file + ".png")

#pl.plotfile("./everything_vs_MaxDeamonEnergy.dat", cols=range(3), delimiter='\t')
#pl.savefig("everything_vs_MaxDeamonEnergy.png")

#pl.plotfile("./everything_vs_system_size.dat", cols=range(3), plotfuncs={}, delimiter='\t')
#pl.savefig("everything_vs_system_size.png")
