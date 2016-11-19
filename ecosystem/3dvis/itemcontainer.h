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
    Item* at(QString id);

public slots:
    void clear();
	void setRotation(QString id, double r);
    void updatePosition(QString id, double x, double y);
   

private:
    QHash<QString, Item*> container;

};

#endif
