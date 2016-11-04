//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "messageparser.h"
#include "itemcontainer.h"
#include "agent.h"
#include "waypoint.h"
#include "obstacle.h"
#include "item.h"
#include "globals.h"
#include "metricswidget.h"

#include <QtWidgets>

#include <iostream>
#include <string>

#include <QtGlobal>

#ifdef USE_CHARTS
#include "chartswidget.h"
extern ChartsWidget *chartswidget;
#endif


extern QGraphicsScene *scene;
extern ItemContainer agentcontainer;
extern ItemContainer waypointcontainer;
extern ItemContainer obstaclecontainer;
extern MetricsWidget *metricswidget;

QString scenarioname = "";
static const double SCALE = 10.0;
QMultiHash<int, QGraphicsItem*> temporaryitems;
long timestep; 

QDomNodeList metricslist;

MessageParser::MessageParser(QByteArray datagram) {
  //       std::cout << QString(datagram).toUtf8().constData()  << std::endl; // <--- uncomment to show the received message!
    doc = QDomDocument("mydocument");
    if (!doc.setContent(datagram)) {
        std::cout << "Can't parse message" << std::endl;
        std::cout << QString(datagram).toUtf8().constData()  << std::endl;
    }

    // No chance at this stage, connect is way too slow  --cgloor 2014-05-21
    //    QObject::connect(this, SIGNAL(updateAgentPosition(int, double, double)),
    //                     &agentcontainer, SLOT(updatePosition(int, double, double)));
    //    QObject::connect(this, SIGNAL(updateObstaclePosition(int, double, double)),
    //                     &obstaclecontainer, SLOT(updatePosition(int, double, double)));

    return;
}


void scene_remove_item(Item *item) {
    scene->removeItem(item);
}

void delete_item(Item *item) {
    delete item;
}

void rem(int timestep) {
  	QList<QGraphicsItem*> values = temporaryitems.values(timestep);
	while (!values.isEmpty()) scene->removeItem(values.takeFirst());
	temporaryitems.remove(timestep);
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

	if (g_option_metrics) {
	  metricswidget->update("Timestep", timestep);
	}
	
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
	
	scene->advance();
	scene->update();
	
	if (g_option_writefile) {
	  int rx = 1280;
	  int ry = 720;
	  qDebug() << "Writing frame " << stimestep << " to directory " << g_option_writefile_directory;
	  QImage img(rx, ry, QImage::Format_ARGB32_Premultiplied);
	  //QImage img(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
	  QPainter p(&img);

	  p.beginNativePainting();
	  p.setRenderHint(QPainter::Antialiasing);

	  scene->clearSelection();
	  scene->setSceneRect(-rx, -ry, 2*rx, 2*ry);

	  //	  scene->advance();

	  scene->render(&p, QRectF(), QRectF(), Qt::KeepAspectRatioByExpanding);

	  // display logo, title, and timestep
	  QFont font = p.font() ;
	  font.setPointSize ( 12 );
	  p.setFont(font);

	  p.setPen(QColor(255, 192, 0));
	  p.drawText(0, ry-82, rx-40, 22, Qt::AlignRight, scenarioname);

	  p.setPen(QColor(255, 192, 0));
	  p.drawText(0, ry-60, rx-40, 22, Qt::AlignRight, stimestep.rightJustified(8, '0'));

	  font.setItalic(true);
	  p.setFont(font);
	  p.setPen(QColor(128, 128, 128));
	  p.drawText(0, ry-104, rx-40, 22, Qt::AlignRight, "PEDSIM");


	  // display metrics
	  for (int i = 0; i<metricslist.length(); ++i) {
	    QDomNode n = metricslist.item(i);
	    QDomElement e = n.toElement();
	    QString key = e.attribute("key", "");
	    QString value = e.attribute("value", "");

	    font.setItalic(false);
	    p.setFont(font);
	    p.setPen(QColor(128, 128, 128));
	    p.drawText( 40, ry-60-22*i, 200, 22, Qt::AlignLeft, key);
	    p.drawText(240, ry-60-22*i, 200, 22, Qt::AlignLeft, value.left(8));
	  }

	  p.endNativePainting();
	  if (!img.save(g_option_writefile_directory + "/" + stimestep.rightJustified(8, '0') + ".png")) {
	    qDebug() << "Writing frame " << stimestep << " to directory " << g_option_writefile_directory << " failed!";
	  }
	}
      }
      if (e.tagName() == "scenario") {
	scenarioname = e.attribute("name", "");
      }
      if (e.tagName() == "reset") {
	timestep = 0;

	QList<QGraphicsItem*> values = temporaryitems.values();
	while (!values.isEmpty()) scene->removeItem(values.takeFirst());
	temporaryitems.clear();

	agentcontainer.for_each(scene_remove_item);
	agentcontainer.for_each(delete_item);
	agentcontainer.clear();

	obstaclecontainer.for_each(scene_remove_item);
	obstaclecontainer.for_each(delete_item);
	obstaclecontainer.clear();

	if (g_option_metrics) {
	  metricswidget->clear();
	}
      }

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

      if (e.tagName() == "remove") {
	std::string type = e.attribute("type", "").toStdString().c_str();
	QString id = e.attribute("id", "0");

	if (type == "agent") {
	  if (agentcontainer.contains(id)) {
	    agentcontainer.removeItem(id);
	  }
	}
      }

      if (e.tagName() == "metrics") {
	metricslist = e.elementsByTagName("metric");

	for (int i = 0; i<metricslist.length(); ++i) {
	  QDomNode n = metricslist.item(i);
	  QDomElement e = n.toElement();
	  QString key = e.attribute("key", "");
	  double value = e.attribute("value", "").toDouble();
	  if (g_option_metrics) {
	    metricswidget->update(key, value);
	  }
	  
#ifdef USE_CHARTS
	if (g_option_charts) {
	  chartswidget->update(timestep, key, value);
	}
#endif	  

	}

      }

      if (e.tagName() == "position") {
	std::string type = e.attribute("type", "").toStdString().c_str();
	QString id = e.attribute("id", "0");
	double x = atof(e.attribute("x", "0.0").toStdString().c_str());
	double y = atof(e.attribute("y", "0.0").toStdString().c_str());

	if (type == "agent") {
	  if (!agentcontainer.contains(id)) {
	    Agent *agent = new Agent;
	    scene->addItem(agent);
	    agentcontainer.addItem(id, agent);
	  }
	  agentcontainer.updatePosition(id, x, y);
	}

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

	if (type == "obstacle") {
	  if (!obstaclecontainer.contains(id)) {
	    Obstacle *obstacle = new Obstacle;
	    scene->addItem(obstacle);
	    obstaclecontainer.addItem(id, obstacle);
	  }
	  double dx = atof(e.attribute("dx", "0.0").toStdString().c_str());
	  double dy = atof(e.attribute("dy", "0.0").toStdString().c_str());
	  obstaclecontainer.updatePosition(id, x, y, dx, dy);
	  obstaclecontainer.setRotation(id, 0.0);
	}

      }
    }
    n = n.nextSibling();
  }
}
