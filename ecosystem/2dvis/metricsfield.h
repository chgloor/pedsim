#ifndef METRICSFIELD_H
#define METRICSFIELD_H

#include <QtWidgets>

class MetricsField : public QWidget {
  Q_OBJECT

public:
  MetricsField(QString name);

  void update(double value);

private:
  double value;
  QLabel *label;
};


#endif
