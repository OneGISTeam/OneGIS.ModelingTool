/********************************************************************************
** Form generated from reading UI file 'objectComposeWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTCOMPOSEWIDGET_H
#define UI_OBJECTCOMPOSEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ObjectComposeWidget
{
public:
    QGridLayout *gridLayout_10;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_9;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_6;
    QTreeWidget *treeWidget;
    QPushButton *pushButton_addPart;
    QPushButton *pushButton_removePart;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_8;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_7;
    QLabel *label;
    QLineEdit *lineEdit_partName;
    QLabel *label_2;
    QLineEdit *lineEdit_partOID;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBox_dX;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBox_dY;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox_dZ;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_8;
    QDoubleSpinBox *doubleSpinBox_rX;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_9;
    QDoubleSpinBox *doubleSpinBox_rY;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_10;
    QDoubleSpinBox *doubleSpinBox_rZ;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_11;
    QDoubleSpinBox *doubleSpinBox_sX;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_12;
    QDoubleSpinBox *doubleSpinBox_sY;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_13;
    QDoubleSpinBox *doubleSpinBox_sZ;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_14;
    QDoubleSpinBox *doubleSpinBox_sX_2;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_15;
    QDoubleSpinBox *doubleSpinBox_sY_2;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_16;
    QDoubleSpinBox *doubleSpinBox_sZ_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_saveEdit;

    void setupUi(QWidget *ObjectComposeWidget)
    {
        if (ObjectComposeWidget->objectName().isEmpty())
            ObjectComposeWidget->setObjectName(QString::fromUtf8("ObjectComposeWidget"));
        ObjectComposeWidget->resize(614, 496);
        gridLayout_10 = new QGridLayout(ObjectComposeWidget);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        scrollArea = new QScrollArea(ObjectComposeWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 590, 472));
        gridLayout_9 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        treeWidget = new QTreeWidget(scrollAreaWidgetContents);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/class.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/object.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem1->setIcon(0, icon1);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->header()->setVisible(true);
        treeWidget->header()->setDefaultSectionSize(110);
        treeWidget->header()->setMinimumSectionSize(40);

        verticalLayout_6->addWidget(treeWidget);

        pushButton_addPart = new QPushButton(scrollAreaWidgetContents);
        pushButton_addPart->setObjectName(QString::fromUtf8("pushButton_addPart"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_addPart->setIcon(icon2);

        verticalLayout_6->addWidget(pushButton_addPart);

        pushButton_removePart = new QPushButton(scrollAreaWidgetContents);
        pushButton_removePart->setObjectName(QString::fromUtf8("pushButton_removePart"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ModelingTool/Images/remove_circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_removePart->setIcon(icon3);

        verticalLayout_6->addWidget(pushButton_removePart);


        horizontalLayout->addLayout(verticalLayout_6);

        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_8 = new QGridLayout(groupBox);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_7->addWidget(label, 0, 0, 1, 1);

        lineEdit_partName = new QLineEdit(groupBox);
        lineEdit_partName->setObjectName(QString::fromUtf8("lineEdit_partName"));
        lineEdit_partName->setEnabled(false);

        gridLayout_7->addWidget(lineEdit_partName, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_7->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_partOID = new QLineEdit(groupBox);
        lineEdit_partOID->setObjectName(QString::fromUtf8("lineEdit_partOID"));
        lineEdit_partOID->setEnabled(false);

        gridLayout_7->addWidget(lineEdit_partOID, 1, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_7);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_6 = new QGridLayout(groupBox_3);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout = new QGridLayout(groupBox_4);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_6->addWidget(label_5);

        doubleSpinBox_dX = new QDoubleSpinBox(groupBox_4);
        doubleSpinBox_dX->setObjectName(QString::fromUtf8("doubleSpinBox_dX"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(doubleSpinBox_dX->sizePolicy().hasHeightForWidth());
        doubleSpinBox_dX->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(doubleSpinBox_dX);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_10->addWidget(label_6);

        doubleSpinBox_dY = new QDoubleSpinBox(groupBox_4);
        doubleSpinBox_dY->setObjectName(QString::fromUtf8("doubleSpinBox_dY"));
        sizePolicy.setHeightForWidth(doubleSpinBox_dY->sizePolicy().hasHeightForWidth());
        doubleSpinBox_dY->setSizePolicy(sizePolicy);

        horizontalLayout_10->addWidget(doubleSpinBox_dY);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_11->addWidget(label_7);

        doubleSpinBox_dZ = new QDoubleSpinBox(groupBox_4);
        doubleSpinBox_dZ->setObjectName(QString::fromUtf8("doubleSpinBox_dZ"));
        sizePolicy.setHeightForWidth(doubleSpinBox_dZ->sizePolicy().hasHeightForWidth());
        doubleSpinBox_dZ->setSizePolicy(sizePolicy);

        horizontalLayout_11->addWidget(doubleSpinBox_dZ);


        verticalLayout->addLayout(horizontalLayout_11);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_4, 0, 0, 1, 1);

        groupBox_5 = new QGroupBox(groupBox_3);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_3 = new QGridLayout(groupBox_5);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_8 = new QLabel(groupBox_5);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_12->addWidget(label_8);

        doubleSpinBox_rX = new QDoubleSpinBox(groupBox_5);
        doubleSpinBox_rX->setObjectName(QString::fromUtf8("doubleSpinBox_rX"));
        sizePolicy.setHeightForWidth(doubleSpinBox_rX->sizePolicy().hasHeightForWidth());
        doubleSpinBox_rX->setSizePolicy(sizePolicy);

        horizontalLayout_12->addWidget(doubleSpinBox_rX);


        verticalLayout_2->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_9 = new QLabel(groupBox_5);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_13->addWidget(label_9);

        doubleSpinBox_rY = new QDoubleSpinBox(groupBox_5);
        doubleSpinBox_rY->setObjectName(QString::fromUtf8("doubleSpinBox_rY"));
        sizePolicy.setHeightForWidth(doubleSpinBox_rY->sizePolicy().hasHeightForWidth());
        doubleSpinBox_rY->setSizePolicy(sizePolicy);

        horizontalLayout_13->addWidget(doubleSpinBox_rY);


        verticalLayout_2->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_10 = new QLabel(groupBox_5);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_14->addWidget(label_10);

        doubleSpinBox_rZ = new QDoubleSpinBox(groupBox_5);
        doubleSpinBox_rZ->setObjectName(QString::fromUtf8("doubleSpinBox_rZ"));
        sizePolicy.setHeightForWidth(doubleSpinBox_rZ->sizePolicy().hasHeightForWidth());
        doubleSpinBox_rZ->setSizePolicy(sizePolicy);

        horizontalLayout_14->addWidget(doubleSpinBox_rZ);


        verticalLayout_2->addLayout(horizontalLayout_14);


        gridLayout_3->addLayout(verticalLayout_2, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_5, 0, 1, 1, 1);

        groupBox_6 = new QGroupBox(groupBox_3);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        gridLayout_4 = new QGridLayout(groupBox_6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_11 = new QLabel(groupBox_6);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_15->addWidget(label_11);

        doubleSpinBox_sX = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_sX->setObjectName(QString::fromUtf8("doubleSpinBox_sX"));
        sizePolicy.setHeightForWidth(doubleSpinBox_sX->sizePolicy().hasHeightForWidth());
        doubleSpinBox_sX->setSizePolicy(sizePolicy);
        doubleSpinBox_sX->setValue(1);

        horizontalLayout_15->addWidget(doubleSpinBox_sX);


        verticalLayout_4->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_12 = new QLabel(groupBox_6);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_16->addWidget(label_12);

        doubleSpinBox_sY = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_sY->setObjectName(QString::fromUtf8("doubleSpinBox_sY"));
        sizePolicy.setHeightForWidth(doubleSpinBox_sY->sizePolicy().hasHeightForWidth());
        doubleSpinBox_sY->setSizePolicy(sizePolicy);
        doubleSpinBox_sY->setValue(1);

        horizontalLayout_16->addWidget(doubleSpinBox_sY);


        verticalLayout_4->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_13 = new QLabel(groupBox_6);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_17->addWidget(label_13);

        doubleSpinBox_sZ = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_sZ->setObjectName(QString::fromUtf8("doubleSpinBox_sZ"));
        sizePolicy.setHeightForWidth(doubleSpinBox_sZ->sizePolicy().hasHeightForWidth());
        doubleSpinBox_sZ->setSizePolicy(sizePolicy);
        doubleSpinBox_sZ->setValue(1);

        horizontalLayout_17->addWidget(doubleSpinBox_sZ);


        verticalLayout_4->addLayout(horizontalLayout_17);


        gridLayout_4->addLayout(verticalLayout_4, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_6, 1, 0, 1, 1);

        groupBox_7 = new QGroupBox(groupBox_3);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        gridLayout_5 = new QGridLayout(groupBox_7);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_14 = new QLabel(groupBox_7);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_18->addWidget(label_14);

        doubleSpinBox_sX_2 = new QDoubleSpinBox(groupBox_7);
        doubleSpinBox_sX_2->setObjectName(QString::fromUtf8("doubleSpinBox_sX_2"));
        sizePolicy.setHeightForWidth(doubleSpinBox_sX_2->sizePolicy().hasHeightForWidth());
        doubleSpinBox_sX_2->setSizePolicy(sizePolicy);

        horizontalLayout_18->addWidget(doubleSpinBox_sX_2);


        verticalLayout_5->addLayout(horizontalLayout_18);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_15 = new QLabel(groupBox_7);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_19->addWidget(label_15);

        doubleSpinBox_sY_2 = new QDoubleSpinBox(groupBox_7);
        doubleSpinBox_sY_2->setObjectName(QString::fromUtf8("doubleSpinBox_sY_2"));
        sizePolicy.setHeightForWidth(doubleSpinBox_sY_2->sizePolicy().hasHeightForWidth());
        doubleSpinBox_sY_2->setSizePolicy(sizePolicy);

        horizontalLayout_19->addWidget(doubleSpinBox_sY_2);


        verticalLayout_5->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        label_16 = new QLabel(groupBox_7);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_20->addWidget(label_16);

        doubleSpinBox_sZ_2 = new QDoubleSpinBox(groupBox_7);
        doubleSpinBox_sZ_2->setObjectName(QString::fromUtf8("doubleSpinBox_sZ_2"));
        sizePolicy.setHeightForWidth(doubleSpinBox_sZ_2->sizePolicy().hasHeightForWidth());
        doubleSpinBox_sZ_2->setSizePolicy(sizePolicy);

        horizontalLayout_20->addWidget(doubleSpinBox_sZ_2);


        verticalLayout_5->addLayout(horizontalLayout_20);


        gridLayout_5->addLayout(verticalLayout_5, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_7, 1, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout_2, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer, 2, 0, 1, 1);

        pushButton_saveEdit = new QPushButton(groupBox_3);
        pushButton_saveEdit->setObjectName(QString::fromUtf8("pushButton_saveEdit"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ModelingTool/Images/saveProject.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_saveEdit->setIcon(icon4);

        gridLayout_6->addWidget(pushButton_saveEdit, 1, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_3);


        gridLayout_8->addLayout(verticalLayout_3, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox);


        gridLayout_9->addLayout(horizontalLayout, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_10->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(ObjectComposeWidget);

        QMetaObject::connectSlotsByName(ObjectComposeWidget);
    } // setupUi

    void retranslateUi(QWidget *ObjectComposeWidget)
    {
        ObjectComposeWidget->setWindowTitle(QApplication::translate("ObjectComposeWidget", "\345\257\271\350\261\241\347\273\204\346\210\220\347\273\223\346\236\204", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("ObjectComposeWidget", "\346\240\207\350\257\206", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("ObjectComposeWidget", "\345\257\271\350\261\241/\347\261\273", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(1, QApplication::translate("ObjectComposeWidget", "30003", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(0, QApplication::translate("ObjectComposeWidget", "GPS\344\273\252\345\231\250", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(1, QApplication::translate("ObjectComposeWidget", "30011", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem2->setText(0, QApplication::translate("ObjectComposeWidget", "GPS-11", 0, QApplication::UnicodeUTF8));
        treeWidget->setSortingEnabled(__sortingEnabled);

        pushButton_addPart->setText(QApplication::translate("ObjectComposeWidget", "\346\267\273\345\212\240\345\255\220\345\257\271\350\261\241", 0, QApplication::UnicodeUTF8));
        pushButton_removePart->setText(QApplication::translate("ObjectComposeWidget", "\347\247\273\351\231\244\345\255\220\345\257\271\350\261\241", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ObjectComposeWidget", "\347\274\226\350\276\221\345\255\220\345\257\271\350\261\241", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ObjectComposeWidget", "\345\255\220\345\257\271\350\261\241\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ObjectComposeWidget", "\345\255\220\345\257\271\350\261\241\346\240\207\350\257\206\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("ObjectComposeWidget", "\345\217\230\346\215\242\347\237\251\351\230\265", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("ObjectComposeWidget", "\345\235\220\346\240\207\345\271\263\347\247\273", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ObjectComposeWidget", "dX", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ObjectComposeWidget", "dY", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ObjectComposeWidget", "dZ", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("ObjectComposeWidget", "\345\235\220\346\240\207\346\227\213\350\275\254", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("ObjectComposeWidget", "rX", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("ObjectComposeWidget", "rY", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("ObjectComposeWidget", "rZ", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("ObjectComposeWidget", "\345\235\220\346\240\207\347\274\251\346\224\276", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("ObjectComposeWidget", "sX", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("ObjectComposeWidget", "sY", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("ObjectComposeWidget", "sZ", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("ObjectComposeWidget", "\345\234\260\347\220\206\345\256\232\344\275\215", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("ObjectComposeWidget", "L", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("ObjectComposeWidget", "B", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("ObjectComposeWidget", "H", 0, QApplication::UnicodeUTF8));
        pushButton_saveEdit->setText(QApplication::translate("ObjectComposeWidget", "\344\277\235\345\255\230\344\277\256\346\224\271", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ObjectComposeWidget: public Ui_ObjectComposeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTCOMPOSEWIDGET_H
