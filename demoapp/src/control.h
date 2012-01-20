// (c) 2011 by Gloor Consulting
// See main.cpp for more information

#ifndef _control_h_
#define _control_h_

#include "ui_control.h" 


class Control : public QDockWidget {
	Q_OBJECT

 public:
	Control(QWidget *parent = 0, bool admin = false);

 signals: 
	void zoomin();
	void zoomout();

 public slots:
	void showWaypoints(bool show);
	void simWallForce(int value);
	void simPedForce(int value);
	void simSpeed(int value);
	void simh(int value);
	void mlTendency(bool value);
	void mlLookAhead(bool value);

	void showForces(bool show);
	void showDirection(bool show);

 private:
	  Ui_Control ui;

 };

#endif
