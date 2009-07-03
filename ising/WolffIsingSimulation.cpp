//
// C++ Implementation: WolffIsingSimulation
//
// Description: Holds the paramemeters for one simulation,
//              gives the option to run it and to query
//              the results.
//
//
// Author: Raphael Das Gupta <raphaeld@ethz.ch>, (C) 2009
//
// Copyright: All rites reversed -- copy what you like.
//
//
#include "WolffIsingSimulation.h"

WolffIsingSimulation::WolffIsingSimulation(const int &rL, const double &rReducedTemp)
	: IsingSimulation(rL,rReducedTemp)
{
}

/* override */
WolffIsingSimulation::~WolffIsingSimulation()
{
	//empty
}


