/********************************************************************************
** Form generated from reading UI file 'frameProducerDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRAMEPRODUCERDIALOG_H
#define UI_FRAMEPRODUCERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FrameProducerDialog
{
public:
    QGridLayout *gridLayout_6;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit_componentID;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *lineEdit_componentName;
    QLabel *label_4;
    QLabel *label_7;
    QLineEdit *lineEdit_componentAlias;
    QLabel *label_8;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QSpacerItem *verticalSpacer;
    QTextEdit *textEdit_componentDesc;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_6;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;
    QTableWidget *tableWidget_beheviors;
    QPushButton *pushButton_add;
    QPushButton *pushButton_remove;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_outputPath;
    QPushButton *pushButton_search;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_produce;
    QPushButton *pushButton_cancel;

    void setupUi(QDialog *FrameProducerDialog)
    {
        if (FrameProducerDialog->objectName().isEmpty())
            FrameProducerDialog->setObjectName(QString::fromUtf8("FrameProducerDialog"));
        FrameProducerDialog->resize(586, 568);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/behaviorComponent.png"), QSize(), QIcon::Normal, QIcon::Off);
        FrameProducerDialog->setWindowIcon(icon);
        gridLayout_6 = new QGridLayout(FrameProducerDialog);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox = new QGroupBox(FrameProducerDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit_componentID = new QLineEdit(groupBox);
        lineEdit_componentID->setObjectName(QString::fromUtf8("lineEdit_componentID"));

        gridLayout->addWidget(lineEdit_componentID, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font;
        font.setItalic(true);
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 0, 2, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_componentName = new QLineEdit(groupBox);
        lineEdit_componentName->setObjectName(QString::fromUtf8("lineEdit_componentName"));

        gridLayout->addWidget(lineEdit_componentName, 1, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        gridLayout->addWidget(label_4, 1, 2, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        lineEdit_componentAlias = new QLineEdit(groupBox);
        lineEdit_componentAlias->setObjectName(QString::fromUtf8("lineEdit_componentAlias"));

        gridLayout->addWidget(lineEdit_componentAlias, 2, 1, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);

        gridLayout->addWidget(label_8, 2, 2, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout->addWidget(label_5);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 3, 0, 1, 1);

        textEdit_componentDesc = new QTextEdit(groupBox);
        textEdit_componentDesc->setObjectName(QString::fromUtf8("textEdit_componentDesc"));

        gridLayout->addWidget(textEdit_componentDesc, 3, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);

        verticalLayout_2->addWidget(label_6);

        verticalSpacer_2 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        gridLayout->addLayout(verticalLayout_2, 3, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(FrameProducerDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        tableWidget_beheviors = new QTableWidget(groupBox_2);
        if (tableWidget_beheviors->columnCount() < 6)
            tableWidget_beheviors->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_beheviors->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_beheviors->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_beheviors->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_beheviors->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_beheviors->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_beheviors->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (tableWidget_beheviors->rowCount() < 3)
            tableWidget_beheviors->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_beheviors->setVerticalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_beheviors->setVerticalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_beheviors->setVerticalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_beheviors->setItem(0, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_beheviors->setItem(0, 1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_beheviors->setItem(0, 2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_beheviors->setItem(0, 3, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_beheviors->setItem(0, 4, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_beheviors->setItem(0, 5, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_beheviors->setItem(1, 0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_beheviors->setItem(1, 1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_beheviors->setItem(1, 2, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_beheviors->setItem(1, 3, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_beheviors->setItem(1, 4, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget_beheviors->setItem(1, 5, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget_beheviors->setItem(2, 0, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget_beheviors->setItem(2, 1, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget_beheviors->setItem(2, 2, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget_beheviors->setItem(2, 3, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget_beheviors->setItem(2, 4, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget_beheviors->setItem(2, 5, __qtablewidgetitem26);
        tableWidget_beheviors->setObjectName(QString::fromUtf8("tableWidget_beheviors"));
        tableWidget_beheviors->setMinimumSize(QSize(0, 200));

        gridLayout_4->addWidget(tableWidget_beheviors, 0, 0, 1, 2);

        pushButton_add = new QPushButton(groupBox_2);
        pushButton_add->setObjectName(QString::fromUtf8("pushButton_add"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_add->setIcon(icon1);

        gridLayout_4->addWidget(pushButton_add, 1, 0, 1, 1);

        pushButton_remove = new QPushButton(groupBox_2);
        pushButton_remove->setObjectName(QString::fromUtf8("pushButton_remove"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/remove_circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_remove->setIcon(icon2);

        gridLayout_4->addWidget(pushButton_remove, 1, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(FrameProducerDialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit_outputPath = new QLineEdit(groupBox_3);
        lineEdit_outputPath->setObjectName(QString::fromUtf8("lineEdit_outputPath"));

        horizontalLayout->addWidget(lineEdit_outputPath);

        pushButton_search = new QPushButton(groupBox_3);
        pushButton_search->setObjectName(QString::fromUtf8("pushButton_search"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ModelingTool/Images/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_search->setIcon(icon3);

        horizontalLayout->addWidget(pushButton_search);


        gridLayout_3->addLayout(horizontalLayout, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_produce = new QPushButton(FrameProducerDialog);
        pushButton_produce->setObjectName(QString::fromUtf8("pushButton_produce"));

        horizontalLayout_2->addWidget(pushButton_produce);

        pushButton_cancel = new QPushButton(FrameProducerDialog);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));

        horizontalLayout_2->addWidget(pushButton_cancel);


        verticalLayout_3->addLayout(horizontalLayout_2);


        gridLayout_6->addLayout(verticalLayout_3, 0, 0, 1, 1);


        retranslateUi(FrameProducerDialog);

        QMetaObject::connectSlotsByName(FrameProducerDialog);
    } // setupUi

    void retranslateUi(QDialog *FrameProducerDialog)
    {
        FrameProducerDialog->setWindowTitle(QApplication::translate("FrameProducerDialog", "\350\241\214\344\270\272\347\273\204\344\273\266\346\241\206\346\236\266\347\224\237\346\210\220", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("FrameProducerDialog", "\350\241\214\344\270\272\347\273\204\344\273\266\345\237\272\346\234\254\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FrameProducerDialog", "\350\241\214\344\270\272\347\273\204\344\273\266\346\240\207\350\257\206\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FrameProducerDialog", "\347\261\273\345\210\253\346\240\207\350\257\206\347\224\250\344\272\216\345\224\257\344\270\200\346\240\207\350\257\206\350\257\245\350\241\214\344\270\272\347\273\204\344\273\266\345\212\250\346\200\201\345\272\223", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FrameProducerDialog", "\350\241\214\344\270\272\347\273\204\344\273\266\347\261\273\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FrameProducerDialog", "\347\273\204\344\273\266\345\220\215\347\247\260\345\260\206\344\275\234\344\270\272\347\273\204\344\273\266\345\267\245\345\216\202\345\272\223\347\232\204\347\261\273\345\220\215\357\274\210.h\357\274\211", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FrameProducerDialog", "\350\241\214\344\270\272\347\273\204\344\273\266\345\210\253\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("FrameProducerDialog", "\347\224\250\344\272\216\347\224\250\346\210\267\350\257\206\345\210\253\350\257\245\350\241\214\344\270\272\347\273\204\344\273\266\347\232\204\346\230\223\350\257\273\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FrameProducerDialog", "\350\241\214\344\270\272\347\273\204\344\273\266\346\217\217\350\277\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FrameProducerDialog", "\345\257\271\350\241\214\344\270\272\347\273\204\344\273\266\350\277\233\350\241\214\344\270\200\344\270\252\346\225\264\344\275\223\347\232\204\346\217\217\350\277\260", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("FrameProducerDialog", "\350\241\214\344\270\272\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_beheviors->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("FrameProducerDialog", "\350\241\214\344\270\272\345\210\253\345\220\215", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_beheviors->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("FrameProducerDialog", "\350\241\214\344\270\272\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_beheviors->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("FrameProducerDialog", "\350\241\214\344\270\272\347\261\273\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_beheviors->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("FrameProducerDialog", "\350\241\214\344\270\272\346\217\217\350\277\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_beheviors->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("FrameProducerDialog", "\345\217\202\346\225\260\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_beheviors->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("FrameProducerDialog", "\350\276\223\345\205\245\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_beheviors->verticalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("FrameProducerDialog", "1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_beheviors->verticalHeaderItem(1);
        ___qtablewidgetitem7->setText(QApplication::translate("FrameProducerDialog", "2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_beheviors->verticalHeaderItem(2);
        ___qtablewidgetitem8->setText(QApplication::translate("FrameProducerDialog", "3", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tableWidget_beheviors->isSortingEnabled();
        tableWidget_beheviors->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_beheviors->item(0, 0);
        ___qtablewidgetitem9->setText(QApplication::translate("FrameProducerDialog", "\350\265\267\351\243\236", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_beheviors->item(0, 1);
        ___qtablewidgetitem10->setText(QApplication::translate("FrameProducerDialog", "PlaneTakeOff", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_beheviors->item(0, 2);
        ___qtablewidgetitem11->setText(QApplication::translate("FrameProducerDialog", "C_PlaneTakeOff", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_beheviors->item(0, 3);
        ___qtablewidgetitem12->setText(QApplication::translate("FrameProducerDialog", "\344\270\273\350\246\201\346\230\257\351\200\232\350\277\207\346\273\221\350\241\214\343\200\201\345\212\240\351\200\237\344\271\213\345\220\216\350\276\276\345\210\260\345\271\263\351\243\236\351\253\230\345\272\246\343\200\202", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_beheviors->item(0, 4);
        ___qtablewidgetitem13->setText(QApplication::translate("FrameProducerDialog", "\346\234\272\351\225\277/\346\234\272\351\253\230/\347\277\274\345\261\225", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_beheviors->item(0, 5);
        ___qtablewidgetitem14->setText(QApplication::translate("FrameProducerDialog", "\350\265\267\351\243\236\347\202\271/\350\275\275\351\207\215/\351\243\216\351\200\237/\351\243\216\345\220\221", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_beheviors->item(1, 0);
        ___qtablewidgetitem15->setText(QApplication::translate("FrameProducerDialog", "\345\271\263\351\243\236", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_beheviors->item(1, 1);
        ___qtablewidgetitem16->setText(QApplication::translate("FrameProducerDialog", "PlaneFly", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_beheviors->item(1, 2);
        ___qtablewidgetitem17->setText(QApplication::translate("FrameProducerDialog", "C_PlaneFly", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_beheviors->item(1, 3);
        ___qtablewidgetitem18->setText(QApplication::translate("FrameProducerDialog", "\344\270\273\350\246\201\346\230\257\351\243\236\346\234\272\345\234\250\351\253\230\347\251\272\347\232\204\345\271\263\347\250\263\351\243\236\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_beheviors->item(1, 4);
        ___qtablewidgetitem19->setText(QApplication::translate("FrameProducerDialog", "\346\234\272\351\225\277/\346\234\272\351\253\230/\347\277\274\345\261\225", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_beheviors->item(1, 5);
        ___qtablewidgetitem20->setText(QApplication::translate("FrameProducerDialog", "\346\227\266\351\200\237/\345\271\263\351\243\236\351\253\230\345\272\246/\350\265\267\345\247\213\347\202\271", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget_beheviors->item(2, 0);
        ___qtablewidgetitem21->setText(QApplication::translate("FrameProducerDialog", "\351\231\215\350\220\275", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget_beheviors->item(2, 1);
        ___qtablewidgetitem22->setText(QApplication::translate("FrameProducerDialog", "PlaneLanding", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget_beheviors->item(2, 2);
        ___qtablewidgetitem23->setText(QApplication::translate("FrameProducerDialog", "C_PlaneLanding", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget_beheviors->item(2, 3);
        ___qtablewidgetitem24->setText(QApplication::translate("FrameProducerDialog", "\344\270\273\350\246\201\346\230\257\351\243\236\346\234\272\347\232\204\345\207\217\351\200\237\343\200\201\351\231\215\350\220\275\343\200\201\346\273\221\350\241\214\347\233\264\345\210\260\345\201\234\346\255\242\343\200\202", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget_beheviors->item(2, 4);
        ___qtablewidgetitem25->setText(QApplication::translate("FrameProducerDialog", "\346\234\272\351\225\277/\346\234\272\351\253\230/\347\277\274\345\261\225", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget_beheviors->item(2, 5);
        ___qtablewidgetitem26->setText(QApplication::translate("FrameProducerDialog", "\351\231\215\350\220\275\347\202\271/\346\227\266\351\200\237", 0, QApplication::UnicodeUTF8));
        tableWidget_beheviors->setSortingEnabled(__sortingEnabled);

        pushButton_add->setText(QApplication::translate("FrameProducerDialog", "\346\267\273\345\212\240\350\241\214\344\270\272", 0, QApplication::UnicodeUTF8));
        pushButton_remove->setText(QApplication::translate("FrameProducerDialog", "\347\247\273\351\231\244\350\241\214\344\270\272", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("FrameProducerDialog", "\344\273\243\347\240\201\347\224\237\346\210\220\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        pushButton_search->setText(QString());
        pushButton_produce->setText(QApplication::translate("FrameProducerDialog", "\347\224\237\346\210\220", 0, QApplication::UnicodeUTF8));
        pushButton_cancel->setText(QApplication::translate("FrameProducerDialog", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FrameProducerDialog: public Ui_FrameProducerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRAMEPRODUCERDIALOG_H
