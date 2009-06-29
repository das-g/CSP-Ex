#!/usr/bin/env python
import os
import pylab as pl

## files that contain "hist_"
data_files = [f for f in os.listdir(os.path.curdir) if "hist_" in f]

for data_file in data_files:
	pl.figure()
	data = pl.load(data_file)
	absolute_frequency, deamon_energy, dummy = pl.hist(data, log=True)
	pl.savefig(data_file + ".png")

#pl.plotfile("./everything_vs_MaxDeamonEnergy.dat", cols=range(3), delimiter='\t')
#pl.savefig("everything_vs_MaxDeamonEnergy.png")

#pl.plotfile("./everything_vs_system_size.dat", cols=range(3), plotfuncs={}, delimiter='\t')
#pl.savefig("everything_vs_system_size.png")
