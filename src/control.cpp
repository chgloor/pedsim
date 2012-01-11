// (c) 2011 by Gloor Consulting
// See main.cpp for more information

#include "control.h"
#include "config.h"

#include <QtGui>

#include <iostream>


using namespace std;

extern Config config;

Control::Control(QWidget *parent, bool admin) : QDockWidget(parent) {
	ui.setupUi(this);

	if (admin == false) {
		//		ui.positionBox->hide();
	}

	connect(ui.waypointsCheckBox, SIGNAL(toggled(bool)), this, SLOT(showWaypoints(bool)));
	connect(ui.wallforceSlider, SIGNAL(valueChanged(int)), this, SLOT(simWallForce(int)));
	connect(ui.pedforceSlider, SIGNAL(valueChanged(int)), this, SLOT(simPedForce(int)));
	connect(ui.simspeedSlider, SIGNAL(valueChanged(int)), this, SLOT(simSpeed(int)));
}

void Control::showWaypoints(bool show) {
	config.setGuiShowWaypoints(show);
}

void Control::simWallForce(int value) {
	config.setSimWallForce(0.1f*value); // div value by 10
}

void Control::simPedForce(int value) {
	config.setSimPedForce(0.1f*value); // div value by 10
}

void Control::simSpeed(int value) {
	config.setSimSpeed(1000/value); // div value by 10
}

