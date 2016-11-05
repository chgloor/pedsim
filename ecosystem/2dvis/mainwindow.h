#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "mygraphicsview.h"


class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow();
  MyGraphicsView *view;

};


#endif
