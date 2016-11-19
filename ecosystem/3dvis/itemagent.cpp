//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "itemagent.h"

#include <Qt3DExtras/QTorusMesh>
#include <QCylinderMesh>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QGoochMaterial>


ItemAgent::ItemAgent(Qt3DCore::QEntity *rootEntity) : Item(rootEntity) {
	Qt3DExtras::QGoochMaterial *material = new Qt3DExtras::QGoochMaterial(rootEntity);

	Qt3DCore::QEntity *entity = new Qt3DCore::QEntity(rootEntity);
	material->setDiffuse(QColor(QRgb(0xaaaaaa)));

	Qt3DExtras::QCylinderMesh *m = new Qt3DExtras::QCylinderMesh;
	m->setRadius(0.75);
	m->setLength(2);
	m->setRings(30);
	m->setSlices(10);

	entity->addComponent(m);
	entity->addComponent(transform);
	entity->addComponent(material);
}

void ItemAgent::updateComponents() {
	transform->setTranslation(QVector3D(x, 1.0+z, y));
	//transform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), r));
};
