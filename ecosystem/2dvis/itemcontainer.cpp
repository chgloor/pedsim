//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "itemcontainer.h"
#include "item.h"

#include <iostream>

ItemContainer::ItemContainer() {
}


void ItemContainer::updatePosition(int id, double x, double y) {
    if (id < container.size()) {
        container[id]->x = x;
        container[id]->y = y;
        //std::cout << id << " pos " << x << "/" << y << std::endl;
    } else {
        std::cout << "Item not in container: " << id << " < " << container.size() << std::endl;
    }
}

void ItemContainer::updatePosition(int id, double x, double y, double dx, double dy) {
    updatePosition(id, x, y);
    if (id < container.size()) {
        container[id]->dx = dx;
        container[id]->dy = dy;
        //std::cout << id << " pos " << x << "/" << y << std::endl;
    }
}
