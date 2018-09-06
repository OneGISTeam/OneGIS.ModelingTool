/********************************************************************************
** Form generated from reading UI file 'timeAxisViewWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMEAXISVIEWWIDGET_H
#define UI_TIMEAXISVIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDockWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewWidgetTimeAxis
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *framePlotLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *currentTimeLabel;
    QCheckBox *cbFixTimePoint;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton_play;
    QToolButton *toolButton_reset;
    QToolButton *toolButton_speedDown;
    QToolButton *toolButton_speedUp;
    QToolButton *toolButton_backward;
    QToolButton *toolButton_forward;
    QSpacerItem *verticalSpacer;

    void setupUi(QDockWidget *ViewWidgetTimeAxis)
    {
        if (ViewWidgetTimeAxis->objectName().isEmpty())
            ViewWidgetTimeAxis->setObjectName(QString::fromUtf8("ViewWidgetTimeAxis"));
        ViewWidgetTimeAxis->resize(436, 141);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ViewWidgetTimeAxis->sizePolicy().hasHeightForWidth());
        ViewWidgetTimeAxis->setSizePolicy(sizePolicy);
        ViewWidgetTimeAxis->setFloating(false);
        ViewWidgetTimeAxis->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
        centralWidget = new QWidget();
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(1);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
        gridLayout->setContentsMargins(3, 1, 3, 1);
        framePlotLayout = new QHBoxLayout();
        framePlotLayout->setSpacing(0);
        framePlotLayout->setObjectName(QString::fromUtf8("framePlotLayout"));
        framePlotLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        currentTimeLabel = new QLabel(centralWidget);
        currentTimeLabel->setObjectName(QString::fromUtf8("currentTimeLabel"));

        verticalLayout->addWidget(currentTimeLabel);

        cbFixTimePoint = new QCheckBox(centralWidget);
        cbFixTimePoint->setObjectName(QString::fromUtf8("cbFixTimePoint"));

        verticalLayout->addWidget(cbFixTimePoint);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(15);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        toolButton_play = new QToolButton(centralWidget);
        toolButton_play->setObjectName(QString::fromUtf8("toolButton_play"));
        toolButton_play->setMinimumSize(QSize(30, 30));
        toolButton_play->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_play->setIcon(icon);
        toolButton_play->setIconSize(QSize(30, 30));
        toolButton_play->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_play);

        toolButton_reset = new QToolButton(centralWidget);
        toolButton_reset->setObjectName(QString::fromUtf8("toolButton_reset"));
        toolButton_reset->setMinimumSize(QSize(30, 30));
        toolButton_reset->setMaximumSize(QSize(30, 30));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/reset.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_reset->setIcon(icon1);
        toolButton_reset->setIconSize(QSize(30, 30));
        toolButton_reset->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_reset);

        toolButton_speedDown = new QToolButton(centralWidget);
        toolButton_speedDown->setObjectName(QString::fromUtf8("toolButton_speedDown"));
        toolButton_speedDown->setMinimumSize(QSize(30, 30));
        toolButton_speedDown->setMaximumSize(QSize(30, 30));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/speedDown.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_speedDown->setIcon(icon2);
        toolButton_speedDown->setIconSize(QSize(30, 30));
        toolButton_speedDown->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_speedDown);

        toolButton_speedUp = new QToolButton(centralWidget);
        toolButton_speedUp->setObjectName(QString::fromUtf8("toolButton_speedUp"));
        toolButton_speedUp->setMinimumSize(QSize(30, 30));
        toolButton_speedUp->setMaximumSize(QSize(30, 30));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ModelingTool/Images/speedUp.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_speedUp->setIcon(icon3);
        toolButton_speedUp->setIconSize(QSize(30, 30));
        toolButton_speedUp->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_speedUp);

        toolButton_backward = new QToolButton(centralWidget);
        toolButton_backward->setObjectName(QString::fromUtf8("toolButton_backward"));
        toolButton_backward->setMinimumSize(QSize(30, 30));
        toolButton_backward->setMaximumSize(QSize(30, 30));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ModelingTool/Images/backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_backward->setIcon(icon4);
        toolButton_backward->setIconSize(QSize(30, 30));
        toolButton_backward->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_backward);

        toolButton_forward = new QToolButton(centralWidget);
        toolButton_forward->setObjectName(QString::fromUtf8("toolButton_forward"));
        toolButton_forward->setMinimumSize(QSize(30, 30));
        toolButton_forward->setMaximumSize(QSize(30, 30));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/ModelingTool/Images/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_forward->setIcon(icon5);
        toolButton_forward->setIconSize(QSize(30, 30));
        toolButton_forward->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_forward);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        framePlotLayout->addLayout(verticalLayout);


        gridLayout->addLayout(framePlotLayout, 0, 0, 1, 1);

        ViewWidgetTimeAxis->setWidget(centralWidget);

        retranslateUi(ViewWidgetTimeAxis);

        QMetaObject::connectSlotsByName(ViewWidgetTimeAxis);
    } // setupUi

    void retranslateUi(QDockWidget *ViewWidgetTimeAxis)
    {
        ViewWidgetTimeAxis->setWindowTitle(QApplication::translate("ViewWidgetTimeAxis", "\346\227\266\351\227\264\350\275\264\347\252\227\345\217\243", 0, QApplication::UnicodeUTF8));
        currentTimeLabel->setText(QApplication::translate("ViewWidgetTimeAxis", "\345\275\223\345\211\215\346\227\266\351\227\264\357\274\232XXXX\345\271\264XX\346\234\210XX\346\227\245hh:mm:ss", 0, QApplication::UnicodeUTF8));
        cbFixTimePoint->setText(QApplication::translate("ViewWidgetTimeAxis", "\345\233\272\345\256\232\346\227\266\351\227\264\346\214\207\351\222\210", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        toolButton_play->setStatusTip(QApplication::translate("ViewWidgetTimeAxis", "\346\222\255\346\224\276/\346\232\202\345\201\234", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        toolButton_play->setText(QString());
#ifndef QT_NO_STATUSTIP
        toolButton_reset->setStatusTip(QApplication::translate("ViewWidgetTimeAxis", "\351\207\215\347\275\256", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        toolButton_reset->setText(QString());
#ifndef QT_NO_STATUSTIP
        toolButton_speedDown->setStatusTip(QApplication::translate("ViewWidgetTimeAxis", "\346\224\276\346\205\242\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        toolButton_speedDown->setText(QString());
#ifndef QT_NO_STATUSTIP
        toolButton_speedUp->setStatusTip(QApplication::translate("ViewWidgetTimeAxis", "\345\212\240\345\277\253\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        toolButton_speedUp->setText(QString());
#ifndef QT_NO_STATUSTIP
        toolButton_backward->setStatusTip(QApplication::translate("ViewWidgetTimeAxis", "\345\220\216\351\200\200", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        toolButton_backward->setText(QString());
#ifndef QT_NO_STATUSTIP
        toolButton_forward->setStatusTip(QApplication::translate("ViewWidgetTimeAxis", "\345\211\215\350\277\233", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        toolButton_forward->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ViewWidgetTimeAxis: public Ui_ViewWidgetTimeAxis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMEAXISVIEWWIDGET_H
