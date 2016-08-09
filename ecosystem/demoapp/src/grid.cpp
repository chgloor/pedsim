//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#include "grid.h"
#include "cell.h"

#include <QPen>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include <iostream>

const double cellwidth = 10;
const double cellheight = 10;

using namespace std;

/// 
/// \author  chgloor
/// \date    2012-02-18
/// \return  
/// \warning 
/// \param   
Grid::Grid(double x, double y, double w, double h, QGraphicsScene *gs) {
	graphicsscene = gs;
	minx = x;
	miny = y;

	QPen p = QPen(QColor(0,88,0), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	p.setCosmetic(true);
	rect = graphicsscene->addRect(x, y, w, h, p);
	rect->setVisible(true);
	rect->setZValue(-200);

	for (double xx = x; xx < (x+w); xx += cellwidth) {
		vector<Cell*> row; // Create an empty row
		for (double yy = y; yy < (y+h); yy += cellheight) {
			row.push_back(new Cell(xx, yy, cellwidth, cellheight, gs)); // Add an element (column) to the row
		}
		cells.push_back(row); // Add the row to the main vector
	}

}



/// Gets a value out of a cell in the grid, based on the coordinates
/// \author  chgloor
/// \date    2012-02-18
/// \return  One of the values stored in the specified cell
/// \param   x/y The coordinates
/// \param   value The requested value
double Grid::getValue(double x, double y, int value) {
	if ((x-minx) < 0) return 0;
	if ((y-miny) < 0) return 0;

	unsigned int cellx = (x-minx)/cellwidth;
	unsigned int celly = (y-miny)/cellheight;	

	if (cellx >= cells.size()) return 0;
	if (celly >= cells[0].size()) return 0;

	return cells[cellx][celly]->values[value];
}
