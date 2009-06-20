#!/usr/bin/env python

import pylab as pl

pl.plotfile("./max_chi_vs_N.dat", cols=range(3), delimiter='\t')
pl.savefig("max_chi_vs_N.png")