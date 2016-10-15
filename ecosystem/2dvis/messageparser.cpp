//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "messageparser.h"
#include "itemcontainer.h"
#include "agent.h"
#include "obstacle.h"
#include "item.h"
#include "globals.h"

#include <QtWidgets>

#include <iostream>
#include <string>

extern QGraphicsScene *scene;
extern ItemContainer agentcontainer;
extern ItemContainer obstaclecontainer;

QString scenarioname = "";
static const double SCALE = 10.0;
QMultiHash<int, QGraphicsItem*> temporaryitems;
long timestep; 

MessageParser::MessageParser(QByteArray datagram) {
  //      std::cout << QString(datagram).toUtf8().constData()  << std::endl; // <--- uncomment to show the received message!
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

void MessageParser::parse() {
  QDomElement docElem = doc.documentElement();

  QDomNode n = docElem.firstChild();
  while (!n.isNull()) {
    QDomElement e = n.toElement();
    if (!e.isNull()) {
      if (e.tagName() == "timestep") {
	QString stimestep = e.attribute("value", "0");
	timestep = stimestep.toLong();

	QList<QGraphicsItem*> values = temporaryitems.values(timestep);
	while (!values.isEmpty()) scene->removeItem(values.takeFirst());
	temporaryitems.remove(timestep);	

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

	  scene->advance();

	  scene->render(&p, QRectF(), QRectF(), Qt::KeepAspectRatioByExpanding);

	  QFont font = p.font() ;
	  font.setPointSize ( 12 );
	  //font.setWeight(QFont::DemiBold);
	  p.setFont(font);

	  p.setPen(QColor(255, 192, 0));
	  p.drawText(0, ry-80, rx-40, 20, Qt::AlignRight, scenarioname);

	  p.setPen(QColor(255, 192, 0));
	  p.drawText(0, ry-60, rx-40, 20, Qt::AlignRight, stimestep.rightJustified(8, '0'));

	  //		  font.setWeight(QFont::DemiBold);
	  font.setItalic(true);
	  p.setFont(font);
	  p.setPen(QColor(128, 128, 128));
	  p.drawText(0, ry-100, rx-40, 20, Qt::AlignRight, "PEDSIM");

	  p.endNativePainting();
	  img.save(g_option_writefile_directory + "/" + stimestep.rightJustified(8, '0') + ".png");
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

	if (type == "obstacle") {
	  if (!obstaclecontainer.contains(id)) {
	    Obstacle *obstacle = new Obstacle;
	    scene->addItem(obstacle);
	    obstaclecontainer.addItem(id, obstacle);
	  }
	  double dx = atof(e.attribute("dx", "0.0").toStdString().c_str());
	  double dy = atof(e.attribute("dy", "0.0").toStdString().c_str());
	  obstaclecontainer.updatePosition(id, x, y, dx, dy);
	}

      }
    }
    n = n.nextSibling();
  }
}
