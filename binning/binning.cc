#include<iostream>
#include<fstream>
#include"CStat.h"
using namespace std;


// example for usage of binning (done by CStat.h) 
int main(){

    CStat A;  // quantity to be measured

    int i=0;
    while(i<=2<<20){  // draw 2^20 numbers (uses bitwise operator left shift: "<<")
	i++;
	A.add(drand48());  // here the values are just uniform random numbers
    }

    std::cerr<<A.mean() << "\t" << A.variance() <<std::endl; // output of values
    A.binning_error(); // output of binning into cout (default)
    //  A.binning_error("test.dat"); // alternatively specify file

    return 0;
}

