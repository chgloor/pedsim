//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include <iostream>

#include "messageparser.h"


MessageParser::MessageParser(QByteArray datagram) {
    doc = QDomDocument("mydocument");
    if (!doc.setContent(datagram)) {
        std::cout << "Can't parse message" << std::endl;
        std::cout << QString(datagram).toUtf8().constData()  << std::endl;
    }
    return;
}


void MessageParser::parse() {
    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    while (!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if (!e.isNull()) {
            std::cout << qPrintable(e.tagName()) << std::endl;
            if (e.tagName() == "position") {
                int id = atoi(e.attribute("id", "0").toStdString().c_str());
                double x = atof(e.attribute("x", "0.0").toStdString().c_str());
                double y = atof(e.attribute("y", "0.0").toStdString().c_str());

                std::cout << id << " " << x << "/" << y << std::endl;

                emit updateAgentPosition(id, x, y);

            }
        }
        n = n.nextSibling();
    }
}
