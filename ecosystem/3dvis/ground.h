//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#ifndef GROUND_H
#define GROUND_H

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QMesh>
class Ground : public Qt3DCore::QEntity {
public:
  Ground(Qt3DCore::QEntity *rootEntity, QString filename);

private:
  Qt3DCore::QTransform *transform;
  Qt3DRender::QMesh *mesh;

};

#endif
