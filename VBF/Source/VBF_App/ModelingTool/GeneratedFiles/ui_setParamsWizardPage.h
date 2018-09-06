/********************************************************************************
** Form generated from reading UI file 'setParamsWizardPage.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETPARAMSWIZARDPAGE_H
#define UI_SETPARAMSWIZARDPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_SetParamsWizardPage
{
public:
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableWidget;
    QFrame *line;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *comboBox;
    QWidget *widget_mathmode;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QLineEdit *lineEdit_2;

    void setupUi(QWizardPage *SetParamsWizardPage)
    {
        if (SetParamsWizardPage->objectName().isEmpty())
            SetParamsWizardPage->setObjectName(QString::fromUtf8("SetParamsWizardPage"));
        SetParamsWizardPage->resize(537, 425);
        gridLayout_5 = new QGridLayout(SetParamsWizardPage);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        groupBox = new QGroupBox(SetParamsWizardPage);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(288, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_2);

        tableWidget = new QTableWidget(groupBox);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (tableWidget->rowCount() < 3)
            tableWidget->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setItem(0, 3, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setItem(0, 4, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setItem(0, 5, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setItem(1, 1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setItem(1, 2, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setItem(1, 3, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setItem(1, 4, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setItem(1, 5, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setItem(2, 1, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setItem(2, 2, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget->setItem(2, 3, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget->setItem(2, 4, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget->setItem(2, 5, __qtablewidgetitem26);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout_2->addWidget(tableWidget);

        line = new QFrame(groupBox);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setCheckable(true);
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout);

        widget_mathmode = new QWidget(groupBox_2);
        widget_mathmode->setObjectName(QString::fromUtf8("widget_mathmode"));
        gridLayout_2 = new QGridLayout(widget_mathmode);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(widget_mathmode);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        lineEdit = new QLineEdit(widget_mathmode);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label_4 = new QLabel(widget_mathmode);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(widget_mathmode);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        verticalLayout->addWidget(widget_mathmode);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);


        gridLayout_4->addLayout(verticalLayout_2, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(SetParamsWizardPage);

        QMetaObject::connectSlotsByName(SetParamsWizardPage);
    } // setupUi

    void retranslateUi(QWizardPage *SetParamsWizardPage)
    {
        SetParamsWizardPage->setWindowTitle(QApplication::translate("SetParamsWizardPage", "WizardPage", 0, QApplication::UnicodeUTF8));
        SetParamsWizardPage->setTitle(QApplication::translate("SetParamsWizardPage", "\347\254\254\344\270\211\346\255\245\357\274\232\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        SetParamsWizardPage->setSubTitle(QApplication::translate("SetParamsWizardPage", "\346\202\250\345\215\263\345\260\206\346\236\204\345\273\272\345\246\202\344\270\213\345\210\227\350\241\250\344\270\255\347\232\204\345\205\263\347\263\273\357\274\214\350\257\267\345\257\271\345\205\263\347\263\273\347\232\204\345\217\202\346\225\260\350\277\233\350\241\214\344\277\256\346\224\271\357\274\214\345\271\266\345\257\271\345\205\263\347\263\273\347\232\204\345\274\272\345\272\246\350\277\233\350\241\214\350\256\276\347\275\256\343\200\202", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SetParamsWizardPage", "\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SetParamsWizardPage", "\345\217\202\346\225\260\345\210\227\350\241\250\357\274\232", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SetParamsWizardPage", "\350\265\267\345\247\213\345\257\271\350\261\241", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SetParamsWizardPage", "\347\273\210\346\255\242\345\257\271\350\261\241", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("SetParamsWizardPage", "\345\205\263\347\263\273\345\274\272\345\272\246", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("SetParamsWizardPage", "\345\217\202\346\225\2601", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("SetParamsWizardPage", "\345\217\202\346\225\2602", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("SetParamsWizardPage", "\345\217\202\346\225\2603", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("SetParamsWizardPage", "1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem7->setText(QApplication::translate("SetParamsWizardPage", "2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem8->setText(QApplication::translate("SetParamsWizardPage", "3", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->item(0, 0);
        ___qtablewidgetitem9->setText(QApplication::translate("SetParamsWizardPage", "\347\233\26495001", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->item(0, 1);
        ___qtablewidgetitem10->setText(QApplication::translate("SetParamsWizardPage", "\347\233\26495002", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->item(0, 2);
        ___qtablewidgetitem11->setText(QApplication::translate("SetParamsWizardPage", "0.87", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->item(0, 3);
        ___qtablewidgetitem12->setText(QApplication::translate("SetParamsWizardPage", "980.09", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->item(0, 4);
        ___qtablewidgetitem13->setText(QApplication::translate("SetParamsWizardPage", "764.97", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->item(0, 5);
        ___qtablewidgetitem14->setText(QApplication::translate("SetParamsWizardPage", "65.99", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->item(1, 0);
        ___qtablewidgetitem15->setText(QApplication::translate("SetParamsWizardPage", "\347\233\26495002", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->item(1, 1);
        ___qtablewidgetitem16->setText(QApplication::translate("SetParamsWizardPage", "\347\233\26495003", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->item(1, 2);
        ___qtablewidgetitem17->setText(QApplication::translate("SetParamsWizardPage", "0.76", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->item(1, 3);
        ___qtablewidgetitem18->setText(QApplication::translate("SetParamsWizardPage", "875.00", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->item(1, 4);
        ___qtablewidgetitem19->setText(QApplication::translate("SetParamsWizardPage", "23.87", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->item(1, 5);
        ___qtablewidgetitem20->setText(QApplication::translate("SetParamsWizardPage", "46.87", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->item(2, 0);
        ___qtablewidgetitem21->setText(QApplication::translate("SetParamsWizardPage", "\347\233\26495003", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->item(2, 1);
        ___qtablewidgetitem22->setText(QApplication::translate("SetParamsWizardPage", "\347\233\26495001", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->item(2, 2);
        ___qtablewidgetitem23->setText(QApplication::translate("SetParamsWizardPage", "0.34", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget->item(2, 3);
        ___qtablewidgetitem24->setText(QApplication::translate("SetParamsWizardPage", "198.99", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget->item(2, 4);
        ___qtablewidgetitem25->setText(QApplication::translate("SetParamsWizardPage", "24.87", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget->item(2, 5);
        ___qtablewidgetitem26->setText(QApplication::translate("SetParamsWizardPage", "98.09", 0, QApplication::UnicodeUTF8));
        tableWidget->setSortingEnabled(__sortingEnabled);

        groupBox_2->setTitle(QApplication::translate("SetParamsWizardPage", "\350\256\276\347\275\256\345\274\272\345\272\246\350\256\241\347\256\227\346\250\241\345\236\213", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SetParamsWizardPage", "\346\250\241\345\236\213\351\200\211\346\213\251\357\274\232", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("SetParamsWizardPage", "\346\250\241\345\236\213\344\270\200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetParamsWizardPage", "\346\250\241\345\236\213\344\272\214", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetParamsWizardPage", "\346\250\241\345\236\213\344\270\211", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("SetParamsWizardPage", "\346\250\241\345\236\213\345\217\202\346\225\260\344\270\200\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SetParamsWizardPage", "\346\250\241\345\236\213\345\217\202\346\225\260\344\272\214\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SetParamsWizardPage: public Ui_SetParamsWizardPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETPARAMSWIZARDPAGE_H
