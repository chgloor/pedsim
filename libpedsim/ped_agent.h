//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#ifndef _ped_agent_h_
#define _ped_agent_h_ 1

#ifdef WIN32
#define LIBEXPORT __declspec(dllexport)
#else
#define LIBEXPORT
#endif

#include <iostream>
#include <vector>
#include <queue>

#include "ped_waypoint.h"
#include "ped_scene.h"

using namespace std;

namespace Ped {

	class Tscene;

/// \example example.cpp


/// This is the main class of the library. It contains the Tagent, which eventually will move through the
/// Tscene and interact with Tobstacle and other Tagent.  You can use it as it is, and access the agent's 
/// coordinates using the getx() etc methods. Or, if you want to change the way the agent behaves, you can
/// derive a new class from it, and overwrite the methods you want to change. This is also a convenient way
/// to get access to internal variables not available though public methods, like the individual forces that 
/// affect the agent. 
/// \author  chgloor
/// \date    2003-12-26
	class LIBEXPORT Tagent {
	private:
		int id;                                           ///< agent number
		Tvector p;                                        ///< current position of the agent 
		Tvector v;                                        ///< velocity of the agent
		Tvector a;                                        ///< current acceleration of the agent
		int type;                                         
		double vmax;                                      ///< individual max velocity per agent
		int follow;

		Ped::Tscene *scene;
		
		queue<Twaypoint*> destinations;                    ///< coordinates of the next destinations
		Twaypoint *destination;                            ///< coordinates of the next destination
		Twaypoint *lastdestination;                        ///< coordinates of the last destination
		bool hasreacheddestination;                       ///< true if it ahs reached its destination

		bool mlLookAhead;
		
		double factorsocialforce;
		double factorobstacleforce;
		double factordesiredforce;
		double factorlookaheadforce;
		
		Ped::Tvector socialforce;
		Ped::Tvector obstacleforce;
		Ped::Tvector desiredforce;
		Ped::Tvector lookaheadforce;
		Ped::Tvector myforce;

		set<const Ped::Tagent*> neighbors;

		long timestep;

	public:
		Tagent(); 
		virtual ~Tagent();

		virtual void move(double h);                      
		virtual Tvector socialForce();
		virtual Tvector obstacleForce();
		virtual Tvector desiredForce();
		virtual Tvector lookaheadForce(Tvector desired);
		virtual Tvector myForce(Tvector desired);

		virtual void print() const {cout << "agent " << id << ": " << p.x << "/" << p.y << "/" << p.z << endl; }; 
		
		void setPosition(double px, double py, double pz);
		void setType(int t) {this->type = t; };           
		void setFollow(int id);
		void setVmax(double vmax);

		int getFollow() const;
				
		int getid() const { return id; };
		int gettype() const { return type; };                   
		double getx() const { return p.x; };                    
		double gety() const { return p.y; };                    
		double getz() const { return p.z; };                    
		double getax() const { return a.x; };                   
		double getay() const { return a.y; };                   
		double getaz() const { return a.z; };                   
		double getvx() const { return v.x; };                   
		double getvy() const { return v.y; };                   
		double getvz() const { return v.z; };                   

		void setfactorsocialforce(double f);
		void setfactorobstacleforce(double f);
		void setfactordesiredforce(double f);
		void setfactorlookaheadforce(double f);
		
		void addWaypoint(Twaypoint *wp);
		void assignScene(Tscene *s);		
	};
}
#endif
