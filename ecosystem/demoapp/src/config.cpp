// (c) 2011 by Christian Gloor
// See main.cpp for more information

#include "config.h"

#include <QtGui>

#include <iostream>

using namespace std;

/// \date    2012-01-11
Config::Config() { // make sure this reflects what is set as default in the user interface!  --chgloor 2012-01-13
    guiShowWaypoints = false;
    simWallForce = 50;
    simPedForce = 30;
    simSpeed = 1000/30;
    mlTendency = false;
    mlLookAhead = true;
    showForces = true;
    showDirection = true;
    showTree = false;
    simh = 0.4;
    followAgent = true;
}

/// \date    2012-01-11
void Config::setGuiShowWaypoints(bool value) {
    guiShowWaypoints = value;
}

/// \date    2012-01-11
void Config::setSimWallForce(double value) {
    simWallForce = value;
}

/// \date    2012-01-11
void Config::setSimPedForce(double value) {
    simPedForce = value;
}

/// \date    2012-01-11
void Config::setSimSpeed(int value) {
    simSpeed = value;
}
