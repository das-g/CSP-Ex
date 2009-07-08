#!/usr/bin/env python

import pylab as pl

data_sf = pl.load("./binning_single_flip.dat", delimiter='\t')
data_w = pl.load("./binning_wolff.dat", delimiter='\t')

pl.plot(data_sf[:,0], data_sf[:,1])
pl.plot(data_w[:,0], data_w[:,1])

pl.savefig("./binning_analysis.png")
