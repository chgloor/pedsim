// (c) 2011 by Gloor Consulting
// See main.cpp for more information

#include "config.h"
//#include "logger.h"

#include <QtGui>

#include <iostream>

//extern Logger* logger;

using namespace std;


Config::Config() {
	guiShowWaypoints = false;
	simWallForce = 10;
	simPedForce = 15;
	simSpeed = 1000/20;
}

/// \author  chgloor
/// \date    2012-01-11
void Config::setGuiShowWaypoints(bool value) {
	guiShowWaypoints = value;
}

/// \author  chgloor
/// \date    2012-01-11
void Config::setSimWallForce(double value) {
	simWallForce = value;
}

/// \author  chgloor
/// \date    2012-01-11
void Config::setSimPedForce(double value) {
	simPedForce = value;
}

/// \author  chgloor
/// \date    2012-01-11
void Config::setSimSpeed(int value) {
	simSpeed = value;
}
