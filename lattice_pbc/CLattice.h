/*
You can change or do whatever with this code as you like to make it better or adjust it to your taste.
This is a very simple class intended to handle a 3d array easier. Using standard arrays of C++ appears to be cumbersome sometimes. 

This class makes the life easier in the following respects:
 1. Through this you can pass a 3d-array to a function easily.
 2. You can specify the the dimenstions of the array at run-time. This is good because you will not need to recompile your code if you want to run your simulation with a different size.
 3. The periodic boundary condition is implemented, that is, the neighbour of the last element is the first and vice versa.

USAGE:
To create an object of this class use:
        CLattice<double> yourlattice(N) for a lattice of size N x 1 x 1 (1d lattice)
        CLattice<double> yourlattice(Nx,Ny) for a lattice of size Nx x Ny x 1 (2d lattice)
        CLattice<double> yourlattice(Nx,Ny,Nz) for a lattice of size Nx x Ny x Nz
        You can change double to whatever type or class you want. You may then have to define the operator + in order to sum() works.
        
        To access the element (i,j,k)
        yourlattice(i,j,k)=value
        value=yourlattice(i,j,k)

There are few methods for this class. You are welcome to add your own methods to add more functionality to the class. The methods are:
        Nx(): returns the x-dimension
        Ny(): returns the y-dimension
        Nz(): returns the z-dimension

        size(): returns the total number of elements, i.e., Nx*Ny*Nz

        sum(): returns the sum of all the elements
*/

#ifndef CLATTICE_H
#define CLATTICE_H
#include<iostream>

//This function takes care of periodic boundary condition
inline int indexing(int i, int N){
        if(i>=N)return i%N;
        if(i<0)return i%N+N;
        return i;
}

//A class containing a 3d array
template <class T>
class CLattice {
        public:
                ~CLattice();
                CLattice(){site=NULL;};
                CLattice(int m, int n=1, int o=1);
                
                T& operator() (int i, int j, int k);
                T sum();

                int Nx(){return lx;}
                int Ny(){return ly;}
                int Nz(){return lz;}
                int size(){return lz*ly*lx;}

        private:
                int lx,ly,lz;
                T ***site;
};

template <class T> CLattice<T>::CLattice(int nx, int ny, int nz){
        lx=nx;
        ly=ny;
        lz=nz;

        // Constructing the array by allocating memory dynamically
        site= new T **[lx];
        for( int i = 0; i < lx; i++ )
                site[i] = new T *[ly];
        for( int i = 0; i < lx; i++ )
        for( int j = 0; j < ly; j++ )
                site[i][j] = new T [lz];
}

template <class T> CLattice<T>::~CLattice(){
        // Deleting all the memory dynamically allocated
        for( int i = 0; i < lx; i++ )
        for( int j = 0; j < ly; j++ )
                delete [] site[i][j];
        for( int i = 0; i < lx; i++ )
                delete [] site[i];
        delete(site);
}

//Returns the values with (i,j,k) indices 
template <class T> T& CLattice<T>::operator() (int i, int j, int k){
        int ii=indexing(i,lx);
        int jj=indexing(j,ly);
        int kk=indexing(k,lz);

        return site[ii][jj][kk];
}

//Return the sum of all the values. Perhaps it is useful...
template <class T> T CLattice<T>::sum(){
        T s=(T)(0);

        for( int i = 0; i < lx; i++ )
        for( int j = 0; j < ly; j++ )
        for( int k = 0; k < lz; k++ )
                s+=site[i][j][k];
return s;
}
#endif
