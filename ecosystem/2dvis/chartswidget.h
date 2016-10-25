#ifndef CHARTSWIDGET_H
#define CHARTSWIDGET_H

#include <QtWidgets>

class ChartsField;

class ChartsWidget : public QWidget {
  Q_OBJECT

public:
  ChartsWidget();

  void update(long timestep, QString name, double value);
  void clear();

private:
  QHash<QString, ChartsField*> charts;
  QHBoxLayout *layout;

};


#endif
