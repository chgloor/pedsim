#ifndef SERVERSTREAM_H
#define SERVERSTREAM_H

#include <QtCore>
#include <QtNetwork>
#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QMutex>

class ServerStream : public QObject {
  Q_OBJECT

 public:
  ServerStream(QObject* parent, QString host, int port); 

 signals: 
  void connected();
  void disconnected();
  void welcomeReceived();
  void socketError(QAbstractSocket::SocketError err);

 public slots:
  void handleError(QAbstractSocket::SocketError);
  void open();
  void close();
  void sendWelcome();
  void sendGoodBye();

 private slots:
  void processData();

 private:
  QXmlStreamReader xmlReader_;
  QTcpSocket* socket_;
  QMutex* mutex_;
  QString host_;
  int port_;
};
#endif
