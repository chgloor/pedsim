#ifndef METRICSWIDGET_H
#define METRICSWIDGET_H

#include <QtWidgets>

class MetricsField;

class MetricsWidget : public QWidget {
  Q_OBJECT

public:
  MetricsWidget();

  void update(QString name, double value);
  void clear();

private:
  QHash<QString, MetricsField*> metrics;
  QVBoxLayout *layout;

};


#endif
