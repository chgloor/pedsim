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
	//	void showWaypoints(bool show);

 public slots:
	void showWaypoints(bool show);
	void simWallForce(int value);
	void simPedForce(int value);
	void simSpeed(int value);
	//	  void updateSubsystemConnectedIR(QString ready);

 private:
	  Ui_Control ui;
	  //	  bool ison;

 };

#endif
