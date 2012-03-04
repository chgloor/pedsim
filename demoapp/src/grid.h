//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#ifndef _grid_h_
#define _grid_h_ 1

#include "cell.h"

#include <QGraphicsScene>

#include <vector>

using namespace std;

/// \author  chgloor
/// \date    2012-02-17
class Grid {
 private:

	double minx;
	double miny;
	
  vector< vector<Cell*> > cells;

 public:
  Grid(double x, double y, double w, double h, QGraphicsScene *l);
  QGraphicsScene *graphicsscene;
  QGraphicsRectItem *rect;

  double getValue(double x, double y, int value);
  

};

#endif
