//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include <QtWidgets>

#include <math.h>

#include "mygraphicsview.h"
#include "agent.h"
#include "obstacle.h"
#include "itemcontainer.h"
#include "receiver.h"
#include "messageparser.h"
#include "globals.h"

static const int AgentCount = 50;
static const double SCALE = 1.0;

QGraphicsScene *scene;
Receiver *receiver;

ItemContainer agentcontainer;
ItemContainer obstaclecontainer;


int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QCommandLineParser cparser;
    cparser.setApplicationDescription("2-dimensional PEDSIM visualizer.");
    cparser.addHelpOption();

    QCommandLineOption quietOption(QStringList() << "q" << "quiet", "Do not show graphical output");
    cparser.addOption(quietOption);

    QCommandLineOption networkOption(QStringList() << "n" << "network", "Read input from network on port <port>", "port");
    cparser.addOption(networkOption);

    QCommandLineOption fileOption(QStringList() << "f" << "file", "Read input from <file>", "file");
    cparser.addOption(fileOption);

    QCommandLineOption outputOption(QStringList() << "o" << "outputdirectory", "Write frame-by-frame image output to <directory>", "directory");
    cparser.addOption(outputOption);

    // Process the actual command line arguments given by the user
    cparser.process(app);

    g_option_writefile = cparser.isSet(outputOption);
    g_option_writefile_directory = cparser.value(outputOption);


    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    scene = new QGraphicsScene();

    scene->setSceneRect(SCALE * -100, SCALE * -100, SCALE * 200, SCALE * 200);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setBackgroundBrush(Qt::black);

    MyGraphicsView view(scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(QPixmap(":/images/street.jpg"));
    //view.setBackgroundBrush(Qt::black);
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "PEDSIM's 2D Visualizer"));
    view.resize(1440, 810);
    view.scale(0.5, 0.5);
    view.show();

    // use network stream as input
    QString port = cparser.value(networkOption);
    if (cparser.isSet(networkOption)) {
      receiver = new Receiver(port.toInt());
    }

    // use provided file as input
    if (cparser.isSet(fileOption)) {
        QFile inputFile(cparser.value(fileOption));
	if (inputFile.open(QIODevice::ReadOnly)) {
	  QTextStream in(&inputFile);
	  while (!in.atEnd()) {
	    QString line = "<message>" + in.readLine() + "</message>";
	    QByteArray datagram = line.toUtf8();
	    MessageParser parser(datagram);
	    parser.parse();
	  }
	  inputFile.close();
	}
    }
    
    // show output if not disabled (quiet)
    if (!cparser.isSet(quietOption)) {
	QTimer timer;
	QObject::connect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));
	timer.start(1000 / 33);
	
	return app.exec();
    }
    
}
