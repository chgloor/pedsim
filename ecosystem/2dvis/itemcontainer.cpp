//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "itemcontainer.h"
#include "item.h"

#include <iostream>

ItemContainer::ItemContainer() {
}


// Removes all items from the container
void ItemContainer::clear() {
    container.clear();
}


void ItemContainer::for_each(void (*fn)(Item*)) {
    QHash<QString, Item*>::iterator it;
    for (it = container.begin(); it != container.end(); ++it) {
        fn(*it);
    }

}


void ItemContainer::updatePosition(QString id, double x, double y) {
    container[id]->x = x;
    container[id]->y = y;
}

void ItemContainer::updatePosition(QString id, double x, double y, double radius) {
    container[id]->x = x;
    container[id]->y = y;
    container[id]->radius = radius;
}


void ItemContainer::updatePosition(QString id, double x, double y, double dx, double dy) {
    updatePosition(id, x, y);
    container[id]->dx = dx;
    container[id]->dy = dy;
}
