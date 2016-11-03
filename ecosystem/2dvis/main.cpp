//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include <QtWidgets>

#include <math.h>

#include "mygraphicsview.h"
#include "agent.h"
#include "waypoint.h"
#include "obstacle.h"
#include "itemcontainer.h"
#include "mainwindow.h"
#include "globals.h"

// /opt/Qt/5.7/gcc_64/bin/qmake 


//static const int AgentCount = 50;
static const double SCALE = 1.0;


ItemContainer agentcontainer;
ItemContainer waypointcontainer;
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

    QCommandLineOption chartsOption(QStringList() << "c" << "charts", "Display charts DockWidget");
    cparser.addOption(chartsOption);

    QCommandLineOption metricsOption(QStringList() << "m" << "metrics", "Display metrics DockWidget");
    cparser.addOption(metricsOption);

    QCommandLineOption outputOption(QStringList() << "o" << "outputdirectory", "Write frame-by-frame image output to <directory>", "directory");
    cparser.addOption(outputOption);

    // Process the actual command line arguments given by the user
    cparser.process(app);

    g_option_writefile = cparser.isSet(outputOption);
    g_option_writefile_directory = cparser.value(outputOption);

    g_option_network = cparser.isSet(networkOption);
    g_option_network_port = cparser.value(networkOption).toInt();

    g_option_file = cparser.isSet(fileOption);
    g_option_file_name = cparser.value(fileOption);

    g_option_charts = cparser.isSet(chartsOption);
    g_option_metrics = cparser.isSet(metricsOption);

    
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));


    QFile File("darkorange.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    qApp->setStyleSheet(StyleSheet);
    

    MainWindow mainWin;
    
    // show output if not disabled (quiet)
    if (!cparser.isSet(quietOption)) {
      mainWin.show();
      return app.exec();
    }
    
}
