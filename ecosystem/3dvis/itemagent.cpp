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

#include <Qt3DRender/QMesh>


ItemAgent::ItemAgent(Qt3DCore::QEntity *rootEntity) : Item(rootEntity) {
	Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial(rootEntity);

	Qt3DCore::QEntity *entity = new Qt3DCore::QEntity(rootEntity);
	material->setDiffuse(QColor(QRgb(0xffffff)));

	QMatrix4x4 m;
	// m.translate(m_position);
	// m.rotate(270, QVector3D(1.0f, 0.0f, 0.0f));
	m.rotate(90, QVector3D(0.0f, 1.0f, 0.0f));
	m.scale(0.03);
	transform->setMatrix(m);

	
	Qt3DRender::QMesh *mesh = new Qt3DRender::QMesh();
	mesh->setSource(QUrl("file:agent/stickman.obj"));
	entity->addComponent(mesh);
	entity->addComponent(transform);
	entity->addComponent(material);
}

void ItemAgent::updateComponents() {
	transform->setTranslation(QVector3D(x, 1.0+z, y));
	//transform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), r));
};
