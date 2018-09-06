/********************************************************************************
** Form generated from reading UI file 'objectClassFormWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTCLASSFORMWIDGET_H
#define UI_OBJECTCLASSFORMWIDGET_H

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

class Ui_ObjectClassFormWidget
{
public:
    QGridLayout *gridLayout_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QTableWidget *tableWidget_publicForm;
    QPushButton *pushButton_editPublicFormPart;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableWidget_privateForm;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_addPrivateForm;
    QPushButton *pushButton_removePrivateForm;
    QPushButton *pushButton_editPrivateFormPart;

    void setupUi(QWidget *ObjectClassFormWidget)
    {
        if (ObjectClassFormWidget->objectName().isEmpty())
            ObjectClassFormWidget->setObjectName(QString::fromUtf8("ObjectClassFormWidget"));
        ObjectClassFormWidget->resize(583, 544);
        gridLayout_4 = new QGridLayout(ObjectClassFormWidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        scrollArea = new QScrollArea(ObjectClassFormWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 563, 524));
        gridLayout_3 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setItalic(true);
        label_2->setFont(font);
        label_2->setWordWrap(true);

        verticalLayout->addWidget(label_2);

        tableWidget_publicForm = new QTableWidget(groupBox);
        if (tableWidget_publicForm->columnCount() < 6)
            tableWidget_publicForm->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_publicForm->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_publicForm->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_publicForm->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_publicForm->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_publicForm->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_publicForm->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (tableWidget_publicForm->rowCount() < 1)
            tableWidget_publicForm->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_publicForm->setVerticalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tableWidget_publicForm->setItem(0, 0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tableWidget_publicForm->setItem(0, 1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_publicForm->setItem(0, 2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_publicForm->setItem(0, 3, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setCheckState(Qt::Checked);
        tableWidget_publicForm->setItem(0, 4, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_publicForm->setItem(0, 5, __qtablewidgetitem12);
        tableWidget_publicForm->setObjectName(QString::fromUtf8("tableWidget_publicForm"));
        tableWidget_publicForm->setMaximumSize(QSize(16777215, 160));

        verticalLayout->addWidget(tableWidget_publicForm);

        pushButton_editPublicFormPart = new QPushButton(groupBox);
        pushButton_editPublicFormPart->setObjectName(QString::fromUtf8("pushButton_editPublicFormPart"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_editPublicFormPart->setIcon(icon);

        verticalLayout->addWidget(pushButton_editPublicFormPart);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);
        label_3->setWordWrap(false);

        horizontalLayout_2->addWidget(label_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_2);

        tableWidget_privateForm = new QTableWidget(groupBox_2);
        if (tableWidget_privateForm->columnCount() < 5)
            tableWidget_privateForm->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_privateForm->setHorizontalHeaderItem(0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_privateForm->setHorizontalHeaderItem(1, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_privateForm->setHorizontalHeaderItem(2, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_privateForm->setHorizontalHeaderItem(3, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_privateForm->setHorizontalHeaderItem(4, __qtablewidgetitem17);
        if (tableWidget_privateForm->rowCount() < 1)
            tableWidget_privateForm->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_privateForm->setVerticalHeaderItem(0, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_privateForm->setItem(0, 0, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget_privateForm->setItem(0, 1, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget_privateForm->setItem(0, 2, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        __qtablewidgetitem22->setCheckState(Qt::Checked);
        tableWidget_privateForm->setItem(0, 3, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget_privateForm->setItem(0, 4, __qtablewidgetitem23);
        tableWidget_privateForm->setObjectName(QString::fromUtf8("tableWidget_privateForm"));
        tableWidget_privateForm->setMaximumSize(QSize(16777215, 160));

        verticalLayout_2->addWidget(tableWidget_privateForm);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_addPrivateForm = new QPushButton(groupBox_2);
        pushButton_addPrivateForm->setObjectName(QString::fromUtf8("pushButton_addPrivateForm"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_addPrivateForm->setIcon(icon1);

        horizontalLayout->addWidget(pushButton_addPrivateForm);

        pushButton_removePrivateForm = new QPushButton(groupBox_2);
        pushButton_removePrivateForm->setObjectName(QString::fromUtf8("pushButton_removePrivateForm"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/remove_circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_removePrivateForm->setIcon(icon2);

        horizontalLayout->addWidget(pushButton_removePrivateForm);

        pushButton_editPrivateFormPart = new QPushButton(groupBox_2);
        pushButton_editPrivateFormPart->setObjectName(QString::fromUtf8("pushButton_editPrivateFormPart"));
        pushButton_editPrivateFormPart->setIcon(icon);

        horizontalLayout->addWidget(pushButton_editPrivateFormPart);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_2);


        gridLayout_3->addLayout(verticalLayout_3, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_4->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(ObjectClassFormWidget);

        QMetaObject::connectSlotsByName(ObjectClassFormWidget);
    } // setupUi

    void retranslateUi(QWidget *ObjectClassFormWidget)
    {
        ObjectClassFormWidget->setWindowTitle(QApplication::translate("ObjectClassFormWidget", "\345\257\271\350\261\241\347\261\273\347\251\272\351\227\264\345\275\242\346\200\201", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ObjectClassFormWidget", "\345\205\254\346\234\211\345\275\242\346\200\201", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ObjectClassFormWidget", "\346\202\250\345\217\257\344\273\245\346\233\264\346\224\271\347\273\247\346\211\277\350\207\252\347\273\247\346\211\277\350\207\252\345\257\271\350\261\241\346\250\241\346\235\277\344\270\255\347\232\204\345\275\242\346\200\201\346\225\260\346\215\256\357\274\214\344\275\206\344\270\215\345\217\257\344\273\245\345\210\240\351\231\244\344\273\273\344\275\225\345\205\254\346\234\211\345\275\242\346\200\201", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_publicForm->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ObjectClassFormWidget", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_publicForm->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ObjectClassFormWidget", "\347\273\247\346\211\277\350\207\252", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_publicForm->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("ObjectClassFormWidget", "\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_publicForm->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("ObjectClassFormWidget", "\345\260\272\345\272\246", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_publicForm->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("ObjectClassFormWidget", "\346\230\257\345\220\246\344\275\215\347\275\256\344\276\235\350\265\226", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_publicForm->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("ObjectClassFormWidget", "\345\275\242\346\200\201\351\203\250\344\273\266", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_publicForm->verticalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("ObjectClassFormWidget", "1", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tableWidget_publicForm->isSortingEnabled();
        tableWidget_publicForm->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_publicForm->item(0, 0);
        ___qtablewidgetitem7->setText(QApplication::translate("ObjectClassFormWidget", "default", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_publicForm->item(0, 1);
        ___qtablewidgetitem8->setText(QApplication::translate("ObjectClassFormWidget", "airplane", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_publicForm->item(0, 2);
        ___qtablewidgetitem9->setText(QApplication::translate("ObjectClassFormWidget", "normal", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_publicForm->item(0, 3);
        ___qtablewidgetitem10->setText(QApplication::translate("ObjectClassFormWidget", "10000", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_publicForm->item(0, 5);
        ___qtablewidgetitem11->setText(QApplication::translate("ObjectClassFormWidget", "\346\234\272\350\272\253/\346\234\272\347\277\274", 0, QApplication::UnicodeUTF8));
        tableWidget_publicForm->setSortingEnabled(__sortingEnabled);

        pushButton_editPublicFormPart->setText(QApplication::translate("ObjectClassFormWidget", "\347\274\226\350\276\221\345\205\254\346\234\211\345\275\242\346\200\201\351\203\250\344\273\266", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("ObjectClassFormWidget", "\347\247\201\346\234\211\345\275\242\346\200\201", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ObjectClassFormWidget", "\346\202\250\345\217\257\344\273\245\346\267\273\345\212\240\343\200\201\344\277\256\346\224\271\343\200\201\345\210\240\351\231\244\345\257\271\350\261\241\347\232\204\344\273\273\346\204\217\347\247\201\346\234\211\345\275\242\346\200\201", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_privateForm->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QApplication::translate("ObjectClassFormWidget", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_privateForm->horizontalHeaderItem(1);
        ___qtablewidgetitem13->setText(QApplication::translate("ObjectClassFormWidget", "\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_privateForm->horizontalHeaderItem(2);
        ___qtablewidgetitem14->setText(QApplication::translate("ObjectClassFormWidget", "\345\260\272\345\272\246", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_privateForm->horizontalHeaderItem(3);
        ___qtablewidgetitem15->setText(QApplication::translate("ObjectClassFormWidget", "\346\230\257\345\220\246\344\275\215\347\275\256\344\276\235\350\265\226", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_privateForm->horizontalHeaderItem(4);
        ___qtablewidgetitem16->setText(QApplication::translate("ObjectClassFormWidget", "\345\275\242\346\200\201\351\203\250\344\273\266", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_privateForm->verticalHeaderItem(0);
        ___qtablewidgetitem17->setText(QApplication::translate("ObjectClassFormWidget", "1", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled1 = tableWidget_privateForm->isSortingEnabled();
        tableWidget_privateForm->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_privateForm->item(0, 0);
        ___qtablewidgetitem18->setText(QApplication::translate("ObjectClassFormWidget", "default", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_privateForm->item(0, 1);
        ___qtablewidgetitem19->setText(QApplication::translate("ObjectClassFormWidget", "normal", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_privateForm->item(0, 2);
        ___qtablewidgetitem20->setText(QApplication::translate("ObjectClassFormWidget", "10000", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget_privateForm->item(0, 4);
        ___qtablewidgetitem21->setText(QApplication::translate("ObjectClassFormWidget", "\346\234\272\350\272\253/\346\234\272\347\277\274", 0, QApplication::UnicodeUTF8));
        tableWidget_privateForm->setSortingEnabled(__sortingEnabled1);

        pushButton_addPrivateForm->setText(QApplication::translate("ObjectClassFormWidget", "\346\267\273\345\212\240\347\247\201\346\234\211\345\275\242\346\200\201", 0, QApplication::UnicodeUTF8));
        pushButton_removePrivateForm->setText(QApplication::translate("ObjectClassFormWidget", "\347\247\273\351\231\244\347\247\201\346\234\211\345\275\242\346\200\201", 0, QApplication::UnicodeUTF8));
        pushButton_editPrivateFormPart->setText(QApplication::translate("ObjectClassFormWidget", "\347\274\226\350\276\221\347\247\201\346\234\211\345\275\242\346\200\201\351\203\250\344\273\266", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ObjectClassFormWidget: public Ui_ObjectClassFormWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTCLASSFORMWIDGET_H
