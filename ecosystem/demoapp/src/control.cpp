// (c) 2011 by Christian Gloor
// See main.cpp for more information

#include "control.h"
#include "config.h"

#include <QtGui>

#include <iostream>

using namespace std;

extern Config config;


Control::Control(QWidget *parent, bool admin) : QDockWidget(parent) {
    ui.setupUi(this);

    connect(ui.waypointsCheckBox, SIGNAL(toggled(bool)), this, SLOT(showWaypoints(bool)));
    connect(ui.treeCheckBox, SIGNAL(toggled(bool)), this, SLOT(showTree(bool)));

    connect(ui.showForcesCheckBox, SIGNAL(toggled(bool)), this, SLOT(showForces(bool)));
    connect(ui.showDirectionCheckBox, SIGNAL(toggled(bool)), this, SLOT(showDirection(bool)));

    connect(ui.followAgentCheckBox, SIGNAL(toggled(bool)), this, SLOT(followAgent(bool)));

    connect(ui.mlLookAheadCheckBox, SIGNAL(toggled(bool)), this, SLOT(mlLookAhead(bool)));
    connect(ui.mlTendencyCheckBox, SIGNAL(toggled(bool)), this, SLOT(mlTendency(bool)));

    connect(ui.wallforceSlider, SIGNAL(valueChanged(int)), this, SLOT(simWallForce(int)));
    connect(ui.pedforceSlider, SIGNAL(valueChanged(int)), this, SLOT(simPedForce(int)));
    connect(ui.simspeedSlider, SIGNAL(valueChanged(int)), this, SLOT(simSpeed(int)));
    connect(ui.simhSlider, SIGNAL(valueChanged(int)), this, SLOT(simh(int)));

    connect(ui.zoominButton, SIGNAL(clicked()), this, SIGNAL(zoomin()));
    connect(ui.zoomoutButton, SIGNAL(clicked()), this, SIGNAL(zoomout()));
}


void Control::setfps(double fps) {
    ui.fpsLabel->setText(QString("FPS (req %0 curr %1)").arg(ui.simspeedSlider->value()).arg(fps, 0, 'f', 1));
}


void Control::showWaypoints(bool show) {
    config.setGuiShowWaypoints(show);
}


void Control::showTree(bool show) {
    config.showTree = show;
}


void Control::simWallForce(int value) {
    config.setSimWallForce(0.1f*value); // div value by 10
    ui.wallforceLabel->setText(QString("Wall Force (%1)").arg(config.simWallForce));
}


void Control::simPedForce(int value) {
    config.setSimPedForce(0.1f*value); // div value by 10
    ui.pedforceLabel->setText(QString("Pedestrian Force (%1)").arg(config.simPedForce));
}


void Control::simSpeed(int value) {
    config.setSimSpeed(1000/value); // div value by 10
}


void Control::mlLookAhead(bool value) {
    config.mlLookAhead = value;
}


void Control::mlTendency(bool value) {
    config.mlTendency = value;
}


void Control::showForces(bool show) {
    config.showForces = show;
}


void Control::showDirection(bool show) {
    config.showDirection = show;
}


void Control::simh(int value) {
    config.simh = 0.01f*value;
    ui.simhLabel->setText(QString("Precision (h=%1)").arg(config.simh));
}


void Control::followAgent(bool follow) {
    config.followAgent = follow;
}
