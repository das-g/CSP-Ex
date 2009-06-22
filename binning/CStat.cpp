//
// C++ Implementation: CStat
//
// Description: 
//
//
// Split off by: Raphael Das Gupta <raphaeld@ethz.ch>, 2009
//
// Copyright: This file was split off from binning/CStat.h, see there for origin
//
//

#include "./CStat.h"

CStat::~CStat(){  // Destructor
        // Deleting all the memory dynamically allocated
	clear();
}

void CStat::delete_child(CStat *c){
	if(c!=NULL){
		delete c;
	}
	return;
}
void CStat::clear(){
	M=0;
	A1=0;A2=0;
	sum_value=0.0;
	error_value=0.0;
	squareSum_value=0.0;
	variance_value=0.0;
	mean_value=0.0;

	make_bin=0;
	delete_child(child);
	child=NULL;
}


void CStat::add(double a){
	M++;
	A1=A2; A2=a;
	sum_value+=a;
	squareSum_value+=a*a;
	mean_value=sum_value/(double)(M);
	variance_value=(squareSum_value-(double)(M)*mean_value*mean_value)/(double)(M-1);
	error_value=sqrt(variance_value/(double)(M));


	if(child==NULL){child=new CStat;};
        
	//make_bin is used to add every other entries to the child 
	if(make_bin){
		child->add(0.5*(A1+A2));
		make_bin=0;
	}
	else    make_bin=1;
            
	return;
}

//printing out the errors from all levels
void CStat::binning_error(const char *name, int level){
	std::ofstream out(name);
	binning_error(out, level);
	return ;
}
void CStat::binning_error(std::ostream &out, int level){
        
	out<<level<<"   "<<error()<<std::endl;
	std::cerr<< "Number samples of Level "<<level<<": "<<M <<std::endl;  // output of number of values in each level to std::err (to check)
	if(child==NULL || M<10) return;  // use binning level only if enough values M (can be changed)
	child->binning_error(out,level+1);
	return;
}
