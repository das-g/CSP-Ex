#!/usr/bin/env python

import pylab as pl

data_sf = pl.load("./binning_single_flip.dat", delimiter='\t')
data_w = pl.load("./binning_wolff.dat", delimiter='\t')

pl.plot(data_sf[:,0], data_sf[:,1], '.-', label="single flip")
pl.plot(data_w[:,0], data_w[:,1], '.-', label="Wolff")
pl.xlabel("binning level")
pl.ylabel("energy error")
pl.legend(loc='best')

pl.savefig("./binning_analysis.png")
