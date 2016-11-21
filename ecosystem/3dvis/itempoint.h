//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#ifndef ITEMPOINT_H
#define ITEMPOINT_H

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

#include "item.h"

class ItemPoint : public Item {
public:
	ItemPoint(Qt3DCore::QEntity *rootEntity, QString type);
	virtual void updateComponents();

private:
	QString type_;
	double scale_;
	double zoffset_;
};

#endif
