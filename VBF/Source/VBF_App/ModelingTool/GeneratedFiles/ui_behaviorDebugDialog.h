/********************************************************************************
** Form generated from reading UI file 'behaviorDebugDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BEHAVIORDEBUGDIALOG_H
#define UI_BEHAVIORDEBUGDIALOG_H

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
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BehaviorDebugDialog
{
public:
    QGridLayout *gridLayout_7;
    QGridLayout *gridLayout_6;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTreeWidget *treeWidget_objects;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_name;
    QLabel *label_3;
    QLineEdit *lineEdit_alias;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QSpacerItem *verticalSpacer;
    QTextEdit *textEdit_desc;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QTableWidget *tableWidget_params;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_5;
    QTableWidget *tableWidget_inputs;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_debug;
    QPushButton *pushButton_cancel;

    void setupUi(QDialog *BehaviorDebugDialog)
    {
        if (BehaviorDebugDialog->objectName().isEmpty())
            BehaviorDebugDialog->setObjectName(QString::fromUtf8("BehaviorDebugDialog"));
        BehaviorDebugDialog->resize(758, 436);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/behaviorDebug.png"), QSize(), QIcon::Normal, QIcon::Off);
        BehaviorDebugDialog->setWindowIcon(icon);
        BehaviorDebugDialog->setModal(false);
        gridLayout_7 = new QGridLayout(BehaviorDebugDialog);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        groupBox = new QGroupBox(BehaviorDebugDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        treeWidget_objects = new QTreeWidget(groupBox);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/object.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/behaviorComponent.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget_objects);
        __qtreewidgetitem->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem1->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem2->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem3->setIcon(0, icon2);
        treeWidget_objects->setObjectName(QString::fromUtf8("treeWidget_objects"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeWidget_objects->sizePolicy().hasHeightForWidth());
        treeWidget_objects->setSizePolicy(sizePolicy);
        treeWidget_objects->setMinimumSize(QSize(120, 0));
        treeWidget_objects->setMaximumSize(QSize(16777215, 16777215));
        treeWidget_objects->header()->setVisible(false);

        verticalLayout->addWidget(treeWidget_objects);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout_6->addWidget(groupBox, 0, 0, 3, 1);

        groupBox_2 = new QGroupBox(BehaviorDebugDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setEnabled(false);
        groupBox_2->setCheckable(false);
        groupBox_2->setChecked(false);
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        lineEdit_name = new QLineEdit(groupBox_2);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));

        gridLayout_2->addWidget(lineEdit_name, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        lineEdit_alias = new QLineEdit(groupBox_2);
        lineEdit_alias->setObjectName(QString::fromUtf8("lineEdit_alias"));

        gridLayout_2->addWidget(lineEdit_alias, 1, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        gridLayout_2->addLayout(verticalLayout_2, 2, 0, 1, 1);

        textEdit_desc = new QTextEdit(groupBox_2);
        textEdit_desc->setObjectName(QString::fromUtf8("textEdit_desc"));

        gridLayout_2->addWidget(textEdit_desc, 2, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_2, 0, 1, 1, 1);

        groupBox_3 = new QGroupBox(BehaviorDebugDialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setEnabled(true);
        groupBox_3->setCheckable(false);
        groupBox_3->setChecked(false);
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        tableWidget_params = new QTableWidget(groupBox_3);
        if (tableWidget_params->columnCount() < 4)
            tableWidget_params->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_params->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_params->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_params->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_params->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget_params->setObjectName(QString::fromUtf8("tableWidget_params"));

        gridLayout_4->addWidget(tableWidget_params, 0, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_3, 1, 1, 1, 1);

        groupBox_4 = new QGroupBox(BehaviorDebugDialog);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_5 = new QGridLayout(groupBox_4);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        tableWidget_inputs = new QTableWidget(groupBox_4);
        if (tableWidget_inputs->columnCount() < 4)
            tableWidget_inputs->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_inputs->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_inputs->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_inputs->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_inputs->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        tableWidget_inputs->setObjectName(QString::fromUtf8("tableWidget_inputs"));

        gridLayout_5->addWidget(tableWidget_inputs, 0, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_4, 2, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(288, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_debug = new QPushButton(BehaviorDebugDialog);
        pushButton_debug->setObjectName(QString::fromUtf8("pushButton_debug"));
        pushButton_debug->setIcon(icon);

        horizontalLayout->addWidget(pushButton_debug);

        pushButton_cancel = new QPushButton(BehaviorDebugDialog);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));

        horizontalLayout->addWidget(pushButton_cancel);


        gridLayout_6->addLayout(horizontalLayout, 3, 0, 1, 2);


        gridLayout_7->addLayout(gridLayout_6, 0, 0, 1, 1);


        retranslateUi(BehaviorDebugDialog);

        QMetaObject::connectSlotsByName(BehaviorDebugDialog);
    } // setupUi

    void retranslateUi(QDialog *BehaviorDebugDialog)
    {
        BehaviorDebugDialog->setWindowTitle(QApplication::translate("BehaviorDebugDialog", "\345\257\271\350\261\241\350\241\214\344\270\272\350\260\203\350\257\225", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("BehaviorDebugDialog", "\345\205\267\346\234\211\350\241\214\344\270\272\347\232\204\345\257\271\350\261\241\350\247\206\345\233\276", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("BehaviorDebugDialog", "\350\257\267\351\200\211\346\213\251\346\202\250\350\246\201\350\260\203\350\257\225\347\232\204\345\257\271\350\261\241\350\241\214\344\270\272\357\274\232", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_objects->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("BehaviorDebugDialog", "1", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = treeWidget_objects->isSortingEnabled();
        treeWidget_objects->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget_objects->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("BehaviorDebugDialog", "\347\233\26495", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("BehaviorDebugDialog", "\351\243\236\350\241\214\350\241\214\344\270\272", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QApplication::translate("BehaviorDebugDialog", "\346\211\223\345\207\273\350\241\214\344\270\272", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem1->child(2);
        ___qtreewidgetitem4->setText(0, QApplication::translate("BehaviorDebugDialog", "\345\267\241\350\210\252\350\241\214\344\270\272", 0, QApplication::UnicodeUTF8));
        treeWidget_objects->setSortingEnabled(__sortingEnabled);

        groupBox_2->setTitle(QApplication::translate("BehaviorDebugDialog", "\350\241\214\344\270\272\345\237\272\346\234\254\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("BehaviorDebugDialog", "\350\241\214\344\270\272\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("BehaviorDebugDialog", "\350\241\214\344\270\272\345\210\253\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("BehaviorDebugDialog", "\350\241\214\344\270\272\346\217\217\350\277\260\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("BehaviorDebugDialog", "\345\217\202\346\225\260\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_params->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("BehaviorDebugDialog", "\345\217\202\346\225\260\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_params->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("BehaviorDebugDialog", "\345\217\202\346\225\260\345\210\253\345\220\215", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_params->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("BehaviorDebugDialog", "\345\217\202\346\225\260\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_params->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("BehaviorDebugDialog", "\345\217\202\346\225\260\345\200\274", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("BehaviorDebugDialog", "*\350\276\223\345\205\245\345\210\227\350\241\250*", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_inputs->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("BehaviorDebugDialog", "\350\276\223\345\205\245\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_inputs->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("BehaviorDebugDialog", "\350\276\223\345\205\245\345\210\253\345\220\215", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_inputs->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("BehaviorDebugDialog", "\350\276\223\345\205\245\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_inputs->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QApplication::translate("BehaviorDebugDialog", "\350\276\223\345\205\245\345\200\274", 0, QApplication::UnicodeUTF8));
        pushButton_debug->setText(QApplication::translate("BehaviorDebugDialog", "\350\260\203\350\257\225", 0, QApplication::UnicodeUTF8));
        pushButton_cancel->setText(QApplication::translate("BehaviorDebugDialog", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BehaviorDebugDialog: public Ui_BehaviorDebugDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEHAVIORDEBUGDIALOG_H
