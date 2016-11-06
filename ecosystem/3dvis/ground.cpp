//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "ground.h"

#include <QCylinderMesh>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QGoochMaterial>
#include <QComponent>

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QMesh>

Ground::Ground(Qt3DCore::QEntity *rootEntity, QString filename) : Qt3DCore::QEntity(rootEntity), mesh(new Qt3DRender::QMesh()), transform(new Qt3DCore::QTransform()) {
  mesh->setSource(QUrl(filename));
  addComponent(mesh);

  //  QMatrix4x4 m;
  //  m.translate(m_position);
  //  m.rotate(270, QVector3D(1.0f, 0.0f, 0.0f));
  //  m.rotate(m_phi, QVector3D(0.0f, 1.0f, 0.0f));
  //  m.scale(m_scale);
  //  transform->setMatrix(m);
  addComponent(transform);

  auto *material = new Qt3DExtras::QPhongMaterial();
  material->setDiffuse(QColor(QRgb(0x33aa33)));
  addComponent(material);

}

