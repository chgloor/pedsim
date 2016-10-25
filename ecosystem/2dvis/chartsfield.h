#ifndef CHARTSFIELD_H
#define CHARTSFIELD_H

#include <QtWidgets>
#include <QtCharts>
using namespace QtCharts;

class ChartsField : public QWidget {
  Q_OBJECT

public:
  ChartsField(QString name);

  void update(long timestep, double value);

private:
  double value;
  QLineSeries *series;
  QChart *chart;
  QChartView *chartView;
};


#endif
