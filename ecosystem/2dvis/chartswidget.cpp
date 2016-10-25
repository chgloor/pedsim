#include <QtWidgets>

#include "chartswidget.h"
#include "chartsfield.h"


ChartsWidget::ChartsWidget() {
  layout = new QHBoxLayout;
  setLayout(layout);
};

void ChartsWidget::update(long timestep, QString name, double value) {
  if (charts.contains(name)) {
    charts[name]->update(timestep, value);
  } else {
    charts[name] = new ChartsField(name);
    layout->addWidget(charts[name]);
  }
}

void ChartsWidget::clear() {
  foreach (QWidget* value, charts) {
    layout->removeWidget(value);
    delete value;
  }
  charts.clear();
}
