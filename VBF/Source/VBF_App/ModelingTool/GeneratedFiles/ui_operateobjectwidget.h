/********************************************************************************
** Form generated from reading UI file 'operateobjectwidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPERATEOBJECTWIDGET_H
#define UI_OPERATEOBJECTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OperateObjectWidget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton_style;
    QToolButton *toolButton_traits;
    QToolButton *toolButton_visible;
    QToolButton *toolButton_moveup;
    QToolButton *toolButton_movedown;
    QToolButton *toolButton_remove;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *OperateObjectWidget)
    {
        if (OperateObjectWidget->objectName().isEmpty())
            OperateObjectWidget->setObjectName(QString::fromUtf8("OperateObjectWidget"));
        OperateObjectWidget->resize(222, 26);
        gridLayout = new QGridLayout(OperateObjectWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        toolButton_style = new QToolButton(OperateObjectWidget);
        toolButton_style->setObjectName(QString::fromUtf8("toolButton_style"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/brush.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_style->setIcon(icon);
        toolButton_style->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_style);

        toolButton_traits = new QToolButton(OperateObjectWidget);
        toolButton_traits->setObjectName(QString::fromUtf8("toolButton_traits"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/traits.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_traits->setIcon(icon1);
        toolButton_traits->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_traits);

        toolButton_visible = new QToolButton(OperateObjectWidget);
        toolButton_visible->setObjectName(QString::fromUtf8("toolButton_visible"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/visible.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_visible->setIcon(icon2);
        toolButton_visible->setPopupMode(QToolButton::MenuButtonPopup);
        toolButton_visible->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_visible);

        toolButton_moveup = new QToolButton(OperateObjectWidget);
        toolButton_moveup->setObjectName(QString::fromUtf8("toolButton_moveup"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ModelingTool/Images/moveup.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_moveup->setIcon(icon3);
        toolButton_moveup->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_moveup);

        toolButton_movedown = new QToolButton(OperateObjectWidget);
        toolButton_movedown->setObjectName(QString::fromUtf8("toolButton_movedown"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ModelingTool/Images/movedowm.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_movedown->setIcon(icon4);
        toolButton_movedown->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_movedown);

        toolButton_remove = new QToolButton(OperateObjectWidget);
        toolButton_remove->setObjectName(QString::fromUtf8("toolButton_remove"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/ModelingTool/Images/remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_remove->setIcon(icon5);
        toolButton_remove->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_remove);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(OperateObjectWidget);

        QMetaObject::connectSlotsByName(OperateObjectWidget);
    } // setupUi

    void retranslateUi(QWidget *OperateObjectWidget)
    {
        OperateObjectWidget->setWindowTitle(QApplication::translate("OperateObjectWidget", "Form", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButton_style->setToolTip(QApplication::translate("OperateObjectWidget", "\345\257\271\350\261\241\346\240\267\345\274\217", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_style->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_traits->setToolTip(QApplication::translate("OperateObjectWidget", "\346\237\245\347\234\213\347\211\271\345\276\201\351\241\271", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_traits->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_visible->setToolTip(QApplication::translate("OperateObjectWidget", "\345\217\257\350\247\201\346\200\247", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_visible->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_moveup->setToolTip(QApplication::translate("OperateObjectWidget", "\344\270\212\347\247\273", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_moveup->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_movedown->setToolTip(QApplication::translate("OperateObjectWidget", "\344\270\213\347\247\273", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_movedown->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_remove->setToolTip(QApplication::translate("OperateObjectWidget", "\347\247\273\351\231\244\345\257\271\350\261\241", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_remove->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class OperateObjectWidget: public Ui_OperateObjectWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPERATEOBJECTWIDGET_H
