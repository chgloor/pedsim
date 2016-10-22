//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#ifndef ITEMCONTAINER_H
#define ITEMCONTAINER_H

#include <QHash>
#include <QObject>

#include <algorithm>
#include <item.h>

class ItemContainer : public QObject {
    Q_OBJECT

public:
    ItemContainer();
    void addItem(QString id, Item *i) {container[id]=i; };
    void removeItem(QString id);
    bool contains(QString id) { return (container.contains(id)); };
    void for_each(void (*fn)(Item*));

public slots:
    void clear();
    void setRotation(QString id, double r) { container[id]->r = r; container[id]->setRotation(r);};
    void updatePosition(QString id, double x, double y);
    void updatePosition(QString id, double x, double y, double radius);
    void updatePosition(QString id, double x, double y, double dx, double dy);

private:
    QHash<QString, Item*> container;

};

#endif
