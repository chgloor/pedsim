#include <QtWidgets>

#include "metricswidget.h"
#include "metricsfield.h"



MetricsWidget::MetricsWidget() {

  //  MetricsField *button1 = new MetricsField("Timestep");
  QSpacerItem *spacer = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
  
  layout = new QVBoxLayout;

    layout->addItem(spacer);
  //  layout->addWidget(button1);

  setLayout(layout);
};

void MetricsWidget::update(QString name, double value) {
  if (metrics.contains(name)) {
    metrics[name]->update(value);
  } else {
    metrics[name] = new MetricsField(name);
    layout->addWidget(metrics[name]);
  }
}

void MetricsWidget::clear() {
  foreach (QWidget* value, metrics) {
    layout->removeWidget(value);
    delete value;
  }
  metrics.clear();
}
