#include <QtWidgets>

#include "metricsfield.h"


MetricsField::MetricsField(QString name)  {
  value = 0.0;

  
  QGroupBox *groupbox = new QGroupBox(name);
  label = new QLabel(QString::number(value));

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(label);
  groupbox->setLayout(vbox);
  
  QVBoxLayout *layout;
  layout = new QVBoxLayout();

  layout->addWidget(groupbox);

  setLayout(layout);


}

void MetricsField::update(double pvalue) {
  value = pvalue;
  label->setText(QString::number(value));
}
