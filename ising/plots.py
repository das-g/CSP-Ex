#!/usr/bin/env python

import pylab as pl

pl.plotfile("./everything_vs_MaxDeamonEnergy.dat", cols=range(3), delimiter='\t')
pl.savefig("everything_vs_MaxDeamonEnergy.png")

pl.plotfile("./everything_vs_system_size.dat", cols=range(3), plotfuncs={}, delimiter='\t')
pl.savefig("everything_vs_system_size.png")
