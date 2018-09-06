/********************************************************************************
** Form generated from reading UI file 'operaterelationwidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPERATERELATIONWIDGET_H
#define UI_OPERATERELATIONWIDGET_H

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

class Ui_OperateRelationWidget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton_createrelation;
    QToolButton *toolButton_visual;
    QToolButton *toolButton_style;
    QToolButton *toolButton_moveup;
    QToolButton *toolButton_movedown;
    QToolButton *toolButton_remove;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *OperateRelationWidget)
    {
        if (OperateRelationWidget->objectName().isEmpty())
            OperateRelationWidget->setObjectName(QString::fromUtf8("OperateRelationWidget"));
        OperateRelationWidget->resize(222, 26);
        gridLayout = new QGridLayout(OperateRelationWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        toolButton_createrelation = new QToolButton(OperateRelationWidget);
        toolButton_createrelation->setObjectName(QString::fromUtf8("toolButton_createrelation"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/createRelation.ico"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_createrelation->setIcon(icon);
        toolButton_createrelation->setPopupMode(QToolButton::MenuButtonPopup);
        toolButton_createrelation->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_createrelation);

        toolButton_visual = new QToolButton(OperateRelationWidget);
        toolButton_visual->setObjectName(QString::fromUtf8("toolButton_visual"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/visualize.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_visual->setIcon(icon1);
        toolButton_visual->setPopupMode(QToolButton::MenuButtonPopup);
        toolButton_visual->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_visual);

        toolButton_style = new QToolButton(OperateRelationWidget);
        toolButton_style->setObjectName(QString::fromUtf8("toolButton_style"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/brush.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_style->setIcon(icon2);
        toolButton_style->setPopupMode(QToolButton::DelayedPopup);
        toolButton_style->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_style);

        toolButton_moveup = new QToolButton(OperateRelationWidget);
        toolButton_moveup->setObjectName(QString::fromUtf8("toolButton_moveup"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ModelingTool/Images/moveup.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_moveup->setIcon(icon3);
        toolButton_moveup->setPopupMode(QToolButton::DelayedPopup);
        toolButton_moveup->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_moveup);

        toolButton_movedown = new QToolButton(OperateRelationWidget);
        toolButton_movedown->setObjectName(QString::fromUtf8("toolButton_movedown"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ModelingTool/Images/movedowm.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_movedown->setIcon(icon4);
        toolButton_movedown->setPopupMode(QToolButton::DelayedPopup);
        toolButton_movedown->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_movedown);

        toolButton_remove = new QToolButton(OperateRelationWidget);
        toolButton_remove->setObjectName(QString::fromUtf8("toolButton_remove"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/ModelingTool/Images/remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_remove->setIcon(icon5);
        toolButton_remove->setPopupMode(QToolButton::DelayedPopup);
        toolButton_remove->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_remove);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(OperateRelationWidget);

        QMetaObject::connectSlotsByName(OperateRelationWidget);
    } // setupUi

    void retranslateUi(QWidget *OperateRelationWidget)
    {
        OperateRelationWidget->setWindowTitle(QApplication::translate("OperateRelationWidget", "Form", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButton_createrelation->setToolTip(QApplication::translate("OperateRelationWidget", "\345\210\233\345\273\272\345\205\263\350\201\224\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_createrelation->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_visual->setToolTip(QApplication::translate("OperateRelationWidget", "\345\205\263\347\263\273\345\217\257\350\247\206\345\214\226", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_visual->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_style->setToolTip(QApplication::translate("OperateRelationWidget", "\345\205\263\347\263\273\346\240\267\345\274\217", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_style->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_moveup->setToolTip(QApplication::translate("OperateRelationWidget", "\344\270\212\347\247\273", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_moveup->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_movedown->setToolTip(QApplication::translate("OperateRelationWidget", "\344\270\213\347\247\273", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_movedown->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_remove->setToolTip(QApplication::translate("OperateRelationWidget", "\347\247\273\351\231\244", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_remove->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class OperateRelationWidget: public Ui_OperateRelationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPERATERELATIONWIDGET_H
