///
/// pedsim - A microscopic pedestrian simulation system. 
/// Copyright (c) 2003 - 2012 by Christian Gloor
///                              

#ifndef _loadscene_h_
#define _loadscene_h_

class Scene;
class Waypoint;
class QGraphicsScene;
class Agent;

#include <QtCore>
#include <QXmlStreamReader>

class Loadscene : public QObject {

	Q_OBJECT
	
 public:
	Loadscene(QString file, Scene *pedscene, QGraphicsScene *graphicsscene); 
	
 signals: 
	
 public slots:		
	
 private slots:
	void processData(QByteArray data);
	
 private:
	QXmlStreamReader m_xmlReader;
	Scene *pedscene; 
	QGraphicsScene *graphicsscene;
	
	QMap<QString, Waypoint*> waypoints;
	QList<Agent*> agents;
};

#endif
