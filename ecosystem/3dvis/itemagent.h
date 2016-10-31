//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#ifndef ITEMAGENT_H
#define ITEMAGENT_H

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

#include "item.h"

//class Item : public QGraphicsItem {
class ItemAgent : public Item {
public:
	ItemAgent(Qt3DCore::QEntity *rootEntity);
	virtual void updateComponents();


};

#endif
