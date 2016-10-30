//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "item.h"

#include <QCylinderMesh>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QGoochMaterial>


Item::Item(Qt3DCore::QEntity *rootEntity) : Qt3DCore::QEntity(rootEntity), transform(new Qt3DCore::QTransform), r(0) {
	// does basically nothing for the time being. 
}

void Item::updateComponents() {
	transform->setTranslation(QVector3D(x, 1, y));
	//transform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), r));
};
