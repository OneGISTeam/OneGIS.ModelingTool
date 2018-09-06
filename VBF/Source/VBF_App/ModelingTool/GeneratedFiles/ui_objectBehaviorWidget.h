/********************************************************************************
** Form generated from reading UI file 'objectBehaviorWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTBEHAVIORWIDGET_H
#define UI_OBJECTBEHAVIORWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ObjectBehaviorWidget
{
public:
    QGridLayout *gridLayout_8;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_7;
    QGridLayout *gridLayout_6;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableWidget_2;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QTableWidget *tableWidget;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QTableWidget *tableWidget_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_editPrivateFormPart;
    QSpacerItem *horizontalSpacer_6;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_4;
    QTableWidget *tableWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_addPrivateBehavior;
    QPushButton *pushButton_removePrivateForm;

    void setupUi(QWidget *ObjectBehaviorWidget)
    {
        if (ObjectBehaviorWidget->objectName().isEmpty())
            ObjectBehaviorWidget->setObjectName(QString::fromUtf8("ObjectBehaviorWidget"));
        ObjectBehaviorWidget->resize(863, 585);
        gridLayout_8 = new QGridLayout(ObjectBehaviorWidget);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        scrollArea = new QScrollArea(ObjectBehaviorWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 951, 540));
        gridLayout_7 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        groupBox_3 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        tableWidget_2 = new QTableWidget(groupBox_3);
        if (tableWidget_2->columnCount() < 4)
            tableWidget_2->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        if (tableWidget_2->rowCount() < 8)
            tableWidget_2->setRowCount(8);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(4, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(5, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(6, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(7, __qtablewidgetitem11);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));

        verticalLayout->addWidget(tableWidget_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_3, 0, 0, 1, 1);

        groupBox_5 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_4 = new QGridLayout(groupBox_5);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox = new QGroupBox(groupBox_5);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tableWidget = new QTableWidget(groupBox);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem15);
        if (tableWidget->rowCount() < 8)
            tableWidget->setRowCount(8);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem23);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setMinimumSize(QSize(400, 0));

        gridLayout_3->addWidget(tableWidget, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(groupBox_5);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setEnabled(true);
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        tableWidget_3 = new QTableWidget(groupBox_2);
        if (tableWidget_3->columnCount() < 4)
            tableWidget_3->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(0, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(1, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(2, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(3, __qtablewidgetitem27);
        if (tableWidget_3->rowCount() < 8)
            tableWidget_3->setRowCount(8);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(0, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(1, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(2, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(3, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(4, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(5, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(6, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(7, __qtablewidgetitem35);
        tableWidget_3->setObjectName(QString::fromUtf8("tableWidget_3"));
        tableWidget_3->setEnabled(true);
        tableWidget_3->setMinimumSize(QSize(400, 0));

        gridLayout_5->addWidget(tableWidget_3, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_5 = new QSpacerItem(133, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        pushButton_editPrivateFormPart = new QPushButton(groupBox_5);
        pushButton_editPrivateFormPart->setObjectName(QString::fromUtf8("pushButton_editPrivateFormPart"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/saveProject.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_editPrivateFormPart->setIcon(icon);

        horizontalLayout_2->addWidget(pushButton_editPrivateFormPart);

        horizontalSpacer_6 = new QSpacerItem(133, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        verticalLayout_3->addLayout(horizontalLayout_2);


        gridLayout_4->addLayout(verticalLayout_3, 0, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_5, 0, 1, 2, 1);

        groupBox_4 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_2 = new QGridLayout(groupBox_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_3);

        tableWidget_4 = new QTableWidget(groupBox_4);
        if (tableWidget_4->columnCount() < 3)
            tableWidget_4->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(0, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(1, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(2, __qtablewidgetitem38);
        if (tableWidget_4->rowCount() < 8)
            tableWidget_4->setRowCount(8);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(0, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(1, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(2, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(3, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(4, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(5, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(6, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(7, __qtablewidgetitem46);
        tableWidget_4->setObjectName(QString::fromUtf8("tableWidget_4"));

        verticalLayout_2->addWidget(tableWidget_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButton_addPrivateBehavior = new QPushButton(groupBox_4);
        pushButton_addPrivateBehavior->setObjectName(QString::fromUtf8("pushButton_addPrivateBehavior"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_addPrivateBehavior->setIcon(icon1);

        horizontalLayout_4->addWidget(pushButton_addPrivateBehavior);

        pushButton_removePrivateForm = new QPushButton(groupBox_4);
        pushButton_removePrivateForm->setObjectName(QString::fromUtf8("pushButton_removePrivateForm"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/remove_circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_removePrivateForm->setIcon(icon2);

        horizontalLayout_4->addWidget(pushButton_removePrivateForm);


        verticalLayout_2->addLayout(horizontalLayout_4);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_4, 1, 0, 1, 1);


        gridLayout_7->addLayout(gridLayout_6, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_8->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(ObjectBehaviorWidget);

        QMetaObject::connectSlotsByName(ObjectBehaviorWidget);
    } // setupUi

    void retranslateUi(QWidget *ObjectBehaviorWidget)
    {
        ObjectBehaviorWidget->setWindowTitle(QApplication::translate("ObjectBehaviorWidget", "\350\241\214\344\270\272\350\203\275\345\212\233", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("ObjectBehaviorWidget", "\345\205\254\346\234\211\350\241\214\344\270\272\345\210\227\350\241\250\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ObjectBehaviorWidget", "\345\217\257\344\273\245\346\233\264\346\224\271\347\273\247\346\211\277\350\207\252\345\257\271\350\261\241\346\250\241\346\235\277\344\270\255\347\232\204\350\241\214\344\270\272\357\274\214\344\275\206\344\270\215\345\217\257\344\273\245\345\210\240\351\231\244\344\273\273\344\275\225\345\205\254\346\234\211\350\241\214\344\270\272\343\200\202", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ObjectBehaviorWidget", "\350\241\214\344\270\272\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ObjectBehaviorWidget", "\350\241\214\344\270\272\345\210\253\345\220\215", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("ObjectBehaviorWidget", "\351\232\266\345\261\236\350\241\214\344\270\272\347\273\204\344\273\266", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("ObjectBehaviorWidget", "\347\273\247\346\211\277\350\207\252", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_2->verticalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("ObjectBehaviorWidget", "1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_2->verticalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("ObjectBehaviorWidget", "2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_2->verticalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("ObjectBehaviorWidget", "3", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_2->verticalHeaderItem(3);
        ___qtablewidgetitem7->setText(QApplication::translate("ObjectBehaviorWidget", "4", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_2->verticalHeaderItem(4);
        ___qtablewidgetitem8->setText(QApplication::translate("ObjectBehaviorWidget", "5", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_2->verticalHeaderItem(5);
        ___qtablewidgetitem9->setText(QApplication::translate("ObjectBehaviorWidget", "6", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_2->verticalHeaderItem(6);
        ___qtablewidgetitem10->setText(QApplication::translate("ObjectBehaviorWidget", "7", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_2->verticalHeaderItem(7);
        ___qtablewidgetitem11->setText(QApplication::translate("ObjectBehaviorWidget", "9", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("ObjectBehaviorWidget", "\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ObjectBehaviorWidget", "\350\241\214\344\270\272\345\217\202\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QApplication::translate("ObjectBehaviorWidget", "\345\217\202\346\225\260\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem13->setText(QApplication::translate("ObjectBehaviorWidget", "\345\217\202\346\225\260\345\210\253\345\220\215", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem14->setText(QApplication::translate("ObjectBehaviorWidget", "\345\217\202\346\225\260\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem15->setText(QApplication::translate("ObjectBehaviorWidget", "\345\217\202\346\225\260\345\200\274", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem16->setText(QApplication::translate("ObjectBehaviorWidget", "1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem17->setText(QApplication::translate("ObjectBehaviorWidget", "2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem18->setText(QApplication::translate("ObjectBehaviorWidget", "3", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem19->setText(QApplication::translate("ObjectBehaviorWidget", "4", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem20->setText(QApplication::translate("ObjectBehaviorWidget", "5", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem21->setText(QApplication::translate("ObjectBehaviorWidget", "6", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem22->setText(QApplication::translate("ObjectBehaviorWidget", "7", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem23->setText(QApplication::translate("ObjectBehaviorWidget", "9", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("ObjectBehaviorWidget", "\350\276\223\345\205\245\345\217\202\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget_3->horizontalHeaderItem(0);
        ___qtablewidgetitem24->setText(QApplication::translate("ObjectBehaviorWidget", "\350\276\223\345\205\245\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget_3->horizontalHeaderItem(1);
        ___qtablewidgetitem25->setText(QApplication::translate("ObjectBehaviorWidget", "\350\276\223\345\205\245\345\210\253\345\220\215", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget_3->horizontalHeaderItem(2);
        ___qtablewidgetitem26->setText(QApplication::translate("ObjectBehaviorWidget", "\350\276\223\345\205\245\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget_3->horizontalHeaderItem(3);
        ___qtablewidgetitem27->setText(QApplication::translate("ObjectBehaviorWidget", "\350\276\223\345\205\245\345\200\274", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget_3->verticalHeaderItem(0);
        ___qtablewidgetitem28->setText(QApplication::translate("ObjectBehaviorWidget", "1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget_3->verticalHeaderItem(1);
        ___qtablewidgetitem29->setText(QApplication::translate("ObjectBehaviorWidget", "2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget_3->verticalHeaderItem(2);
        ___qtablewidgetitem30->setText(QApplication::translate("ObjectBehaviorWidget", "3", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget_3->verticalHeaderItem(3);
        ___qtablewidgetitem31->setText(QApplication::translate("ObjectBehaviorWidget", "4", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget_3->verticalHeaderItem(4);
        ___qtablewidgetitem32->setText(QApplication::translate("ObjectBehaviorWidget", "5", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget_3->verticalHeaderItem(5);
        ___qtablewidgetitem33->setText(QApplication::translate("ObjectBehaviorWidget", "6", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget_3->verticalHeaderItem(6);
        ___qtablewidgetitem34->setText(QApplication::translate("ObjectBehaviorWidget", "7", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget_3->verticalHeaderItem(7);
        ___qtablewidgetitem35->setText(QApplication::translate("ObjectBehaviorWidget", "9", 0, QApplication::UnicodeUTF8));
        pushButton_editPrivateFormPart->setText(QApplication::translate("ObjectBehaviorWidget", "\344\277\235\345\255\230\347\274\226\350\276\221", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("ObjectBehaviorWidget", "\347\247\201\346\234\211\350\241\214\344\270\272\345\210\227\350\241\250\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ObjectBehaviorWidget", "\345\217\257\344\273\245\344\273\273\346\204\217\346\267\273\345\212\240\343\200\201\345\210\240\351\231\244\343\200\201\344\277\256\346\224\271\345\257\271\350\261\241\347\232\204\347\247\201\346\234\211\350\241\214\344\270\272\343\200\202", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget_4->horizontalHeaderItem(0);
        ___qtablewidgetitem36->setText(QApplication::translate("ObjectBehaviorWidget", "\350\241\214\344\270\272\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidget_4->horizontalHeaderItem(1);
        ___qtablewidgetitem37->setText(QApplication::translate("ObjectBehaviorWidget", "\350\241\214\344\270\272\345\210\253\345\220\215", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidget_4->horizontalHeaderItem(2);
        ___qtablewidgetitem38->setText(QApplication::translate("ObjectBehaviorWidget", "\351\232\266\345\261\236\350\241\214\344\270\272\347\273\204\344\273\266", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem39 = tableWidget_4->verticalHeaderItem(0);
        ___qtablewidgetitem39->setText(QApplication::translate("ObjectBehaviorWidget", "1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem40 = tableWidget_4->verticalHeaderItem(1);
        ___qtablewidgetitem40->setText(QApplication::translate("ObjectBehaviorWidget", "2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem41 = tableWidget_4->verticalHeaderItem(2);
        ___qtablewidgetitem41->setText(QApplication::translate("ObjectBehaviorWidget", "3", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem42 = tableWidget_4->verticalHeaderItem(3);
        ___qtablewidgetitem42->setText(QApplication::translate("ObjectBehaviorWidget", "4", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem43 = tableWidget_4->verticalHeaderItem(4);
        ___qtablewidgetitem43->setText(QApplication::translate("ObjectBehaviorWidget", "5", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem44 = tableWidget_4->verticalHeaderItem(5);
        ___qtablewidgetitem44->setText(QApplication::translate("ObjectBehaviorWidget", "6", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem45 = tableWidget_4->verticalHeaderItem(6);
        ___qtablewidgetitem45->setText(QApplication::translate("ObjectBehaviorWidget", "7", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem46 = tableWidget_4->verticalHeaderItem(7);
        ___qtablewidgetitem46->setText(QApplication::translate("ObjectBehaviorWidget", "9", 0, QApplication::UnicodeUTF8));
        pushButton_addPrivateBehavior->setText(QApplication::translate("ObjectBehaviorWidget", "\346\267\273\345\212\240\347\247\201\346\234\211\350\241\214\344\270\272", 0, QApplication::UnicodeUTF8));
        pushButton_removePrivateForm->setText(QApplication::translate("ObjectBehaviorWidget", "\347\247\273\351\231\244\347\247\201\346\234\211\350\241\214\344\270\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ObjectBehaviorWidget: public Ui_ObjectBehaviorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTBEHAVIORWIDGET_H
