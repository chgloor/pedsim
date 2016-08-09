//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#ifndef _cell_h_
#define _cell_h_ 1

#include <QGraphicsScene>

#include <vector>

using namespace std;

/// \author  chgloor
/// \date    2012-02-17
class Cell {
 private:

 public:
	Cell(double x, double y, double w, double h, QGraphicsScene *l);
	QGraphicsScene *graphicsscene;
	
	vector<double> values;
};

#endif
