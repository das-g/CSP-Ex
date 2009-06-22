/*
The original version of this file was provided at http://www.ifb.ethz.ch/education/statisticalphysics/20090220_lattice.zip

Newer versions might be available from http://www.ifb.ethz.ch/education/statisticalphysics
*/

#include<iostream>
#include<fstream>
#include"CLattice.h"
using namespace std;

int main(){
    
    int pos=0;
    const int N=2;
    CLattice<int> S(N,N,N);
    for (int i=0; i<S.Nx(); i++)  
	for (int j=0; j<S.Ny(); j++)  
	    for (int k=0; k<S.Nz(); k++) {
		S(i,j,k)=pos++;
		cerr << i << "\t"  << j << "\t"  << k << "\t"  << S(i,j,k) << "\n";
	    }
    
    
return 0;
}

