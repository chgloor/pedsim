///
/// pedsim - A microscopic pedestrian simulation system. 
/// Copyright (c) 2003 - 2012 by Christian Gloor
///                              


#ifndef _mainwindow_h_
#define _mainwindow_h_

#include <QMainWindow>

class QAction;
class QMenu;
class Control;
class QGraphicsView;

class MainWindow : public QMainWindow {
	Q_OBJECT
		
 public:	
	MainWindow();
	QGraphicsView *graphicsView;
	
 protected:
	void closeEvent(QCloseEvent *event);
	
 private slots:
	void about();

 public slots:
	void zoomin();
	void zoomout();
	
 private:
	void createActions();
	void createMenus();
	void createToolBars();
	void createStatusBar();
	void readSettings();
	void writeSettings();

	QString strippedName(const QString &fullFileName);

	QMenu *fileMenu;
	QMenu *viewMenu;
	QMenu *helpMenu;
	QToolBar *editToolBar;
	QAction *exitAct;
	QAction *aboutAct;
	QAction *zoominAct;
	QAction *zoomoutAct;

	Control *uicontrol;

	QTimer *timer;
};

#endif
