/********************************************************************************
** Form generated from reading UI file 'setSimulationTimeDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETSIMULATIONTIMEDIALOG_H
#define UI_SETSIMULATIONTIMEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_setSimulationTimeDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_5;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_7;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_8;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_9;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QDateTimeEdit *dateTimeEdit;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_11;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QDateTimeEdit *dateTimeEdit_2;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_12;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QSpinBox *spinBox;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_13;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_5;
    QSpinBox *spinBox_2;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_6;
    QSpinBox *spinBox_5;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QDialog *setSimulationTimeDialog)
    {
        if (setSimulationTimeDialog->objectName().isEmpty())
            setSimulationTimeDialog->setObjectName(QString::fromUtf8("setSimulationTimeDialog"));
        setSimulationTimeDialog->resize(498, 223);
        layoutWidget = new QWidget(setSimulationTimeDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        layoutWidget1 = new QWidget(setSimulationTimeDialog);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        layoutWidget2 = new QWidget(setSimulationTimeDialog);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        layoutWidget3 = new QWidget(setSimulationTimeDialog);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(setSimulationTimeDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 491, 221));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));

        gridLayout_2->addLayout(horizontalLayout_9, 0, 0, 1, 1);

        scrollArea = new QScrollArea(widget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 479, 209));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        dateTimeEdit = new QDateTimeEdit(scrollAreaWidgetContents);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));

        horizontalLayout_2->addWidget(dateTimeEdit);


        horizontalLayout->addLayout(horizontalLayout_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        dateTimeEdit_2 = new QDateTimeEdit(scrollAreaWidgetContents);
        dateTimeEdit_2->setObjectName(QString::fromUtf8("dateTimeEdit_2"));

        horizontalLayout_3->addWidget(dateTimeEdit_2);


        horizontalLayout_11->addLayout(horizontalLayout_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_11, 1, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_4 = new QLabel(scrollAreaWidgetContents);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_6->addWidget(label_4);

        spinBox = new QSpinBox(scrollAreaWidgetContents);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        horizontalLayout_6->addWidget(spinBox);


        horizontalLayout_12->addLayout(horizontalLayout_6);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_12, 2, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_5 = new QLabel(scrollAreaWidgetContents);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_10->addWidget(label_5);

        spinBox_2 = new QSpinBox(scrollAreaWidgetContents);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));

        horizontalLayout_10->addWidget(spinBox_2);


        horizontalLayout_13->addLayout(horizontalLayout_10);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_13, 3, 0, 1, 1);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_6 = new QLabel(scrollAreaWidgetContents);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_14->addWidget(label_6);

        spinBox_5 = new QSpinBox(scrollAreaWidgetContents);
        spinBox_5->setObjectName(QString::fromUtf8("spinBox_5"));

        horizontalLayout_14->addWidget(spinBox_5);

        label_8 = new QLabel(scrollAreaWidgetContents);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_14->addWidget(label_8);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_5);


        gridLayout->addLayout(horizontalLayout_14, 4, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();

        gridLayout_2->addWidget(scrollArea, 1, 1, 1, 1);

        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        scrollArea->raise();

        retranslateUi(setSimulationTimeDialog);

        QMetaObject::connectSlotsByName(setSimulationTimeDialog);
    } // setupUi

    void retranslateUi(QDialog *setSimulationTimeDialog)
    {
        setSimulationTimeDialog->setWindowTitle(QApplication::translate("setSimulationTimeDialog", "\344\273\277\347\234\237\346\227\266\351\227\264\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("setSimulationTimeDialog", "\346\227\266\351\227\264\350\265\267\347\202\271\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("setSimulationTimeDialog", "\346\227\266\351\227\264\347\273\210\347\202\271\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("setSimulationTimeDialog", "\346\227\266\351\227\264\346\257\224\347\216\207\357\274\232", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("setSimulationTimeDialog", "\350\267\263\345\212\250\345\200\215\347\216\207\357\274\232", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("setSimulationTimeDialog", "\350\267\263\345\212\250\346\255\245\351\225\277\357\274\232", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("setSimulationTimeDialog", "\346\227\245\357\274\210\345\204\222\347\225\245\346\227\245\357\274\211", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class setSimulationTimeDialog: public Ui_setSimulationTimeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETSIMULATIONTIMEDIALOG_H
