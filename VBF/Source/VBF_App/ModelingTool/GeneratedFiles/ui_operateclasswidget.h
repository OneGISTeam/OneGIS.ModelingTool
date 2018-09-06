/********************************************************************************
** Form generated from reading UI file 'operateclasswidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPERATECLASSWIDGET_H
#define UI_OPERATECLASSWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OperateClassWidget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_style;
    QPushButton *pushButton_traits;
    QPushButton *pushButton_visible;
    QPushButton *pushButton_moveup;
    QPushButton *pushButton_movedown;
    QPushButton *pushButton_remove;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *OperateClassWidget)
    {
        if (OperateClassWidget->objectName().isEmpty())
            OperateClassWidget->setObjectName(QString::fromUtf8("OperateClassWidget"));
        OperateClassWidget->resize(222, 26);
        gridLayout = new QGridLayout(OperateClassWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_style = new QPushButton(OperateClassWidget);
        pushButton_style->setObjectName(QString::fromUtf8("pushButton_style"));
        pushButton_style->setMinimumSize(QSize(24, 24));
        pushButton_style->setMaximumSize(QSize(24, 24));
        pushButton_style->setStyleSheet(QString::fromUtf8(""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/brush.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_style->setIcon(icon);
        pushButton_style->setIconSize(QSize(16, 16));
        pushButton_style->setFlat(true);

        horizontalLayout->addWidget(pushButton_style);

        pushButton_traits = new QPushButton(OperateClassWidget);
        pushButton_traits->setObjectName(QString::fromUtf8("pushButton_traits"));
        pushButton_traits->setMinimumSize(QSize(24, 24));
        pushButton_traits->setMaximumSize(QSize(24, 24));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/traits.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_traits->setIcon(icon1);
        pushButton_traits->setIconSize(QSize(16, 16));
        pushButton_traits->setFlat(true);

        horizontalLayout->addWidget(pushButton_traits);

        pushButton_visible = new QPushButton(OperateClassWidget);
        pushButton_visible->setObjectName(QString::fromUtf8("pushButton_visible"));
        pushButton_visible->setMinimumSize(QSize(24, 24));
        pushButton_visible->setMaximumSize(QSize(24, 24));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/visible.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_visible->setIcon(icon2);
        pushButton_visible->setIconSize(QSize(16, 16));
        pushButton_visible->setFlat(true);

        horizontalLayout->addWidget(pushButton_visible);

        pushButton_moveup = new QPushButton(OperateClassWidget);
        pushButton_moveup->setObjectName(QString::fromUtf8("pushButton_moveup"));
        pushButton_moveup->setMinimumSize(QSize(24, 24));
        pushButton_moveup->setMaximumSize(QSize(24, 24));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ModelingTool/Images/moveup.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_moveup->setIcon(icon3);
        pushButton_moveup->setIconSize(QSize(16, 16));
        pushButton_moveup->setFlat(true);

        horizontalLayout->addWidget(pushButton_moveup);

        pushButton_movedown = new QPushButton(OperateClassWidget);
        pushButton_movedown->setObjectName(QString::fromUtf8("pushButton_movedown"));
        pushButton_movedown->setMinimumSize(QSize(24, 24));
        pushButton_movedown->setMaximumSize(QSize(24, 24));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ModelingTool/Images/movedowm.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_movedown->setIcon(icon4);
        pushButton_movedown->setIconSize(QSize(16, 16));
        pushButton_movedown->setFlat(true);

        horizontalLayout->addWidget(pushButton_movedown);

        pushButton_remove = new QPushButton(OperateClassWidget);
        pushButton_remove->setObjectName(QString::fromUtf8("pushButton_remove"));
        pushButton_remove->setMinimumSize(QSize(24, 24));
        pushButton_remove->setMaximumSize(QSize(24, 24));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/ModelingTool/Images/remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_remove->setIcon(icon5);
        pushButton_remove->setIconSize(QSize(16, 16));
        pushButton_remove->setFlat(true);

        horizontalLayout->addWidget(pushButton_remove);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(OperateClassWidget);

        QMetaObject::connectSlotsByName(OperateClassWidget);
    } // setupUi

    void retranslateUi(QWidget *OperateClassWidget)
    {
        OperateClassWidget->setWindowTitle(QApplication::translate("OperateClassWidget", "Form", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_style->setToolTip(QApplication::translate("OperateClassWidget", "\346\211\223\345\274\200\346\240\267\345\274\217\350\241\250", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_style->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_traits->setToolTip(QApplication::translate("OperateClassWidget", "\346\237\245\347\234\213\347\211\271\345\276\201\351\241\271", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_traits->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_visible->setToolTip(QApplication::translate("OperateClassWidget", "\345\217\257\350\247\201\346\200\247", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_visible->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_moveup->setToolTip(QApplication::translate("OperateClassWidget", "\344\270\212\347\247\273", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_moveup->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_movedown->setToolTip(QApplication::translate("OperateClassWidget", "\344\270\213\347\247\273", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_movedown->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_remove->setToolTip(QApplication::translate("OperateClassWidget", "\347\247\273\351\231\244\345\257\271\350\261\241", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_remove->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class OperateClassWidget: public Ui_OperateClassWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPERATECLASSWIDGET_H
