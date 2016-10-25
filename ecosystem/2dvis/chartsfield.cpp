#include <QtWidgets>

#include "chartsfield.h"

#include <QtCharts>

using namespace QtCharts;

ChartsField::ChartsField(QString name)  {
  value = 0.0;

  series = new QLineSeries();

  chart = new QChart();
  chart->legend()->hide();
  // chart->addSeries(series);
  // chart->createDefaultAxes();
  chart->setTitle(name);
  chart->setTheme(QChart::ChartThemeBlueCerulean);
  
  chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);
  chartView->setMinimumWidth(100);
  chartView->setMaximumWidth(800);
  QVBoxLayout *layout;
  layout = new QVBoxLayout();
  
  layout->addWidget(chartView);

  setLayout(layout);

}

void ChartsField::update(long timestep, double pvalue) {
  if (value != pvalue) {
    value = pvalue;
    chart->removeSeries(series);
    chart->addSeries(series);
    chart->createDefaultAxes();
    series->append(timestep, value);

    QValueAxis *axisX = new QValueAxis;
    //    axisX->setRange(0, timestep);
    axisX->setTickCount(10);
    axisX->setMinorTickCount(1);
    axisX->setLabelFormat("%d");
    chart->setAxisX(axisX, series);

    chartView->update();
    chartView->repaint();
  }
}
