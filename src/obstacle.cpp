//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2004 by Christian Gloor
//                              
// You can redistribute and/or modify this program under the terms of
// the GNU General Public License.  See copying.txt for details.
// 


#include "math.h"

#include "obstacle.h"
#include "vector.h"

#include <QPen>


#include <vector>

extern ObstacleContainer obstacle;

using namespace std;


/// Description: set intial values
/// \author  chgloor
/// \date    2012-01-07
Tobstacle::Tobstacle(double pax, double pay, double pbx, double pby, QGraphicsLineItem *pl) {
  static int staticid = 0;
  id = staticid++;
  ax = pax;
  ay = pay;
  bx = pbx;
  by = pby;
  line = pl;
  line->setLine(ax, ay, bx, by);
};

/// 
/// \author  chgloor
/// \date    2012-01-07
Tobstacle::Tobstacle() {
  static int staticid = 0;
  id = staticid++;
  ax = 0;
  ay = 0;
  bx = 1;
  by = 1;
  line = NULL;
};

/// 
/// \author  chgloor
/// \date    2012-01-07
/// \return  
/// \warning 
/// \param   
void Tobstacle::setPosition(double pax, double pay, double pbx, double pby) {
	ax = pax, ay = pay;
	bx = pbx, by = pby;

	line->setLine(ax, ay, bx, by);

};
