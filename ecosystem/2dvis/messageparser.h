//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include <QObject>
#include <QDomDocument>

class MessageParser : public QObject {
    Q_OBJECT

public:
    MessageParser(QByteArray datagram);

public:
    void parse();

signals:
    void updateAgentPosition(int id, double x, double y);
    void updateObstaclePosition(int id, double x, double y);

private:
    QDomDocument doc;


};

#endif
