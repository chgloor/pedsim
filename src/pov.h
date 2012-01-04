//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2004 by Christian Gloor
//                              
// You can redistribute and/or modify this program under the terms of
// the GNU General Public License.  See copying.txt for details.
// 


#ifndef _pov_h_ 
#define _pov_h_ 1

#include "agent.h"

using namespace std;

#include <iostream> // cout ...
#include <fstream> // files
#include <string>     // strncpy
#include <map>      // maps 

class Tpov {
	long systemtime;
  ofstream file;
  char filename[255];
  void newfile();
 public:
  Tpov(char *filename, long systemtime);
  void drawAgent(int id, int type, double x, double y, double z, double vx, double vy, double vz, bool isfireing, double nex, double ney, double nez);
  void drawAgent(AgentIterator a);
};



#endif
