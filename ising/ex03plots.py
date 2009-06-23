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

gamma_over_nu = gamma_over_nu_estimation
print gamma_over_nu
for i in range(40):
	pl.figure()
	one_over_nu = (i / 20 - 1.) * 0.7
	pl.loglog(abs(kT - T_C) * (N ** one_over_nu), chi * (N ** (-gamma_over_nu)), '.')
	pl.savefig("./data_collapse" +i.__str__()+"__"+ one_over_nu.__str__() + ".png")
