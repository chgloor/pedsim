//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#ifndef _ped_waypoint_h_
#define _ped_waypoint_h_ 1

#ifdef WIN32
#define LIBEXPORT __declspec(dllexport)
#else
#define LIBEXPORT
#endif

#include "ped_vector.h"

#include <iostream>


using namespace std;

namespace Ped {
	
	/// The waypoint classs
	/// \author  chgloor
	/// \date    2012-01-07
	class LIBEXPORT Twaypoint {
	private:
		int id;                                           ///< waypoint number
		double x;                                         ///< position of the waypoint 
		double y;                                         ///< position of the waypoint 
		double r;                                         ///< position of the waypoint 
		int type;                                         
		
	public:
		Twaypoint();
		Twaypoint(double x, double y, double r);

		virtual Tvector getForce(double myx, double myy, double fromx, double fromy, bool *reached);
		virtual Tvector normalpoint(double p1, double p2, double oc11, double oc12, double oc21, double oc22);

		void setType(int t) {type = t; };      
		int getid() { return id; };            
		int gettype() { return type; };        
		double getx() { return x; };           
		double gety() { return y; };           
		double getr() { return r; };           
		void setx(double px) { x = px; };      
		void sety(double py) { y = py; };      
		void setr(double pr) { r = pr; };      
		void settype(int t) { type = t; };                       		
	};
	
	/// A container for the waypoints. Defined here because some methods inside the Twaypoint class iterate over this container
#define WaypointContainer vector<Twaypoint*>
	
	/// A container iterator for the waypoints. Defined here because some methods inside the Twaypoint class iterate over this container
#define WaypointIterator vector<Twaypoint*>::iterator
	
	
}

#endif
