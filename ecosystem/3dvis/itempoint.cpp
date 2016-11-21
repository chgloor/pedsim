//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "itempoint.h"

#include <Qt3DExtras/QCuboidMesh>
#include <QCylinderMesh>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QGoochMaterial>


#include <Qt3DRender/QMesh>



ItemPoint::ItemPoint(Qt3DCore::QEntity *rootEntity, QString type) : Item(rootEntity), type_(type), scale_(3.0), zoffset_(-4.0) {
  Qt3DCore::QEntity *entity = new Qt3DCore::QEntity(rootEntity);

  Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial(rootEntity);
  material->setDiffuse(QColor(QRgb(0x00aa00)));
	
  QMatrix4x4 m;
  m.translate(QVector3D(0, 0+zoffset_, 0)); 
  // m.translate(m_position);
  // m.rotate(270, QVector3D(1.0f, 0.0f, 0.0f));
  m.rotate(90, QVector3D(0.0f, 1.0f, 0.0f));
  m.scale(scale_);
  transform->setMatrix(m);
	
  Qt3DRender::QMesh *mesh = new Qt3DRender::QMesh();
  mesh->setSource(QUrl("file:agent/tree1.obj"));

  entity->addComponent(mesh);
  entity->addComponent(transform);
  entity->addComponent(material);
}


void ItemPoint::updateComponents() {
  QMatrix4x4 m;
  m.translate(QVector3D(x, z+zoffset_, y)); 
  m.scale(scale_);
 // m.rotate(r, QVector3D(0.0f, 1.0f, 0.0f));
  // m.translate(QVector3D(l / 2.0, 0, 0));
  transform->setMatrix(m);
};
