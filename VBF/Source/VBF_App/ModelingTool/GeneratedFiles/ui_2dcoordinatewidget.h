/********************************************************************************
** Form generated from reading UI file '2dcoordinatewidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_2DCOORDINATEWIDGET_H
#define UI_2DCOORDINATEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CoordinateWidget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_coord;
    QLabel *label_2;
    QLineEdit *lineEdit_scale;
    QToolButton *toolButton_srs;
    QToolButton *toolButton_trs;

    void setupUi(QWidget *CoordinateWidget)
    {
        if (CoordinateWidget->objectName().isEmpty())
            CoordinateWidget->setObjectName(QString::fromUtf8("CoordinateWidget"));
        CoordinateWidget->resize(451, 28);
        gridLayout = new QGridLayout(CoordinateWidget);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(CoordinateWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(36, 16777215));

        horizontalLayout->addWidget(label);

        lineEdit_coord = new QLineEdit(CoordinateWidget);
        lineEdit_coord->setObjectName(QString::fromUtf8("lineEdit_coord"));
        lineEdit_coord->setMinimumSize(QSize(150, 0));
        lineEdit_coord->setMaximumSize(QSize(150, 16777215));
        lineEdit_coord->setStyleSheet(QString::fromUtf8("border: 1px solid gray;\n"
"border-radius:0px;\n"
"background:rgba(255,255,255,255);\n"
"selection-background-color: lightgray;"));

        horizontalLayout->addWidget(lineEdit_coord);

        label_2 = new QLabel(CoordinateWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(label_2);

        lineEdit_scale = new QLineEdit(CoordinateWidget);
        lineEdit_scale->setObjectName(QString::fromUtf8("lineEdit_scale"));
        lineEdit_scale->setMinimumSize(QSize(120, 0));
        lineEdit_scale->setMaximumSize(QSize(120, 16777215));
        lineEdit_scale->setStyleSheet(QString::fromUtf8("border: 1px solid gray;\n"
"border-radius:0px;\n"
"background:rgba(255,255,255,255);\n"
"selection-background-color: lightgray;"));

        horizontalLayout->addWidget(lineEdit_scale);

        toolButton_srs = new QToolButton(CoordinateWidget);
        toolButton_srs->setObjectName(QString::fromUtf8("toolButton_srs"));
        toolButton_srs->setMinimumSize(QSize(24, 0));
        toolButton_srs->setMaximumSize(QSize(24, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/SRS.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_srs->setIcon(icon);
        toolButton_srs->setIconSize(QSize(20, 20));
        toolButton_srs->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_srs);

        toolButton_trs = new QToolButton(CoordinateWidget);
        toolButton_trs->setObjectName(QString::fromUtf8("toolButton_trs"));
        toolButton_trs->setMinimumSize(QSize(24, 0));
        toolButton_trs->setMaximumSize(QSize(24, 16777215));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/TRS.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_trs->setIcon(icon1);
        toolButton_trs->setIconSize(QSize(20, 20));
        toolButton_trs->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_trs);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(CoordinateWidget);

        QMetaObject::connectSlotsByName(CoordinateWidget);
    } // setupUi

    void retranslateUi(QWidget *CoordinateWidget)
    {
        CoordinateWidget->setWindowTitle(QApplication::translate("CoordinateWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CoordinateWidget", "\345\235\220\346\240\207\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CoordinateWidget", "\346\257\224\344\276\213\345\260\272\357\274\232", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButton_srs->setToolTip(QApplication::translate("CoordinateWidget", "\350\256\276\347\275\256\347\251\272\351\227\264\345\217\202\347\205\247", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_srs->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_trs->setToolTip(QApplication::translate("CoordinateWidget", "\350\256\276\347\275\256\346\227\266\351\227\264\345\217\202\347\205\247", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_trs->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CoordinateWidget: public Ui_CoordinateWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_2DCOORDINATEWIDGET_H
