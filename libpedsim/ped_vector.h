//
// Copyright (c) 2010 by Christian Gloor
//                              

#ifndef _ped_vector_h_ 
#define _ped_vector_h_ 1

class Tvector {
 public:
	double x;
	double y;
	double z;
	void cross(Tvector *a, Tvector *b);
	double scalar(Tvector *a, Tvector *b);
	void normalize();
};


#endif
