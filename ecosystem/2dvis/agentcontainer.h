//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#ifndef AGENTCONTAINER_H
#define AGENTCONTAINER_H

#include <QVector>
#include <QObject>

class Agent;

class AgentContainer : public QObject {
    Q_OBJECT

public:
    AgentContainer();
    void addItem(Agent *a) {container.append(a); };

public slots:
    void updatePosition(int id, double x, double y);

private:
    QVector<Agent*> container;

};

#endif
