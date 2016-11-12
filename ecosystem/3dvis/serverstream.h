#ifndef SERVERSTREAM_H
#define SERVERSTREAM_H

//#include "serverstreamxmlreader.h"
/* #include "quote.h" */
/* #include "order.h" */
/* #include "project.h" */
/* #include "instrument.h" */
/* #include "position.h" */

#include <QtCore>
#include <QtNetwork>
#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QMutex>

class ServerStream : public QObject {

	Q_OBJECT

	public:
		ServerStream(QObject* parent); 

	signals: 
		void connected();
		void encrypted();
		void disconnected();
		void welcomeReceived();
		void socketError(QAbstractSocket::SocketError err);

	public slots:
		void handleError(QAbstractSocket::SocketError);
		/* void subscribeInstrument(int iid); */
		/* void unsubscribeInstrument(int iid); */
		void open();
		void close();
		void sendWelcome();
		void sendGoodBye();

	private slots:
		void processData();

	private:
		//		ServerStreamXMLReader m_xmlReader;
		QXmlStreamReader m_xmlReader;
		QTcpSocket* m_socket;
		bool inPosition;
		QMutex* m_mutex;

};
#endif
