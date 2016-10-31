//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "messageparser.h"
#include "itemcontainer.h"
#include "item.h"
#include "itemagent.h"
#include "itemobstacle.h"

#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265359
#endif

#include <QtGlobal>
#include <Qt3DCore/QEntity>

extern Qt3DCore::QEntity *scene;

extern ItemContainer agentcontainer;
extern ItemContainer obstaclecontainer;

long timestep; 

MessageParser::MessageParser(QByteArray datagram) {
    // std::cout << QString(datagram).toUtf8().constData() << std::endl; // <--- uncomment to show the received message!
    doc = QDomDocument("mydocument");
    if (!doc.setContent(datagram)) {
        std::cout << "Can't parse message" << std::endl;
        std::cout << QString(datagram).toUtf8().constData()  << std::endl;
    }
}


//void scene_remove_item(Item *item) {
//    scene->removeItem(item);
//}

void delete_item(Item *item) {
    delete item;
}

void rem(int timestep) {
//  	QList<QGraphicsItem*> values = temporaryitems.values(timestep);
//	while (!values.isEmpty()) scene->removeItem(values.takeFirst());
//	temporaryitems.remove(timestep);
}

void MessageParser::parse() {
	QDomElement docElem = doc.documentElement();

	QDomNode n = docElem.firstChild();
	while (!n.isNull()) {
		QDomElement e = n.toElement();
		if (!e.isNull()) {
			if (e.tagName() == "timestep") {
				QString stimestep = e.attribute("value", "0");
				timestep = stimestep.toLong();

	/*
	rem(timestep);

	if ((timestep % 10) == 0) { // ideall we would use a priority queue or something like that here ...
	  QList<int> l = temporaryitems.uniqueKeys();
	  while (!l.isEmpty()) {	    
	    int t = l.takeFirst();
	    if (t < timestep) {
	      rem(t);
	    }
	  }
	}
	*/

//	scene->advance();
//	scene->update();
	
			}

			if (e.tagName() == "scenario") {
				//scenarioname = e.attribute("name", "");
			}

			if (e.tagName() == "reset") {
				timestep = 0;

				//QList<QGraphicsItem*> values = temporaryitems.values();
				//while (!values.isEmpty()) scene->removeItem(values.takeFirst());
				//temporaryitems.clear();

//				agentcontainer.for_each(scene_remove_item);
//				agentcontainer.for_each(delete_item);
//				agentcontainer.clear();

				//obstaclecontainer.for_each(scene_remove_item);
				//obstaclecontainer.for_each(delete_item);
				//obstaclecontainer.clear();

				//metricswidget->clear();
			}

			/*
			if (e.tagName() == "draw") {
				std::string type = e.attribute("type", "").toStdString().c_str();

				double duration = atoi(e.attribute("duration", "1").toStdString().c_str());

				double red = atof(e.attribute("red", "1.0").toStdString().c_str());
				double green = atof(e.attribute("green", "1.0").toStdString().c_str());
				double blue = atof(e.attribute("blue", "1.0").toStdString().c_str());
	
				if (type == "line") {
					double sx = atof(e.attribute("sx", "0.0").toStdString().c_str());
					double sy = atof(e.attribute("sy", "0.0").toStdString().c_str());
					double ex = atof(e.attribute("ex", "0.0").toStdString().c_str());
					double ey = atof(e.attribute("ey", "0.0").toStdString().c_str());
					QBrush brush = QBrush(QColor(red * 255.0, 255.0*green, 255.0*blue));
					temporaryitems.insert(timestep + 1 + duration, scene->addLine(SCALE * sx, SCALE * sy, SCALE * ex, SCALE * ey, QPen(brush, 1.0)));
				}
			}
			*/

			if (e.tagName() == "remove") {
				std::string type = e.attribute("type", "").toStdString().c_str();
				QString id = e.attribute("id", "0");
				
				if (type == "agent") {
					if (agentcontainer.contains(id)) {
					  agentcontainer.removeItem(id);
					}
				}
				
			}

			/*
			if (e.tagName() == "metrics") {
				metricslist = e.elementsByTagName("metric");

				for (int i = 0; i < metricslist.length(); ++i) {
					QDomNode n = metricslist.item(i);
					QDomElement e = n.toElement();
					QString key = e.attribute("key", "");
					double value = e.attribute("value", "").toDouble();
					metricswidget->update(key, value);

				}

			}
			*/

			if (e.tagName() == "position") {
				std::string type = e.attribute("type", "").toStdString().c_str();
				QString id = e.attribute("id", "0");
				double x = atof(e.attribute("x", "0.0").toStdString().c_str());
				double y = atof(e.attribute("y", "0.0").toStdString().c_str());

				
				if (type == "agent") {
					if (!agentcontainer.contains(id)) {
						Item *agent = new ItemAgent(scene);
						agentcontainer.addItem(id, agent);
					}
					agentcontainer.updatePosition(id, x, y);
				}
				/*
				if (type == "waypoint") {
					if (!waypointcontainer.contains(id)) {
						Waypoint *waypoint = new Waypoint;
						scene->addItem(waypoint);
						waypointcontainer.addItem(id, waypoint);
					}
					double radius = atof(e.attribute("radius", "0.0").toStdString().c_str());
					waypointcontainer.updatePosition(id, x, y, radius);
					obstaclecontainer.setRotation(id, 0.0);
				}
				*/
				if (type == "obstacle") {
					double dx = atof(e.attribute("dx", "0.0").toStdString().c_str());
					double dy = atof(e.attribute("dy", "0.0").toStdString().c_str());
					double l = sqrt(dx*dx + dy*dy);
					if (!obstaclecontainer.contains(id)) {
						Item *obstacle = new ItemObstacle(scene, l);
						obstaclecontainer.addItem(id, obstacle);
					}
					obstaclecontainer.updatePosition(id, x, y);
					obstaclecontainer.setRotation(id, 270.0+atan2(dx, dy) * 360.0 / (2.0 * M_PI));
				}
				
			}
	}
	n = n.nextSibling();
  }
}
