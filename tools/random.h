#include <cstdlib> // for random()

inline double drand(){
	return (double)random() / (double)(RAND_MAX+1);
}

inline unsigned int uirand(unsigned int max_plus_one){
	return ((unsigned int)random() * max_plus_one) / ((unsigned int)RAND_MAX + 1u);
}
