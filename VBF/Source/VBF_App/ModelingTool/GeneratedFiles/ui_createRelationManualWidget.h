/********************************************************************************
** Form generated from reading UI file 'createRelationManualWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATERELATIONMANUALWIDGET_H
#define UI_CREATERELATIONMANUALWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateRelationManualWidget
{
public:
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_operate;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton_pick;
    QRadioButton *radioButton_drawline;
    QFrame *line;
    QToolButton *toolButton_exchange;
    QToolButton *toolButton_create;
    QGroupBox *groupBox_nodes;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
    QFrame *line_2;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QToolButton *toolButton_5;
    QToolButton *toolButton_6;

    void setupUi(QDockWidget *CreateRelationManualWidget)
    {
        if (CreateRelationManualWidget->objectName().isEmpty())
            CreateRelationManualWidget->setObjectName(QString::fromUtf8("CreateRelationManualWidget"));
        CreateRelationManualWidget->resize(918, 93);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/manualCreateRelation.png"), QSize(), QIcon::Normal, QIcon::Off);
        CreateRelationManualWidget->setWindowIcon(icon);
        CreateRelationManualWidget->setAllowedAreas(Qt::TopDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout_3 = new QGridLayout(dockWidgetContents);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        groupBox_operate = new QGroupBox(dockWidgetContents);
        groupBox_operate->setObjectName(QString::fromUtf8("groupBox_operate"));
        gridLayout = new QGridLayout(groupBox_operate);
        gridLayout->setSpacing(2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(3, 3, 2, 2);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioButton_pick = new QRadioButton(groupBox_operate);
        radioButton_pick->setObjectName(QString::fromUtf8("radioButton_pick"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/selectByPick.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioButton_pick->setIcon(icon1);

        horizontalLayout->addWidget(radioButton_pick);

        radioButton_drawline = new QRadioButton(groupBox_operate);
        radioButton_drawline->setObjectName(QString::fromUtf8("radioButton_drawline"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/selectByDraw.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioButton_drawline->setIcon(icon2);

        horizontalLayout->addWidget(radioButton_drawline);

        line = new QFrame(groupBox_operate);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        toolButton_exchange = new QToolButton(groupBox_operate);
        toolButton_exchange->setObjectName(QString::fromUtf8("toolButton_exchange"));
        toolButton_exchange->setMinimumSize(QSize(30, 30));
        toolButton_exchange->setMaximumSize(QSize(30, 30));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ModelingTool/Images/exchange.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_exchange->setIcon(icon3);
        toolButton_exchange->setIconSize(QSize(24, 24));
        toolButton_exchange->setCheckable(false);
        toolButton_exchange->setChecked(false);
        toolButton_exchange->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_exchange);

        toolButton_create = new QToolButton(groupBox_operate);
        toolButton_create->setObjectName(QString::fromUtf8("toolButton_create"));
        toolButton_create->setMinimumSize(QSize(30, 30));
        toolButton_create->setMaximumSize(QSize(30, 30));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ModelingTool/Images/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_create->setIcon(icon4);
        toolButton_create->setIconSize(QSize(24, 24));
        toolButton_create->setCheckable(false);
        toolButton_create->setChecked(false);
        toolButton_create->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_create);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        horizontalLayout_3->addWidget(groupBox_operate);

        groupBox_nodes = new QGroupBox(dockWidgetContents);
        groupBox_nodes->setObjectName(QString::fromUtf8("groupBox_nodes"));
        gridLayout_2 = new QGridLayout(groupBox_nodes);
        gridLayout_2->setSpacing(2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(3, 3, 2, 2);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(groupBox_nodes);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(groupBox_nodes);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setStyleSheet(QString::fromUtf8("border: 1px solid gray;\n"
"border-radius:0px;\n"
"background:rgba(255,255,255,255);\n"
"selection-background-color: lightgray;"));

        horizontalLayout_2->addWidget(lineEdit);

        toolButton_3 = new QToolButton(groupBox_nodes);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        toolButton_3->setMinimumSize(QSize(30, 30));
        toolButton_3->setMaximumSize(QSize(30, 30));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/ModelingTool/Images/select.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_3->setIcon(icon5);
        toolButton_3->setIconSize(QSize(24, 24));
        toolButton_3->setCheckable(true);
        toolButton_3->setChecked(false);
        toolButton_3->setToolButtonStyle(Qt::ToolButtonIconOnly);
        toolButton_3->setAutoRaise(true);

        horizontalLayout_2->addWidget(toolButton_3);

        toolButton_4 = new QToolButton(groupBox_nodes);
        toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));
        toolButton_4->setMinimumSize(QSize(30, 30));
        toolButton_4->setMaximumSize(QSize(30, 30));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/ModelingTool/Images/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_4->setIcon(icon6);
        toolButton_4->setIconSize(QSize(24, 24));
        toolButton_4->setCheckable(false);
        toolButton_4->setChecked(false);
        toolButton_4->setAutoRaise(true);

        horizontalLayout_2->addWidget(toolButton_4);

        line_2 = new QFrame(groupBox_nodes);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_2);

        label_2 = new QLabel(groupBox_nodes);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_2 = new QLineEdit(groupBox_nodes);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setStyleSheet(QString::fromUtf8("border: 1px solid gray;\n"
"border-radius:0px;\n"
"background:rgba(255,255,255,255);\n"
"selection-background-color: lightgray;"));

        horizontalLayout_2->addWidget(lineEdit_2);

        toolButton_5 = new QToolButton(groupBox_nodes);
        toolButton_5->setObjectName(QString::fromUtf8("toolButton_5"));
        toolButton_5->setMinimumSize(QSize(30, 30));
        toolButton_5->setMaximumSize(QSize(30, 30));
        toolButton_5->setIcon(icon5);
        toolButton_5->setIconSize(QSize(24, 24));
        toolButton_5->setCheckable(true);
        toolButton_5->setChecked(false);
        toolButton_5->setToolButtonStyle(Qt::ToolButtonIconOnly);
        toolButton_5->setAutoRaise(true);

        horizontalLayout_2->addWidget(toolButton_5);

        toolButton_6 = new QToolButton(groupBox_nodes);
        toolButton_6->setObjectName(QString::fromUtf8("toolButton_6"));
        toolButton_6->setMinimumSize(QSize(30, 30));
        toolButton_6->setMaximumSize(QSize(30, 30));
        toolButton_6->setIcon(icon6);
        toolButton_6->setIconSize(QSize(24, 24));
        toolButton_6->setCheckable(false);
        toolButton_6->setChecked(false);
        toolButton_6->setAutoRaise(true);

        horizontalLayout_2->addWidget(toolButton_6);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);


        horizontalLayout_3->addWidget(groupBox_nodes);


        gridLayout_3->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        CreateRelationManualWidget->setWidget(dockWidgetContents);

        retranslateUi(CreateRelationManualWidget);

        QMetaObject::connectSlotsByName(CreateRelationManualWidget);
    } // setupUi

    void retranslateUi(QDockWidget *CreateRelationManualWidget)
    {
        CreateRelationManualWidget->setWindowTitle(QApplication::translate("CreateRelationManualWidget", "\346\211\213\345\212\250\345\210\233\345\273\272\345\205\263\350\201\224\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
        groupBox_operate->setTitle(QApplication::translate("CreateRelationManualWidget", "\346\223\215\344\275\234\346\240\217", 0, QApplication::UnicodeUTF8));
        radioButton_pick->setText(QApplication::translate("CreateRelationManualWidget", "\347\202\271\351\200\211", 0, QApplication::UnicodeUTF8));
        radioButton_drawline->setText(QApplication::translate("CreateRelationManualWidget", "\350\277\236\347\272\277", 0, QApplication::UnicodeUTF8));
        toolButton_exchange->setText(QString());
        toolButton_create->setText(QString());
        groupBox_nodes->setTitle(QApplication::translate("CreateRelationManualWidget", "\346\272\220\350\212\202\347\202\271-\347\253\257\350\212\202\347\202\271", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CreateRelationManualWidget", "\346\272\220\345\257\271\350\261\241\357\274\232", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButton_3->setToolTip(QApplication::translate("CreateRelationManualWidget", "\351\200\211\346\213\251\346\272\220\345\257\271\350\261\241", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_3->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_4->setToolTip(QApplication::translate("CreateRelationManualWidget", "\346\270\205\351\231\244\346\272\220\345\257\271\350\261\241", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_4->setText(QString());
        label_2->setText(QApplication::translate("CreateRelationManualWidget", "\347\253\257\345\257\271\350\261\241\357\274\232", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButton_5->setToolTip(QApplication::translate("CreateRelationManualWidget", "\351\200\211\346\213\251\346\272\220\345\257\271\350\261\241", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_5->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_6->setToolTip(QApplication::translate("CreateRelationManualWidget", "\346\270\205\351\231\244\346\272\220\345\257\271\350\261\241", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CreateRelationManualWidget: public Ui_CreateRelationManualWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATERELATIONMANUALWIDGET_H
