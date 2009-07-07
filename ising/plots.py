#!/usr/bin/env python

import sys
import pylab as pl

for versus in ["kT","system_size"]:
	
	pl.figure()
	
	sf_data = pl.csv2rec("./everything_vs_" + versus + "_single_flip.dat", delimiter='\t')
	wolff_data = pl.csv2rec("./everything_vs_" + versus + "_wolff.dat", delimiter='\t')
	
	if not all(sf_data[versus.lower()] == wolff_data[versus.lower()]):
		sys.sys.stderr.write('WARNING: plotting data for different input values')
	
	## Energies
	pl.subplot(221)
	pl.plot(sf_data[versus.lower()], sf_data["energy"], label="single flip")
	pl.plot(wolff_data[versus.lower()], wolff_data["energy"], label="Wolff")
	pl.ylabel("Energy")
	pl.xlabel(versus)
	
	## Magn.
	pl.subplot(222)
	pl.plot(sf_data[versus.lower()], sf_data["magnetization"], label="single flip")
	pl.plot(wolff_data[versus.lower()], wolff_data["magnetization"], label="Wolff")
	pl.ylabel("Magn.")
	pl.xlabel(versus)
	
	## Susc. (chi)
	pl.subplot(223)
	pl.plot(sf_data[versus.lower()], sf_data["susceptibility"], label="single flip")
	pl.plot(wolff_data[versus.lower()], wolff_data["susceptibility"], label="Wolff")
	pl.ylabel("Susc. $\chi$")
	pl.xlabel(versus)
	
	## C_V
	pl.subplot(224)
	pl.plot(sf_data[versus.lower()], sf_data["specific_heat"], label="single flip")
	pl.plot(wolff_data[versus.lower()], wolff_data["specific_heat"], label="Wolff")
	pl.ylabel("spec. heat $C_V$")
	pl.xlabel(versus)
	pl.legend()
	
	pl.subplots_adjust(wspace=0.35)
	pl.savefig("everything_vs_" + versus + ".png")

## END OF for versus
