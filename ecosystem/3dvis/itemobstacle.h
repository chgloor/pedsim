//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#ifndef ITEMOBSTACLE_H
#define ITEMOBSTACLE_H

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

#include "item.h"

class ItemObstacle : public Item {
public:
	ItemObstacle(Qt3DCore::QEntity *rootEntity, double l);
	virtual void updateComponents();

private:
	double l;
};

#endif
