#include <QtWidgets>

#include "mainwindow.h"

static const double SCALE = 10.0;

QGraphicsScene *scene;


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
	

  
};
