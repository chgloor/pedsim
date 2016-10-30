//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>

class QLabel;
class QPushButton;
class QUdpSocket;
class QAction;

class Receiver : public QObject {
		Q_OBJECT

public:
    Receiver(int port);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket *udpSocket;
};

#endif
