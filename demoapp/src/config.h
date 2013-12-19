// (c) 2011 by Christian Gloor
// See main.cpp for more information

#ifndef _config_h_
#define _config_h_

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
    bool showTree;
    bool followAgent;
    
 public slots:
    void setGuiShowWaypoints(bool value);
    void setSimWallForce(double value);
    void setSimPedForce(double value);
    void setSimSpeed(int value);
 };

#endif
