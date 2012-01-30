// (c) 2011 by Gloor Consulting
// See main.cpp for more information

#ifndef _config_h_
#define _config_h_

//#include "ui_config.h" 

#include <QObject>

class Config : public QObject {
	Q_OBJECT

 public:
	Config();

	bool guiShowWaypoints;
	double simWallForce;
	double simPedForce;
	int simSpeed;
	bool mlTendency;
	bool mlLookAhead;
	bool showForces;
	bool showDirection;
	double simh;

 signals: 
	//	void showWaypoints(bool show);

 public slots:
	void setGuiShowWaypoints(bool value);
	void setSimWallForce(double value);
	void setSimPedForce(double value);
	void setSimSpeed(int value);
 };

#endif
