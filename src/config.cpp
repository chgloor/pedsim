// (c) 2011 by Gloor Consulting
// See main.cpp for more information

#include "config.h"
//#include "logger.h"

#include <QtGui>

#include <iostream>

//extern Logger* logger;

using namespace std;


Config::Config() { // make sure this reflects what is set as default in the suer interface!  --chgloor 2012-01-13
	guiShowWaypoints = false;
	simWallForce = 10;
	simPedForce = 10;
	simSpeed = 1000/20;
	mlTendency = true;
	showForces = false;
	showDirection = false;
	simh = 0.4;
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
