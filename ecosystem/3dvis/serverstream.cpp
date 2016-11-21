//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "itemcontainer.h"
#include "item.h"
#include "itemagent.h"
#include "itempoint.h"
#include "itemobstacle.h"
#include "globals.h"

#include "serverstream.h"
#include "iostream"
#include "sstream"

#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>
#include <QMutex>
#include <QMutexLocker>

#include <QtGlobal>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>

using namespace std;

extern Qt3DCore::QEntity *scene;
extern Qt3DRender::QCamera *camera;

extern ItemContainer agentcontainer;
extern ItemContainer pointcontainer;
extern ItemContainer obstaclecontainer;


ServerStream::ServerStream(QObject* parent = 0, QString host = "localhost", int port = 2323) : QObject(parent), host_(host), port_(port) {
  mutex_ = new QMutex(QMutex::Recursive);
  socket_ = new QTcpSocket();

  connect(socket_, SIGNAL(connected()), this, SIGNAL(connected()));
  connect(socket_, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
  connect(socket_, SIGNAL(readyRead()), this, SLOT(processData()));
  connect(socket_, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError(QAbstractSocket::SocketError)));
  connect(this, SIGNAL(welcomeReceived()), this, SLOT(sendWelcome()));
}


void ServerStream::open() {
  QMutexLocker locker(mutex_);
  socket_->connectToHost(host_, port_);
}


void ServerStream::close () {
  QMutexLocker locker(mutex_);
  socket_->disconnectFromHost();
  emit disconnected(); // NOTE: disconnectFromHost() should send this, but somehow it doesn't
}


void ServerStream::processData () {
  while (socket_->bytesAvailable() > 4096) {
    char buffer[4096];
    int numRead = socket_->read(buffer, 4096);
    buffer[numRead] = '\0';
    xmlReader_.addData(buffer);
  }

  while (!xmlReader_.atEnd()) {
    QMutexLocker locker(mutex_);

    xmlReader_.readNext();

    if (xmlReader_.isStartElement()) {
      if (xmlReader_.name() == "timestep") {
	QString value = xmlReader_.attributes().value("value").toString();
	cout << "timestep " << value.toStdString() << endl;

      } else if (xmlReader_.name() == "welcome") {
	// emit welcomeReceived();

      } else if (xmlReader_.name() == "position") { // <position id="249" type="agent" x="27.6718" y="-0.552733" z="6.0119"  />
	QString type = xmlReader_.attributes().value("type").toString();
	QString id = xmlReader_.attributes().value("id").toString();
	double x = xmlReader_.attributes().value("x").toString().toDouble();
	double y = xmlReader_.attributes().value("y").toString().toDouble();
	double z = xmlReader_.attributes().value("z").toString().toDouble();

	if (type == "agent") {
	  if (!agentcontainer.contains(id)) {
	    Item *agent = new ItemAgent(scene);
	    agentcontainer.addItem(id, agent);
	  }
	  agentcontainer.updatePosition(id, x, y, z);
	}

	if (type == "point") {
	  QString mesh = xmlReader_.attributes().value("mesh").toString();
	  if (!pointcontainer.contains(id)) {
	    Item *point = new ItemPoint(scene, mesh);
	    pointcontainer.addItem(id, point);
	  }
	  pointcontainer.updatePosition(id, x, y, z);
	}

	if (type == "camera") {
	  if (g_option_camera) {
	    if (id == g_option_camera_id) {
	      double rx = xmlReader_.attributes().value("rx").toString().toDouble();
	      double ry = xmlReader_.attributes().value("ry").toString().toDouble();
	      double rz = xmlReader_.attributes().value("rz").toString().toDouble();
	      camera->setPosition(QVector3D(x, z, y));
	      camera->setViewCenter(QVector3D(x + rx, z + rz , y + ry));
	    }
	  }
	}

      }

      else if (xmlReader_.isEndElement()) {
	//   if (xmlReader_.name() == "position") {
	//  	this->inPosition = false;
	//   }
     }
    }
  }
}


void ServerStream::handleError (QAbstractSocket::SocketError err) {
  emit socketError(err);
}


void ServerStream::sendWelcome () {
  QMutexLocker locker(mutex_);

  stringstream ss;
  ss << "<welcome client=\"" << "3dvis\">";
  socket_->write(ss.str().c_str());
}


void ServerStream::sendGoodBye () {
  QMutexLocker locker(mutex_);

  stringstream ss;
  ss << "</welcome>";
  socket_->write(ss.str().c_str());
}
