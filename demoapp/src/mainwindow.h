
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/QGraphicsView>

class QAction;
class QMenu;
class Control;

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

	/* void startTime(); */
	/* void resetTime(); */

	void timestep();
	void fps();
	
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
	//	QToolBar *fileToolBar;
	QToolBar *editToolBar;
	QAction *exitAct;
	QAction *aboutAct;
	//	QAction *aboutQtAct;

	QAction *zoominAct;
	QAction *zoomoutAct;

	Control *uicontrol;

	//	QAction *resetTimeAct;
	//	QAction *startTimeAct;

	QTimer *timer;

	int fpscount;
};

#endif
