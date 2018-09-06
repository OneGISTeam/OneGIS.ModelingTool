/********************************************************************************
** Form generated from reading UI file 'createRelationClassDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATERELATIONCLASSDIALOG_H
#define UI_CREATERELATIONCLASSDIALOG_H

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
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CreateRelationClassDialog
{
public:
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_basicInfo;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_name;
    QLineEdit *lineEdit_name;
    QLabel *label_ID;
    QLineEdit *lineEdit_ID;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_addParam;
    QSpacerItem *spacer_4;
    QTableWidget *tableWidget_param;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *spacer;
    QPushButton *btn_addItem;
    QSpacerItem *spacer_2;
    QPushButton *btn_deleteItem;
    QSpacerItem *spacer_3;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *btn_ok;
    QPushButton *btn_cancel;

    void setupUi(QDialog *CreateRelationClassDialog)
    {
        if (CreateRelationClassDialog->objectName().isEmpty())
            CreateRelationClassDialog->setObjectName(QString::fromUtf8("CreateRelationClassDialog"));
        CreateRelationClassDialog->resize(545, 331);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/createRelationClass.png"), QSize(), QIcon::Normal, QIcon::Off);
        CreateRelationClassDialog->setWindowIcon(icon);
        gridLayout_3 = new QGridLayout(CreateRelationClassDialog);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_basicInfo = new QGroupBox(CreateRelationClassDialog);
        groupBox_basicInfo->setObjectName(QString::fromUtf8("groupBox_basicInfo"));
        gridLayout = new QGridLayout(groupBox_basicInfo);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_name = new QLabel(groupBox_basicInfo);
        label_name->setObjectName(QString::fromUtf8("label_name"));

        horizontalLayout->addWidget(label_name);

        lineEdit_name = new QLineEdit(groupBox_basicInfo);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        lineEdit_name->setEnabled(true);

        horizontalLayout->addWidget(lineEdit_name);

        label_ID = new QLabel(groupBox_basicInfo);
        label_ID->setObjectName(QString::fromUtf8("label_ID"));

        horizontalLayout->addWidget(label_ID);

        lineEdit_ID = new QLineEdit(groupBox_basicInfo);
        lineEdit_ID->setObjectName(QString::fromUtf8("lineEdit_ID"));
        lineEdit_ID->setEnabled(true);

        horizontalLayout->addWidget(lineEdit_ID);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_basicInfo);

        groupBox = new QGroupBox(CreateRelationClassDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_addParam = new QLabel(groupBox);
        label_addParam->setObjectName(QString::fromUtf8("label_addParam"));

        horizontalLayout_3->addWidget(label_addParam);

        spacer_4 = new QSpacerItem(45, 25, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(spacer_4);


        verticalLayout->addLayout(horizontalLayout_3);

        tableWidget_param = new QTableWidget(groupBox);
        if (tableWidget_param->columnCount() < 5)
            tableWidget_param->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_param->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_param->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_param->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_param->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_param->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget_param->setObjectName(QString::fromUtf8("tableWidget_param"));

        verticalLayout->addWidget(tableWidget_param);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        spacer = new QSpacerItem(48, 28, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(spacer);

        btn_addItem = new QPushButton(groupBox);
        btn_addItem->setObjectName(QString::fromUtf8("btn_addItem"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_addItem->setIcon(icon1);

        horizontalLayout_2->addWidget(btn_addItem);

        spacer_2 = new QSpacerItem(48, 28, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(spacer_2);

        btn_deleteItem = new QPushButton(groupBox);
        btn_deleteItem->setObjectName(QString::fromUtf8("btn_deleteItem"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/remove_circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_deleteItem->setIcon(icon2);

        horizontalLayout_2->addWidget(btn_deleteItem);

        spacer_3 = new QSpacerItem(48, 28, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(spacer_3);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        btn_ok = new QPushButton(CreateRelationClassDialog);
        btn_ok->setObjectName(QString::fromUtf8("btn_ok"));

        hboxLayout->addWidget(btn_ok);

        btn_cancel = new QPushButton(CreateRelationClassDialog);
        btn_cancel->setObjectName(QString::fromUtf8("btn_cancel"));

        hboxLayout->addWidget(btn_cancel);


        verticalLayout_2->addLayout(hboxLayout);


        gridLayout_3->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(CreateRelationClassDialog);
        QObject::connect(btn_ok, SIGNAL(clicked()), CreateRelationClassDialog, SLOT(accept()));
        QObject::connect(btn_cancel, SIGNAL(clicked()), CreateRelationClassDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CreateRelationClassDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateRelationClassDialog)
    {
        CreateRelationClassDialog->setWindowTitle(QApplication::translate("CreateRelationClassDialog", "\345\210\233\345\273\272\345\205\263\347\263\273\347\261\273", 0, QApplication::UnicodeUTF8));
        groupBox_basicInfo->setTitle(QApplication::translate("CreateRelationClassDialog", "\345\237\272\346\234\254\344\277\241\346\201\257\346\240\217", 0, QApplication::UnicodeUTF8));
        label_name->setText(QApplication::translate("CreateRelationClassDialog", "\345\205\263\347\263\273\347\261\273\345\236\213\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_ID->setText(QApplication::translate("CreateRelationClassDialog", "\345\205\263\347\263\273\347\261\273\345\236\213\346\240\207\350\257\206\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("CreateRelationClassDialog", "\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_addParam->setText(QApplication::translate("CreateRelationClassDialog", "\350\257\267\345\257\271\350\257\245\345\205\263\347\263\273\347\232\204\345\217\202\346\225\260\350\277\233\350\241\214\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_param->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CreateRelationClassDialog", "\345\217\202\346\225\260\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_param->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CreateRelationClassDialog", "\345\217\202\346\225\260\346\240\207\350\257\206", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_param->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("CreateRelationClassDialog", "\345\200\274\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_param->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("CreateRelationClassDialog", "\351\273\230\350\256\244\345\200\274", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_param->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("CreateRelationClassDialog", "\345\215\225\344\275\215", 0, QApplication::UnicodeUTF8));
        btn_addItem->setText(QApplication::translate("CreateRelationClassDialog", "\346\267\273\345\212\240\344\270\200\346\235\241\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        btn_deleteItem->setText(QApplication::translate("CreateRelationClassDialog", "\345\210\240\351\231\244\350\257\245\346\235\241\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        btn_ok->setText(QApplication::translate("CreateRelationClassDialog", "\345\210\233\345\273\272", 0, QApplication::UnicodeUTF8));
        btn_cancel->setText(QApplication::translate("CreateRelationClassDialog", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CreateRelationClassDialog: public Ui_CreateRelationClassDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATERELATIONCLASSDIALOG_H
