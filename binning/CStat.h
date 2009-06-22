/*
The original version of this file was provided at http://www.ifb.ethz.ch/education/statisticalphysics/20090220_binning.zip

Newer versions might be available from http://www.ifb.ethz.ch/education/statisticalphysics
*/

#ifndef CSTAT_H
#define CSTAT_H

#include<iostream>
#include<fstream>
#include<math.h>


class CStat {
        public:
                ~CStat();
                CStat(){                // constructor
			child=NULL;
			clear();
			};
                // memberfunctoins for output of following values
                unsigned long size(){return M;}; 
                double sum(){return sum_value;};
                double squareSum(){return squareSum_value;};
                double variance(){return variance_value;};
                double error(){return error_value;};
                double mean(){return mean_value;};
                double standard_deviation(){return sqrt(variance_value);};

                void add(double a);  // adding a measurement value
                void clear();
		
		// output of the error depending on binning levels
                void binning_error(std::ostream &out=std::cout, int level=0);
		void binning_error(const char *name, int level=0);

        private:
                unsigned long M;    // totel number of measurements
                double sum_value, squareSum_value;
                double mean_value, variance_value, error_value;
                double A1, A2;     // previous and current measurement value
                void delete_child(CStat *c);
                bool make_bin;
                CStat *child;  // for child processes
};

#endif // CSTAT_H
