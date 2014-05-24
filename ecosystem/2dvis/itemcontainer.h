//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#ifndef ITEMCONTAINER_H
#define ITEMCONTAINER_H

#include <QVector>
#include <QObject>

class Item;

class ItemContainer : public QObject {
    Q_OBJECT

public:
    ItemContainer();
    void addItem(Item *i) {container.append(i); };
    bool contains(int id) { return (id < container.size()); };

public slots:
    void updatePosition(int id, double x, double y);
    void updatePosition(int id, double x, double y, double dx, double dy);

private:
    QVector<Item*> container;

};

#endif
