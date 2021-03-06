#!/usr/bin/env python

import pylab as pl

pl.plotfile("./everything_vs_kT.dat", cols=range(5), delimiter='\t')
pl.savefig("everything_vs_kT.png")

pl.plotfile("./everything_vs_system_size.dat", cols=range(5), plotfuncs={2:'plot',3:'semilogy'}, delimiter='\t')
pl.savefig("everything_vs_system_size.png")
