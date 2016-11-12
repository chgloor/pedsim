//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include <QtNetwork>
#include <iostream>

#include "messageparser.h"
#include "receiver.h"

Receiver::Receiver(int port) : QObject() {
  udpSocket = new QUdpSocket(this);

  if (udpSocket->bind(QHostAddress::AnyIPv4, port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint) == true) {
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    std::cout << "Listening for UDP/XML packets on port " << port << std::endl;
  } else {
    std::cout << "Can't bind socket to port " << port << std::endl;
  }
}

/*
Receiver::Receiver(QString host, int port) : QObject() {
  tcpSocket = new QTcpSocket(this);

  tcpSocket->abort();
  if (tcpSocket->connectToHost(host, port) == true) {
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagramsStream()));
    std::cout << "Listening for TCP/XML messages from " << host.toStdString() << " on port " << port << std::endl;
  } else {
    std::cout << "Can't connect to " << host.toStdString() << " port " << port << std::endl;
  }
}
*/

void Receiver::processPendingDatagrams() {
  while (udpSocket->hasPendingDatagrams()) {
    QByteArray datagram;
    datagram.resize(udpSocket->pendingDatagramSize());
    udpSocket->readDatagram(datagram.data(), datagram.size());
    //    std::cout	<< QString(datagram).toUtf8().constData()  << std::endl;
    MessageParser parser(datagram);
    parser.parse();
  }
}
