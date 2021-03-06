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
                unsigned long size() const {return M;}; 
                double sum() const {return sum_value;};
                double squareSum() const {return squareSum_value;};
                double variance() const {return variance_value;};
                double error() const {return error_value;};
                double mean() const {return mean_value;};
                double standard_deviation() const {return sqrt(variance_value);};

                void add(double a);  // adding a measurement value
                void clear();
		
		// output of the error depending on binning levels
		void binning_error(std::ostream &out=std::cout, std::ostream &out2 = std::cerr, int level=0) const;
		void binning_error(const char *name, int level=0) const;
		
		const CStat* get_max_variance_level() const;

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
