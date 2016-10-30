//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "itemobstacle.h"

#include <Qt3DExtras/QCuboidMesh>
#include <QCylinderMesh>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QGoochMaterial>


ItemObstacle::ItemObstacle(Qt3DCore::QEntity *rootEntity, double l) : Item(rootEntity), l(l) {
	Qt3DExtras::QGoochMaterial *material = new Qt3DExtras::QGoochMaterial(rootEntity);
	material->setDiffuse(QColor(QRgb(0xaaaaaa)));
	
	Qt3DCore::QEntity *entity = new Qt3DCore::QEntity(rootEntity);

	Qt3DExtras::QCuboidMesh *m = new Qt3DExtras::QCuboidMesh;
	m->setXExtent((l>0)? l : 1.0);
	m->setYExtent(4);
	m->setZExtent(0.5);

	entity->addComponent(m);
	entity->addComponent(transform);
	entity->addComponent(material);
}


void ItemObstacle::updateComponents() {
	QMatrix4x4 m;
	m.translate(QVector3D(x, 2, y));
	m.rotate(r, QVector3D(0.0f, 1.0f, 0.0f));
	m.translate(QVector3D(l / 2.0, 0, 0));
	transform->setMatrix(m);
};