///
/// pedsim - A microscopic pedestrian simulation system.
/// Copyright (c) 2003 - 2012 by Christian Gloor
///


#include "loadscene.h"
#include "scene.h"
#include "obstacle.h"
#include "waypoint.h"
#include "agent.h"

#include <QObject>
#include <QGraphicsScene>

#include <iostream>
#include <sstream>

using namespace std;

/// object constructor
/// \date    2011-01-03
/// \param   please set the parent, if available.
//Loadscene::Loadscene(QObject* parent = 0) : QObject(parent) {
Loadscene::Loadscene(QString filename, Scene *ppedscene, QGraphicsScene *pgraphicsscene) : QObject(0) {
    pedscene = ppedscene;
    graphicsscene = pgraphicsscene;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd()) {
         QByteArray line = file.readLine();
         processData(line);
     }
}


/// Called for each line in the file
/// \date    2012-02-03
void Loadscene::processData(QByteArray data) {
    m_xmlReader.addData(data);

    while (!m_xmlReader.atEnd()) {
        m_xmlReader.readNext();
        if (m_xmlReader.isStartElement()) {
            if (m_xmlReader.name() == "welcome") {
                // nop
            } else if (m_xmlReader.name() == "obstacle") {
                double x1 = m_xmlReader.attributes().value("x1").toString().toDouble();
                double y1 = m_xmlReader.attributes().value("y1").toString().toDouble();
                double x2 = m_xmlReader.attributes().value("x2").toString().toDouble();
                double y2 = m_xmlReader.attributes().value("y2").toString().toDouble();
                pedscene->addObstacle(
                    new Obstacle(x1, y1, x2, y2,
                                 graphicsscene->addLine(1, 1, 0, 0,
                                                        QPen(QColor(150, 75, 0), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
                                                        )
                                 )
                );

            } else if (m_xmlReader.name() == "waypoint") {
                QString id = m_xmlReader.attributes().value("id").toString();
                double x = m_xmlReader.attributes().value("x").toString().toDouble();
                double y = m_xmlReader.attributes().value("y").toString().toDouble();
                double r = m_xmlReader.attributes().value("r").toString().toDouble();
                Waypoint *w = new Waypoint(x, y, r, graphicsscene);
                waypoints[id] = w;

            } else if (m_xmlReader.name() == "agent") {
                double x = m_xmlReader.attributes().value("x").toString().toDouble();
                double y = m_xmlReader.attributes().value("y").toString().toDouble();
                int n = m_xmlReader.attributes().value("n").toString().toDouble();
                double dx = m_xmlReader.attributes().value("dx").toString().toDouble();
                double dy = m_xmlReader.attributes().value("dy").toString().toDouble();
                agents.clear();
                for (int i=0; i<n; i++) {
                    Agent *a = new Agent(graphicsscene);
                    a->setPosition(x + qrand()/(RAND_MAX/dx) -dx/2, y + qrand()/(RAND_MAX/dy) -dy/2, 0);
                    agents.push_back(a);
                }

            } else if (m_xmlReader.name() == "addwaypoint") {
                QString id = m_xmlReader.attributes().value("id").toString();
                Agent *a; foreach (a, agents) a->addWaypoint(waypoints[id]);
            }

        } else if (m_xmlReader.isEndElement()) {
            if (m_xmlReader.name() == "agent") {
                Agent *a; foreach (a, agents) pedscene->addAgent(a);
            }
        }
    }
}
