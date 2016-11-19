//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include <QGuiApplication>

#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>

#include <Qt3DInput/QInputAspect>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QGoochMaterial>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPlaneMesh>

#include <QFirstPersonCameraController>
#include <QDirectionalLight>

#include "qt3dwindow.h"

#include "item.h"
#include "itemcontainer.h"
#include "receiver.h"


ItemContainer agentcontainer;
ItemContainer obstaclecontainer;
Receiver *receiver;

Qt3DCore::QEntity *scene;

Qt3DCore::QEntity *createScene() {
    // Root entity
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity;

    // Material
    Qt3DRender::QMaterial *material = new Qt3DExtras::QGoochMaterial(rootEntity);

	Qt3DCore::QEntity *planeEntity;
	// Plane shape data
	Qt3DExtras::QPlaneMesh *planeMesh = new Qt3DExtras::QPlaneMesh();
	planeMesh->setWidth(100* 2 * 125.0f);
	planeMesh->setHeight(100* 2 * 75.0f);

	// Plane mesh transform
	Qt3DCore::QTransform *planeTransform = new Qt3DCore::QTransform();

	Qt3DExtras::QGoochMaterial *planeMaterial = new Qt3DExtras::QGoochMaterial();
	planeMaterial->setDiffuse(QColor(QRgb(0x33aa33)));

	// Light
	Qt3DRender::QDirectionalLight *l = new Qt3DRender::QDirectionalLight();
	l->setWorldDirection(QVector3D(0.3, -1, 0.3));

	// Plane
	planeEntity = new Qt3DCore::QEntity(rootEntity);
	planeEntity->addComponent(planeMesh);
	planeEntity->addComponent(planeMaterial);
	planeEntity->addComponent(planeTransform);
	planeEntity->addComponent(l);
    return rootEntity;
}


int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    Qt3DExtras::Qt3DWindow view;

    scene = createScene();
	receiver = new Receiver(2222);
	
    // Camera
    Qt3DRender::QCamera *camera = view.camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 75.0f, 200.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // For camera controls
	Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(scene);
	camController->setLinearSpeed(50.0f);
    camController->setLookSpeed(180.0f);
    camController->setCamera(camera);

    view.setRootEntity(scene);
    view.resize(1280, 720);
    view.show();

    return app.exec();
}
