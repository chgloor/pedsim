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
class QTcpSocket;
class QAction;

class Receiver : public QObject {
		Q_OBJECT

public:
    Receiver(int port);
    Receiver(QString host, int port);

private slots:
    void processPendingDatagrams();
    //    void processPendingDatagramsStream();

private:
    QUdpSocket *udpSocket;
    //    QTcpSocket *tcpSocket;
};

#endif
