//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//
// Small UDP xml packet sender, based on the corresoponding Qt example.
//


#include <QApplication>

#include "sender.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Sender sender;
    sender.show();
    return app.exec();
}
