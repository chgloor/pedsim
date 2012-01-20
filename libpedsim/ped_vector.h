//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#ifndef _ped_vector_h_ 
#define _ped_vector_h_ 1

#ifdef WIN32
#define LIBEXPORT __declspec(dllexport)
#else
#define LIBEXPORT
#endif

namespace Ped {
	
	/// Vector helper class. This is basically a struct with some related functions attached.
	/// \author  chgloor
	/// \date    2010-02-12
	class LIBEXPORT Tvector {
	public:
		Tvector();
		
		double x;
		double y;
		double z;
		void cross(Tvector *a, Tvector *b);
		double scalar(Tvector *a, Tvector *b);
		void normalize();
	};

}


#endif
