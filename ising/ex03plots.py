#!/usr/bin/env python
from __future__ import division
import pylab as pl

pl.plotfile("./max_chi_vs_N.dat", cols=range(3), delimiter='\t')
pl.savefig("./max_chi_vs_N.png")

## Data collaps
pl.figure()
tmp_data = pl.csv2rec("./max_chi_vs_N.dat", delimiter='\t')
gamma_over_nu_estimation = pl.mean(tmp_data['max_chi'] / tmp_data['system_size'])
del tmp_data

data = pl.csv2rec("./data_collapse.dat", delimiter='\t')
kT = data['kt']
T_C = 4.51
N = data['system_size']
chi = data['susceptibility']

gamma = 1.24
nu = 0.63

gamma_over_nu = gamma / nu

for one_over_nu in (-0.595, 0.0, 0.75, 1./nu):
	pl.figure()
	pl.loglog(abs(kT - T_C) * (N ** one_over_nu), chi * (N ** (-gamma_over_nu)), '.')
	pl.savefig("./data_collapse" + one_over_nu.__str__() + ".png")
