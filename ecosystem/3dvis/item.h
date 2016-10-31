//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#ifndef ITEM_H
#define ITEM_H

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

class Item : public Qt3DCore::QEntity {
public:
	Item(Qt3DCore::QEntity *rootEntity);
	virtual void updateComponents();

	double x;
	double y;
	double z;
	double r; // rotation


protected:
	Qt3DCore::QTransform *transform;

};

#endif
