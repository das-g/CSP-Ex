#include <cstdlib> // for random()

inline double drand(){
	return (double)random() / (double)((unsigned int)RAND_MAX + 1u);
}

inline unsigned int uirand(unsigned int max_plus_one){
	return ((unsigned long long int)random() * (unsigned long long int)max_plus_one) / ((unsigned int)RAND_MAX + 1u);
}
