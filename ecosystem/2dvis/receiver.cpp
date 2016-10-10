//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include <QtWidgets>
#include <QtNetwork>

#include <iostream>

#include "messageparser.h"
#include "receiver.h"


Receiver::Receiver(int port, QWidget *parent) : QWidget(parent) {
  udpSocket = new QUdpSocket(this);
  if (udpSocket->bind(QHostAddress::AnyIPv4, port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint) == true) {
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    std::cout << "Listening for UDP/XML packets on port " << port << std::endl;
  } else {
    std::cout << "Can't bind socket to port " << port << std::endl;
  }
}


void Receiver::processPendingDatagrams() {
  while (udpSocket->hasPendingDatagrams()) {
    QByteArray datagram;
    datagram.resize(udpSocket->pendingDatagramSize());
    udpSocket->readDatagram(datagram.data(), datagram.size());
    //    std::cout << QString(datagram).toUtf8().constData()  << std::endl;
    MessageParser parser(datagram);
    parser.parse();
  }
}
