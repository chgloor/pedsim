//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "messageparser.h"
#include "itemcontainer.h"
#include "agent.h"
#include "obstacle.h"

#include <QtWidgets>

#include <iostream>
#include <string>

extern QGraphicsScene *scene;
extern ItemContainer agentcontainer;
extern ItemContainer obstaclecontainer;


MessageParser::MessageParser(QByteArray datagram) {
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


void MessageParser::parse() {
    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    while (!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if (!e.isNull()) {
            //            std::cout << qPrintable(e.tagName()) << std::endl;
            if (e.tagName() == "position") {
                std::string type = e.attribute("type", "").toStdString().c_str();
                int id = atoi(e.attribute("id", "0").toStdString().c_str());
                double x = atof(e.attribute("x", "0.0").toStdString().c_str());
                double y = atof(e.attribute("y", "0.0").toStdString().c_str());
                //                std::cout << id << " " << type << std::endl;

                if (type == "agent") {
                    if (!agentcontainer.contains(id)) {
                        Agent *agent = new Agent;
                        scene->addItem(agent);
                        agentcontainer.addItem(agent);
                    }
                    agentcontainer.updatePosition(id, x, y);
                }

                if (type == "obstacle") {
                    if (!obstaclecontainer.contains(id)) {
                        Obstacle *obstacle = new Obstacle;
                        scene->addItem(obstacle);
                        obstaclecontainer.addItem(obstacle);
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
