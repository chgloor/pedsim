//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

// /opt/Qt/5.7/gcc_64/bin/qmake

#include <QGuiApplication>
#include <QCommandLineParser>

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
#include "ground.h"
#include "globals.h"
#include "serverstream.h"


ItemContainer agentcontainer;
ItemContainer pointcontainer;
ItemContainer obstaclecontainer;
Receiver *receiver;
ServerStream *serverstream;

Qt3DRender::QCamera *camera;
Qt3DCore::QEntity *scene;


Qt3DCore::QEntity *createScene() {
    // Root entity
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity;

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
    l->setWorldDirection(QVector3D(0.8, -1, 0.3));

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

    QCommandLineParser cparser;
    cparser.setApplicationDescription("3-dimensional PEDSIM visualizer.");
    cparser.addHelpOption();

    QCommandLineOption udpOption(QStringList() << "u" << "udp", "Read input from network on UDP port <port>", "port");
    cparser.addOption(udpOption);

    QCommandLineOption hostOption(QStringList() << "s" << "server", "Read input from network on TCP host <host>", "host");
    cparser.addOption(hostOption);

    QCommandLineOption portOption(QStringList() << "p" << "port", "Read input from network on TCP port <port>", "port");
    cparser.addOption(portOption);

    QCommandLineOption camOption(QStringList() << "c" << "camera", "Display view from camera with ID <camera>", "camera");
    cparser.addOption(camOption);

    QCommandLineOption elevationOption(QStringList() << "e" << "elevation", "Elevation data URL, e.g. file:ground.obj", "URL");
    cparser.addOption(elevationOption);

    cparser.process(app);

    bool g_option_udp = cparser.isSet(udpOption);
    int g_option_udp_port = cparser.value(udpOption).toInt();

    bool g_option_port = cparser.isSet(portOption);
    int g_option_port_port = cparser.value(portOption).toInt();

    bool g_option_host = cparser.isSet(hostOption);
    QString g_option_host_host = cparser.value(hostOption);

    g_option_camera = cparser.isSet(camOption);
    g_option_camera_id = cparser.value(camOption);

    g_option_elevation = cparser.isSet(elevationOption);
    g_option_elevation_filename = cparser.value(elevationOption);


    Qt3DExtras::Qt3DWindow view;

    scene = createScene();
    if (g_option_elevation) {
      Ground *g = new Ground(scene, g_option_elevation_filename);
    }

    if (g_option_udp) {
      receiver = new Receiver(g_option_udp_port);
    }

    if (g_option_host) {
      int port = 2323;
      if (g_option_port) {
	port = g_option_port_port;
      }      
      serverstream = new ServerStream(NULL, g_option_host_host, g_option_port_port);
      serverstream->open();
    }
    
    // Camera
    camera = view.camera();
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
