#include <QtWidgets>
#include <QtGlobal>

#ifdef USE_CHARTS
#include "chartswidget.h"
ChartsWidget *chartswidget;
#endif

#include "mainwindow.h"
#include "metricswidget.h"
#include "receiver.h"
#include "messageparser.h"

#include "globals.h"

static const double SCALE = 10.0;
MetricsWidget *metricswidget;

QGraphicsScene *scene;

Receiver *receiver;


MainWindow::MainWindow() {
  scene = new QGraphicsScene();
  scene->setSceneRect(SCALE * -100, SCALE * -100, SCALE * 200, SCALE * 200);
  scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  scene->setBackgroundBrush(Qt::black);

  view = new MyGraphicsView(scene);

  view->setRenderHint(QPainter::Antialiasing);
  //view->setBackgroundBrush(QPixmap(":/images/street.jpg"));
  //  view->setCacheMode(QGraphicsView::CacheBackground);
  view->setBackgroundBrush(QColor(24, 24, 24));
  //  view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
  view->setDragMode(QGraphicsView::ScrollHandDrag);
  //  view->scale(0.5, 0.5);

  resize(1440, 810);
  setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "PEDSIM's 2D Visualizer"));

  setCentralWidget(view);

  // QTimer timer;
  // QObject::connect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));
  // timer.start(1000 / 33);


  if (g_option_metrics) {
    metricswidget = new MetricsWidget;
    QDockWidget *dockWidget = new QDockWidget(tr("Metrics"), this);
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dockWidget->setWidget(metricswidget);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
  }

#ifdef USE_CHARTS
  if (g_option_charts) {
    chartswidget = new ChartsWidget;
    QDockWidget *dockWidget = new QDockWidget(tr("Charts"), this);
    dockWidget->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    dockWidget->setWidget(chartswidget);
    addDockWidget(Qt::TopDockWidgetArea, dockWidget);
  }
#endif


  // use network stream as input
  if (g_option_network) {
    receiver = new Receiver(g_option_network_port);
  }

  // use provided file as input
  if (g_option_file) {
    QFile inputFile(g_option_file_name);
    if (inputFile.open(QIODevice::ReadOnly)) {
      QTextStream in(&inputFile);
      while (!in.atEnd()) {
	QString line = "<message>" + in.readLine() + "</message>";
	QByteArray datagram = line.toUtf8();
	MessageParser parser(datagram);
	parser.parse();
	update();
      }
      inputFile.close();
    }
  }

  
};
