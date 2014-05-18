#include <QtWidgets>
#include <QtNetwork>

#include <iostream>

#include "messageparser.h"
#include "receiver.h"


Receiver::Receiver(QWidget *parent) : QWidget(parent) {
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(45454, QUdpSocket::ShareAddress);

    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}


void Receiver::processPendingDatagrams() {
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        MessageParser parser(datagram);
        parser.parse();
    }
}

