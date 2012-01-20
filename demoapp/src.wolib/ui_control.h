/********************************************************************************
** Form generated from reading UI file 'control.ui'
**
** Created: Sun 15. Jan 22:02:24 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROL_H
#define UI_CONTROL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Control
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QPushButton *zoominButton;
    QPushButton *zoomoutButton;
    QCheckBox *waypointsCheckBox;
    QCheckBox *showDirectionCheckBox;
    QCheckBox *showForcesCheckBox;
    QLabel *label_5;
    QSlider *simspeedSlider;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *mlTendencyCheckBox;
    QCheckBox *mlLookAheadCheckBox;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_3;
    QSpacerItem *verticalSpacer_4;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_9;
    QSlider *simhSlider;
    QLabel *label_2;
    QSlider *wallforceSlider;
    QLabel *label_4;
    QSlider *pedforceSlider;
    QSpacerItem *verticalSpacer;

    void setupUi(QDockWidget *Control)
    {
        if (Control->objectName().isEmpty())
            Control->setObjectName(QString::fromUtf8("Control"));
        Control->resize(200, 673);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Control->sizePolicy().hasHeightForWidth());
        Control->setSizePolicy(sizePolicy);
        Control->setMinimumSize(QSize(200, 175));
        Control->setAutoFillBackground(false);
        Control->setStyleSheet(QString::fromUtf8(""));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dockWidgetContents->sizePolicy().hasHeightForWidth());
        dockWidgetContents->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(dockWidgetContents);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMaximumSize(QSize(16777215, 40));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);


        verticalLayout->addWidget(frame);

        groupBox = new QGroupBox(dockWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        frame_2 = new QFrame(groupBox);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMinimumSize(QSize(0, 40));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Plain);
        horizontalLayout = new QHBoxLayout(frame_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_6 = new QLabel(frame_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout->addWidget(label_6);

        zoominButton = new QPushButton(frame_2);
        zoominButton->setObjectName(QString::fromUtf8("zoominButton"));
        zoominButton->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(zoominButton);

        zoomoutButton = new QPushButton(frame_2);
        zoomoutButton->setObjectName(QString::fromUtf8("zoomoutButton"));
        zoomoutButton->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(zoomoutButton);


        verticalLayout_5->addWidget(frame_2);

        waypointsCheckBox = new QCheckBox(groupBox);
        waypointsCheckBox->setObjectName(QString::fromUtf8("waypointsCheckBox"));

        verticalLayout_5->addWidget(waypointsCheckBox);

        showDirectionCheckBox = new QCheckBox(groupBox);
        showDirectionCheckBox->setObjectName(QString::fromUtf8("showDirectionCheckBox"));
        showDirectionCheckBox->setEnabled(true);

        verticalLayout_5->addWidget(showDirectionCheckBox);

        showForcesCheckBox = new QCheckBox(groupBox);
        showForcesCheckBox->setObjectName(QString::fromUtf8("showForcesCheckBox"));

        verticalLayout_5->addWidget(showForcesCheckBox);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_5->addWidget(label_5);

        simspeedSlider = new QSlider(groupBox);
        simspeedSlider->setObjectName(QString::fromUtf8("simspeedSlider"));
        simspeedSlider->setMinimum(1);
        simspeedSlider->setMaximum(50);
        simspeedSlider->setValue(20);
        simspeedSlider->setOrientation(Qt::Horizontal);

        verticalLayout_5->addWidget(simspeedSlider);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        showDirectionCheckBox->raise();
        waypointsCheckBox->raise();
        frame_2->raise();
        label_5->raise();
        simspeedSlider->raise();
        showForcesCheckBox->raise();

        verticalLayout->addWidget(groupBox);

        groupBox_4 = new QGroupBox(dockWidgetContents);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(0, 0));
        verticalLayout_6 = new QVBoxLayout(groupBox_4);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        mlTendencyCheckBox = new QCheckBox(groupBox_4);
        mlTendencyCheckBox->setObjectName(QString::fromUtf8("mlTendencyCheckBox"));
        mlTendencyCheckBox->setChecked(false);

        verticalLayout_6->addWidget(mlTendencyCheckBox);

        mlLookAheadCheckBox = new QCheckBox(groupBox_4);
        mlLookAheadCheckBox->setObjectName(QString::fromUtf8("mlLookAheadCheckBox"));
        mlLookAheadCheckBox->setEnabled(true);

        verticalLayout_6->addWidget(mlLookAheadCheckBox);

        checkBox_4 = new QCheckBox(groupBox_4);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setEnabled(false);

        verticalLayout_6->addWidget(checkBox_4);

        checkBox_3 = new QCheckBox(groupBox_4);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setEnabled(false);

        verticalLayout_6->addWidget(checkBox_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_4);


        verticalLayout->addWidget(groupBox_4);

        groupBox_2 = new QGroupBox(dockWidgetContents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout_4->addWidget(label_9);

        simhSlider = new QSlider(groupBox_2);
        simhSlider->setObjectName(QString::fromUtf8("simhSlider"));
        simhSlider->setMaximum(100);
        simhSlider->setValue(40);
        simhSlider->setOrientation(Qt::Horizontal);
        simhSlider->setInvertedAppearance(true);
        simhSlider->setInvertedControls(false);

        verticalLayout_4->addWidget(simhSlider);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_4->addWidget(label_2);

        wallforceSlider = new QSlider(groupBox_2);
        wallforceSlider->setObjectName(QString::fromUtf8("wallforceSlider"));
        wallforceSlider->setMinimum(10);
        wallforceSlider->setMaximum(500);
        wallforceSlider->setValue(100);
        wallforceSlider->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(wallforceSlider);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_4->addWidget(label_4);

        pedforceSlider = new QSlider(groupBox_2);
        pedforceSlider->setObjectName(QString::fromUtf8("pedforceSlider"));
        pedforceSlider->setMinimum(10);
        pedforceSlider->setMaximum(500);
        pedforceSlider->setValue(100);
        pedforceSlider->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(pedforceSlider);

        verticalSpacer = new QSpacerItem(20, 252, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        verticalLayout->addWidget(groupBox_2);

        Control->setWidget(dockWidgetContents);

        retranslateUi(Control);

        QMetaObject::connectSlotsByName(Control);
    } // setupUi

    void retranslateUi(QDockWidget *Control)
    {
        Control->setWindowTitle(QApplication::translate("Control", "PedSim Control", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Control", "<font color=\"white\">PedSim v2.1 Demo</font>", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Control", "Display Options", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Control", "Zoom Level", 0, QApplication::UnicodeUTF8));
        zoominButton->setText(QApplication::translate("Control", "+", 0, QApplication::UnicodeUTF8));
        zoomoutButton->setText(QApplication::translate("Control", "-", 0, QApplication::UnicodeUTF8));
        waypointsCheckBox->setText(QApplication::translate("Control", "Show Waypoints", 0, QApplication::UnicodeUTF8));
        showDirectionCheckBox->setText(QApplication::translate("Control", "Show Direction", 0, QApplication::UnicodeUTF8));
        showForcesCheckBox->setText(QApplication::translate("Control", "Show Forces", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Control", "Framerate", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("Control", "Mental Layer Options", 0, QApplication::UnicodeUTF8));
        mlTendencyCheckBox->setText(QApplication::translate("Control", "Tendency Strategy", 0, QApplication::UnicodeUTF8));
        mlLookAheadCheckBox->setText(QApplication::translate("Control", "Look Ahead", 0, QApplication::UnicodeUTF8));
        checkBox_4->setText(QApplication::translate("Control", "Dijkstra Routing", 0, QApplication::UnicodeUTF8));
        checkBox_3->setText(QApplication::translate("Control", "Visual Avoidance", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("Control", "Physical Layer Options", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Control", "Precision (h)", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Control", "Wall Force", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Control", "Pedestrian Force", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Control: public Ui_Control {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROL_H
