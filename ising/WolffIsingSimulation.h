//
// C++ Interface: WolffIsingSimulation
//
// Description:  Holds the paramemeters for one simulation,
//              gives the option to run it and to query
//              the results.
//
//
// Author: Raphael Das Gupta <raphaeld@ethz.ch>, (C) 2009
//
// Copyright: All rites reversed -- copy what you like.
//
//
#ifndef WOLFFISINGSIMULATION_H
#define WOLFFISINGSIMULATION_H

#include "./IsingSimulation.h" // base class

/**
	@author Raphael Das Gupta
*/
class WolffIsingSimulation : public IsingSimulation
{
public:
	WolffIsingSimulation(const int &rL, const double &rReducedTemp);
	
	/* override */
	~WolffIsingSimulation();
	
private:
	/* override */
	void do_step();
};

#endif //WOLFFISINGSIMULATION_H
