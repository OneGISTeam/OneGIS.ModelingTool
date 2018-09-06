/********************************************************************************
** Form generated from reading UI file '3dcoordinatewidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_3DCOORDINATEWIDGET_H
#define UI_3DCOORDINATEWIDGET_H

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

class Ui_CoordinateWidget3D
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_coord;
    QLabel *label_2;
    QLineEdit *lineEdit_cameraposition;
    QLabel *label_3;
    QLineEdit *lineEdit_cameraposture;
    QToolButton *toolButton_srs;
    QToolButton *toolButton_trs;

    void setupUi(QWidget *CoordinateWidget3D)
    {
        if (CoordinateWidget3D->objectName().isEmpty())
            CoordinateWidget3D->setObjectName(QString::fromUtf8("CoordinateWidget3D"));
        CoordinateWidget3D->resize(974, 28);
        gridLayout = new QGridLayout(CoordinateWidget3D);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(CoordinateWidget3D);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(40, 16777215));

        horizontalLayout->addWidget(label);

        lineEdit_coord = new QLineEdit(CoordinateWidget3D);
        lineEdit_coord->setObjectName(QString::fromUtf8("lineEdit_coord"));
        lineEdit_coord->setMinimumSize(QSize(200, 0));
        lineEdit_coord->setMaximumSize(QSize(200, 16777215));
        lineEdit_coord->setStyleSheet(QString::fromUtf8("border: 1px solid gray;\n"
"border-radius:0px;\n"
"background:rgba(255,255,255,255);\n"
"selection-background-color: lightgray;"));

        horizontalLayout->addWidget(lineEdit_coord);

        label_2 = new QLabel(CoordinateWidget3D);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(60, 0));
        label_2->setMaximumSize(QSize(75, 16777215));

        horizontalLayout->addWidget(label_2);

        lineEdit_cameraposition = new QLineEdit(CoordinateWidget3D);
        lineEdit_cameraposition->setObjectName(QString::fromUtf8("lineEdit_cameraposition"));
        lineEdit_cameraposition->setMinimumSize(QSize(200, 0));
        lineEdit_cameraposition->setMaximumSize(QSize(200, 16777215));
        lineEdit_cameraposition->setStyleSheet(QString::fromUtf8("border: 1px solid gray;\n"
"border-radius:0px;\n"
"background:rgba(255,255,255,255);\n"
"selection-background-color: lightgray;"));

        horizontalLayout->addWidget(lineEdit_cameraposition);

        label_3 = new QLabel(CoordinateWidget3D);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(60, 0));
        label_3->setMaximumSize(QSize(75, 16777215));

        horizontalLayout->addWidget(label_3);

        lineEdit_cameraposture = new QLineEdit(CoordinateWidget3D);
        lineEdit_cameraposture->setObjectName(QString::fromUtf8("lineEdit_cameraposture"));
        lineEdit_cameraposture->setMinimumSize(QSize(150, 0));
        lineEdit_cameraposture->setMaximumSize(QSize(150, 16777215));
        lineEdit_cameraposture->setStyleSheet(QString::fromUtf8("border: 1px solid gray;\n"
"border-radius:0px;\n"
"background:rgba(255,255,255,255);\n"
"selection-background-color: lightgray;"));

        horizontalLayout->addWidget(lineEdit_cameraposture);

        toolButton_srs = new QToolButton(CoordinateWidget3D);
        toolButton_srs->setObjectName(QString::fromUtf8("toolButton_srs"));
        toolButton_srs->setMinimumSize(QSize(24, 0));
        toolButton_srs->setMaximumSize(QSize(24, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/SRS.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_srs->setIcon(icon);
        toolButton_srs->setIconSize(QSize(20, 20));
        toolButton_srs->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_srs);

        toolButton_trs = new QToolButton(CoordinateWidget3D);
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


        retranslateUi(CoordinateWidget3D);

        QMetaObject::connectSlotsByName(CoordinateWidget3D);
    } // setupUi

    void retranslateUi(QWidget *CoordinateWidget3D)
    {
        CoordinateWidget3D->setWindowTitle(QApplication::translate("CoordinateWidget3D", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CoordinateWidget3D", "\345\235\220\346\240\207\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CoordinateWidget3D", "\347\233\270\346\234\272\344\275\215\347\275\256\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CoordinateWidget3D", "\347\233\270\346\234\272\345\247\277\346\200\201\357\274\232", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButton_srs->setToolTip(QApplication::translate("CoordinateWidget3D", "\350\256\276\347\275\256\347\251\272\351\227\264\345\217\202\347\205\247", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_srs->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_trs->setToolTip(QApplication::translate("CoordinateWidget3D", "\350\256\276\347\275\256\346\227\266\351\227\264\345\217\202\347\205\247", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_trs->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CoordinateWidget3D: public Ui_CoordinateWidget3D {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_3DCOORDINATEWIDGET_H
