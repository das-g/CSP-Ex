//
// Utility header providing some wrapper functions.
//
// Description: Wrapper functions for cstdlib's random().
//              random() only provides long int pseudo
//              random numbers between 0 and RAND_MAX
//              (inclusive). The wrapper functions here
//              provide doubles between 0.0 and 1.0, as
//              well as unsigned ints between 0 and a given
//              parameter (upper bounds exclusive).
//
//
// Author: Raphael Das Gupta <raphaeld@ethz.ch>, (C) 2009
//
// Copyright: All rites reversed -- copy what you like.
//
//
#ifndef TOOLS_RANDOM_H
#define TOOLS_RANDOM_H

#include <cstdlib> // for random()

inline double drand(){
	return (double)random() / (double)((unsigned int)RAND_MAX + 1u);
}

inline unsigned int uirand(unsigned int max_plus_one){
	return ((unsigned long long int)random() * (unsigned long long int)max_plus_one) / ((unsigned int)RAND_MAX + 1u);
}

#endif // TOOLS_RANDOM_H
